#include "CLProcedure.h"

#include "CLForm.h"
#include "CLAccessoryManagerForm.h"
#include "CLBypassConfigForm.h"
#include "CLInputConfigForm.h"
#include "CLOutputConfigForm.h"
#include "CLServiceMenu.h"
#include "CLInfoForm.h"
#include "CLSystemDateTimeConfigForm.h"
#include "CLReportDebugDataForm.h"
#include "CLReportDebugDataAdminForm.h"
#include "CLSettingsMenu.h"
#include "CLBoxInfoConfigForm.h"
#include "CLPartyConfigForm.h"
#include "CLSelectionLanguageForm.h"
#include "CLSpeedModeConfigForm.h"
#include "CLSelectionVentilationControlForm.h"
#include "CLCO2ConfigForm.h"
#include "CLVOCConfigForm.h"
#include "CLRHConfigForm.h"
#include "CLFilterConfigForm.h"
#include "CLScreenSaverConfigForm.h"
#include "CLTemperatureConfigForm.h"
#include "CLHysteresisTemperatureConfigForm.h"
#include "CLUnbalanceConfigForm.h"
#include "CLScreenCalibrationForm.h"
#include "CLWeeklyMainForm.h"
#include "CLPasswordForm.h"
#include "CLLCDCommon.h"
#include "CLEndUserPasswordConfigForm.h"
#include "CLUpgradeForm.h"
#include "CLProbesSettingsForm.h"
#include "CLModBusConfigForm.h"
#include "CLFunction.h"
#include "CLTestUnitForm.h"
#include "CLCommunication_Driver.h"
#include "CLRFMSelectChannelForm.h"
#include "CLEepromResetForm.h"
#include "CLReferenceTSettingForm.h"
#include "CLShowFontsForm.h"
#include "CLDscDelayUpdateConfigForm.h"
#include "CLPirDelayUpdateConfigForm.h"
#include "CLCleanEventForm.h"

CLFormResult Procedure_Execute( CLProcedureId procedureId, unsigned short options )
{
	CLFormResult	result			= CLFormResult_None;

	switch (procedureId)
	{
		case CLProcedureId_ScreenCalibrationForm:
			result	= CLScreenCalibrationForm_Open( options );
			break;

		case CLProcedureId_AccessoryManagerForm:
			result	= CLAccessoryManagerForm_Open( options );
			break;

		case CLProcedureId_BypassConfigForm:
			result	= CLBypassConfigForm_Open( options );
			break;

		case CLProcedureId_TestUnitForm:
			result	= CLTestUnitForm_Open( options );
			break;

		case CLProcedureId_UnbalanceConfigForm:
			result	= CLUnbalanceConfigForm_Open( options );
			break;

		case CLProcedureId_EndUserPasswordConfigForm:
			result	= CLEndUserPasswordConfigForm_Open( options );
			break;

		case CLProcedureId_ServicePasswordChangeForm:
			if ((result == CLKTS::ChangePassword( true )) == CLFormResult_Cancel)
			{
				// Visualizza il messaggio di errore
				CLLCDCommon::WriteDataPanel_DisplayError();
			}
			break;

		case CLProcedureId_BoxInfoConfigForm:
			result	= CLBoxInfoConfigForm_Open( options );
			break;

		case CLProcedureId_InputConfigForm:
			result	= CLInputConfigForm_Open( options );
			break;

		case CLProcedureId_OutputConfigForm:
			result	= CLOutputConfigForm_Open( options );
			break;

		case CLProcedureId_FilterConfigForm:
			result	= CLFilterConfigForm_Open( options );
			break;

		case CLProcedureId_CO2ConfigForm:
			result	= CLCO2ConfigForm_Open( options );
			break;

		case CLProcedureId_VOCConfigForm:
			result	= CLVOCConfigForm_Open( options );
			break;

		case CLProcedureId_HysteresisTemperatureConfigForm:
			result	= CLHysteresisTemperatureConfigForm_Open( options );
			break;

		case CLProcedureId_SettingsMenu:
			result	= CLSettingsMenu_Open();
			break;

#if KTS_SHOWFONTSFORM == 1
		case CLProcedureId_ShowFontsForm:
			result	= CLShowFontsForm_Open();
			break;
#endif

		case CLProcedureId_ServiceMenu:
			result	= CLServiceMenu_Open();
			break;

		case CLProcedureId_InfoForm:
			result	= CLInfoForm_Open();
			break;

		case CLProcedureId_SelectionLanguageForm:
			result	= CLSelectionLanguageForm_Open( options );
			break;

		case CLProcedureId_ScreenSaverConfigForm:
			result	= CLScreenSaverConfigForm_Open( options );
			break;

		case CLProcedureId_SystemDateTimeConfigForm:
			result	= CLSystemDateTimeConfigForm_Open( options );
			break;

		case CLProcedureId_UpgradeForm:
			result	= CLUpgradeForm_Open( options );
			break;

		case CLProcedureId_WeeklyMainForm:
			result	= CLWeeklyMainForm_Open( options );
			break;

		case CLProcedureId_ClimaSettingsForm:
			result	= CLTemperatureConfigForm_Open( options, CLTemperatureConfigFormOption_Mode_Auto );
			break;

		case CLProcedureId_SpeedModeConfigForm:
			result	= CLSpeedModeConfigForm_Open( options );
			break;

		case CLProcedureId_RHConfigForm:
			result	= CLRHConfigForm_Open( options );
			break;
		
		case CLProcedureId_DSCUpdateDelay:
			result	= CLDscDelayUpdateConfigForm_Open( options );
			break;
		
		case CLProcedureId_PIRUpdateDelay:
			result	= CLPirDelayUpdateConfigForm_Open( options );
			break;
		
        case CLProcedureId_CleanEventForm:
			result	= CLCleanEventForm_Open( options );
			break;
            
		case CLProcedureId_PartyConfigForm:
			result	= CLPartyConfigForm_Open( options );
			break;

		case CLProcedureId_ReportDebugDataForm:
			result	= CLReportDebugDataForm_Open( options );
			break;

		case CLProcedureId_ReportDebugDataAdminForm:
			result	= CLReportDebugDataAdminForm_Open( options );
			break;

		case CLProcedureId_SelectionVentilationControlForm:
			result	= CLSelectionVentilationControlForm_Open( options );
			break;

		case CLProcedureId_ProbesSettingsForm:
			result	= CLProbesSettingsForm_Open( options );
			break;

		case CLProcedureId_ModBusConfigForm:
			result	= CLModBusConfigForm_Open( options );
			break;

		case CLProcedureId_RFMChangeChannelForm:
			result	= CLRFMSelectChannelForm_Open( options,
				CLRFMSelectChannelForm::CLExtOption_HighlightCurrentChannel );
			break;

		case CLProcedureId_EepromResetForm:
			result	= CLEepromResetForm_Open( options );
			break;

		case CLProcedureId_ReferenceTSetting:
			result	= CLReferenceTSettingForm_Open( options );
			break;
	}

	return result;
}

