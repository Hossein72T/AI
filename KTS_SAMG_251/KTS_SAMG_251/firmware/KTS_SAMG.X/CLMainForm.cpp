#include "CLMainForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLTouch.h"
#include "CLMainMenu.h"
#include "CLImages.h"
#include "CLBoxInfo.h"
#include "CLAlarm.h"
#include "CLAlarmsReportForm.h"
#include "CLWarningAlarmsReportForm.h"
#include "CLFunction.h"
#include "CLSpeedMode.h"
#include "CLVentilationControl.h"
#include "CLFranceTX.h"
#include "CLWeekly.h"
#include "CLAccessory.h"
#include "CLInputOutput.h"
#include "CLServiceMenu.h"
#include "CLCommunication_Driver.h"
#include "CLTemperatureConfigForm.h"

// Main Rectangles
#define	CLMainForm_Main_PowerOffButtonRectangle				7, 38, 68, 104
#define	CLMainForm_Main_DemoTextRectangle					86, 60, 163, 82
#define	CLMainForm_Main_MenuButtonRectangle					3, 198, 143, 237

#define	CLMainForm_Main_ErrorIconRectangle					150, 198, 189, 237
#define	CLMainForm_Main_WarningIconRectangle				195, 198, 234, 237
#define	CLMainForm_Main_DateTimePoint						238, 200

#define	CLMainForm_Main_RHIconIconRectangle					7, 4, 38, 35
#define	CLMainForm_Main_CO2IconIconRectangle				40, 4, 71, 35
#define	CLMainForm_Main_VOCIconIconRectangle				73, 4, 104, 35
#define	CLMainForm_Main_RFMSignalIconRectangle				106, 4, 137, 35
#define	CLMainForm_Main_SummerWinterIconRectangle			139, 4, 170, 35
#define	CLMainForm_Main_WeeklyIconRectangle					145, 38, 165, 58
#define	CLMainForm_Main_DSCIconIconRectangle				106, 38, 137, 69

#define	CLMainForm_AirFlow_FrameRectangle					184, 6, 312, 185

// BoxInfo Rectangle
#define	CLBoxInfo_Rectangle									7, 109, 176, 185

// Stepless Mode Rectangles
#define	CLMainForm_Stepless_FrameRectangle					184, 6, 312, 185
#define	CLMainForm_Stepless_UpButtonRectangle				253, 15, 293, 55
#define	CLMainForm_Stepless_DownButtonRectangle				253, 114, 293, 154
#define	CLMainForm_Stepless_ProgressBarRectangle			195, 15, 234, 154
#define	CLMainForm_Stepless_ValueTextPoint					194, 161
#define	CLMainForm_Stepless_ModePoint                       188, 161
#define	CLMainForm_Stepless_ModePoint_Rectangle             188, 155, 205, 178

// ThreeSpeed Mode Rectangles
#define	CLMainForm_ThreeSpeed_FrameRectangle				184, 6, 312, 185
#define	CLMainForm_ThreeSpeed_Speed1ButtonRectangle			255, 111, 304, 154
#define	CLMainForm_ThreeSpeed_Speed2ButtonRectangle			255, 62, 304, 105
#define	CLMainForm_ThreeSpeed_Speed3ButtonRectangle			255, 13, 304, 56
#define	CLMainForm_ThreeSpeed_ProgressBarRectangle			192, 13, 231, 154
#define	CLMainForm_ThreeSpeed_ValueTextPoint				192, 161

// FranceTx Mode Rectangles
#define	CLMainForm_FranceTx_FrameRectangle					184, 6, 312, 185
#define	CLMainForm_FranceTx_Speed1ButtonRectangle			218, 15, 280, 64
#define	CLMainForm_FranceTx_Speed2ButtonRectangle			218, 73, 280, 122
#define	CLMainForm_FranceTx_TextValuePoint					194, 161
#define	CLMainForm_FranceTx_TextUMPoint						254, 163

// ExternalControl Mode Rectangles
#define	CLMainForm_ExternalControl_FrameRectangle			184, 6, 312, 185
#define	CLMainForm_ExternalControl_ProgressBarRectangle		226, 48, 270, 156
#define	CLMainForm_ExternalControl_TitleFrameRectangle		192, 13, 306, 42
#define	CLMainForm_ExternalControl_TextValuePoint			193, 162
#define	CLMainForm_ExternalControl_TextValueLength			6

// Weekly Mode Rectangles
#define	CLMainForm_Weekly_FrameRectangle					184, 6, 312, 174
#define	CLMainForm_Weekly_DataFrameRectangle				184, 6, 312, 117
#define	CLMainForm_Weekly_UnbalanceFrameRectangle			230, 133, 309, 174
#define	CLMainForm_Weekly_TemperatureIconRectangle			191, 129, 220, 158
#define	CLMainForm_Weekly_TemperatureValueTextPoint			188, 163
#define	CLMainForm_Weekly_TemperatureValueTextLength		4
#define	CLMainForm_Weekly_SupplyUnbalanceRectangle			231, 139, 268, 151
#define	CLMainForm_Weekly_ExtractUnbalanceRectangle			270, 139, 307, 151
#define	CLMainForm_Weekly_UnbalanceTextPoint				231, 153
#define	CLMainForm_Weekly_UnbalanceTextLength				9

#define	CLMainForm_Weekly_DataProgramFrameRectangle			184, 124, 312, 184

#define	CLMainForm_Weekly_ThreeSpeed_ProgressBarRectangle	212, 13, 241, 90
#define	CLMainForm_Weekly_ThreeSpeed_Speed3BarRectangle		260, 13, 289, 35
#define	CLMainForm_Weekly_ThreeSpeed_Speed2BarRectangle		260, 40, 289, 62
#define	CLMainForm_Weekly_ThreeSpeed_Speed1BarRectangle		260, 68, 289, 90
#define	CLMainForm_Weekly_ThreeSpeed_TextValuePoint			195, 96
#define	CLMainForm_Weekly_ThreeSpeed_TextValueLength		13

#define	CLMainForm_Weekly_FranceTX_Speed2BarRectangle		240, 13, 302, 47
#define	CLMainForm_Weekly_FranceTX_Speed1BarRectangle		240, 56, 302, 90
#define	CLMainForm_Weekly_FranceTX_TextValuePoint			195, 96
#define	CLMainForm_Weekly_FranceTX_TextValueLength			13

// Fire Mode Rectangles
#define	CLMainForm_Fire_FrameRectangle						184, 6, 312, 185
#define	CLMainForm_Fire_ProgressBarRectangle				195, 15, 234, 154
#define	CLMainForm_Fire_ValueTextPoint						194, 161

// Boost Mode Rectangles
#define	CLMainForm_Boost_FrameRectangle						184, 6, 312, 185

extern bool Debounce;
bool Mode_Caps_Capr = false;

CLFormResult CLMainForm_Open()
{
	CLMainForm	form;

	return form.Open();
}

