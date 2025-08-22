#include "CLVOCConfigForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLVOCConfigForm_UpButtonRectangle			255, 40, 295, 80
#define	CLVOCConfigForm_DownButtonRectangle			255, 116, 295, 156
#define	CLVOCConfigForm_ProgressBarFrameRectangle	17, 40, 231, 156
#define	CLVOCConfigForm_ProgressBarRectangle		30, 71, 219, 110
#define	CLVOCConfigForm_TextProgressPoint			30, 119

CLFormResult CLVOCConfigForm_Open( unsigned short options )
{
	CLVOCConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLVOCConfigForm [class]
// -----------------------------------------------------------------------------
CLVOCConfigForm::CLVOCConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_UpButtonRectangle.Set( CLVOCConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLVOCConfigForm_DownButtonRectangle );

	m_VOC_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 3, 1 );
}

CLFormResult CLVOCConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( gRDEeprom.SetPoint_VOC );
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

				m_VOC_ProgressiveTouchUpDown.Reset();
				while (m_VOC_ProgressiveTouchUpDown.InWhile())
				{
					if (m_VOC_ProgressiveTouchUpDown.CanIncrement())
						SetValue( m_Value + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Down Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				m_VOC_ProgressiveTouchUpDown.Reset();
				while (m_VOC_ProgressiveTouchUpDown.InWhile())
				{
					if (m_VOC_ProgressiveTouchUpDown.CanIncrement())
						SetValue( m_Value - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLVOCConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	unsigned short	saveSetPoint_VOC;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveSetPoint_VOC	= gRDEeprom.SetPoint_VOC;

	// Imposta i nuovi dati
	gRDEeprom.SetPoint_VOC	= m_Value;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, SetPoint_VOC ),
		sizeof(gRDEeprom.SetPoint_VOC),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.SetPoint_VOC	= saveSetPoint_VOC;

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

void CLVOCConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_VOC_CONFIG ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	CLGraphics::DrawBox( CLRectangle( CLVOCConfigForm_ProgressBarFrameRectangle ),
		GenericForm_Group_Style );

	// Up Button
	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	
	// Down Button
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	RenderProgressBar();
}

void CLVOCConfigForm::RenderProgressBar()
{
	char	text[ 15 ];

	CLGraphics::DrawProgressBar( CLRectangle( CLVOCConfigForm_ProgressBarRectangle ),
		CLDrawBarOptions_Direction_Horizontal| CLDrawBarOptions_BarShape_Progressive,
		VOC_ProgressBar_Color_Background, VOC_ProgressBar_Color_BarFalse, VOC_ProgressBar_Color_BarTrue,
		0, CLKTS::VOC_GetMax(), m_Value,
		6, 3 );

	sprintf( text, "%d %s", m_Value, CLFixedText_PPM );
	
	CLGraphics::DrawText( CLVOCConfigForm_TextProgressPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 12 );
}

void CLVOCConfigForm::SetValue( unsigned short value )
{
	if (value < CLKTS::VOC_GetMin())
		value	= CLKTS::VOC_GetMax();
	else
	if (value > CLKTS::VOC_GetMax())
		value	= CLKTS::VOC_GetMin();

	m_Value	= value;

	if (GetState() == CLState_Running)
		RenderProgressBar();
}
// -----------------------------------------------------------------------------
// CLVOCConfigForm [class]
// =============================================================================


