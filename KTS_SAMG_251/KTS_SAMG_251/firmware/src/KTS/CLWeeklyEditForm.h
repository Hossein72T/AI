 /*************************************************************************************
 *  file:			CLWeeklyEditForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLWeeklyEditForm_h
#define __CLWeeklyEditForm_h

#include "CLForm.h"
#include "CLKTS.h"

CLFormResult CLWeeklyEditForm_Open( unsigned short options );

// =============================================================================
// CLWeeklyEditForm [class]
// =============================================================================
// Description: Form per la modifica del weekly program
// -----------------------------------------------------------------------------
class _PACK CLWeeklyEditForm
	: public CLForm
{
	public: CLWeeklyEditForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_CopyButtonRectangle;
	private: CLRectangle m_PasteButtonRectangle;
	private: CLRectangle m_DaysButtonRectangles[ 7 ];
	private: CLRectangle m_EditButtonRectangle;

	private: SDAYPROG m_Days[ sizeof(gRDEeprom.sDayProg) / sizeof(SDAYPROG) ];
	private: void SetDays( SDAYPROG* days );

	// Day Selected
	private: byte m_SelectedDays;
	private: byte m_SelectedDayCount;
	private: void ClearSelectedDays();
	private: void SelectDay( byte index, bool value );
	private: bool IsSelectedDay( byte index );

	// Copy / Paste
	private: bool m_CopyMode;
	private: byte m_CopyModeDay;
	private: void SetCopyMode( bool value, byte day );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderDaysButtons();
	private: void RenderEditButtons();

	private: bool Close( unsigned short options );
	private: bool IsDataChanged();
};
// -----------------------------------------------------------------------------
// CLWeeklyEditForm [class]
// =============================================================================

#endif

