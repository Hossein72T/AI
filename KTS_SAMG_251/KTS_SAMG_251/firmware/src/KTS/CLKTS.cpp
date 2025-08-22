#include "CLKTS.h"

#include "CLCommon.h"
#include "CLFranceTX.h"
#include "CLFunction.h"
#include "CLPasswordForm.h"
#include "CLWeekly.h"
#include "CLLCDCommon.h"
#include "CLFonts.h"
#include "CLLogo.h"
#include "CLScreenSaver.h"
#include "CLAccessory.h"
#include "CLCommunication_Driver.h"
#include "RFM73.h"
#include "CLKTSEeprom.h"
#include "CLSelectionLanguageForm.h"
#include "CLAlarm.h"
#include "RDAlarms.h"
#include "CLDateTime.h"

#ifdef _CLIKTS
#include "VS\KTS\CLIKTS\CLIKTS.h"
#endif

#define CUSTOMIZATION_DELIMITER ";"
#define EXPA(A) "alpha " A " gamma"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define CUSTOMIZATION_CODE "@[" \
	STR(CUSTOMERID) ";" \
	STR(LANGUAGE_PRIMARY) ";" \
	STR(LANGUAGE_SECONDARY) ";" \
	KTS_VERSION ";" \
	STR(KTS_DEMO) ";" \
	STR(KTS_SHOWFONTSFORM) ";" \
	STR(KTS_DEBUG) \
	"]@"

#pragma  whatever "Customization Code = " CUSTOMIZATION_CODE

#define ONE_MINUTE_MS (60UL * 1000UL) // 60 secondi in millisecondi (UL = Unsigned Long)
#define PIR_HIGH_LEVEL_EVENT 1000 // numero di eventi minimi in un minuto per tenere l'unità accesa
#define PIR_LEVEL            30 // livello del segnale PIR per cui considero effettiva la presenza di una persona (range: 1 - 33 )

// Contiene i dati in RAM (PollingBase)
CLKTSData gKTSData;

// Classe per l'accesso alla eeprom del KTS
CLKTSEeprom gKTSEeprom;

// Dati del polling debug data
CLKTSDebugData gKTSDebugData;

// Contiene le variabili globali
CLKTSGlobal gKTSGlobal;

// Contiene i dati della EPROM in RAM ----
S_EEPROM gRDEeprom;

// Accesso al Real Time Clock
Rtc_Pcf8563 gRTC;

// Accesso allo schermo LCD
TFTLCD gLCD( 39, 12, 40, 4 );

const unsigned long PollingBase_PowerOn_RFM_Milliseconds	= 1500;
const unsigned long PollingBase_PowerOn_Serial_Milliseconds	= 1100; // 1100
const unsigned long PollingBase_PowerOff_Milliseconds		= 5000;
const unsigned long PollingDebugData_Milliseconds			= 4800; // 4800

const char* BackdoorPassword = "88940";
const char* AdminPassword = "02015";
const char* FirmwareVersion = KTS_VERSION;

//char* gCustomizationCode = CUSTOMIZATION_CODE;

bool Debounce = false;
extern long seed1;
extern bool Clean_Event_Power_Off;

extern uint8_t CO2_1_Accuracy;
extern uint8_t CO2_2_Accuracy;

unsigned long pir_high_samples_in_minute = 0; // Contatore eventi 

CLUnitModel gUnitModels[] =
{
	{ (char*)"0025", 300, 200 },
	{ (char*)"0035", 400, 250 },
	{ (char*)"0045", 450, 350 },
	{ (char*)"0055", 550, 500 },
	{ NULL, 0 }
};

#if KTS_DEBUG == 1

void KTSDebug_DisplayDate( const char* title, CLDateTime dateTime )
{
	char	text[ 40 ];
	gLCD.setFont( SmallFont );
	gLCD.setRGBColor( RGBColor_White );
	sprintf( text, "%s: %d/%d/%d %d:%d.%d", title,
		dateTime.GetDay(),
		dateTime.GetMonth(),
		dateTime.GetYear(),
		dateTime.GetHour(),
		dateTime.GetMinute(),
		dateTime.GetSecond() );
	gLCD.print( text, 1, 60 );

	delay( 5000 );
}

void KTSDebug_DisplayText( char* text )
{
	CLGraphics::DrawText( 0, 0, CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Center,
		RGBColor_Black, RGBColor_White,
		text, 39 );

	CLKTS::Delay( 1000 );
}

void KTSDebug_DisplayInfo()
{
	if (gKTSGlobal.KTSDebug_ShowInfo)
	{
		char	text[ 60 ];

		sprintf( text, "RX=%d TX=%d EC=%d EL=%d EH=%d", gKTSGlobal.KTSDebug_MessageRXCount,
			gKTSGlobal.KTSDebug_MessageTXCount,
			gKTSGlobal.KTSDebug_MessageErrorCRCCount,
			gKTSGlobal.KTSDebug_MessageErrorLenCount,
			gKTSGlobal.KTSDebug_MessageErrorHeadCount );
		CLGraphics::DrawText( 0, 0, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
			RGBColor_Black, RGBColor_White,
			text, 40 );

		sprintf( text, "LWR=%c RE=%d WE=%d WEO=%d WEE=%d  ",
			gKTSGlobal.KTSDebug_LastWriteEepromResult,
			gKTSGlobal.KTSDebug_ReadEepromCount,
			gKTSGlobal.KTSDebug_WriteEepromCount,
			gKTSGlobal.KTSDebug_WriteEepromOkCount,
			gKTSGlobal.KTSDebug_WriteEepromErrorCount );
		CLGraphics::DrawText( 0, 14, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
			RGBColor_Black, RGBColor_White,
			text, 40 );

		sprintf( text, "T0=%4.1f T1=%4.1f T2=%4.1f T3=%4.1f",
			gKTSData.Measure_Temp[ 0 ],
			gKTSData.Measure_Temp[ 1 ],
			gKTSData.Measure_Temp[ 2 ],
			gKTSData.Measure_Temp[ 3 ] );
		CLGraphics::DrawText( 0, 226, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
			RGBColor_Black, RGBColor_White,
			text, 40 );

		sprintf( text, "SU=%d PIE=%d SI=%d", gKTSData.Status_Unit,
			(gKTSGlobal.Party_IsEnabled ? 1 : 0),
			(gKTSGlobal.KTSDebug_ShowInfo ? 1 : 0) );
		CLGraphics::DrawText( 0, 200, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
			RGBColor_Black, RGBColor_White,
			text, 40 );
	}
}

#endif