bool Procedure_IsEnabled( CLProcedureId procedureId )
{
	switch (procedureId)
	{
		case CLProcedureId_ScreenCalibrationForm:
			return false;

		case CLProcedureId_ReferenceTSetting:
			return true;

		case CLProcedureId_UnbalanceConfigForm:
			return Function_CanEnable( ENAB_IMBALANCE );

		case CLProcedureId_InputConfigForm:
			return Accessory_IsPresent( ACC_EEP_INP );

		case CLProcedureId_OutputConfigForm:
			return Accessory_IsPresent( ACC_EEP_OUT );

		case CLProcedureId_BypassConfigForm:
			return Accessory_IsPresent( ACC_EEP_BPD );

		case CLProcedureId_HysteresisTemperatureConfigForm:
			return Accessory_IsPresent( ACC_EEP_CWD ) ||
				Accessory_IsPresent( ACC_EEP_EHD ) ||
				Accessory_IsPresent( ACC_EEP_SSR ) ||
				Accessory_IsPresent( ACC_EEP_HWD ) ||
				Accessory_IsPresent( ACC_EEP_P2CO2 ) ||
				Accessory_IsPresent( ACC_EEP_P1CO2 );

		case CLProcedureId_SystemDateTimeConfigForm:
			return (gRDEeprom.Type_func != CLKTSType_BASIC);

		case CLProcedureId_UpgradeForm:
			return (gRDEeprom.Type_func != CLKTSType_EXTRA);

		case CLProcedureId_WeeklyMainForm:
			return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO);

		//case CLProcedureId_ClimaSettingsForm:
		//	return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO);

		case CLProcedureId_SpeedModeConfigForm:
			return (gRDEeprom.Type_func != CLKTSType_BASIC);

		case CLProcedureId_RHConfigForm:
			return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO) &&
				(Accessory_IsPresent( ACC_EEP_P2RH ) || Accessory_IsPresent( ACC_EEP_P1RH ));

		case CLProcedureId_CO2ConfigForm:
			return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO) &&
				(Accessory_IsPresent( ACC_EEP_P2CO2 ) || Accessory_IsPresent( ACC_EEP_P1CO2 ));

		case CLProcedureId_VOCConfigForm:
			return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO) &&
				(Accessory_IsPresent( ACC_EEP_P1VOC ));

		case CLProcedureId_PartyConfigForm:
			return (gRDEeprom.Type_func == CLKTSType_EXTRA || gRDEeprom.Type_func == CLKTSType_DEMO);

		case CLProcedureId_SelectionVentilationControlForm:
			return (gRDEeprom.Type_func != CLKTSType_BASIC);

		case CLProcedureId_ModBusConfigForm:
			return Accessory_IsPresent( ACC_EEP_MBUS );

		case CLProcedureId_RFMChangeChannelForm:
			return sdata_wi.install_rfm && gKTSGlobal.RunningMode == CLKTSRunningMode_Running;
	}

	return true;
}

