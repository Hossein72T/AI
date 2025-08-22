#include "CLRFMSelectChannelForm.h"

#include "CLKTS.h"
#include "CLImages.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "RFM_driver.h"

#define	CLRFMSelectChannelForm_ScanButton_Rectangle				160, 190, 254, 229

#define	CLRFMSelectChannelForm_ChannelList_UpButton_Rectangle	253, 25, 312, 88
#define	CLRFMSelectChannelForm_ChannelList_DownButton_Rectangle	253, 107, 312, 170

#define	CLRFMSelectChannelForm_ChannelList_Frame					8, 25, 243, 172
#define	CLRFMSelectChannelForm_ChannelList_FirstItem_Icon_Rectangle	13, 30, 32, 41
#define	CLRFMSelectChannelForm_ChannelList_FirstItem_Text_Point		36, 30
#define	CLRFMSelectChannelForm_ChannelList_FirstItem_Text_Length	25

#define CLRFMSelectChannelForm_ChannelList_VisibleItemCount			8
#define CLRFMSelectChannelForm_ScanningPanelRectangle				15, 85, 304, 144

const unsigned long Scan_CheckChannelMilliseconds = 5500;

CLFormResult CLRFMSelectChannelForm_Open( unsigned short options,
	byte extOptions )
{
	CLRFMSelectChannelForm	form;

	return form.Open( options, extOptions );
}