// =============================================================================
// CLMainForm [class]
// -----------------------------------------------------------------------------
CLMainForm::CLMainForm()
{
	m_PowerOffButtonRectangle.Set( CLMainForm_Main_PowerOffButtonRectangle );
	m_MenuButtonRectangle.Set( CLMainForm_Main_MenuButtonRectangle );

	m_Stepless_UpButtonRectangle.Set( CLMainForm_Stepless_UpButtonRectangle );
	m_Stepless_DownButtonRectangle.Set( CLMainForm_Stepless_DownButtonRectangle );

	m_ThreeSpeed_Speed1ButtonRectangle.Set( CLMainForm_ThreeSpeed_Speed1ButtonRectangle );
	m_ThreeSpeed_Speed2ButtonRectangle.Set( CLMainForm_ThreeSpeed_Speed2ButtonRectangle );
	m_ThreeSpeed_Speed3ButtonRectangle.Set( CLMainForm_ThreeSpeed_Speed3ButtonRectangle );

#ifdef FRANCETX_ENABLED
	m_FranceTx_Speed1ButtonRectangle.Set( CLMainForm_FranceTx_Speed1ButtonRectangle );
	m_FranceTx_Speed2ButtonRectangle.Set( CLMainForm_FranceTx_Speed2ButtonRectangle );
#endif
	m_ErrorIconRectangle.Set( CLMainForm_Main_ErrorIconRectangle );
	m_WarningIconRectangle.Set( CLMainForm_Main_WarningIconRectangle );
	m_RHIconRectangle.Set( CLMainForm_Main_RHIconIconRectangle );
	m_CO2IconRectangle.Set( CLMainForm_Main_CO2IconIconRectangle );
	m_VOCIconRectangle.Set( CLMainForm_Main_VOCIconIconRectangle );
	m_SummerWinterIconRectangle.Set( CLMainForm_Main_SummerWinterIconRectangle );
	m_DSCIconRectangle.Set( CLMainForm_Main_DSCIconIconRectangle );
    m_Caps_Capr_Rectangle.Set ( CLMainForm_ThreeSpeed_ProgressBarRectangle );

	m_Stepless_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 20, 1 );

	m_BoxInfo.SetRectangle( CLBoxInfo_Rectangle );
}

CLFormResult CLMainForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;
	unsigned long	displayDatePreviousMilliseconds = millis();
	unsigned long	blinkIconMilliseconds = millis();
#if KTS_DEBUG == 1
	CLRectangle		suspendTXButtonRectangle( 0, 0, 20, 20 );
#endif

	//analogWrite( pBACKLIGHT, HIGH_BRIGHTESS );
    TC0_CH1_CompareASet (HIGH_BRIGHTESS);

	m_RunningMode							= CLRunningMode_Nothing;
	m_Stepless_WriteValue_InProgress		= false;
	m_Stepless_WriteValue_TimerMilliseconds	= millis();

	SetState( CLState_Initializing );
	SetRunningMode( CLRunningMode_Nothing );
	SetState( CLState_Running );

	RenderPage();
    Caps_Capr_RenderDynamicObject();

	while (true)
	{

		// Se l'unità è in fire alarm o richiede un riarmo, allora esce
		if (IsFireAlarm() || gRDEeprom.manual_Reset)
		{
			gKTSGlobal.RunningMode	= CLKTSRunningMode_FireAlarm;
			formResult				= CLFormResult_None;
			break;
		}

		// Controlla che se l'unità è in power off, allora esce
		if (gRDEeprom.Set_Power_ON == CLKTSPowerMode_Off)
		{
			gKTSGlobal.RunningMode	= CLKTSRunningMode_PowerOff;
			formResult				= CLFormResult_None;
			break;
		}

		// Nel caso in cui si è connessi in RFM e non si riceve una risposta da più di un minuto
		// significa connessione persa, ritorna al form di connessione
		if (CLKTS::IsMissingRFMSignal())
		{
			gKTSGlobal.RunningMode	= CLKTSRunningMode_Initializing;
			formResult				= CLFormResult_Ok;
			break;
		}

		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		// Visualizza eventualmente l'icona dell'allarme, se è presente un allarme
		if (m_CurrentInAlarm != (!gKTSGlobal.InAlarm ? 1 : 2))
		{
			if (gKTSGlobal.InAlarm)
				StatusIcon_DisplayError( m_ErrorIconRectangle.GetX1(), m_ErrorIconRectangle.GetY1() );
			else
				CLGraphics::DrawBox( m_ErrorIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );

			m_CurrentInAlarm	= (!gKTSGlobal.InAlarm ? 1 : 2);
		}

		// Visualizza l'icona del warning, se presente un allarme di warning
		if (m_CurrentFilterInAlarm != (!gKTSGlobal.FilterInAlarm ? 1 : 2))
		{
			if (gKTSGlobal.FilterInAlarm)
				StatusIcon_DisplayWarning( m_WarningIconRectangle.GetX1(), m_WarningIconRectangle.GetY1() );
			else
				CLGraphics::DrawBox( m_WarningIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );

			m_CurrentFilterInAlarm	= (!gKTSGlobal.FilterInAlarm ? 1 : 2);
		}

		// RH Max
		if (KTSStatusUnit_IsRHMax( gKTSData.Status_Unit ))
			CLGraphics::DrawBoxWithDrawer( m_RHIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &RHImage );
		else
			CLGraphics::DrawBox( m_RHIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );

		// CO2 Max
		if (KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ))
			CLGraphics::DrawBoxWithDrawer( m_CO2IconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &CO2Image );
		else
			CLGraphics::DrawBox( m_CO2IconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );

		// VOC Max
		if (KTSStatusUnit_IsVOCMax( gKTSData.Status_Unit ))
			CLGraphics::DrawBoxWithDrawer( m_VOCIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &VOCImage );
		else
			CLGraphics::DrawBox( m_VOCIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );
		
		// DSC
		//if ( (gKTSDebugData.Dsc_Status & 0x02 ) == 0x02 )
		  if ( (gKTSData.DSC_Status & 0x02 ) == 0x02 )
			CLGraphics::DrawBoxWithDrawer( m_DSCIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &DSCImage );
		else
			CLGraphics::DrawBox( m_DSCIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );
		
		// Winter/Summer
		if (Function_IsEnabled( ENAB_HEATING ) && Accessory_HasHeather())
		{
			if (gKTSDebugData.Heater_Status & 0x04)
			{
				if (millis() - blinkIconMilliseconds >= 500 || millis() < blinkIconMilliseconds)
				{
					if ((blinkIconMilliseconds / 500) & 0x01)
					{
						CLGraphics::DrawBoxWithDrawer( m_SummerWinterIconRectangle,
							CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &WinterImage );
					}
					else
					{
						CLGraphics::DrawBox( m_SummerWinterIconRectangle,
							CLGraphicStyleOptions_Default, RGBColor_Black );
					}
					blinkIconMilliseconds	= millis();
				}
			}
			else
			{
				CLGraphics::DrawBoxWithDrawer( m_SummerWinterIconRectangle,
					CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &WinterImage );
			}
		}
		else
		if (Function_IsEnabled( ENAB_COOLING ) && Accessory_HasCooler())
		{
			if (Accessory_HasHeather() && gKTSDebugData.Heater_Status & 0x04)
			{
				if (millis() - blinkIconMilliseconds >= 500 || millis() < blinkIconMilliseconds)
				{
					if ((blinkIconMilliseconds / 500) & 0x01)
					{
						CLGraphics::DrawBoxWithDrawer( m_SummerWinterIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &SummerImage );
					}
					else
					{
						CLGraphics::DrawBox( m_SummerWinterIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );
					}
					blinkIconMilliseconds	= millis();
				}
			}
			else
			{
				CLGraphics::DrawBoxWithDrawer( m_SummerWinterIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, &SummerImage );
			}
		}
		else
			CLGraphics::DrawBox( m_SummerWinterIconRectangle, CLGraphicStyleOptions_Default, RGBColor_Black );

		// Icona Wireless
		if (gKTSGlobal.ComLinkType == BY_SERIAL_0)
		{
			CLGraphics::DrawBox( CLRectangle( CLMainForm_Main_RFMSignalIconRectangle ),
				CLGraphicStyleOptions_Default,
				RGBColor_Black );
		}
		else
		{
			CLRectangle	rfmSignalIconRectangle	= CLRectangle( CLMainForm_Main_RFMSignalIconRectangle );

			CLLCDCommon::DrawRFMSignalIcon( rfmSignalIconRectangle.GetX1(), rfmSignalIconRectangle.GetY1(),
				sdata_wi.level_signal );
		}

		// Visualizza la data/ora
		if(gRDEeprom.Type_func != CLKTSType_BASIC)
		{
			if (millis() - displayDatePreviousMilliseconds >= 1000 ||
				millis() < displayDatePreviousMilliseconds)
			{
				CLLCDCommon::DrawDateTimeBox( CLMainForm_Main_DateTimePoint );
				displayDatePreviousMilliseconds	= millis();
			}
		}

		// Aggiorna il Box Info
		m_BoxInfo.Process();

		// Aggiorna il running mode
		RunningMode_Process();

		// Aggiorna il lo stepless Mode
		Stepless_WriteValue_Process();

		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Suspend TX