void KTS_PollingBaseResponse_Callback( byte* rxBuffer, void* userData )
{
	gKTSData.Measure_Temp[ 0 ]	= ((float) MAKESHORT( rxBuffer, IRSP_MEASURE_TEMP_1_HI, IRSP_MEASURE_TEMP_1_LO ) / 10.0);
	gKTSData.Measure_Temp[ 1 ]	= ((float) MAKESHORT( rxBuffer, IRSP_MEASURE_TEMP_2_HI, IRSP_MEASURE_TEMP_2_LO ) / 10.0);
	gKTSData.Measure_Temp[ 2 ]	= ((float) MAKESHORT( rxBuffer, IRSP_MEASURE_TEMP_3_HI, IRSP_MEASURE_TEMP_3_LO ) / 10.0);
	gKTSData.Measure_Temp[ 3 ]	= ((float) MAKESHORT( rxBuffer, IRSP_MEASURE_TEMP_4_HI, IRSP_MEASURE_TEMP_4_LO ) / 10.0);

	// Misura della sonda RH interna all'Unita'
	gKTSData.Measure_RH_max		= rxBuffer[ IRSP_MEASURE_RH_SENS ];

	// Misura della sonda CO2 interna all'Unita'
	gKTSData.Measure_CO2_max	= MAKEWORD( rxBuffer, IRSP_MEASURE_CO2_SENS_HI, IRSP_MEASURE_CO2_SENS_LO );

	// Misura della sonda VOC interna all'Unita'
	gKTSData.Measure_VOC_max	= MAKEWORD( rxBuffer, IRSP_MEASURE_VOC_SENS_HI, IRSP_MEASURE_VOC_SENS_LO );

	// Misura della sonda AWP
	gKTSData.Measure_Temp_AWP	= ((float) MAKESHORT( rxBuffer, IRSP_MEASURE_AWP_SENS_HI, IRSP_MEASURE_AWP_SENS_LO ) / 10.0);
	
	// Status
	gKTSData.Status_Unit		= MAKEWORD( rxBuffer, IRSP_STATUS_UNIT_HI, IRSP_STATUS_UNIT_LO );

	// Status Weekly
	gKTSData.Status_Weekly		= rxBuffer[ IRSP_STATUS_WEEKLY ];

	gKTSData.InputMeasure1		= rxBuffer[ IRSP_MEASURE_IN1 ];
	gKTSData.InputMeasure2		= rxBuffer[ IRSP_MEASURE_IN2 ];

	// Allarmi/ Eventi
	memcpy( gKTSData.Events, rxBuffer + IRSP_EVENT_BYTE_00, sizeof(gKTSData.Events) );

	// IncreaseSpeed RH/CO2
	gKTSData.IncreaseSpeed_RH_CO2	= rxBuffer[ IRSP_INCREASE_SPEED_RH_CO2 ];

	// Contatori sezioni EEPROM
	gKTSData.CntUpdate_info			= rxBuffer[ IRSP_CNT_UPDATE_EEP_INFO ];
	gKTSData.CntUpdate_SettingPar	= rxBuffer[ IRSP_CNT_UPDATE_EEP_SETTING_PAR ];
	gKTSData.CntUpdate_SetTemp		= rxBuffer[ IRSP_CNT_UPDATE_EEP_SETP_TEMP ];
	gKTSData.CntUpdate_dayProg		= rxBuffer[ IRSP_CNT_UPDATE_EEP_WEEKLY ];
	
	gKTSData.DSC_Status				= rxBuffer[ IRSP_NONE_0 ];
    
    CO2_1_Accuracy = rxBuffer[ IRSD_ACCURACY_CO2_1 ] & 3;
    CO2_2_Accuracy = rxBuffer[ IRSD_ACCURACY_CO2_2 ] & 3;       

	// Se i contatori delle sezioni della Eeprom sono diversi mette in coda la richiesta di lettura dei dati Eeprom
    // Si les compteurs des sections Eeprom sont différents, il met en file d'attente la demande de lecture des données Eeprom

	if(gKTSGlobal.DisableTX != 'D')
	{	
		if (gKTSData.CntUpdate_info != gRDEeprom.cntUpdate_info)
			KTS_QueueReadEepromRequest( EEepromSection_Info, NULL );

		if (gKTSData.CntUpdate_SettingPar != gRDEeprom.cntUpdate_SettingPar)
			KTS_QueueReadEepromRequest( EEepromSection_SettingPar, NULL );

		if (gKTSData.CntUpdate_SetTemp != gRDEeprom.cntUpdate_SetTemp)
			KTS_QueueReadEepromRequest( EEepromSection_SetTemp, NULL );

		if (gKTSData.CntUpdate_dayProg != gRDEeprom.cntUpdate_dayProg)
			KTS_QueueReadEepromRequest( EEepromSection_DayProg, NULL );
	}

	// Controlla se esistono degli Allarmi attivi ed imposta le variabili di ambiente
	gKTSGlobal.InAlarm			= false;
	gKTSGlobal.FilterInAlarm	= false;
	for (int eventsCounter = 0; eventsCounter < EVENT_COUNT; eventsCounter++)
	{
		if (gKTSData.Events[ eventsCounter ])
		{
			if (eventsCounter == 10)
			{
				gKTSGlobal.FilterInAlarm	= gKTSData.Events[ eventsCounter ] & 0x20;
				if (gKTSData.Events[ eventsCounter ] != 0x20)
					gKTSGlobal.InAlarm	= true;
			}
			else
				gKTSGlobal.InAlarm	= true;
		}
	}

	// Se sono in RFM e il canale rfm Ã¨ occupato, segnalo l'alert
	if (!gKTSGlobal.InAlarm &&
		gKTSGlobal.ComLinkType == BY_WIRELESS &&
		gKTSGlobal.RFMCheckChannel == CLRFMCheckChannel_Busy)
	{
		gKTSGlobal.InAlarm	= true;
	}

	// Aggiorna il Party Mode
	//----------------------------------------------
	if (Function_IsEnabled( ENAB_BOOST ) &&
		CLKTS::IsRunningBoost() && !gKTSGlobal.Party_IsEnabled)
	{
		gKTSGlobal.Party_IsEnabled		= true;
		gKTSGlobal.Party_StartDateTime	= CLDateTime::GetNow();
	}
	else
	if (!CLKTS::IsRunningBoost() && gKTSGlobal.Party_IsEnabled)
	{
		gKTSGlobal.Party_IsEnabled		= false;
	}

	// Aggiorna il timer dell'ultimo polling ricevuto
	gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds	= millis();
}

void KTS_DebugDataResponse_Callback( byte* rxBuffer, void* userData )
{
	gKTSDebugData.PreHeater_Status	= rxBuffer[ IRSD_STATUS_PREHEATER ];
	gKTSDebugData.Heater_Status		= rxBuffer[ IRSD_STATUS_HEATER ];
	gKTSDebugData.Cooler_Status		= rxBuffer[ IRSD_STATUS_COOLER ];
	gKTSDebugData.Dsc_Status		= rxBuffer[ IRSD_STATUS_DSC ];
}

void KTS_ReadEepromResponse_Callback( byte* rxBuffer, void* userData )
{
    ComQueue_Status	writeEeprom_Status;
    
	memcpy( ((byte*) &gRDEeprom) + sRxBuffer[ IRSR_ADDR_BYTE_START_EEP ],
		((byte*) sRxBuffer) + IRSR_START_DATA_EEPROM,
		sRxBuffer[ IRSR_ADDR_NUM_BYTE_EEP ] );
    
    /*if ( gRDEeprom.KTS_Watchdog == 1 ) // need to change to 0 within 60 seconds
    {
        gRDEeprom.KTS_Watchdog = 0;
        // Accoda la richiesta di WriteEeprom
        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, KTS_Watchdog ), sizeof(gRDEeprom.KTS_Watchdog), &writeEeprom_Status );
        
        gRDEeprom.cntUpdate_info += 1;
        // Accoda la richiesta di WriteEeprom
        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, cntUpdate_info ), sizeof(gRDEeprom.cntUpdate_info), &writeEeprom_Status );
    }*/
}

void KTS_WriteEepromResponse_Callback( byte* rxBuffer, void* userData )
{
	// Controlla che se il counter update INFO e' maggiore di 1, richiede la rilettura della eeprom
	if (MAX( sRxBuffer[ IRSW_CNT_UPDATE_EEP_INFO ], gRDEeprom.cntUpdate_info ) -
		MIN( sRxBuffer[ IRSW_CNT_UPDATE_EEP_INFO ], gRDEeprom.cntUpdate_info ) > 1)
	{
		KTS_QueueReadEepromRequest( EEepromSection_Info, NULL );
	}
	gRDEeprom.cntUpdate_info	= sRxBuffer[ IRSW_CNT_UPDATE_EEP_INFO ];

	// Controlla che se il counter update SETTING_PAR e' maggiore di 1, richiede la rilettura della eeprom
	if (MAX( sRxBuffer[ IRSW_CNT_UPDATE_EEP_SETTING_PAR ], gRDEeprom.cntUpdate_SettingPar ) -
		MIN( sRxBuffer[ IRSW_CNT_UPDATE_EEP_SETTING_PAR ], gRDEeprom.cntUpdate_SettingPar ) > 1)
	{
		KTS_QueueReadEepromRequest( EEepromSection_SettingPar, NULL );
	}
	gRDEeprom.cntUpdate_SettingPar	= sRxBuffer[ IRSW_CNT_UPDATE_EEP_SETTING_PAR ];
				
	// Controlla che se il counter update SETP_TEMP e' maggiore di 1, richiede la rilettura della eeprom
	if (MAX( sRxBuffer[ IRSP_CNT_UPDATE_EEP_SETP_TEMP ], gRDEeprom.cntUpdate_SetTemp ) -
		MIN( sRxBuffer[ IRSP_CNT_UPDATE_EEP_SETP_TEMP ], gRDEeprom.cntUpdate_SetTemp ) > 1)
	{
		KTS_QueueReadEepromRequest( EEepromSection_SetTemp, NULL );
	}
	gRDEeprom.cntUpdate_SetTemp	= sRxBuffer[ IRSP_CNT_UPDATE_EEP_SETP_TEMP ];
				
	// Controlla che se il counter update WEEKLY e' maggiore di 1, richiede la rilettura della eeprom
	if (MAX( sRxBuffer[ IRSP_CNT_UPDATE_EEP_WEEKLY ], gRDEeprom.cntUpdate_dayProg ) -
		MIN( sRxBuffer[ IRSP_CNT_UPDATE_EEP_WEEKLY ], gRDEeprom.cntUpdate_dayProg ) > 1)
	{
		KTS_QueueReadEepromRequest( EEepromSection_SetTemp, NULL );
	}
	gRDEeprom.cntUpdate_dayProg	= sRxBuffer[ IRSP_CNT_UPDATE_EEP_WEEKLY ];
}

