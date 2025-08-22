#include "CLOutputConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLAccessory.h"
#include "CLInputOutput.h"

#define CLOutputConfig_SelectOutputFrameRectangle		6, 33, 52, 173
#define CLOutputConfig_Output1ButtonRectangle			15, 41, 44, 100
#define CLOutputConfig_Output2ButtonRectangle			15, 107, 44, 166

#define CLOutputConfig_SelectEventFrameRectangle		59, 33, 308, 148
#define CLOutputConfig_SelectEventFrameTitlePoint		69, 28
#define CLOutputConfig_EventDisableButtonRectangle		69, 45, 178, 70
#define CLOutputConfig_EventBypassOpenButtonRectangle	189, 45, 298, 70
#define CLOutputConfig_EventUnitRunButtonRectangle		69, 79, 178, 104
#define CLOutputConfig_EventUnitFaultButtonRectangle	189, 79, 298, 104
#define CLOutputConfig_EventSumWinButtonRectangle		69, 113, 178, 138
#define CLOutputConfig_EventMaxSpeedButtonRectangle		189, 113, 298, 138
#define CLOutputConfig_EventValveButtonRectangle		69, 147, 178, 172

#define CLOutputConfig_SelectActionFrameRectangle		59, 33, 308, 82
#define CLOutputConfig_SelectActionFrameTitlePoint		69, 28
#define CLOutputConfig_Action1ButtonRectangle			69, 42, 178, 73
#define CLOutputConfig_Action2ButtonRectangle			189, 42, 298, 73

#define	CLOutputConfig_PreviousButtonRectangle			161, 190, 204, 229
#define	CLOutputConfig_NextButtonRectangle				215, 190, 258, 229

CLFormResult CLOutputConfigForm_Open( unsigned short options )
{
	CLOutputConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLOutputConfigForm [class]
// -----------------------------------------------------------------------------
CLOutputConfigForm::CLOutputConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_Output1ButtonRectangle.Set( CLOutputConfig_Output1ButtonRectangle );
	m_Output2ButtonRectangle.Set( CLOutputConfig_Output2ButtonRectangle );

	m_EventDisableButtonRectangle.Set( CLOutputConfig_EventDisableButtonRectangle );
	m_EventBypassOpenButtonRectangle.Set( CLOutputConfig_EventBypassOpenButtonRectangle );
	m_EventUnitRunButtonRectangle.Set( CLOutputConfig_EventUnitRunButtonRectangle );
	m_EventUnitFaultButtonRectangle.Set( CLOutputConfig_EventUnitFaultButtonRectangle );
	m_EventValveButtonRectangle.Set( CLOutputConfig_EventValveButtonRectangle );
	m_EventSumWinButtonRectangle.Set( CLOutputConfig_EventSumWinButtonRectangle );
	m_EventMaxSpeedButtonRectangle.Set( CLOutputConfig_EventMaxSpeedButtonRectangle );

	m_Action1ButtonRectangle.Set( CLOutputConfig_Action1ButtonRectangle );
	m_Action2ButtonRectangle.Set( CLOutputConfig_Action2ButtonRectangle );

	m_PreviousButtonRectangle.Set( CLOutputConfig_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( CLOutputConfig_NextButtonRectangle );

	m_ActionSelectedButtonStyle.Set( GenericButtonStyle_Selected_SmallFont );
	m_ActionSelectedButtonStyle.Options	|= CLGraphicStyleOptions_Text_MultiLine;

	m_ActionNormalButtonStyle.Set( GenericButtonStyle_Normal_SmallFont );
	m_ActionNormalButtonStyle.Options	|= CLGraphicStyleOptions_Text_MultiLine;
}

CLFormResult CLOutputConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SelectOutput( 0 );
	SetOutput( 0, gRDEeprom.Set_Output[ 0 ] );
	SetOutput( 1, gRDEeprom.Set_Output[ 1 ] );
	SetState( CLState_Running );

	// Visualizza il form
	m_Page.SetPageCount( 2 );
	m_Page.Go( 0 );
	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Next Button
			if (m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage();
			}
			else
			// Previous Button
			if (m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				if (m_Page.GoPrevious())
					RenderPage();
			}
			else
			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
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

				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
			}
			else
			// Select Output1 Button
			if (m_Output1ButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_Output1ButtonRectangle );
				SelectOutput( 0 );
			}
			else
			// Select Output2 Button
			if (m_Output2ButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_Output2ButtonRectangle );
				SelectOutput( 1 );
			}
			else
			{
				switch (m_Page.GetValue())
				{
					case 0:
						// EventDisable Button
						if (m_EventDisableButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventDisableButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_Disable );
						}
						else
						// EventBypassOpen Button
						if (m_EventBypassOpenButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventBypassOpenButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_BypassOpen );
						}
						else
						// EventUnitFault Button
						if (m_EventUnitFaultButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventUnitFaultButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_UnitIsFault );
						}
						else
						// EventUnitRun Button
						if (m_EventUnitRunButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventUnitRunButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_UnitIsRun );
						}
						else
						// EventSumWin Button
						if (m_EventSumWinButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventSumWinButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_SumWin);
						}
						else
						// EventMaxSpeed Button
						if (m_EventMaxSpeedButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventMaxSpeedButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_MaxSpeed);
						}
						else
						// EventValve Button
						if (Accessory_IsPresent( ACC_EEP_AWP ) &&
							m_EventValveButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_EventValveButtonRectangle );
							SetOutput( m_SelectedOutputIndex, (m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) | CLOutputType_Valve );
						}
						else
							WaitForTouchRelease();
						break;

					case 1:
						// Action1 Button
						if (m_Action1ButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_Action1ButtonRectangle );
							SetOutput( m_SelectedOutputIndex, m_SetOutputs[ m_SelectedOutputIndex ] & ~0x80 );
						}
						else
						// Action2 Button
						if (m_Action2ButtonRectangle.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_Action2ButtonRectangle );
							SetOutput( m_SelectedOutputIndex, m_SetOutputs[ m_SelectedOutputIndex ] | 0x80 );
						}
						else
							WaitForTouchRelease();
						break;
					
					default:
						WaitForTouchRelease();
						break;
				}
			}
		}
    }

	return formResult;
}

