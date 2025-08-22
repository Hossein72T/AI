#include "CLWeekly.h"
#include "CLKTS.h"
#include "CLFunction.h"
#include "CLSpeedMode.h"
#include "CLVentilationControl.h"
#include "CLFranceTX.h"
#include "CLCommunicationManager.h"
#include "CLFonts.h"

void Weekly_GetTextStartTime( char* text, SDAYPROG* dayProgs, byte range )
{
	sprintf( text, "%02d:%02d", dayProgs->timeON[ range ] / 2, ((dayProgs->timeON[ range ] % 2) ? 30 : 0) );
}

void Weekly_GetTextEndTime( char* text, SDAYPROG* dayProgs, byte range )
{
	sprintf( text, "%02d:%02d", dayProgs->timeOFF[ range ] / 2, ((dayProgs->timeOFF[ range ] % 2) ? 30 : 0) );
}

void Weekly_GetTextAirFlowSpeed( char* text, SDAYPROG* dayProgs, byte range, bool includeMeasureUnit ) 
{
	switch (SpeedMode_GetType())
	{

#ifdef FRANCETX_ENABLED
		case CLSpeedModeType_FranceTx:
			byte	classIndex;

			FranceTx_DecodeState( FranceTx_GetState(), &classIndex );
			sprintf( text, "%d",
				FranceTx_Classes[ classIndex ][ GET2BITVALUE( dayProgs->ConfigSpeed, range ) ] );
			break;
#endif
		default:
		{
			byte	value	= GET2BITVALUE( dayProgs->ConfigSpeed, range );

			switch (VentilationControl_Get())
			{
				case CLVentilationControl_CAF:
					sprintf( text, "%d",
						CLCommon::PercentageToM3H( (float) SpeedMode_Speed_GetValue( VentilationControl_Get(), value ) / 100.0f ) );
					break;

				case CLVentilationControl_FSC:
					sprintf( text, "%d", SpeedMode_Speed_GetValue( VentilationControl_Get(), value ) );
					break;
				
				case CLVentilationControl_CAP:
					sprintf( text, "%d",
						SpeedMode_Speed_GetValue( VentilationControl_Get(), value ) );
					break;
			}
			break;
		}
	}

	if (includeMeasureUnit)
	{
		strcat( text, " " );
		strcat( text, CLKTS::GetSpeedMeasureUnit() );
	}
}

void Weekly_GetTextUnbalance( char* text, SDAYPROG* dayProgs, byte range )
{
	if (GET2BITVALUE( dayProgs->ConfigImbal, range ) == 0)
	{
		*text	= '\0';
		return;
	}

	sprintf( text, "%d %%", gRDEeprom.Set_Imbalance[ 0 ] );
}

void Weekly_GetTextTemperature( char* text, SDAYPROG* dayProgs, byte range )
{
	sprintf( text, "%d %cC", gRDEeprom.SetPointTemp[ GET2BITVALUE( dayProgs->ConfigTemp, range ) ] / 10, FONT_SYMBOL_DEGREES );
}

char Weekly_GetTextTemperatureSymbol( SDAYPROG* dayProgs, byte range )
{
	return GET2BITVALUE( dayProgs->ConfigTemp, range ) == 0 ? 'S' : 'M';
}

const char* Weekly_GetDayName( byte index )
{
	switch (index)
	{
		case 0:
			return CLLocalitation::GetText( CLTextId_SUNDAY );
		case 1:
			return CLLocalitation::GetText( CLTextId_MONDAY );
		case 2:
			return CLLocalitation::GetText( CLTextId_TUESDAY );
		case 3:
			return CLLocalitation::GetText( CLTextId_WEDNESDAY );
		case 4:
			return CLLocalitation::GetText( CLTextId_THURSDAY );
		case 5:
			return CLLocalitation::GetText( CLTextId_FRIDAY );
		case 6:
			return CLLocalitation::GetText( CLTextId_SATURDAY );
	}
	return "";
}

bool Weekly_Write( SDAYPROG* dayProgs )
{
	ComQueue_Status	writeEeprom_Status;
	SDAYPROG		savesDayProg[ 7 ];

	// Salva temporaneamente i dati correnti
	memcpy( savesDayProg, gRDEeprom.sDayProg, sizeof(savesDayProg) );

	// Imposta i nuovi dati
	memcpy( gRDEeprom.sDayProg, dayProgs, sizeof(gRDEeprom.sDayProg) );

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sDayProg ),
		sizeof(gRDEeprom.sDayProg),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		memcpy( gRDEeprom.sDayProg, savesDayProg, sizeof(gRDEeprom.sDayProg) );

		return false;
	}

	return true;
}

