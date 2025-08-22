#include "CLSelectionSpeedForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLSelectionSpeedForm_UpButtonRectangle			255, 51, 295, 91
#define	CLSelectionSpeedForm_DownButtonRectangle		255, 127, 295, 167
#define	CLSelectionSpeedForm_ProgressBarFrameRectangle	17, 51, 231, 167
#define	CLSelectionSpeedForm_ProgressBarRectangle		30, 89, 219, 128
#define	CLSelectionSpeedForm_ProgressBarTextPoint		30, 136

CLFormResult CLSelectionSpeedForm_Open( unsigned short options,
	const char* mainTitle, const char* subTitle,
	CLVentilationControl ventilationControl,
	unsigned short minValue, unsigned short maxValue, unsigned short incValue,
	unsigned short& value )
{
	CLSelectionSpeedForm	form;

	return form.Open( options,
		mainTitle, subTitle,
		ventilationControl,
		minValue, maxValue, incValue,
		value );
}

// =============================================================================
// CLSelectionSpeedForm [class]
// -----------------------------------------------------------------------------
CLSelectionSpeedForm::CLSelectionSpeedForm()
{
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_SaveButtonRectangle );

	m_UpButtonRectangle.Set( CLSelectionSpeedForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLSelectionSpeedForm_DownButtonRectangle );
	m_ProgressBarRectangle.Set( CLSelectionSpeedForm_ProgressBarRectangle );

	m_Speed_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 20, 1 );
}

CLFormResult CLSelectionSpeedForm::Open( unsigned short options,
	const char* mainTitle,
	const char* subTitle,
	CLVentilationControl ventilationControl,
	unsigned short minValue, unsigned short maxValue, unsigned short incValue,
	unsigned short& value )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_MainTitle				= (char*) mainTitle;
	m_SubTitle				= (char*) subTitle;
	m_MinValue				= minValue;
	m_MaxValue				= maxValue;
	m_IncValue				= incValue;
	m_VentilationControl	= ventilationControl;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( value );
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
				value		= m_Value;
				formResult	= CLFormResult_Ok;
				break;
			}
			else
			// Up Button
			if (m_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				m_Speed_ProgressiveTouchUpDown.Reset();
				while (m_Speed_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Speed_ProgressiveTouchUpDown.CanIncrement())
						SetValue( m_Value + m_IncValue );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Down Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				m_Speed_ProgressiveTouchUpDown.Reset();
				while (m_Speed_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Speed_ProgressiveTouchUpDown.CanIncrement())
						SetValue( m_Value - m_IncValue );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLSelectionSpeedForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Main Title
	RenderFormTitle( m_MainTitle,
		NULL );

	// Display Sub Title
	if (m_SubTitle != NULL)
	{
		CLGraphics::DrawBoxWithText( CLRectangle( 1, 24, 318, 43 ),
			GenericForm_Title_SmallFont_Style,
			m_SubTitle );
	}

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	RenderProgressBar();
}

void CLSelectionSpeedForm::RenderProgressBar()
{
	char	text[ 20 ];

	switch (m_VentilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			CLGraphics::DrawProgressBar( m_ProgressBarRectangle,
				CLDrawBarOptions_Direction_Horizontal| CLDrawBarOptions_BarShape_Progressive,
				CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, CAF_FSC_ProgressBar_Color_BarTrue,
				0, 100, m_Value,
				6, 3 );

			if (m_VentilationControl == CLVentilationControl_CAF)
				sprintf( text, "%d %s",
					CLCommon::PercentageToM3H( (float) m_Value / 100.0f ),
					CLFixedText_M3_H );
			else
				sprintf( text, "%d %%", m_Value );
			break;

		case CLVentilationControl_CAP:
			CLGraphics::DrawProgressBar( m_ProgressBarRectangle,
				CLDrawBarOptions_Direction_Horizontal| CLDrawBarOptions_BarShape_Progressive,
				CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, CAP_ProgressBar_Color_BarTrue,
				0, m_MaxValue, m_Value,
				6, 3 );

			sprintf( text, "%d Pa", m_Value );
			break;
	}

	CLGraphics::DrawText( CLSelectionSpeedForm_ProgressBarTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 10 );
}

void CLSelectionSpeedForm::SetValue( unsigned short value )
{
	if (value < m_MinValue)
		value	= m_MinValue;
	else
	if (value > m_MaxValue)
		value	= m_MaxValue;

	m_Value	= value;

	if (GetState() == CLState_Running)
		RenderProgressBar();
}
// -----------------------------------------------------------------------------
// CLSelectionSpeedForm [class]
// =============================================================================

