/*******************************************************************
 * file: CLCommunication_Driver.h
 *
 * Author/Date: Maurizio Colmone dic.2013
 *
 * Description: Il file gestisce il traffico sulla seriale 1, tramite
 *              il protocollo ser1.
 *
 ******************************************************************/

#ifndef __CLCommunication_Driver_h
#define __CLCommunication_Driver_h

#include "RDProtocol.h"
#include "CLSerialDriver.h"
#include "protocol_wireless.h"
#include "RFM73.h"

#define RFM_CHANNELS_MIN	1
#define RFM_CHANNELS_MAX	8

extern byte sRxBuffer[ MAX_SERIAL_BUFFER_LENGHT ];
extern DEF_DATA_WIRELESS sdata_wi;

//-------------------------------------------------------------
// Manda un messaggio all'unitÃ . 
// viene passato la stringa da mandare, e l'uscita da utilizzare
//   type_output : BY_WIRELESS
//                 BY_SERIAL_0
//-------------------------------------------------------------
void Write_Message(byte *buff, char type_output);

/*******************************************************************                                                                 
                                                                 
  Name:  Read_Message                                         
   
  Description:
    Analizza se vi sono messaggi in ricezione.
    Tempo di ricezione di 1 byte ÃƒÂ¨ circa 1,05ms.
        
                                                                      
  Return:
    Value statusRX |            Description
   ----------------+-----------------------------------------
         > 1           Ricezione OK , Lunghezza del Messaggio
          1            RUN_DOWNLOAD
          0            BUFFER EMPY nessun messaggio.
         -1            ERROR_HEAD_MESSAGE
         -2            ERROR_LEN_MESSAGE
         -3            ERROR_CKSUM_16
         
 *******************************************************************/          
int Read_Message();

//-------------------------------------------------
// La funzione gestisce il traffico dei messaggi in 
// wireless, Ã¨ temporizzata (sample= 9ms)
//-------------------------------------------------
void management_message_wi(unsigned long tmr_mills);

#endif

