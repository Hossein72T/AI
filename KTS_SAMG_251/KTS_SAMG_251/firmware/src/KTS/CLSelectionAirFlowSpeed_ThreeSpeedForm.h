 /*************************************************************************************
 *  file:			CLSelectionAirFlowSpeed_ThreeSpeedForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionAirFlowSpeed_ThreeSpeedForm_h
#define __CLSelectionAirFlowSpeed_ThreeSpeedForm_h

#include "CLForm.h"
#include "CLVentilationControl.h"

CLFormResult CLSelectionAirFlowSpeed_ThreeSpeedForm_Open( unsigned short options,
	CLVentilationControl ventilationControl, unsigned short* speeds );

// =============================================================================
// CLSelectionAirFlowSpeed_ThreeSpeedForm [class]
// =============================================================================
// Description: Form per la selezione della data
// -----------------------------------------------------------------------------
class _PACK CLSelectionAirFlowSpeed_ThreeSpeedForm
	: public CLForm
{
	public: CLSelectionAirFlowSpeed_ThreeSpeedForm();

	public: CLFormResult Open( unsigned short options,
		CLVentilationControl ventilationControl, unsigned short* speeds );
};
// -----------------------------------------------------------------------------
// CLSelectionAirFlowSpeed_ThreeSpeedForm [class]
// =============================================================================

#endif

