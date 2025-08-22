 /*************************************************************************************
 *  file:			CLInputConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLInputConfigForm_h
#define __CLInputConfigForm_h

#include "CLForm.h"

CLFormResult CLInputConfigForm_Open( unsigned short options );

// =============================================================================
// CLInputConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle porte di input
// -----------------------------------------------------------------------------
class _PACK CLInputConfigForm
	: public CLForm
{
	public: CLInputConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;

	private: CLRectangle m_DisableButtonRectangle;
	private: CLRectangle m_0VUnitStopButtonRectangle;
	private: CLRectangle m_10VUnitStopButtonRectangle;
	private: CLRectangle m_RegAirFlowButtonRectangle;
	private: CLRectangle m_RegAirFlowProgressBarRectangle;
	private: CLRectangle m_10VBypassOpenButtonRectangle;
	private: CLRectangle m_0VBypassOpenButtonRectangle;

	private: CLRectangle m_FireNoFanButtonRectangle;
#if FIREALARM_ALL_CONFIGURATION == 1
	private: CLRectangle m_FireMaxFanButtonRectangle;
	private: CLRectangle m_FireOnlyFanExtractButtonRectangle;
	private: CLRectangle m_FireOnlyFanSupplyButtonRectangle;
#endif
	private: CLRectangle m_Input1ButtonRectangle;
	private: CLRectangle m_Input2ButtonRectangle;

	private: CLPage m_Page;

	private: byte m_CurrentPowerON;

	private: byte m_SelectedInputIndex;
	private: byte m_SetInputs[ 2 ];

	private: float m_SaveInputMeasures[ 2 ];

	public: void SelectInput( byte index, bool focusSelectedPage );
	public: void SetInput( byte index, byte value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderInputButtons();
	private: void RenderInputConfigButtons();
	private: void RenderFireConfigButtons();
	private: void RenderInputMeasure( bool forceRefresh );
};
// -----------------------------------------------------------------------------
// CLInputConfigForm [class]
// =============================================================================

#endif

