/************************************************************************************************
 ************************************************************************************************
 *
 *  file: RDEeprom.h
 *
 ************************************************************************************************/

#ifndef _RDEeprom_H
#define _RDEeprom_H

#include "CLCommon.h"

#ifndef _PACK
#define _PACK __attribute__ ((aligned(1),packed))
#endif

#ifdef _CLIKTS
#pragma pack( push, 1 )
#endif

// indirizzo del chip eeprom.
// #define   DEVICE_24LCO2B    0x50   // 256 Byte fmax 100KHz

//---- byte che identifica la versione dell'EEPROM ----
// #define EEPROM_VERSION      '0'

 //------------------------------------------------------------------------------------
 // List AccessoyHW[0]:    DXD,   BPD,   AWP,   CWD,   EHD,   HWD,  PHWD,  PEHD  (LSB)     dalla 2.15 inserito accessorio DXD
 // List AccessoyHW[1]:    DPS, PCAF,   PCAP, -----,  ----, DPPV2,   RFM,  MBUS  (LSB)   dove PCAP = Probe Costant Air Flow
 // List AccessoyHW[2]:  P2CO2, P1CO2, -----,  P2RH,  P1RH, -----, P1VOC, -----, (LSB)  
 // List AccessoyHW[3]:  -----, -----, -----, -----, -----, -----, -----, -----, (LSB)
 //------------------------------------------------------------------------------------
enum _NUMBER_ACCESSORY_EEP {
//     0              1              2              3             4               5              6              7          // bit
  ACC_EEP_PEHD,  ACC_EEP_PHWD,  ACC_EEP_HWD,   ACC_EEP_EHD,   ACC_EEP_CWD,   ACC_EEP_AWP,   ACC_EEP_BPD,   ACC_EEP_DXD,    // byte 1 
  ACC_EEP_MBUS,  ACC_EEP_RFM,   ACC_EEP_DPPV2, ACC_EEP_OUT,   ACC_EEP_INP,   ACC_EEP_PCAP,  ACC_EEP_PCAF,  ACC_EEP_DPP,    // byte 2
  ACC_EEP_EBP2, ACC_EEP_P1VOC, ACC_EEP_SSR,   ACC_EEP_P1RH,  ACC_EEP_P2RH,  ACC_EEP_EBPD,  ACC_EEP_P1CO2, ACC_EEP_P2CO2,  // byte 3
  ACC_EEP_EXT1,  ACC_EEP_EXT2,  ACC_EEP_EXT3,  ACC_EEP_EXT4,  ACC_EEP_FLW1,  ACC_EEP_FLW2,  ACC_EEP_DSC, ACC_EEP_NP_31,  // byte 4
};  

 //----------------------------------------------------------------
 // Tipi di Configurazioni Bypass Damper
 //----------------------------------------------------------------
 enum _SEL_BYPASS
 {
	BPD_AUTOMATIC,
	BPD_EXT_CTRL,
	BPD_MANUAL_CLOSE,
	BPD_MANUAL_OPEN,
	BPD_AUTO_ON_OFF
 };

 //----------------------------------------------------------------
 // Tipi di Configurazioni input
 //----------------------------------------------------------------
enum _CFG_INPUT {
     INP_DISABLE,                  // 0= Disable    
     INP_0V_UNIT_STOP,             // 1= 12V->Unit RUN , 0V->Unit STOP 
     INP_12V_UNIT_STOP,            // 2= 0V->Unit RUN , 12V->Unit STOP
     INP_REG_AIR_FLOW,             // 3= 0-10V Air flow regulation 
     INP_12V_BYPASS_OPEN,          // 4= 12V->Bypass Open ,  0V->Bypass Closed 
     INP_0V_BYPASS_OPEN,           // 5=  0V->Bypass Open , 12V->Bypass Closed	
     INP_12V_CLIMA_OFF,            // 6= 12V->spegne tutti gli accessori clima 
     INP_CFG_7_NONE,               // 7= * * *
     INP_CFG_8_NONE,               // 8= * * *
     INP_CFG_9_NONE,               // 9= * * *
     INP_CFG_10_NONE,              //10= * * *
     INP_12V_ALM_FIRE_UNIT_STOP,   //11= 12V-> Unit STOP + messaggio: 'ALARM Incendio Ventilazione ferma'
     INP_12V_ALM_FIRE_VENT_MAX,    //12= 12V-> Ventilazione MAX + messaggio:'ALARM Incendio Ventilazione al massimo'
     INP_12V_ALM_FIRE_ONLY_EXTRACT,//13= 12V-> Vent. Estrazione al Massimo, Immisione spenta + messaggio: 'ALARM Incendio Solo estrazione aria'
     INP_12V_ALM_FIRE_ONLY_SUPPLY, //14= 12V-> Vent. Immisione al Massimo, Estrazione spenta + messaggio: 'ALARM Incendio Solo estrazione aria'
};

