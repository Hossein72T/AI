 /*************************************************************************************
 *  file:			CLKTSStartupForm.h
 *
 *  Author/Date:	Paolo Menchi maggio 2015
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLKTSStartupForm_h
#define __CLKTSStartupForm_h

#include "CLForm.h"

CLFormResult CLKTSStartupForm_Open();

// =============================================================================
// CLKTSStartupForm [class]
// =============================================================================
// Description: Form di inizializzazione KTS (grande finta)
// -----------------------------------------------------------------------------
class _PACK CLKTSStartupForm
	: public CLForm
{
	public: CLKTSStartupForm();

	public: CLFormResult Open();

	private: int m_WaitCounter;
	private: void RenderPage();
	private: void RenderDynamicObject();
};
// -----------------------------------------------------------------------------
// CLKTSStartupForm [class]
// =============================================================================

#endif

