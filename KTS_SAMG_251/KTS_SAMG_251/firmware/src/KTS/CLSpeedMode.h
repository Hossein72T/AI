#ifndef __CLSpeedMode_h
#define __CLSpeedMode_h

#include "CLCommon.h"
#include "RDEeprom.h"
#include "CLVentilationControl.h"

// Tipo del flow rate
enum CLSpeedModeType
{
	CLSpeedModeType_ThreeSpeed	= 0,
	CLSpeedModeType_Stepless	= 1,
#ifdef FRANCETX_ENABLED
	CLSpeedModeType_FranceTx	= 2
#endif
};

CLSpeedModeType SpeedMode_GetType();

unsigned short SpeedMode_Stepless_GetMinValue( CLVentilationControl ventilationControl );
unsigned short SpeedMode_Stepless_GetMaxValue( CLVentilationControl ventilationControl );
unsigned short SpeedMode_Stepless_GetValue( CLVentilationControl ventilationControl , bool Caps_Capr_State);
byte SpeedMode_Stepless_GetIncValue( CLVentilationControl ventilationControl );
bool SpeedMode_Stepless_SetValue( CLVentilationControl ventilationControl, unsigned short value , bool Caps_Capr_State);

byte SpeedMode_Speed_GetIndex();

unsigned short SpeedMode_Speed_GetValue( CLVentilationControl ventilationControl, byte index );
unsigned short SpeedMode_Speed_GetValue1( CLVentilationControl ventilationControl, byte index );
void SpeedMode_Speed_SetValue( CLVentilationControl ventilationControl, byte index, unsigned short value );
void SpeedMode_Speed_GetValues( CLVentilationControl ventilationControl, unsigned short* values );
void SpeedMode_Speed_SetValues( CLVentilationControl ventilationControl, unsigned short* values );

bool SpeedMode_Speed_Write( CLVentilationControl ventilationControl,
	CLSpeedModeType speedModeType,
	unsigned short* newSet_StepMotors,
	byte newSel_IdxStepMotors );

#endif

