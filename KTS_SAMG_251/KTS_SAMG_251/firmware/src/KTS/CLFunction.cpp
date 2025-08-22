#include "CLFunction.h"
#include "CLKTS.h"
#include "CLCommunicationManager.h"

bool Function_IsEnabled( _BIT_NUMBER_ENAB_FUCTIONS functionIndex )
{
	return bitRead( gRDEeprom.Enab_Fuction, functionIndex );
}

void Function_SetEnabled( _BIT_NUMBER_ENAB_FUCTIONS functionIndex, bool value )
{
	bitWrite( gRDEeprom.Enab_Fuction, functionIndex, value );
}

bool Function_CanEnable( _BIT_NUMBER_ENAB_FUCTIONS functionIndex )
{
	return bitRead( gRDEeprom.msk_Enab_Fuction, functionIndex );
}

bool Function_Write( _BIT_NUMBER_ENAB_FUCTIONS functionIndex, bool value )
{
	ComQueue_Status	writeEeprom_Status;
	unsigned short	saveEnab_Function;

	if (Function_IsEnabled( functionIndex ) == value)
		return true;

	// Salva i valori correnti
	saveEnab_Function		= gRDEeprom.Enab_Fuction;

	// Imposta i nuovi valori
	Function_SetEnabled( functionIndex, value );

	// Accoda la richiesta di WriteEeprom per impostare i step motors
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
		sizeof(gRDEeprom.Enab_Fuction),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valori precedenti
		gRDEeprom.Enab_Fuction	= saveEnab_Function;
		return false;
	}

	return true;
}

