/* 
 * File:   serial_protocol.h
 * Author: Marketing
 *
 * Created on 14 dicembre 2013, 9.57
 *
 * Descriptions:
 *  Protocollo Messaggio di uart interna al rack
 */

#ifndef SERIAL_PROTOCOL_H
#define	SERIAL_PROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

//-------------------------------------------------------
//              caratteri speciali protocollo
//-------------------------------------------------------
// inizio messaggio
#define PROTO_START_MSG_0       's'
#define PROTO_START_MSG_1       'm'
// TYPE_COMAND
#define COMAND_READ_EEP         'R'
#define COMAND_WRITE_EEP        'W'
#define COMAND_POLLING_CTRL_FAN 'F'


//---------------  Indirizzi RECEIVER  ------------------
#define ADDR_RD_UNIT            0x01
#define ADDR_CTRL_FAN           0x04
#define ADDR_REM_CTRL           0x07



//-------------------------------------------------------
//  Testa dei Messaggi del protocollo 1.0
//-------------------------------------------------------
enum index_Head_Message{
   IHM_START_MSG_0 = 0,    // byte_0: start message 's'
   IHM_START_MSG_1,        // byte_1: start message 'm'
   IHM_POS_CRC_LO,         // byte_2: posizione cksum_16 (byte LO) che è anche il penultimo byte
   IHM_ADDR_RECEIVER,      // byte_3: Indirizzo del destinatorio del messaggio
   IHM_TYPE_COMAND,        // byte_4: Tipo di comando/richiesta
   IHM_START_DATA          // byte_5: Inizio BYTE Dati, lo sviluppo dei dati è in funzione del TYPE_COMAND
};
   

//-----------------------------------------------------
//  Richesta di Polling da Modulo RD a Modulo CTRL_FAN
//  LEN: 6 + 9 = 15 Byte
//-----------------------------------------------------
enum index_message_req_polling_ctrlFan {
   IRQ_CMD_F_SPEED_FANS_R = IHM_START_DATA, // valori SPEED_FANS_R da 0 -> 255
   IRQ_CMD_F_SPEED_FANS_F,                  // valori SPEED_FANS_F da 0 -> 255
   IRQ_CMD_F_STATUS_LEDS,                   //  [1,0] LED 3 GIALLO (11= none, 10= ON FIXED, 01=Toggle, 00 = OFF)
                                            //  [3,2] LED 4 ROSS0  (11= none, 10= ON FIXED, 01=Toggle, 00 = OFF)
                                            //  [5,4] LED 1 VERDE  (11= none, 10= ON FIXED, 01=Toggle, 00 = OFF)
                                            //  [7,6] LED 2 VERDE  (11= none, 10= ON FIXED, 01=Toggle, 00 = OFF)
   IRQ_CMD_F_NPULSE_XROUND,                 // numero di pulse per giro. ( 2, 3, 4)
   IRQ_CMD_F_NUM_MOTORS,                    // numero di motori da gestire
   IRQ_CMD_F_BYTE_1_DONE,                   // done
   IRQ_CMD_F_BYTE_0_DONE,                   // done
   IRQ_CMD_F_CRC_LO,                        // byte_13
   IRQ_CMD_F_CRC_HI                         // byte_14
};


//-----------------------------------------------------
//  Risposta Polling da Modulo CTRL_FAN a Modulo RD
//  LEN : 6 + 22 = 28 Byte
//-----------------------------------------------------
enum index_message_resp_polling_ctrlFan {
   IRS_CMD_F_STATUS_FAN_R = IHM_START_DATA, // bit MSB->LSB : [7.none],[6.AlarmMR3], [5.AlarmMR3], [4.AlarmMR3],[3.ErrVoutSpeed],[2.PowerMR3],[1.PowerMR2],[0.PowerMR1]
   IRS_CMD_F_STATUS_FAN_F,                  // bit MSB->LSB : [7.none],[6.AlarmMF3], [5.AlarmMF3], [4.AlarmMF3],[3.ErrVoutSpeed],[2.PowerMF3],[1.PowerMF2],[0.PowerMF1]
   IRS_CMD_F_FEEDBK_VOUT_R_LO,              // valore di tensione letto in uscita del pilota ventole R: da 0.00V a 11.00V
   IRS_CMD_F_FEEDBK_VOUT_R_HI,
   IRS_CMD_F_FEEDBK_VOUT_F_LO,              // valore di tensione letto in uscita del pilota ventole F: da 0.0V a 11.00V
   IRS_CMD_F_FEEDBK_VOUT_F_HI,
   IRS_CMD_F_RPM_FAN_R1_LO,                 // RMP Motore R1
   IRS_CMD_F_RPM_FAN_R1_HI,
   IRS_CMD_F_RPM_FAN_R2_LO,
   IRS_CMD_F_RPM_FAN_R2_HI,
   IRS_CMD_F_RPM_FAN_R3_LO,
   IRS_CMD_F_RPM_FAN_R3_HI,
   IRS_CMD_F_RPM_FAN_F1_LO,
   IRS_CMD_F_RPM_FAN_F1_HI,
   IRS_CMD_F_RPM_FAN_F2_LO,
   IRS_CMD_F_RPM_FAN_F2_HI,
   IRS_CMD_F_RPM_FAN_F3_LO,
   IRS_CMD_F_RPM_FAN_F3_HI,
   IRS_CMD_F_RPM_VERSION_FW_H,              // versione FW 1,... Cifra + significativa
   IRS_CMD_F_RPM_VERSION_FW_L,              // versione FW 0,... Cifra - significativa
   IRS_CMD_F_BYTE_0_DONE,                   // done
   IRS_CMD_F_BYTE_1_DONE,                   // done
   IRS_CMD_F_CRC_LO,
   IRS_CMD_F_CRC_HI
};
   
 



#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_PROTOCOL_H */
