 /*************************************************************************************
 *  file:			CLLocalitation.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLLocalitation_h
#define __CLLocalitation_h

#include "CLCommon.h"
#include "CLGraphics.h"

extern const char* CLText_NoText;

extern const char* CLFixedText_BPD;
extern const char* CLFixedText_ON;
extern const char* CLFixedText_OFF;
extern const char* CLFixedText_OK;
extern const char* CLFixedText_CAF;
extern const char* CLFixedText_CAP;
extern const char* CLFixedText_FSC;
extern const char* CLFixedText_RH;
extern const char* CLFixedText_CO2;
extern const char* CLFixedText_PPM;
extern const char* CLFixedText_VOC;
extern const char* CLFixedText_AWP;
extern const char* CLFixedText_M3_H;
extern const char* CLFixedText_PA;
extern const char* CLFixedText_Perc;
extern const char CLFixedText_ugM3[];
extern const char* CLFixedText_CRLF;
extern const char* CLFixedText_IPHED;
extern const char* CLFixedText_PHED;

//enum CLLanguageId
//{
#define CLLanguageId_EN	0	// Inglese
#define CLLanguageId_IT	1	// Italiano
#define CLLanguageId_DE	2	// Tedesco
#define CLLanguageId_NL	3	// Olandese
#define CLLanguageId_FR	4	// Francese
#define CLLanguageId_PT	5	// Portoghese
#define CLLanguageId_PL	6	// Polacco
#define CLLanguageId_SL	7	// Sloveno
#define CLLanguageId_HU	8	// Ungherese
#define CLLanguageId_RO	9	// Rumeno
#define CLLanguageId_BG	10	// Bulgaro

#define CLLanguageId__COUNT CLLanguageId_BG + 1
//};

enum CLTextId
{
	CLTextId_BYPASS,
	CLTextId_DEFROST,
	CLTextId_FILTERS,
	CLTextId_MENU,
	CLTextId_SAVE,
	CLTextId_TIME,
	CLTextId_DATE,
	CLTextId_SELECT_KTS,
	CLTextId_CONFIG_BOX_INFO,
	CLTextId_SELECTION_LANGUAGE,
	CLTextId_CONFIG_SCREEN_SAVER,
	CLTextId_UPGRADE,
	CLTextId_DATE_SETTINGS,
	CLTextId_THREE_SPEED_SETTINGS,
	CLTextId_WEEKLY_PROGRAMMER,
	CLTextId_TOUCH_CALIBRATION,
	CLTextId_FILTER_SETTINGS,
	CLTextId_BPD_SETTINGS,
	CLTextId_UNBALANCE_AIRFLOW,
	CLTextId_UPGRADE_ACTIVATION,
	CLTextId_PASSWORD_INCORRECT,
	CLTextId_SERIAL_ID,
	CLTextId_FIRMWARE_VERSION,
	CLTextId_UNIT_TYPE,
	CLTextId_ACCESSORY,
	CLTextId_SETTINGS,
	CLTextId_SERVICE,
	CLTextId_INFO,
	CLTextId_SELECT_LANGUAGE,
	CLTextId_MONDAY_SHORTNAME,
	CLTextId_TUESDAY_SHORTNAME,
	CLTextId_WEBNESDAY_SHORTNAME,
	CLTextId_THURSDAY_SHORTNAME,
	CLTextId_FRIDAY_SHORTNAME,
	CLTextId_SATURDAY_SHORTNAME,
	CLTextId_SUNDAY_SHORTNAME,
	CLTextId_PASTE,
	CLTextId_COPY,
	CLTextId_SET_FIRST_RANGE,
	CLTextId_SET_SECOND_RANGE,
	CLTextId_SET_THIRD_RANGE,
	CLTextId_SET_FOURTH_RANGE,
	CLTextId_START_TIME,
	CLTextId_END_TIME,
	CLTextId_AIR_FLOW,
	CLTextId_MONDAY,
	CLTextId_TUESDAY,
	CLTextId_WEDNESDAY,
	CLTextId_THURSDAY,
	CLTextId_FRIDAY,
	CLTextId_SATURDAY,
	CLTextId_SUNDAY,
	CLTextId_MAKE_USE_OF_A_STYLUS_PEN,
	CLTextId_PRESS_THE_BLUE_BAR,
	CLTextId_SELECT_SPEED_MODE,
	CLTextId_THREE_SPEED,
	CLTextId_STEPLESS,
	CLTextId_SELECT_SPEED_MIN,
	CLTextId_SELECT_SPEED_MED,
	CLTextId_SELECT_SPEED_MAX,
	CLTextId_SET_FILTER_TIME,
	CLTextId_MONTHS,
	CLTextId_SET_UNBALANCE,
	CLTextId_BACK,
	CLTextId_ACCESSORY_MANAGER,
	CLTextId_CLIMA_SETTINGS,
	CLTextId_TEMPERATURE_SETTINGS,
	CLTextId_WEEKLY_SETTINGS,
	CLTextId_PROGRAM,
	CLTextId_VIEW,
	CLTextId_PROG,
	CLTextId_SET_NBR_OF_RANGES,
	CLTextId_RETURN,
	CLTextId_UNIT,
	CLTextId_SEARCHING,
	CLTextId_ERROR,
	CLTextId_UNIT_NOT_FOUND,
	CLTextId_PLEASE_CHECK_THE,
	CLTextId_CABLE_AND_RESTART,
	CLTextId_THE_SYSTEM,
	CLTextId_CONNECTED,
	CLTextId_DISABLE,
	CLTextId_TOUCH_CALIBRATED,
	CLTextId_WARNINGS_REPORT,
	CLTextId_RECOMMEND_TO_CHANGE_FILTERS,
	CLTextId_PASSWORD_CORRECT,
	CLTextId_SUN,
	CLTextId_MON,
	CLTextId_TUE,
	CLTextId_WED,
	CLTextId_THU,
	CLTextId_FRI,
	CLTextId_SAT,
	CLTextId_NC,
	CLTextId_RH_SETTINGS,
	CLTextId_SET_RH_THRESHOLD,
	CLTextId_CO2_SETTINGS,
	CLTextId_SET_CO2_THRESHOLD,
	CLTextId_COUNTER,
	CLTextId_PARTY_SETTINGS,
	CLTextId_SET_PARTY_TIMER,
	CLTextId_EVENT,
	CLTextId_WEEK,
	CLTextId_PROBES,
	CLTextId_CONFIG,
	CLTextId_HYSTER_TEMPSET,
	CLTextId_SUMMER,
	CLTextId_WINTER,
	CLTextId_TFRESH,
	CLTextId_TEMPERATURE_HYSTERESIS,
	CLTextId_SUPPLY,
	CLTextId_EXTRACT,
	CLTextId_REPORT_DATA,
	CLTextId_PRESSURE_SENSOR,
	CLTextId_LEVEL_LINK_SENSOR,
	CLTextId_SETPOINT_PRESSURE,
	CLTextId_MEASURE_PRESSURE,
	CLTextId_SPEED_MOTORS,
	CLTextId_CONNECT,
	CLTextId_NOT_CONNECTED,
	CLTextId_REMOVE_ACCESSORY,
	CLTextId_CONFIRM_REMOVE,
	CLTextId_TRETURN,
	CLTextId_YES,
	CLTextId_NO,
	CLTextId_MANUAL,
	CLTextId_AUTOMATIC_ON,
	CLTextId_OPEN,
	CLTextId_CLOSED,
	CLTextId_CLIMA,
	CLTextId_PASSWORD,
	CLTextId_HOT,
	CLTextId_COLD,
	CLTextId_RESET,
	CLTextId_INPUT_CONFIG,
	CLTextId_INPUT_CONFIG_0V_STOP,
	CLTextId_INPUT_CONFIG_10V_STOP,
	CLTextId_INPUT_CONFIG_0V_OPEN,
	CLTextId_INPUT_CONFIG_10V_OPEN,
	CLTextId_INPUT_CONFIG_REG_AIR_FLOW,
	CLTextId_OUTPUT_CONFIG,
	CLTextId_SELECT_FRANCE_CLASSTX,
	CLTextId_FRANCE_CLASSTX,
	CLTextId_VENTILATION_CONTROL,
	CLTextId_VOC_CONFIG,
	CLTextId_TEMPERATURE,
	CLTextId_SPEED,
	CLTextId_CLIMA_CONTROL,
	CLTextId_WRITING_DATA,
	CLTextId_WRITING_DATA_COMPLETED,
	CLTextId_WRITING_DATA_ERROR,
	CLTextId_IN_ALARM,
	CLTextId_EXTERNAL_CONTROL,
	CLTextId_ERRORS_REPORT,
	CLTextId_SET_RANGE,
	CLTextId_MANUAL_OFF,
	CLTextId_MANUAL_ON,
	CLTextId_MANUAL_CLOSE,
	CLTextId_MANUAL_OPEN,
	CLTextId_AUT_OFF,
	CLTextId_AUT_ON,
	CLTextId_CHANGING,
	CLTextId_MINUTE_ABBR,
	CLTextId_AIRFLOW_CONFIG,
	CLTextId_WATER_CK,
	CLTextId_SELECT_EVENT,
	CLTextId_BYPASS_OPEN,
	CLTextId_BYPASS_CLOSE,
	CLTextId_UNIT_RUN,
	CLTextId_UNIT_FAULT,
	CLTextId_SELECT_ACTION,
	CLTextId_OLD_PASSWORD,
	CLTextId_NEW_PASSWORD,
	CLTextId_REPEAT_NEW_PASSWORD,
	CLTextId_CHANGE_END_USER_PASSWORD,
	CLTextId_CHANGE_SERVICE_PASSWORD,
	CLTextId_CHANGE_PASSWORD,
	CLTextId_PASSWORD_SETTINGS,
	CLTextId_DATA_CHANGED,
	CLTextId_SAVE_CHANGES,
	CLTextId_CANCEL,
	CLTextId_PROBES_SETTINGS,
	CLTextId_HEATER,
	CLTextId_COOLER,
	CLTextId_DAYS,
	CLTextId_DISCONNECT_ACCESSORY,
	CLTextId_BOXINFO_ACCESSORY_CLIMA,
	CLTextId_MB_HARDWARE_VERSION,
	CLTextId_MB_SOFTWARE_VERSION,
	CLTextId_PREHEATER,
	CLTextId_POSTHEATER,
	CLTextId_INTERNAL,
	CLTextId_MEASURE_AIRFLOW,
	CLTextId_MODBUS_SETTINGS,
	CLTextId_MODBUS_ADDRESS,
	CLTextId_MODBUS_STATUS,
	CLTextId_DISCONNECTED,
	CLTextId_BYPASS_MIN_EXT_TEMPERATURE,
	CLTextId_DATA_AVAILABLE_FROM_MODBUS,
	CLTextId_RFM__CHANNEL,
	CLTextId_RFM__STATUS,
	CLTextId_RFM__CHANGE_CHANNEL,
	CLTextId_CONNECTING,
	CLTextId_RFM__CHANNEL_FREE,
	CLTextId_RFM__CHANNEL_BUSY,
	CLTextId_RFM__CHANNEL_INPROGRESS,
	CLTextId_RFM__ALERT_CHANNEL_BUSY,
	CLTextId_CONNECT__RETRY_CONNECTION_MESSAGE,
	CLTextId_RFM__CHECKING_CHANNEL_IN_PROGRESS,
	CLTextId_FIREALARM_FIRE_ALARM,
	CLTextId_REFERENCE_T_SETTING,
	CLTextId_SECOND_ABBR,
	CLTextId_DXDSETTINGS_REFERENCEPROBE,
	CLTextId_DXDSETTINGS_DELTATEMPERATURE,
	CLTextId_DXDSETTINGS_DELAY,
	CLTextId_BYPASS_OPERATED_BY_EXT_INPUT,
	CLTextId_CAP_CALIBRATION_PROCEDURE,
	CLTextId_CAP_CALIBRATION_START_MESSAGE,
	CLTextId_CAP_CALIBRATION_RUNNING_MESSAGE,
	CLTextId_CAP_CALIBRATION_CONFIRMDATA_MESSAGE,
	CLTextId_AUTOMATIC_ON_STANDBY,
	CLTextId_FIREALARM_ALARM_ACTIVATED,
	CLTextId_FIREALARM_ALARM_DEACTIVATED,
	CLTextId_FIREALARM_CONFIGURATION,
	CLTextId_FIREALARM_REARM_MESSAGE,
	CLTextId_FIREALARM_REARM,
	CLTextId_PARTY_MODE,
	CLTextId_PROCEDURE_STARTING_MESSAGE,
	CLTextId_PROCEDURE_RUNNING_MESSAGE,
	CLTextId_PROCEDURE_COMPLETED_MESSAGE,
	CLTextId_DPP_THRESHOLD,
	CLTextId_DPP_CALIBRATION,
	CLTextId_DPP_FILTER_LEVEL,
	CLTextId_DISCONNECT_ALL,
	CLTextId_DSC_DELAY_UPDATE,
	CLTextId_PIR_DELAY_UPDATE,
    CLTextId_QR_CODE,
    CLTextId_AIR_SENSOR_STATE,
    CLTextId_CO2_VALUE,
    CLTextId_VOC_VALUE,
    CLTextId_RH_VALUE,
    CLTextId_AIR_SENSOR_ACCURRACY,
    CLTextId_AIR_QUALITY,
    CLTextId_AIR_QUALITY_PRECISION,
    CLTextId_CLEAN_EVENT_UPDATE,
    CLTextId_DAYS_ABBR,
    CLTextId_SET_CLEAN_EVENT_DELAY,
	CLTextId__TEXT_COUNT
};

// =============================================================================
// CLLocalitation [class]
// =============================================================================
// Description: Classe di supporto per la localizzazione
// -----------------------------------------------------------------------------
class CLLocalitation
{
	private: static int m_PrimaryLanguageId;
	private: static char** m_PrimaryLanguageTexts;

	private: static int m_SecondaryLanguageId;
	private: static char** m_SecondaryLanguageTexts;

	public: static const char** GetLanguageTexts( int languageId );

	public: static void SetPrimaryLanguage( int languageId );
	public: static int GetPrimaryLanguageId();
	public: static const char** GetPrimaryLanguageTexts();

	public: static void SetSecondaryLanguage( int languageId );
	public: static int GetSecondaryLanguageId();
	public: static const char** GetSecondaryLanguageTexts();

	public: static const char* GetText( short id );
};
// -----------------------------------------------------------------------------
// CLLocalitation [class]
// =============================================================================

#endif

