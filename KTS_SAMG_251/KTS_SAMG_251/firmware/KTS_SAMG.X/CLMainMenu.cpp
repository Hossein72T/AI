#include "CLMainMenu.h"

#include "CLLCDCommon.h"
#include "CLGraphics.h"
#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLTouch.h"

CLFormResult CLMainMenu_Open( CLProcedureId& procedureId )
{
	CLMainMenu	menu;
	return menu.Open( procedureId );
}

// =============================================================================
// CLMainMenu [class]
// -----------------------------------------------------------------------------
CLMainMenu::CLMainMenu()
	: m_Page()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );

	m_ItemButtonRectangles[ 0 ].Set( 70, 32, 250, 69 );
	m_ItemButtonRectangles[ 1 ].Set( 70, 83, 250, 120 );
	m_ItemButtonRectangles[ 2 ].Set( 70, 135, 250, 172 );
	m_ItemButtonRectangles[ 3 ].Set( 70, 186, 250, 223 );

	m_PreviousButtonRectangle.Set( 13, 83, 52, 136 );
	m_NextButtonRectangle.Set( 267, 83, 306, 136 );
}

void CLMainMenu::BuildItems()
{
	m_Items[  0 ].ProcedureId	= CLProcedureId_SettingsMenu;
	m_Items[  1 ].ProcedureId	= CLProcedureId_ServiceMenu;
	m_Items[  2 ].ProcedureId	= CLProcedureId_InfoForm;

	CheckItems();
}

void CLMainMenu::CheckItems()
{
	for (int itemsCounter = 0; itemsCounter < CLMainMenu_ItemCount; itemsCounter++)
		m_Items[ itemsCounter ].Enabled	= Procedure_IsEnabled( m_Items[ itemsCounter ].ProcedureId );
}

CLFormResult CLMainMenu::Open( CLProcedureId& procedureId )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	BuildItems();

	m_Page.SetPageCount( (CLMainMenu_ItemCount / 4) + (CLMainMenu_ItemCount % 4 > 0 ? 1 : 0) );
	m_Page.Go( 0 );

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
			// Next Button
			if (m_Page.GetPageCount() > 1 && m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage();
			}
			else
			// Previous Button
			if (m_Page.GetPageCount() > 1 && m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				if (m_Page.GoPrevious())
					RenderPage();
			}
			else
			// Check Menu Items Button
			{
				int				itemIndex			= m_Page.GetValue() * 4;
				CLProcedureId	selectedProcedureId	= CLProcedureId_None;
				for (int itemButtonsCounter = 0; itemButtonsCounter < 4 && itemIndex < CLMainMenu_ItemCount; itemButtonsCounter++, itemIndex++)
				{
					if (m_Items[ itemIndex ].Enabled &&
						m_ItemButtonRectangles[ itemButtonsCounter ].Contains( touchX, touchY ))
					{
						unsigned long	time1	= millis();
						CLLCDCommon::WaitButton( m_ItemButtonRectangles[ itemButtonsCounter ] );

						selectedProcedureId	= (CLProcedureId) m_Items[ itemIndex ].ProcedureId;
						break;
					}
				}

				if (selectedProcedureId != CLProcedureId_None)
				{
					formResult	= CLFormResult_Ok;
					procedureId	= selectedProcedureId;
					break;
				}
				else
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

void CLMainMenu::RenderItem( int itemIndex, int buttonRectangleIndex )
{
	CLLCDCommon::DrawMenuItem( m_Items[ itemIndex ].ProcedureId,
		m_ItemButtonRectangles[ buttonRectangleIndex ],
		(m_Items[ itemIndex ].Enabled ? GenericButtonStyle_Normal_SmallFont_Multiline : GenericButtonStyle_Disabled_SmallFont_Multiline) );
}

void CLMainMenu::RenderPage()
{
	int	itemIndex;

	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 239 ),
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	itemIndex	= m_Page.GetValue() * 4;
	for (int itemButtonsCounter = 0; itemButtonsCounter < 4 && itemIndex < CLMainMenu_ItemCount; itemButtonsCounter++, itemIndex++)
		RenderItem( itemIndex, itemButtonsCounter );

	if (m_Page.GetPageCount() > 1)
	{
		CLLCDCommon::DrawArrowButton( m_PreviousButtonRectangle.GetX1(), m_PreviousButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Left );

		CLLCDCommon::DrawArrowButton( m_NextButtonRectangle.GetX1(), m_NextButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Right );
	}
}
// -----------------------------------------------------------------------------
// CLMainMenu [class]
// =============================================================================

