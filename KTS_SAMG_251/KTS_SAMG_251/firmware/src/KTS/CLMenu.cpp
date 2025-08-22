#include "CLMenu.h"

#include "CLLCDCommon.h"
#include "CLGraphics.h"
#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLTouch.h"

// =============================================================================
// CLMenu [class]
// -----------------------------------------------------------------------------
CLMenu::CLMenu()
{
}

void CLMenu::SetMenuItems( CLItem items[], byte itemCount,
	byte* displayedItems, byte itemsPerPage )
{
	m_Items				= items;
	m_ItemCount			= itemCount;
	m_DisplayedItems	= displayedItems;
	m_ItemsPerPage		= itemsPerPage;

	// Clear Item
	for (int itemsCounter = 0; itemsCounter < itemCount; itemsCounter++)
	{
		m_Items[ itemsCounter ].ProcedureId	= CLProcedureId_None;
		m_Items[ itemsCounter ].Visible		= false;
	}
	//RebuildItems();
}

void CLMenu::RebuildItems()
{
	short	visibleItemCount		= 0;
	short	pagesCounter			= -1;
	short	currentPageIndex		= m_Page.GetValue();
	short	displayedItemsCounter	= 0;

	for (int menuItemsCounter = 0; menuItemsCounter < m_ItemCount; menuItemsCounter++)
	{
		m_Items[ menuItemsCounter ].Enabled	= Procedure_IsEnabled( m_Items[ menuItemsCounter ].ProcedureId );
		if (!m_Items[ menuItemsCounter ].Visible)
			continue;

		visibleItemCount++;

		if ((visibleItemCount % m_ItemsPerPage) == 1)
			pagesCounter++;
	}

	m_Page.SetPageCount( (visibleItemCount / m_ItemsPerPage) + ((visibleItemCount % m_ItemsPerPage) > 0 ? 1 : 0) );

	if (currentPageIndex >= m_Page.GetPageCount())
		currentPageIndex	= m_Page.GetPageCount() - 1;
	else
	if (currentPageIndex < 0)
		currentPageIndex	= 0;

	m_Page.Go( currentPageIndex );

	for (displayedItemsCounter = 0; displayedItemsCounter < m_ItemsPerPage; displayedItemsCounter++)
		m_DisplayedItems[ displayedItemsCounter ]	= 0xFF;

	visibleItemCount		= 0;
	displayedItemsCounter	= 0;
	pagesCounter			= -1;
	for (int menuItemsCounter = 0; menuItemsCounter < m_ItemCount; menuItemsCounter++)
	{
		if (!m_Items[ menuItemsCounter ].Visible)
			continue;

		visibleItemCount++;

		if ((visibleItemCount % m_ItemsPerPage) == 1)
		{
			pagesCounter++;
			if (pagesCounter > currentPageIndex)
				break;
		}

		if (pagesCounter == currentPageIndex)
			m_DisplayedItems[ displayedItemsCounter++ ]	= menuItemsCounter;
	}
}

byte CLMenu::GetPageCount()
{
	return m_Page.GetPageCount();
}

byte CLMenu::GoPage( byte pageIndex )
{
	m_Page.Go( pageIndex );
	return m_Page.GetValue();
}

byte CLMenu::GetPageIndex()
{
	return m_Page.GetValue();
}

byte CLMenu::GoNextPage()
{
	m_Page.GoNext();
	return m_Page.GetValue();
}

byte CLMenu::GoPreviousPage()
{
	m_Page.GoPrevious();
	return m_Page.GetValue();
}

void CLMenu::SetMenuItem( int index, CLProcedureId procedureId, bool visible )
{
	m_Items[ index ].ProcedureId	= procedureId;
	m_Items[ index ].Enabled		= Procedure_IsEnabled( procedureId );
	m_Items[ index ].Visible		= visible;
}

void CLMenu::RenderItems( CLRectangle* displayedItemRectangles )
{
	// Display Items
	for (int menuItemsCounter = 0; menuItemsCounter < 4; menuItemsCounter++)
	{
		if (m_DisplayedItems[ menuItemsCounter ] == 0xFF)
			break;

		CLLCDCommon::DrawMenuItem( m_Items[ m_DisplayedItems[ menuItemsCounter ] ].ProcedureId,
			displayedItemRectangles[ menuItemsCounter ],
			(m_Items[ m_DisplayedItems[ menuItemsCounter ] ].Enabled ? GenericButtonStyle_Normal_SmallFont_Multiline : GenericButtonStyle_Disabled_SmallFont_Multiline) );
	}
}
// -----------------------------------------------------------------------------
// CLMenu [class]
// =============================================================================

