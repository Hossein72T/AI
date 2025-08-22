#ifndef __CLBypass_h
#define __CLBypass_h

#include "CLCommon.h"
#include "RDEeprom.h"
#include "CLKTS.h"

enum CLBypassStatus
{
	CLBypassStatus_Open		= KTSStatusUnit_BypassState_BypassOpen,
	CLBypassStatus_Run		= KTSStatusUnit_BypassState_BypassRun,
	CLBypassStatus_Close	= KTSStatusUnit_BypassState_BypassClose
};

enum CLBypassConfig
{
	CLBypassConfig_AutomaticOn			= BPD_AUTOMATIC,
	CLBypassConfig_ExternalControl		= BPD_EXT_CTRL,
	CLBypassConfig_ManualClose			= BPD_MANUAL_CLOSE,
	CLBypassConfig_ManualOpen			= BPD_MANUAL_OPEN,
	CLBypassConfig_AutomaticOnStandby	= BPD_AUTO_ON_OFF
};

CLBypassStatus Bypass_GetStatus();
void Bypass_GetConfigText( char* text, byte configBypass, bool combineManual );
void Bypass_GetStatusText( char* text, word statusUnit );
bool Bypass_Write( byte config );
bool Bypass_WriteMinTemperature( float value );
bool Bypass_WriteRotation( byte rotation );

float Bypass_GetMinTemperature();
void Bypass_SetMinTemperature( float value );

#endif

