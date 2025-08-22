//************************************************************************
//**
//**  Definizione .
//**
//**  Data: dic.2013
//**
//**  Descrizione: Definizione struttura dati che girano in ram.
//**
//**  Autore: Maurizio Colmone
//**
//************************************************************************

#ifndef _RDData_H
#define _RDData_H

#include "CLCommon.h"
#include "Rtc_Pcf8563.h"  // RTC library

const int EVENT_COUNT = 13;

//--------------- Maschere: status_unit -------------------
#define MSK_CLEAR_OPERATING          0xFFC0   // Maschera bit[5,...,0], b000000 = equivale a  UNITA' IN STANDBY
#define POS_BIT_UNIT_RUN                  0   // bit[0]: se =1 l'unita' sta facendo girare i motori.
#define POS_BIT_DEFROST_OPERATING         1   // bit[1]: FUNZIONAMENTO IN DEFROST
#define POS_BIT_POST_VENT_OPERATING       2   // bit[2]: FUNZIONAMENTO POST VENTILAZIONE
#define POS_BIT_IMBALANCE_OPERATING       3   // bit[3]: FUNZIONAMENTO CON  I 2 RAMI SBILANCIATI
#define POS_BIT_BOOST_OPERATING           4   // bit[4]: FUNZIONAMENTO IN BOOST ATTIVO
#define POS_BIT_NONE_OPERATING            5   // bit[5]: FUNZIONAMENTO * none *
#define MSK_CLEAR_STS_BYPASS         0xFF3F   // Maschera bit[7,6]
#define POS_BIT_BYPASS_RUN                6   // bit[6]: STATO BYPASS IN APERTURA/CHIUSURA
#define POS_BIT_BYPASS_CLOSE              7   // bit[7]: STATO BYPASS CHIUSO
#define POS_BIT_CMD_FAN_INPUT             8   // bit[8]: Sta Comandando la velocitÃƒÂ  dei motori, in funz. della lettura degli inputs
#define POS_BIT_MAX_RH                    9
#define POS_BIT_MAX_CO2                  10
#define POS_BIT_MAX_VOC                  11
#define POS_BIT_IN_TESTING               12
#define POS_BIT_DPP_CHECK                13  //  bit[13]: Sta Comandando la velocit�  dei motori, in funz. della lettura della taratura o verifica DPP
#define POS_BIT_CLEANEVENT_CHECK         14  //  bit[14 : Clean Event Activated
#define POS_BIT_PIR_CHECK                15  //  bit[15]: PIR level 1 detect
// dal bit 12 al bit 15  * LIBERI *

//------------- Indici Accessori con uscita digitale (bus I2C) -------------
enum _INDEX_DIGITAL_ACCESSOTY {
  ACC_I2C_HEATER,
  ACC_I2C_COOLER,
  ACC_I2C_PREHEATER,
  ACC_I2C_CO2_1,
  ACC_I2C_CO2_2,
  ACC_I2C_RH_1,
  ACC_I2C_RH_2,
  ACC_I2C_VOC, 
  ACC_I2C_AWP,
  ACC_I2C_PCAP,    
  ACC_I2C_PCAF,    
  ACC_I2C_DPP,  
  ACC_I2C_DXD,                 // dalla 2.16 Accessorio Clima CALDO/FREDDO con compressore 
  ACC_I2C_EXT1,				   // dalla 2.24 ZH v1
  ACC_I2C_EXT2,
  ACC_I2C_EXT3,
  ACC_I2C_EXT4,  
  ACC_I2C_FLW1,				   // dalla 2.25 ZH v2
  ACC_I2C_FLW2,
  ACC_I2C_EBPD,
  ACC_I2C_SSR,
  ACC_I2C_EBP2,
  ACC_I2C_DSC,
  TOT_ACCESSORY_I2C            // totale 23 accessori. 
};

