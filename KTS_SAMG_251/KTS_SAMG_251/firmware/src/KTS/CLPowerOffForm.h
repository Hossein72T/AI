 /*************************************************************************************
 *  file:			CLPowerOffForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLPowerOffForm_h
#define __CLPowerOffForm_h

#include "CLForm.h"

CLFormResult CLPowerOffForm_Open();

// =============================================================================
// CLPowerOffForm [class]
// =============================================================================
// Description: Form del KTS quando è spento
// -----------------------------------------------------------------------------
class _PACK CLPowerOffForm
	: public CLForm
{
	public: CLPowerOffForm();

	// Buttons
	private: CLRectangle m_PowerOnButtonRectangle;
	//private: CLRectangle m_WeeklyProgrammerButtonRectangle;

	public: CLFormResult Open();

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLPowerOffForm [class]
// =============================================================================

#endif