void CLRFMSelectChannelForm_KTSConnect_Callback( CLKTSConnectState currentState,
	int step, int stepCount )
{
	char	text[ 40 ];

	switch (currentState)
	{
		case CLKTSConnectState_Init:
			break;
		
		case CLKTSConnectState_TrySerialLink:
			sprintf( text, "%s COM", CLLocalitation::GetText( CLTextId_CONNECTING ) );
			CLGraphics::DrawBoxWithText( CLRectangle( CLRFMSelectChannelForm_ScanningPanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
				0x778899, RGBColor_White,
				1, RGBColor_Black,
				text );
			break;

		case CLKTSConnectState_TryRFMLink:
			sprintf( text, "%s  RFM #%d", CLLocalitation::GetText( CLTextId_CONNECTING ),
				sdata_wi.channel );
			CLGraphics::DrawBoxWithText( CLRectangle( CLRFMSelectChannelForm_ScanningPanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
				0x778899, RGBColor_White,
				1, RGBColor_Black,
				text );
			break;

		default:
			sprintf( text, "%s %s %d", CLLocalitation::GetText( CLTextId_UNIT ),
				CLLocalitation::GetText( CLTextId_SEARCHING ),
				step );
			CLGraphics::DrawBoxWithText( CLRectangle( CLRFMSelectChannelForm_ScanningPanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
				0x778899, RGBColor_White,
				1, RGBColor_Black,
				text );
			break;

	}
}

// =============================================================================
// CLRFMSelectChannelForm [class]
// -----------------------------------------------------------------------------
CLRFMSelectChannelForm::CLRFMSelectChannelForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_SelectedChannelUpButtonRectangle.Set( CLRFMSelectChannelForm_ChannelList_UpButton_Rectangle );
	m_SelectedChannelDownButtonRectangle.Set( CLRFMSelectChannelForm_ChannelList_DownButton_Rectangle );
	m_ScanButtonRectangle.Set( CLRFMSelectChannelForm_ScanButton_Rectangle );
	
	m_Channel_ProgressiveTouchUpDown.Set( 10, 1, 200, 2, 100, 2 );
}

CLFormResult CLRFMSelectChannelForm::Open( unsigned short options,
	byte extOptions )
{
	int				touchX, touchY;
	CLFormResult	formResult;
	byte			currentRFMSignalLevel;
	
	// Inizializza i dati
	SetState( CLState_Initializing );

	m_ExtState					= CLExtState_Default;
	m_Options					= options;
	m_ExtOptions				= extOptions;
	m_FirstDisplayedChannel		= 1;
	m_Scanner_InProgress		= false;

	// Set Channel States
	for (int channelsCounter = 0; channelsCounter < RFM_CHANNELS_MAX; channelsCounter++)
		m_ChannelStates[ channelsCounter ]	= CLRFMScanner::CLChannelState_Unknow;

	// Set Selected Channel
	SetSelectedChannel( gKTSEeprom.GetRFMChannel() );
	
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	if (!(extOptions & CLExtOption_NoAutoScanning))
		Scan_Start();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		Scan_Process();

		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (!(m_Options & CLFormOption_HideButton_Home) &&
				!(m_ExtState & CLExtState_KTSInvalid) &&
				m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ) &&
				!(m_ExtState & CLExtState_KTSInvalid))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			else
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OkButtonRectangle );

				// Fermiamo eventuale scansione
				Scan_Stop();

				// Nel caso in cui sono in running, effettuo il cambio canale
				if (gKTSGlobal.RunningMode == CLKTSRunningMode_Running)
				{
					CLLCDCommon::RenderPanelInfo( (char*) CLLocalitation::GetText( CLTextId_RFM__CHECKING_CHANNEL_IN_PROGRESS ),
						0x778899, RGBColor_White, RGBColor_Black );

					// Verifico che il canale selezionato sia libero
					m_Scanner.Scan( m_SelectedChannel, Scan_CheckChannelMilliseconds );
					while (m_Scanner.IsInProgress())
					{
						CLKTS::Process();
						CLKTS::Pir_Process();
						m_Scanner.Process();
					}

					m_ChannelStates[ m_Scanner.GetChannel() - 1 ]	= m_Scanner.GetChannelState();
					RefreshChannels();

					// Se il canale è libero, ok comunica all'rd l'intenzione di cambiare canale
					if (m_ChannelStates[ m_SelectedChannel - 1 ] == CLRFMScanner::CLChannelState_Free)
					{
						if (Save( options ))
						{
							formResult	= CLFormResult_Ok;
							break;
						}
					}
					else
					{
						CLLCDCommon::RenderPanelInfo( (char*) CLLocalitation::GetText( CLTextId_RFM__ALERT_CHANNEL_BUSY ),
							0xDA5757, RGBColor_White, RGBColor_Black,
							3000 );
					}
				}
				else
				// Nella fase di inizializzazione imposta semplicemente il canale selezionato
				if (gKTSGlobal.RunningMode == CLKTSRunningMode_Initializing)
				{
					if (m_SelectedChannel != gKTSEeprom.GetRFMChannel())
						gKTSEeprom.SetRFMChannel( m_SelectedChannel );
					formResult	= CLFormResult_Ok;
					break;
				}

				RenderPage();

				//if (selectedChannel == NULL)
				//{
				//	CLKTSConnectState	connectState;
				//	char				text[ 40 ];
				//		
				//	// Prova la connessione alla nuova unità
				//	SetChannelNum( m_SelectedChannel );
				//	connectState	= CLKTS::Connect( CLRFMSelectChannelForm_KTSConnect_Callback,
				//		CLKTSConnectOption_SkipSerialLink );

				//	if (connectState == CLKTSConnectState_Connected)
				//	{
				//		gKTSEeprom.SetRFMChannel( m_SelectedChannel );
				//		formResult	= CLFormResult_Ok;
				//		break;
				//	}

				//		// Non è riuscita la connessione
				//		SetChannelNum( gKTSEeprom.GetRFMChannel() );

				//		// Se siamo in running ed è stata letta anche una parte di eeprom
				//		// lo stato del KTS è compromesso
				//		if (gKTSGlobal.RunningMode == CLKTSRunningMode_Running &&
				//			connectState > CLKTSConnectState_LinkConnected)
				//		{
				//			gKTSGlobal.RunningMode	= CLKTSRunningMode_Initializing;
				//			m_KTSIsInvalid			= true;
				//		}

				//		sprintf( text, "%s: %s", CLLocalitation::GetText( CLTextId_ERROR ),
				//			CLLocalitation::GetText( CLTextId_UNIT_NOT_FOUND ) );
				//		CLGraphics::DrawBoxWithText( CLRFMSelectChannelForm_ScanningPanelRectangle, CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
				//			0xDA5757, RGBColor_White,
				//			1, RGBColor_Black, /*0xE58989,*/
				//			text );

				//		CLKTS::Delay( 2000 );
				//		RenderPage();
				//	}
				//	else
				//	{
				//		formResult	= CLFormResult_Ok;
				//		break;
				//	}
				//}
				//else
				//{
				//	formResult			= CLFormResult_Ok;
				//	*selectedChannel	= m_SelectedChannel;
				//	break;
				//}
			}
			else
			// Up Button
			if (m_SelectedChannelUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_SelectedChannelUpButtonRectangle );

				m_Channel_ProgressiveTouchUpDown.Reset();
				while (m_Channel_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Channel_ProgressiveTouchUpDown.CanIncrement())
						SetSelectedChannel( m_SelectedChannel - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_SelectedChannelUpButtonRectangle );
			}
			else
			// Down Button
			if (m_SelectedChannelDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_SelectedChannelDownButtonRectangle );

				m_Channel_ProgressiveTouchUpDown.Reset();
				while (m_Channel_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Channel_ProgressiveTouchUpDown.CanIncrement())
						SetSelectedChannel( m_SelectedChannel + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_SelectedChannelDownButtonRectangle );
			}
			// 'Scan' Button
			if (!m_Scanner_InProgress && m_ScanButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ScanButtonRectangle );
				Scan_Start();
			}
			else
				WaitForTouchRelease();
		}
    }

	Scan_Stop();
	SetChannelNum( gKTSEeprom.GetRFMChannel() );

	return formResult;
}