//---------------------Maschere bit: status_weekly ------------------------------
#define MSK_BIT_WEEKLY_ENAB 0x01   // bit[0]
#define MSK_BIT_WEEKLY_RUN  0x02   // bit[1]
#define POS_BIT_RIF_TEMP       2   // bit[3,2]:1,1=---/ 1,0=---    / 0,1=RIF_TEMP2 / 0,0=RIF_TEMP1
#define POS_BIT_SET_IMBAL      4   // bit[5,4]:1,1=---/ 1,0=---    / 0,1=IMBAL_1_ON/ 0,0=IMBAL_OFF
#define POS_STEP_SPEED         6   // bit[7,6]:1,1=---/ 1,0=SPEED_3/ 0,1=SPEED_2   / 0,0=SPEED_1

//--------------------- index: Probes Ambient. -----------------------------
enum _INDEX_PROBES_TEMPERATURE {
  I_PROBE_FRESH,
  I_PROBE_RETURN,
  I_PROBE_SUPPLY,
  I_PROBE_EXHAUST
};


//----------------- Type Probes Quality Ambient.(status_SensQAir) ---------------------
#define  PROBES_RH    0
#define  PROBES_CO2   1
#define  PROBES_VOC   2

//------------------------------------------------------------------------
// Definizione della timer
//------------------------------------------------------------------------
typedef struct S_CLOCK_TAG{
  byte  seconds;
  byte  minutes;
  byte  hours;
  byte  weekday;
}_PACK S_CLOCK_WEEK;


//------------------------------------------------------------------------
// Definizione della struttura Dati degli Accessori
//------------------------------------------------------------------------
typedef struct S_DIG_ACCESSORY_TAG{
  byte  comand;              // Comando di Accensione o Spegnimento
  byte  sts;                 // Stato in cui si trova l'accessorio: ..., bit[2]:1=ACCESO/0=SPENTO, bit[1]:1=OPEARATIVO, bit[0]:1=Collegato
  int   measure1;            // misura principale
  int   measure2;            // misura secondaria
  byte  size_pwr;            // taglia potenza es: 10 = 1,0KW, 15 = 1,5KW  etc..
  byte  level_link;          // bontÃƒÂ  della comunicazione (valore espresso in 10/10)
  byte  cnt_link_ok;         // Contatore Link buoni
  byte  cnt_link_ko;         // Contatore Link falliti
  byte  cnt_persist_link_ko; // contatore di persistenza di collegamenti Falliti
}_PACK S_DIG_ACCESSORY;  // tot: 12 byte

//------------------ Definizione stati accesorio ------------------------
#define STS_ACC_CONNECT     0x01  // bit.0: l'accesorio e' stato rilevato dall'unita'Â  almeno 1 volta
#define STS_ACC_OPERATIVE   0x02  // bit.1: l'accessorio e' operativo (no link KO)
#define STS_ACC_ON          0x04  // bit.2: l'accessorio e' acceso
#define STS_ACC_ACQUA       0x08  // bit.3: l'accessorio e' tipo acqua


#define CMD_OFF             0x01   // bit.0: byte command
#define CMD_ON              0x02   // bit.1: byte command

