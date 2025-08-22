 /*************************************************************************************
 *  file:			CLFireAlarmForm.h
 *
 *  Author/Date:	Paolo Menchi 2016
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLFireAlarmForm_h
#define __CLFireAlarmForm_h

#include "CLForm.h"

CLFormResult CLFireAlarmForm_Open( unsigned short options );

// =============================================================================
// CLFireAlarmForm [class]
// =============================================================================
// Description: Form per allarme fuoco
// -----------------------------------------------------------------------------
class _PACK CLFireAlarmForm
	: public CLForm
{
	public: CLFireAlarmForm();

	// Buttons
	private: CLRectangle m_RearmButtonRectangle;

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderDynamicObjects();
};
// -----------------------------------------------------------------------------
// CLFireAlarmForm [class]
// =============================================================================

#endif

