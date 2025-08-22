 /*************************************************************************************
 *  file:			CLSelectionSpeedMotorModeForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionSpeedMotorModeForm_h
#define __CLSelectionSpeedMotorModeForm_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLVentilationControl.h"

CLFormResult CLSelectionVentilationControlForm_Open( unsigned short options );

// =============================================================================
// CLSelectionVentilationControlForm [class]
// =============================================================================
// Description: Form per la configurazione delle porte di input
// -----------------------------------------------------------------------------
class _PACK CLSelectionVentilationControlForm
	: public CLForm
{
	public: CLSelectionVentilationControlForm();

	private: unsigned short m_Options;

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_CAFModeButtonRectangle;
	private: CLRectangle m_CAPModeButtonRectangle;
	private: CLRectangle m_FSCModeButtonRectangle;
	private: CLRectangle m_CAPCalibrationButtonRectangle;

	private: CLVentilationControl m_VentilationControl;
	public: void SetVentilationControl( CLVentilationControl value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save();
	private: bool Save_Old();


	private: void RenderPage();
	private: void RenderSelectionButtons();

};
// -----------------------------------------------------------------------------
// CLSelectionVentilationControlForm [class]
// =============================================================================

#endif

