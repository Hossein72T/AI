#include "CLSpeedMode.h"
#include "CLKTS.h"
#include "CLFunction.h"
#include "CLFranceTX.h"
#include "CLVentilationControl.h"
#include "CLCommunicationManager.h"

extern bool Mode_Caps_Capr;

CLSpeedModeType SpeedMode_GetType()
{
	if (Function_IsEnabled( ENAB_STEPLESS ))
	{
		return CLSpeedModeType_Stepless;
	}

#ifdef FRANCETX_ENABLED
	if (FranceTx_IsEnabled())
		return CLSpeedModeType_FranceTx;
#endif

	return CLSpeedModeType_ThreeSpeed;
}

unsigned short SpeedMode_Stepless_GetMinValue( CLVentilationControl ventilationControl )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			return 20;

		case CLVentilationControl_CAP:
			return CLKTS::Pressure_GetMin();
	}
	return 0;
}

unsigned short SpeedMode_Stepless_GetMaxValue( CLVentilationControl ventilationControl )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			return 100;

		case CLVentilationControl_CAP:
			return CLKTS::Pressure_GetMax();
	}
	return 0;
}

unsigned short SpeedMode_Stepless_GetValue( CLVentilationControl ventilationControl , bool Caps_Capr_State)
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			return gRDEeprom.Set_StepMotorsFSC_CAF[ 3 ] / 10;

		case CLVentilationControl_CAP:
            if ( !Caps_Capr_State)
                return gRDEeprom.Set_StepMotors_CAP[ 3 ];
            else
                return gRDEeprom.Set_StepMotors_CAP[ 1 ];
	}
	return 0;
}

byte SpeedMode_Stepless_GetIncValue( CLVentilationControl ventilationControl )
{
	if (ventilationControl == CLVentilationControl_CAF ||
		ventilationControl == CLVentilationControl_FSC)
		return 1;

	return 5;
}

bool SpeedMode_Stepless_SetValue( CLVentilationControl ventilationControl, unsigned short value , bool Caps_Capr_State)
{
	if (value < SpeedMode_Stepless_GetMinValue( ventilationControl ) ||
		value > SpeedMode_Stepless_GetMaxValue( ventilationControl ))
		return false;

	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			gRDEeprom.Set_StepMotorsFSC_CAF[ 3 ]	= value * 10;
			return true;

		case CLVentilationControl_CAP:
            if ( !Caps_Capr_State)
                gRDEeprom.Set_StepMotors_CAP[ 3 ] = value;
            else
                gRDEeprom.Set_StepMotors_CAP[ 1 ]	= value;
			return true;
	}
	return true;
}

byte SpeedMode_Speed_GetIndex()
{
	return gRDEeprom.sel_idxStepMotors;
}

unsigned short SpeedMode_Speed_GetValue( CLVentilationControl ventilationControl, byte index )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			return gRDEeprom.Set_StepMotorsFSC_CAF[ index ] / 10;

		case CLVentilationControl_CAP:
			return gRDEeprom.Set_StepMotors_CAP[ index ];
	}
	return 0;
}

unsigned short SpeedMode_Speed_GetValue1( CLVentilationControl ventilationControl, byte index )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			return gRDEeprom.Set_StepMotorsFSC_CAF[ index ] / 10;

		case CLVentilationControl_CAP:
			return gRDEeprom.Set_StepMotors_CAP[ index ];
	}
	return 0;
}

void SpeedMode_Speed_SetValue( CLVentilationControl ventilationControl, byte index, unsigned short value )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			gRDEeprom.Set_StepMotorsFSC_CAF[ index ]	= value * 10;
			break;

		case CLVentilationControl_CAP:
			gRDEeprom.Set_StepMotors_CAP[ index ]	= value;
			break;
	}
}

