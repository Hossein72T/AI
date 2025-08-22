/************************************************************************************************
 ************************************************************************************************
 * File: alarm.h
 *
 ************************************************************************************************/
#ifndef _CLAlarm_H
#define _CLAlarm_H

#include "CLCommon.h"
#include "RDAlarms.h"

extern bool Alarm_IsActive( int nalm );
extern void Alarm_SetActive( int nalm, bool value );

extern bool IsFireAlarm();
extern byte GetCurrentFireAlarm();

#endif