#if KTS_DEBUG == 1
			if (suspendTXButtonRectangle.Contains( touchX, touchY ))
			{
				unsigned long	waitTimeSeconds	= CLDateTime::GetNow().GetTotalSeconds();

				WaitForTouchRelease();

				if (CLDateTime::GetNow().GetTotalSeconds() - waitTimeSeconds > 3)
					gKTSGlobal.KTSDebug_SuspendTX	= !gKTSGlobal.KTSDebug_SuspendTX;
			}
			else
#endif
			if (m_BoxInfo.GetRectangle().Contains( touchX, touchY ))
			{
				Procedure_Execute( CLProcedureId_BoxInfoConfigForm, CLFormOption_ShowWriteMesssages_All | CLFormOption_GoBackAfterWrite );
				RenderPage();
			}
			else
            // switch between CAPR and CAPS settings    
            if ( m_Caps_Capr_Rectangle.Contains(touchX, touchY ))
            {
                 if ( !Mode_Caps_Capr )
                     Mode_Caps_Capr = true;
                 else
                    Mode_Caps_Capr = false; 
                Caps_Capr_RenderDynamicObject();
                WaitForTouchRelease();
            }
            else
			// PowerOff Button
			if (m_PowerOffButtonRectangle.Contains( touchX, touchY ) && m_RunningMode != CLRunningMode_Weekly)
			{
				CLLCDCommon::WaitButton( m_PowerOffButtonRectangle );

				if (CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_Off ))
				{
					formResult	= CLFormResult_Ok;
					Debounce = true;
					break;
				}

				RenderPage();
			}
			else
			// Menu Button
			if (m_MenuButtonRectangle.Contains( touchX, touchY ))
			{
				CLProcedureId	procedureId;

				CLLCDCommon::WaitButton( m_MenuButtonRectangle );

				if (CLMainMenu_Open( procedureId ) == CLFormResult_Ok)
					Procedure_Execute( procedureId, CLFormOption_Default );

				m_RunningMode	= CLRunningMode_Nothing;
				RenderPage();
			}
			else
			// Error Icon
			if (gKTSGlobal.InAlarm && m_ErrorIconRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ErrorIconRectangle );

				CLAlarmsReportForm_Open( CLFormOption_ShowWriteMesssages_None );

				RenderPage();
			}
			else
			// Warning Icon
			if (gKTSGlobal.FilterInAlarm && m_WarningIconRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_WarningIconRectangle );

				CLWarningAlarmsReportForm_Open( CLFormOption_ShowWriteMesssages_All );
				RenderPage();
			}
			else
			// Summer/Winter Icon
			if (m_SummerWinterIconRectangle.Contains( touchX, touchY )
				&& ((Function_IsEnabled( ENAB_HEATING ) && Accessory_HasHeather())
				|| (Function_IsEnabled( ENAB_COOLING ) && Accessory_HasCooler())))
			{
				CLLCDCommon::WaitButton( m_SummerWinterIconRectangle );

				CLTemperatureConfigForm_Open( CLFormOption_ShowWriteMesssages_All | CLFormOption_GoHomeAfterWrite,
					CLTemperatureConfigFormOption_Mode_Auto );
				RenderPage();
			}
			else
			// ThreeSpeed Mode
			if (m_RunningMode == CLRunningMode_ThreeSpeed && gKTSGlobal.DisableTX != 'D')
			{
				if (m_ThreeSpeed_Speed1ButtonRectangle.Contains( touchX, touchY ) &&
					(gRDEeprom.sel_idxStepMotors) != 0)
				{
					CLLCDCommon::WaitButton( m_ThreeSpeed_Speed1ButtonRectangle );

					if (ThreeSpeed_WriteValue( 0 ))
						ThreeSpeed_RenderDynamicObject();
				}
				else
				if (m_ThreeSpeed_Speed2ButtonRectangle.Contains( touchX, touchY ) &&
					(gRDEeprom.sel_idxStepMotors) != 1)
				{
					CLLCDCommon::WaitButton( m_ThreeSpeed_Speed2ButtonRectangle );

					if (ThreeSpeed_WriteValue( 1 ))
						ThreeSpeed_RenderDynamicObject();
				}
				else
				if (m_ThreeSpeed_Speed3ButtonRectangle.Contains( touchX, touchY ) &&
					gRDEeprom.sel_idxStepMotors != 2)
				{
					CLLCDCommon::WaitButton( m_ThreeSpeed_Speed3ButtonRectangle );

					if (ThreeSpeed_WriteValue( 2 ))
						ThreeSpeed_RenderDynamicObject();
				}
				else
					WaitForTouchRelease();
			}
			else
			// Stepless Mode
			if (m_RunningMode == CLRunningMode_Stepless && gKTSGlobal.DisableTX != 'D')
			{
				if (m_Stepless_UpButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_Stepless_UpButtonRectangle );

					m_Stepless_ProgressiveTouchUpDown.Reset();
					while (m_Stepless_ProgressiveTouchUpDown.InWhile())
					{
						if (m_Stepless_ProgressiveTouchUpDown.CanIncrement())
							Stepless_SetValue( m_Stepless_Value + m_Stepless_IncValue );
					}

					CLLCDCommon::WaitButton_Unpressed( m_Stepless_UpButtonRectangle );
				}
				else
				if (m_Stepless_DownButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_Stepless_DownButtonRectangle );

					m_Stepless_ProgressiveTouchUpDown.Reset();
					while (m_Stepless_ProgressiveTouchUpDown.InWhile())
					{
						if (m_Stepless_ProgressiveTouchUpDown.CanIncrement())
							Stepless_SetValue( m_Stepless_Value - m_Stepless_IncValue );
					}

					CLLCDCommon::WaitButton_Unpressed( m_Stepless_DownButtonRectangle );
				}
				else
					WaitForTouchRelease();
			}
			else
#ifndef FRANCETX_ENABLED
				WaitForTouchRelease();
#else
			// FranceTx Mode
			if (m_RunningMode == CLRunningMode_FranceTX && gKTSGlobal.DisableTX != 'D')
			{
				if (m_FranceTx_Speed1ButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FranceTx_Speed1ButtonRectangle );

					if (FranceTx_WriteValue( 0 ))
						FranceTx_RenderDynamicObject();
				}
				else
				if (m_FranceTx_Speed2ButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FranceTx_Speed2ButtonRectangle );

					if (FranceTx_WriteValue( 1 ))
						FranceTx_RenderDynamicObject();
				}
				else
					WaitForTouchRelease();
			}
			else
				WaitForTouchRelease();
