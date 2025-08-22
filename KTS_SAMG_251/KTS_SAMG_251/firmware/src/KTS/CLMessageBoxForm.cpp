#include "CLAccessoryManagerForm.h"

#include "CLMessageBoxForm.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"
#include "CLLocalitation.h"

#define CLMessageBoxForm_Ok_OkButtonRectangle				119, 190, 198, 229

#define CLMessageBoxForm_YesNo_YesButtonRectangle			59, 190, 138, 229
#define CLMessageBoxForm_YesNo_NoButtonRectangle			179, 190, 258, 229

#define CLMessageBoxForm_YesNoCancel_YesButtonRectangle		12, 190, 91, 229
#define CLMessageBoxForm_YesNoCancel_NoButtonRectangle		105, 190, 184, 229
#define CLMessageBoxForm_YesNoCancel_CancelButtonRectangle	198, 190, 308, 229

// =============================================================================
// CLMessageBoxForm [class]
// -----------------------------------------------------------------------------
void CLMessageBoxForm::Open_Render( CLMessageBoxButtons buttons, CLMessageBoxGravity gravity,
	const char* title, const char* message,
	CLRectangle& buttonRectangle1, CLRectangle& buttonRectangle2, CLRectangle& buttonRectangle3 )
{
	RenderPanel( gravity, title, message );

	switch (buttons)
	{
		case CLMessageBoxButtons_Ok:
			buttonRectangle1.Set( CLMessageBoxForm_Ok_OkButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle1,
				GenericButtonStyle_Normal_BigFont,
				CLFixedText_OK );
			break;

		case CLMessageBoxButtons_YesNo:
			buttonRectangle1.Set( CLMessageBoxForm_YesNo_YesButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle1,
				GenericButtonStyle_Normal_BigFont,
				CLLocalitation::GetText( CLTextId_YES ) );

			buttonRectangle2.Set( CLMessageBoxForm_YesNo_NoButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle2,
				GenericButtonStyle_Normal_BigFont,
				CLLocalitation::GetText( CLTextId_NO ) );
			break;

		case CLMessageBoxButtons_YesNoCancel:
			buttonRectangle1.Set( CLMessageBoxForm_YesNoCancel_YesButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle1,
				GenericButtonStyle_Normal_BigFont,
				CLLocalitation::GetText( CLTextId_YES ) );

			buttonRectangle2.Set( CLMessageBoxForm_YesNoCancel_NoButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle2,
				GenericButtonStyle_Normal_BigFont,
				CLLocalitation::GetText( CLTextId_NO ) );

			buttonRectangle3.Set( CLMessageBoxForm_YesNoCancel_CancelButtonRectangle );
			CLGraphics::DrawBoxWithText( buttonRectangle3,
				GenericButtonStyle_Normal_BigFont,
				CLLocalitation::GetText( CLTextId_CANCEL ) );
			break;
	}
}

CLMessageBoxResult CLMessageBoxForm::Open( CLMessageBoxButtons buttons, CLMessageBoxGravity gravity,
	const char* title, const char* message )
{
	int					touchX, touchY;
	CLRectangle			buttonRectangle1;
	CLRectangle 		buttonRectangle2;
	CLRectangle 		buttonRectangle3;
	CLMessageBoxResult	result;
	bool				exitForm	= false;

	Open_Render( buttons, gravity,
		title, message,
		buttonRectangle1, buttonRectangle2, buttonRectangle3 );

	while (!exitForm)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
		{
			Open_Render( buttons, gravity,
				title, message,
				buttonRectangle1, buttonRectangle2, buttonRectangle3 );
		}
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			switch (buttons)
			{
				case CLMessageBoxButtons_Ok:
					if (buttonRectangle1.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle1 );
						result		= CLMessageBoxResult_Ok;
						exitForm	= true;
					}
					break;

				case CLMessageBoxButtons_YesNo:
					if (buttonRectangle1.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle1 );
						result		= CLMessageBoxResult_Yes;
						exitForm	= true;
					}
					else
					if (buttonRectangle2.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle2 );
						result		= CLMessageBoxResult_No;
						exitForm	= true;
					}
					break;

				case CLMessageBoxButtons_YesNoCancel:
					if (buttonRectangle1.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle1 );
						result		= CLMessageBoxResult_Yes;
						exitForm	= true;
					}
					else
					if (buttonRectangle2.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle2 );
						result		= CLMessageBoxResult_No;
						exitForm	= true;
					}
					else
					if (buttonRectangle3.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( buttonRectangle3 );
						result		= CLMessageBoxResult_Cancel;
						exitForm	= true;
					}
					break;
			}
		}
		else
			WaitForTouchRelease();
    }

	return result;
}

void CLMessageBoxForm::RenderPanel( CLMessageBoxGravity gravity,
		const char* title, const char* message )
{
	gLCD.clrScr();

	// Draw Frame/Message
	CLGraphics::DrawBoxWithText( GenericForm_Data_Rectangle, CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_Text_MultiLine,
		GenericForm_Data_Style.BackgroundColor, GenericForm_Data_Style.ForegroundColor,
		GenericForm_Data_Style.BorderWidth, GenericForm_Data_Style.BorderColor,
		message );

	// Draw Title
	switch (gravity)
	{
		case CLMessageBoxGravity_Question:
		case CLMessageBoxGravity_Info:
			CLGraphics::DrawBoxWithText( GenericForm_Title_Rectangle,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				0, RGBColor_Empty,
				title );
			break;

		case CLMessageBoxGravity_Error:
			CLGraphics::DrawBoxWithText( GenericForm_Title_Rectangle,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big,
				RGBColor_Red, RGBColor_White,
				0, RGBColor_Empty,
				title );
			break;

		case CLMessageBoxGravity_Warning:
			CLGraphics::DrawBoxWithText( GenericForm_Title_Rectangle,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big,
				0xE8D64D, RGBColor_Black,
				0, RGBColor_Empty,
				title );
			break;
	}
}
// -----------------------------------------------------------------------------
// CLMessageBoxForm [class]
// =============================================================================

