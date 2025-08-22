#ifndef __CLKTSDefines_H
#define __CLKTSDefines_H

#ifdef _CLIKTS

#include <string.h>
#include <stdio.h>
#include <stddef.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef unsigned char byte;
typedef unsigned short word;

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define abs(x) ((x)>0?(x):-(x))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define RX_BUFFER_SIZE  128

unsigned long millis();
void delay( unsigned long millisencond );
void delayMicroseconds( unsigned int us );
long random(long);
long random(long, long);
void randomSeed(unsigned int);

double sin( double );
double cos( double );
double pow( double x, double y );

void	pinMode( uint8_t pin, uint8_t mode );
void	digitalWrite(uint8_t pin, uint8_t val);
int		digitalRead(uint8_t pin);
int		analogRead(uint8_t);
void	analogWrite(uint8_t, int);

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define OPEN 0x02

extern void setup(void);
extern void loop(void);

void KTSRun();

class Serial
{
	public: void begin( int baudRate );

	public: int available();
	public: int read();
	public: int write( byte* buff, int len ); 
};

#define _PACK __attribute__ ((aligned(1),packed)) 
//#define __DOXYGEN__

#define _VSARDUINO_H_
#define ARDUINO 23
#define ARDUINO_MAIN
#define printf iprintf
#define __PIC32__
#define __pic32__
#define F_CPU 80000000L
//#define __cplusplus
#define __inline__
#define __asm__(x)
#define __asm__(char)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
#define __ATTR_NORETURN__
#define __ATTR_MALLOC__

//typedef unsigned char byte;
//extern "C" void __cxa_pure_virtual() {;}

//
//

byte* EEPROM_GetEepromData( int& size );

//#include "C:\mpide-0023-windows-20111221\hardware\pic32\cores\pic32\wprogram.h"
//#include "C:\mpide-0023-windows-20111221\hardware\pic32\variants\Uno32\Board_Defs.h" 
//#include "C:\Documents and Settings\ITM\Documenti\Arduino\KTS\KTS.ino"
#else
#define _PACK   __attribute__ ((aligned(1),packed))
#endif
#endif


