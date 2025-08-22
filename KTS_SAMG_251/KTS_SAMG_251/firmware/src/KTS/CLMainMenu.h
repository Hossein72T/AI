 /*************************************************************************************
 *  file:			CLMainMenu.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLMainMenu_h
#define __CLMainMenu_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLProcedure.h"

CLFormResult CLMainMenu_Open( CLProcedureId& procedureId );

const int CLMainMenu_ItemCount = 3;

// =============================================================================
// CLMainMenu [class]
// =============================================================================
// Description: Form per la visualizzazione del menu Principale
// -----------------------------------------------------------------------------
class _PACK CLMainMenu
{
	struct _PACK CLItem
	{
		CLProcedureId ProcedureId	: 7;
		byte Enabled				: 1;
	};

	public: CLMainMenu();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;

	private: CLRectangle m_ItemButtonRectangles[ 4 ];

	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;

	private: CLPage m_Page;
	private: void RenderPage();

	private: CLItem m_Items[ CLMainMenu_ItemCount ];
	private: void CheckItems();
	private: void BuildItems();
	private: void RenderItem( int itemIndex, int buttonRectangleIndex );

	public: CLFormResult Open( CLProcedureId& procedureId );
};
// -----------------------------------------------------------------------------
// CLMainMenu [class]
// =============================================================================

#endif

