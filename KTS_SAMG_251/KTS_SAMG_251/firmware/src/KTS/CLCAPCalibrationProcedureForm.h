 /*************************************************************************************
 *  file:			CLSelectionSpeedMotorModeForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLCAPCalibrationProcedureForm_h
#define __CLCAPCalibrationProcedureForm_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLVentilationControl.h"

CLFormResult CLCAPCalibrationProcedureForm_Open( unsigned short options );

// =============================================================================
// CLCAPCalibrationProcedureForm [class]
// =============================================================================
// Description: Form per la procedura di calibrazione del CAP
// -----------------------------------------------------------------------------
class _PACK CLCAPCalibrationProcedureForm
	: public CLForm
{
	public: CLCAPCalibrationProcedureForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_CancelButtonRectangle;
	private: CLRectangle m_YesButtonRectangle;
	private: CLRectangle m_NoButtonRectangle;
	private: CLRectangle m_ResetButtonRectangle;

	private: enum CLCalibrationState
	{
		CLCalibrationState_Ready,
		CLCalibrationState_Measuring,
		CLCalibrationState_ConfirmMeasure,
		CLCalibrationState_Completed,
		CLCalibrationState_Error
	};

	private: enum CLCalibrationSubState
	{
		CLCalibrationSubState_None,
		CLCalibrationSubState_Ok,
		CLCalibrationSubState_ErrorWritingData
	};

	private: CLCalibrationState m_CalibrationState;
	private: CLCalibrationSubState m_CalibrationSubState;
	private: void SetCalibrationState( CLCalibrationState state, CLCalibrationSubState subState );

	private: unsigned long m_CalibrationStartMillis;

	private: CLVentilationControl m_SaveVentilationControl;
	private: CLSpeedModeType m_SaveSpeedMode;
	private: unsigned short m_SaveStepMotorCAP_2;
	private: byte m_SaveIdxStepMotors;
	private: unsigned short m_SaveCalibra_CAP;
    private: unsigned short m_SaveCalibra_CAP1;

	private: unsigned short m_MeasurePressure; // CAP or CAPS
    private: unsigned short m_MeasurePressure1; // CAPR
	private: int m_MeasurePressureCount;
	public: void SetMeasurePressure( unsigned short value ); // CAP or CAPS
    public: void SetMeasurePressure1( unsigned short value ); // CAPR

	private: unsigned short m_Options;

	public: CLFormResult Open( unsigned short options );
	
	private: bool MeasureStart();
	private: void MeasureEnd();
	
	private: bool CalibrationSave( unsigned short value , unsigned short value1);

	private: void RenderPage();
	private: void Render_StaticObject();
	private: void Render_DinamycObject();
};
// -----------------------------------------------------------------------------
// CLCAPCalibrationProcedureForm [class]
// =============================================================================

#endif

