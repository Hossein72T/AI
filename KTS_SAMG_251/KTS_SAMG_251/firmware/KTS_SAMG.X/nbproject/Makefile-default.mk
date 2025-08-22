#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/peripheral/adc/plib_adc.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/cmcc/plib_cmcc.c ../src/config/default/peripheral/efc/plib_efc.c ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/pio/plib_pio.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc1.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/KTS/CLBigFont.cpp ../src/KTS/CLSmallFont.cpp ../src/KTS/CLFonts.cpp ../src/KTS/Rtc_Pcf8563.cpp ../src/KTS/Eeprom.cpp ../src/KTS/CLKTSDefines.cpp ../src/KTS/CLKTSEeprom.cpp ../src/KTS/CLCommunicationManager.cpp ../src/KTS/CLCommunication_Driver.cpp ../src/KTS/CLSerialDriver.cpp ../src/KTS/CLCommon.cpp ../src/KTS/RFM_driver.cpp ../src/KTS/CLKTS.cpp ../src/KTS/CLForm.cpp ../src/KTS/CLDateTime.cpp ../src/KTS/CLLocalitation.cpp ../src/KTS/CLSpeedMode.cpp ../src/KTS/CLVentilationControl.cpp ../src/KTS/CLGraphics.cpp ../src/KTS/CLFranceTX.cpp ../src/KTS/CLFunction.cpp ../src/KTS/CLLCDCommon.cpp ../src/KTS/CLLanguage_DE.cpp ../src/KTS/CLLanguage_EN.cpp ../src/KTS/CLLogo.cpp ../src/KTS/CLProcedure.cpp ../src/KTS/CLLanguage_FR.cpp ../src/KTS/CLScreenSaver.cpp ../src/KTS/CLLanguage_IT.cpp ../src/KTS/CLPasswordForm.cpp ../src/KTS/CLAccessoryManagerForm.cpp ../src/KTS/CLWeekly.cpp ../src/KTS/CLMessageBoxForm.cpp ../src/KTS/CLImages.cpp ../src/KTS/CLAccessory.cpp ../src/KTS/CLBypassConfigForm.cpp ../src/KTS/CLBypass.cpp ../src/KTS/CLLanguage_NL.cpp ../src/KTS/CLLanguage_PT.cpp ../src/KTS/CLLanguage_PL.cpp ../src/KTS/CLSelectionLanguageForm.cpp ../src/KTS/CLInputConfigForm.cpp ../src/KTS/CLOutputConfigForm.cpp ../src/KTS/CLServiceMenu.cpp ../src/KTS/CLAlarm.cpp ../src/KTS/CLMenu.cpp ../src/KTS/CLLanguage_SL.cpp ../src/KTS/CLLanguage_RO.cpp ../src/KTS/CLLanguage_BG.cpp ../src/KTS/CLLanguage_HU.cpp ../src/KTS/CLLanguage_TR.cpp ../src/KTS/CLInfoForm.cpp ../src/KTS/CLSystemDateTimeConfigForm.cpp ../src/KTS/CLScreenSaverForm.cpp ../src/KTS/CLReportDebugDataForm.cpp ../src/KTS/CLReportDebugDataAdminForm.cpp ../src/KTS/CLSettingsMenu.cpp ../src/KTS/CLInputOutput.cpp ../src/KTS/CLBoxInfoConfigForm.cpp ../src/KTS/CLSelectionDateForm.cpp ../src/KTS/CLBoxInfo.cpp ../src/KTS/CLPartyConfigForm.cpp ../src/KTS/CLSpeedModeConfigForm.cpp ../src/KTS/CLSelectionTimeForm.cpp ../src/KTS/CLSelectionVentilationControlForm.cpp ../src/KTS/CLCO2ConfigForm.cpp ../src/KTS/CLCAPCalibrationProcedureForm.cpp ../src/KTS/CLSelectionSpeedForm.cpp ../src/KTS/CLVOCConfigForm.cpp ../src/KTS/CLRHConfigForm.cpp ../src/KTS/CLSelectionFranceTxClassForm.cpp ../src/KTS/CLFilterConfigForm.cpp ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp ../src/KTS/CLScreenSaverConfigForm.cpp ../src/KTS/CLTemperatureConfigForm.cpp ../src/KTS/CLHysteresisTemperatureConfigForm.cpp ../src/KTS/CLUnbalanceConfigForm.cpp ../src/KTS/CLScreenCalibrationForm.cpp CLWeeklyMainForm.cpp CLTemperature.cpp CLEndUserPasswordConfigForm.cpp CLUpgradeForm.cpp CLProbesSettingsForm.cpp CLModBusConfigForm.cpp CLTestUnitForm.cpp CLRFMSelectChannelForm.cpp CLRFMScanner.cpp CLEepromResetForm.cpp CLReferenceTSettingForm.cpp CLShowFontsForm.cpp CLDscDelayUpdateConfigForm.cpp CLPirDelayUpdateConfigForm.cpp CLWeeklyViewForm.cpp CLWeeklyEditForm.cpp CLWeeklyDaysEditForm.cpp CLPowerOffForm.cpp CLMainForm.cpp CLKTSConnectForm.cpp CLFireAlarmForm.cpp CLKTSStartupForm.cpp CLMainMenu.cpp CLAlarmsReportForm.cpp CLWarningAlarmsReportForm.cpp CLLogo_AC.cpp CLLogo_AL.cpp CLLogo_AV.cpp CLLogo_CL.cpp CLLogo_CV.cpp CLLogo_FA.cpp CLLogo_FAI.cpp CLLogo_FS.cpp CLLogo_FT.cpp CLLogo_IN.cpp CLLogo_NL.cpp CLLogo_SIG.cpp CLLogo_UE.cpp CLLogo_WE.cpp ../src/KTS/qrcodegen.c ../src/KTS/CLLogo_TL.cpp ../src/KTS/CLCleanEventForm.cpp ../src/TFTLCD/TFTLCD.cpp ../src/KTS/CLTouch.cpp ../src/main.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/60163342/plib_adc.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o ${OBJECTDIR}/_ext/60167248/plib_efc.o ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/60177924/plib_pio.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/659828752/CLBigFont.o ${OBJECTDIR}/_ext/659828752/CLSmallFont.o ${OBJECTDIR}/_ext/659828752/CLFonts.o ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o ${OBJECTDIR}/_ext/659828752/Eeprom.o ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o ${OBJECTDIR}/_ext/659828752/CLCommon.o ${OBJECTDIR}/_ext/659828752/RFM_driver.o ${OBJECTDIR}/_ext/659828752/CLKTS.o ${OBJECTDIR}/_ext/659828752/CLForm.o ${OBJECTDIR}/_ext/659828752/CLDateTime.o ${OBJECTDIR}/_ext/659828752/CLLocalitation.o ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o ${OBJECTDIR}/_ext/659828752/CLGraphics.o ${OBJECTDIR}/_ext/659828752/CLFranceTX.o ${OBJECTDIR}/_ext/659828752/CLFunction.o ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o ${OBJECTDIR}/_ext/659828752/CLLogo.o ${OBJECTDIR}/_ext/659828752/CLProcedure.o ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o ${OBJECTDIR}/_ext/659828752/CLWeekly.o ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o ${OBJECTDIR}/_ext/659828752/CLImages.o ${OBJECTDIR}/_ext/659828752/CLAccessory.o ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o ${OBJECTDIR}/_ext/659828752/CLBypass.o ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o ${OBJECTDIR}/_ext/659828752/CLAlarm.o ${OBJECTDIR}/_ext/659828752/CLMenu.o ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o ${OBJECTDIR}/_ext/659828752/CLInfoForm.o ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o ${OBJECTDIR}/_ext/659828752/CLInputOutput.o ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o ${OBJECTDIR}/CLWeeklyMainForm.o ${OBJECTDIR}/CLTemperature.o ${OBJECTDIR}/CLEndUserPasswordConfigForm.o ${OBJECTDIR}/CLUpgradeForm.o ${OBJECTDIR}/CLProbesSettingsForm.o ${OBJECTDIR}/CLModBusConfigForm.o ${OBJECTDIR}/CLTestUnitForm.o ${OBJECTDIR}/CLRFMSelectChannelForm.o ${OBJECTDIR}/CLRFMScanner.o ${OBJECTDIR}/CLEepromResetForm.o ${OBJECTDIR}/CLReferenceTSettingForm.o ${OBJECTDIR}/CLShowFontsForm.o ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o ${OBJECTDIR}/CLWeeklyViewForm.o ${OBJECTDIR}/CLWeeklyEditForm.o ${OBJECTDIR}/CLWeeklyDaysEditForm.o ${OBJECTDIR}/CLPowerOffForm.o ${OBJECTDIR}/CLMainForm.o ${OBJECTDIR}/CLKTSConnectForm.o ${OBJECTDIR}/CLFireAlarmForm.o ${OBJECTDIR}/CLKTSStartupForm.o ${OBJECTDIR}/CLMainMenu.o ${OBJECTDIR}/CLAlarmsReportForm.o ${OBJECTDIR}/CLWarningAlarmsReportForm.o ${OBJECTDIR}/CLLogo_AC.o ${OBJECTDIR}/CLLogo_AL.o ${OBJECTDIR}/CLLogo_AV.o ${OBJECTDIR}/CLLogo_CL.o ${OBJECTDIR}/CLLogo_CV.o ${OBJECTDIR}/CLLogo_FA.o ${OBJECTDIR}/CLLogo_FAI.o ${OBJECTDIR}/CLLogo_FS.o ${OBJECTDIR}/CLLogo_FT.o ${OBJECTDIR}/CLLogo_IN.o ${OBJECTDIR}/CLLogo_NL.o ${OBJECTDIR}/CLLogo_SIG.o ${OBJECTDIR}/CLLogo_UE.o ${OBJECTDIR}/CLLogo_WE.o ${OBJECTDIR}/_ext/659828752/qrcodegen.o ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o ${OBJECTDIR}/_ext/862124923/TFTLCD.o ${OBJECTDIR}/_ext/659828752/CLTouch.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/60163342/plib_adc.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o.d ${OBJECTDIR}/_ext/60167248/plib_efc.o.d ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o.d ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o.d ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o.d ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/60177924/plib_pio.o.d ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/659828752/CLBigFont.o.d ${OBJECTDIR}/_ext/659828752/CLSmallFont.o.d ${OBJECTDIR}/_ext/659828752/CLFonts.o.d ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o.d ${OBJECTDIR}/_ext/659828752/Eeprom.o.d ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o.d ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o.d ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o.d ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o.d ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o.d ${OBJECTDIR}/_ext/659828752/CLCommon.o.d ${OBJECTDIR}/_ext/659828752/RFM_driver.o.d ${OBJECTDIR}/_ext/659828752/CLKTS.o.d ${OBJECTDIR}/_ext/659828752/CLForm.o.d ${OBJECTDIR}/_ext/659828752/CLDateTime.o.d ${OBJECTDIR}/_ext/659828752/CLLocalitation.o.d ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o.d ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o.d ${OBJECTDIR}/_ext/659828752/CLGraphics.o.d ${OBJECTDIR}/_ext/659828752/CLFranceTX.o.d ${OBJECTDIR}/_ext/659828752/CLFunction.o.d ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o.d ${OBJECTDIR}/_ext/659828752/CLLogo.o.d ${OBJECTDIR}/_ext/659828752/CLProcedure.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o.d ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o.d ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o.d ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o.d ${OBJECTDIR}/_ext/659828752/CLWeekly.o.d ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o.d ${OBJECTDIR}/_ext/659828752/CLImages.o.d ${OBJECTDIR}/_ext/659828752/CLAccessory.o.d ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLBypass.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o.d ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o.d ${OBJECTDIR}/_ext/659828752/CLAlarm.o.d ${OBJECTDIR}/_ext/659828752/CLMenu.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o.d ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o.d ${OBJECTDIR}/_ext/659828752/CLInfoForm.o.d ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o.d ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o.d ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o.d ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o.d ${OBJECTDIR}/_ext/659828752/CLInputOutput.o.d ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o.d ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o.d ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o.d ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o.d ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o.d ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o.d ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o.d ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o.d ${OBJECTDIR}/CLWeeklyMainForm.o.d ${OBJECTDIR}/CLTemperature.o.d ${OBJECTDIR}/CLEndUserPasswordConfigForm.o.d ${OBJECTDIR}/CLUpgradeForm.o.d ${OBJECTDIR}/CLProbesSettingsForm.o.d ${OBJECTDIR}/CLModBusConfigForm.o.d ${OBJECTDIR}/CLTestUnitForm.o.d ${OBJECTDIR}/CLRFMSelectChannelForm.o.d ${OBJECTDIR}/CLRFMScanner.o.d ${OBJECTDIR}/CLEepromResetForm.o.d ${OBJECTDIR}/CLReferenceTSettingForm.o.d ${OBJECTDIR}/CLShowFontsForm.o.d ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o.d ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o.d ${OBJECTDIR}/CLWeeklyViewForm.o.d ${OBJECTDIR}/CLWeeklyEditForm.o.d ${OBJECTDIR}/CLWeeklyDaysEditForm.o.d ${OBJECTDIR}/CLPowerOffForm.o.d ${OBJECTDIR}/CLMainForm.o.d ${OBJECTDIR}/CLKTSConnectForm.o.d ${OBJECTDIR}/CLFireAlarmForm.o.d ${OBJECTDIR}/CLKTSStartupForm.o.d ${OBJECTDIR}/CLMainMenu.o.d ${OBJECTDIR}/CLAlarmsReportForm.o.d ${OBJECTDIR}/CLWarningAlarmsReportForm.o.d ${OBJECTDIR}/CLLogo_AC.o.d ${OBJECTDIR}/CLLogo_AL.o.d ${OBJECTDIR}/CLLogo_AV.o.d ${OBJECTDIR}/CLLogo_CL.o.d ${OBJECTDIR}/CLLogo_CV.o.d ${OBJECTDIR}/CLLogo_FA.o.d ${OBJECTDIR}/CLLogo_FAI.o.d ${OBJECTDIR}/CLLogo_FS.o.d ${OBJECTDIR}/CLLogo_FT.o.d ${OBJECTDIR}/CLLogo_IN.o.d ${OBJECTDIR}/CLLogo_NL.o.d ${OBJECTDIR}/CLLogo_SIG.o.d ${OBJECTDIR}/CLLogo_UE.o.d ${OBJECTDIR}/CLLogo_WE.o.d ${OBJECTDIR}/_ext/659828752/qrcodegen.o.d ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o.d ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o.d ${OBJECTDIR}/_ext/862124923/TFTLCD.o.d ${OBJECTDIR}/_ext/659828752/CLTouch.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/60163342/plib_adc.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o ${OBJECTDIR}/_ext/60167248/plib_efc.o ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/60177924/plib_pio.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/659828752/CLBigFont.o ${OBJECTDIR}/_ext/659828752/CLSmallFont.o ${OBJECTDIR}/_ext/659828752/CLFonts.o ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o ${OBJECTDIR}/_ext/659828752/Eeprom.o ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o ${OBJECTDIR}/_ext/659828752/CLCommon.o ${OBJECTDIR}/_ext/659828752/RFM_driver.o ${OBJECTDIR}/_ext/659828752/CLKTS.o ${OBJECTDIR}/_ext/659828752/CLForm.o ${OBJECTDIR}/_ext/659828752/CLDateTime.o ${OBJECTDIR}/_ext/659828752/CLLocalitation.o ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o ${OBJECTDIR}/_ext/659828752/CLGraphics.o ${OBJECTDIR}/_ext/659828752/CLFranceTX.o ${OBJECTDIR}/_ext/659828752/CLFunction.o ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o ${OBJECTDIR}/_ext/659828752/CLLogo.o ${OBJECTDIR}/_ext/659828752/CLProcedure.o ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o ${OBJECTDIR}/_ext/659828752/CLWeekly.o ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o ${OBJECTDIR}/_ext/659828752/CLImages.o ${OBJECTDIR}/_ext/659828752/CLAccessory.o ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o ${OBJECTDIR}/_ext/659828752/CLBypass.o ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o ${OBJECTDIR}/_ext/659828752/CLAlarm.o ${OBJECTDIR}/_ext/659828752/CLMenu.o ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o ${OBJECTDIR}/_ext/659828752/CLInfoForm.o ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o ${OBJECTDIR}/_ext/659828752/CLInputOutput.o ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o ${OBJECTDIR}/CLWeeklyMainForm.o ${OBJECTDIR}/CLTemperature.o ${OBJECTDIR}/CLEndUserPasswordConfigForm.o ${OBJECTDIR}/CLUpgradeForm.o ${OBJECTDIR}/CLProbesSettingsForm.o ${OBJECTDIR}/CLModBusConfigForm.o ${OBJECTDIR}/CLTestUnitForm.o ${OBJECTDIR}/CLRFMSelectChannelForm.o ${OBJECTDIR}/CLRFMScanner.o ${OBJECTDIR}/CLEepromResetForm.o ${OBJECTDIR}/CLReferenceTSettingForm.o ${OBJECTDIR}/CLShowFontsForm.o ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o ${OBJECTDIR}/CLWeeklyViewForm.o ${OBJECTDIR}/CLWeeklyEditForm.o ${OBJECTDIR}/CLWeeklyDaysEditForm.o ${OBJECTDIR}/CLPowerOffForm.o ${OBJECTDIR}/CLMainForm.o ${OBJECTDIR}/CLKTSConnectForm.o ${OBJECTDIR}/CLFireAlarmForm.o ${OBJECTDIR}/CLKTSStartupForm.o ${OBJECTDIR}/CLMainMenu.o ${OBJECTDIR}/CLAlarmsReportForm.o ${OBJECTDIR}/CLWarningAlarmsReportForm.o ${OBJECTDIR}/CLLogo_AC.o ${OBJECTDIR}/CLLogo_AL.o ${OBJECTDIR}/CLLogo_AV.o ${OBJECTDIR}/CLLogo_CL.o ${OBJECTDIR}/CLLogo_CV.o ${OBJECTDIR}/CLLogo_FA.o ${OBJECTDIR}/CLLogo_FAI.o ${OBJECTDIR}/CLLogo_FS.o ${OBJECTDIR}/CLLogo_FT.o ${OBJECTDIR}/CLLogo_IN.o ${OBJECTDIR}/CLLogo_NL.o ${OBJECTDIR}/CLLogo_SIG.o ${OBJECTDIR}/CLLogo_UE.o ${OBJECTDIR}/CLLogo_WE.o ${OBJECTDIR}/_ext/659828752/qrcodegen.o ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o ${OBJECTDIR}/_ext/862124923/TFTLCD.o ${OBJECTDIR}/_ext/659828752/CLTouch.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/config/default/peripheral/adc/plib_adc.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/cmcc/plib_cmcc.c ../src/config/default/peripheral/efc/plib_efc.c ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/pio/plib_pio.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc1.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/KTS/CLBigFont.cpp ../src/KTS/CLSmallFont.cpp ../src/KTS/CLFonts.cpp ../src/KTS/Rtc_Pcf8563.cpp ../src/KTS/Eeprom.cpp ../src/KTS/CLKTSDefines.cpp ../src/KTS/CLKTSEeprom.cpp ../src/KTS/CLCommunicationManager.cpp ../src/KTS/CLCommunication_Driver.cpp ../src/KTS/CLSerialDriver.cpp ../src/KTS/CLCommon.cpp ../src/KTS/RFM_driver.cpp ../src/KTS/CLKTS.cpp ../src/KTS/CLForm.cpp ../src/KTS/CLDateTime.cpp ../src/KTS/CLLocalitation.cpp ../src/KTS/CLSpeedMode.cpp ../src/KTS/CLVentilationControl.cpp ../src/KTS/CLGraphics.cpp ../src/KTS/CLFranceTX.cpp ../src/KTS/CLFunction.cpp ../src/KTS/CLLCDCommon.cpp ../src/KTS/CLLanguage_DE.cpp ../src/KTS/CLLanguage_EN.cpp ../src/KTS/CLLogo.cpp ../src/KTS/CLProcedure.cpp ../src/KTS/CLLanguage_FR.cpp ../src/KTS/CLScreenSaver.cpp ../src/KTS/CLLanguage_IT.cpp ../src/KTS/CLPasswordForm.cpp ../src/KTS/CLAccessoryManagerForm.cpp ../src/KTS/CLWeekly.cpp ../src/KTS/CLMessageBoxForm.cpp ../src/KTS/CLImages.cpp ../src/KTS/CLAccessory.cpp ../src/KTS/CLBypassConfigForm.cpp ../src/KTS/CLBypass.cpp ../src/KTS/CLLanguage_NL.cpp ../src/KTS/CLLanguage_PT.cpp ../src/KTS/CLLanguage_PL.cpp ../src/KTS/CLSelectionLanguageForm.cpp ../src/KTS/CLInputConfigForm.cpp ../src/KTS/CLOutputConfigForm.cpp ../src/KTS/CLServiceMenu.cpp ../src/KTS/CLAlarm.cpp ../src/KTS/CLMenu.cpp ../src/KTS/CLLanguage_SL.cpp ../src/KTS/CLLanguage_RO.cpp ../src/KTS/CLLanguage_BG.cpp ../src/KTS/CLLanguage_HU.cpp ../src/KTS/CLLanguage_TR.cpp ../src/KTS/CLInfoForm.cpp ../src/KTS/CLSystemDateTimeConfigForm.cpp ../src/KTS/CLScreenSaverForm.cpp ../src/KTS/CLReportDebugDataForm.cpp ../src/KTS/CLReportDebugDataAdminForm.cpp ../src/KTS/CLSettingsMenu.cpp ../src/KTS/CLInputOutput.cpp ../src/KTS/CLBoxInfoConfigForm.cpp ../src/KTS/CLSelectionDateForm.cpp ../src/KTS/CLBoxInfo.cpp ../src/KTS/CLPartyConfigForm.cpp ../src/KTS/CLSpeedModeConfigForm.cpp ../src/KTS/CLSelectionTimeForm.cpp ../src/KTS/CLSelectionVentilationControlForm.cpp ../src/KTS/CLCO2ConfigForm.cpp ../src/KTS/CLCAPCalibrationProcedureForm.cpp ../src/KTS/CLSelectionSpeedForm.cpp ../src/KTS/CLVOCConfigForm.cpp ../src/KTS/CLRHConfigForm.cpp ../src/KTS/CLSelectionFranceTxClassForm.cpp ../src/KTS/CLFilterConfigForm.cpp ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp ../src/KTS/CLScreenSaverConfigForm.cpp ../src/KTS/CLTemperatureConfigForm.cpp ../src/KTS/CLHysteresisTemperatureConfigForm.cpp ../src/KTS/CLUnbalanceConfigForm.cpp ../src/KTS/CLScreenCalibrationForm.cpp CLWeeklyMainForm.cpp CLTemperature.cpp CLEndUserPasswordConfigForm.cpp CLUpgradeForm.cpp CLProbesSettingsForm.cpp CLModBusConfigForm.cpp CLTestUnitForm.cpp CLRFMSelectChannelForm.cpp CLRFMScanner.cpp CLEepromResetForm.cpp CLReferenceTSettingForm.cpp CLShowFontsForm.cpp CLDscDelayUpdateConfigForm.cpp CLPirDelayUpdateConfigForm.cpp CLWeeklyViewForm.cpp CLWeeklyEditForm.cpp CLWeeklyDaysEditForm.cpp CLPowerOffForm.cpp CLMainForm.cpp CLKTSConnectForm.cpp CLFireAlarmForm.cpp CLKTSStartupForm.cpp CLMainMenu.cpp CLAlarmsReportForm.cpp CLWarningAlarmsReportForm.cpp CLLogo_AC.cpp CLLogo_AL.cpp CLLogo_AV.cpp CLLogo_CL.cpp CLLogo_CV.cpp CLLogo_FA.cpp CLLogo_FAI.cpp CLLogo_FS.cpp CLLogo_FT.cpp CLLogo_IN.cpp CLLogo_NL.cpp CLLogo_SIG.cpp CLLogo_UE.cpp CLLogo_WE.cpp ../src/KTS/qrcodegen.c ../src/KTS/CLLogo_TL.cpp ../src/KTS/CLCleanEventForm.cpp ../src/TFTLCD/TFTLCD.cpp ../src/KTS/CLTouch.cpp ../src/main.cpp

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATSAMG55J19
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\ATSAMG55J19.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/60163342/plib_adc.o: ../src/config/default/peripheral/adc/plib_adc.c  .generated_files/98aee401307d1c22c5a940c1a220cc908adfa4e8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc.o ../src/config/default/peripheral/adc/plib_adc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/4b25d54b9ec348260c7e52bd9d81a81013136814.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865131932/plib_cmcc.o: ../src/config/default/peripheral/cmcc/plib_cmcc.c  .generated_files/738fad5f1dd5a02c0c06cc729e6efc597bc74fae.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865131932" 
	@${RM} ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865131932/plib_cmcc.o.d" -o ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o ../src/config/default/peripheral/cmcc/plib_cmcc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167248/plib_efc.o: ../src/config/default/peripheral/efc/plib_efc.c  .generated_files/8c6b8dab3deb628451282d3d82edd95bd1e2f51e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60167248" 
	@${RM} ${OBJECTDIR}/_ext/60167248/plib_efc.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167248/plib_efc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167248/plib_efc.o.d" -o ${OBJECTDIR}/_ext/60167248/plib_efc.o ../src/config/default/peripheral/efc/plib_efc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o: ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c  .generated_files/2f29ba0f44e70a9876f2edb4a7660a337c9d0c20.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/393231230" 
	@${RM} ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o.d" -o ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o: ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c  .generated_files/c3ad8a422aab9371e7082863d3b7d919b5bdbe43.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/429438372" 
	@${RM} ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o.d" -o ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o: ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c  .generated_files/98147ad9636bf33352927b4ea3b36fd27ff0f1e2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1818436620" 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o.d" -o ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o: ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c  .generated_files/ad349113a51bc2c0ca693be4fb565562b272265.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1818436620" 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o.d" -o ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/7ee61980649ab922964a8fbd98ef80cc36e2323d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60177924/plib_pio.o: ../src/config/default/peripheral/pio/plib_pio.c  .generated_files/46f90d91e26d74ee290395714ff1d82055ff593e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60177924" 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o.d 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" -o ${OBJECTDIR}/_ext/60177924/plib_pio.o ../src/config/default/peripheral/pio/plib_pio.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/7112c33ae4f21fa7a9826e567c45e237f57aa889.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc1.o: ../src/config/default/peripheral/tc/plib_tc1.c  .generated_files/1a2b678a53159db1c0aa7996cbdd10793163b941.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ../src/config/default/peripheral/tc/plib_tc1.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/f118c6f0f41aa53cfd936e818ff08c4f52c02484.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/9ee72a67a4365cd1ed356cf07466dcc845a256b5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/20f8a8070d5d408d7dab8cb4c1f3401fc2e9f2ed.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/acc8f613214323dc54acb26c094072a384641c68.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/d547833a169d1d6ded1f3d162d72d90ab57caa52.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/c21c7a3d678e30b3b2e039ce180bab525f062e0.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/435b6587129eae4955e3a3195e9086ac466a651c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/qrcodegen.o: ../src/KTS/qrcodegen.c  .generated_files/b9d57e71bf24be498e09fb586683fbc97a68655e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/qrcodegen.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/qrcodegen.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/qrcodegen.o.d" -o ${OBJECTDIR}/_ext/659828752/qrcodegen.o ../src/KTS/qrcodegen.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/60163342/plib_adc.o: ../src/config/default/peripheral/adc/plib_adc.c  .generated_files/5a5b0e6ebdc358060e91719cd610657b4e68cd0.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc.o ../src/config/default/peripheral/adc/plib_adc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/cdafb2a03b65925b941d529b0b2765e74aab2bb2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865131932/plib_cmcc.o: ../src/config/default/peripheral/cmcc/plib_cmcc.c  .generated_files/5c8ac36a9ff22565ada1ef6c62a9dc23e7b813a4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865131932" 
	@${RM} ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865131932/plib_cmcc.o.d" -o ${OBJECTDIR}/_ext/1865131932/plib_cmcc.o ../src/config/default/peripheral/cmcc/plib_cmcc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167248/plib_efc.o: ../src/config/default/peripheral/efc/plib_efc.c  .generated_files/f49f989970c8268b9f17effa61d570a7fa263acd.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60167248" 
	@${RM} ${OBJECTDIR}/_ext/60167248/plib_efc.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167248/plib_efc.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167248/plib_efc.o.d" -o ${OBJECTDIR}/_ext/60167248/plib_efc.o ../src/config/default/peripheral/efc/plib_efc.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o: ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c  .generated_files/cbe25aba1af436a9ae1c2a051834439a7abad60.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/393231230" 
	@${RM} ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o.d" -o ${OBJECTDIR}/_ext/393231230/plib_flexcom2_spi_master.o ../src/config/default/peripheral/flexcom/spi/master/plib_flexcom2_spi_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o: ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c  .generated_files/c8e49c35e9d96b84987b486cbb04635ce6a95d3a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/429438372" 
	@${RM} ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o.d" -o ${OBJECTDIR}/_ext/429438372/plib_flexcom4_twi_master.o ../src/config/default/peripheral/flexcom/twi/master/plib_flexcom4_twi_master.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o: ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c  .generated_files/a422163d0be032999e0ba257b94ac8ea149fac9d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1818436620" 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o.d" -o ${OBJECTDIR}/_ext/1818436620/plib_flexcom3_usart.o ../src/config/default/peripheral/flexcom/usart/plib_flexcom3_usart.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o: ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c  .generated_files/d993687a13d281f37dd0273f38441e172d3fb5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1818436620" 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o.d" -o ${OBJECTDIR}/_ext/1818436620/plib_flexcom0_usart.o ../src/config/default/peripheral/flexcom/usart/plib_flexcom0_usart.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/13cec87fc6f13e38db3e31aa8ac166043b90f0a6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60177924/plib_pio.o: ../src/config/default/peripheral/pio/plib_pio.c  .generated_files/aa74dc7ce561bfed386c13ea69aae13fc18eae0b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60177924" 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o.d 
	@${RM} ${OBJECTDIR}/_ext/60177924/plib_pio.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60177924/plib_pio.o.d" -o ${OBJECTDIR}/_ext/60177924/plib_pio.o ../src/config/default/peripheral/pio/plib_pio.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/e55ee0349e416172a9e227dce74b24b5e6218fbe.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc1.o: ../src/config/default/peripheral/tc/plib_tc1.c  .generated_files/e435376072cd995d4b36b7c3ab92074a3cb8c4d9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc1.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc1.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc1.o ../src/config/default/peripheral/tc/plib_tc1.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/fd0bad2c0a965a35793113f39f779a291fddda75.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/3eac949f1b9473f25ce19184143b491e86848d03.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/83cb09a8d16e75d080795528e476f5c225d6926c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/ea12e7f37dfe70369d7767920836c36c5d276189.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/b7da707e6624d7bd5c763c447d9d0cd3e95584f3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/46aea096dc13078464d2e279454ef30e0c0896b1.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/4954ed261c7cf6b740d65a761a68dd1795dcabf4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/qrcodegen.o: ../src/KTS/qrcodegen.c  .generated_files/ebc1db94604f58e14edb42684379363c01706bea.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/qrcodegen.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/qrcodegen.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src/KTS" -I"../src/TFTLCD" -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/qrcodegen.o.d" -o ${OBJECTDIR}/_ext/659828752/qrcodegen.o ../src/KTS/qrcodegen.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/659828752/CLBigFont.o: ../src/KTS/CLBigFont.cpp  .generated_files/9ec5a7de72e89e002b896ee1d0ad4358785ea5a1.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBigFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBigFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBigFont.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBigFont.o ../src/KTS/CLBigFont.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSmallFont.o: ../src/KTS/CLSmallFont.cpp  .generated_files/179826d5f4a4f88befc927846c6b14ab2466efbb.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSmallFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSmallFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSmallFont.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSmallFont.o ../src/KTS/CLSmallFont.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFonts.o: ../src/KTS/CLFonts.cpp  .generated_files/ceae182367188b92b1da34773441fac601a4dcd9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFonts.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFonts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFonts.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFonts.o ../src/KTS/CLFonts.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o: ../src/KTS/Rtc_Pcf8563.cpp  .generated_files/e10772b29ef06f8938d19fa847e25d46bef46bd8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o.d" -o ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o ../src/KTS/Rtc_Pcf8563.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/Eeprom.o: ../src/KTS/Eeprom.cpp  .generated_files/67531b05d0335b43cd0598819b6af2879fafccf.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/Eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/Eeprom.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/Eeprom.o.d" -o ${OBJECTDIR}/_ext/659828752/Eeprom.o ../src/KTS/Eeprom.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTSDefines.o: ../src/KTS/CLKTSDefines.cpp  .generated_files/dd641250c5b7c0df915330a39c0dd74982e73b6e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTSDefines.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o ../src/KTS/CLKTSDefines.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o: ../src/KTS/CLKTSEeprom.cpp  .generated_files/4bad2e9e44888f1fcf45f45ef219392ab9d001d3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o ../src/KTS/CLKTSEeprom.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o: ../src/KTS/CLCommunicationManager.cpp  .generated_files/a15c2f611a6750897720ccfb5ccc71b60d65b3d4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o ../src/KTS/CLCommunicationManager.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o: ../src/KTS/CLCommunication_Driver.cpp  .generated_files/bb64a7d4d5587f54956669173fd2af6803d9677d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o ../src/KTS/CLCommunication_Driver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSerialDriver.o: ../src/KTS/CLSerialDriver.cpp  .generated_files/a93dee47117646b17640551ec720749f9c7b1b55.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSerialDriver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o ../src/KTS/CLSerialDriver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommon.o: ../src/KTS/CLCommon.cpp  .generated_files/88f0e23993d0551900bd4a7dc71f1dfebee1c088.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommon.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommon.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommon.o ../src/KTS/CLCommon.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/RFM_driver.o: ../src/KTS/RFM_driver.cpp  .generated_files/9b0ad248be5d384c1fcad8b7f4bba7466a2d4c27.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/RFM_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/RFM_driver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/RFM_driver.o.d" -o ${OBJECTDIR}/_ext/659828752/RFM_driver.o ../src/KTS/RFM_driver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTS.o: ../src/KTS/CLKTS.cpp  .generated_files/4526a93ce03b0ff322877b11db54153a449e5a42.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTS.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTS.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTS.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTS.o ../src/KTS/CLKTS.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLForm.o: ../src/KTS/CLForm.cpp  .generated_files/579183f8d74f5a155b9e601cc4dc2714fe5ce683.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLForm.o ../src/KTS/CLForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLDateTime.o: ../src/KTS/CLDateTime.cpp  .generated_files/6ed4fcac9636c10afe6f911c897db776aac9d062.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLDateTime.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLDateTime.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLDateTime.o.d" -o ${OBJECTDIR}/_ext/659828752/CLDateTime.o ../src/KTS/CLDateTime.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLocalitation.o: ../src/KTS/CLLocalitation.cpp  .generated_files/2bc176f2eac8c627e4aa97204ad810bac1e7ae63.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLocalitation.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLocalitation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLocalitation.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLocalitation.o ../src/KTS/CLLocalitation.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSpeedMode.o: ../src/KTS/CLSpeedMode.cpp  .generated_files/7b24a60f23e675ad0a2ae7ce74f44eacefa2c268.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSpeedMode.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o ../src/KTS/CLSpeedMode.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLVentilationControl.o: ../src/KTS/CLVentilationControl.cpp  .generated_files/a6dfc77b41db2ccd44a68978079773fd303ce05e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLVentilationControl.o.d" -o ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o ../src/KTS/CLVentilationControl.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLGraphics.o: ../src/KTS/CLGraphics.cpp  .generated_files/825e290e5efa7a72afe21d225a15a7c66a99d34b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLGraphics.o.d" -o ${OBJECTDIR}/_ext/659828752/CLGraphics.o ../src/KTS/CLGraphics.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFranceTX.o: ../src/KTS/CLFranceTX.cpp  .generated_files/978cc2645bd8108c66ccb33c19beaad4b8a82ac1.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFranceTX.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFranceTX.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFranceTX.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFranceTX.o ../src/KTS/CLFranceTX.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFunction.o: ../src/KTS/CLFunction.cpp  .generated_files/c9714fcd8bea3308ae587470e40cbcaa78994816.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFunction.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFunction.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFunction.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFunction.o ../src/KTS/CLFunction.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLCDCommon.o: ../src/KTS/CLLCDCommon.cpp  .generated_files/9de4e4d826d432071ffd4f3a492ef0f396d3487b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLCDCommon.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o ../src/KTS/CLLCDCommon.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o: ../src/KTS/CLLanguage_DE.cpp  .generated_files/7ce5a769fb17b93e80527c402de1e54cca7aacc5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o ../src/KTS/CLLanguage_DE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o: ../src/KTS/CLLanguage_EN.cpp  .generated_files/94b60731b5e0beb03864ac3d5219d37cb5d4641a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o ../src/KTS/CLLanguage_EN.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLogo.o: ../src/KTS/CLLogo.cpp  .generated_files/8d2bb136d9c62cc48197634c265b11a21345709b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLogo.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLogo.o ../src/KTS/CLLogo.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLProcedure.o: ../src/KTS/CLProcedure.cpp  .generated_files/82e01f1234f168238147d604118fcf7fd7bcbb59.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLProcedure.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLProcedure.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLProcedure.o.d" -o ${OBJECTDIR}/_ext/659828752/CLProcedure.o ../src/KTS/CLProcedure.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o: ../src/KTS/CLLanguage_FR.cpp  .generated_files/a0f330d008d6054607bd5933ecec441fd68c726d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o ../src/KTS/CLLanguage_FR.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaver.o: ../src/KTS/CLScreenSaver.cpp  .generated_files/2b029377830535a1e1d31a7d1b2cadccf8872fab.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o ../src/KTS/CLScreenSaver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o: ../src/KTS/CLLanguage_IT.cpp  .generated_files/9461b3bb79039b16f9e2f6fa863fba9ff42c333e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o ../src/KTS/CLLanguage_IT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLPasswordForm.o: ../src/KTS/CLPasswordForm.cpp  .generated_files/e41fb8607493b1a9bcc9a85916a98d7be39a6238.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLPasswordForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o ../src/KTS/CLPasswordForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o: ../src/KTS/CLAccessoryManagerForm.cpp  .generated_files/c92ad7953fb285117faeaa97fb95070127312a09.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o ../src/KTS/CLAccessoryManagerForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLWeekly.o: ../src/KTS/CLWeekly.cpp  .generated_files/d1c36f6f7c5f7b0a150d1ba16784e0d695c5b726.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLWeekly.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLWeekly.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLWeekly.o.d" -o ${OBJECTDIR}/_ext/659828752/CLWeekly.o ../src/KTS/CLWeekly.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o: ../src/KTS/CLMessageBoxForm.cpp  .generated_files/58a1d7cb41c028229eae44497d4212e789aca05f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o ../src/KTS/CLMessageBoxForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLImages.o: ../src/KTS/CLImages.cpp  .generated_files/d4fa0d299ecc6ff2a2006d2bb37115241161f3f0.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLImages.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLImages.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLImages.o.d" -o ${OBJECTDIR}/_ext/659828752/CLImages.o ../src/KTS/CLImages.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAccessory.o: ../src/KTS/CLAccessory.cpp  .generated_files/e36d75d8f2dddbd616f6ec8a1b3bea5a4e42025.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessory.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessory.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAccessory.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAccessory.o ../src/KTS/CLAccessory.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o: ../src/KTS/CLBypassConfigForm.cpp  .generated_files/432f2ae5cb3b60f09ce2dab8911e683ab05a8d91.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o ../src/KTS/CLBypassConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBypass.o: ../src/KTS/CLBypass.cpp  .generated_files/13898fb4d38974c46399c2416bbace6af18ba1f1.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypass.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypass.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBypass.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBypass.o ../src/KTS/CLBypass.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o: ../src/KTS/CLLanguage_NL.cpp  .generated_files/30fcd3a9931a94ec6065a7b9430766fd0a3ca491.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o ../src/KTS/CLLanguage_NL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o: ../src/KTS/CLLanguage_PT.cpp  .generated_files/405c5e5097a30c6ef1fc69a708a09d19f71074c4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o ../src/KTS/CLLanguage_PT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o: ../src/KTS/CLLanguage_PL.cpp  .generated_files/7e3fa48c52472a9d24b5c656ed0106f3af32e228.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o ../src/KTS/CLLanguage_PL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o: ../src/KTS/CLSelectionLanguageForm.cpp  .generated_files/7ce6d5104cfe50db170f7faedb0d5e3a5bf369bb.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o ../src/KTS/CLSelectionLanguageForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o: ../src/KTS/CLInputConfigForm.cpp  .generated_files/81e5a0055a5a7a4a9a926c3070249d9c69fb37c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o ../src/KTS/CLInputConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o: ../src/KTS/CLOutputConfigForm.cpp  .generated_files/44c44221e51b5e8f63aa25e48d5b544ef40c721f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o ../src/KTS/CLOutputConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLServiceMenu.o: ../src/KTS/CLServiceMenu.cpp  .generated_files/8a67af0b14d44a180a76dbab79ea62bf9355db09.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLServiceMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o ../src/KTS/CLServiceMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAlarm.o: ../src/KTS/CLAlarm.cpp  .generated_files/e497a380959dd34fa7891120f84eaebd93dc34d6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAlarm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAlarm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAlarm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAlarm.o ../src/KTS/CLAlarm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLMenu.o: ../src/KTS/CLMenu.cpp  .generated_files/172a9e33b01d882b7998868ce20a795698e5455.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLMenu.o ../src/KTS/CLMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o: ../src/KTS/CLLanguage_SL.cpp  .generated_files/eff0abaaff66e94730ca6d8b4d6b9401256f647f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o ../src/KTS/CLLanguage_SL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o: ../src/KTS/CLLanguage_RO.cpp  .generated_files/e3f106638d77ee77ee05ba9d8338d83a4f3de5a0.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o ../src/KTS/CLLanguage_RO.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o: ../src/KTS/CLLanguage_BG.cpp  .generated_files/2f0c6efc4c5fa7981b63c013fe3100f8bb199d35.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o ../src/KTS/CLLanguage_BG.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o: ../src/KTS/CLLanguage_HU.cpp  .generated_files/e9b9d4acf24f6bb52e0d79060ad7ee5f235601e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o ../src/KTS/CLLanguage_HU.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o: ../src/KTS/CLLanguage_TR.cpp  .generated_files/3ec18f98e305155d46fbc22c92a0476588eab54a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o ../src/KTS/CLLanguage_TR.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInfoForm.o: ../src/KTS/CLInfoForm.cpp  .generated_files/3030605bc0d762839dc368558c7b373e39993db5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInfoForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInfoForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInfoForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInfoForm.o ../src/KTS/CLInfoForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o: ../src/KTS/CLSystemDateTimeConfigForm.cpp  .generated_files/9aa2e49d6270be29a9e4a56d7e707b4ef8138586.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o ../src/KTS/CLSystemDateTimeConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o: ../src/KTS/CLScreenSaverForm.cpp  .generated_files/b3fa513228f541f79559340811d54bdc421e79fe.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o ../src/KTS/CLScreenSaverForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o: ../src/KTS/CLReportDebugDataForm.cpp  .generated_files/af73ba850e5ec6cec6a1462eabad86e9de403518.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o ../src/KTS/CLReportDebugDataForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o: ../src/KTS/CLReportDebugDataAdminForm.cpp  .generated_files/aa7df83c614e2da401a2beee662be3352b445af6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o ../src/KTS/CLReportDebugDataAdminForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o: ../src/KTS/CLSettingsMenu.cpp  .generated_files/e38b43fe9114023c01d5b328f2c0d8d3cd832b4a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o ../src/KTS/CLSettingsMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInputOutput.o: ../src/KTS/CLInputOutput.cpp  .generated_files/dfaf7dea7d63d0fd05b95a0d9cd24d174f552bd3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputOutput.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInputOutput.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInputOutput.o ../src/KTS/CLInputOutput.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o: ../src/KTS/CLBoxInfoConfigForm.cpp  .generated_files/6a6ad13b67409a2e483803dfcee24291d751a074.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o ../src/KTS/CLBoxInfoConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o: ../src/KTS/CLSelectionDateForm.cpp  .generated_files/f45bb213f76efb4c889e080336386925c8f8817a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o ../src/KTS/CLSelectionDateForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBoxInfo.o: ../src/KTS/CLBoxInfo.cpp  .generated_files/d104a931de42a347bc0086d30e6e14ed6745b120.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBoxInfo.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o ../src/KTS/CLBoxInfo.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o: ../src/KTS/CLPartyConfigForm.cpp  .generated_files/87705e27b55134bf5a4531060e7f613fbec332b2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o ../src/KTS/CLPartyConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o: ../src/KTS/CLSpeedModeConfigForm.cpp  .generated_files/23a4157af009a2979c8288f2d8c5301797388e52.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o ../src/KTS/CLSpeedModeConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o: ../src/KTS/CLSelectionTimeForm.cpp  .generated_files/c3eb7ca2f822277486024ea2b5456e319bc9117a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o ../src/KTS/CLSelectionTimeForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o: ../src/KTS/CLSelectionVentilationControlForm.cpp  .generated_files/d170256534d977e08185a6cc25efc64f9a2a99a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o ../src/KTS/CLSelectionVentilationControlForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o: ../src/KTS/CLCO2ConfigForm.cpp  .generated_files/de6b040554a36ac69c582687e142b2907251d1ba.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o ../src/KTS/CLCO2ConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o: ../src/KTS/CLCAPCalibrationProcedureForm.cpp  .generated_files/8c65c35b0f9d27e8cfed171efbb28a149e05909f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o ../src/KTS/CLCAPCalibrationProcedureForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o: ../src/KTS/CLSelectionSpeedForm.cpp  .generated_files/8eb4ffc516141cf7fc9adc1f92f26499334abe96.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o ../src/KTS/CLSelectionSpeedForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o: ../src/KTS/CLVOCConfigForm.cpp  .generated_files/f01a048c49a4457da8b35a5c06ae66c8fdd40e1c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o ../src/KTS/CLVOCConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o: ../src/KTS/CLRHConfigForm.cpp  .generated_files/e62da9f50e938a855c305be7277803ed1e16f556.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o ../src/KTS/CLRHConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o: ../src/KTS/CLSelectionFranceTxClassForm.cpp  .generated_files/a637a9eddc562fcd39cfa13f1ec2bb4e7540d6b7.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o ../src/KTS/CLSelectionFranceTxClassForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o: ../src/KTS/CLFilterConfigForm.cpp  .generated_files/aeb409f7b97b10e5b3ad1a261a9935d3e108af1c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o ../src/KTS/CLFilterConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o: ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp  .generated_files/665f2f5950a19c06f3ad74ac2bafc733494f5fc8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o: ../src/KTS/CLScreenSaverConfigForm.cpp  .generated_files/f0a92c86afc6ea0b4d0a76e6f151d014f17548ea.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o ../src/KTS/CLScreenSaverConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o: ../src/KTS/CLTemperatureConfigForm.cpp  .generated_files/50f2391d4677f8fba03cc1ec1d08ff2b4606cb7e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o ../src/KTS/CLTemperatureConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o: ../src/KTS/CLHysteresisTemperatureConfigForm.cpp  .generated_files/bc377b3fc32b4601dab78734f64629dd4fdc987a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o ../src/KTS/CLHysteresisTemperatureConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o: ../src/KTS/CLUnbalanceConfigForm.cpp  .generated_files/6f3847bc54e51d06f5189f29c404a9fd068084b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o ../src/KTS/CLUnbalanceConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o: ../src/KTS/CLScreenCalibrationForm.cpp  .generated_files/d7a2c775009ffa52ab28499749785d67a4909d04.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o ../src/KTS/CLScreenCalibrationForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyMainForm.o: CLWeeklyMainForm.cpp  .generated_files/583344a1df654401381e5ab0da28a4e926401d8b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyMainForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyMainForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyMainForm.o.d" -o ${OBJECTDIR}/CLWeeklyMainForm.o CLWeeklyMainForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLTemperature.o: CLTemperature.cpp  .generated_files/476d0e6da6396955d28dfa3f28303f17269e6f56.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLTemperature.o.d 
	@${RM} ${OBJECTDIR}/CLTemperature.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLTemperature.o.d" -o ${OBJECTDIR}/CLTemperature.o CLTemperature.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLEndUserPasswordConfigForm.o: CLEndUserPasswordConfigForm.cpp  .generated_files/396f447f01abe26b02d9bb9fa2944080d1171684.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLEndUserPasswordConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLEndUserPasswordConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLEndUserPasswordConfigForm.o.d" -o ${OBJECTDIR}/CLEndUserPasswordConfigForm.o CLEndUserPasswordConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLUpgradeForm.o: CLUpgradeForm.cpp  .generated_files/c4cf3ddd813f0681a28b97884f8e4b3b125cbd05.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLUpgradeForm.o.d 
	@${RM} ${OBJECTDIR}/CLUpgradeForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLUpgradeForm.o.d" -o ${OBJECTDIR}/CLUpgradeForm.o CLUpgradeForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLProbesSettingsForm.o: CLProbesSettingsForm.cpp  .generated_files/ccc2ad911f9140e92894bb6a8fd3aae4118ff7ed.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLProbesSettingsForm.o.d 
	@${RM} ${OBJECTDIR}/CLProbesSettingsForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLProbesSettingsForm.o.d" -o ${OBJECTDIR}/CLProbesSettingsForm.o CLProbesSettingsForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLModBusConfigForm.o: CLModBusConfigForm.cpp  .generated_files/a51adb769937dd5d2592bb42cdaa24b8cc12f431.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLModBusConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLModBusConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLModBusConfigForm.o.d" -o ${OBJECTDIR}/CLModBusConfigForm.o CLModBusConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLTestUnitForm.o: CLTestUnitForm.cpp  .generated_files/a3e4d444d76d4950c67ed2b50eea4f54dad5f2bf.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLTestUnitForm.o.d 
	@${RM} ${OBJECTDIR}/CLTestUnitForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLTestUnitForm.o.d" -o ${OBJECTDIR}/CLTestUnitForm.o CLTestUnitForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLRFMSelectChannelForm.o: CLRFMSelectChannelForm.cpp  .generated_files/8ad70a08005b44e2f204b5c4c9776dc2eb6369cf.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLRFMSelectChannelForm.o.d 
	@${RM} ${OBJECTDIR}/CLRFMSelectChannelForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLRFMSelectChannelForm.o.d" -o ${OBJECTDIR}/CLRFMSelectChannelForm.o CLRFMSelectChannelForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLRFMScanner.o: CLRFMScanner.cpp  .generated_files/5485969d7f75d9fb99999c93f840a0ef6f9c2455.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLRFMScanner.o.d 
	@${RM} ${OBJECTDIR}/CLRFMScanner.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLRFMScanner.o.d" -o ${OBJECTDIR}/CLRFMScanner.o CLRFMScanner.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLEepromResetForm.o: CLEepromResetForm.cpp  .generated_files/df68af4480e258bf48a698be687b8997655e2788.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLEepromResetForm.o.d 
	@${RM} ${OBJECTDIR}/CLEepromResetForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLEepromResetForm.o.d" -o ${OBJECTDIR}/CLEepromResetForm.o CLEepromResetForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLReferenceTSettingForm.o: CLReferenceTSettingForm.cpp  .generated_files/7a2ebe244a444232a1237610aa1223a04f8c4eb9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLReferenceTSettingForm.o.d 
	@${RM} ${OBJECTDIR}/CLReferenceTSettingForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLReferenceTSettingForm.o.d" -o ${OBJECTDIR}/CLReferenceTSettingForm.o CLReferenceTSettingForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLShowFontsForm.o: CLShowFontsForm.cpp  .generated_files/3aeb85fc40a963de2769503bd483fd27135c0765.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLShowFontsForm.o.d 
	@${RM} ${OBJECTDIR}/CLShowFontsForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLShowFontsForm.o.d" -o ${OBJECTDIR}/CLShowFontsForm.o CLShowFontsForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLDscDelayUpdateConfigForm.o: CLDscDelayUpdateConfigForm.cpp  .generated_files/18020833b82bb52204a1b3351fa958fc1454330c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLDscDelayUpdateConfigForm.o.d" -o ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o CLDscDelayUpdateConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLPirDelayUpdateConfigForm.o: CLPirDelayUpdateConfigForm.cpp  .generated_files/61dc13e1e3938c815799841e4f1e72a1d291acdc.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLPirDelayUpdateConfigForm.o.d" -o ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o CLPirDelayUpdateConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyViewForm.o: CLWeeklyViewForm.cpp  .generated_files/3ac0af23f633ed945fed22bca46dfbd6e2af8572.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyViewForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyViewForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyViewForm.o.d" -o ${OBJECTDIR}/CLWeeklyViewForm.o CLWeeklyViewForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyEditForm.o: CLWeeklyEditForm.cpp  .generated_files/2f727f170a48560bd30e0107a7a4d2bf38ec565f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyEditForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyEditForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyEditForm.o.d" -o ${OBJECTDIR}/CLWeeklyEditForm.o CLWeeklyEditForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyDaysEditForm.o: CLWeeklyDaysEditForm.cpp  .generated_files/ea59c37a181822d2fe95f9809fc2012a15782797.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyDaysEditForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyDaysEditForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyDaysEditForm.o.d" -o ${OBJECTDIR}/CLWeeklyDaysEditForm.o CLWeeklyDaysEditForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLPowerOffForm.o: CLPowerOffForm.cpp  .generated_files/a35fa99bc9596fa193c1e60280cfdacb886a7a44.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLPowerOffForm.o.d 
	@${RM} ${OBJECTDIR}/CLPowerOffForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLPowerOffForm.o.d" -o ${OBJECTDIR}/CLPowerOffForm.o CLPowerOffForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLMainForm.o: CLMainForm.cpp  .generated_files/deaf428ae4fe45d124490b990340cf3e203c99ff.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLMainForm.o.d 
	@${RM} ${OBJECTDIR}/CLMainForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLMainForm.o.d" -o ${OBJECTDIR}/CLMainForm.o CLMainForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLKTSConnectForm.o: CLKTSConnectForm.cpp  .generated_files/faaab8b8cb77154b7c90a3c649350a98692eb194.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLKTSConnectForm.o.d 
	@${RM} ${OBJECTDIR}/CLKTSConnectForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLKTSConnectForm.o.d" -o ${OBJECTDIR}/CLKTSConnectForm.o CLKTSConnectForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLFireAlarmForm.o: CLFireAlarmForm.cpp  .generated_files/eb17cf286ba85964977cb2e8b78b76dfaac48c08.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLFireAlarmForm.o.d 
	@${RM} ${OBJECTDIR}/CLFireAlarmForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLFireAlarmForm.o.d" -o ${OBJECTDIR}/CLFireAlarmForm.o CLFireAlarmForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLKTSStartupForm.o: CLKTSStartupForm.cpp  .generated_files/4b0594422687f6d0415f41b39dec347ff5c21d78.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLKTSStartupForm.o.d 
	@${RM} ${OBJECTDIR}/CLKTSStartupForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLKTSStartupForm.o.d" -o ${OBJECTDIR}/CLKTSStartupForm.o CLKTSStartupForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLMainMenu.o: CLMainMenu.cpp  .generated_files/93c70c83468d438e4641655d8cd1a3b4317ea4f5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLMainMenu.o.d 
	@${RM} ${OBJECTDIR}/CLMainMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLMainMenu.o.d" -o ${OBJECTDIR}/CLMainMenu.o CLMainMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLAlarmsReportForm.o: CLAlarmsReportForm.cpp  .generated_files/59934b12fd1186c8851e1ee68bfc4258759ebfc5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLAlarmsReportForm.o.d 
	@${RM} ${OBJECTDIR}/CLAlarmsReportForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLAlarmsReportForm.o.d" -o ${OBJECTDIR}/CLAlarmsReportForm.o CLAlarmsReportForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWarningAlarmsReportForm.o: CLWarningAlarmsReportForm.cpp  .generated_files/814783ba48e178aa00d0cc874709cc870e2fc048.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWarningAlarmsReportForm.o.d 
	@${RM} ${OBJECTDIR}/CLWarningAlarmsReportForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWarningAlarmsReportForm.o.d" -o ${OBJECTDIR}/CLWarningAlarmsReportForm.o CLWarningAlarmsReportForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AC.o: CLLogo_AC.cpp  .generated_files/b92e07cf04c14fcdc78bcd60b381ef94a9e91796.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AC.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AC.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AC.o.d" -o ${OBJECTDIR}/CLLogo_AC.o CLLogo_AC.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AL.o: CLLogo_AL.cpp  .generated_files/e28e14dff026277c9301ffd56cea9078917479e2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AL.o.d" -o ${OBJECTDIR}/CLLogo_AL.o CLLogo_AL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AV.o: CLLogo_AV.cpp  .generated_files/5f2deb0682778acb7333056b6c1f4a6b8cb141b2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AV.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AV.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AV.o.d" -o ${OBJECTDIR}/CLLogo_AV.o CLLogo_AV.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_CL.o: CLLogo_CL.cpp  .generated_files/f40491d4f26ce9b6a4dde1350f80cf9cd7d86ee9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_CL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_CL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_CL.o.d" -o ${OBJECTDIR}/CLLogo_CL.o CLLogo_CL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_CV.o: CLLogo_CV.cpp  .generated_files/8673c6e67dd5ce5a9a8329728a1eee53a14e6508.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_CV.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_CV.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_CV.o.d" -o ${OBJECTDIR}/CLLogo_CV.o CLLogo_CV.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FA.o: CLLogo_FA.cpp  .generated_files/b169b45fcd0bdf58108bd08672a12dd8a2bafa3b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FA.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FA.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FA.o.d" -o ${OBJECTDIR}/CLLogo_FA.o CLLogo_FA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FAI.o: CLLogo_FAI.cpp  .generated_files/a92f614655a12397088acc81a43d4b3be212e10c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FAI.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FAI.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FAI.o.d" -o ${OBJECTDIR}/CLLogo_FAI.o CLLogo_FAI.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FS.o: CLLogo_FS.cpp  .generated_files/569013241ddcc586bd94833728fd8cce858d2997.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FS.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FS.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FS.o.d" -o ${OBJECTDIR}/CLLogo_FS.o CLLogo_FS.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FT.o: CLLogo_FT.cpp  .generated_files/b53a02addcb2da0f0a72b08657b739e469745356.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FT.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FT.o.d" -o ${OBJECTDIR}/CLLogo_FT.o CLLogo_FT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_IN.o: CLLogo_IN.cpp  .generated_files/83c0237ff9f61ff30da4f2aa20c7edce6718e8cb.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_IN.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_IN.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_IN.o.d" -o ${OBJECTDIR}/CLLogo_IN.o CLLogo_IN.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_NL.o: CLLogo_NL.cpp  .generated_files/459930ee4f09766dddd6729bba4f76c635623412.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_NL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_NL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_NL.o.d" -o ${OBJECTDIR}/CLLogo_NL.o CLLogo_NL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_SIG.o: CLLogo_SIG.cpp  .generated_files/c9ec214f54578c330ae3a6738f37d77d49f6ee2b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_SIG.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_SIG.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_SIG.o.d" -o ${OBJECTDIR}/CLLogo_SIG.o CLLogo_SIG.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_UE.o: CLLogo_UE.cpp  .generated_files/529a03eb1c7cd616acb78747fd154c33bd27e439.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_UE.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_UE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_UE.o.d" -o ${OBJECTDIR}/CLLogo_UE.o CLLogo_UE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_WE.o: CLLogo_WE.cpp  .generated_files/8e67331d6b52187f625519274b44a68e66376585.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_WE.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_WE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_WE.o.d" -o ${OBJECTDIR}/CLLogo_WE.o CLLogo_WE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLogo_TL.o: ../src/KTS/CLLogo_TL.cpp  .generated_files/5d8892706c712a7329794391044d59b63bf372be.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLogo_TL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o ../src/KTS/CLLogo_TL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o: ../src/KTS/CLCleanEventForm.cpp  .generated_files/caa8a9fef15af0ae60826ed2ac34c7ed8944619d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o ../src/KTS/CLCleanEventForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/862124923/TFTLCD.o: ../src/TFTLCD/TFTLCD.cpp  .generated_files/df7615cd3c0cfe80d48cd2e30ebe2b51f13bf70c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/862124923" 
	@${RM} ${OBJECTDIR}/_ext/862124923/TFTLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/862124923/TFTLCD.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/862124923/TFTLCD.o.d" -o ${OBJECTDIR}/_ext/862124923/TFTLCD.o ../src/TFTLCD/TFTLCD.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLTouch.o: ../src/KTS/CLTouch.cpp  .generated_files/78ca6270130d466cff6995f0616131362047def2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTouch.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTouch.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLTouch.o.d" -o ${OBJECTDIR}/_ext/659828752/CLTouch.o ../src/KTS/CLTouch.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.cpp  .generated_files/b2e96dad3b076c0ae061339502f930cd6436cc9a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/659828752/CLBigFont.o: ../src/KTS/CLBigFont.cpp  .generated_files/b80c1607ecf77f3b60c6bea19decd86ca21301fa.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBigFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBigFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBigFont.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBigFont.o ../src/KTS/CLBigFont.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSmallFont.o: ../src/KTS/CLSmallFont.cpp  .generated_files/78738a3b3f74329883d58682eba591ab653ab5c6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSmallFont.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSmallFont.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSmallFont.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSmallFont.o ../src/KTS/CLSmallFont.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFonts.o: ../src/KTS/CLFonts.cpp  .generated_files/3bb86113f13b5e0de74b2e606f44a30b9a6623b4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFonts.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFonts.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFonts.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFonts.o ../src/KTS/CLFonts.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o: ../src/KTS/Rtc_Pcf8563.cpp  .generated_files/69994080dcbe22adbd40b5e8d0bd857ca456f93.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o.d" -o ${OBJECTDIR}/_ext/659828752/Rtc_Pcf8563.o ../src/KTS/Rtc_Pcf8563.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/Eeprom.o: ../src/KTS/Eeprom.cpp  .generated_files/199e0daac4ea79b7ffae86cd0318d03f023b650e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/Eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/Eeprom.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/Eeprom.o.d" -o ${OBJECTDIR}/_ext/659828752/Eeprom.o ../src/KTS/Eeprom.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTSDefines.o: ../src/KTS/CLKTSDefines.cpp  .generated_files/ad3429c1ca3601068f043e887e11566cdf8b71ab.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTSDefines.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTSDefines.o ../src/KTS/CLKTSDefines.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o: ../src/KTS/CLKTSEeprom.cpp  .generated_files/21fd004b91f21d80e7b5d72eb70e4876a91cee67.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTSEeprom.o ../src/KTS/CLKTSEeprom.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o: ../src/KTS/CLCommunicationManager.cpp  .generated_files/c6f16e93a962ebbd1c6e304113eceb860759f642.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommunicationManager.o ../src/KTS/CLCommunicationManager.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o: ../src/KTS/CLCommunication_Driver.cpp  .generated_files/61bbec6f2e979fe96455781f3a26422d39ac4c39.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommunication_Driver.o ../src/KTS/CLCommunication_Driver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSerialDriver.o: ../src/KTS/CLSerialDriver.cpp  .generated_files/307e484e631c21cddfe7d2468a76b89d402d2e0e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSerialDriver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSerialDriver.o ../src/KTS/CLSerialDriver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCommon.o: ../src/KTS/CLCommon.cpp  .generated_files/7807cb5549c1bfd56b7609c4438e48efc60f0b20.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCommon.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCommon.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCommon.o ../src/KTS/CLCommon.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/RFM_driver.o: ../src/KTS/RFM_driver.cpp  .generated_files/66385c8a676bbf9479507981ff4e608f473d0fea.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/RFM_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/RFM_driver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/RFM_driver.o.d" -o ${OBJECTDIR}/_ext/659828752/RFM_driver.o ../src/KTS/RFM_driver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLKTS.o: ../src/KTS/CLKTS.cpp  .generated_files/67b9a94db9b9d81a3c46237cc076374eb8fdd03.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTS.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLKTS.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLKTS.o.d" -o ${OBJECTDIR}/_ext/659828752/CLKTS.o ../src/KTS/CLKTS.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLForm.o: ../src/KTS/CLForm.cpp  .generated_files/eff46f04d71046cca7bfb052c1843a09c384bbb5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLForm.o ../src/KTS/CLForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLDateTime.o: ../src/KTS/CLDateTime.cpp  .generated_files/baa940e9b9327813b2cb18c8b8b201ac99735b8b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLDateTime.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLDateTime.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLDateTime.o.d" -o ${OBJECTDIR}/_ext/659828752/CLDateTime.o ../src/KTS/CLDateTime.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLocalitation.o: ../src/KTS/CLLocalitation.cpp  .generated_files/f5c96438c6d2988fbd25b283bdb822c11dff0f5f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLocalitation.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLocalitation.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLocalitation.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLocalitation.o ../src/KTS/CLLocalitation.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSpeedMode.o: ../src/KTS/CLSpeedMode.cpp  .generated_files/3e955c9d38db429bc8a787a75f7716ab39939960.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSpeedMode.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSpeedMode.o ../src/KTS/CLSpeedMode.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLVentilationControl.o: ../src/KTS/CLVentilationControl.cpp  .generated_files/8c17f35772e1881adeeef71aeb49bb2d534bb1e4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLVentilationControl.o.d" -o ${OBJECTDIR}/_ext/659828752/CLVentilationControl.o ../src/KTS/CLVentilationControl.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLGraphics.o: ../src/KTS/CLGraphics.cpp  .generated_files/8b91a2fca0cf0d37f2d31ea17840af202f18f4a8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLGraphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLGraphics.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLGraphics.o.d" -o ${OBJECTDIR}/_ext/659828752/CLGraphics.o ../src/KTS/CLGraphics.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFranceTX.o: ../src/KTS/CLFranceTX.cpp  .generated_files/77ce1fbcdf0a169be5b077aed8282e4064debad3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFranceTX.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFranceTX.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFranceTX.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFranceTX.o ../src/KTS/CLFranceTX.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFunction.o: ../src/KTS/CLFunction.cpp  .generated_files/529728df4eb55d99038f2012d35a86e1b8acebc3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFunction.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFunction.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFunction.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFunction.o ../src/KTS/CLFunction.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLCDCommon.o: ../src/KTS/CLLCDCommon.cpp  .generated_files/34eb647b4d6fd8b917c415f125c96bd3d5ee0a74.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLCDCommon.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLCDCommon.o ../src/KTS/CLLCDCommon.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o: ../src/KTS/CLLanguage_DE.cpp  .generated_files/7ae9c6f284d45e1da7724d174c7f5dedde3c1362.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_DE.o ../src/KTS/CLLanguage_DE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o: ../src/KTS/CLLanguage_EN.cpp  .generated_files/248e2ecf0efac7618a8847ff6d13e045d3d40d08.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_EN.o ../src/KTS/CLLanguage_EN.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLogo.o: ../src/KTS/CLLogo.cpp  .generated_files/31d0992abe8cd8362b515897d23c879cb6ea86e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLogo.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLogo.o ../src/KTS/CLLogo.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLProcedure.o: ../src/KTS/CLProcedure.cpp  .generated_files/64ab58cc8d576f44ebb66ed4ce65b02d2efac32c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLProcedure.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLProcedure.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLProcedure.o.d" -o ${OBJECTDIR}/_ext/659828752/CLProcedure.o ../src/KTS/CLProcedure.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o: ../src/KTS/CLLanguage_FR.cpp  .generated_files/1b4a0a01573685f05941e28ac76f9b983841253c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_FR.o ../src/KTS/CLLanguage_FR.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaver.o: ../src/KTS/CLScreenSaver.cpp  .generated_files/72bbeb6566191f36e4816a348a42edb5cdc46da7.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaver.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaver.o ../src/KTS/CLScreenSaver.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o: ../src/KTS/CLLanguage_IT.cpp  .generated_files/a6f3ec1d3d6acf93965850fd0f1a4a2e93a11b26.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_IT.o ../src/KTS/CLLanguage_IT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLPasswordForm.o: ../src/KTS/CLPasswordForm.cpp  .generated_files/45549e89411b3f3d7b45e035d4b5cf3d6aa7649b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLPasswordForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLPasswordForm.o ../src/KTS/CLPasswordForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o: ../src/KTS/CLAccessoryManagerForm.cpp  .generated_files/39863dd92ee9c2ade36cc15924f5c09b277f35e6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAccessoryManagerForm.o ../src/KTS/CLAccessoryManagerForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLWeekly.o: ../src/KTS/CLWeekly.cpp  .generated_files/5f76a635a2a4af82dd1638a38bab8b47b8a0ab02.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLWeekly.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLWeekly.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLWeekly.o.d" -o ${OBJECTDIR}/_ext/659828752/CLWeekly.o ../src/KTS/CLWeekly.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o: ../src/KTS/CLMessageBoxForm.cpp  .generated_files/ebf0523cb7759a8a496e4dbd82c521416f5f73e2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLMessageBoxForm.o ../src/KTS/CLMessageBoxForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLImages.o: ../src/KTS/CLImages.cpp  .generated_files/5216fe66d41f6b3e5f0a315d42db0049693296a2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLImages.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLImages.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLImages.o.d" -o ${OBJECTDIR}/_ext/659828752/CLImages.o ../src/KTS/CLImages.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAccessory.o: ../src/KTS/CLAccessory.cpp  .generated_files/fc67ebbba7511ded53aea22441e696104c996945.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessory.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAccessory.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAccessory.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAccessory.o ../src/KTS/CLAccessory.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o: ../src/KTS/CLBypassConfigForm.cpp  .generated_files/f8724087e4a12542e2925c664182e8c73e165fa2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBypassConfigForm.o ../src/KTS/CLBypassConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBypass.o: ../src/KTS/CLBypass.cpp  .generated_files/5df466adc97d17cf02e7f80a5457f76ff7153563.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypass.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBypass.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBypass.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBypass.o ../src/KTS/CLBypass.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o: ../src/KTS/CLLanguage_NL.cpp  .generated_files/2e53d976c0220684e80c4136e79271dc334a2686.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_NL.o ../src/KTS/CLLanguage_NL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o: ../src/KTS/CLLanguage_PT.cpp  .generated_files/3743d6bea7f752da72eaf869cb554a676e74736d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_PT.o ../src/KTS/CLLanguage_PT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o: ../src/KTS/CLLanguage_PL.cpp  .generated_files/46f0e2444d0d8c5c4df5fc702610f94e4302ca34.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_PL.o ../src/KTS/CLLanguage_PL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o: ../src/KTS/CLSelectionLanguageForm.cpp  .generated_files/fdbdc5cb6af5aaf47af5a1dc9f38348220807100.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionLanguageForm.o ../src/KTS/CLSelectionLanguageForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o: ../src/KTS/CLInputConfigForm.cpp  .generated_files/2eea45dd6182a8af5973bdd780b27b3968ea0652.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInputConfigForm.o ../src/KTS/CLInputConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o: ../src/KTS/CLOutputConfigForm.cpp  .generated_files/6dd8f9bcb7100cfc44d4dfe9ba661437ad00a3aa.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLOutputConfigForm.o ../src/KTS/CLOutputConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLServiceMenu.o: ../src/KTS/CLServiceMenu.cpp  .generated_files/d4227d4080de6fe75e3c84de6e81b684854ec788.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLServiceMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLServiceMenu.o ../src/KTS/CLServiceMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLAlarm.o: ../src/KTS/CLAlarm.cpp  .generated_files/6478a74774c5afee7f97ffdce9aa9cd453b4c586.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAlarm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLAlarm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLAlarm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLAlarm.o ../src/KTS/CLAlarm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLMenu.o: ../src/KTS/CLMenu.cpp  .generated_files/97647dbccc6697ceb79c77c2b0d123d78ad83c1a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLMenu.o ../src/KTS/CLMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o: ../src/KTS/CLLanguage_SL.cpp  .generated_files/ee333594eb659715e876ce8d1e4f121671a2988f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_SL.o ../src/KTS/CLLanguage_SL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o: ../src/KTS/CLLanguage_RO.cpp  .generated_files/152308af43b99411f151abd69a1d7b14c1b8e97f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_RO.o ../src/KTS/CLLanguage_RO.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o: ../src/KTS/CLLanguage_BG.cpp  .generated_files/990c2a0008464b1ec72b127ce4d090ed6d461a58.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_BG.o ../src/KTS/CLLanguage_BG.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o: ../src/KTS/CLLanguage_HU.cpp  .generated_files/3c180ab6c1500b826c9c69977b58f64360c8fd4b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_HU.o ../src/KTS/CLLanguage_HU.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o: ../src/KTS/CLLanguage_TR.cpp  .generated_files/f06fa76ef15f82d0842a97091d6790af0616d673.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLanguage_TR.o ../src/KTS/CLLanguage_TR.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInfoForm.o: ../src/KTS/CLInfoForm.cpp  .generated_files/67e8c3107003c79f2804eb4bfe9cc72a900c784a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInfoForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInfoForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInfoForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInfoForm.o ../src/KTS/CLInfoForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o: ../src/KTS/CLSystemDateTimeConfigForm.cpp  .generated_files/4d163a8e305f2875131d40300da82909162c0cb6.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSystemDateTimeConfigForm.o ../src/KTS/CLSystemDateTimeConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o: ../src/KTS/CLScreenSaverForm.cpp  .generated_files/14e8b4abb8844b9e04938816d8307d7d0faf7b0.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaverForm.o ../src/KTS/CLScreenSaverForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o: ../src/KTS/CLReportDebugDataForm.cpp  .generated_files/4d4fb241fb4045dc2e4bfb309d0a0c0ceb9a323b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataForm.o ../src/KTS/CLReportDebugDataForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o: ../src/KTS/CLReportDebugDataAdminForm.cpp  .generated_files/12d7ca22a35dd5e6c19e7282492ca71ff34354b5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLReportDebugDataAdminForm.o ../src/KTS/CLReportDebugDataAdminForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o: ../src/KTS/CLSettingsMenu.cpp  .generated_files/62c1c5ff0c6ba786fff210d3ae191f70b452635b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSettingsMenu.o ../src/KTS/CLSettingsMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLInputOutput.o: ../src/KTS/CLInputOutput.cpp  .generated_files/8c5e720b9ccdc773c671c060b2211e41f8bc8931.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputOutput.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLInputOutput.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLInputOutput.o.d" -o ${OBJECTDIR}/_ext/659828752/CLInputOutput.o ../src/KTS/CLInputOutput.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o: ../src/KTS/CLBoxInfoConfigForm.cpp  .generated_files/69740e0234327e3731f21fd95999b0fb058cf010.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBoxInfoConfigForm.o ../src/KTS/CLBoxInfoConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o: ../src/KTS/CLSelectionDateForm.cpp  .generated_files/be9b45a90e7e9e8ab2c8cec1101c5fcf9a67dc71.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionDateForm.o ../src/KTS/CLSelectionDateForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLBoxInfo.o: ../src/KTS/CLBoxInfo.cpp  .generated_files/4500b4813443c653c91bc7080b43910c06280e77.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLBoxInfo.o.d" -o ${OBJECTDIR}/_ext/659828752/CLBoxInfo.o ../src/KTS/CLBoxInfo.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o: ../src/KTS/CLPartyConfigForm.cpp  .generated_files/897f8254a97eec2a132a245f663937c38dbe8553.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLPartyConfigForm.o ../src/KTS/CLPartyConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o: ../src/KTS/CLSpeedModeConfigForm.cpp  .generated_files/4c1f2ed5bed8eb5550657e1c589a61b26e95732f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSpeedModeConfigForm.o ../src/KTS/CLSpeedModeConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o: ../src/KTS/CLSelectionTimeForm.cpp  .generated_files/f6ac4720dda3bbda74abf117f833a8811c5b018a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionTimeForm.o ../src/KTS/CLSelectionTimeForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o: ../src/KTS/CLSelectionVentilationControlForm.cpp  .generated_files/19333f36fc16107195e3b276b8c8f98480194a8a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionVentilationControlForm.o ../src/KTS/CLSelectionVentilationControlForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o: ../src/KTS/CLCO2ConfigForm.cpp  .generated_files/92934585e743cab0ac303f6f25fe33768a544ae8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCO2ConfigForm.o ../src/KTS/CLCO2ConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o: ../src/KTS/CLCAPCalibrationProcedureForm.cpp  .generated_files/1e93490ac312a1c9282828a0ad75883a3a084d9c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCAPCalibrationProcedureForm.o ../src/KTS/CLCAPCalibrationProcedureForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o: ../src/KTS/CLSelectionSpeedForm.cpp  .generated_files/53a6412aa6e9207a4b8202e4b87b57be2fe40e2b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionSpeedForm.o ../src/KTS/CLSelectionSpeedForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o: ../src/KTS/CLVOCConfigForm.cpp  .generated_files/e25ea913e5d9e2fd93a2c19f06e0ad1ec51f8ef2.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLVOCConfigForm.o ../src/KTS/CLVOCConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o: ../src/KTS/CLRHConfigForm.cpp  .generated_files/3437dee0059e6e7b615457eea33c2c2a8094cff9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLRHConfigForm.o ../src/KTS/CLRHConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o: ../src/KTS/CLSelectionFranceTxClassForm.cpp  .generated_files/473ba0c84d5e02d77025b81c8433c904949f77fa.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionFranceTxClassForm.o ../src/KTS/CLSelectionFranceTxClassForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o: ../src/KTS/CLFilterConfigForm.cpp  .generated_files/2b06ae322e6a76badba99d3e015ced09d316153e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLFilterConfigForm.o ../src/KTS/CLFilterConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o: ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp  .generated_files/6c3776d2dcbd7287219d97b0f7a2acf87ada9fa8.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLSelectionAirFlowSpeed_ThreeSpeedForm.o ../src/KTS/CLSelectionAirFlowSpeed_ThreeSpeedForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o: ../src/KTS/CLScreenSaverConfigForm.cpp  .generated_files/13bffcc4a5517d40e07a95e240b8884b78b1fee5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenSaverConfigForm.o ../src/KTS/CLScreenSaverConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o: ../src/KTS/CLTemperatureConfigForm.cpp  .generated_files/51b0067dd94d2a2e2c40ced213299cc85d96ecb4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLTemperatureConfigForm.o ../src/KTS/CLTemperatureConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o: ../src/KTS/CLHysteresisTemperatureConfigForm.cpp  .generated_files/ccaa4b1f3aafb81e4768699c7aa99f22e5c24ffe.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLHysteresisTemperatureConfigForm.o ../src/KTS/CLHysteresisTemperatureConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o: ../src/KTS/CLUnbalanceConfigForm.cpp  .generated_files/769c9ba941a4b5dfdb0bfcb26f10aaf09954e9ec.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLUnbalanceConfigForm.o ../src/KTS/CLUnbalanceConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o: ../src/KTS/CLScreenCalibrationForm.cpp  .generated_files/f2dd545089c9322eb3643c636641203dbc2c70da.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLScreenCalibrationForm.o ../src/KTS/CLScreenCalibrationForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyMainForm.o: CLWeeklyMainForm.cpp  .generated_files/68e166ae26bc475647e2c54a481eb62bad759a6b.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyMainForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyMainForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyMainForm.o.d" -o ${OBJECTDIR}/CLWeeklyMainForm.o CLWeeklyMainForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLTemperature.o: CLTemperature.cpp  .generated_files/af39c892ff56c66163a2b66c503a4cad1f412b20.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLTemperature.o.d 
	@${RM} ${OBJECTDIR}/CLTemperature.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLTemperature.o.d" -o ${OBJECTDIR}/CLTemperature.o CLTemperature.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLEndUserPasswordConfigForm.o: CLEndUserPasswordConfigForm.cpp  .generated_files/337e238be7def52c34ccf70b75eaa3336fa6137c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLEndUserPasswordConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLEndUserPasswordConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLEndUserPasswordConfigForm.o.d" -o ${OBJECTDIR}/CLEndUserPasswordConfigForm.o CLEndUserPasswordConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLUpgradeForm.o: CLUpgradeForm.cpp  .generated_files/fd8248f2688dd67a827c481308480b130506e4eb.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLUpgradeForm.o.d 
	@${RM} ${OBJECTDIR}/CLUpgradeForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLUpgradeForm.o.d" -o ${OBJECTDIR}/CLUpgradeForm.o CLUpgradeForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLProbesSettingsForm.o: CLProbesSettingsForm.cpp  .generated_files/2b6a1c26c39827ccf15a1bd3805013d74cc32794.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLProbesSettingsForm.o.d 
	@${RM} ${OBJECTDIR}/CLProbesSettingsForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLProbesSettingsForm.o.d" -o ${OBJECTDIR}/CLProbesSettingsForm.o CLProbesSettingsForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLModBusConfigForm.o: CLModBusConfigForm.cpp  .generated_files/e0fb636fc1f708e237a7d3cabe1e4bf86ef9d8de.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLModBusConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLModBusConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLModBusConfigForm.o.d" -o ${OBJECTDIR}/CLModBusConfigForm.o CLModBusConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLTestUnitForm.o: CLTestUnitForm.cpp  .generated_files/99f15292e9e527daa23b11d77d011f10e14e1c9c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLTestUnitForm.o.d 
	@${RM} ${OBJECTDIR}/CLTestUnitForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLTestUnitForm.o.d" -o ${OBJECTDIR}/CLTestUnitForm.o CLTestUnitForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLRFMSelectChannelForm.o: CLRFMSelectChannelForm.cpp  .generated_files/26e71ba76c85bd72a1372938a35470cad12efaa5.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLRFMSelectChannelForm.o.d 
	@${RM} ${OBJECTDIR}/CLRFMSelectChannelForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLRFMSelectChannelForm.o.d" -o ${OBJECTDIR}/CLRFMSelectChannelForm.o CLRFMSelectChannelForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLRFMScanner.o: CLRFMScanner.cpp  .generated_files/3ae9c96d05ec8eabe7e64af60e9b2413de709125.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLRFMScanner.o.d 
	@${RM} ${OBJECTDIR}/CLRFMScanner.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLRFMScanner.o.d" -o ${OBJECTDIR}/CLRFMScanner.o CLRFMScanner.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLEepromResetForm.o: CLEepromResetForm.cpp  .generated_files/aad99edc4ad7ce3dc077d882dae82d834807de52.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLEepromResetForm.o.d 
	@${RM} ${OBJECTDIR}/CLEepromResetForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLEepromResetForm.o.d" -o ${OBJECTDIR}/CLEepromResetForm.o CLEepromResetForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLReferenceTSettingForm.o: CLReferenceTSettingForm.cpp  .generated_files/d8bbc145d62de42a5d1844417838e87aacd9a831.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLReferenceTSettingForm.o.d 
	@${RM} ${OBJECTDIR}/CLReferenceTSettingForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLReferenceTSettingForm.o.d" -o ${OBJECTDIR}/CLReferenceTSettingForm.o CLReferenceTSettingForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLShowFontsForm.o: CLShowFontsForm.cpp  .generated_files/5f46e3995e27e6cdf3d3d1ef55f65f0e7b2a43c4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLShowFontsForm.o.d 
	@${RM} ${OBJECTDIR}/CLShowFontsForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLShowFontsForm.o.d" -o ${OBJECTDIR}/CLShowFontsForm.o CLShowFontsForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLDscDelayUpdateConfigForm.o: CLDscDelayUpdateConfigForm.cpp  .generated_files/5acd62a8c0f3b879599fe8164c8111f1880acc7a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLDscDelayUpdateConfigForm.o.d" -o ${OBJECTDIR}/CLDscDelayUpdateConfigForm.o CLDscDelayUpdateConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLPirDelayUpdateConfigForm.o: CLPirDelayUpdateConfigForm.cpp  .generated_files/1f6aa204ae5e6d60169ec372131de45bfbc9c306.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o.d 
	@${RM} ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLPirDelayUpdateConfigForm.o.d" -o ${OBJECTDIR}/CLPirDelayUpdateConfigForm.o CLPirDelayUpdateConfigForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyViewForm.o: CLWeeklyViewForm.cpp  .generated_files/cd5acd746fcdc05bbf90b59e510a7cc5f586383a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyViewForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyViewForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyViewForm.o.d" -o ${OBJECTDIR}/CLWeeklyViewForm.o CLWeeklyViewForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyEditForm.o: CLWeeklyEditForm.cpp  .generated_files/e0937565c6bc73ee7384af4380d458e1bf1a6a6c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyEditForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyEditForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyEditForm.o.d" -o ${OBJECTDIR}/CLWeeklyEditForm.o CLWeeklyEditForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWeeklyDaysEditForm.o: CLWeeklyDaysEditForm.cpp  .generated_files/8cb64ca9cbc7bc16cda161a88ff69002c33efeba.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWeeklyDaysEditForm.o.d 
	@${RM} ${OBJECTDIR}/CLWeeklyDaysEditForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWeeklyDaysEditForm.o.d" -o ${OBJECTDIR}/CLWeeklyDaysEditForm.o CLWeeklyDaysEditForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLPowerOffForm.o: CLPowerOffForm.cpp  .generated_files/48f38ae7f86fde274947faa2fed52fbef34a0c29.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLPowerOffForm.o.d 
	@${RM} ${OBJECTDIR}/CLPowerOffForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLPowerOffForm.o.d" -o ${OBJECTDIR}/CLPowerOffForm.o CLPowerOffForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLMainForm.o: CLMainForm.cpp  .generated_files/9cca027770c9c22a2673027f34880f34c7a7bffc.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLMainForm.o.d 
	@${RM} ${OBJECTDIR}/CLMainForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLMainForm.o.d" -o ${OBJECTDIR}/CLMainForm.o CLMainForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLKTSConnectForm.o: CLKTSConnectForm.cpp  .generated_files/e344cff78264dfde5ea71826bb206d2937f4b67f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLKTSConnectForm.o.d 
	@${RM} ${OBJECTDIR}/CLKTSConnectForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLKTSConnectForm.o.d" -o ${OBJECTDIR}/CLKTSConnectForm.o CLKTSConnectForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLFireAlarmForm.o: CLFireAlarmForm.cpp  .generated_files/c2c943301a1bb1a1cedcc0d8120a638bd345d1fc.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLFireAlarmForm.o.d 
	@${RM} ${OBJECTDIR}/CLFireAlarmForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLFireAlarmForm.o.d" -o ${OBJECTDIR}/CLFireAlarmForm.o CLFireAlarmForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLKTSStartupForm.o: CLKTSStartupForm.cpp  .generated_files/1da252a2eb27057fd58dfdbd5fdbaf60c7efa718.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLKTSStartupForm.o.d 
	@${RM} ${OBJECTDIR}/CLKTSStartupForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLKTSStartupForm.o.d" -o ${OBJECTDIR}/CLKTSStartupForm.o CLKTSStartupForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLMainMenu.o: CLMainMenu.cpp  .generated_files/1341f6094b90064a7322ea0a78530853cdefbbc9.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLMainMenu.o.d 
	@${RM} ${OBJECTDIR}/CLMainMenu.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLMainMenu.o.d" -o ${OBJECTDIR}/CLMainMenu.o CLMainMenu.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLAlarmsReportForm.o: CLAlarmsReportForm.cpp  .generated_files/7926d8bca38f4085dfc6ee0b667495c911de88d7.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLAlarmsReportForm.o.d 
	@${RM} ${OBJECTDIR}/CLAlarmsReportForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLAlarmsReportForm.o.d" -o ${OBJECTDIR}/CLAlarmsReportForm.o CLAlarmsReportForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLWarningAlarmsReportForm.o: CLWarningAlarmsReportForm.cpp  .generated_files/e001faa927d81419722459d196cd09af6659a55f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLWarningAlarmsReportForm.o.d 
	@${RM} ${OBJECTDIR}/CLWarningAlarmsReportForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLWarningAlarmsReportForm.o.d" -o ${OBJECTDIR}/CLWarningAlarmsReportForm.o CLWarningAlarmsReportForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AC.o: CLLogo_AC.cpp  .generated_files/e00eb144f6f554f156ccc2ed39c965525057d446.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AC.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AC.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AC.o.d" -o ${OBJECTDIR}/CLLogo_AC.o CLLogo_AC.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AL.o: CLLogo_AL.cpp  .generated_files/afa4d4d55ba62c434d5acf360f8a4f1575ca9fcf.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AL.o.d" -o ${OBJECTDIR}/CLLogo_AL.o CLLogo_AL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_AV.o: CLLogo_AV.cpp  .generated_files/a35c76c0e07ffaf9191646f15178bf66b8a2711d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_AV.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_AV.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_AV.o.d" -o ${OBJECTDIR}/CLLogo_AV.o CLLogo_AV.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_CL.o: CLLogo_CL.cpp  .generated_files/e176eede3e9178c00b1259a156374ed5cf64b3ff.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_CL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_CL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_CL.o.d" -o ${OBJECTDIR}/CLLogo_CL.o CLLogo_CL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_CV.o: CLLogo_CV.cpp  .generated_files/8b4028e0604f82a59ad5756ba03237bca452d349.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_CV.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_CV.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_CV.o.d" -o ${OBJECTDIR}/CLLogo_CV.o CLLogo_CV.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FA.o: CLLogo_FA.cpp  .generated_files/61013a97e2c886007b1f874d924cca21fb563185.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FA.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FA.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FA.o.d" -o ${OBJECTDIR}/CLLogo_FA.o CLLogo_FA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FAI.o: CLLogo_FAI.cpp  .generated_files/a88a52e89fd6d3a36ad3a1064c799c119373c42f.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FAI.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FAI.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FAI.o.d" -o ${OBJECTDIR}/CLLogo_FAI.o CLLogo_FAI.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FS.o: CLLogo_FS.cpp  .generated_files/9f4ad2b418451ed5b0cee7850fbcfd88215ea706.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FS.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FS.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FS.o.d" -o ${OBJECTDIR}/CLLogo_FS.o CLLogo_FS.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_FT.o: CLLogo_FT.cpp  .generated_files/d778a6860cb910c2b82b2cbef944e6b5425dce57.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_FT.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_FT.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_FT.o.d" -o ${OBJECTDIR}/CLLogo_FT.o CLLogo_FT.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_IN.o: CLLogo_IN.cpp  .generated_files/cd163cee18fe9f28f87704065d0917d6fe501e95.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_IN.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_IN.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_IN.o.d" -o ${OBJECTDIR}/CLLogo_IN.o CLLogo_IN.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_NL.o: CLLogo_NL.cpp  .generated_files/c03afc6c61615f6b857330aa5d34153f889e8a3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_NL.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_NL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_NL.o.d" -o ${OBJECTDIR}/CLLogo_NL.o CLLogo_NL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_SIG.o: CLLogo_SIG.cpp  .generated_files/f420866c1681842a59f3c4a9a6b3c3e254b7ee2d.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_SIG.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_SIG.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_SIG.o.d" -o ${OBJECTDIR}/CLLogo_SIG.o CLLogo_SIG.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_UE.o: CLLogo_UE.cpp  .generated_files/1236084102ee6a04f6c00d3a9d55987f3afce768.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_UE.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_UE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_UE.o.d" -o ${OBJECTDIR}/CLLogo_UE.o CLLogo_UE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/CLLogo_WE.o: CLLogo_WE.cpp  .generated_files/3d9be4c9e2dff01a6a56a70a2f9bba8b7ca4045c.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CLLogo_WE.o.d 
	@${RM} ${OBJECTDIR}/CLLogo_WE.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/CLLogo_WE.o.d" -o ${OBJECTDIR}/CLLogo_WE.o CLLogo_WE.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLLogo_TL.o: ../src/KTS/CLLogo_TL.cpp  .generated_files/931f1b481905bc1acd58c6318d50b50bd6a726de.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLLogo_TL.o.d" -o ${OBJECTDIR}/_ext/659828752/CLLogo_TL.o ../src/KTS/CLLogo_TL.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o: ../src/KTS/CLCleanEventForm.cpp  .generated_files/6006af35da9c74f14ed9b79cc6b2114ad863085a.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o.d" -o ${OBJECTDIR}/_ext/659828752/CLCleanEventForm.o ../src/KTS/CLCleanEventForm.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/862124923/TFTLCD.o: ../src/TFTLCD/TFTLCD.cpp  .generated_files/35120e4e9c78700d26889fc662c2ce2b5ba7b2a3.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/862124923" 
	@${RM} ${OBJECTDIR}/_ext/862124923/TFTLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/862124923/TFTLCD.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/862124923/TFTLCD.o.d" -o ${OBJECTDIR}/_ext/862124923/TFTLCD.o ../src/TFTLCD/TFTLCD.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/659828752/CLTouch.o: ../src/KTS/CLTouch.cpp  .generated_files/90e0ec51026a9f36d4e9b6faf5763164ffb7f52e.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/659828752" 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTouch.o.d 
	@${RM} ${OBJECTDIR}/_ext/659828752/CLTouch.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/659828752/CLTouch.o.d" -o ${OBJECTDIR}/_ext/659828752/CLTouch.o ../src/KTS/CLTouch.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.cpp  .generated_files/b3afbd85dbc8c00529524330de4c842775ecffe4.flag .generated_files/fda157d761823eca48ca4b068ff6d14cb714db22.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src/KTS" -I"../src/TFTLCD" -frtti -fexceptions -fno-check-new -fenforce-eh-specs -ffunction-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMG55J19_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samg55" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMG55J19.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=10000,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samg55"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMG55J19.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10000,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samg55"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/KTS_SAMG.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
