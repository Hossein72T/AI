/*************************************************************************************
 *  file:			CLMenu.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLMenu_h
#define __CLMenu_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLProcedure.h"

// =============================================================================
// CLMenu [class]
// =============================================================================
// Description: Classe base per i menu
// -----------------------------------------------------------------------------
class _PACK CLMenu
{
	protected: struct _PACK CLItem
	{
		CLProcedureId	ProcedureId	: 8;
		byte			Enabled		: 1;
		byte			Visible		: 1;
	};

	protected: CLPage m_Page;

	public: CLMenu();

	private: CLItem* m_Items;
	private: byte m_ItemCount;
	private: byte m_ItemsPerPage;
	private: byte* m_DisplayedItems;

	protected: void SetMenuItems( CLItem items[], byte itemCount,
		byte* pageItems, byte itemsPerPage );

	protected: byte GetVisibleItemCount();
	public: byte GetPageCount();
	public: byte GoPage( byte pageIndex );
	public: byte GetPageIndex();
	public: byte GoNextPage();
	public: byte GoPreviousPage();

	protected: void SetMenuItem( int index, CLProcedureId procedureId, bool visible = true );
	protected: void RebuildItems();
	protected: void RenderItems( CLRectangle* displayedItemRectangles );
};
// -----------------------------------------------------------------------------
// CLMainMenu [class]
// =============================================================================

#endif

