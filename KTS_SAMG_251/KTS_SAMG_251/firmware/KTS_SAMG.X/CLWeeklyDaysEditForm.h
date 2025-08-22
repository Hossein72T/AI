 /*************************************************************************************
 *  file:			CLWeeklyDaysEditForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLWeeklyDaysEditForm_h
#define __CLWeeklyDaysEditForm_h

#include "CLForm.h"
#include "RDEeprom.h"

CLFormResult CLWeeklyDaysEditForm_Open( unsigned short options,
	SDAYPROG* days, byte selectedDays );

// =============================================================================
// CLWeeklyDaysEditForm [class]
// =============================================================================
// Description: Form per l'edit di uno o più days del weekly
// -----------------------------------------------------------------------------
class _PACK CLWeeklyDaysEditForm
	: public CLForm
{
	private: enum CLStepId
	{
		CLStepId_SelectRangeCount,
		CLStepId_SelectStartTime,
		CLStepId_SelectEndTime,
		CLStepId_SelectAirFlow,
		CLStepId_SelectTemperature,
		CLStepId_SelectUnbalance
	};

	public: CLWeeklyDaysEditForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_HoursProgressBarRectangle;
	private: CLRectangle m_StepButtonRectangle1;
	private: CLRectangle m_StepButtonRectangle2;
	private: CLRectangle m_StepButtonRectangle3;
	private: float m_HoursBarSize;

	private: byte m_SelectedDays;

	private: SDAYPROG m_Day;

	public: void SelectStartTime();
	public: void SetStartTime( byte range, byte value );

	public: void SelectEndTime();
	public: void SetEndTime( byte range, byte value );

	public: void SelectAirFlow();
	public: void SetAirFlow( byte range, byte value );

#ifdef FRANCETX_ENABLED
	public: void SetAirFlow_FranceTx( byte range, byte value );
#endif

	public: void SetAirFlow_ThreeSpeed( byte range, byte value );

	public: void SelectTemperature();
	public: void SetTemperature( byte range, byte value );

	public: void SelectUnbalance();
	public: void SetUnbalance( byte range, byte value );

	public: void SelectRangeCount();
	public: void SetRangeCount( byte value );

	private: byte m_CurrentRange;
	private: CLStepId m_CurrentStep;

	public: CLFormResult Open( unsigned short options,
		SDAYPROG* days, byte selectedDays );

	private: void RenderPage();
	private: void RenderStep();
	private: void RenderStep_StaticObject();
	private: void RenderStep_DynamicObject();
	private: void RenderTimeProgressBar( byte range );
	private: void RenderAllTimeProgressBar();
};
// -----------------------------------------------------------------------------
// CLWeeklyDaysEditForm [class]
// =============================================================================

#endif

