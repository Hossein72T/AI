 /*************************************************************************************
 *  file:			CLVOCConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLVOCConfigForm_h
#define __CLVOCConfigForm_h

#include "CLForm.h"

CLFormResult CLVOCConfigForm_Open( unsigned short options );

// =============================================================================
// CLVOCConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle soglie VOC
// -----------------------------------------------------------------------------
class _PACK CLVOCConfigForm
	: public CLForm
{
	public: CLVOCConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_VOC_ProgressiveTouchUpDown;

	private: unsigned short m_Value;
	public: void SetValue( unsigned short value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderProgressBar();
};
// -----------------------------------------------------------------------------
// CLVOCConfigForm [class]
// =============================================================================

#endif

