#ifndef _CLIKTS
/***********************************************************
 * file: eeprom.cpp
 *
 * Description:
 *
 *
 *
 *********************************************************/
 
#include "eeprom.h"

extern volatile APP_TRANSFER_STATUS transferStatus;
_PCA9500 PCA9500;

/*********************************************************************
*
* Messaggio di scrittura di 1 byte:
*
*       S   BYTE_CONTROL  A  WORD_ADDRESS   A   DATA_WRITE    A P     
*      +-+---------------+-+---------------+-+---------------+-+-+
* SDA   \|1 0 1 0 1 1 0 0|0|A A A A A A A A|0|D D D D D D D D|0|/
*
**********************************************************************/
void EEPROM_write_byte(uint16_t address, uint8_t data )
{
    
  byte Buff[2];
  
  if(address > 255)
      address = 255;
      
  PCA9500.WP = 0;
  PCA9500_write( PCA9500 );
  Buff[0] = address;
  Buff[1] = data;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(0x53, &Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  SYSTICK_DelayMs ( 5 );
  PCA9500.WP = 1;
  PCA9500_write( PCA9500 );
  
}

/*************************************************************************************
*
* Messaggio di lettura di 1 byte (RANDOM_READ):
*
*      S   BYTE_CONTROL  A  WORD_ADDRESS   A S  BYTE_CONTROL  |S|  DATA_READ     |N|P     
*     +-+---------------+-+---------------+-+-+---------------+-+----------------+-+-+
* SDA  \ 1 0 1 0 0 0 0 0 0 A A A A A A A A 0 \ 1 0 1 0 0 0 0 1 0  R R R R R R R R 1 /
*
***************************************************************************************/
byte EEPROM_read_byte(uint16_t  address)
{	
  uint8_t  rdata=0xFF;
  uint8_t  Address;
  
  PCA9500.WP = 0;
  PCA9500_write( PCA9500 );
  Address = address;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_WriteRead(0x53, &Address, 1,  &rdata, 1);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  SYSTICK_DelayMs ( 1 );
  PCA9500.WP = 1;
  PCA9500_write( PCA9500 );
  
  return rdata;
	
}

void PCA9500_write( _PCA9500 data )
{
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(0x20, &data.Output, 1);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { }; 
}

_PCA9500 PCA9500_read( void )
{
    
  _PCA9500 data;
  
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Read(0x20, &data.Output, 1);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };

  return data;
          
}

#endif

