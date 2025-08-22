#include "CLFranceTX.h"
#include "CLKTS.h"
#include "CLSpeedMode.h"
#include "CLFunction.h"
#include "CLVentilationControl.h"

#ifdef FRANCETX_ENABLED

short FranceTx_Classes[ FranceTx_ClassCount ][ 2 ] =
{
	{  75, 135 },
	{ 105, 165 },
	{ 135, 210 },
	{ 150, 240 },
	{ 180, 270 }
};

char* FranceTx_GetText( char* text, byte classIndex )
{
	sprintf( text, "T%d", classIndex + 2 );
	return text;
}

char* FranceTx_GetText( char* text, byte classIndex, byte subClassIndex )
{
	sprintf( text, "T%d%c", classIndex + 2, (subClassIndex == 0 ? '-' : '+') );
	return text;
}

bool FranceTx_GetClassIndexFromPercentage( byte percentage, byte& classIndex, byte& classSubIndex )
{
	short	maxAirFlow	= CLKTS::AirFlow_GetMax();

	for (int franceTxClassesCounter = 0; franceTxClassesCounter < FranceTx_ClassCount; franceTxClassesCounter++)
	{
		short	currentPercentage;

		currentPercentage	= (byte) ((float) FranceTx_Classes[ franceTxClassesCounter ][ 0 ] / (float) maxAirFlow) * 100.0f;
		if (percentage >= currentPercentage - 1 && percentage <= currentPercentage + 1)
		{
			classIndex		= franceTxClassesCounter;
			classSubIndex	= 0;
			return true;
		}

		currentPercentage	= (byte) ((float) FranceTx_Classes[ franceTxClassesCounter ][ 1 ] / (float) maxAirFlow) * 100.0f;
		if (percentage >= currentPercentage - 1 && percentage <= currentPercentage + 1)
		{
			classIndex		= franceTxClassesCounter;
			classSubIndex	= 1;
			return true;
		}
	}

	return false;
}

byte FranceTx_GetPercentageFromClassIndex( byte classIndex, byte classSubIndex )
{
	return (byte) (((float) FranceTx_Classes[ classIndex ][ classSubIndex ] / (float) CLKTS::AirFlow_GetMax()) * 100.0);
}

unsigned short FranceTx_EncodeState( byte classIndex )
{
	return ((unsigned short) 0x8000) | ((classIndex & 0x07) << 12);
}

bool FranceTx_DecodeState( unsigned short value, byte* classIndex )
{
	if (!(value & 0x8000))
		return false;

	if (classIndex)
		*classIndex		= (byte) ((value & 0x7000) >> 12);
	return true;
}

bool FranceTx_CanSelect()
{
	return VentilationControl_Get() == CLVentilationControl_CAF;
}

bool FranceTx_IsEnabled()
{
	return !Function_IsEnabled( ENAB_STEPLESS ) && 
		FranceTx_CanSelect() &&
		(gRDEeprom.Set_StepMotorsFSC_CAF[ FranceTx_StepMotorsFSC_CAF_StateIndex ] & 0x8000);
}

void FranceTx_SetState( unsigned short value )
{
	gRDEeprom.Set_StepMotorsFSC_CAF[ FranceTx_StepMotorsFSC_CAF_StateIndex ]	= value;
}

unsigned short FranceTx_GetState()
{
	return gRDEeprom.Set_StepMotorsFSC_CAF[ FranceTx_StepMotorsFSC_CAF_StateIndex ];
}

#endif


