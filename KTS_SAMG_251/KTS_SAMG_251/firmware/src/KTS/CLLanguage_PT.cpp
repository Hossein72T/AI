#include "CLLanguage_PT.h"

const char* gLanguage_PTTexts[ CLTextId__TEXT_COUNT ] =
{
	"ByPass",   /* BYPASS */
	"Antigel",   /* DEFROST */
	"Filtros",   /* FILTERS */
	"Menu",   /* MENU */
	"Guar",   /* SAVE */
	"Hora",   /* TIME */
	"Data:",   /* DATE */
	"Seleci.KTS",   /* SELECT_KTS */
	"DEF BOX INFO PARAM.",   /* CONFIG_BOX_INFO */
	"ESCOLHER LINGUA",   /* SELECTION_LANGUAGE */
	"PARAMET. SCREENSAVER",   /* CONFIG_SCREEN_SAVER */
	"ACTUALIZAR",   /* UPGRADE */
	"REGULACAO DATA",   /* DATE_SETTINGS */
	"REGUL. 3 VELOCIDADES",   /* THREE_SPEED_SETTINGS */
	"PROGRAMACAO SEMANAL",   /* WEEKLY_PROGRAMMER */
	"CALIBRACAO ECRAN",   /* TOUCH_CALIBRATION */
	"REGULACAO FILTROS",   /* FILTER_SETTINGS */
	"REGULACAO BYPASS",   /* BPD_SETTINGS */
	"DESIQUIL. CAUDAl",   /* UNBALANCE_AIRFLOW */
	"Activar Actualizacao",   /* UPGRADE_ACTIVATION */
	"Password incorreta",   /* PASSWORD_INCORRECT */
	"Nu. Serie",   /* SERIAL_ID */
	"VERS. FIRMWARE",   /* FIRMWARE_VERSION */
	"Tipo Unid",   /* UNIT_TYPE */
	"Acessorios:",   /* ACCESSORY */
	"Regulac.",   /* SETTINGS */
	"Servico",   /* SERVICE */
	"Info",   /* INFO */
	"Escolher Lingua",   /* SELECT_LANGUAGE */
	"S",   /* MONDAY_SHORTNAME */
	"T",   /* TUESDAY_SHORTNAME */
	"Q",   /* WEBNESDAY_SHORTNAME */
	"Q",   /* THURSDAY_SHORTNAME */
	"S",   /* FRIDAY_SHORTNAME */
	"S",   /* SATURDAY_SHORTNAME */
	"D",   /* SUNDAY_SHORTNAME */
	"colar",   /* PASTE */
	"copiar",   /* COPY */
	"Def.prim.escalao",   /* SET_FIRST_RANGE */
	"Def.Seg.escalao",   /* SET_SECOND_RANGE */
	"Def.ter.escalao",   /* SET_THIRD_RANGE */
	"Def.qua.escalao",   /* SET_FOURTH_RANGE */
	"In.relogio",   /* START_TIME */
	"Pa.relogio",   /* END_TIME */
	"Caudal",   /* AIR_FLOW */
	"Segunda",   /* MONDAY */
	"Terca",   /* TUESDAY */
	"Quarta",   /* WEDNESDAY */
	"Quinta",   /* THURSDAY */
	"Sexta",   /* FRIDAY */
	"Sabado",   /* SATURDAY */
	"Domingo",   /* SUNDAY */
	"Utilizar ponteiro",   /* MAKE_USE_OF_A_STYLUS_PEN */
	"Pressionar barra Azul",   /* PRESS_THE_BLUE_BAR */
	"Selecionar modo",   /* SELECT_SPEED_MODE */
	"3 velocid.",   /* THREE_SPEED */
	"modulacao",   /* STEPLESS */
	"escol.vel.min",   /* SELECT_SPEED_MIN */
	"escol.vel.media",   /* SELECT_SPEED_MED */
	"escol.vel.máxima",   /* SELECT_SPEED_MAX */
	"Reg.duracao filt:",   /* SET_FILTER_TIME */
	"meses",   /* MONTHS */
	"Reg. Desiquilibrio",   /* SET_UNBALANCE */
	"volta",   /* BACK */
	"GESTAO ACESSORIOS",   /* ACCESSORY_MANAGER */
	"Regul. Temp",   /* CLIMA_SETTINGS */
	"LIMITE DE TEMPERAT.",   /* TEMPERATURE_SETTINGS */
	"Program. Semanal",   /* WEEKLY_SETTINGS */
	"Program",   /* PROGRAM */
	"Ver",   /* VIEW */
	"Prog",   /* PROG */
	"Def.N. escaloes:",   /* SET_NBR_OF_RANGES */
	"voltar",   /* RETURN */
	"unida",   /* UNIT */
	"a carregar..",   /* SEARCHING */
	"Erro",   /* ERROR */
	"unid.nao encontr.",   /* UNIT_NOT_FOUND */
	"Por fav. verique",   /* PLEASE_CHECK_THE */
	"Ligueocabo erein.",   /* CABLE_AND_RESTART */
	"O Sistema",   /* THE_SYSTEM */
	"Ligado",   /* CONNECTED */
	"Indisp.",   /* DISABLE */
	"Visor calibrado",   /* TOUCH_CALIBRATED */
	"Relatorio alar.:",   /* WARNINGS_REPORT */
	"Recomend.para mudar filtros",   /* RECOMMEND_TO_CHANGE_FILTERS */
	"password incorr.",   /* PASSWORD_CORRECT */
	"Dom",   /* SUN */
	"Seg",   /* MON */
	"Ter",   /* TUE */
	"Qua",   /* WED */
	"Qui",   /* THU */
	"Sex",   /* FRI */
	"Sab",   /* SAT */
	"nc",   /* NC */
	"UMIDADE PAR.DE CONF.",   /* RH_SETTINGS */
	"Param. Niv. HR",   /* SET_RH_THRESHOLD */
	"CO2 PAR.DE CONGFIG.",   /* CO2_SETTINGS */
	"    CO2     Caudal",   /* SET_CO2_THRESHOLD */
	"Contador",   /* COUNTER */
	"SOBRE-VENTILACAO",   /* PARTY_SETTINGS */
	"Dur.sobre-vent.:",   /* SET_PARTY_TIMER */
	"Evento",   /* EVENT */
	"Seman",   /* WEEK */
	"Sondas",   /* PROBES */
	"Config",   /* CONFIG */
	"Histerese Temp.",   /* HYSTER_TEMPSET */
	"VERAO",   /* SUMMER */
	"INVERN",   /* WINTER */
	"T.Fresco",   /* TFRESH */
	"TEMPER. HISTERRSE",   /* TEMPERATURE_HYSTERESIS */
	"SUPPLY",   /* SUPPLY */
	"EXTRACT",   /* EXTRACT */
	"REPORT DATA",   /* REPORT_DATA */
	"PRESSURE SENSOR:",   /* PRESSURE_SENSOR */
	"LEVEL LINK SENSOR:",   /* LEVEL_LINK_SENSOR */
	"SETPOINT PRESSURE:",   /* SETPOINT_PRESSURE */
	"MEASURE PRESSURE:",   /* MEASURE_PRESSURE */
	"SPEED MOTORS:",   /* SPEED_MOTORS */
	"CONNECT",   /* CONNECT */
	"NOT CONNECTED",   /* NOT_CONNECTED */
	CLText_NoText,   /* REMOVE_ACCESSORY */
	CLText_NoText,   /* CONFIRM_REMOVE */
	CLText_NoText,   /* TRETURN */
	CLText_NoText,   /* YES */
	CLText_NoText,   /* NO */
	CLText_NoText,   /* MANUAL */
	CLText_NoText,   /* AUTOMATIC */
	CLText_NoText,   /* OPEN */
	CLText_NoText,   /* CLOSED */
	CLText_NoText,   /* CLIMA */
	CLText_NoText,   /* PASSWORD */
	CLText_NoText,   /* HOT */
	CLText_NoText,   /* COLD */
	CLText_NoText,   /* RESET */
	CLText_NoText,   /* INPUT_CONFIG */
	CLText_NoText,   /* INPUT_CONFIG_0V_STOP */
	CLText_NoText,   /* INPUT_CONFIG_10V_STOP */
	CLText_NoText,   /* INPUT_CONFIG_0V_OPEN */
	CLText_NoText,   /* INPUT_CONFIG_10V_OPEN */
	CLText_NoText,   /* INPUT_CONFIG_REG_AIR_FLOW */
	CLText_NoText,   /* OUTPUT_CONFIG */
	CLText_NoText,   /* SELECT_FRANCE_CLASSTX */
	CLText_NoText,   /* FRANCE_CLASSTX */
	CLText_NoText,   /* VENTILATION_CONTROL */
	CLText_NoText,   /* VOC_CONFIG */
	CLText_NoText,   /* TEMPERATURE */
	CLText_NoText,   /* SPEED */
	CLText_NoText,   /* CLIMA_CONTROL */
	CLText_NoText,   /* WRITING_DATA */
	CLText_NoText,   /* WRITING_DATA_COMPLETED */
	CLText_NoText,   /* WRITING_DATA_ERROR */
	CLText_NoText,   /* IN_ALARM */
	CLText_NoText,   /* EXTERNAL_CONTROL */
	CLText_NoText,   /* ERRORS_REPORT */
	CLText_NoText,   /* SET_RANGE */
	CLText_NoText,   /* MANUAL_OFF */
	CLText_NoText,   /* MANUAL_ON */
	CLText_NoText,   /* MANUAL_CLOSE */
	CLText_NoText,   /* MANUAL_OPEN */
	CLText_NoText,   /* AUT_OFF */
	CLText_NoText,   /* AUT_ON */
	CLText_NoText,   /* CHANGING */
	CLText_NoText,   /* MINUTE_ABBR */
	CLText_NoText,   /* AIRFLOW_CONFIG */
	CLText_NoText,   /* WATER_CK */
	CLText_NoText,   /* SELECT_EVENT */
	CLText_NoText,   /* BYPASS_OPEN */
	CLText_NoText,   /* BYPASS_CLOSE */
	CLText_NoText,   /* UNIT_RUN */
	CLText_NoText,   /* UNIT_FAULT */
	CLText_NoText,   /* SELECT_ACTION */
	CLText_NoText,   /* OLD_PASSWORD */
	CLText_NoText,   /* NEW_PASSWORD */
	CLText_NoText,   /* REPEAT_NEW_PASSWORD */
	CLText_NoText,   /* CHANGE_END_USER_PASSWORD */
	CLText_NoText,   /* CHANGE_SERVICE_PASSWORD */
	CLText_NoText,   /* CHANGE_PASSWORD */
	CLText_NoText,   /* PASSWORD_SETTINGS */
	CLText_NoText,   /* DATA_CHANGED */
	CLText_NoText,   /* SAVE_CHANGES */
	CLText_NoText,   /* CANCEL */
	CLText_NoText,   /* PROBES_SETTINGS */
	CLText_NoText,   /* HEATER */
	CLText_NoText,   /* COOLER */
	CLText_NoText,   /* DAYS */
	CLText_NoText,   /* DISCONNECT_ACCESSORY */
	CLText_NoText,   /* BOXINFO_ACCESSORY_CLIMA */
	CLText_NoText,   /* MB_HARDWARE_VERSION */
	CLText_NoText,   /* MB_SOFTWARE_VERSION */
	CLText_NoText,   /* PREHEATER */
	CLText_NoText,   /* POSTHEATER */
	CLText_NoText,   /* INTERNAL */
	CLText_NoText,   /* MEASURE_AIRFLOW */
	CLText_NoText,   /* MODBUS_SETTINGS */
	CLText_NoText,   /* MODBUS_ADDRESS */
	CLText_NoText,   /* MODBUS_STATUS */
	CLText_NoText,   /* DISCONNECTED */
	CLText_NoText,   /* BYPASS_MIN_EXT_TEMPERATURE */
	CLText_NoText,   /* DATA_AVAILABLE_FROM_MODBUS */
	CLText_NoText,   /* RFM__CHANNEL */
	CLText_NoText,   /* RFM__STATUS */
	CLText_NoText,   /* RFM__CHANGE_CHANNEL */
	CLText_NoText,   /* CONNECTING */
	CLText_NoText,   /* RFM__CHANNEL_FREE */
	CLText_NoText,   /* RFM__CHANNEL_BUSY */
	CLText_NoText,   /* RFM__CHANNEL_INPROGRESS */
	CLText_NoText,   /* RFM__ALERT_CHANNEL_BUSY */
	CLText_NoText,   /* CONNECT__RETRY_CONNECTION_MESSAGE */
	CLText_NoText,   /* RFM__CHECKING_CHANNEL_IN_PROGRESS */
	CLText_NoText,   /* FIREALARM_FIRE_ALARM */
	CLText_NoText,   /* REFERENCE_T_SETTING */
	CLText_NoText,   /* SECOND_ABBR */
	CLText_NoText,   /* DXDSETTINGS_REFERENCEPROBE */
	CLText_NoText,   /* DXDSETTINGS_DELTATEMPERATURE */
	CLText_NoText,   /* DXDSETTINGS_DELAY */
	CLText_NoText,   /* BYPASS_OPERATED_BY_EXT_INPUT */
	CLText_NoText,   /* CAP_CALIBRATION_PROCEDURE */
	CLText_NoText,   /* CAP_CALIBRATION_START_MESSAGE */
	CLText_NoText,   /* CAP_CALIBRATION_RUNNING_MESSAGE */
	CLText_NoText,   /* CAP_CALIBRATION_CONFIRMDATA_MESSAGE */
	CLText_NoText,   /* AUTOMATIC_ON_STANDBY */
	CLText_NoText,   /* FIREALARM_ALARM_ACTIVATED */
	CLText_NoText,   /* FIREALARM_ALARM_DEACTIVATED */
	CLText_NoText,   /* FIREALARM_CONFIGURATION */
	CLText_NoText,   /* FIREALARM_REARM_MESSAGE */
	CLText_NoText,   /* FIREALARM_REARM */
	CLText_NoText,   /* PARTY_MODE */
	CLText_NoText, /* PROCEDURE_STARTING_MESSAGE */
	CLText_NoText, /* PROCEDURE_RUNNING_MESSAGE */
	CLText_NoText, /* PROCEDURE_COMPLETED_MESSAGE */
	CLText_NoText, /* DPP_THRESHOLD */
	CLText_NoText, /* DPP_CALIBRATION */
	CLText_NoText, /* DPP_FILTER_LEVEL */
	CLText_NoText, /* Disconnect all accessories */
};

