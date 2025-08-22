/*************************************************************************************
 *  file: CLSerialDriver.h
 *
 *  Author/Date:  04/02/2014
 *  
 *  Descrizione:   Funzioni per la gestione comunicazione tra KTFS e RD2.0
 *
 *  Esempio:
 *        
 *************************************************************************************/

#ifndef __CLSerialDriver_h
#define __CLSerialDriver_h

#include "CLCommon.h"

#define MAX_SERIAL_BUFFER_LENGHT  128

//---- STATI RICEZIONE SERIALI --------
#define  RUN_DOWNLOAD              1
#define  BUFFER_RX_EMPY            0            
#define  ERROR_HEAD_MESSAGE       -1          
#define  ERROR_LEN_MESSAGE        -2   
#define  ERROR_CKSUM_16           -3

void DisablePinTX();
void EnablePinTX();

#ifdef EXCLUDED

void Write_Message_Ser1(byte *buff);
int Read_Message_Ser1();

#endif

#endif

