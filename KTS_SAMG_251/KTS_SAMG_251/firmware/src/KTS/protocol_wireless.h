/**************************************************************************************** 
 * File:   protocol_wireless.h
 * Author: electro (Maurizio C.)
 *
 * Created on 7 aprile 2015, 9.17
 *
 * Descrizione:
 *  Il messaggio via wireless Ã¨ formato da N pachetti (min:1 max:5).
 *  Ogni pachetto contiene 28 byte di dati e 4 byte di controllo.
 *  
 *
 ****************************************************************************************/

#ifndef PROTOCOL_WIRELESS_H
#define	PROTOCOL_WIRELESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BY_WIRELESS    'W'
#define BY_SERIAL_0    'S'

//---------------------------------------------------------------
//  Composizione Messaggio protocollo wireless
//---------------------------------------------------------------
enum _index_Head_Message_Wireless {
   IHMW_ID_DEVICE_LO = 0,         // identitÃ  del device (low) che Ã¨ associato il messaggio
   IHMW_ID_DEVICE_HI,             // identitÃ  del device (high) che Ã¨ associato il messaggio
   IHMW_PACKET,                   // byte_01: bit[7..4]-> Totale Pachetti, bit[3..0]-> Numero pacchetto del messaggio.
   IHMW_LEN_DATA,                 // byte_02: Lunghezza dei dati utilizzati
   IHMW_START_DATA,               // Inizio BYTE Dati : 27 byte di dati a disposizione
   IHMW_END_DATA = 30,            // ..Fine BYTE Dati
   IHMW_CKSUM_8                   // byte_31:  1byte per il cksum 8bit
};


//---------------------------------------------------------------
//   Macro Status message
//---------------------------------------------------------------
#define WIRELESS_DISABLE           0x00 
#define BUFF_WIRELESS_EMPY         0x01 // Nessun messaggio pendente
#define RX_WIRELESS_IN_PROGRESS    0x02 // ricezione in corso
#define RX_WIRELESS_END            0x04 // ricezione finita
#define TX_WIRELESS_IN_PROGRESS    0x10 // Trasmissione in corso

//----------------------------------------------------------------
#define NUM_MAX_PACKET              5
#define NUM_BYTE_PACKET            27



#ifdef	__cplusplus
}
#endif

#endif	/* PROTOCOL_WIRELESS_H */

