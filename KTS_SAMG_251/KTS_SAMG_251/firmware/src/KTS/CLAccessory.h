#ifndef __CLAccessory_h
#define __CLAccessory_h

#include "CLCommon.h"
#include "RDEeprom.h"

const int AccessoryCount = 32;
extern const char* AccessoryNames[];

bool Accessory_IsPresent( int accessoryIndex );
bool Accessory_Set( int accessoryIndex, bool value );
void Accessory_GetCommandText( char* text, byte status );
void Accessory_GetStatusText( char* text, byte status );
int Accessory_GetPresentCount();

bool Accessory_CO2IsPresent();
bool Accessory_RHIsPresent();
bool Accessory_VOCIsPresent();

bool Accessory_HasCooler();
bool Accessory_HasHeather();
bool Accessory_HasPreCooler();

bool AccessoryDPP_Request( bool requestVerify );

#endif