// -------------- bit: Enab_Fuction ----------------
//  (LOW)  bit[7]:CAF  | bit[6]:CAP  | bit[5]:CSF    | bit[4]:ImbalanON   | bit[3]:STPL     | bit[2]:WeeklyON | bit[1]:BoostON   | bit[0]:DeFrostON. 
//  (HIGH) bit[15]:--- | bit[14]:--- | bit[13]:DPP   | bit[12]:PREHEATING | bit[11]:COOLING | bit[10]:HEATING | bit[9]:CtrlFilter| bit[8]:Password
enum _BIT_NUMBER_ENAB_FUCTIONS {
   // bit0, ... , bit7
   ENAB_DEFROST, ENAB_BOOST, ENAB_WEEKLY, ENAB_STEPLESS,  ENAB_IMBALANCE, ENAB_FSC, ENAB_CAP,  ENAB_CAF,
   //bit8, ... , bit15    
   ENAB_PASSWORD, ENAB_CTRL_FILTER, ENAB_HEATING,  ENAB_COOLING,  ENAB_PREHEATING, ENAB_DPP, ENAB_MBF, ENAB_CLEAN_EVENT,  

};

// -------------- Struct Weekly Day ----------------
typedef struct SDAYPROG_TAG
{
    byte numRange;        //  1 byte: numbers of ranges (from 0= disable to 4)
    byte timeON[4];       //  4 byte: timeON, Values from 0 to 48 (step di 30')
    byte timeOFF[4];      //  4 byte: timeOFF, Values from 0 to 48 (step di 30')
    // per ogni range si posso configurare finoi a : 4 step di velocita', 4 rif. di temp., 4 stati di imbalance
    char ConfigSpeed;     //  1 byte: bit[7,6]:Step Speed range 4 | bit[5,4]:Step Speed range 3 | bit[3,2]:Step Speed range 2 | bit[1,0]:Step Speed range 1.
    char ConfigImbal;     //  1 byte: bit[7,6]:Set Imbal. range 4 | bit[5,4]:Set Imbal. range 3 | bit[3,2]:Set Imbal. range 2 | bit[1,0]:Set Imbal. range 1.
    char ConfigTemp;      //  1 byte: bit[7,6]:Rif. Temp. range 4 | bit[5,4]:Rif. Temp. range 3 | bit[3,2]:Rif. Temp. range 2 | bit[1,0]:Rif. Temp.range 1.
}_PACK SDAYPROG;          // Totale 12 byte for day


