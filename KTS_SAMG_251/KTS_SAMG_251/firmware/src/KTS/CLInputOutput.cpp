#include "CLInputOutput.h"
#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLBypass.h"

short Input_ExtCtrl_GetRegAirFlowInputIndex()
{
	if (gRDEeprom.Set_Input[ 0 ] == INP_REG_AIR_FLOW)
		return 0;
	if (gRDEeprom.Set_Input[ 1 ] == INP_REG_AIR_FLOW)
		return 1;
	return -1;
}

short Input_ExtCtrl_GetRegAirFlowMeausure()
{
	if (gRDEeprom.Set_Input[ 0 ] == INP_REG_AIR_FLOW)
		return gKTSData.InputMeasure1;
	if (gRDEeprom.Set_Input[ 1 ] == INP_REG_AIR_FLOW)
		return gKTSData.InputMeasure2;
	return -1;
}

bool Input_Write( byte input1, byte input2 )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveSet_Input[ 2 ];

	// Salva temporaneamente la configurazione del bypass
	saveSet_Input[ 0 ]	= gRDEeprom.Set_Input[ 0 ];
	saveSet_Input[ 1 ]	= gRDEeprom.Set_Input[ 1 ];

	//Imposta il nuovo stato del bypass
	gRDEeprom.Set_Input[ 0 ]	= input1;
	gRDEeprom.Set_Input[ 1 ]	= input2;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_Input ),
		sizeof(gRDEeprom.Set_Input),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Set_Input[ 0 ]	= saveSet_Input[ 0 ];
		gRDEeprom.Set_Input[ 1 ]	= saveSet_Input[ 1 ];

		return false;
	}

	// Nel caso in cui uno degli input lavora sul bypass e il bypass è diverso da EXT_CTRL
	// imposta il bypass su EXT_CTLR
	if ((input1 == INP_12V_BYPASS_OPEN
		|| input1 == INP_0V_BYPASS_OPEN
		|| input2 == INP_12V_BYPASS_OPEN
		|| input2 == INP_0V_BYPASS_OPEN)
		&& gRDEeprom.Config_Bypass != BPD_EXT_CTRL)
	{
		return Bypass_Write( BPD_EXT_CTRL );
	}
	else
	// Nel caso in cui nessuno degli input lavora sul bypass e il bypass è impostato su EXT_CTRL
	// imposta il bypass su AUTOMATIC
	if (input1 != INP_12V_BYPASS_OPEN
		&& input1 != INP_0V_BYPASS_OPEN
		&& input2 != INP_12V_BYPASS_OPEN
		&& input2 != INP_0V_BYPASS_OPEN
		&& gRDEeprom.Config_Bypass == BPD_EXT_CTRL)
	{
		return Bypass_Write( BPD_AUTOMATIC );
	}

	return true;
}

