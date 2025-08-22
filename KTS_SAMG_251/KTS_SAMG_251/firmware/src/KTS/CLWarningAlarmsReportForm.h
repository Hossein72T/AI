 /*************************************************************************************
 *  file:			CLWarningAlarmsReportForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLWarningAlarmsReportForm_h
#define __CLWarningAlarmsReportForm_h

#include "CLForm.h"

CLFormResult CLWarningAlarmsReportForm_Open( unsigned short options );

// =============================================================================
// CLWarningAlarmsReportForm [class]
// =============================================================================
// Description: Form per la visualizzazione degli allarmi di avvertimento
// -----------------------------------------------------------------------------
class _PACK CLWarningAlarmsReportForm
	: public CLForm
{
	public: CLWarningAlarmsReportForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_ResetButtonRectangle;

	private: bool m_FilterInAlarm;

	public: CLFormResult Open( unsigned short options );
	private: void RenderPage();

	private: bool Save( unsigned short options );
};
// -----------------------------------------------------------------------------
// CLWarningAlarmsReportForm [class]
// =============================================================================

#endif

