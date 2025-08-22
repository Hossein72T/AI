#include "CLKTSConnectForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLFunction.h"
#include "CLWeeklyMainForm.h"
#include "CLWeekly.h"
#include "CLLogo.h"
#include "CLCommunication_Driver.h"
#include "CLRFMSelectChannelForm.h"

#define	CLKTSConnectForm_TitleLine1_Point				13, 10
#define	CLKTSConnectForm_TitleLine1_Length				18
#define	CLKTSConnectForm_TitleLine2_Point				13, 34
#define	CLKTSConnectForm_TitleLine2_Length				18

#define	CLKTSConnectForm_MessageFrame_Rectangle			12, 58, 306, 171

#define	CLKTSConnectForm_RFMSettingsButton_Rectangle	8, 190, 178, 229
#define	CLKTSConnectForm_OKButton_Rectangle				193, 190, 314, 229

CLFormResult CLKTSConnectForm_Open()
{
	CLKTSConnectForm	form;

	return form.Open();
}

void CLKTSConnect_Callback( CLKTSConnectState currentState,
	int step, int stepCount )
{
	char	text[ 40 ];

	switch (currentState)
	{
		case CLKTSConnectState_Init:
			gLCD.clrScr();

			logo( 0, 0, ALIGNED_LOGO_CENTER ); // stampa logo

			CLGraphics::DrawBox( CLRectangle( 0, 200, 319, 239 ), CLGraphicStyleOptions_Default,
				RGBColor_Black, 0, RGBColor_White );

			break;
		
		case CLKTSConnectState_TrySerialLink:
			sprintf( text, "%s COM",
				CLLocalitation::GetText( CLTextId_CONNECTING ) );
			CLGraphics::DrawText( 1, 203, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, 19 );
			break;

		case CLKTSConnectState_TryRFMLink:
			sprintf( text, "%s RFM #%d", CLLocalitation::GetText( CLTextId_CONNECTING ),
				sdata_wi.channel );
			CLGraphics::DrawText( 1, 203, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, 19 );
			break;

		default:
			sprintf( text, "%s %s %d",
				CLLocalitation::GetText( CLTextId_UNIT ),
				CLLocalitation::GetText( CLTextId_SEARCHING ),
				step );
			CLGraphics::DrawText( 1, 203, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, 19 );

			CLGraphics::DrawProgressBar( CLRectangle( 1, 221, 318, 236 ),
				CLDrawBarOptions_Direction_Horizontal,
				RGBColor_Black, 0x606060, RGBColor_White,
				0, stepCount, step,
				7, 3 );
			break;

	}
}

// =============================================================================
// CLKTSConnectForm [class]
// -----------------------------------------------------------------------------
CLKTSConnectForm::CLKTSConnectForm()
{
	m_RFMSettingsButtonRectangle.Set( CLKTSConnectForm_RFMSettingsButton_Rectangle );
	m_OkButtonRectangle.Set( CLKTSConnectForm_OKButton_Rectangle );
}

CLFormResult CLKTSConnectForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;
	int				connectOptions	= CLKTSConnectOption_Default;

	SetState( CLForm::CLState_Initializing );
	m_Mode	= CLMode_TryConnect;
	SetState( CLForm::CLState_Running );

	//analogWrite( pBACKLIGHT, (HIGH_BRIGHTESS - 10) );
    TC0_CH1_CompareASet (HIGH_BRIGHTESS + 600);

	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		CLKTS::Process();
		CLKTS::Pir_Process();
		
		if (m_Mode == CLMode_TryConnect)
		{
			if (CLKTS::Connect( CLKTSConnect_Callback, connectOptions ) == CLKTSConnectState_Connected)
			{
				formResult	= CLFormResult_Ok;
				break;
			}
			m_Mode	= CLMode_Error;
			RenderPage();
		}
		else
		if (m_Mode == CLMode_Error)
		{
			if (Touched())
			{
				touchX	= ReadX();
				touchY	= ReadY();

				// 'RFM Settings' Button
				if (sdata_wi.install_rfm && m_RFMSettingsButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_RFMSettingsButtonRectangle );

					if (CLRFMSelectChannelForm_Open( CLFormOption_HideButton_Home, CLRFMSelectChannelForm::CLExtOption_HighlightCurrentChannel ) == CLFormResult_Ok)
					{
						m_Mode			= CLMode_TryConnect;
						connectOptions	= CLKTSConnectOption_Default | CLKTSConnectOption_SkipSerialLink;
					}
					else
						RenderPage();
				}
				else
				// 'OK' Button
				if (m_OkButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_OkButtonRectangle );

					m_Mode			= CLMode_TryConnect;
					connectOptions	= CLKTSConnectOption_Default;
				}
				else
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

void CLKTSConnectForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	switch (m_Mode)
	{
		case CLMode_Error:
			// Draw main Frame
			CLGraphics::DrawBox( GenericForm_Data_Rectangle,
				GenericForm_Data_Style );
	
			// Draw 'Title'
			CLGraphics::DrawText( CLKTSConnectForm_TitleLine1_Point, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_ERROR ), CLKTSConnectForm_TitleLine1_Length );
			CLGraphics::DrawText( CLKTSConnectForm_TitleLine2_Point, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_UNIT_NOT_FOUND ), CLKTSConnectForm_TitleLine2_Length );

			// Draw Frame 'Message'
			CLGraphics::DrawBoxWithText( CLRectangle( CLKTSConnectForm_MessageFrame_Rectangle ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_Text_MultiLine,
				GenericForm_Group_Style.BackgroundColor, GenericForm_Group_Style.ForegroundColor,
				GenericForm_Group_Style.BorderWidth, GenericForm_Group_Style.BorderColor,
				CLLocalitation::GetText( CLTextId_CONNECT__RETRY_CONNECTION_MESSAGE ) );

			// 'SET RFM Channel' Button
			if (sdata_wi.install_rfm)
			{
				CLLCDCommon::DrawGenericButton( m_RFMSettingsButtonRectangle,
					GenericButtonStyle_Normal_SmallFont,
					CLLocalitation::GetText( CLTextId_RFM__CHANGE_CHANNEL ) );
			}

			// 'OK' Button
			CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
				GenericButtonStyle_Normal_SmallFont );

			break;
	}
}
// -----------------------------------------------------------------------------
// CLKTSConnectForm [class]
// =============================================================================