#endif
		}
		
    }
	
	return formResult;
}

void CLMainForm::SetRunningMode( CLRunningMode value )
{
	// End Mode
	switch (m_RunningMode)
	{
		case CLRunningMode_Weekly:

			// Pulisce l'area dell'icona weekly
			CLGraphics::DrawBox( CLRectangle( CLMainForm_Main_WeeklyIconRectangle ), CLGraphicStyleOptions_Default, RGBColor_Black );
			break;
	}

	// Imposta il nuovo Running Mode
	m_RunningMode	= value;

	m_IncreaseSpeed_RH_CO2		= gKTSData.IncreaseSpeed_RH_CO2;
	m_IsMaxRH_CO2				= KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit );

	// Start Mode
	switch (m_RunningMode)
	{
		case CLRunningMode_Nothing:
			m_CurrentInAlarm			= 0;
			m_CurrentFilterInAlarm		= 0;
			m_CurrentVentilationControl	= VentilationControl_Get();
			break;

		case CLRunningMode_ThreeSpeed:
			m_ThreeSpeed_CurrentSpeedIndex	= SpeedMode_Speed_GetIndex();
			break;

#ifdef FRANCETX_ENABLED
		case CLRunningMode_FranceTX:
			m_FranceTx_CurrentSpeedIndex	= SpeedMode_Speed_GetIndex();
			m_IncreaseSpeed_RH_CO2			= gKTSData.IncreaseSpeed_RH_CO2;
			break;
#endif

		case CLRunningMode_ExternalControl:
			m_ExternalControl_CurrentSpeedIndex	= Input_ExtCtrl_GetRegAirFlowInputIndex();
			m_ExternalControl_CurrentMeasure	= Input_ExtCtrl_GetRegAirFlowMeausure();
			break;

		case CLRunningMode_Weekly:
			m_Weekly_CurrentStatus	= gKTSData.Status_Weekly;
			break;

		case CLRunningMode_Stepless:
			m_Stepless_CurrentSpeed	= SpeedMode_Stepless_GetValue( VentilationControl_Get() , Mode_Caps_Capr);
			m_Stepless_MinValue		= SpeedMode_Stepless_GetMinValue( VentilationControl_Get() );
			m_Stepless_MaxValue		= SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() );
			m_Stepless_Value		= m_Stepless_CurrentSpeed;
			m_Stepless_IncValue		= SpeedMode_Stepless_GetIncValue( VentilationControl_Get() );
			break;

		case CLRunningMode_Fire:
			m_CurrentFireAlarm	= GetCurrentFireAlarm();
			break;

	}
	AirFlowPanel_Render();
}

void CLMainForm::RunningMode_Process()
{
	CLRunningMode	newRunningMode;

	// Determina il nuovo Running Mode
	if (IsFireAlarm())
		newRunningMode	= CLRunningMode_Fire;
	else
	if (gRDEeprom.Set_Input[ 0 ] == INP_REG_AIR_FLOW ||
		gRDEeprom.Set_Input[ 1 ] == INP_REG_AIR_FLOW)
		newRunningMode	= CLRunningMode_ExternalControl;
	else
	if (Function_IsEnabled( ENAB_WEEKLY ))
		newRunningMode	= CLRunningMode_Weekly;
	else
	if (CLKTS::IsRunningBoost())
		newRunningMode	= CLRunningMode_Boost;
	else
	{
		switch (SpeedMode_GetType())
		{
			case CLSpeedModeType_Stepless:
				newRunningMode	= CLRunningMode_Stepless;
				break;

			case CLSpeedModeType_ThreeSpeed:
				newRunningMode	= CLRunningMode_ThreeSpeed;
				break;

#ifdef FRANCETX_ENABLED
			case CLSpeedModeType_FranceTx:
				newRunningMode	= CLRunningMode_FranceTX;
				break;
#endif
			default:
				newRunningMode	= CLRunningMode_Stepless;
				break;
		}
	}

	// Se il running mode è diverso da quello corrente, imposta il nuovo mode
	if (newRunningMode != m_RunningMode)
	{
		m_CurrentVentilationControl = VentilationControl_Get();
		SetRunningMode( newRunningMode );
		m_BoxInfo.ForceRefresh();
	}
	else
	if (m_CurrentVentilationControl != VentilationControl_Get())
	{
		m_CurrentVentilationControl	= VentilationControl_Get();
		SetRunningMode( m_RunningMode );
	}
	// Il running mode è uguale a quello corrente, controlla se ci sono variazioni tali da
	// far scattare un aggiornamento
	else
	{
		bool	refreshDynamicObject	= false;

		// Effettua il controllo delle sonde CO2 o RH, nel caso in cui viene rilevata il massimo valore,
		// allora l'RD può decidere di incrementare la velocità (IRSP_INCREASE_SPEED_RH_CO2)
		// In tal caso nella progressbar della velocità oltre a visualizzare la speed selezionata
		// viene disegnato anche la veloctà delta in un diverso colore
		if (m_IsMaxRH_CO2 != (KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) ||
			m_IsMaxRH_CO2 && m_IncreaseSpeed_RH_CO2	!= gKTSData.IncreaseSpeed_RH_CO2)
		{
			m_IsMaxRH_CO2			= KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit );
			m_IncreaseSpeed_RH_CO2	= gKTSData.IncreaseSpeed_RH_CO2;
			refreshDynamicObject	= true;
		}

		switch (m_RunningMode)
		{
			case CLRunningMode_Stepless:
				if (m_Stepless_CurrentSpeed != SpeedMode_Stepless_GetValue( VentilationControl_Get() , Mode_Caps_Capr))
				{
					m_Stepless_CurrentSpeed	= SpeedMode_Stepless_GetValue( VentilationControl_Get() , Mode_Caps_Capr);
					m_Stepless_Value		= m_Stepless_CurrentSpeed;
					refreshDynamicObject	= true;
				}
				break;

			case CLRunningMode_ThreeSpeed:
				if (m_ThreeSpeed_CurrentSpeedIndex != SpeedMode_Speed_GetIndex())
				{
					m_ThreeSpeed_CurrentSpeedIndex	= SpeedMode_Speed_GetIndex();
					refreshDynamicObject			= true;
				}
				break;

#ifdef FRANCETX_ENABLED
			case CLRunningMode_FranceTX:
				if (m_FranceTx_CurrentSpeedIndex != SpeedMode_Speed_GetIndex())
				{
					m_FranceTx_CurrentSpeedIndex	= SpeedMode_Speed_GetIndex();
					refreshDynamicObject			= true;
				}
				break;
#endif
			case CLRunningMode_ExternalControl:
				if (m_ExternalControl_CurrentMeasure != Input_ExtCtrl_GetRegAirFlowMeausure())
				{
					m_ExternalControl_CurrentSpeedIndex	= Input_ExtCtrl_GetRegAirFlowInputIndex();
					m_ExternalControl_CurrentMeasure	= Input_ExtCtrl_GetRegAirFlowMeausure();
					refreshDynamicObject				= true;
				}
				break;

			case CLRunningMode_Weekly:
				if (m_Weekly_CurrentStatus != gKTSData.Status_Weekly)
				{
					m_Weekly_CurrentStatus	= gKTSData.Status_Weekly;
					refreshDynamicObject	= true;
				}
				break;

			case CLRunningMode_Boost:
				refreshDynamicObject	= false;
				break;

			case CLRunningMode_Fire:
				if (m_CurrentFireAlarm != GetCurrentFireAlarm())
				{
					m_CurrentFireAlarm	= GetCurrentFireAlarm();
					m_BoxInfo.ForceRefresh();
					refreshDynamicObject	= true;
				}
				break;
		}

		if (refreshDynamicObject)
			AirFlowPanel_RenderDynamicObject();
	}
}

