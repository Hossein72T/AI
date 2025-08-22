#include "CLAlarm.h" 

#include "CLKTS.h"

//----------------------------------------------------
// Ritorna lo stato dell'allarme, se attivo true
//----------------------------------------------------
bool Alarm_IsActive( int nalm )
{ 
   byte ie, sh;
  
   ie = (nalm >> 3);
   sh = nalm & 0x07;
    
   if (gKTSData.Events[ ie ] & (1 <<sh))
     return true;
  
   return false; 
}

void Alarm_SetActive( int nalm, bool value )
{ 
	byte ie, sh;

	ie = (nalm >> 3);
	sh = nalm & 0x07;
    
	if (value)
		gKTSData.Events[ ie ] |= (1 << sh);
	else
		gKTSData.Events[ ie ] &= ~(1 << sh);
}  

bool IsFireAlarm()
{
	return Alarm_IsActive( ALM_SMOKE_VENT_OFF ) ||
		Alarm_IsActive( ALM_SMOKE_VENT_MAX ) ||
		Alarm_IsActive( ALM_SMOKE_ONLY_EXT ) ||
		Alarm_IsActive( ALM_SMOKE_ONLY_SUP );
}

byte GetCurrentFireAlarm()
{
	if (Alarm_IsActive( ALM_SMOKE_VENT_OFF ))
		return ALM_SMOKE_VENT_OFF;
	if (Alarm_IsActive( ALM_SMOKE_VENT_MAX ))
		return ALM_SMOKE_VENT_MAX;
	if (Alarm_IsActive( ALM_SMOKE_ONLY_EXT ))
		return ALM_SMOKE_ONLY_EXT;
	if (Alarm_IsActive( ALM_SMOKE_ONLY_SUP ))
		return ALM_SMOKE_ONLY_SUP;
	return 0;
}
 
 



