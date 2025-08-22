#ifndef __CLProcedure_h
#define __CLProcedure_h

#include "CLCommon.h"
#include "CLForm.h"

enum CLProcedureId
{
	CLProcedureId_None,

	// Service
	CLProcedureId_ScreenCalibrationForm,
	CLProcedureId_AccessoryManagerForm,
	CLProcedureId_BypassConfigForm,
	CLProcedureId_UnbalanceConfigForm,
	CLProcedureId_BoxInfoConfigForm,
	CLProcedureId_InputConfigForm,
	CLProcedureId_OutputConfigForm,
	CLProcedureId_FilterConfigForm,
	CLProcedureId_CO2ConfigForm,
	CLProcedureId_VOCConfigForm,
	CLProcedureId_HysteresisTemperatureConfigForm,
	CLProcedureId_ReportDebugDataForm,
	CLProcedureId_ReportDebugDataAdminForm,
	CLProcedureId_SelectionVentilationControlForm,
	CLProcedureId_EndUserPasswordConfigForm,
	CLProcedureId_ProbesSettingsForm,
	CLProcedureId_ModBusConfigForm,
	CLProcedureId_TestUnitForm,
	CLProcedureId_RFMChangeChannelForm,
	CLProcedureId_EepromResetForm,
	CLProcedureId_ReferenceTSetting,
	#if KTS_SHOWFONTSFORM == 1
	CLProcedureId_ShowFontsForm,
	#endif
	CLProcedureId_DSCUpdateDelay,
	CLProcedureId_PIRUpdateDelay,
    CLProcedureId_CleanEventForm,
	
	// Main Menu
	CLProcedureId_SettingsMenu,
	CLProcedureId_ServiceMenu,
	CLProcedureId_InfoForm,

	// Config Menu
	CLProcedureId_SelectionLanguageForm,
	CLProcedureId_ScreenSaverConfigForm,
	CLProcedureId_SystemDateTimeConfigForm,
	CLProcedureId_UpgradeForm,
	CLProcedureId_WeeklyMainForm,
	CLProcedureId_ClimaSettingsForm,
	CLProcedureId_SpeedModeConfigForm,
	CLProcedureId_RHConfigForm,
	CLProcedureId_PartyConfigForm,
	CLProcedureId_ServicePasswordChangeForm
};

// Funzioni per la gestione delle procedure
CLFormResult Procedure_Execute( CLProcedureId procedureId, unsigned short options );
bool Procedure_IsEnabled( CLProcedureId procedureId );

#endif

