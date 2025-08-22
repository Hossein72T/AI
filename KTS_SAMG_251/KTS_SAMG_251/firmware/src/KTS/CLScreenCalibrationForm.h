 /*************************************************************************************
 *  file:			CLScreenCalibrationForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLScreenCalibrationForm_h
#define __CLScreenCalibrationForm_h

#include "CLForm.h"

CLFormResult CLScreenCalibrationForm_Open( unsigned short options );

// =============================================================================
// CLScreenCalibrationForm [class]
// =============================================================================
// Description: Form per la calibrazione dello schermo
// -----------------------------------------------------------------------------
class _PACK CLScreenCalibrationForm
	: public CLForm
{
	public: CLScreenCalibrationForm();

	// Buttons
	private: CLRectangle m_BarRectangle;

	private: int m_YOffset;
	private: int m_YMax;
	private: int m_XOffset;
	private: int m_XMax;

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderBar( CLRectangle& barRectangle, bool clear );
};
// -----------------------------------------------------------------------------
// CLScreenCalibrationForm [class]
// =============================================================================

#endif

