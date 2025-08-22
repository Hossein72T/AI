#ifndef __CLFunction_h
#define __CLFunction_h

#include "CLCommon.h"
#include "RDEeprom.h"

bool Function_CanEnable( _BIT_NUMBER_ENAB_FUCTIONS functionIndex );
bool Function_IsEnabled( _BIT_NUMBER_ENAB_FUCTIONS functionIndex );
void Function_SetEnabled( _BIT_NUMBER_ENAB_FUCTIONS functionIndex, bool value );

bool Function_Write( _BIT_NUMBER_ENAB_FUCTIONS functionIndex, bool value );

#endif