void CLMainForm::AirFlowPanel_Render()
{
	bool	renderPowerOnOffIcon	= true;

	switch (m_RunningMode)
	{
		case CLRunningMode_Fire:
			Fire_Render();
			break;

		case CLRunningMode_ExternalControl:
			ExternalControl_Render();
			break;

		case CLRunningMode_Weekly:
			renderPowerOnOffIcon	= false;
			Weekly_Render();
			break;

		case CLRunningMode_Boost:
			Boost_Render();
			break;

		case CLRunningMode_Stepless:
			Stepless_Render();
			break;

		case CLRunningMode_ThreeSpeed:
			ThreeSpeed_Render();
			break;

#ifdef FRANCETX_ENABLED
		case CLRunningMode_FranceTX:
			FranceTx_Render();
			break;
#endif
		case CLRunningMode_Nothing:
			renderPowerOnOffIcon	= false;
			break;
	}
	AirFlowPanel_RenderDynamicObject();

	// Display PowerOff Button
	if (renderPowerOnOffIcon)
	{
		CLLCDCommon::DrawOnOffIcon( m_PowerOffButtonRectangle.GetX1(), m_PowerOffButtonRectangle.GetY1(),
			PowerOnOff_Icon_Color_On );
	}
}

void CLMainForm::AirFlowPanel_RenderDynamicObject()
{
	switch (m_RunningMode)
	{
		case CLRunningMode_Fire:
			Fire_RenderDynamicObject();
			break;

		case CLRunningMode_ExternalControl:
			ExternalControl_RenderDynamicObject();
			break;

		case CLRunningMode_Weekly:
			Weekly_RenderDynamicObject();
			break;

		case CLRunningMode_Boost:
			Boost_RenderDynamicObject();
			break;

		case CLRunningMode_Stepless:
			Stepless_RenderDynamicObject();
			break;

		case CLRunningMode_ThreeSpeed:
			ThreeSpeed_RenderDynamicObject();
			break;

#ifdef FRANCETX_ENABLED
		case CLRunningMode_FranceTX:
			FranceTx_RenderDynamicObject();
			break;
#endif
	}
}

void CLMainForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 191 ),
		GenericForm_Data_Style );

	// Menu Button
	CLLCDCommon::DrawGenericButton( m_MenuButtonRectangle,
		GenericButtonStyle_Normal_BigFont, CLLocalitation::GetText( CLTextId_MENU ) );

    // Nella versione Demo stampa una label "[DEMO]" gialla alto/centrato.
    if (gRDEeprom.Type_func == CLKTSType_DEMO)
	{
		CLGraphics::DrawBoxWithText( CLRectangle( CLMainForm_Main_DemoTextRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
			RGBColor_Black, 0xC8C800,
			1, 0xC8C800,
			"DEMO" );
    }
    
    /*if ( !Mode_Caps_Capr )
        CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                    RGBColor_Black, RGBColor_White,
                    "S", 1 );
    else
        CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                    RGBColor_Black, RGBColor_White,
                    "R", 1 );*/
    
	SetRunningMode( CLRunningMode_Nothing );
	m_BoxInfo.ClearBox();
}

void CLMainForm::StatusIcon_DisplayError( int x, int y )
{
   gLCD.drawBitmap( x, y,
	   CLImage565_RedAlert_Width, CLImage565_RedAlert_Height,
	   (unsigned short*) CLImage565_RedAlert );
}

void CLMainForm::StatusIcon_DisplayWarning( int x, int y )
{
   gLCD.drawBitmap( x, y,
	   CLImage565_GreenWarning_Width, CLImage565_GreenWarning_Height,
	   (unsigned short*) CLImage565_GreenWarning );
}

// Stepless Mode
// -----------------------------------
void CLMainForm::Stepless_SetValue( unsigned short value )
{
	if (value < SpeedMode_Stepless_GetMinValue( VentilationControl_Get() ))
		value	= SpeedMode_Stepless_GetMinValue( VentilationControl_Get() );
	else
	if (value > SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() ))
		value	= SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() );

	m_Stepless_Value	= value;
	if (GetState() == CLState_Running)
		Stepless_RenderDynamicObject();
}

void CLMainForm::Stepless_WriteValue_Process()
{
	if (m_RunningMode != CLRunningMode_Stepless)
		return;

	// C'e' una richiesta in corso?
	if (m_Stepless_WriteValue_InProgress)
	{
		if (COM_REQUEST_ISRUNNING( m_Stepless_WriteValue_SendStatus ))
			return;
	
		// Se si è verificato un errore, ripristina il valore precendete
		if (m_Stepless_WriteValue_SendStatus.Status != COM_REQUEST_STATUS_COMPLETED)
		{
			SpeedMode_Stepless_SetValue( VentilationControl_Get(), m_Stepless_WriteValue_SavedValue , Mode_Caps_Capr );
			Stepless_SetValue( m_Stepless_WriteValue_SavedValue );
		}

		// Nessuna richiesta in corso
		m_Stepless_WriteValue_InProgress	= 0;

		// Restart Timer
		m_Stepless_WriteValue_TimerMilliseconds	= millis();
		return;
	}

	// Il tempo di attesa è scaduto?
	if (millis() - m_Stepless_WriteValue_TimerMilliseconds >= 2000 ||
		millis() < m_Stepless_WriteValue_TimerMilliseconds)
	{
		// Se il valore corrente è diverso da quello presente in Eeprom, lo comunica all'rd
		if (m_Stepless_Value != SpeedMode_Stepless_GetValue( VentilationControl_Get() , Mode_Caps_Capr))
		{
			// Salva il valore corrente
			m_Stepless_WriteValue_SavedValue	= SpeedMode_Stepless_GetValue( VentilationControl_Get() , Mode_Caps_Capr);

			// Imposta il nuovo valore
			if (!SpeedMode_Stepless_SetValue( VentilationControl_Get(), m_Stepless_Value , Mode_Caps_Capr ))
			{
				Stepless_SetValue( m_Stepless_WriteValue_SavedValue );
			}
			else
			{
				int	sendRequestId	= -1;
				
				// Accoda la richiesta di WriteEeprom
				switch (VentilationControl_Get())
				{
					case CLVentilationControl_CAF:
					case CLVentilationControl_FSC:
						sendRequestId	= KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_StepMotorsFSC_CAF ),
							sizeof(gRDEeprom.Set_StepMotorsFSC_CAF),
							&m_Stepless_WriteValue_SendStatus );
						break;
	
					case CLVentilationControl_CAP:
						sendRequestId	= KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_StepMotors_CAP ),
							sizeof(gRDEeprom.Set_StepMotors_CAP),
							&m_Stepless_WriteValue_SendStatus );
						break;
				}

				if (sendRequestId == -1)
				{
					SpeedMode_Stepless_SetValue( VentilationControl_Get(), m_Stepless_WriteValue_SavedValue , Mode_Caps_Capr);
					Stepless_SetValue( m_Stepless_WriteValue_SavedValue );
					m_Stepless_WriteValue_InProgress	= 0;
				}
				else
					m_Stepless_WriteValue_InProgress	= 1;
			}
		}

		// Update Timer
		m_Stepless_WriteValue_TimerMilliseconds	= millis();
	}
}

