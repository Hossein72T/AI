 /*************************************************************************************
 *  file:			CLAccessoryManagerForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLAccessoryManagerForm_h
#define __CLAccessoryManagerForm_h

#include "CLForm.h"
#include "CLAccessory.h"
#include "RDEeprom.h"

CLFormResult CLAccessoryManagerForm_Open( unsigned short options );

const int AccessoryPerPage	= 9;

// =============================================================================
// CLAccessoryManagerForm [class]
// =============================================================================
// Description: Form per la gestione degli accessori
// -----------------------------------------------------------------------------
class _PACK CLAccessoryManagerForm
	: public CLForm
{
	// =============================================================================
	// CLAccessory [struct]
	// =============================================================================
	// Description: Dati accessorio
	// -----------------------------------------------------------------------------
	struct _PACK CLAccessory
	{
		byte	RDIndex;
		byte	Present : 1;
	};
	// -----------------------------------------------------------------------------
	// CLAccessory [struct]
	// =============================================================================

	public: CLAccessoryManagerForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;
        private: CLRectangle m_Disconect_All_ButtonRectangle;
	
        // Page
	private: CLPage m_Page;

	private: int m_DisplayedAccessoryCount;
	private: int m_DisplayedAccessoryStartIndex;
	private: CLRectangle m_DisplayedAccessoryButtonRectangles[ AccessoryPerPage ];

	private: int m_AccessoryCount;
	private: CLAccessory m_Accessories[ AccessoryCount ];
	private: CLAccessory* GetAccessory( _NUMBER_ACCESSORY_EEP accessoryIndex );
	
	public: CLFormResult Open( unsigned short options );
	private: void RefreshData( bool render );
	private: void RemoveAccessory( unsigned short options, short accessoryIndexToRemove );

	private: void RenderPage();
};

#endif

