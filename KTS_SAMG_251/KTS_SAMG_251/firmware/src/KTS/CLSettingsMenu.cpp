#include "CLSettingsMenu.h"

#include "CLLCDCommon.h"
#include "CLGraphics.h"
#include "CLKTS.h"
#include "CLPasswordForm.h"
#include "RDEeprom.h"
#include "CLLocalitation.h"
#include "CLTouch.h"

CLFormResult CLSettingsMenu_Open()
{
	CLSettingsMenu	form;

	return form.Open();
}

// =============================================================================
// CLSettingsMenu [class]
// -----------------------------------------------------------------------------
CLSettingsMenu::CLSettingsMenu()
	: m_HomeButtonRectangle( Form_HomeButtonRectangle )
{
	m_ItemButtonRectangles[ 0 ].Set( 70, 32, 250, 69 );
	m_ItemButtonRectangles[ 1 ].Set( 70, 83, 250, 120 );
	m_ItemButtonRectangles[ 2 ].Set( 70, 135, 250, 172 );
	m_ItemButtonRectangles[ 3 ].Set( 70, 186, 250, 223 );

	m_PreviousButtonRectangle.Set( 13, 83, 52, 136 );
	m_NextButtonRectangle.Set( 267, 83, 306, 136 );
}

CLFormResult CLSettingsMenu::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Impostiamo gli items del menu'
	SetMenuItems( m_Items, CLSettingsMenu_ItemCount, m_DisplayedItems, 4 );
	SetMenuItem(  0, CLProcedureId_SelectionLanguageForm );
	SetMenuItem(  1, CLProcedureId_ScreenSaverConfigForm );
	SetMenuItem(  2, CLProcedureId_SystemDateTimeConfigForm );
	SetMenuItem(  3, CLProcedureId_WeeklyMainForm );
	SetMenuItem(  4, CLProcedureId_ClimaSettingsForm );
	SetMenuItem(  5, CLProcedureId_PartyConfigForm );
	SetMenuItem(  6, CLProcedureId_EndUserPasswordConfigForm );
	SetMenuItem(  7, CLProcedureId_RFMChangeChannelForm );
	RebuildItems();

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
			if (GetPageCount() > 1 && m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );
				GoNextPage();
				RebuildItems();
				RenderPage();
			}
			else
			// Previous Button
			if (GetPageCount() > 1 && m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );
				GoPreviousPage();
				RebuildItems();
				RenderPage();
			}
			else
			// Check Menu Items Button
			{
				CLProcedureId	selectedProcedureId	= CLProcedureId_None;

				for (short menuItemsCounter = 0; menuItemsCounter < 4; menuItemsCounter++)
				{
					if (m_DisplayedItems[ menuItemsCounter ] == 0xFF)
						break;

					if (m_Items[ m_DisplayedItems[ menuItemsCounter ] ].Enabled &&
						m_ItemButtonRectangles[ menuItemsCounter ].Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( m_ItemButtonRectangles[ menuItemsCounter ] );

						selectedProcedureId	= m_Items[ m_DisplayedItems[ menuItemsCounter ] ].ProcedureId;
						break;
					}
				}

				if (selectedProcedureId != CLProcedureId_None)
				{
					formResult	= ExecuteProcedure( selectedProcedureId );
					if (formResult == CLFormResult_Home)
						break;
					RebuildItems();
					RenderPage();
				}
				else
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

CLFormResult CLSettingsMenu::ExecuteProcedure( CLProcedureId procedureId )
{
	switch (procedureId)
	{
		case CLProcedureId_SystemDateTimeConfigForm:
		case CLProcedureId_SelectionLanguageForm:
		case CLProcedureId_ScreenSaverConfigForm:
			return Procedure_Execute( procedureId, CLFormOption_GoHomeAfterWrite );
	}

	return Procedure_Execute( procedureId, CLFormOption_ShowWriteMesssages_All | CLFormOption_GoBackAfterWrite );
}

void CLSettingsMenu::RenderPage()
{
	char	text[ 30 ];

	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 239 ),
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	// Display Title
	strcpy( text, CLLocalitation::GetText( CLTextId_SETTINGS ) );
	CLForm::RenderFormTitle( text,
		(GetPageCount() > 1 ? &m_Page : NULL) );

	if (GetPageCount() > 1)
	{
		CLLCDCommon::DrawArrowButton( m_PreviousButtonRectangle.GetX1(), m_PreviousButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Left );

		CLLCDCommon::DrawArrowButton( m_NextButtonRectangle.GetX1(), m_NextButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Right );
	}

	RenderItems();
}

void CLSettingsMenu::RebuildItems()
{
	CLMenu::RebuildItems();
}

void CLSettingsMenu::RenderItems()
{
	CLMenu::RenderItems( m_ItemButtonRectangles );
}
// -----------------------------------------------------------------------------
// CLSettingsMenu [class]
// =============================================================================

