 /*************************************************************************************
 *  file:			CLMainForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLMainForm_h
#define __CLMainForm_h

#include "CLForm.h"
#include "CLBoxInfo.h"
#include "CLVentilationControl.h"
#include "CLCommunicationManager.h"

CLFormResult CLMainForm_Open();

// =============================================================================
// CLMainForm [class]
// =============================================================================
// Description: Form principale
// -----------------------------------------------------------------------------
class _PACK CLMainForm
	: public CLForm
{
	private: enum CLRunningMode
	{
		CLRunningMode_Nothing,
		CLRunningMode_Stepless,
		CLRunningMode_ThreeSpeed,
#ifdef FRANCETX_ENABLED
		CLRunningMode_FranceTX,
#endif
		CLRunningMode_ExternalControl,
		CLRunningMode_Weekly,
		CLRunningMode_Boost,
		CLRunningMode_Fire
	};

	public: CLMainForm();


	private: byte m_CurrentInAlarm;
	private: byte m_CurrentFilterInAlarm;

	private: CLRunningMode m_RunningMode;
	private: void SetRunningMode( CLRunningMode value );
	private: void RunningMode_Process();

	// BoxInfo
	private: CLBoxInfo m_BoxInfo;

	// Buttons
	private: CLRectangle m_PowerOffButtonRectangle;
	private: CLRectangle m_MenuButtonRectangle;

	// Icons
	private: CLRectangle m_ErrorIconRectangle;
	private: CLRectangle m_WarningIconRectangle;
	private: CLRectangle m_RHIconRectangle;
	private: CLRectangle m_CO2IconRectangle;
	private: CLRectangle m_VOCIconRectangle;
	private: CLRectangle m_SummerWinterIconRectangle;
	private: CLRectangle m_DSCIconRectangle;

	public: CLFormResult Open();

	private: void RenderPage();

	private: void AirFlowPanel_Render();
	private: void AirFlowPanel_RenderDynamicObject();

	private: CLVentilationControl m_CurrentVentilationControl;

	// Stepless Mode
	// -----------------------------------
	private: unsigned short m_Stepless_CurrentSpeed;
	private: CLRectangle m_Stepless_UpButtonRectangle;
	private: CLRectangle m_Stepless_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_Stepless_ProgressiveTouchUpDown;

	private: byte m_IncreaseSpeed_RH_CO2;
	private: bool m_IsMaxRH_CO2;

	private: unsigned short m_Stepless_Value;
	private: unsigned short m_Stepless_MinValue;
	private: unsigned short m_Stepless_MaxValue;
	private: unsigned short m_Stepless_IncValue;

	public: void Stepless_SetValue( unsigned short value );
			 
	private: void Stepless_Render();
	private: void Stepless_RenderDynamicObject();

	// Stepless Mode -- Stepless WriteValue
	private: unsigned long m_Stepless_WriteValue_TimerMilliseconds;
	private: unsigned short m_Stepless_WriteValue_SavedValue;
	private: ComQueue_Status m_Stepless_WriteValue_SendStatus;
	private: byte m_Stepless_WriteValue_InProgress;

	private: void Stepless_WriteValue_Process();

	// ThreeSpeed Mode
	// -----------------------------------
	private: CLRectangle m_ThreeSpeed_Speed1ButtonRectangle;
	private: CLRectangle m_ThreeSpeed_Speed2ButtonRectangle;
	private: CLRectangle m_ThreeSpeed_Speed3ButtonRectangle;
	private: CLRectangle m_ThreeSpeed_ProgressBarRectangle;
	private: byte m_ThreeSpeed_CurrentSpeedIndex;

	private: bool ThreeSpeed_WriteValue( byte value );

	private: void ThreeSpeed_Render();
	private: void ThreeSpeed_RenderDynamicObject();

#ifdef FRANCETX_ENABLED
	// FranceTx Mode
	// -----------------------------------
	private: CLRectangle m_FranceTx_Speed1ButtonRectangle;
	private: CLRectangle m_FranceTx_Speed2ButtonRectangle;

	private: byte m_FranceTx_CurrentSpeedIndex;

	private: bool FranceTx_WriteValue( byte classSubIndex );
	private: void FranceTx_Render();
	private: void FranceTx_RenderDynamicObject();
#endif

	// ExternalControl Mode
	// -----------------------------------
	private: short m_ExternalControl_CurrentSpeedIndex;
	private: short m_ExternalControl_CurrentMeasure;

	private: void ExternalControl_Render();
	private: void ExternalControl_RenderDynamicObject();

	// Boost Mode
	// -----------------------------------
	private: void Boost_Render();
	private: void Boost_RenderDynamicObject();

	// Fire Mode
	// -----------------------------------
	private: byte m_CurrentFireAlarm;
	private: void Fire_Render();
	private: void Fire_RenderDynamicObject();

	// Weekly Mode
	// -----------------------------------
	private: byte m_Weekly_CurrentStatus;

	private: void Weekly_Render();
	private: void Weekly_RenderDynamicObject();

	private: void StatusIcon_DisplayError( int x, int y );
	private: void StatusIcon_DisplayWarning( int x, int y );

	public: static void RenderDateBox( int x, int y );
};
// -----------------------------------------------------------------------------
// CLMainForm [class]
// =============================================================================

#endif

