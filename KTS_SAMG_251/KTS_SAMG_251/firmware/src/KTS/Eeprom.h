/***********************************************************
 * file: eeprom.h
 *
 * Description: Funzioni a basso livello per accedere alla eeprom
 *
 *
 *
 *********************************************************/

#ifndef __Eeprom_h
#define __Eeprom_h

#include "definitions.h"
#include "CLCommon.h"

typedef union __attribute__ ((packed)) {
    struct {
    byte CE_RFM : 1;
    byte TREN_RFM : 1;
    byte PAEN_RFM : 1;
    byte IRQ_RFM : 1;
    byte WIFI_RESET : 1;
    byte WP : 1;
    byte USB_ID : 1;
    };
    
    byte Output;
    
}_PCA9500;

/*********************************************************************
*
* Messaggio di scrittura di 1 byte:
*
*       S   BYTE_CONTROL  A  WORD_ADDRESS   A   DATA_WRITE    A P     
*      +-+---------------+-+---------------+-+---------------+-+-+
* SDA   \|1 0 1 0 1 1 0 0|0|A A A A A A A A|0|D D D D D D D D|0|/
*
**********************************************************************/
void EEPROM_write_byte(uint16_t address, uint8_t data );

/*************************************************************************************
*
* Messaggio di lettura di 1 byte (RANDOM_READ):
*
*      S   BYTE_CONTROL  A  WORD_ADDRESS   A S  BYTE_CONTROL  |S|  DATA_READ     |N|P     
*     +-+---------------+-+---------------+-+-+---------------+-+----------------+-+-+
* SDA  \ 1 0 1 0 0 0 0 0 0 A A A A A A A A 0 \ 1 0 1 0 0 0 0 1 0  R R R R R R R R 1 /
*
***************************************************************************************/
byte EEPROM_read_byte(uint16_t  address);

void PCA9500_write( _PCA9500 data );

_PCA9500 PCA9500_read( void );

#endif
