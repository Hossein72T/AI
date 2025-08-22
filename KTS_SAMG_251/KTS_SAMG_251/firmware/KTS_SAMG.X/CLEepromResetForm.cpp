#include "CLEepromResetForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"

CLFormResult CLEepromResetForm_Open( unsigned short options )
{
	CLEepromResetForm	form;

	return form.Open( options );
}

// =============================================================================
// CLEepromResetForm [class]
// -----------------------------------------------------------------------------
CLEepromResetForm::CLEepromResetForm()
{
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
}

CLFormResult CLEepromResetForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
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

				gKTSEeprom.Reset();

				CLLCDCommon::RenderPanelInfo( "PLEASE RESTART KTS...",
					0x778899, RGBColor_White, RGBColor_Black );
				while (true);
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLEepromResetForm::RenderPage()
{

	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( "RESET EEEPROM",
		NULL );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	CLGraphics::DrawText( GenericForm_Data_Rectangle, CLGraphicStyleOptions_BorderRound_No | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
		RGBColor_Black, RGBColor_White,
		"ARE YOU SURE TO RESET EEPROM DATA?" );
}
// -----------------------------------------------------------------------------
// CLSelectionTimeForm [class]
// =============================================================================

