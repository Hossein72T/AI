 /*************************************************************************************
 *  file:			CLRHConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLRHConfigForm_h
#define __CLRHConfigForm_h

#include "CLForm.h"

CLFormResult CLRHConfigForm_Open( unsigned short options );

// =============================================================================
// CLRHConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle soglie CO2
// -----------------------------------------------------------------------------
class _PACK CLRHConfigForm
	: public CLForm
{
	public: CLRHConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_RH_ProgressiveTouchUpDown;

	private: unsigned short m_Value;
	public: void SetValue( unsigned short value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderProgressBar();
};
// -----------------------------------------------------------------------------
// CLRHConfigForm [class]
// =============================================================================

#endif