//------------------------------------------------------------------------
// Definizione della struttare dei dati in RAM e relativi indirizzi
//------------------------------------------------------------------------
typedef struct EEPROM_DATA_TAG {
        //----------  Information (59 Byte) ------------------
/*000*/ byte  AddrUnit;								//  1 byte:  da 1 a 63, lo 0 e' utilizzato per i comandi di broadcast.
/*001*/ byte  Type_func;							//  1 byte:  configurazione funzionalita' UnitÃ :  0= BASIC, 1= PLUS, 2= EXTRA
/*002*/ byte  HW_Vers[4];							//  4 byte:  Ascii: versione hardware MB     Es: " 4.0"
/*006*/ byte  SW_Vers[5];							//  5 byte:  Ascii: versione software MB     Es: "2.01" oppure "2.10"
/*011*/ byte  SerialString[18];						// 18 byte:  Ascii:  "OrVe SIZE CFG DATA PRG",
													//              es:  "1565 0023 115 1351 002"
													//          SIZE:  0023, 0043, 0053,... 0423
													//          CFG:   [8]: '0'= OSC, '1'= SSC, '2'= EOS, '3'= FOS, .. | [9]: '1'='A', '2'='B',  ... | [10]: '1', '2', ... , '9'
													//          DATA:  [11,12]: '13' = Anno | [13,14]: '51' = Settimana
													//          PROG:  Progress. Number
		byte  swVer_ModBus[ 2 ];					//  2 byte:  Versione [0] = Major version, [1] = Minor Version
        byte  Sign_Test[2];							//  2 byte:  Ascii: Sigla Operatore che ha eseguito il Test (MM, etc..)
        byte  CodeErrTest;							//  1 byte:   se = 0  esito positivo, altrimenti viene inserito un codic di errore.

        long  hour_runnig;							//  4 byte:  ogni 10 ore memorizza in eeprom l'avanzamento del timer.
        long  time_lastCloggedFilers;				//  4 byte:  tempo in ore dell'ultima pulizzia filtri.

        byte  AccessoyHW[4];						//  4 byte:  parte 1 list accessory HW   (MSB)    PIR, [BPD],   AWP,   CWD,   EHD,   HWD,  PHWD,  PEHD  (LSB)
													//           parte 2 list accessory HW   (MSB)    DPS,  PCAF,  PCAP, [INPUT], [OUT], DDPV2, RFM,  MBUS  (LSB)
													//           parte 3 list accessory HW   (MSB)  P2CO2, P1CO2,  EBPD,  P2RH,  P1RH,   SSR, P1VOC,  EBP2  (LSB) 
                                                    //           parte 4 list accessory HW   (MSB)  -----, -----, -----, -----,  EXT4,  EXT3,  EXT2,  EXT1  (LSB)
													// Leggenda Acronimi:  DPS=Controllo Filtri con Press., PIVOC=Probe Interna VOC,  P1CO2=Probe 1 CO2,  PCAP= Probe Constant Air Pressure

        unsigned short  Enab_Fuction;				//  2 byte:  (LOW) bit[7]:CAF  | bit[6]:CAP  | bit[5]:CSF     | bit[4]:ImbalanON | bit[3]:STPL | bit[2]:WeeklyON | bit[1]:BoostON    | bit[0]:DeFrostON.
													//           (HIGH)bit[15]:--- | bit[14]:--- | bit[13]:---    | bit[12]:---      | bit[11]:--- | bit[10]:CLIMA   | bit[9]:CtrlFilter | bit[8]:PASSWORD

		unsigned short  msk_Enab_Fuction;			// bit = 0 funzione non abilitabile...
		byte  Dsc_Sdcard_Update_Delay;				// 1 byte : 3 to 60
		byte  Pir_Update_Delay;						// 1 byte : 3 to 30
        unsigned short  calibra_CAP1;               //  2 Byte:
        byte  Clean_Event_Delay;                    // 1 Byte : 30, 60 , 90
        byte KTS_Watchdog;                          // 1 Byte 0 or 1 ( default 0 )
        byte  size1_free[2];						// 2 byte:  liberi per ampliamenti futuri

        byte  cntUpdate_info;						//  1 byte:

        //--- configurazioni HW di fabbrica non modificabili (17 byte) ---
        byte  numMotors;							//  1 byte:  valori: 2, 4, 6.
        byte  numPulseMotors;						//  1 byte:  numero di pulse per giro. 1, 2, 3, 4,..., 8
        byte  typeMotors;							//  1 byte:  ('F' = Forward) , 'B' = Backward
        byte  chWireless;							//  1 byte:  numero canale wireless da 1 a 16 (era  progMotors = 'S'  non usato)
        byte  depotMotors;							//  1 byte:  depotenziamento dei motori da 100% a 40%
        byte  numNTC;								//  1 byte:  numero sonde da 2 a 4.
        byte  Posiz_NTC;							//  1 byte:  bit 7,6 = Exuast, bit 5,4 = Supply, bit 3,2 = Return, bit 1,0 = Fresh
        byte  RotazioneBypass;						//  1 byte:  0xFF = bypass chiuso in senso AntiOrario(default), 0= bypass chiuso in senso Orario
        //byte  size2_free[9];						//  9 byte:  liberi per ampliamenti futuri
        unsigned short Set_StepMotors_CAP1[4];		//  8 byte: 4 Soglie di velocita'  dei motori in modalita' : CAP  (Range da 30Pa a 250/350/450Pa), ..[3]= per funz. in Stepless
        byte  size2_free[1];						//  9 byte:  liberi per ampliamenti futuri

        //---------  Setting/Config. Param.(51 byte) ---------------
        byte  Set_Power_ON;							//  1 byte:   1= SET UNIT IDLE (power_on), 0 = SET UNIT STANDBY (power_off)
        byte  Config_Bypass;						//  1 byte:   0= Automatic,  1= Ext Ctrl,  2= Manual CLOSE,  3= Manual OPEN
        byte  Set_Input[2];							//  2 byte:   0= Disable
													//            1= 10V->Unit RUN , 0V->Unit STOP
													//            2=  0V->Unit RUN ,10V->Unit STOP
													//            3= 0-10V Air flow regulation
													//            4= 10V->Bypass Open ,  0V->Bypass Closed
													//            5=  0V->Bypass Open , 10V->Bypass Closed
        byte  Set_Output[2];						//  2 byte:   0= Disable                   (il rele rimane non alimentato)
													//            1= Bypass Status Open        (il rele passa in attrazione se: Bypass Open)
													//            2= Common Fault Status       (il rele passa in attrazione se: Unita' in allarme)
													//            3= Unit is Run (ex: SDD)     (il rele passa in attrazione se: Unita e' in funz.)
													//          128= Disable                   (il rele rimane in attrazione)
													//          129= Bypass Status Open        (il rele passa in Diseccitaz. se: Bypass Open)
													//          130= Common Fault Status       (il rele passa in Diseccitaz. se: Unita' in allarme)
													//          131= Unit is Run (ex: SDD)     (il rele passa in Diseccitaz. se: Unita' e' in funz.)
        byte  sel_idxStepMotors;					//  1 byte: Selettore dell'indice degli array Set_StepMotors*[4]: 0, 1, 2, 3=Steepless
        unsigned short Set_StepMotorsFSC_CAF[4];	//  8 byte: 4 Soglie di velocita'  dei motori in modalita' : FSC/CAF (Range: da 20.0% a 100.0%),   ..[3]= per funz. in Stepless
        unsigned short Set_StepMotors_CAP[4];		//  8 byte: 4 Soglie di velocita'  dei motori in modalita' : CAP  (Range da 30Pa a 250/350/450Pa), ..[3]= per funz. in Stepless
        signed char Set_Imbalance[2];				//  2 byte: 2 Set di Imbalance,  values max: +/-70 %.
        byte  Set_TimeBoost;						//  1 byte: valore espresso in minuti (min:15, max:240) se abilitato va al massimo della velocita'  per il tempo indicato.
        unsigned short  SetPoint_CO2;				//  2 byte: da 700 a 1500 PPM
        byte  SetPoint_RH;							//  1 byte: da 20% a 99%
        unsigned short  SetPoint_VOC;				//  2 byte: SetPoint_VOC, da 1 a 100 ppm
        union _PACK
		{
			unsigned short  gg_manut_Filter;		//  2 byte: gg funz., trascorso il quale occorre fare manutenzione ai Filter
			struct _PACK
			{
				byte DPP_Threshold;					// 1 byte: Soglia percentuale di cambio filtro per DPP
				byte DPP_FilterLevel;				// 1 byte: bit[0]:   Richiesta: 0 = Nessuna richiesta, 1 = Richiesta lettura
													//         bit[1]:   Tipo Lettura Richiesta: 0 = calibrazione, 1 = verifica
													//         bit[2-6]: Ultima lettura verifica (0-20) (in step di 5%)
			};
		};
        byte  servicePassword[5];					//  5 byte: password, 5 caratteri in Ascii numerici da'0' a '9'.
        byte  endUserPassword[5];					//  5 byte: password, 5 caratteri in Ascii numerici da'0' a '9'.
        unsigned short calibra_CAP;					//  2 byte: valore del CAP calibrato
		byte manual_Reset;							// 1 byte: 1 = rearm alarm manuale inserito (incendio), 0 = rearm alarm manuale ripristinato
		byte DPP_CalibrationValue;					// Valore percentuale di calibrazione (0 = Nessuna calibrazione effettuata)
        byte  Set_MBF_fresh;             //  1 byte: set modbus fan fresh  (Range: da 0.0% a 100.0%) // il modbus controlla in modo indipendente i motori
        byte  Set_MBF_return;            //  1 byte: set modbus fan return (Range: da 0.0% a 100.0%) // il modbus controlla in modo indipendente i motori
        //byte size3_free[1];							// 12 byte: liberi per ampliamenti futuri
		byte  SetPoint_Airflow_CO2;			// //  1 byte: da 40% a 100%

        byte cntUpdate_SettingPar;					//  1 byte:

        //---------- Calibrazione Sonde ( 6 byte) -----------------
        byte Calibr[6];								//  6 Byte: 4 sonde temp + 2 Qual_Air

        //--------- Soglie Temperature (20 byte)----------------
        short Bypass_minTempExt;					//  2 byte:  valore espresso in 15.0 °C
        short SetPointTemp[2];						//  4 byte:  Set-Point Temperature 1&2 value 16.0 °C a 32.0 °C. 0 = sole, 1 = luna
        char  idxSetPointT;							//  1 byte:  ...bit[0]: 1=Rif.Temp2, 0=Rif.Temp1
        signed char hister_AWP_Temp_Hot[2];			//  2 byte:  isteresi temperature per attivare HWD/EHD (0= OFF, 1= ON), con AWP presente.
        signed char hister_AWP_Temp_Cold[2];		//  2 byte:  isteresi temperature 1&2 per attivare CWD (0= OFF, 1= ON), con AWP presente.
        signed char hister_Temp_Hot[2];				//  2 byte:  isteresi temperature per attivare HWD/EHD (0= OFF, 1= ON), con loop aperto.
        signed char hister_Temp_Cold[2];			//  2 byte:  isteresi temperature 1&2 per attivare CWD (0= OFF, 1= ON), con loop aperto.
		byte  RefTSetting;							//  1 byte:  ...bit[6]: 1=START test IPEHD 0=STOP test IPEHD, bit[5,4,3,2]: speed_regulator , bit[1]: 1= TempAmb=TR / TempAmb=TS, bit[0]: *
		byte  DeltaTemp_Supply;						//  1 byte: isteresi da applicare alla temperatura in uscita al compressore se il conrtollo è sulla sonda supply 
        byte  Set_EHD_mod;                          //  1 byte: set EHD modulation level (Range: da 0.0% a 100.0%) // il modbus controlla in modo indipendente un EHD modulante
        byte  Set_BPD_mod;                          //  1 byte: set BPD modulation level (Range: da 0.0% a 100.0%) // il modbus controlla in modo indipendente un BPD modulante
        

        byte  cntUpdate_SetTemp;					//  1 byte:

        //--------- weekly program (85 byte) -------------------
        SDAYPROG sDayProg[7];						// 84 byte:  12 byte * 7 days

        byte  cntUpdate_dayProg;					//  1 byte:

        //------------------------  (2 byte) -------------------
        byte  none;									//  1 byte:  contatore aggiornamenti della eeprom
        byte  version_eeprom;						//  1 byte: '1'
}_PACK S_EEPROM;									// totale  Byte: 240


// //------------------------------------------------------------------------
// // definizione puntatore alla struttura eeprom.
// //------------------------------------------------------------------------
// #define ADDR_EEP(x)	(unsigned int)(&((S_EEPROM *)0x0000)->x)

// //------------------------- proto global ---------------------------------
// extern  byte read_byte_eeprom(unsigned short addr_eep);
// extern  unsigned short read_word_eeprom(unsigned short addr_eep);

// extern  void write_byte_eeprom(unsigned short addr_eep, byte val);
// extern  void write_byte_eeprom(unsigned short addr_eep, unsigned short val_16);

// //--------------------- array eeprom virtuale ----------------------------
// extern  byte Shadow_eep[255];

#ifdef _CLIKTS
#pragma pack( pop )
#endif

#endif //----- _EEPROM_MAP_H  -----