void KTS_ComReceiveMessageHandler( byte* rxBuffer, unsigned short deviceId )
{
	if (gKTSGlobal.ComLinkType == BY_WIRELESS &&
		deviceId != gKTSEeprom.GetDeviceID() &&
		gKTSGlobal.RFMCheckChannel_DifferenceDeviceIDPacketCount < 255)
	{
		gKTSGlobal.RFMCheckChannel_DifferenceDeviceIDPacketCount++;
	}
}

// =============================================================================
// CLKTS [class]
// -----------------------------------------------------------------------------
byte CLKTS::m_SaveRTCFirstRead;
bool CLKTS::Pir_Strategy;
long CLKTS::Pir_Strategy_Counter;

void CLKTS::Initialize()
{
	m_SaveRTCFirstRead	= 1;
	Pir_Strategy = false;
	Pir_Strategy_Counter = 0;

	// Allarmi
	gKTSGlobal.InAlarm			= false;
	gKTSGlobal.FilterInAlarm	= false;

	// Initializing
	gKTSGlobal.RunningMode	= CLKTSRunningMode_Initializing;

	gKTSDebugData.PreHeater_Status	= 0;
	gKTSDebugData.Heater_Status		= 0;
	gKTSDebugData.Cooler_Status		= 0;
	gKTSDebugData.Dsc_Status		= 0;

	// ScreenSaver
	gKTSGlobal.ScreenSaverActive					= false;
	gKTSGlobal.ScreenSaver_LastTouchedMilliseconds	= millis();
	gKTSGlobal.ScreenSaverSuspendCounter			= 0;

	// Touch
	gKTSGlobal.LastTouchedMilliseconds		= millis();

	// Inizializza i dati del Party
	gKTSGlobal.Party_StartDateTime.Set( 1, 1, 0, 0, 0, 0 );
	gKTSGlobal.Party_IsEnabled	= false;
	
	gKTSGlobal.FirstRunningTime	= gKTSEeprom.GetFirstTime();

	// Test Unit
	gKTSGlobal.DisableTX = 0;
	memset( gKTSGlobal.DataTest, /*NULL*/ 0, sizeof(gKTSGlobal.DataTest) );

	gKTSGlobal.UpdateRTC_TimerMilliseconds	= millis();

	// Imposta la lingua
	gKTSGlobal.LanguageId	= gKTSEeprom.GetLanguage();

	CLLocalitation::SetPrimaryLanguage( gKTSGlobal.LanguageId );
	CLLocalitation::SetSecondaryLanguage( LANGUAGE_SECONDARY );

#if KTS_DEBUG == 1
	gKTSGlobal.KTSDebug_MessageRXCount			= 0;
	gKTSGlobal.KTSDebug_MessageTXCount			= 0;
	gKTSGlobal.KTSDebug_MessageErrorCRCCount	= 0;
	gKTSGlobal.KTSDebug_MessageErrorHeadCount	= 0;
	gKTSGlobal.KTSDebug_MessageErrorLenCount	= 0;

	gKTSGlobal.KTSDebug_LastWriteEepromResult	= ' ';
	gKTSGlobal.KTSDebug_ReadEepromCount			= 0;
	gKTSGlobal.KTSDebug_WriteEepromCount		= 0;
	gKTSGlobal.KTSDebug_WriteEepromOkCount		= 0;
	gKTSGlobal.KTSDebug_WriteEepromErrorCount	= 0;
	gKTSGlobal.KTSDebug_ShowInfo				= false;
	gKTSGlobal.KTSDebug_SuspendTX				= false;
#endif

	gKTSGlobal.PollingBase_TimerMilliseconds		= millis();
	gKTSGlobal.PollingDebugData_TimerMilliseconds	= gKTSGlobal.PollingBase_TimerMilliseconds;

#if KTS_DEMO == 1

	// Imposta il tipo di KTS a DEMO
	gRDEeprom.Type_func	= CLKTSType_DEMO;

	gRDEeprom.msk_Enab_Fuction	= 0xFFFF;

	// Abilita CAF + stepless
	Function_SetEnabled( ENAB_CAF, true );
	Function_SetEnabled( ENAB_STEPLESS, true );

	for (int accessoriesCounter = 0; accessoriesCounter < AccessoryCount; accessoriesCounter++)
	{
		if (AccessoryNames[ accessoriesCounter ] != NULL)
			Accessory_Set( accessoriesCounter, true );
	}

	// Imposta le velocitÃ  FSC/CAF di default
	SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 0, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAF ) * 0.30) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 1, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAF ) * 0.60) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 2, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAF ) * 0.70) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 3, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAF )) );

	// Imposta le velocitÃ  CAP di default
	SpeedMode_Speed_SetValue( CLVentilationControl_CAP, 0, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAP ) * 0.30) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAP, 1, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAP ) * 0.60) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAP, 2, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAP ) * 0.70) );
	SpeedMode_Speed_SetValue( CLVentilationControl_CAP, 3, (unsigned short) ((float) SpeedMode_Stepless_GetMaxValue( CLVentilationControl_CAP )) );

	// Imposta le password di service (12345)
	gRDEeprom.servicePassword[ 0 ]	= '1';
	gRDEeprom.servicePassword[ 1 ]	= '2';
	gRDEeprom.servicePassword[ 2 ]	= '3';
	gRDEeprom.servicePassword[ 3 ]	= '4';
	gRDEeprom.servicePassword[ 4 ]	= '5';

	// Imposta le password di user (00000)
	memset( gRDEeprom.endUserPassword, '0', sizeof(gRDEeprom.endUserPassword) );

#endif

	// Inizialmente imposta la seriale come mezzo di comunicazione
	gKTSGlobal.ComLinkType										= BY_SERIAL_0;
	gComReceiveMessageHandler									= KTS_ComReceiveMessageHandler;
	gKTSGlobal.RFMCheckChannel									= CLRFMCheckChannel_OK;
	gKTSGlobal.RFMCheckChannel_DifferenceDeviceIDPacketCount	= 0;
	gKTSGlobal.RFMCheckChannel_TimerMilliseconds				= 0;

	gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds		= 0;
}

int CLKTS::Connect_WaitResponse( ComQueue_Status* requestStatus,
	unsigned long& globalTimeoutMilliseconds,
	unsigned long timeoutMilliseconds )
{
	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING((*requestStatus)))
	{
		if ((millis() - globalTimeoutMilliseconds >= timeoutMilliseconds ||
			millis() < globalTimeoutMilliseconds))
		{
			return -2;
		}

		CLKTS::Process();
		CLKTS::Pir_Process();
	}

	if (requestStatus->Status == COM_REQUEST_STATUS_COMPLETED)
	{
		Delay( 100 );
		return 0;
	}

	return -1;
}

