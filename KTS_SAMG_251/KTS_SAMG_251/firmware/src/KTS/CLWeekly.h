#ifndef __CLWeekly_h
#define __CLWeekly_h

#include "CLCommon.h"
#include "RDEeprom.h"

#define Weekly_Status_IsActive( status ) (status & 0x01)
#define Weekly_Status_IsRunning( status ) (status & 0x02)
#define Weekly_Status_GetSpeedIndex( status ) ((status >> 6) & 0x03)
#define Weekly_Status_GetUnbalanceIndex( status ) ((status >> 4) & 0x03)
#define Weekly_Status_GetTemperatureIndex( status ) ((status >> 2) & 0x03)

void Weekly_GetTextStartTime( char* text, SDAYPROG* dayProgs, byte range );
void Weekly_GetTextEndTime( char* text, SDAYPROG* dayProgs, byte range );
void Weekly_GetTextAirFlowSpeed( char* text, SDAYPROG* dayProgs, byte range, bool includeMeasureUnit );
void Weekly_GetTextUnbalance( char* text, SDAYPROG* dayProgs, byte range );
void Weekly_GetTextTemperature( char* text, SDAYPROG* dayProgs, byte range );
char Weekly_GetTextTemperatureSymbol( SDAYPROG* dayProgs, byte range );

const char* Weekly_GetDayName( byte index );
bool Weekly_Write( SDAYPROG* dayProgs );

#endif