void CLMainForm::Stepless_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_Stepless_FrameRectangle ),
		GenericForm_Group_Style );
    Caps_Capr_RenderDynamicObject();
}

void CLMainForm::Stepless_RenderDynamicObject()
{
	char		text[ 20 ];
	float		values[ 2 ];
	RGBColor	barTrueColors[ 2 ];
	short		valueCount;

	// Visualizza i pulsanti +/-
	CLLCDCommon::DrawGenericButton( m_Stepless_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_Stepless_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &DownMonoImage );

	// Draw Bar e Text relativo alla portata
	switch (VentilationControl_Get())
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:

			values[ 0 ]			= m_Stepless_Value;
			barTrueColors[ 0 ]	= CAF_FSC_ProgressBar_Color_BarTrue;
			if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
				gKTSData.IncreaseSpeed_RH_CO2 != 0)
			{
				values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
				barTrueColors[ 1 ]	= CAF_FSC_ProgressBar_Color_BarTrueIncreaseCO2_RH;
				valueCount			= 2;
			}
			else
				valueCount	= 1;

			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, barTrueColors,
				0, m_Stepless_MaxValue, values, valueCount,
				4, 2 );

			if (VentilationControl_Get() == CLVentilationControl_FSC)
			{
				sprintf( text, "%d %%", m_Stepless_Value );
			}
			else
			{
				sprintf( text, "%d %s",
					CLCommon::PercentageToM3H( (float) m_Stepless_Value / 100.0f ),
					CLFixedText_M3_H );
			}
			CLGraphics::DrawText( CLMainForm_Stepless_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );
            
            /*if ( !Mode_Caps_Capr )
                CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                            RGBColor_Black, RGBColor_White,
                            "S", 1 );
            else
                CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                            RGBColor_Black, RGBColor_White,
                            "R", 1 );*/
			break;

		case CLVentilationControl_CAP:

			values[ 0 ]			= m_Stepless_Value;
			barTrueColors[ 0 ]	= CAP_ProgressBar_Color_BarTrue;
			if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
				gKTSData.IncreaseSpeed_RH_CO2 != 0)
			{
				values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
				barTrueColors[ 1 ]	= CAP_ProgressBar_Color_BarTrueIncreaseCO2_RH;
				valueCount			= 2;
			}
			else
				valueCount	= 1;

			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
				0, m_Stepless_MaxValue, values, valueCount,
				4, 2 );

			sprintf( text, "%d %s",
				m_Stepless_Value,
				CLFixedText_PA );
			CLGraphics::DrawText( CLMainForm_Stepless_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );
            
            /*if ( !Mode_Caps_Capr )
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
            else
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );*/
			break;
	}
    Caps_Capr_RenderDynamicObject();
}

// ThreeSpeed Mode
// -----------------------------------
bool CLMainForm::ThreeSpeed_WriteValue( byte value )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveIdxStepMotors	= gRDEeprom.sel_idxStepMotors;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
		sizeof(gRDEeprom.sel_idxStepMotors),
		&writeEeprom_Status );

	gRDEeprom.sel_idxStepMotors	= value;

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		gRDEeprom.sel_idxStepMotors	= saveIdxStepMotors;
		return false;
	}

	return true;
}

void CLMainForm::ThreeSpeed_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_ThreeSpeed_FrameRectangle ),
		GenericForm_Group_Style );
}

void CLMainForm::ThreeSpeed_RenderDynamicObject()
{
	char		text[ 20 ];
	float		values[ 2 ];
	RGBColor	barTrueColors[ 2 ];
	short		valueCount;

	CLLCDCommon::DrawGenericButton( m_ThreeSpeed_Speed1ButtonRectangle,
		(SpeedMode_Speed_GetIndex() == 0 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Normal_BigFont), "1" );
	CLLCDCommon::DrawGenericButton( m_ThreeSpeed_Speed2ButtonRectangle,
		(SpeedMode_Speed_GetIndex() == 1 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Normal_BigFont), "2" );
	CLLCDCommon::DrawGenericButton( m_ThreeSpeed_Speed3ButtonRectangle,
		(SpeedMode_Speed_GetIndex() == 2 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Normal_BigFont), "3" );

	if (VentilationControl_Get() == CLVentilationControl_CAF ||
		VentilationControl_Get() == CLVentilationControl_FSC)
	{
		values[ 0 ]			= SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() );
		barTrueColors[ 0 ]	= CAF_FSC_ProgressBar_Color_BarTrue;
		if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
			gKTSData.IncreaseSpeed_RH_CO2 != 0)
		{
			values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
			barTrueColors[ 1 ]	= CAF_FSC_ProgressBar_Color_BarTrueIncreaseCO2_RH;
			valueCount			= 2;
		}
		else
			valueCount	= 1;

		CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_ThreeSpeed_ProgressBarRectangle ),
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
			CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, barTrueColors,
			0.0, 100.0, values, valueCount,
			4, 2 );

		if (VentilationControl_Get() == CLVentilationControl_FSC)
		{
			sprintf( text, "%d %%", SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ) );
		}
		else
		{
			sprintf( text, "%d %s",
				CLCommon::PercentageToM3H( (float) SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ) / 100.0f ),
				CLFixedText_M3_H );
		}
		CLGraphics::DrawText( CLMainForm_Stepless_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			text, 14 );
        
         /*if ( !Mode_Caps_Capr )
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
        else
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );*/
	}
	else
	if (VentilationControl_Get() == CLVentilationControl_CAP)
	{
		values[ 0 ]			= SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() );
		barTrueColors[ 0 ]	= CAP_ProgressBar_Color_BarTrue;
		if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
			gKTSData.IncreaseSpeed_RH_CO2 != 0)
		{
			values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
			barTrueColors[ 1 ]	= CAP_ProgressBar_Color_BarTrueIncreaseCO2_RH;
			valueCount			= 2;
		}
		else
			valueCount	= 1;
        
        if (Accessory_IsPresent( ACC_EEP_FLW1 ) && Accessory_IsPresent( ACC_EEP_FLW2 )) // CAPS and CAPR
        {
            if ( !Mode_Caps_Capr ) // CAPS
                CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
                CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
                CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
                0, CLKTS::Pressure_GetMax(), values, valueCount,
                4, 2 );
            else // CAPS
                CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
                CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
                CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
                0, CLKTS::Pressure_GetMax1(), values, valueCount,
                4, 2 );
        }
        else
            CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
			CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
			0, CLKTS::Pressure_GetMax(), values, valueCount,
			4, 2 );

		sprintf( text, "%d %s",
			SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ),
			CLFixedText_PA );
		CLGraphics::DrawText( CLMainForm_Stepless_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			text, 6 );
        
         /*if ( !Mode_Caps_Capr )
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
        else
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );*/
	}
}

// FranceTx Mode
// -----------------------------------
#ifdef FRANCETX_ENABLED

bool CLMainForm::FranceTx_WriteValue( byte classSubIndex )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveIdxStepMotors;

	if (classSubIndex != 0 && classSubIndex != 1)
		return false;

	// Salva i valori correnti
	saveIdxStepMotors	= gRDEeprom.sel_idxStepMotors;

	// Imposta i nuovi valori
	gRDEeprom.sel_idxStepMotors	= classSubIndex;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
		sizeof(gRDEeprom.sel_idxStepMotors),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		gRDEeprom.sel_idxStepMotors	= saveIdxStepMotors;
		return false;
	}

	return true;
}

