#ifndef __CLVentilationControl_h
#define __CLVentilationControl_h

#include "CLCommon.h"
#include "RDEeprom.h"

enum CLVentilationControl
{
	CLVentilationControl_CAF	= ENAB_CAF,
	CLVentilationControl_FSC	= ENAB_FSC,
	CLVentilationControl_CAP	= ENAB_CAP
};

bool VentilationControl_CanSelect( CLVentilationControl value );

CLVentilationControl VentilationControl_Get();
//void VentilationControl_Set( CLVentilationControl value );
bool VentilationControl_Write( CLVentilationControl value );

#endif

