 /*************************************************************************************
 *  file:			CLWeeklyViewForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLWeeklyViewForm_h
#define __CLWeeklyViewForm_h

#include "CLForm.h"
#include "CLKTS.h"

CLFormResult CLWeeklyViewForm_Open( unsigned short options );

// =============================================================================
// CLWeeklyViewForm [class]
// =============================================================================
// Description: Form per la visualizzazione della programmazione Weekly
// -----------------------------------------------------------------------------
class _PACK CLWeeklyViewForm
	: public CLForm
{
	public: CLWeeklyViewForm();

	private: unsigned short m_Options;

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;

	private: byte m_Day;
	private: void SetDay( byte value );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLWeeklyViewForm [class]
// =============================================================================

#endif