void CLMainForm::FranceTx_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_FranceTx_FrameRectangle ),
		GenericForm_Group_Style );
}

void CLMainForm::FranceTx_RenderDynamicObject()
{
	char	text[ 10 ];
	byte	classIndex;

	FranceTx_DecodeState( FranceTx_GetState(), &classIndex );

	// Class Buttons
	CLLCDCommon::DrawGenericButton( m_FranceTx_Speed1ButtonRectangle,
		(m_FranceTx_CurrentSpeedIndex == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		FranceTx_GetText( text, classIndex, 0 ) );

	CLLCDCommon::DrawGenericButton( m_FranceTx_Speed2ButtonRectangle,
		(m_FranceTx_CurrentSpeedIndex == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		FranceTx_GetText( text, classIndex, 1 ) );

	sprintf( text, "%d", FranceTx_Classes[ classIndex ][ m_FranceTx_CurrentSpeedIndex ] );
	CLGraphics::DrawText( CLMainForm_FranceTx_TextValuePoint, CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 3 );
	CLGraphics::DrawText( CLMainForm_FranceTx_TextUMPoint, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		CLFixedText_M3_H );
}

#endif

// ExternalControl Mode
// -----------------------------------
void CLMainForm::ExternalControl_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_ExternalControl_FrameRectangle ),
		GenericForm_Group_Style );
}

void CLMainForm::ExternalControl_RenderDynamicObject()
{
	char	text[ 30 ];

	if (m_ExternalControl_CurrentSpeedIndex != -1)
	{
		sprintf( text, "%s #%d",
			CLLocalitation::GetText( CLTextId_EXTERNAL_CONTROL ),
			m_ExternalControl_CurrentSpeedIndex + 1 );
	}
	else
		text[ 0 ]	= '\0';

	CLGraphics::DrawText( CLRectangle( CLMainForm_ExternalControl_TitleFrameRectangle ), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
		RGBColor_Black, RGBColor_White,
		text );

	CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_ExternalControl_ProgressBarRectangle ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
		CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, CAF_FSC_ProgressBar_Color_BarTrue,
		0, 100, (m_ExternalControl_CurrentSpeedIndex == -1 ? 0 : m_ExternalControl_CurrentMeasure),
		4, 2 );

	if (m_ExternalControl_CurrentSpeedIndex != -1)
		sprintf( text, "%d %%", (m_ExternalControl_CurrentSpeedIndex == -1 ? 0 : m_ExternalControl_CurrentMeasure) );
	else
		text[ 0 ]	= '\0';
	CLGraphics::DrawText( CLMainForm_ExternalControl_TextValuePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, CLMainForm_ExternalControl_TextValueLength );
}

// Boost Mode
// -----------------------------------
void CLMainForm::Boost_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_Boost_FrameRectangle ),
		GenericForm_Group_Style );

	CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Stepless_ProgressBarRectangle ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
		CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, CAF_FSC_ProgressBar_Color_BarTrue,
		0, 100, 100,
		4, 2 );

	CLGraphics::DrawText( CLMainForm_Stepless_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		"PARTY", 6 );
    
     /*if ( !Mode_Caps_Capr )
        CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                    RGBColor_Black, RGBColor_White,
                    "S", 1 );
    else
        CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                    RGBColor_Black, RGBColor_White,
                    "R", 1 );*/
}

void CLMainForm::Boost_RenderDynamicObject()
{
}

void CLMainForm::Caps_Capr_RenderDynamicObject()
{
    if ( VentilationControl_Get() == CLVentilationControl_CAP )
    {
        if ( !Mode_Caps_Capr )
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
        else
            CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );
    }
    else
    {
        CLGraphics::DrawText( CLMainForm_Stepless_ModePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
                        RGBColor_Black, RGBColor_White,
                        " ", 1 );
    }
}

// Weekly Mode
// -----------------------------------
void CLMainForm::Weekly_Render()
{
	CLPoint	weeklyIconPoint	= CLRectangle( CLMainForm_Main_WeeklyIconRectangle ).GetPoint1();

	CLGraphics::DrawBox( CLRectangle( CLMainForm_Weekly_FrameRectangle ), CLGraphicStyleOptions_Default,
		RGBColor_Black );

	CLLCDCommon::DrawWeeklyIcon( weeklyIconPoint.GetX(), weeklyIconPoint.GetY() );
}

