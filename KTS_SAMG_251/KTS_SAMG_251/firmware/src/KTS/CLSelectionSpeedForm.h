 /*************************************************************************************
 *  file:			CLSelectionSpeedForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionSpeedForm_h
#define __CLSelectionSpeedForm_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLVentilationControl.h"

CLFormResult CLSelectionSpeedForm_Open( unsigned short options,
	const char* mainTitle, const char* subTitle,
	CLVentilationControl ventilationControl,
	unsigned short minValue, unsigned short maxValue, unsigned short incValue,
	unsigned short& value );

// =============================================================================
// CLSelectionSpeedForm [class]
// =============================================================================
// Description: Form per la selezione della velocita'
// -----------------------------------------------------------------------------
class _PACK CLSelectionSpeedForm
	: public CLForm
{
	public: CLSelectionSpeedForm();

	// Buttons
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_ProgressBarRectangle;
	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_Speed_ProgressiveTouchUpDown;

	private: const char* m_MainTitle;
	private: const char* m_SubTitle;

	private: unsigned short m_MinValue;
	private: unsigned short m_MaxValue;
	private: unsigned short m_IncValue;
	private: CLVentilationControl m_VentilationControl;

	private: unsigned short m_Value;
	public: void SetValue( unsigned short value );

	public: CLFormResult Open( unsigned short options,
		const char* mainTitle, const char* subTitle,
		CLVentilationControl ventilationControl,
		unsigned short minValue, unsigned short maxValue, unsigned short incValue,
		unsigned short& value );

	private: void RenderPage();
	private: void RenderProgressBar();
};
// -----------------------------------------------------------------------------
// CLSelectionSpeedForm [class]
// =============================================================================

#endif

