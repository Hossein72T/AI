/* 
 * File:   uart_driver.h
 * Author: Marketing
 *
 * Created on 17 dicembre 2013, 11.29
 */

#ifndef UART_DRIVER_H
#define	UART_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

//--------------------------------------------------------
// Contatore per definire la fine di un messaggio, se dall'ultimo
// carattere ricevuto trascorre un tempo di circa 1 ms senza un successivo
// carattere allora il messaggio è concluso.
#define COUNTDOWN_UARTRX_DISABLE        0xFFFF
#define COUNTDOWN_LOAD_VALUE            0x0710  // 0x0700 = ~30ms

typedef unsigned char           BYTE;                           /* 8-bit unsigned  */
typedef unsigned short int      WORD;                           /* 16-bit unsigned */
typedef unsigned long           DWORD;                          /* 32-bit unsigned */


extern BYTE U1_buffRX[128];
extern BYTE count_U1RX;
extern BYTE U2_buffRX[128];
extern BYTE count_U2RX;

extern unsigned int countDownEndU1RX;
extern unsigned int countDownEndU2RX;


#ifdef	__cplusplus
}
#endif

#endif	/* UART_DRIVER_H */