bool CLOutputConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveSet_Output[ 2 ];

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente la configurazione del bypass
	saveSet_Output[ 0 ]	= gRDEeprom.Set_Output[ 0 ];
	saveSet_Output[ 1 ]	= gRDEeprom.Set_Output[ 1 ];

	//Imposta il nuovo stato del bypass
	gRDEeprom.Set_Output[ 0 ]	= m_SetOutputs[ 0 ];
	gRDEeprom.Set_Output[ 1 ]	= m_SetOutputs[ 1 ];

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_Output ),
		sizeof(gRDEeprom.Set_Output),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Set_Output[ 0 ]	= saveSet_Output[ 0 ];
		gRDEeprom.Set_Output[ 1 ]	= saveSet_Output[ 1 ];

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLOutputConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_OUTPUT_CONFIG ),
		&m_Page );

	// Draw SelectOutput Frame
	CLGraphics::DrawBox( CLRectangle( CLOutputConfig_SelectOutputFrameRectangle ),
		GenericForm_Group_Style );

	// Tasto Previous
	CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Next
	CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	switch (m_Page.GetValue())
	{
		case 0:
			// Draw SelectEvent Frame
			CLGraphics::DrawBox( CLRectangle( CLOutputConfig_SelectEventFrameRectangle ),
				GenericForm_Group_Style );

			CLGraphics::DrawText( CLOutputConfig_SelectEventFrameTitlePoint, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_SELECT_EVENT ) );
			break;

		case 1:
			// Draw SelectAction Frame
			CLGraphics::DrawBox( CLRectangle( CLOutputConfig_SelectActionFrameRectangle ),
				GenericForm_Group_Style );

			CLGraphics::DrawText( CLOutputConfig_SelectActionFrameTitlePoint, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_SELECT_ACTION ) );
			break;
	}

	RenderOutputButtons();
	RenderOutputConfigButtons();
}

void CLOutputConfigForm::RenderOutputButtons()
{
	CLLCDCommon::DrawGenericButton( m_Output1ButtonRectangle,
		(m_SelectedOutputIndex == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		"1" );
	CLLCDCommon::DrawGenericButton( m_Output2ButtonRectangle,
		(m_SelectedOutputIndex == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		"2" );
}

void CLOutputConfigForm::RenderOutputConfigButtons()
{
	int		configValue	= m_SetOutputs[ m_SelectedOutputIndex ] & ~0x80;
	char	text[ 30 ];

	switch (m_Page.GetValue())
	{
		case 0:
			CLLCDCommon::DrawGenericButton( m_EventDisableButtonRectangle,
				(configValue == 0 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
				CLLocalitation::GetText( CLTextId_DISABLE ) );
			CLLCDCommon::DrawGenericButton( m_EventBypassOpenButtonRectangle,
				(configValue == 1 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
				CLLocalitation::GetText( CLTextId_BYPASS_OPEN ) );
			CLLCDCommon::DrawGenericButton( m_EventUnitFaultButtonRectangle,
				(configValue == 2 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
				CLLocalitation::GetText( CLTextId_UNIT_FAULT ) );
			CLLCDCommon::DrawGenericButton( m_EventUnitRunButtonRectangle,
				(configValue == 3 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
				CLLocalitation::GetText( CLTextId_UNIT_RUN ) );
				

			if (Accessory_IsPresent( ACC_EEP_AWP ))
			{
				CLLCDCommon::DrawGenericButton( m_EventValveButtonRectangle,
					(configValue == 4 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
					"VALVE" );
			}
			
			CLLCDCommon::DrawGenericButton( m_EventSumWinButtonRectangle,
					(configValue == 5 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
					"SUM/WIN" );
			CLLCDCommon::DrawGenericButton( m_EventMaxSpeedButtonRectangle,
					(configValue == 6 ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
					"MAX SPEED" );
			
			break;

		case 1:
			sprintf( text, (m_SelectedOutputIndex == 0 ? "X1 (11-10)\r%s" : "X1 (9-8)\r%s"),
				CLLocalitation::GetText( CLTextId_CLOSED ) );
			CLLCDCommon::DrawGenericButton( m_Action1ButtonRectangle,
				(!(m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) ? m_ActionSelectedButtonStyle : m_ActionNormalButtonStyle),
				text );

			sprintf( text, (m_SelectedOutputIndex == 0 ? "X1 (11-10)\r%s" : "X1 (9-8)\r%s"),
				CLLocalitation::GetText( CLTextId_OPEN ) );
			CLLCDCommon::DrawGenericButton( m_Action2ButtonRectangle,
				((m_SetOutputs[ m_SelectedOutputIndex ] & 0x80) ? m_ActionSelectedButtonStyle : m_ActionNormalButtonStyle),
				text );
			break;
	}

}

void CLOutputConfigForm::SetOutput( byte index, byte value )
{
	m_SetOutputs[ index ]	= value;

	if (GetState() == CLState_Running)
		RenderOutputConfigButtons();
}

void CLOutputConfigForm::SelectOutput( byte index )
{
	m_SelectedOutputIndex	= index;

	if (GetState() == CLState_Running)
	{
		RenderOutputButtons();
		RenderOutputConfigButtons();
	}
}
// -----------------------------------------------------------------------------
// CLOutputConfigForm [class]
// =============================================================================



