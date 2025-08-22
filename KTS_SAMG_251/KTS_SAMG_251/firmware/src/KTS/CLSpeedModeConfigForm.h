 /*************************************************************************************
 *  file:			CLSpeedModeConfigForm.h
 *
 *  Author/Date:	Paolo Menchi aprile 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSpeedModeConfigForm_h
#define __CLSpeedModeConfigForm_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLSpeedMode.h"

CLFormResult CLSpeedModeConfigForm_Open( unsigned short options );

// =============================================================================
// CLSpeedModeConfigForm [class]
// =============================================================================
// Description: Form per la selezione del Flow Rate
// -----------------------------------------------------------------------------
class _PACK CLSpeedModeConfigForm
	: public CLForm
{
	public: CLSpeedModeConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_ThreeSpeedButtonRectangle;
	private: CLRectangle m_SteplessButtonRectangle;
	#ifdef FRANCETX_ENABLED
	private: CLRectangle m_FranceTxButtonRectangle;
	#endif

	private: CLSpeedModeType m_SpeedMode;
	public: void SetSpeedModeType( CLSpeedModeType value );

	public: CLFormResult Open( unsigned short options );

	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderAirFlowTypeButtons();
};
// -----------------------------------------------------------------------------
// CLSpeedModeConfigForm [class]
// =============================================================================

#endif

