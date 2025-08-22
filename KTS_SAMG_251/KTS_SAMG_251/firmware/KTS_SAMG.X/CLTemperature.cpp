#include "CLTemperature.h"
#include "CLKTS.h"
#include "CLFunction.h"

float Temperature_Get()
{
	return (float) gRDEeprom.SetPointTemp[ gRDEeprom.idxSetPointT ] / 10.0f;
}

float Hysteresis_GetHot( CLHysteresisLimitType limitType )
{
	return ((float) gRDEeprom.hister_Temp_Hot[ limitType ]) / 10.0f;
}

void Hysteresis_SetHot( CLHysteresisLimitType limitType, float value )
{
	gRDEeprom.hister_Temp_Hot[ limitType ]	= (signed char) (value * 10.0f);
}

float Hysteresis_GetCold( CLHysteresisLimitType limitType )
{
	return ((float) gRDEeprom.hister_Temp_Cold[ limitType ]) / 10.0f;
}

void Hysteresis_SetCold( CLHysteresisLimitType limitType, float value )
{
	gRDEeprom.hister_Temp_Cold[ limitType ]	= (signed char) (value * 10.0f);
}


float Hysteresis_GetAWPHot( CLHysteresisLimitType limitType )
{
	return ((float) gRDEeprom.hister_AWP_Temp_Hot[ limitType ]) / 10.0f;
}

void Hysteresis_SetAWPHot( CLHysteresisLimitType limitType, float value )
{
	gRDEeprom.hister_AWP_Temp_Hot[ limitType ]	= (signed char) (value * 10.0f);
}

float Hysteresis_GetAWPCold( CLHysteresisLimitType limitType )
{
	return ((float) gRDEeprom.hister_AWP_Temp_Cold[ limitType ]) / 10.0f;
}

void Hysteresis_SetAWPCold( CLHysteresisLimitType limitType, float value )
{
	gRDEeprom.hister_AWP_Temp_Cold[ limitType ]	= (signed char) (value * 10.0f);
}

