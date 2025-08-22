#include "CLVentilationControl.h"
#include "CLKTS.h"
#include "CLFunction.h"
#include "CLCommunicationManager.h"

bool VentilationControl_CanSelect( CLVentilationControl value )
{
	return Function_CanEnable( (_BIT_NUMBER_ENAB_FUCTIONS) value );
}

CLVentilationControl VentilationControl_Get()
{
	if (Function_IsEnabled( ENAB_CAP ))
		return CLVentilationControl_CAP;
	if (Function_IsEnabled( ENAB_FSC ))
		return CLVentilationControl_FSC;
	return CLVentilationControl_CAF;
}

bool VentilationControl_Write( CLVentilationControl value )
{
	ComQueue_Status			writeEeprom_Status;
	CLVentilationControl	saveVentilationControl;

	// Salva temporaneamente i dati prima del salvataggio
	saveVentilationControl	= VentilationControl_Get();

	// Imposta il nuovo stato del bypass
	Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) saveVentilationControl, false );
	Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) value, true );

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
		sizeof(gRDEeprom.Enab_Fuction),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) value, false );
		Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) saveVentilationControl, true );

		return false;
	}

	return true;
}