bool CLRFMSelectChannelForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveCHWireless;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveCHWireless	= gRDEeprom.chWireless;

	// Imposta i nuovi dati
	gRDEeprom.chWireless	= m_SelectedChannel;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, chWireless ),
		sizeof(gRDEeprom.chWireless),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se sono in connessione rfm
	// -----------------------------------------
	if (gKTSGlobal.ComLinkType == BY_WIRELESS)
	{
		// Indipendentemente che sia andata a buon fine o meno
		// cambio canale
		gKTSEeprom.SetRFMChannel( m_SelectedChannel );
		SetChannelNum( m_SelectedChannel );

		// Proviamo ad inviare per x volte il polling
		for (int retriesCounter = 0; retriesCounter < 6; retriesCounter++)
		{
			// Accoda la richiesta di Polling
			KTS_QueuePollingBaseRequest( &writeEeprom_Status );

			// Aspetta l'elaborazione della richiesta
			while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
				CLKTS::Process();
			
			CLKTS::Pir_Process();
			
			// Se ricevuto il polling, visualizza msg e exit
			if (writeEeprom_Status.Status == COM_REQUEST_STATUS_COMPLETED)
			{
				// Visualizza il messaggio di ok
				if (CLFormOption_CanShowWriteMessage_Success( options ))
					CLLCDCommon::WriteDataPanel_DisplaySuccess();

				return true;
			}
		}

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	// Nel caso di serial
	// -----------------------------------------
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.chWireless	= saveCHWireless;

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	gKTSEeprom.SetRFMChannel( m_SelectedChannel );

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLRFMSelectChannelForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_RFM__CHANGE_CHANNEL ),
		NULL );

	// Display Home Button
	if (!(m_Options & CLFormOption_HideButton_Home) &&
		!(m_ExtState & CLExtState_KTSInvalid))
		CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(),
			Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	if (!(m_ExtState & CLExtState_KTSInvalid))
		CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
			GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Draw Frame 'LIST CHANNELS'
	CLGraphics::DrawBox( CLRectangle( CLRFMSelectChannelForm_ChannelList_Frame ),
		GenericForm_Group_Style );
	
	RefreshChannels();
	RenderDynamicObjects();
}

void CLRFMSelectChannelForm::RefreshChannels()
{
	char		text[ 40 ];
	CLRectangle	itemIconRectangle( CLRFMSelectChannelForm_ChannelList_FirstItem_Icon_Rectangle );
	CLPoint		itemTextPoint( CLRFMSelectChannelForm_ChannelList_FirstItem_Text_Point );

	// Display list caption
	sprintf( text, "  [ #] %s", CLLocalitation::GetText( CLTextId_RFM__STATUS ) );
	CLGraphics::DrawText( itemTextPoint.GetX(), itemTextPoint.GetY(), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White,
		text, CLRFMSelectChannelForm_ChannelList_FirstItem_Text_Length );
	
	itemTextPoint.MoveOffset( 0, 16 );
	itemIconRectangle.MoveOffset( 0, 16 );

	for (int channelsCounter = 0; channelsCounter < CLRFMSelectChannelForm_ChannelList_VisibleItemCount; channelsCounter++)
	{
		int			channel	= m_FirstDisplayedChannel + channelsCounter;
		CLImage*	image	= NULL;

		*text	= '\0';
		if (channel <= RFM_CHANNELS_MAX)
		{
			if (m_Scanner.GetRunningMode() == CLKTSRunningMode_Running)
			{
				switch (m_ChannelStates[ channel - 1 ])
				{
					case CLRFMScanner::CLChannelState_InProgress:
						image	= &RFMChannelScanningImage;
						break;

					case CLRFMScanner::CLChannelState_Busy:
						image	= &RFMChannelBusyImage;
						break;

					case CLRFMScanner::CLChannelState_Free:
						image	= &RFMChannelOkImage;
						break;
				}
			}
			else
			if (m_Scanner.GetRunningMode() == CLKTSRunningMode_Initializing)
			{
				switch (m_ChannelStates[ channel - 1 ])
				{
					case CLRFMScanner::CLChannelState_InProgress:
						image	= &RFMChannelScanningImage;
						break;

					case CLRFMScanner::CLChannelState_Busy:
						image	= &RFMChannelBusyImage;
						break;

					case CLRFMScanner::CLChannelState_Free:
						image	= &RFMChannelOkImage;
						break;
				}
			}

			sprintf( text, "%s[%2d] %s",
				((m_ExtOptions & CLExtOption_HighlightCurrentChannel) && channel == gKTSEeprom.GetRFMChannel() ? ">>" : "  "),
				channel,
				CLRFMScanner::GetChannelStateText( (CLRFMScanner::CLChannelState) m_ChannelStates[ channel - 1 ] ));
		}

		// Draw Icon
		if (image != NULL)
		{
			CLGraphics::DrawBoxWithDrawer( itemIconRectangle, CLGraphicStyleOptions_HVAlign_Center,
				RGBColor_Black, RGBColor_White,
				image );
		}
		else
		{
			CLGraphics::DrawBox( itemIconRectangle, CLGraphicStyleOptions_HVAlign_Center,
				RGBColor_Black );
		}

		// Draw Text
		CLGraphics::DrawText( itemTextPoint.GetX(), itemTextPoint.GetY(), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
			(channel == m_SelectedChannel ? RGBColor_Green : RGBColor_Black),
			(channel == m_SelectedChannel ? RGBColor_Black : RGBColor_White),
			text, CLRFMSelectChannelForm_ChannelList_FirstItem_Text_Length );

		itemTextPoint.MoveOffset( 0, 16 );
		itemIconRectangle.MoveOffset( 0, 16 );
	}
}

