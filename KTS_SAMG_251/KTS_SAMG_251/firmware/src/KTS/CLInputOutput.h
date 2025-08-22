#ifndef __CLInput_h
#define __CLInput_h

#include "CLCommon.h"
#include "RDEeprom.h"

enum CLOutputType
{
	CLOutputType_Disable		= 0,
	CLOutputType_BypassOpen		= 1,
	CLOutputType_UnitIsFault	= 2,
	CLOutputType_UnitIsRun		= 3,
	CLOutputType_Valve			= 4,
	CLOutputType_SumWin			= 5,
	CLOutputType_MaxSpeed		= 6
};

short Input_ExtCtrl_GetRegAirFlowInputIndex();
short Input_ExtCtrl_GetRegAirFlowMeausure();
bool Input_Write( byte input1, byte input2 );

#endif