void SpeedMode_Speed_GetValues( CLVentilationControl ventilationControl, unsigned short* values )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			values[ 0 ]	= gRDEeprom.Set_StepMotorsFSC_CAF[ 0 ] / 10;
			values[ 1 ]	= gRDEeprom.Set_StepMotorsFSC_CAF[ 1 ] / 10;
			values[ 2 ]	= gRDEeprom.Set_StepMotorsFSC_CAF[ 2 ] / 10;
			break;

		case CLVentilationControl_CAP:
			memcpy( values, gRDEeprom.Set_StepMotors_CAP, sizeof(gRDEeprom.Set_StepMotors_CAP) );
			break;
	}
}

void SpeedMode_Speed_SetValues( CLVentilationControl ventilationControl, unsigned short* values )
{
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			gRDEeprom.Set_StepMotorsFSC_CAF[ 0 ]	= values[ 0 ] * 10;
			gRDEeprom.Set_StepMotorsFSC_CAF[ 1 ]	= values[ 1 ] * 10;
			gRDEeprom.Set_StepMotorsFSC_CAF[ 2 ]	= values[ 2 ] * 10;
			break;

		case CLVentilationControl_CAP:
			memcpy( gRDEeprom.Set_StepMotors_CAP, values, sizeof(gRDEeprom.Set_StepMotors_CAP) );
			break;
	}
}

bool SpeedMode_Speed_Write( CLVentilationControl ventilationControl,
	CLSpeedModeType speedModeType,
	unsigned short* newSet_StepMotors,
	byte newSel_IdxStepMotors )
{
	ComQueue_Status	writeEeprom_Status;
	unsigned short	saveSet_StepMotors[ 4 ];
	byte			saveSel_IdxStepMotors;

	// Salva i valori correnti
	switch (ventilationControl)
	{
		case CLVentilationControl_CAF:
		case CLVentilationControl_FSC:
			memcpy( saveSet_StepMotors, gRDEeprom.Set_StepMotorsFSC_CAF, sizeof(saveSet_StepMotors) );
			break;

		case CLVentilationControl_CAP:
			memcpy( saveSet_StepMotors, gRDEeprom.Set_StepMotors_CAP, sizeof(saveSet_StepMotors) );
			break;
	}
	saveSel_IdxStepMotors	= SpeedMode_Speed_GetIndex();

	// Imposta i nuovi valori
	gRDEeprom.sel_idxStepMotors	= newSel_IdxStepMotors;
	SpeedMode_Speed_SetValues( ventilationControl, newSet_StepMotors );
#ifdef FRANCETX_ENABLED
	if (SpeedMode_GetType() == CLSpeedModeType_FranceTx && ventilationControl != CLVentilationControl_CAF)
	{
		SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 0, 30 );
		SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 1, 60 );
		SpeedMode_Speed_SetValue( CLVentilationControl_CAF, 2, 90 );
		SpeedMode_Stepless_SetValue( CLVentilationControl_CAF, SpeedMode_Stepless_GetMinValue( CLVentilationControl_CAF ) , Mode_Caps_Capr);
	}

	if (speedModeType == CLSpeedModeType_FranceTx && ventilationControl == CLVentilationControl_CAF)
	{
		gRDEeprom.Set_StepMotorsFSC_CAF[ FranceTx_StepMotorsFSC_CAF_StateIndex ]	= 
			newSet_StepMotors[ FranceTx_StepMotorsFSC_CAF_StateIndex ];
	}
#endif

	// Accoda la richiesta di WriteEeprom per impostare i step motors
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
		offsetof( S_EEPROM, Set_Imbalance ) - offsetof( S_EEPROM, sel_idxStepMotors ),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valori precedenti
		switch (ventilationControl)
		{
			case CLVentilationControl_CAF:
			case CLVentilationControl_FSC:
				memcpy( gRDEeprom.Set_StepMotorsFSC_CAF, saveSet_StepMotors, sizeof(saveSet_StepMotors) );
				break;

			case CLVentilationControl_CAP:
				memcpy( gRDEeprom.Set_StepMotors_CAP, saveSet_StepMotors, sizeof(saveSet_StepMotors) );
				break;
		}
		gRDEeprom.sel_idxStepMotors	= saveSel_IdxStepMotors;
		return false;
	}

	return true;
}