CLKTSConnectState CLKTS::Connect( void (*ktsConnectCallback)( CLKTSConnectState, int, int ),
	byte options )
{
	const unsigned long	TimeoutMilliseconds			= 15000;
	CLKTSConnectState	currentState				= CLKTSConnectState_Init;
	unsigned long		globalTimeoutMilliseconds	= millis();
	char				currentCommand				= COMMAND_EMPTY;
	int					step						= 0;
	char				text[ 40 ];
	ComQueue_Status		requestStatus;
	int					stepCount					= 9;
	
#if KTS_DEMO == 1

	//analogWrite( pBACKLIGHT, HIGH_BRIGHTESS );
    TC0_CH1_CompareASet (HIGH_BRIGHTESS);
	gLCD.setColor( 255, 255, 255 );

	for (int i=0; i < 10; i++)
	{
		gLCD.setColor( 0, 0, 0 );
		gLCD.fillRect( 0, 80, 240, 140 );
		gLCD.setColor( 200, 200, 0 ); // giallo ocra
		gLCD.print( "DEMO VERSION", (5*i), 100);
		delay( 500 );
	}

#else

	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	step	= 1;
	bool	foundComLink	= false;
	bool	requestOk		= false;

	// Link Connecting
	currentState	= CLKTSConnectState_LinkConnecting;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	// STEP: Try Serial Link Connection
	// ---------------------------------------
	if (!(options & CLKTSConnectOption_SkipSerialLink))
	{
		currentState			= CLKTSConnectState_TrySerialLink;
		gKTSGlobal.ComLinkType	= BY_SERIAL_0;
		
		if (ktsConnectCallback)
			ktsConnectCallback( currentState, step, stepCount );

		for (int retriesCounter = 0; retriesCounter < 2 && !foundComLink; retriesCounter++)
		{
			// Accoda Request
			ComQueue_AddPollingBaseRequest( &requestStatus, NULL );
			switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
			{
				// Ok, next step
				case 0:		foundComLink = true; break;
				// Request timeout
				case -1:	break;
				// Global timeout
				default:	return currentState;
			}
			Delay( 200 );
		}
	}
	step++;

	// STEP: Try RFM Connection
	// ---------------------------------------
	if (!foundComLink &&
		sdata_wi.install_rfm == 1 &&
		!(options & CLKTSConnectOption_SkipRFMLink))
	{
		currentState			= CLKTSConnectState_TryRFMLink;
		gKTSGlobal.ComLinkType	= BY_WIRELESS;
		
		if (ktsConnectCallback)
			ktsConnectCallback( currentState, step, stepCount );

		for (int retriesCounter = 0; retriesCounter < 5 && !foundComLink; retriesCounter++)
		{
			// Accoda Request
			ComQueue_AddAssignId( &requestStatus, NULL );
			switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
			{
				// Ok, next step
				case 0:		foundComLink = true; break;
				// Request timeout
				case -1:	break;
				// Global timeout
				default:	return currentState;
			}
			Delay( 200 );
		}
	}
	step++;

	if (!foundComLink)
		return currentState;

	// Link Connected
	currentState			= CLKTSConnectState_LinkConnected;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	// STEP: ReadEeprom Info
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_Info;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_Info, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom Configuration
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_Configuration;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_Configuration, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom SettingPar
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_SettingPar;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_SettingPar, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom SetTemp
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_SetTemp;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_SetTemp, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom DayProg
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_DayProg;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_DayProg, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom HWSetting
	// ---------------------------------------
	currentState	= CLKTSConnectState_ReadEeprom_HWSetting;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		KTS_QueueReadEepromRequest( EEepromSection_HWSetting, &requestStatus );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// STEP: ReadEeprom PollingBase
	// ---------------------------------------
	currentState	= CLKTSConnectState_PollingBase;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

	requestOk	= false;
	while (!requestOk)
	{
		// Accoda Request
		ComQueue_AddPollingBaseRequest( &requestStatus, NULL );
		switch (Connect_WaitResponse( &requestStatus, globalTimeoutMilliseconds, TimeoutMilliseconds ))
		{
			// Ok, next step
			case 0:		requestOk = true; break;
			// Request timeout
			case -1:	continue;
			// Global timeout
			default:	return currentState;
		}
	}
	Delay( 100 );
	step++;

	// Connected
	currentState			= CLKTSConnectState_Connected;
	if (ktsConnectCallback)
		ktsConnectCallback( currentState, step, stepCount );

#endif

	// OK KTS connesso, imposta alcune variabili

	// Imposta la tabella dei nomi accessory
	if (CLKTS::IsSerie3())
		AccessoryNames[ ACC_EEP_PEHD ]	= CLFixedText_PHED;

	#ifdef _CLIKTS
	Climalombarda::KTS::CLIKTS::RaiseInitialized();
	gKTSEeprom.ReadEeprom();
	gKTSGlobal.FirstRunningTime	= gKTSEeprom.GetFirstTime();
	CLKTS::SetLanguage( gKTSEeprom.GetLanguage() );
	#endif

	if (gKTSGlobal.FirstRunningTime)
	{
		// Imposta il linguaggio
		CLSelectionLanguageForm_Open( CLFormOption_GoHomeAfterWrite | CLFormOption_HideButton_Back | CLFormOption_HideButton_Home );

		// Imposta la data e ora
		if(gRDEeprom.Type_func != CLKTSType_BASIC)
			Procedure_Execute( CLProcedureId_SystemDateTimeConfigForm, CLFormOption_GoHomeAfterWrite | CLFormOption_HideButton_Back | CLFormOption_HideButton_Home );

		gKTSGlobal.FirstRunningTime	= false;
		gKTSEeprom.SetFirstTime( false );
	}

	// Imposta lo stato del KTS
	// L'unitÃ  Ã¨ in fire alarm o richiede un riarmo
	if (IsFireAlarm() || gRDEeprom.manual_Reset)
		gKTSGlobal.RunningMode	= CLKTSRunningMode_FireAlarm;
	else
	// L'unitÃ  Ã¨ in Power Off
	if (gRDEeprom.Set_Power_ON == CLKTSPowerMode_Off)
		gKTSGlobal.RunningMode	= CLKTSRunningMode_PowerOff;
	// L'unitÃ  Ã¨ in Power On
	else
		gKTSGlobal.RunningMode	= CLKTSRunningMode_Running;

	gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds	= millis();

	return CLKTSConnectState_Connected;
}

		
void CLKTS::Delay( unsigned long milliseconds )
{
	unsigned long	previousMilliseconds	= millis();

	while (millis() - previousMilliseconds < milliseconds)
	{
		CLKTS::Process();
		CLKTS::Pir_Process();
	}
}

CLFormResult CLKTS::ChangePassword( bool isService )
{
	byte			newPassword[ 5 ];
	byte*			currentPassword	= (isService ? gRDEeprom.servicePassword : gRDEeprom.endUserPassword);
	CLFormResult	formResult;

	formResult	= CLPasswordForm_ChangeOpen( (char*) currentPassword, (char*) newPassword, 
		(isService ? CLLocalitation::GetText( CLTextId_CHANGE_SERVICE_PASSWORD ) : CLLocalitation::GetText( CLTextId_CHANGE_END_USER_PASSWORD )),
		CLFormOption_Default );

	if (formResult == CLFormResult_Ok)
	{
		ComQueue_Status	writeEeprom_Status;
		byte			savePassword[ 5 ];

		// Salva i valori correnti
		memcpy( savePassword, currentPassword, 5 );

		// Imposta i nuovi valori
		memcpy( currentPassword, newPassword, 5 );

		if (isService)
		{
			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, servicePassword ),
				sizeof(gRDEeprom.servicePassword),
				&writeEeprom_Status );
		}
		else
		{
			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, endUserPassword ),
				sizeof(gRDEeprom.endUserPassword),
				&writeEeprom_Status );
		}

		// Aspetta l'elaborazione della richiesta
		while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
			CLKTS::Process();
		
		CLKTS::Pir_Process();
		
		// Se non e' andata a buon fine, message + home
		if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
		{
			// Rispristina valore precedente
			memcpy( currentPassword, savePassword, 5 );

			formResult	= CLFormResult_Cancel;
		}
		else
			formResult	= CLFormResult_Ok;

		return formResult;
	}
    
    return formResult;
}

CLKTSProcessResult CLKTS::Pir_Process1()
{
    if ( gRDEeprom.Set_Input[ 0 ] == INP_0V_UNIT_STOP )
		{
			CLKTS::Pir_Strategy = true;
		}
	else
		{
			CLKTS::Pir_Strategy = false;
		}
    if ( CLKTS::Pir_Strategy )
	{
        if ( gKTSGlobal.RunningMode	== CLKTSRunningMode_PowerOff )
            {
                if ( (gKTSData.Status_Unit & 0x8000 ) == 0x8000 )
                    {
                        if ( !Debounce )
                        {   
                            //KTS_QueueReadEepromRequest( EEepromSection_SettingPar, NULL );
                            CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_On);
                            CLKTS::Pir_Strategy_Counter = millis();
                        }
                    }
                else
                    {
                        Debounce = false;
                        CLKTS::Pir_Strategy_Counter = millis();
                    }
            }
    }
    
    return CLKTSProcessResult_Ok;
}

