#include "CLAlarmsReportForm.h"
#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLLocalitation.h"
#include "protocol_wireless.h"

CLFormResult CLAlarmsReportForm_Open( unsigned short options )
{
	CLAlarmsReportForm	form;

	return form.Open( options );
}

#define CLAlarmsReportForm_RFMAlert_Rectangle	14, 104, 300, 115

// =============================================================================
// CLAlarmsReportForm [class]
// -----------------------------------------------------------------------------
CLAlarmsReportForm::CLAlarmsReportForm()
	: m_HomeButtonRectangle( ::Form_HomeButtonRectangle )
{
}

CLFormResult CLAlarmsReportForm::Open( unsigned short options )
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
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLAlarmsReportForm::RenderPage()
{
	const int	MaxRow		= 11;
	const int	ColumnWidth	= 63;
	const int	LineHeight	= 14;
	const int	ColumnStart	= 14;
	int			activeEventsCounter	= 0;
	int			textX, textY;
	int			rowsCounter	= 0;
	bool		exitDisplay	= false;

	// Clear screen
	gLCD.clrScr();

	// Draw Data Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_ERRORS_REPORT ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	textX	= ColumnStart;
	textY	= 32;
	for (int eventsCounter = 0; eventsCounter < EVENT_COUNT && !exitDisplay; eventsCounter++)
	{
		byte	eventValue	= gKTSData.Events[ eventsCounter ];

		for (int eventBitsCounter = 0; eventBitsCounter < 8 && !exitDisplay; eventBitsCounter++)
		{
			if (eventValue & 0x01)
			{
				char	text[ 8 ];

				if (rowsCounter == MaxRow)
				{
					CLGraphics::DrawText( ColumnStart + (ColumnWidth * 4), textY, CLGraphicStyleOptions_Font_Small,
						RGBColor_Black, RGBColor_White,
						"****" );
					exitDisplay	= true;
					continue;
				}

				sprintf( text, "%02d-%1d", eventsCounter, eventBitsCounter + 1 );
				CLGraphics::DrawText( textX, textY, CLGraphicStyleOptions_Font_Small,
					RGBColor_Black, RGBColor_White,
					text );

				activeEventsCounter++;

				if ((activeEventsCounter % 5) == 0)
				{
					textY	+= LineHeight;
					textX	= ColumnStart;
					rowsCounter++;
				}
				else
					textX	+= ColumnWidth;
			}
			eventValue	>>= 1;
		}
	}

	if (gKTSGlobal.ComLinkType == BY_WIRELESS &&
		gKTSGlobal.RFMCheckChannel == CLRFMCheckChannel_Busy)
	{
		CLGraphics::DrawText( CLRectangle( CLAlarmsReportForm_RFMAlert_Rectangle ), CLGraphicStyleOptions_Font_Small,
			RGBColor_Red, RGBColor_White,
			CLLocalitation::GetText( CLTextId_RFM__ALERT_CHANNEL_BUSY ) );
	}
}
// -----------------------------------------------------------------------------
// CLAlarmsReportForm [class]
// =============================================================================


