/* 
 * File:   data.h
 * Author: Marketing
 *
 * Created on 16 dicembre 2013, 10.51
 */

#ifndef DATA_H
#define	DATA_H

//#define  _DEBUG_CODE  // se non commenatta attiva le funzioni di Monitor del codice

#include <stdint.h>

typedef unsigned char           BYTE;                           /* 8-bit unsigned  */
typedef unsigned short int      WORD;                           /* 16-bit unsigned */
typedef unsigned long           DWORD;                          /* 32-bit unsigned */

#ifdef	__cplusplus
extern "C" {
#endif

//================ Definizione struttura dati ================
typedef struct
{
   volatile unsigned int numMotorsUnit;         // niumero di motori che ha l'unità 2, 4, 6
   volatile unsigned int numPulse_xround;       // il modulo RD passa il numero di pulse per giro (1, 2, 3, 4,..) in funz. del tipo di motore
   volatile unsigned int rpmMotorsR[3];         // velocità motori ramo R (rpm)
   volatile unsigned int rpmMotorsF[3];         // velocità motori Ramo F (rpm)
   volatile unsigned int StatusMotorsR;         // ...,[6.AlarmMR3], [5.AlarmMR3], [4.AlarmMR3],[3.none],[2.PowerMR3],[1.PowerMR2],[0.PowerMR1]
   volatile unsigned int StatusMotorsF;         // ...,[6.AlarmMF3], [5.AlarmMF3], [4.AlarmMF3],[3.none],[2.PowerMF3],[1.PowerMF2],[0.PowerMF1]
   volatile unsigned int SetSpeedMotorsR;       // SetPoint Velocità Motori Ramo R (0% - 100%), il dato viene passato dal modulo RD
   volatile unsigned int SetSpeedMotorsF;       // SetPoint Velocità Motori Ramo F (0% - 100%), il dato viene passato dal modulo RD
   volatile unsigned int SpeedMotorsR_x100V;    // Tensione letta in uscita dall'OP proporzionata al Setpoint R es: 50% = 500 = 5.00V
   volatile unsigned int SpeedMotorsF_x100V;    // Tensione letta in uscita dall'OP proporzionata al Setpoint F es: 50% = 500 = 5.00V
   volatile unsigned int StatusLeds;            //  [1,0] LED BYPASS    (11= none, 10= ON, 01=Toggle, 00 = OFF)
                                                //  [3,2] LED ALARM     (11= none, 10= ON, 01=Toggle, 00 = OFF)
                                                //  [5,4] LED MOTORS R  (11= none, 10= ON, 01=Toggle, 00 = OFF)
                                                //  [7,6] LED MOTORS F  (11= none, 10= ON, 01=Toggle, 00 = OFF)

}DEF_SDATA;

//----------- Global VARS ------------
extern DEF_SDATA  sdata;
extern int countdown_link_ko;

extern BYTE versionCode[2];
extern BYTE EnabMuxTacho;

#ifdef	__cplusplus
}
#endif

#endif	/* DATA_H */