CLKTSProcessResult CLKTS::Pir_Process()
{
	// Determina se la strategia PIR è attiva (invariato)
	if ( gRDEeprom.Set_Input[ 0 ] == INP_0V_UNIT_STOP ) {
		CLKTS::Pir_Strategy = true;
	} else {
		CLKTS::Pir_Strategy = false;
	}

	if ( CLKTS::Pir_Strategy )
	{
		if ( gKTSGlobal.RunningMode == CLKTSRunningMode_Running )
		{
            // --- LOGICA CON CONTEGGIO SU MINUTO ---
            // Incrementa il contatore se il segnale è "alto" (> 20)
            if ( (int) gKTSData.InputMeasure1 > PIR_LEVEL )
            {
                pir_high_samples_in_minute++;
            }

            // Controlla se è passato un minuto
            if ((( millis() - CLKTS::Pir_Strategy_Counter) >= gRDEeprom.Pir_Update_Delay * 60 * 1000 ) || (millis() < CLKTS::Pir_Strategy_Counter))
            {
                // Un minuto è trascorso, verifica il conteggio
                //bool stay_on = (pir_high_samples_in_minute > (PIR_HIGH_LEVEL_EVENT * gRDEeprom.Pir_Update_Delay) );
                
                // Mi spengo a prescrindere
                bool stay_on = false;

                if ( !stay_on ) // Meno di 21 eventi alti nel minuto -> Spegni
                {
                    if (!Debounce) // Invia comando solo se non già inviato
                    {
                        CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_Off);
                        pir_high_samples_in_minute = 0;
                        CLKTS::Pir_Strategy_Counter = millis();
                        Debounce = true; // Attiva debounce per evitare comandi ripetuti
                    }
                }
                else // Più di 20 eventi alti nel minuto -> Resta acceso
                {
                     // Assicurati che il Debounce sia disattivato per permettere
                     // un eventuale spegnimento nel minuto successivo
                     Debounce = false;
                }

                // --- Azzera il contatore e riavvia il timer per il prossimo minuto ---
                CLKTS::Pir_Strategy_Counter = millis(); // Riavvia il timer del minuto
                pir_high_samples_in_minute = 0;        // Azzera il contatore eventi alti
            }
            // --- FINE LOGICA MINUTO ---
		}
        else if ( gKTSGlobal.RunningMode == CLKTSRunningMode_PowerOff )

            {
                    if ( (gKTSData.Status_Unit & 0x8000 ) == 0x8000 )
                    {
                     if ( !Debounce )
                        {
                            //KTS_QueueReadEepromRequest( EEepromSection_SettingPar, NULL );
                            CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_On);
                            CLKTS::Pir_Strategy_Counter = millis();
                            pir_high_samples_in_minute = 0;
                         }
                       }
                    else
                        {
                            Debounce = false;
                            CLKTS::Pir_Strategy_Counter = millis();
                            pir_high_samples_in_minute = 0;
                        }
             }

    }

    // Logica Clean Event (invariata)
    if ( (gKTSData.Status_Unit & 0x4000 ) == 0x0 ) // CleanEvent desactivated
    {
        if ( Clean_Event_Power_Off ) // previous state device OFF
        {
             Clean_Event_Power_Off = false;
             CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_Off); // turn Device OFF
        }
    }

	return CLKTSProcessResult_Ok;
}

