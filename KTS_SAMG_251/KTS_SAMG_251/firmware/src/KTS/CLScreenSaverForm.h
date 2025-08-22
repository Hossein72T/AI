 /*************************************************************************************
 *  file:			CLScreenSaverForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLScreenSaverForm_h
#define __CLScreenSaverForm_h

#include "CLForm.h"

CLFormResult CLScreenSaverForm_Open();

// =============================================================================
// CLScreenSaverForm [class]
// =============================================================================
// Description: Form dello screensaver
// -----------------------------------------------------------------------------
class _PACK CLScreenSaverForm
	: public CLForm
{
	public: CLScreenSaverForm();

	public: CLFormResult Open();

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLScreenSaverForm [class]
// =============================================================================

#endif

