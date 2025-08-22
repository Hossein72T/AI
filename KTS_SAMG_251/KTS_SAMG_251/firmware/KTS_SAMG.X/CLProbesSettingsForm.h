 /*************************************************************************************
 *  file:			CLProbesSettingsForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLProbesSettingsForm_h
#define __CLProbesSettingsForm_h

#include "CLForm.h"

CLFormResult CLProbesSettingsForm_Open( unsigned short options );

// =============================================================================
// CLProbesSettingsForm [class]
// =============================================================================
// Description: Form per la configurazione delle sonde
// -----------------------------------------------------------------------------
class _PACK CLProbesSettingsForm
	: public CLForm
{
	public: CLProbesSettingsForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_NRAnalogProbes2ButtonRectangle;
	private: CLRectangle m_NRAnalogProbes3ButtonRectangle;
	private: CLRectangle m_NRAnalogProbes4ButtonRectangle;

	private: byte m_ProbeCount;
	public: void SetProbeCount( byte value );

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderDynamicObjects();
};
// -----------------------------------------------------------------------------
// CLProbesSettingsForm [class]
// =============================================================================

#endif