CLKTSProcessResult CLKTS::Process()
{
#ifdef _CLIKTS
	delay( 20 );
#endif
	// RFM Loop
	management_message_wi( millis() );

	// Processa la coda della seriale
	ComQueue_Process();
	
	if (gRDEeprom.Set_Power_ON == CLKTSPowerMode_Off &&
		gKTSGlobal.RunningMode != CLKTSRunningMode_Initializing)
		gKTSGlobal.RunningMode	= CLKTSRunningMode_PowerOff;

#if KTS_DEBUG == 1

	if (!gKTSGlobal.KTSDebug_SuspendTX) || 
	{
#else
    if(gKTSGlobal.DisableTX != 'D')
	{
#endif

#if KTS_DEMO == 0

	if (millis() < gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds)
		gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds	= millis();

	// Aggiorna lo stato channel RFM busy
	if (sdata_wi.install_rfm &&
		(millis() - gKTSGlobal.RFMCheckChannel_TimerMilliseconds >= 7000 ||
		millis() < gKTSGlobal.RFMCheckChannel_TimerMilliseconds))
	{
		if (gKTSGlobal.RFMCheckChannel_DifferenceDeviceIDPacketCount > 0)
		{
			gKTSGlobal.RFMCheckChannel									= CLRFMCheckChannel_Busy;
			gKTSGlobal.RFMCheckChannel_DifferenceDeviceIDPacketCount	= 0;
		}
		else
			gKTSGlobal.RFMCheckChannel	= CLRFMCheckChannel_OK;

		gKTSGlobal.RFMCheckChannel_TimerMilliseconds	= millis();
	}

	if (gKTSGlobal.RunningMode == CLKTSRunningMode_PowerOff ||
		gKTSGlobal.RunningMode == CLKTSRunningMode_Running ||
		gKTSGlobal.RunningMode == CLKTSRunningMode_FireAlarm)
	{
		// Aggiunge la richiesta del PollingBase, se si supera il timer e se non esiste in coda
		if (millis() - gKTSGlobal.PollingBase_TimerMilliseconds >=
			(gKTSGlobal.RunningMode == CLKTSRunningMode_PowerOff ? PollingBase_PowerOff_Milliseconds :
			(gKTSGlobal.ComLinkType == BY_WIRELESS ? PollingBase_PowerOn_RFM_Milliseconds : PollingBase_PowerOn_Serial_Milliseconds)) ||
			millis() < gKTSGlobal.PollingBase_TimerMilliseconds)
		{
			if (ComQueue_ContainsCommand( COMMAND_POLLING_BASE, KTS_PollingBaseResponse_Callback ) == -1)
				ComQueue_AddPollingBaseRequest( NULL, KTS_PollingBaseResponse_Callback );

			gKTSGlobal.PollingBase_TimerMilliseconds	= millis();
		}
	}

	if (gKTSGlobal.RunningMode == CLKTSRunningMode_Running)
	{
		// Aggiunge la richiesta del DebugData, se si supera il timer
		if (millis() - gKTSGlobal.PollingDebugData_TimerMilliseconds >= PollingDebugData_Milliseconds ||
			millis() < gKTSGlobal.PollingDebugData_TimerMilliseconds)
		{
			if (ComQueue_ContainsCommand( COMMAND_DATA_DEBUG, KTS_DebugDataResponse_Callback ) == -1)
				ComQueue_AddDataDebugRequest( NULL, KTS_DebugDataResponse_Callback );

			gKTSGlobal.PollingDebugData_TimerMilliseconds	= millis();
            gKTSGlobal.PollingBase_TimerMilliseconds	= millis();
		}
	}

#endif
	if (!IsScreenSaverSuspended()
		&& ScreenSaver_Process() == CLScreenSaverProcessResult_ScreenSaverExecuted)
		return CLKTSProcessResult_ScreenSaverExecuted;

	}

	// Controlla e aggiusta l'ora legale
	if (millis() - gKTSGlobal.UpdateRTC_TimerMilliseconds >= 1000 ||
		millis() < gKTSGlobal.UpdateRTC_TimerMilliseconds)
	{
		CLKTS:RTCRead();
		CLKTS::AdjustDaylightSavingTime();

		gKTSGlobal.UpdateRTC_TimerMilliseconds	= millis();
	}

#if KTS_DEBUG == 1

	KTSDebug_DisplayInfo();
#endif

	return CLKTSProcessResult_Ok;
}

bool CLKTS::Pressure_IsCalibrated()
{
	return gRDEeprom.calibra_CAP > 0
		&& gRDEeprom.calibra_CAP < 2000;
}

bool CLKTS::Pressure_IsCalibrated1()
{
	return gRDEeprom.calibra_CAP1 > 0
		&& gRDEeprom.calibra_CAP1 < 2000;
}

unsigned short CLKTS::Pressure_GetMin()
{
	return 30;
}

unsigned short CLKTS::Pressure_GetMaxCalculated()
{
	CLUnitModel*	unitModel;
	short			maxAirFlow;

	// Lookup tabella dei models
	unitModel	= CLKTS::GetUnitModel();
	if (unitModel != NULL && unitModel->MaxPressure != MODEL_PRESSURE_CALCULATE)
		return unitModel->MaxPressure;

	// Unit Model non codificata, esegue calcolo
	maxAirFlow	= CLKTS::AirFlow_GetMax();
	if (maxAirFlow > 1200)
		return 450;

	if (maxAirFlow > 200)
		return 350;

	return 250;
}

unsigned short CLKTS::Pressure_GetMaxCalibrated()
{
	return gRDEeprom.calibra_CAP;
}

unsigned short CLKTS::Pressure_GetMaxCalibrated1()
{
	return gRDEeprom.calibra_CAP1;
}

unsigned short CLKTS::Pressure_GetMax()
{
	if (Pressure_IsCalibrated())
		return Pressure_GetMaxCalibrated();

	return Pressure_GetMaxCalculated();
}

unsigned short CLKTS::Pressure_GetMax1()
{
	if (Pressure_IsCalibrated1())
		return Pressure_GetMaxCalibrated1();

	return Pressure_GetMaxCalculated();
}

unsigned short CLKTS::VOC_GetMin()
{
	return 8;
}

unsigned short CLKTS::VOC_GetMax()
{
	return 100;
}

unsigned short CLKTS::CO2_GetMin()
{
	return 600;
}

unsigned short CLKTS::CO2_GetMax()
{
	return 1500;
}

unsigned short CLKTS::RH_GetMin()
{
	return 2;
}

unsigned short CLKTS::RH_GetMax()
{
	return 99;
}

bool CLKTS::IsRunningBoost()
{
	return (KTSStatusUnit_UnitState_IsRUN_BOOST( gKTSData.Status_Unit ) ? true : false);
}

bool CLKTS::IsRunningImbalance()
{
	return (KTSStatusUnit_UnitState_IsRUN_IMBALANCE( gKTSData.Status_Unit ) ? true : false);
}

bool CLKTS::IsRunningDefrost()
{
	return (KTSStatusUnit_UnitState_IsRUN_DEFROST( gKTSData.Status_Unit ) ? true : false);
}

int CLKTS::GetCustomerId()
{
	return CUSTOMERID;
}

void CLKTS::LevelLink_GetText( char* text, byte levelLink )
{
	sprintf( text, "%2d/10", levelLink );
}

void CLKTS::UnitType_GetText( char* text )
{
	char	layoutText[ 5 ];
	char	configurationText[ 3 ];
	char	modelNumberText[ 4 ];

	*text	= '\0';

	sprintf( modelNumberText, "%c%c%c",
		gRDEeprom.SerialString[ 5 ],
		gRDEeprom.SerialString[ 6 ],
		gRDEeprom.SerialString[ 7 ] );

	switch (gRDEeprom.SerialString[ 8 ])
	{
		case '0':
			strcpy( layoutText, "OSC" );
			break;
		case '1':
			strcpy( layoutText, "SSC" );
			break;
		case '2':
			strcpy( layoutText, "EOS" );
			break;
		case '3':
			strcpy( layoutText, "FOS" );
			break;
		default:
			*layoutText	= '\0';
			break;
	}

	switch (gRDEeprom.SerialString[ 9 ])
	{
		case '1':
			sprintf( configurationText, "A%c", gRDEeprom.SerialString[ 10 ] );
			break;
		case '2':
			sprintf( configurationText, "B%c", gRDEeprom.SerialString[ 10 ] );
			break;
		case '3':
			sprintf( configurationText, "C%c", gRDEeprom.SerialString[ 10 ] );
			break;
		case '4':
			sprintf( configurationText, "D%c", gRDEeprom.SerialString[ 10 ] );
			break;
		default:
			*configurationText	= '\0';
			break;
	}

#if CUSTOMERID == CUSTOMERID_CL

	if (gRDEeprom.SerialString[ 7 ] == '5')
	{
		sprintf( text, "QUANTUM %s %s %s",
			modelNumberText,
			layoutText,
			configurationText );
	}
	else
	if (gRDEeprom.SerialString[ 7 ] == '3')
	{
		sprintf( text, "CLRC %s %s %s",
			modelNumberText,
			layoutText,
			configurationText );
	}

#elif CUSTOMERID == CUSTOMERID_AV

	if (gRDEeprom.SerialString[ 7 ] == '5')
	{
		sprintf( text, "QUANTUM %s %s %s",
			modelNumberText,
			layoutText,
			configurationText );
	}
	else
	if (gRDEeprom.SerialString[ 7 ] == '3')
	{
		sprintf( text, "CLRC %s %s %s",
			modelNumberText,
			layoutText,
			configurationText );
	}

#elif CUSTOMERID == CUSTOMERID_FT

	sprintf( text, "FT%c-%s %s %s",
		gRDEeprom.SerialString[ 7 ],
		modelNumberText,
		layoutText,
		configurationText );

#elif CUSTOMERID == CUSTOMERID_NL

	sprintf( text, "NL-W %s %s %s",
		modelNumberText,
		layoutText,
		configurationText );

#elif CUSTOMERID == CUSTOMERID_FS

	char	newModelNumberText[ 5 ];

	if (!strcmp( modelNumberText, "025" ))
		strcpy( newModelNumberText, "190" );
	else
	if (!strcmp( modelNumberText, "035" ))
		strcpy( newModelNumberText, "380" );
	else
	if (!strcmp( modelNumberText, "045" ))
		strcpy( newModelNumberText, "450" );
	else
	if (!strcmp( modelNumberText, "055" ))
		strcpy( newModelNumberText, "550" );
	else
		strcpy( newModelNumberText, modelNumberText );

	sprintf( text, "RekuEKO %s %s %s",
		newModelNumberText,
		layoutText,
		configurationText );

#endif

	if (!*text)
	{
		sprintf( text, "CLRC %s %s %s",
			modelNumberText,
			layoutText,
			configurationText );
	}
}

void CLKTS::HWVers_GetText( char* text )
{
	char*	hwVersChar	= (char*) gRDEeprom.HW_Vers;
	byte	charCount	= 0;

	for (int charsCounter = 0; charsCounter < sizeof(gRDEeprom.HW_Vers); charsCounter++, hwVersChar++)
	{
		if (*hwVersChar == ' ' && !charCount)
			continue;

		*text	= *hwVersChar;
		text++;
		charCount++;
	}
	*text	= '\0';
}

void CLKTS::SWVers_GetText( char* text )
{
	char*	swVersChar	= (char*) gRDEeprom.SW_Vers;
	byte	charCount	= 0;

	for (int charsCounter = 0; charsCounter < sizeof(gRDEeprom.SW_Vers); charsCounter++, swVersChar++)
	{
		if (*swVersChar == ' ' && !charCount)
			continue;

		*text	= *swVersChar;
		text++;
	}
	*text	= '\0';
}

void CLKTS::TypeFunc_GetText( char* text )
{
	if(gRDEeprom.Type_func == CLKTSType_BASIC)
		strcpy( text, "BASIC" );
	else
	if(gRDEeprom.Type_func == CLKTSType_EXTRA)
		strcpy( text, "EXTRA" );
	else
	if(gRDEeprom.Type_func == CLKTSType_DEMO)
		strcpy( text, "DEMO" );
	else
		strcpy( text, "" );
}

void CLKTS::AdjustDaylightSavingTime()
{
	//gRTC.getDate();
	//gRTC.getTime();
    //ora legale --> +1  con riferimento al GMT+1(ovvero quando sono le ore 2 aumento di 1)
    if (!gKTSEeprom.GetDaylightSavingTime())
	{
		if (gRTC.getMonth() == 3 && gRTC.getWeekday() == 0 && gRTC.getDay() >= 25 && gRTC.getHour() >= 2)
		{
			gRTC.setTime( gRTC.getHour() + 1, gRTC.getMinute(), gRTC.getSecond() );
			gKTSEeprom.SetDaylightSavingTime( true );
			gRTC.getTime();
		}
	}
	else
    // ora solare --> -1  con riferimento al GMT+1(ovvero quando sono le ore 3 decremento di 1)
	{
		if (gRTC.getMonth() == 10 && gRTC.getWeekday() == 0 && gRTC.getDay() >= 25 && gRTC.getHour() >= 3)
		{
			gRTC.setTime( gRTC.getHour() - 1, gRTC.getMinute(), gRTC.getSecond() );
			gKTSEeprom.SetDaylightSavingTime( false );
			gRTC.getTime();
		}
	}
    //----------------------------------------------------------
}

bool CLKTS::WritePowerOn( unsigned short options, CLKTSPowerMode value )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveSet_Power_ON;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveSet_Power_ON	= gRDEeprom.Set_Power_ON;

	// Imposta i nuovi dati
	gRDEeprom.Set_Power_ON	= value;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_Power_ON ),
		sizeof(gRDEeprom.Set_Power_ON),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	//CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Set_Power_ON	= saveSet_Power_ON;

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	if (value == CLKTSPowerMode_Off)
		gKTSGlobal.RunningMode	= CLKTSRunningMode_PowerOff;
	else
		gKTSGlobal.RunningMode	= CLKTSRunningMode_Running;

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLKTS::_RTCRead( bool force )
{
	byte	saveRTCYear, saveRTCMonth, saveRTCDay, saveRTCHour, saveRTCMinute, saveRTCSeconds, saveRTCDayOfWeek, saveRTCCentury;

	saveRTCYear			= gRTC.getYear();
	saveRTCMonth		= gRTC.getMonth();
	saveRTCDay			= gRTC.getDay();
	saveRTCHour			= gRTC.getHour();
	saveRTCMinute		= gRTC.getMinute();
	saveRTCSeconds		= gRTC.getSecond();
	saveRTCDayOfWeek	= gRTC.getWeekday();
	saveRTCCentury		= gRTC.getCentury();

	gRTC.getDate();
	gRTC.getTime();

	if (m_SaveRTCFirstRead)
	{
		m_SaveRTCFirstRead	= 0;
	}
	else
	{
		if (!force)
		{
			if (saveRTCHour == 23
				&& gRTC.getHour() == 0)
			{
				unsigned short	newYear		= (saveRTCCentury ? 1900 : 2000) + (int) saveRTCYear;
				byte			newMonth	= saveRTCMonth;
				byte			newDay		= saveRTCDay + 1;

				if (newDay > CLDateTime::GetDaysOfMonth( newYear, saveRTCMonth ))
				{
					newDay	= 1;
					newMonth++;
					if (newMonth == 13)
					{
						newMonth	= 1;
						newYear++;
					}
				}

				//char	text[ 200 ];
				//
				//sprintf( text, "SAVE %d %d %d\nCURRENT %d %d %d\nNEW %d %d %d", saveRTCDay, saveRTCMonth, saveRTCYear, gRTC.getDay(), gRTC.getMonth(), gRTC.getYear(), newDay, newMonth, newYear );
				//CLLCDCommon::RenderPanelInfo( text, RGBColor_White, RGBColor_Black, RGBColor_Red, 5000 );

				if (gRTC.getDay() != newDay
					|| gRTC.getMonth() != newMonth
					|| gRTC.getYear() != newYear)
				{
					gRTC.setDate( newDay,
						CLDateTime::GetDayOfWeek( newDay, newMonth, newYear ),
						newMonth,
						saveRTCCentury,
						newYear - (saveRTCCentury ? 1900 : 2000) );
					gRTC.getDate();
					gRTC.getTime();
				}
			}
		}
	}
}

