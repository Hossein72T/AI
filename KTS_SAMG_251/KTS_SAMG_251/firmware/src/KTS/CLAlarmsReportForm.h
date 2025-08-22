 /*************************************************************************************
 *  file:			CLAlarmsReportForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLAlarmsReportForm_h
#define __CLAlarmsReportForm_h

#include "CLForm.h"

CLFormResult CLAlarmsReportForm_Open( unsigned short options );

// =============================================================================
// CLAlarmsReportForm [class]
// =============================================================================
// Description: Form per la visualizzazione degli allarmi
// -----------------------------------------------------------------------------
class _PACK CLAlarmsReportForm
	: public CLForm
{
	public: CLAlarmsReportForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;

	public: CLFormResult Open( unsigned short options );
	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLAlarmsReportForm [class]
// =============================================================================

#endif

