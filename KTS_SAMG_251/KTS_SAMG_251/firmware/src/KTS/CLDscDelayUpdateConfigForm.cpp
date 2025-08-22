#include "CLDscDelayUpdateConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"

#define	CLDscDelayUpdateConfigForm_UpButtonRectangle		230, 49, 289, 88
#define	CLDscDelayUpdateConfigForm_DownButtonRectangle		230, 110, 289, 149
#define	CLDscDelayUpdateConfigForm_MinutesFrameRectangle	93, 35, 304, 164
#define	CLDscDelayUpdateConfigForm_TextMinutesPoint		99, 90

CLFormResult CLDscDelayUpdateConfigForm_Open( unsigned short options )
{
	CLDscDelayUpdateConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLDscDelayUpdateConfigForm [class]
// -----------------------------------------------------------------------------
CLDscDelayUpdateConfigForm::CLDscDelayUpdateConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_UpButtonRectangle.Set( CLDscDelayUpdateConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLDscDelayUpdateConfigForm_DownButtonRectangle );
}

CLFormResult CLDscDelayUpdateConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetMinutes( gRDEeprom.Dsc_Sdcard_Update_Delay );
	SetState( CLState_Running );

	// Visualizza il form
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
			// Up Button
			if (m_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetMinutes( (int) m_Minutes + 1 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					delay( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Off Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetMinutes( (int) m_Minutes - 1 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					delay( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLDscDelayUpdateConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte	saveDsc_Sdcard_Update_Delay;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveDsc_Sdcard_Update_Delay	= gRDEeprom.Dsc_Sdcard_Update_Delay;

	// Imposta i nuovi dati
	gRDEeprom.Dsc_Sdcard_Update_Delay	= m_Minutes;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Dsc_Sdcard_Update_Delay ),
		sizeof(gRDEeprom.Dsc_Sdcard_Update_Delay),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Dsc_Sdcard_Update_Delay	= saveDsc_Sdcard_Update_Delay;

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

void CLDscDelayUpdateConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_DSC_DELAY_UPDATE ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Draw minutes Frame
	CLGraphics::DrawBox( CLRectangle( CLDscDelayUpdateConfigForm_MinutesFrameRectangle ),
		GenericForm_Group_Style );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );
	
	// Up Button
	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	
	// Down Button
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown ,
		&DownMonoImage );
		
	RenderMinutes();
}


void CLDscDelayUpdateConfigForm::RenderMinutes()
{
	char	text[ 10 ];

	sprintf( text, "%d min", m_Minutes );
	CLGraphics::DrawText( CLDscDelayUpdateConfigForm_TextMinutesPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 7 );
}

void CLDscDelayUpdateConfigForm::SetMinutes( short value )
{
	if (value > DSC_UPDATE_DELAY_MAX)
		value	= DSC_UPDATE_DELAY_MAX;
	else
	if (value < DSC_UPDATE_DELAY_MIN)
		value	= DSC_UPDATE_DELAY_MIN;

	m_Minutes	= value;

	if (GetState() == CLState_Running)
		RenderMinutes();
}
// -----------------------------------------------------------------------------
// CLDscDelayUpdateConfigForm [class]
// =============================================================================