// typedef struct SDATA_TAG {

	// // byte KTS_Connect;
	// byte level_link_CTRLFAN;

	// S_DIG_ACCESSORY AccI2C[ TOT_ACCESSORY_I2C ];	// dati degli Accessory collegati tramite I2C

	// // setting par.
	// // byte speed_motors_R;                   // comando ai motori Returns, 0 -> 255 , il dato si puo' discostare dal valore in eeprom se vi e' in corso un Defrost, oppure una Co2 Alarm,...
	// // byte speed_motors_F;                   // comando ai motori Returns, 0 -> 255 , il dato si puo' discostare dal valore in eeprom se vi e' in corso un Defrost, oppure una Co2 Alarm,...

	// // misure
	// int feedbk_v_speed_motors_R;					// tensione letta sul comando dei motori ramo RETURN (0.00V a 11.00V) il valore ÃƒÂ¨ moltipl. per 100, quindi 1100 = 11.00V
	// int feedbk_v_speed_motors_F;					// tensione letta sul comando dei motori ramo FRESH  (0.00V a 11.00V) il valore ÃƒÂ¨ moltipl. per 100, quindi 1100 = 11.00V
	// int measure_CO2_max;        					// valore massimo di Co2 tra i vari sensori: espresso in PPM ( da 0 a 2000 PPM)
	// int measure_RH_max;         					// valore massimo di UmiditÃƒÂ  tra i vari sensori: da 0% a 99%
	// int measure_VOC_max;        					// valore massimo di VOC tra i vari sensori: da 0  a 10000 ug/M3
	// int measure_pressure;       					// valore espresso in Pascal da 0 a 1000Pa
	// // int measure_RH_Analogic;               	// Misura della sonda RH interna all'Unita'
	// // int measure_VOC_Analogic;              	// Misura della sonda VOC interna all'Unita'
	// // int measure_CO2_Analogic;              	// Misura della sonda CO2 interna all'Unita'
	// int measure_Temp[4];                   		// 0=T_Fresh, 1=T_Return, 2=T_Supply, 3=T_Exhaust  (i valori temp. sono espressi per 10, es: 102 = 10.2 gradi C)
	// // int measure_input[2];                  	// i valori sono grezzi (0 a 1024)
	// // int measure_I_KTS;                     	// valori espresi in mA: FS=1024 = 250mA
	// int rpm_motors_R[3];
	// int rpm_motors_F[3];

	// // // stati
	// word status_unit;                      		// 2 byte:  bit[15,14,13,12]: * none *
												// //          bit[11]: 1= VOC_MAX, bit[10]: 1= CO2_MAX, bit[9]: 1= RH_MAX
												// //          bit[8]: 1= CMD_FAN_INPUT
												// //          bit[7,6]: b10=BypassClose, b01=BypassRun, b00=BypassOpen
												// //          bit[5,...,0]: b10000= * none *,  b010000= RUN BOOST, b001000= RUN IMBALANCE, b000100=RUN POST_VENT, b000010=RUN DeFROST, b00001=RUN NORMAL, b000000=STANDBY
	// byte status_weekly;                    		// 1 byte:  bit[7,6]:1,0=SPEED3/ 0,1=SPEED2/ 0,0=SPEED1 | bit[5,4]: 0,1=IMBAL_1_ON/ 0,0=IMBAL_OFF | bit[3,2]:0,1=RIF_TEMP2/ 0,0=RIF_TEMP1 | bit[1]: WEEKLY_RUN, bit[0]:WEEKLY_ENABLE
	// // byte status_Leds_ctrlFan;					// 1 byte:   [1,0] LED BYPASS    (00 = OFF, 01=Toggle, 10= ON, 11= none)
												// //           [3,2] LED ALARM     (00 = OFF, 01=Toggle, 10= ON, 11= none)
												// //           [5,4] LED MOTORS R  (00 = OFF, 01=Toggle, 10= ON, 11= none)
												// //           [7,6] LED MOTORS F  (00 = OFF, 01=Toggle, 10= ON, 11= none)
	// byte StatusMotorsR;                    		// 1 byte:   bit.. 7.none | 6.AlarmM3 | 5.AlarmM2 | 4.AlarmM1 | 3.none | 2.PowerON_M3 | 1.PowerON_M2 | 0.PowerON_M1
	// byte StatusMotorsF;                    		// 1 byte:   bit.. 7.none | 6.AlarmM3 | 5.AlarmM2 | 4.AlarmM1 | 3.none | 2.PowerON_M3 | 1.PowerON_M2 | 0.PowerON_M1

	// // // Allarmi/ Eventi
	// byte Events[ EVENT_COUNT ];							// 13 byte:  vedi in testa al files 'Definizione byte eventi'

	// byte  cntUpdate_info;         //  1 byte:
	// byte  cntUpdate_SettingPar;   //  1 byte:
	// byte  cntUpdate_SetTemp;      //  1 byte:
    // byte  cntUpdate_dayProg;      //  1 byte:

// } _PACK S_DATA;

#endif // chiudi __DATA_H


