 /*************************************************************************************
 *  file:			CLServiceMenu.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLServiceMenu_h
#define __CLServiceMenu_h

#include "CLMenu.h"
#include "CLForm.h"
#include "CLKTS.h"
#include "CLProcedure.h"

CLFormResult CLServiceMenu_Open();

const int CLServiceMenu_ItemCount = 24;

// =============================================================================
// CLServiceMenu [class]
// =============================================================================
// Description: Form per la visualizzazione del menu Manutenzione
// -----------------------------------------------------------------------------
class _PACK CLServiceMenu
	: public CLMenu
{
	public: CLServiceMenu();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;

	private: CLRectangle m_ItemButtonRectangles[ 4 ];
	private: byte m_DisplayedItems[ 4 ];

	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;

	private: void RenderPage();

	private: CLItem m_Items[ CLServiceMenu_ItemCount ];
	private: void RebuildItems();
	private: void RenderItems();

	private: bool m_AdminMode;

	public: CLFormResult Open( bool adminMode );
	private: CLFormResult ExecuteProcedure( CLProcedureId procedureId );
};
// -----------------------------------------------------------------------------
// CLServiceMenu [class]
// =============================================================================

#endif