void CLKTS::RTCRead()
{
	CLKTS::_RTCRead( false );
}

void CLKTS::SetDateTime( CLDateTime& dateTime )
{
	gRTC.setDate( dateTime.GetDay(), dateTime.GetDayOfWeek(), dateTime.GetMonth(), 0, dateTime.GetYear() - 2000 );
	gRTC.setTime( dateTime.GetHour(), dateTime.GetMinute(), dateTime.GetSecond() );
	_RTCRead( true );
	//gRTC.getDate();
	//gRTC.getTime();
}

void CLKTS::SetLanguage( int languageId )
{
	gKTSEeprom.SetLanguage( languageId );
	gKTSGlobal.LanguageId	= languageId;
	CLLocalitation::SetPrimaryLanguage( gKTSGlobal.LanguageId );
}

void CLKTS::Write_GetCurrentStepMotors( CLVentilationControl ventilationControl, 
	unsigned short* stepMotors, 
	byte startIndex, byte endIndex )
{
#ifdef FRANCETX_ENABLED
	if (SpeedMode_GetType() == CLSpeedModeType_FranceTx && ventilationControl == CLVentilationControl_CAF)
	{
		for (int counter = startIndex; counter <= endIndex; counter++)
			stepMotors[ counter - startIndex ]	= 0;
	}
	else
	{
		for (int counter = startIndex; counter <= endIndex; counter++)
			stepMotors[ counter - startIndex ]	= SpeedMode_Speed_GetValue( ventilationControl, counter );
	}
#else
	for (int counter = startIndex; counter <= endIndex; counter++)
		stepMotors[ counter - startIndex ]	= SpeedMode_Speed_GetValue( ventilationControl, counter );
#endif
}

bool CLKTS::Write( CLVentilationControl ventilationControl,
	CLSpeedModeType speedMode,
	unsigned short* stepMotors,
	unsigned short idxStepMotors )
{
	bool	writeSpeed		= false;
	bool	steplessEnabled	= false;

#ifdef FRANCETX_ENABLED
	if (speedMode == CLSpeedModeType_FranceTx)
		steplessEnabled	= false;
	else
#endif
	if (speedMode == CLSpeedModeType_Stepless)
		steplessEnabled	= true;
	else
		steplessEnabled	= false;

	writeSpeed	= (idxStepMotors != gRDEeprom.sel_idxStepMotors);

	if (!writeSpeed)
	{
		switch (speedMode)
		{
			case CLSpeedModeType_Stepless:
				if (SpeedMode_Speed_GetValue( ventilationControl, 3 ) != stepMotors[ 3 ])
					writeSpeed	= true;
				break;

			case CLSpeedModeType_ThreeSpeed:
				if (SpeedMode_Speed_GetValue( ventilationControl, 0 ) != stepMotors[ 0 ] ||
					SpeedMode_Speed_GetValue( ventilationControl, 1 ) != stepMotors[ 1 ] ||
					SpeedMode_Speed_GetValue( ventilationControl, 2 ) != stepMotors[ 2 ])
				{
					writeSpeed	= true;
				}
				break;

#ifdef FRANCETX_ENABLED
			case CLSpeedModeType_FranceTx:
			{
				for (int speedsCounter = 0; speedsCounter < 3; speedsCounter++)
				{
					if (speedsCounter == FranceTx_StepMotorsFSC_CAF_StateIndex)
					{
						if (gRDEeprom.Set_StepMotorsFSC_CAF[ speedsCounter ] != stepMotors[ speedsCounter ])
						{
							writeSpeed	= true;
							break;
						}
					}
					else
					{
						if (SpeedMode_Speed_GetValue( ventilationControl, speedsCounter ) != stepMotors[ speedsCounter ])
						{
							writeSpeed	= true;
							break;
						}
					}
				}
				break;
			}
#endif
		}
	}

	if (writeSpeed)
	{
		if (!SpeedMode_Speed_Write( ventilationControl, speedMode, stepMotors, idxStepMotors ))
			return false;
	}

	if (ventilationControl != VentilationControl_Get())
	{
		if (!VentilationControl_Write( ventilationControl ))
			return false;
	}

	if (steplessEnabled != Function_IsEnabled( ENAB_STEPLESS ))
	{
		if (!Function_Write( ENAB_STEPLESS, steplessEnabled ))
			return false;
	}

#ifdef FRANCETX_ENABLED

	// Nel caso di selezione di FranceTX, modifico quelle speed del weekly che sono > di 1
	if (speedMode == CLSpeedModeType_FranceTx)
	{
		SDAYPROG	dayProgs[ 7 ];
		bool	writeWeekly	= false;

		memcpy( dayProgs, gRDEeprom.sDayProg, sizeof(dayProgs) );
		for (int daysCounter = 0; daysCounter < 7; daysCounter++)
		{
			for (int speedsCounter = 0; speedsCounter < 4; speedsCounter++)
			{
				if (GET2BITVALUE( dayProgs[ daysCounter ].ConfigSpeed, speedsCounter ) > 1)
				{
					dayProgs[ daysCounter ].ConfigSpeed	= SET2BITVALUE( dayProgs[ daysCounter ].ConfigSpeed, speedsCounter, 1 );
					writeWeekly	= true;
				}
			}
		}

		if (writeWeekly)
			Weekly_Write( dayProgs );
	}
#endif

	return true;
}

