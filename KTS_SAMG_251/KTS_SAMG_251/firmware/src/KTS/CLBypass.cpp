#include "CLBypass.h"
#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLInputOutput.h"

CLBypassStatus Bypass_GetStatus()
{
	return (CLBypassStatus) KTSStatusUnit_BypassState( gKTSData.Status_Unit );
}

void Bypass_GetConfigText( char* text, byte configBypass, bool combineManual )
{
	switch (configBypass)
	{
		case CLBypassConfig_AutomaticOn: // Automatic On
			strcpy( text, CLLocalitation::GetText( CLTextId_AUTOMATIC_ON ) );
			return;

		case CLBypassConfig_AutomaticOnStandby: // Automatic On/Standby
			strcpy( text, CLLocalitation::GetText( CLTextId_AUTOMATIC_ON_STANDBY ) );
			return;

		case CLBypassConfig_ExternalControl:
			strcpy( text, CLLocalitation::GetText( CLTextId_EXTERNAL_CONTROL ) );
			return;

		case CLBypassConfig_ManualClose:
			if (combineManual)
				strcpy( text, CLLocalitation::GetText( CLTextId_MANUAL ) );
			else
				strcpy( text, CLLocalitation::GetText( CLTextId_MANUAL_CLOSE ) );
			return;

		case CLBypassConfig_ManualOpen:
			if (combineManual)
				strcpy( text, CLLocalitation::GetText( CLTextId_MANUAL ) );
			else
				strcpy( text, CLLocalitation::GetText( CLTextId_MANUAL_OPEN ) );
			return;
	}
	*text	= '\0';
}

void Bypass_GetStatusText( char* text, word statusUnit )
{
	switch ((statusUnit >> 6) & 0x03)
	{
		case 0:
			strcpy( text, CLLocalitation::GetText( CLTextId_OPEN ) );
			return;

		case 1:
			strcpy( text, CLLocalitation::GetText( CLTextId_CHANGING ) );
			return;

		case 2:
			strcpy( text, CLLocalitation::GetText( CLTextId_CLOSED ) );
			return;
	}
	*text	= '\0';
}

bool Bypass_Write( byte config )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveConfigBypass;

	// Salva temporaneamente i dati attuali
	saveConfigBypass	= gRDEeprom.Config_Bypass;

	// Imposta i nuovi dati
	gRDEeprom.Config_Bypass	= config;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Config_Bypass ),
		sizeof(gRDEeprom.Config_Bypass),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Config_Bypass	= saveConfigBypass;

		return false;
	}

	return true;
}

bool Bypass_WriteRotation( byte rotation )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveRotationBypass;

	// Salva temporaneamente i dati attuali
	saveRotationBypass	= gRDEeprom.RotazioneBypass;

	// Imposta i nuovi dati
	gRDEeprom.RotazioneBypass	= rotation;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, RotazioneBypass ),
		sizeof(gRDEeprom.RotazioneBypass),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.RotazioneBypass	= saveRotationBypass;

		return false;
	}

	return true;
}

bool Bypass_WriteMinTemperature( float value )
{
	ComQueue_Status	writeEeprom_Status;
	float			saveBypass_minTempExt;

	// Salva temporaneamente i dati attuali
	saveBypass_minTempExt	= gRDEeprom.Bypass_minTempExt;

	// Imposta i nuovi dati
	Bypass_SetMinTemperature( value );

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Bypass_minTempExt ),
		sizeof(gRDEeprom.Bypass_minTempExt),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Bypass_minTempExt	= saveBypass_minTempExt;

		return false;
	}

	return true;
}

float Bypass_GetMinTemperature()
{
	return (float) gRDEeprom.Bypass_minTempExt / 10.0f;
}

void Bypass_SetMinTemperature( float value )
{
	gRDEeprom.Bypass_minTempExt	= (short) (value * 10.0f);
}

