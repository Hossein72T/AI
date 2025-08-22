#include "CLKTSStartupForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLFunction.h"
#include "CLWeeklyMainForm.h"
#include "CLWeekly.h"
#include "CLLogo.h"

CLFormResult CLKTSStartupForm_Open()
{
	CLKTSStartupForm	form;

	return form.Open();
}

// =============================================================================
// CLKTSStartupForm [class]
// -----------------------------------------------------------------------------
CLKTSStartupForm::CLKTSStartupForm()
{
}

CLFormResult CLKTSStartupForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult				= CLFormResult_Ok;
	long			previousWaitMilleseconds;

	SetState( CLForm::CLState_Initializing );
	m_WaitCounter				= 0;
	previousWaitMilleseconds	= millis();
	SetState( CLForm::CLState_Running );

	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		CLKTS::Process();
		CLKTS::Pir_Process();

		if (millis() - previousWaitMilleseconds >= 400 ||
			millis() < previousWaitMilleseconds)
		{
			m_WaitCounter++;
			previousWaitMilleseconds	= millis();
			RenderDynamicObject();
		}

		if (m_WaitCounter == 14)
			break;
    }

	return formResult;
}

void CLKTSStartupForm::RenderPage()
{
	char	text[ 100 ];

	CLGraphics::DrawBoxWithDrawer( CLRectangle( 0, 0, 319, 199 ),
		CLGraphicStyleOptions_BorderRound_No | CLGraphicStyleOptions_HVAlign_Center,
		RGBColor_White, RGBColor_White,
		&LogoImage );

	RenderDynamicObject();
}

void CLKTSStartupForm::RenderDynamicObject()
{
	char	text[ 100 ];

	if (!gKTSEeprom.GetFirstTime())
	{
		strcpy( text, "FW VERSION: " );
		strcat( text, FirmwareVersion );
	}
	else
	{
		strcpy( text, "SYSTEM INITIALIZING" );
	}
	strcat( text, "\n\r" );
	for (int waitCounter = 0; waitCounter < m_WaitCounter % 4; waitCounter++)
		strcat( text, "<" );

	strcat( text, " PLEASE WAIT " );
	for (int waitCounter = 0; waitCounter < m_WaitCounter % 4; waitCounter++)
		strcat( text, ">" );

	// Draw Frame 'Message'
	CLGraphics::DrawBoxWithText( CLRectangle( 0, 200, 319, 239 ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_Text_MultiLine,
		RGBColor_Black, RGBColor_White,
		text );
}

// -----------------------------------------------------------------------------
// CLKTSConnectForm [class]
// =============================================================================