bool CLKTS::WriteStepless( CLVentilationControl ventilationControl,
	unsigned short defaultSteplessSpeed )
{
	unsigned short	newStepMotors[ 4 ];

	CLKTS::Write_GetCurrentStepMotors( ventilationControl, newStepMotors, 0, 3 );

	// Nel caso in cui richiedo la scrittura dei dati step motors, lavoro sui nuovi dati
	if (defaultSteplessSpeed)
		newStepMotors[ 3 ]	= defaultSteplessSpeed;

	if (newStepMotors[ 3 ] < SpeedMode_Stepless_GetMinValue( ventilationControl ))
		newStepMotors[ 3 ]	= SpeedMode_Stepless_GetMinValue( ventilationControl );
	else
	if (newStepMotors[ 3 ] > SpeedMode_Stepless_GetMaxValue( ventilationControl ))
		newStepMotors[ 3 ]	= SpeedMode_Stepless_GetMaxValue( ventilationControl );

	return Write( ventilationControl, CLSpeedModeType_Stepless, newStepMotors, 3 );
}

bool CLKTS::WriteThreeSpeed( CLVentilationControl ventilationControl,
	unsigned short* threeSpeeds,
	byte defaultIdxSpeed )
{
	unsigned short	newStepMotors[ 4 ];
	byte			newIdxStepMotors;
	unsigned short	minStepMotor	= SpeedMode_Stepless_GetMinValue( ventilationControl );
	byte			incStepMotor	= SpeedMode_Stepless_GetIncValue( ventilationControl );
	unsigned short	maxStepMotor	= SpeedMode_Stepless_GetMaxValue( ventilationControl ) - (incStepMotor * 2);

	CLKTS::Write_GetCurrentStepMotors( ventilationControl, newStepMotors, 0, 3 );

	// Nel caso in cui richiedo la scrittura dei dati step motors, lavoro sui nuovi dati
	if (threeSpeeds)
	{
		newStepMotors[ 0 ]	= threeSpeeds[ 0 ];
		newStepMotors[ 1 ]	= threeSpeeds[ 1 ];
		newStepMotors[ 2 ]	= threeSpeeds[ 2 ];
	}

	newIdxStepMotors	= defaultIdxSpeed;
	if (newIdxStepMotors > 2)
		newIdxStepMotors	= 2;

	// Controlla valore min e max delle 3 velocitÃ 
	for (int stepMotorsCounter = 0; stepMotorsCounter < 3; stepMotorsCounter++)
	{
		if (newStepMotors[ stepMotorsCounter ] < minStepMotor)
			newStepMotors[ stepMotorsCounter ]	= minStepMotor;
		else
		if (newStepMotors[ stepMotorsCounter ] > maxStepMotor)
			newStepMotors[ stepMotorsCounter ]	= maxStepMotor;

		minStepMotor	= newStepMotors[ stepMotorsCounter ] + incStepMotor;
		maxStepMotor	+= incStepMotor;
	}

	return Write( ventilationControl, CLSpeedModeType_ThreeSpeed, newStepMotors, newIdxStepMotors );
}

#ifdef FRANCETX_ENABLED

bool CLKTS::WriteFranceTX( byte classIndex )
{
	unsigned short	newStepMotors[ 4 ];

	CLKTS::Write_GetCurrentStepMotors( VentilationControl_Get(), newStepMotors, 0, 3 );

	if (classIndex >= FranceTx_ClassCount)
		classIndex	= FranceTx_ClassCount - 1;

	newStepMotors[ 0 ]		= FranceTx_GetPercentageFromClassIndex( classIndex, 0 );
	newStepMotors[ 1 ]		= FranceTx_GetPercentageFromClassIndex( classIndex, 1 );
	newStepMotors[ 2 ]		= 0;
	newStepMotors[ 3 ]		= 0;
	newStepMotors[ FranceTx_StepMotorsFSC_CAF_StateIndex ]	=
		FranceTx_EncodeState( classIndex );

	return Write( CLVentilationControl_CAF, CLSpeedModeType_FranceTx, newStepMotors, 0 );
}

#endif

CLUnitModel* CLKTS::GetUnitModel()
{
	char	modelName[ MODELNAME_MAXLENGTH + 1 ];

	CLKTS::GetUnitModelName( modelName );
	return CLKTS::FindUnitModel( modelName );
}

CLUnitModel* CLKTS::FindUnitModel( const char* modelName )
{
	CLUnitModel*	unitModel	= gUnitModels;

	while (unitModel->Model != NULL)
	{
		if (strncmp( unitModel->Model, modelName, 4 ) == 0)
			return unitModel;
		unitModel++;
	}

	return NULL;
}

void CLKTS::GetUnitModelName( char* modelName )
{
	strncpy( modelName, ((char*) gRDEeprom.SerialString) + 4, 4 );
	modelName[ MODELNAME_MAXLENGTH ]	= '\0';
}

unsigned short CLKTS::AirFlow_GetMin()
{
	return (unsigned short) ((float) AirFlow_GetMax() / 100.0f) * 20.0f;
}

unsigned short CLKTS::AirFlow_GetMax()
{
	short			maxAirFlow;
	CLUnitModel*	unitModel;

	// Lookup Unit Model
	unitModel	= CLKTS::GetUnitModel();
	if (unitModel != NULL && unitModel->MaxAirFlow != MODEL_AIRFLOW_CALCULATE)
		return unitModel->MaxAirFlow;

	// Nessun modello trovato, esegue calcolo...
	maxAirFlow	= ((short) (gRDEeprom.SerialString[ 4 ] - '0') * 100 + 
		(short) (gRDEeprom.SerialString[ 5 ] - '0') * 10 +
		(short) (gRDEeprom.SerialString[ 6 ] - '0'));

	if (maxAirFlow < 0)
		maxAirFlow	= 0;

	return maxAirFlow * 100;
}

const char* CLKTS::GetSpeedMeasureUnit() 
{
	switch (VentilationControl_Get())
	{
		case CLVentilationControl_CAF:
			return CLFixedText_M3_H;

		case CLVentilationControl_CAP:
			return CLFixedText_PA;

		case CLVentilationControl_FSC:
			return CLFixedText_Perc;
	}
	return "";
}

bool CLKTS::IsSerie3()
{
	if (gRDEeprom.SerialString[ 7 ] == '3')
		return true;
	return false;
}

unsigned short CLKTS::GenerateDeviceID()
{
	long _randomSeed;

	//_randomSeed	= analogRead(0);
    //_randomSeed = millis();
	randomSeed( seed1 );

	//delay( (_randomSeed & 0x00FF) );
    //SYSTICK_DelayMs ( _randomSeed & 0x00FF );

	//_randomSeed	= random1( 1, 0x00FF );
	//randomSeed( _randomSeed );

	//return (unsigned short) (random1( 0x0001, 0xFFFF ) & 0xFFFF);
    return randint( seed1 );
}

bool CLKTS::IsMissingRFMSignal()
{
	return (gKTSGlobal.ComLinkType == BY_WIRELESS &&
		(gKTSGlobal.RunningMode == CLKTSRunningMode_Running ||
		gKTSGlobal.RunningMode == CLKTSRunningMode_PowerOff) &&
		millis() - gKTSGlobal.LastReceivedPollingBase_TimerMilliseconds > 60000);
}

void CLKTS::MillisToText( char* text, unsigned long milliseconds, bool includeHour )
{
	long	seconds		= milliseconds / 1000;
	long	hours;
	long	minutes;

	hours	= seconds / 3600;
	seconds	= seconds % 3600;
	minutes	= seconds / 60;
	seconds	= seconds % 60;

	if (includeHour)
		sprintf( text, "%02li:%02li.%02li", hours, minutes, seconds );
	else
		sprintf( text, "%02li.%02li", minutes, seconds );
}

unsigned long CLKTS::MillisDiff( unsigned long milliseconds1, unsigned long milliseconds2 )
{
	if (milliseconds2 < milliseconds1)
		return (0xFFFFFFFF - milliseconds1) + milliseconds2;
	return milliseconds2 - milliseconds1;
}

int CLKTS::GetCodePage()
{
	switch (gKTSGlobal.LanguageId)
	{
		// (Windows-1250) Central Europe Languages
		case CLLanguageId_PL:
		case CLLanguageId_SL:
		case CLLanguageId_HU:
		case CLLanguageId_RO:
			return 1250;

		// (Windows-1251) Cyrillic Languages
		case CLLanguageId_BG:
			return 1251;

		// (Windows-1252) Latin 1 Languages
		case CLLanguageId_EN:
		case CLLanguageId_IT:
		case CLLanguageId_DE:
		case CLLanguageId_NL:
		case CLLanguageId_FR:
		case CLLanguageId_PT:
			return 1252;
	}

	// Default (Windows-1252)
	return 1252;
}
// -----------------------------------------------------------------------------
// CLKTS [class]
// =============================================================================

