 /*************************************************************************************
 *  file:			CLSettingsMenu.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/
#ifndef __CLSettingsMenu_h
#define __CLSettingsMenu_h

#include "CLMenu.h"
#include "CLForm.h"
#include "CLKTS.h"
#include "CLProcedure.h"

CLFormResult CLSettingsMenu_Open();

const int CLSettingsMenu_ItemCount  = 8;

// =============================================================================
// CLSettingsMenu [class]
// =============================================================================
// Description: Form per la visualizzazione del menu delle impostazioni
// -----------------------------------------------------------------------------
class _PACK CLSettingsMenu
	: public CLMenu
{
	public: CLSettingsMenu();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;

	private: CLRectangle m_ItemButtonRectangles[ 4 ];

	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;

	private: byte m_DisplayedItems[ 4 ];

	private: void RenderPage();

	private: CLItem m_Items[ CLSettingsMenu_ItemCount ];

	private: void RebuildItems();
	private: void RenderItems();

	public: CLFormResult Open();
	private: CLFormResult ExecuteProcedure( CLProcedureId procedureId );
};

#endif

