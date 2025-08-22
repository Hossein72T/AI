#include "CLScreenSaverConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"

#define	CLScreenSaverConfigForm_OnOffButtonRectangle	15, 35, 84, 94
#define	CLScreenSaverConfigForm_UpButtonRectangle		230, 49, 289, 88
#define	CLScreenSaverConfigForm_DownButtonRectangle		230, 110, 289, 149
#define	CLScreenSaverConfigForm_MinutesFrameRectangle	93, 35, 304, 164
#define	CLScreenSaverConfigForm_TextMinutesPoint		99, 90

CLFormResult CLScreenSaverConfigForm_Open( unsigned short options )
{
	CLScreenSaverConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLScreenSaverConfigForm [class]
// -----------------------------------------------------------------------------
CLScreenSaverConfigForm::CLScreenSaverConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLScreenSaverConfigForm_OnOffButtonRectangle );

	m_UpButtonRectangle.Set( CLScreenSaverConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLScreenSaverConfigForm_DownButtonRectangle );
}

CLFormResult CLScreenSaverConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetEnabled( gKTSEeprom.GetScreensaverEnabled() );
	SetMinutes( gKTSEeprom.GetScreensaverMinutes() );
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
			// OnOff Button
			if (m_OnOffButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OnOffButtonRectangle );
				SetEnabled( !m_Enabled );
			}
			else
			// Up Button
			if (m_UpButtonRectangle.Contains( touchX, touchY ) && m_Enabled)
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetMinutes( (int) m_Minutes + 1 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Off Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ) && m_Enabled)
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetMinutes( (int) m_Minutes - 1 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLScreenSaverConfigForm::Save( unsigned short options )
{
	gKTSEeprom.SetScreensaver( m_Enabled, m_Minutes );

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLScreenSaverConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_CONFIG_SCREEN_SAVER ),
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
	CLGraphics::DrawBox( CLRectangle( CLScreenSaverConfigForm_MinutesFrameRectangle ),
		GenericForm_Group_Style );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderOnOffButtons();
	RenderMinutes();
}

void CLScreenSaverConfigForm::RenderOnOffButtons()
{
	// On/Off Button
	CLLCDCommon::DrawGenericButton( m_OnOffButtonRectangle,
		(m_Enabled ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(m_Enabled ? CLFixedText_ON : CLFixedText_OFF) );

	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		(m_Enabled ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		(m_Enabled ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&DownMonoImage );
}

void CLScreenSaverConfigForm::RenderMinutes()
{
	char	text[ 10 ];

	sprintf( text, "%d min", m_Minutes );
	CLGraphics::DrawText( CLScreenSaverConfigForm_TextMinutesPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 7 );
}

void CLScreenSaverConfigForm::SetEnabled( bool value )
{
	m_Enabled	= value;

	if (GetState() == CLState_Running)
		RenderOnOffButtons();
}

void CLScreenSaverConfigForm::SetMinutes( short value )
{
	if (value > SCREENSAVER_MINUTES_MAX)
		value	= SCREENSAVER_MINUTES_MAX;
	else
	if (value < SCREENSAVER_MINUTES_MIN)
		value	= SCREENSAVER_MINUTES_MIN;

	m_Minutes	= value;

	if (GetState() == CLState_Running)
		RenderMinutes();
}
// -----------------------------------------------------------------------------
// CLScreenSaverConfigForm [class]
// =============================================================================

