 /*************************************************************************************
 *  file:			KTS.h
 *
 *  Author/Date:
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLKTS_h
#define __CLKTS_h

#include "CLCommon.h"
#include "RDData.h"
#include "CLForm.h"
#include "RDEeprom.h"
#include "CLDateTime.h"
#include "CLLocalitation.h"
#include "CLSpeedMode.h"
#include "CLVentilationControl.h"
#include "CLKTSEeprom.h"
#include "CLCommunicationManager.h"

#define KTSStatusUnit_IsVOCMax( status ) (status & 0x0800)
#define KTSStatusUnit_IsCO2Max( status ) (status & 0x0400)
#define KTSStatusUnit_IsRHMax( status ) (status & 0x0200)
#define KTSStatusUnit_CmdFanInput( status ) (status & 0x0100)
#define KTSStatusUnit_BypassState( status ) (status & 0x00C0)

#define KTSStatusUnit_UnitState_IsSTANDBY( status ) ((status & 0x3F) == 0x00)
#define KTSStatusUnit_UnitState_IsIDLE( status ) (status & 0x01)
#define KTSStatusUnit_UnitState_IsRUN_DEFROST( status ) (status & 0x02)
#define KTSStatusUnit_UnitState_IsRUN_POST_VENT( status ) (status & 0x04)	
#define KTSStatusUnit_UnitState_IsRUN_IMBALANCE( status ) (status & 0x08)
#define KTSStatusUnit_UnitState_IsRUN_BOOST( status ) (status & 0x10)

#define KTSStatusUnit_BypassState_BypassClose	0x80
#define KTSStatusUnit_BypassState_BypassRun		0x40
#define KTSStatusUnit_BypassState_BypassOpen	0x00

extern const char* BackdoorPassword;
extern const char* AdminPassword;

extern const char* FirmwareVersion; // Firmware Version
//extern char* gCustomizationCode;

// LCD
extern TFTLCD gLCD;

// Handler per la gestione delle risposte KTS
extern void KTS_PollingBaseResponse_Callback( byte* rxBuffer, void* userData );
extern void KTS_DebugDataResponse_Callback( byte* rxBuffer, void* userData );
extern void KTS_ReadEepromResponse_Callback( byte* rxBuffer, void* userData );
extern void KTS_WriteEepromResponse_Callback( byte* rxBuffer, void* userData );

#define KTS_QueueWriteEepromRequest( index, count, status ) \
		ComQueue_AddWriteEepromRequest( index, count, status, KTS_WriteEepromResponse_Callback );

#define KTS_QueueReadEepromRequest( sectionInfo, status ) \
		ComQueue_AddReadEepromRequest( sectionInfo, status, KTS_ReadEepromResponse_Callback );

#define KTS_QueuePollingBaseRequest( status ) \
		ComQueue_AddPollingBaseRequest( status, KTS_PollingBaseResponse_Callback );

// Valore del campo PowerON in eeprom 
enum CLKTSPowerMode
{
	CLKTSPowerMode_Off	= 0,
	CLKTSPowerMode_On	= 1
};

// Valore del campo Type_Func in eeprom
enum CLKTSType
{
	CLKTSType_BASIC	= 0,
	CLKTSType_EXTRA	= 1,
	CLKTSType_DEMO	= 0xFF
};

// Dati del polling base
// -----------------------------------------------------------------------------
struct _PACK CLKTSData
{
	// ------------------------------------------------------
	// ----[ Dati valorizzati dal messaggio PollingBase ]----
	// ------------------------------------------------------

	// 0=T_Fresh, 1=T_Return, 2=T_Supply, 3=T_Exhaust  (i valori temp., es: 102 = 10.2 Ã‚Â°C)
	float Measure_Temp[ 4 ];

	// valore massimo di Co2 tra i vari sensori: espresso in PPM ( da 0 a 2000 PPM)
	int Measure_CO2_max;

	// valore massimo di UmiditÃƒÂ  tra i vari sensori: da 0% a 99%
	int Measure_RH_max;

	// valore massimo di VOC tra i vari sensori: da 0 a 100 ppm
	int Measure_VOC_max;

	// temperature corrente awp
	float Measure_Temp_AWP;

	// stati
	word Status_Unit;	// 2 byte:  bit[15,14,13,12]: * none *
						//          bit[11]: 1= VOC_MAX, bit[10]: 1= CO2_MAX, bit[9]: 1= RH_MAX
						//          bit[8]: 1= CMD_FAN_INPUT
						//          bit[7,6]: b10=BypassClose, b01=BypassRun, b00=BypassOpen
						//          bit[5,...,0]: b100000= * none *,  b010000= RUN BOOST, b001000= RUN IMBALANCE, b000100=RUN POST_VENT, b000010=RUN DeFROST, b00001=RUN NORMAL, b000000=STANDBY

	byte Status_Weekly; // 1 byte:  bit[7,6]:1,0=SPEED3/ 0,1=SPEED2/ 0,0=SPEED1 | bit[5,4]: 0,1=IMBAL_1_ON/ 0,0=IMBAL_OFF | bit[3,2]:0,1=RIF_TEMP2/ 0,0=RIF_TEMP1 | bit[1]: WEEKLY_RUN, bit[0]:WEEKLY_ENABLE

	// Allarmi / Eventi
	byte Events[ EVENT_COUNT ];							// 13 byte:  vedi in testa al files 'Definizione byte eventi'

	// Update Counters
	byte CntUpdate_info;         //  1 byte:
	byte CntUpdate_SettingPar;   //  1 byte:
	byte CntUpdate_SetTemp;      //  1 byte:
    byte CntUpdate_dayProg;      //  1 byte:

	byte InputMeasure1;
	byte InputMeasure2;

	byte IncreaseSpeed_RH_CO2;
	
	byte DSC_Status;
};

// Dati del polling Debug Data
// -----------------------------------------------------------------------------
struct _PACK CLKTSDebugData
{
	public: byte PreHeater_Status;
	public: byte Heater_Status;
	public: byte Cooler_Status;
	public: byte Dsc_Status;
};

#define AccessoryClimaStatus_InAlarm( status )		((status & 0x10) >> 4)
#define AccessoryClimaStatus_Command( status )		((status & 0x08) >> 3)
#define AccessoryClimaStatus_IsOn( status )			((status & 0x04) >> 2)
#define AccessoryClimaStatus_IsAir( status )		((status & 0x02) >> 1)
#define AccessoryClimaStatus_IsConnected( status )	(status & 0x01)

// Stato del KTS
enum CLKTSRunningMode
{
	CLKTSRunningMode_Initializing,
	CLKTSRunningMode_PowerOff,
	CLKTSRunningMode_Running,
	CLKTSRunningMode_Scanning,
	CLKTSRunningMode_FireAlarm
};

// Variabili globali
// -----------------------------------------------------------------------------
struct _PACK CLKTSGlobal
{
	// Indica se Ã¨ presente almeno un allarme (escluso il filtro da cambiare)
	bool InAlarm;

	// Indica se Ã¨ l'allarme del filtro
	bool FilterInAlarm;

	// Indica la modalitÃ  di esecuzione corrente
	CLKTSRunningMode RunningMode;

	// Indica se Ã¨ attivo lo screen saver
	bool ScreenSaverActive;
	short ScreenSaverSuspendCounter;
	unsigned long ScreenSaver_LastTouchedMilliseconds;

	// Ultimo touch
	unsigned long LastTouchedMilliseconds;

	// Variabile per la gestione del party (BOOST)
	CLDateTime Party_StartDateTime;
	bool Party_IsEnabled;

	// Lingua corrente
	int LanguageId;

	unsigned long PollingBase_TimerMilliseconds;
	unsigned long PollingDebugData_TimerMilliseconds;
	unsigned long UpdateRTC_TimerMilliseconds;

	bool FirstRunningTime;
	
	char DisableTX;
	byte DataTest[ 3 ];
	byte DataTestDebug0;

#if KTS_DEBUG == 1

	bool KTSDebug_ShowInfo;
	bool KTSDebug_SuspendTX;

	// Counter Messages
	unsigned long KTSDebug_MessageRXCount;
	unsigned long KTSDebug_MessageTXCount;
	unsigned long KTSDebug_MessageErrorLenCount;
	unsigned long KTSDebug_MessageErrorCRCCount;
	unsigned long KTSDebug_MessageErrorHeadCount;
	char KTSDebug_LastWriteEepromResult;
	unsigned long KTSDebug_ReadEepromCount;
	unsigned long KTSDebug_WriteEepromCount;
	unsigned long KTSDebug_WriteEepromOkCount;
	unsigned long KTSDebug_WriteEepromErrorCount;

#endif

	char ComLinkType; // BY_SERIAL_0 | BY_WIRELESS

	// RFM Data
	unsigned long RFMCheckChannel_TimerMilliseconds;
	byte RFMCheckChannel;	// CLRFMCheckChannel_OK = OK,
							// CLRFMCheckChannel_Busy = Channel occupied
	byte RFMCheckChannel_DifferenceDeviceIDPacketCount;

	// Indica il timer dell'ultima ricezione del polling
	unsigned long LastReceivedPollingBase_TimerMilliseconds;

};

enum CLRFMCheckChannel
{
	CLRFMCheckChannel_OK,
	CLRFMCheckChannel_Busy
};

// Funzioni del KTS
enum CLKTSProcessResult
{
	CLKTSProcessResult_Ok,
	CLKTSProcessResult_ScreenSaverExecuted
};

// Dati globali del KTS
extern CLKTSGlobal gKTSGlobal;

// Dati del polling base
extern CLKTSData gKTSData;

// Classe per l'accesso alla eeprom del KTS
extern CLKTSEeprom gKTSEeprom;

// Dati del polling debug data
extern CLKTSDebugData gKTSDebugData;

// Real Time Clock
extern Rtc_Pcf8563 gRTC;

// Dati della Eeprom dell'rd
extern S_EEPROM gRDEeprom;

#if KTS_DEBUG == 1

void KTSDebug_DisplayInfo();
void KTSDebug_DisplayDate( const char* title, CLDateTime dateTime );

#endif

#define MODELNAME_MAXLENGTH 4
#define MODEL_AIRFLOW_CALCULATE 0xFFFF
#define MODEL_PRESSURE_CALCULATE 0xFFFF

typedef struct _PACK SCLUnitModel
{
	char* Model; // char* Model
	unsigned short MaxAirFlow;
	unsigned short MaxPressure;
} CLUnitModel;

extern CLUnitModel gUnitModels[];

// Stato del KTS durante la connessione
// -----------------------------------------------------------------------------
enum CLKTSConnectState
{
	CLKTSConnectState_Init,
	CLKTSConnectState_LinkConnecting,
	CLKTSConnectState_TrySerialLink,
	CLKTSConnectState_TryRFMLink,
	CLKTSConnectState_LinkConnected,
	CLKTSConnectState_ReadEeprom_Info,
	CLKTSConnectState_ReadEeprom_Configuration,
	CLKTSConnectState_ReadEeprom_SettingPar,
	CLKTSConnectState_ReadEeprom_SetTemp,
	CLKTSConnectState_ReadEeprom_DayProg,
	CLKTSConnectState_ReadEeprom_HWSetting,
	CLKTSConnectState_PollingBase,
	CLKTSConnectState_Connected
};

enum CLKTSConnectOption
{
	CLKTSConnectOption_Default			= 0x00,
	CLKTSConnectOption_SkipSerialLink	= 0x01,
	CLKTSConnectOption_SkipRFMLink		= 0x02
};

// =============================================================================
// CLKTS [class]
// =============================================================================
// Description: KTS Functions
// -----------------------------------------------------------------------------
class CLKTS
{
	public: static void Initialize();
	
	public: static CLKTSConnectState Connect( void (*ktsConnectCallback)( CLKTSConnectState, int, int ),
		byte options );

	public: static CLKTSConnectState TryConnectSerialLink( void (*ktsConnectCallback)( CLKTSConnectState, int, int ),
		byte options );
	public: static CLKTSConnectState TryConnectRFMLink( void (*ktsConnectCallback)( CLKTSConnectState, int, int ),
		byte options );

	private: static int Connect_WaitResponse( ComQueue_Status* requestStatus,
		unsigned long& globalTimeoutMilliseconds,
		unsigned long timeoutMilliseconds );
	
	public: static CLKTSProcessResult Pir_Process();
    public: static CLKTSProcessResult Pir_Process1();
	public: static CLKTSProcessResult Process();
	public: static void AdjustDaylightSavingTime();

	private: static byte m_SaveRTCFirstRead;
	public: static bool Pir_Strategy;
	public: static long Pir_Strategy_Counter;
	private: static void _RTCRead( bool force );
	public: static void RTCRead();

	public: static void SetDateTime( CLDateTime& dateTime );
	public: static void SetLanguage( int languageId );

	public: static void Delay( unsigned long milliseconds );
	public: static CLFormResult ChangePassword( bool isService );

	public: static int GetCustomerId();

	public: static unsigned short AirFlow_GetMin();
	public: static unsigned short AirFlow_GetMax();

	public: static unsigned short Pressure_GetMin();
	public: static unsigned short Pressure_GetMax();
    public: static unsigned short Pressure_GetMax1();
	public: static unsigned short Pressure_GetMaxCalculated();
	public: static unsigned short Pressure_GetMaxCalibrated();
    public: static unsigned short Pressure_GetMaxCalibrated1();
	public: static bool Pressure_IsCalibrated();
    public: static bool Pressure_IsCalibrated1();

	public: static bool IsRunningBoost();
	public: static bool IsRunningImbalance();
	public: static bool IsRunningDefrost();

	public: static unsigned short CO2_GetMin();
	public: static unsigned short CO2_GetMax();

	public: static unsigned short RH_GetMin();
	public: static unsigned short RH_GetMax();

	public: static unsigned short VOC_GetMin();
	public: static unsigned short VOC_GetMax();

	public: static bool Write( CLVentilationControl ventilationControl,
		CLSpeedModeType speedMode,
		unsigned short* stepMotors,
		unsigned short idxStepMotors );
	public: static void Write_GetCurrentStepMotors( CLVentilationControl ventilationControl, 
		unsigned short* stepMotors, 
		byte startIndex, byte endIndex );
	public: static bool WriteStepless( CLVentilationControl ventilationControl,
		unsigned short defaultSteplessSpeed );
	public: static bool WriteThreeSpeed( CLVentilationControl ventilationControl,
		unsigned short* threeSpeeds,
		byte defaultIdxSpeed );

	#ifdef FRANCETX_ENABLED

	public: static bool WriteFranceTX( byte classIndex );

	#endif

	public: static bool WritePowerOn( unsigned short options, CLKTSPowerMode value );

	public: static void LevelLink_GetText( char* text, byte levelLink );
	public: static void UnitType_GetText( char* text );
	public: static void HWVers_GetText( char* text );
	public: static void SWVers_GetText( char* text );
	public: static void TypeFunc_GetText( char* text );

	public: static const char* GetSpeedMeasureUnit();

	public: static CLUnitModel* FindUnitModel( const char* modelName );
	public: static CLUnitModel* GetUnitModel();
	public: static void GetUnitModelName( char* modelName );
	public: static bool IsSerie3();

	public: static unsigned short GenerateDeviceID();
	public: static bool IsMissingRFMSignal();

	public: static void MillisToText( char* text, unsigned long milliseconds, bool includeHour );
	public: static unsigned long MillisDiff( unsigned long milliseconds1, unsigned long milliseconds2 );

	public: static int GetCodePage();

	public: inline static void SuspendScreenSaver()
	{
		gKTSGlobal.ScreenSaverSuspendCounter++;
	}

	public: inline static void ResumeScreenSaver()
	{
		if (gKTSGlobal.ScreenSaverSuspendCounter > 0)
		{
			gKTSGlobal.ScreenSaverSuspendCounter--;
			if (!gKTSGlobal.ScreenSaverSuspendCounter)
				gKTSGlobal.ScreenSaver_LastTouchedMilliseconds	= millis();
		}
	}

	public: inline static bool IsScreenSaverSuspended()
	{
		return gKTSGlobal.ScreenSaverSuspendCounter > 0;
	}
};
// -----------------------------------------------------------------------------
// CLKTS [class]
// =============================================================================



#endif

