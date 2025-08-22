/*****************************************
 *  File: RFM_driver
 *
 * Frequenza SPI 3.0 MHz
 *
 */
 
#include "RFM73.h"

/**************************************************
Function: SwitchToRxMode();
Description:
	switch to Rx mode
/**************************************************/
void SwitchToRxMode();

/**************************************************
Function: SwitchToTxMode();
Description:
	switch to Tx mode
/**************************************************/
void SwitchToTxMode();

/**************************************************
 Function: SetChannelNum

 Description:
   Set new channel number
   @Maury: Cambiando canale dobbiamo, reinserire i
           dati di Setup etc..
/**************************************************/
void SetChannelNum(UINT8 ch);