void CLMainForm::Weekly_RenderDynamicObject()
{
	byte	speedIndex	= Weekly_Status_GetSpeedIndex( m_Weekly_CurrentStatus );
	byte	isRunning	= Weekly_Status_IsRunning( m_Weekly_CurrentStatus );
	char	text[ 20 ];

	CLGraphics::DrawBox( CLRectangle( CLMainForm_Weekly_DataFrameRectangle ),
		GenericForm_Group_Style );

	#ifdef FRANCETX_ENABLED
	if (SpeedMode_GetType() == CLSpeedModeType_FranceTx)
	{
		byte	classIndex;

		FranceTx_DecodeState( FranceTx_GetState(), &classIndex );

		// Class Buttons
		CLLCDCommon::DrawGenericButton( CLRectangle( CLMainForm_Weekly_FranceTX_Speed1BarRectangle ),
			(isRunning && speedIndex == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Disabled_BigFont),
			FranceTx_GetText( text, classIndex, 0 ) );

		CLLCDCommon::DrawGenericButton( CLRectangle( CLMainForm_Weekly_FranceTX_Speed2BarRectangle ),
			(isRunning && speedIndex == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Disabled_BigFont),
			FranceTx_GetText( text, classIndex, 1 ) );

		if (isRunning)
		{
			sprintf( text, "%d %s",
				FranceTx_Classes[ classIndex ][ speedIndex ],
				CLFixedText_M3_H );
		}
		else
			*text	= '\0';

		CLGraphics::DrawText( CLMainForm_Weekly_FranceTX_TextValuePoint, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
			RGBColor_Black, RGBColor_White,
			text, CLMainForm_Weekly_FranceTX_TextValueLength );
	}
	else
	#endif
	{
		float		values[ 2 ];
		RGBColor	barTrueColors[ 2 ];
		short		valueCount;

		CLLCDCommon::DrawGenericButton( CLRectangle( CLMainForm_Weekly_ThreeSpeed_Speed1BarRectangle ),
			(isRunning && speedIndex == 0 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Disabled_BigFont), "1" );
		CLLCDCommon::DrawGenericButton( CLRectangle( CLMainForm_Weekly_ThreeSpeed_Speed2BarRectangle ),
			(isRunning && speedIndex == 1 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Disabled_BigFont), "2" );
		CLLCDCommon::DrawGenericButton( CLRectangle( CLMainForm_Weekly_ThreeSpeed_Speed3BarRectangle ),
			(isRunning && speedIndex == 2 ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Disabled_BigFont), "3" );

		if (VentilationControl_Get() == CLVentilationControl_CAF ||
			VentilationControl_Get() == CLVentilationControl_FSC)
		{
			values[ 0 ]			= SpeedMode_Speed_GetValue( VentilationControl_Get(), speedIndex );
			barTrueColors[ 0 ]	= CAF_FSC_ProgressBar_Color_BarTrue;
			if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
				gKTSData.IncreaseSpeed_RH_CO2 != 0)
			{
				values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
				barTrueColors[ 1 ]	= CAF_FSC_ProgressBar_Color_BarTrueIncreaseCO2_RH;
				valueCount			= 2;
			}
			else
				valueCount	= 1;

			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Weekly_ThreeSpeed_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max | CLDrawBarOptions_Data_Range,
				CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, barTrueColors,
				0, 100, values, valueCount,
				4, 2 );

			if (isRunning)
			{
				if (VentilationControl_Get() == CLVentilationControl_FSC)
					sprintf( text, "%d %%", SpeedMode_Speed_GetValue( VentilationControl_Get(), speedIndex ) );
				else
					sprintf( text, "%d %s",
						CLCommon::PercentageToM3H( (float) SpeedMode_Speed_GetValue( VentilationControl_Get(), speedIndex ) / 100.0f ),
						CLFixedText_M3_H );
			}
			else
				*text	= '\0';

			CLGraphics::DrawText( CLMainForm_Weekly_ThreeSpeed_TextValuePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, CLMainForm_Weekly_ThreeSpeed_TextValueLength );
		}
		else
		if (VentilationControl_Get() == CLVentilationControl_CAP)
		{
			values[ 0 ]			= SpeedMode_Speed_GetValue( VentilationControl_Get(), speedIndex );
			barTrueColors[ 0 ]	= CAP_ProgressBar_Color_BarTrue;
			if ((KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) || KTSStatusUnit_IsRHMax( gKTSData.Status_Unit )) &&
				gKTSData.IncreaseSpeed_RH_CO2 != 0)
			{
				values[ 1 ]			= (values[ 0 ] * gKTSData.IncreaseSpeed_RH_CO2) / 10;
				barTrueColors[ 1 ]	= CAP_ProgressBar_Color_BarTrueIncreaseCO2_RH;
				valueCount			= 2;
			}
			else
				valueCount	= 1;
            
			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Weekly_ThreeSpeed_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max | CLDrawBarOptions_Data_Range,
				CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
				0, CLKTS::Pressure_GetMax(), values, valueCount,
				4, 2 );

			if (isRunning)
				sprintf( text, "%d %s",
					SpeedMode_Speed_GetValue( VentilationControl_Get(), speedIndex ),
					CLFixedText_PA );
			else
				*text	= '\0';
			CLGraphics::DrawText( CLMainForm_Weekly_ThreeSpeed_TextValuePoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				text, CLMainForm_Weekly_ThreeSpeed_TextValueLength );
		}

	}

	CLGraphics::DrawBox( CLRectangle( CLMainForm_Weekly_DataProgramFrameRectangle ),
		GenericForm_Group_Style );

	// Visualizza le informazioni della programmazione corrente solo se il weekly è running
	if (isRunning)
	{
		// Draw Temperature Icon (Sun/Moon)
		if (!Weekly_Status_GetTemperatureIndex( m_Weekly_CurrentStatus ))
		{
			CLGraphics::Draw( CLRectangle( CLMainForm_Weekly_TemperatureIconRectangle ),
				CLGraphicStyleOptions_HVAlign_Center,
				&SunMonoImage, RGBColor_Black, RGBColor_SunIcon_Pen );
		}
		else
		{
			CLGraphics::Draw( CLRectangle( CLMainForm_Weekly_TemperatureIconRectangle ),
				CLGraphicStyleOptions_HVAlign_Center,
				&MoonMonoImage, RGBColor_Black, RGBColor_MoonIcon_Pen );
		}

		sprintf( text, "%d%c",
			gRDEeprom.SetPointTemp[ Weekly_Status_GetTemperatureIndex( m_Weekly_CurrentStatus ) ] / 10,
			FONT_SYMBOL_DEGREES );
		CLGraphics::DrawText( CLMainForm_Weekly_TemperatureValueTextPoint, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
			RGBColor_Black, RGBColor_White,
			text, CLMainForm_Weekly_TemperatureValueTextLength );

		if (Weekly_Status_GetUnbalanceIndex( m_Weekly_CurrentStatus ))
		{
			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Weekly_SupplyUnbalanceRectangle ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_StartWith_Max,
				TemperatureCold_ProgressBar_Color_Background, TemperatureCold_ProgressBar_Color_BarTrue, TemperatureCold_ProgressBar_Color_BarFalse,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] > 0 ? gRDEeprom.Set_Imbalance[ 0 ] : 0),
				1, 0 );
			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Weekly_ExtractUnbalanceRectangle ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_StartWith_Min,
				TemperatureHot_ProgressBar_Color_Background, TemperatureHot_ProgressBar_Color_BarTrue, TemperatureHot_ProgressBar_Color_BarFalse,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] < 0 ? abs( gRDEeprom.Set_Imbalance[ 0 ] ) : 0),
				1, 0 );

			sprintf( text, "%d %%", gRDEeprom.Set_Imbalance[ 0 ] );
			CLGraphics::DrawText( CLMainForm_Weekly_UnbalanceTextPoint, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
				RGBColor_Black, RGBColor_White,
				text, CLMainForm_Weekly_UnbalanceTextLength );
		}
	}

	CLLCDCommon::DrawOnOffIcon( m_PowerOffButtonRectangle.GetX1(), m_PowerOffButtonRectangle.GetY1(),
		(isRunning ? PowerOnOff_Icon_Color_On : PowerOnOff_Icon_Color_Off) );
}

// Fire Mode
// -----------------------------------
void CLMainForm::Fire_Render()
{
	CLGraphics::DrawBox( CLRectangle( CLMainForm_Fire_FrameRectangle ), CLGraphicStyleOptions_Default,
		RGBColor_Black );
}

void CLMainForm::Fire_RenderDynamicObject()
{
	char		text[ 20 ];
	float		values[ 1 ];
	RGBColor	barTrueColors[ 1 ];
	//CLRectangle	progressBarRectangle( CLMainForm_Fire_ProgressBarRectangle );

	values[ 0	]		= (m_CurrentFireAlarm == ALM_SMOKE_VENT_OFF ? 0.0f : SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() ));
	barTrueColors[ 0 ]	= CAF_FSC_ProgressBar_Color_BarTrue;

	// Draw Bar e Text relativo alla portata
	switch (VentilationControl_Get())
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Fire_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				CAF_FSC_ProgressBar_Color_Background, CAF_FSC_ProgressBar_Color_BarFalse, barTrueColors,
				0, SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() ), values, 1,
				4, 2 );

			if (VentilationControl_Get() == CLVentilationControl_FSC)
				sprintf( text, "%d %%", (int) values[ 0 ] );
			else
				sprintf( text, "%d %s",
					CLCommon::PercentageToM3H( values[ 0 ] / 100.0f ),
					CLFixedText_M3_H );

			CLGraphics::DrawText( CLMainForm_Fire_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );
			break;

		case CLVentilationControl_CAP:

			CLGraphics::DrawProgressBar( CLRectangle( CLMainForm_Fire_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				CAP_ProgressBar_Color_Background, CAP_ProgressBar_Color_BarFalse, barTrueColors,
				0, SpeedMode_Stepless_GetMaxValue( VentilationControl_Get() ), values, 1,
				4, 2 );

			sprintf( text, "%d %s", (int) values[ 0 ],
				CLFixedText_PA );
			CLGraphics::DrawText( CLMainForm_Fire_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );
			break;
	}
}
// -----------------------------------------------------------------------------
// CLMainForm [class]
// =============================================================================

