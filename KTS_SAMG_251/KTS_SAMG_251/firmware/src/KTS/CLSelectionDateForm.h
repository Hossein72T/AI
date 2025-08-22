 /*************************************************************************************
 *  file:			CLSelectionDateForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionDateForm_h
#define __CLSelectionDateForm_h

#include "CLForm.h"
#include "CLDateTime.h"

CLFormResult CLSelectionDateForm_Open( unsigned short options,
	const char* mainTitle, CLDateTime& date, CLDateTime* minDate, CLDateTime* maxDate );

// =============================================================================
// CLSelectionDateForm [class]
// =============================================================================
// Description: Form per la selezione della data
// -----------------------------------------------------------------------------
class _PACK CLSelectionDateForm
	: public CLForm
{
	public: CLSelectionDateForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_DayUpButtonRectangle;
	private: CLRectangle m_DayDownButtonRectangle;
	private: CLRectangle m_MonthUpButtonRectangle;
	private: CLRectangle m_MonthDownButtonRectangle;
	private: CLRectangle m_YearUpButtonRectangle;
	private: CLRectangle m_YearDownButtonRectangle;

	private: CLProgressiveTouchUpDown m_ProgressiveTouchUpDown;

	private: CLDateTime m_MinValue;
	private: CLDateTime m_MaxValue;
	private: CLDateTime m_Value;
	public: void SetValue( CLDateTime value );

	public: void SetDay( short value );
	public: void SetMonth( short value );
	public: void SetYear( short value );

	public: CLFormResult Open( unsigned short options, const char* mainTitle,
		CLDateTime& date, CLDateTime* minDate, CLDateTime* maxDate );

	private: void RenderPage( unsigned short options, const char* mainTitle );
	private: void RenderDate();
};
// -----------------------------------------------------------------------------
// CLSelectionDateForm [class]
// =============================================================================

#endif

