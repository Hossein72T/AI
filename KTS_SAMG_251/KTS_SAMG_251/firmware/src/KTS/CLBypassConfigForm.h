 /*************************************************************************************
 *  file:			CLBypassConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLBypassConfigForm_h
#define __CLBypassConfigForm_h

#include "CLForm.h"
#include "CLBypass.h"

CLFormResult CLBypassConfigForm_Open( unsigned short options );

const byte CLBypassRotation_Clockwise			= 0x00;
const byte CLBypassRotation_Counterclockwise	= 0xFF;

// =============================================================================
// CLBypassConfigForm [class]
// =============================================================================
// Description: Form per la gestione del Bypass
// -----------------------------------------------------------------------------
class _PACK CLBypassConfigForm
	: public CLForm
{
	public: CLBypassConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;

	private: CLRectangle m_AutomaticOnConfigButtonRectangle;
	private: CLRectangle m_AutomaticOnStandbyConfigButtonRectangle;
	private: CLRectangle m_ManualOpenConfigButtonRectangle;
	private: CLRectangle m_ManualCloseConfigButtonRectangle;
	private: CLRectangle m_ClockwiseRotationButtonRectangle;
	private: CLRectangle m_CounterclockwiseRotationButtonRectangle;

	// Page
	private: CLPage m_Page;
	private: unsigned short m_Options;

	private: byte m_Config;
	public: void SetConfig( CLBypassConfig value );
	private: void RenderConfigButtons();

	private: CLRectangle m_MinTemperature_DownButtonRectangle;
	private: CLRectangle m_MinTemperature_UpButtonRectangle;

	private: float m_MinTemperature;
	public: void SetMinTemperature( float value );
	private: void RenderMinTemperature();

	private: byte m_Rotation;
	public: void SetRotation( byte value );
	private: void RenderRotationButtons();

	public: CLFormResult Open( unsigned short options );
	private: bool Save();

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLBypassConfigForm [class]
// =============================================================================

#endif

