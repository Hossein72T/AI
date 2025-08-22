#include "CLScreenCalibrationForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"

#define	CLScreenCalibrationForm_HomeButtonRectangle			132, 96, 182, 146
#define	CLScreenCalibrationForm_TopBarRectangle				0, 0, 319, 10
#define	CLScreenCalibrationForm_LeftBarRectangle			0, 0, 10, 239
#define	CLScreenCalibrationForm_BottomBarRectangle			0, 229, 319, 239
#define	CLScreenCalibrationForm_RightBarRectangle			309, 0, 319, 239
#define	CLScreenCalibrationForm_TextRectangle				26, 73, 291, 86

CLFormResult CLScreenCalibrationForm_Open( unsigned short options )
{
	CLScreenCalibrationForm	form;

	return form.Open( options );
}

// =============================================================================
// CLScreenCalibrationForm [class]
// -----------------------------------------------------------------------------
CLScreenCalibrationForm::CLScreenCalibrationForm()
{
}

CLFormResult CLScreenCalibrationForm::Open( unsigned short options )
{
	enum CLStep
	{
		CLStep_TopBar,
		CLStep_BottomBar,
		CLStep_LeftBar,
		CLStep_RightBar,
		CLStep_End
	};

	int				touchX, touchY;
	CLFormResult	formResult;
	CLStep			currentStep		= CLStep_TopBar;
	int				saveY_Offset	= Y_Offset;
	int				saveY_Max		= Y_Max;
	int				saveX_Offset	= X_Offset;
	int				saveX_Max		= X_Max;
	// >[PM]
	float			deltaX			= ((float) X_Max / (float) gLCD.getMaxX());
	float			deltaY			= ((float) Y_Max / (float) gLCD.getMaxY());
	// <[PM]

	RenderPage();

	// >[PM]
	Y_Offset	= 0;
	Y_Max		= (deltaY * (float) gLCD.getMaxY());
	X_Offset	= 0;
	X_Max		= (deltaX * (float) gLCD.getMaxX());
	//Y_Offset	= 0;					// default 347
	//Y_Max		= 4 * gLCD.getMaxY();	// default 735
	//X_Offset	= 0;					// default 271
	//X_Max		= 4 * gLCD.getMaxX();	// default 770
	// <[PM]

	CLGraphics::DrawBoxWithText( CLRectangle( CLScreenCalibrationForm_TextRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_MAKE_USE_OF_A_STYLUS_PEN ) );
	//delay( 2000 );
    SYSTICK_DelayMs ( 2000 );
	CLGraphics::DrawBoxWithText( CLRectangle( CLScreenCalibrationForm_TextRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_PRESS_THE_BLUE_BAR ) );

	// Impostiamo la prima barra a top
	m_BarRectangle.Set( CLScreenCalibrationForm_TopBarRectangle );
	RenderBar( m_BarRectangle, false );

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

			CLLCDCommon::WaitButton( m_BarRectangle );

			switch (currentStep)
			{
				case CLStep_TopBar:
					RenderBar( m_BarRectangle, true );
					m_YOffset	= touchY * 4;

					currentStep	= CLStep_BottomBar;
					m_BarRectangle.Set( CLScreenCalibrationForm_BottomBarRectangle );
					RenderBar( m_BarRectangle, false );
					break;

				case CLStep_BottomBar:
					RenderBar( m_BarRectangle, true );
					m_YMax	= touchY * 4;

					currentStep	= CLStep_LeftBar;
					m_BarRectangle.Set( CLScreenCalibrationForm_LeftBarRectangle );
					RenderBar( m_BarRectangle, false );
					break;

				case CLStep_LeftBar:
					RenderBar( m_BarRectangle, true );
					m_XOffset	= touchX * 4;

					currentStep	= CLStep_RightBar;
					m_BarRectangle.Set( CLScreenCalibrationForm_RightBarRectangle );
					RenderBar( m_BarRectangle, false );
					break;

				case CLStep_RightBar:
					RenderBar( m_BarRectangle, true );
					m_XMax	= touchX * 4;

					currentStep	= CLStep_End;
					break;
			}

			if (currentStep == CLStep_End)
			{
				formResult	= CLFormResult_Ok;
				break;
			}
		}
    }

	char	text[ 20 ];

	sprintf( text, "YOffset [%d]", m_YOffset );
	CLGraphics::DrawText( 0, 0, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );
	sprintf( text, "YMax [%d]", m_YMax );
	CLGraphics::DrawText( 0, 20, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );
	sprintf( text, "XOffset [%d]", m_XOffset );
	CLGraphics::DrawText( 0, 40, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );
	sprintf( text, "XMax [%d]", m_XMax );
	CLGraphics::DrawText( 0, 60, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );

	//delay( 10000 );
    SYSTICK_DelayMs ( 10000 );
	if (formResult == CLFormResult_Ok)
	{
		Y_Offset	= m_YOffset;
		Y_Max		= m_YMax;
		X_Offset	= m_XOffset;
		X_Max		= m_XMax;

		gLCD.clrScr();
		CLGraphics::DrawBoxWithText( CLRectangle( 0, 0, gLCD.getMaxX(), gLCD.getMaxY() ), CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Char | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
			RGBColor_Black, RGBColor_White,
			CLLocalitation::GetText( CLTextId_TOUCH_CALIBRATED ) );

		CLKTS::Delay( 2000 );
	}
	else
	{
		Y_Offset	= saveY_Offset;
		Y_Max		= saveY_Max;
		X_Offset	= saveX_Offset;
		X_Max		= saveX_Max;
	}

	return formResult;
}

void CLScreenCalibrationForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();
}

void CLScreenCalibrationForm::RenderBar( CLRectangle& barRectangle, bool clear )
{
	if (clear)
	{
		CLGraphics::DrawBox( barRectangle, CLGraphicStyleOptions_BorderRound_Yes,
			RGBColor_Black,
			1, RGBColor_Black );
	}
	else
	{
		CLGraphics::DrawBox( barRectangle, CLGraphicStyleOptions_BorderRound_Yes,
			0x404080,
			1, RGBColor_White );
	}
}
// -----------------------------------------------------------------------------
// CLScreenCalibrationForm [class]
// =============================================================================


