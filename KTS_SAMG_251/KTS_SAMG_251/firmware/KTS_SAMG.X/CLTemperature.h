#ifndef __CLTemperature_h
#define __CLTemperature_h

#include "CLCommon.h"
#include "RDEeprom.h"

float Temperature_Get();

enum CLHysteresisLimitType
{
	CLHysteresisLimitType_Off	= 0,
	CLHysteresisLimitType_On	= 1
};

float Hysteresis_GetHot( CLHysteresisLimitType limitType );
void Hysteresis_SetHot( CLHysteresisLimitType limitType, float value );
float Hysteresis_GetCold( CLHysteresisLimitType limitType );
void Hysteresis_SetCold( CLHysteresisLimitType limitType, float value );

float Hysteresis_GetAWPHot( CLHysteresisLimitType limitType );
void Hysteresis_SetAWPHot( CLHysteresisLimitType limitType, float value );
float Hysteresis_GetAWPCold( CLHysteresisLimitType limitType );
void Hysteresis_SetAWPCold( CLHysteresisLimitType limitType, float value );



#endif

