/****************************************************************************
 *
 *  File: RFM73.h
 *
 *
 ****************************************************************************/

#ifndef _RFM73_H_
#define _RFM73_H_

#include "definitions.h"
#include "Eeprom.h"

//-------------------------------------
#ifndef INT8
#define INT8   char
#endif

#ifndef INT16
#define INT16  signed short int
#endif

#ifndef UINT8
#define UINT8  unsigned char
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef UINT32
#define UINT32 unsigned long
#endif


#define MAX_PACKET_LEN  32// max value is 32

//   power  : -10dbm, -5dbm, 0 dbm, +5 dbm
#define POWER_NEG_10DBM     0
#define POWER_NEG_5DBM      1
#define POWER_POS_0DBM      2
#define POWER_POS_5DBM      3

// data_rate:  1 Mbit, 2 Mbit
#define DATA_RATE_250KBPS   0
#define DATA_RATE_1MBPS     1
#define DATA_RATE_2MBPS     2

//************************FSK COMMAND and REGISTER****************************************//
// SPI(RFM73) commands
#define READ_REG        		0x00  // Define read command to register
#define WRITE_REG       		0x20  // Define write command to register
#define RD_RX_PLOAD     		0x61  // Define RX payload register address
#define WR_TX_PLOAD     		0xA0  // Define TX payload register address
#define FLUSH_TX        		0xE1  // Define flush TX register command
#define FLUSH_RX        		0xE2  // Define flush RX register command
#define REUSE_TX_PL     		0xE3  // Define reuse TX payload register command
#define W_TX_PAYLOAD_NOACK_CMD          0xb0
#define W_ACK_PAYLOAD_CMD		0xa8
#define ACTIVATE_CMD			0x50
#define R_RX_PL_WID_CMD			0x60  // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
#define NOP_NOP            		0xFF  // Define No Operation, might be used to read status register

// SPI(RFM73) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define REG_STATUS      0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address
#define PAYLOAD_WIDTH   0x1f  // 'payload length of 256 bytes modes register address

//interrupt status
#define STATUS_RX_DR 	0x40
#define STATUS_TX_DS 	0x20
#define STATUS_MAX_RT 	0x10

#define STATUS_TX_FULL 	0x01

//FIFO_STATUS
#define FIFO_STATUS_TX_REUSE 	0x40
#define FIFO_STATUS_TX_FULL 	0x20
#define FIFO_STATUS_TX_EMPTY 	0x10

#define FIFO_STATUS_RX_FULL 	0x02
#define FIFO_STATUS_RX_EMPTY 	0x01


//----------------- Configurazione IO Modulo RFM ------------------------------- 

//#define CE_RFM(x)      ( x ? (LATDbits.LATD6 = 1)  : (LATDbits.LATD6 = 0)) // output
//#define CSN_RFM(x)     ( x ? (LATDbits.LATD1 = 1)  : (LATDbits.LATD1 = 0))
//#define SCK_RFM(x)     ( x ? (LATCbits.LATC14 = 1) : (LATCbits.LATC14 = 0))
//#define MISO_RFM        PORTDbits.RD0   // input
//#define MOSI_RFM(x)    ( x ? (LATCbits.LATC13 = 1) : (LATCbits.LATC13 = 0))
//#define IRQ_RFM         PORTDbits.RD11  // input : INT0
//#define TR_EN_RFM(x)   ( x ? (LATDbits.LATD5 = 1) : (LATDbits.LATD5 = 0))
//#define PA_EN_RFM(x)   ( x ? (LATGbits.LATG6 = 1) : (LATGbits.LATG6 = 0))


//---------------------------------------------------------------
//   Dati per la gestione protocollo wireless
//---------------------------------------------------------------
typedef struct  {
    byte  channel;         // numero del canale della portatante da 1 a 16. (default = 1)
    byte  channel_old;
    byte  rf_setup;        // Power,....
    byte  install_rfm;     // se 1 il modulo Ã¨ installato,se 0 no.
    byte  level_signal;    // da 0 a 4 
    byte  status;          // Nessun messaggio pendente, ricezione in corso,....
    byte  num_packet;      // numero del pacchetto in progress
    byte  tot_packet;      // totale dei pacchetti che compongono il messaggio (da 1 a 5)
    byte  len;             // lunghezza del messaggio in Tx che Rx
    byte  pos_data_tx;     // posizione dell'ultimo byte trasmesso dell'array  data[].
    byte  num_repeat_tx;
    byte  data[140];       // buffer dei dati
	unsigned short deviceId;
	unsigned short receivedDeviceId;
} DEF_DATA_WIRELESS;

extern DEF_DATA_WIRELESS sdata_wi;


//------------------------------ proto ----------------------------------------- 
void init_port_RFM(void);
UINT8 SPI_Read_Reg(UINT8 reg);
void SPI_Read_Buf(UINT8 reg, UINT8 *pBuf, UINT8 bytes);

void SPI_Write_Reg(UINT8 reg, UINT8 value);
void SPI_Write_Buf(UINT8 reg, UINT8 *pBuf, UINT8 length);
void SPI_Write_Buf_bank(UINT8 reg, UINT8 *pBuf, UINT8 length);


void SPI_Bank1_Read_Reg(UINT8 reg, UINT8 *pBuf);
void SPI_Bank1_Write_Reg(UINT8 reg, UINT8 *pBuf);
void SwitchCFG(char _cfg);

int check_install_rfm(void);
void RFM73_Initialize(UINT8 RF_ch, UINT8 power, UINT8 data_rate);

#endif