void CLRFMSelectChannelForm::RenderDynamicObjects()
{
	// Tasto 'Up'
	CLLCDCommon::DrawGenericButton( m_SelectedChannelUpButtonRectangle,
		(m_SelectedChannel == 1 ? GenericButtonStyle_Disabled_UpDown : GenericButtonStyle_Normal_UpDown),
		&UpMonoImage );

	// Tasto 'Down'
	CLLCDCommon::DrawGenericButton( m_SelectedChannelDownButtonRectangle,
		(m_SelectedChannel == RFM_CHANNELS_MAX ? GenericButtonStyle_Disabled_UpDown : GenericButtonStyle_Normal_UpDown),
		&DownMonoImage );

	// Tasto 'Scan'
	CLGraphics::DrawBoxWithDrawer( m_ScanButtonRectangle,
		(m_Scanner_InProgress ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont),
		&RefreshMonoImage );

}

bool CLRFMSelectChannelForm::Scan_Start()
{
	if (m_Scanner_InProgress)
		return false;

	// Reset Channel Info
	for (int channelsCounter = 0; channelsCounter < RFM_CHANNELS_MAX; channelsCounter++)
		m_ChannelStates[ channelsCounter ]	= CLRFMScanner::CLChannelState_Unknow;
	
	RefreshChannels();
	RenderDynamicObjects();

	m_Scanner_InProgress		= true;
	m_Scanner_CurrentChannel	= 0;

	return true;
}

void CLRFMSelectChannelForm::Scan_Stop()
{
	m_Scanner_InProgress	= false;
	m_Scanner.Stop();
}

void CLRFMSelectChannelForm::Scan_Process()
{
	static unsigned long	scanWait_Milliseconds	= 0;

	if (!m_Scanner_InProgress)
		return;

	m_Scanner.Process();

	if (m_Scanner.GetChannel() == m_Scanner_CurrentChannel &&
		m_ChannelStates[ m_Scanner.GetChannel() - 1 ] != m_Scanner.GetChannelState())
	{
		m_ChannelStates[ m_Scanner.GetChannel() - 1 ]	= m_Scanner.GetChannelState();
		RefreshChannels();
	}

	if (!m_Scanner.IsInProgress())
	{
		if (millis() - scanWait_Milliseconds > 2000 ||
			millis() < scanWait_Milliseconds)
		{
			m_Scanner_CurrentChannel++;
			if (m_Scanner_CurrentChannel <= RFM_CHANNELS_MAX)
			{
				if (!m_Scanner.Scan( m_Scanner_CurrentChannel, Scan_CheckChannelMilliseconds ))
					Scan_Stop();
			}
			else
				Scan_Stop();
		}
	}
	else
		scanWait_Milliseconds	= millis();

	RenderDynamicObjects();
}		

void CLRFMSelectChannelForm::SetSelectedChannel( byte channel )
{
	if (channel < RFM_CHANNELS_MIN)
		channel	= RFM_CHANNELS_MIN;
	else
	if (channel > RFM_CHANNELS_MAX)
		channel	= RFM_CHANNELS_MAX;

	if (m_SelectedChannel == channel)
		return;

	if (channel > (m_FirstDisplayedChannel + CLRFMSelectChannelForm_ChannelList_VisibleItemCount - 1))
		m_FirstDisplayedChannel	= (channel - CLRFMSelectChannelForm_ChannelList_VisibleItemCount) + 1;
	else
	if (channel < m_FirstDisplayedChannel)
		m_FirstDisplayedChannel	= channel;

	m_SelectedChannel	= channel;

	if (GetState() == CLState_Running)
		RefreshChannels();
}
// -----------------------------------------------------------------------------
// CLRFMSelectChannelForm [class]
// =============================================================================

