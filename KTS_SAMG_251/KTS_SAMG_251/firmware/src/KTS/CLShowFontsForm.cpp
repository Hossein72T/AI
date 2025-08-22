#include "CLShowFontsForm.h"
#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"

#if KTS_SHOWFONTSFORM == 1

CLFormResult CLShowFontsForm_Open()
{
	CLShowFontsForm	form;

	return form.Open();
}

// =============================================================================
// CLShowFontsForm [class]
// -----------------------------------------------------------------------------
CLShowFontsForm::CLShowFontsForm()
	: m_HomeButtonRectangle( ::Form_HomeButtonRectangle )
{
	m_SelectedFont	= &CLSmallFont;
	m_TextRectangle	= CLRectangle( 0, 0, 319, 250 );
}

CLFormResult CLShowFontsForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;

	RenderPage();

	while (true)
	{
		// Processa le funzionalitÃ  del KTS
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
			{
				WaitForTouchRelease();

				if (m_SelectedFont == &CLSmallFont)
					m_SelectedFont	= &CLBigFont;
				else
					m_SelectedFont	= &CLSmallFont;
				RenderPage();
			}
		}
    }

	return formResult;
}

void CLShowFontsForm::RenderPage()
{
	const int	MaxRow		= 11;
	const int	ColumnWidth	= 63;
	const int	LineHeight	= 14;
	const int	ColumnStart	= 14;
	int			activeEventsCounter	= 0;
	int			textX, textY;
	int			rowsCounter	= 0;
	bool		exitDisplay	= false;

	char		text[ 256 ];

	int	index	= 0;
	for (int counter = 0;  counter < 256;  counter++)
	{
		if (gLCD.hasChar( (char) counter ))
			text[ index++ ]	= (char) counter;
	}
	text[ index ]	= NULL;

	// Clear screen
	gLCD.clrScr();

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	gLCD.setFont( m_SelectedFont, CLKTS::GetCodePage() );
	CLGraphics::DrawText( m_TextRectangle,
		CLGraphicStyleOptions_Default | CLGraphicStyleOptions_TextAlignBy_Char | CLGraphicStyleOptions_Text_MultiLine,
		RGBColor_Black,
		RGBColor_White,
		text );
}
// -----------------------------------------------------------------------------
// CLShowFontsForm [class]
// =============================================================================

#endif

