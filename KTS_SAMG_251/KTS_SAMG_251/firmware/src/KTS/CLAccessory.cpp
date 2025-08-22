#include "CLAccessory.h"
#include "CLKTS.h"
#include "CLTouch.h"
#include "CLCommunicationManager.h"
#include "CLLCDCommon.h"

#include "CLMessageBoxForm.h"

const char* AccessoryNames[] =
{
	CLFixedText_IPHED,  "PHWD",  "HWD", "EHD", "CWD",  "AWP", CLFixedText_BPD, "DXD",
	"MBUS",  "RFM", "DPPV2", "OUT", "INP", "PCAP", "PCAF", "DPS",
	"EBPD2", "P1VOC", "SSR", "P1RH", "P2RH", "EBPD", "P1CO2", "P2CO2",
	"EXT1", "EXT2", "EXT3", "EXT4", "CAPS", "CAPR", "DSC", NULL
};

bool Accessory_IsPresent( int accessoryIndex )
{
	return AccessoryNames[ accessoryIndex ] != NULL && bitRead( gRDEeprom.AccessoyHW[ (accessoryIndex >> 3) ], accessoryIndex & 0x07 );
}

bool Accessory_Set( int accessoryIndex, bool value )
{
	bitWrite( gRDEeprom.AccessoyHW[ (accessoryIndex >> 3) ], accessoryIndex & 0x07, (value ? 1 : 0) );
	return true;
}

void Accessory_GetCommandText( char* text, byte status )
{
	if (bitRead( status, 3 ))
		strcpy( text, CLFixedText_ON );
	else
		strcpy( text, CLFixedText_OFF );
}

void Accessory_GetStatusText( char* text, byte status )
{
	*text	= '\0';

	if (bitRead( status, 4 ))
		strcat( text, CLLocalitation::GetText( CLTextId_IN_ALARM ) );

	if (strlen( text ) > 0)
		strcat( text, " / " );
	if (bitRead( status, 2 ))
		strcat( text, CLFixedText_ON );
	else
		strcat( text, CLFixedText_OFF );

	if (!bitRead( status, 0 ))
	{
		if (strlen( text ) > 0)
			strcat( text, " / " );
		strcat( text, CLLocalitation::GetText( CLTextId_NOT_CONNECTED ) );
	}
}

int Accessory_GetPresentCount()
{
	int	accessoryCount	= 0;

	for (int accessoriesCounter = 0; accessoriesCounter < AccessoryCount; accessoriesCounter++)
	{
		if (Accessory_IsPresent( accessoriesCounter ))
			accessoryCount++;
	}

	return accessoryCount;
}

bool Accessory_CO2IsPresent()
{
	return Accessory_IsPresent( ACC_EEP_P1CO2 ) ||
		Accessory_IsPresent( ACC_EEP_P2CO2 );
}

bool Accessory_RHIsPresent()
{
	return Accessory_IsPresent( ACC_EEP_P1RH ) ||
		Accessory_IsPresent( ACC_EEP_P2RH );
}

bool Accessory_VOCIsPresent()
{
	return Accessory_IsPresent( ACC_EEP_P1VOC );
}

bool Accessory_HasCooler()
{
	return Accessory_IsPresent( ACC_EEP_CWD )
		|| Accessory_IsPresent( ACC_EEP_DXD );
}

bool Accessory_HasHeather()
{
	return Accessory_IsPresent( ACC_EEP_HWD )
		|| Accessory_IsPresent( ACC_EEP_EHD )
		|| Accessory_IsPresent( ACC_EEP_SSR )
		|| Accessory_IsPresent( ACC_EEP_DXD );
}

bool Accessory_HasPreCooler()
{
	return Accessory_IsPresent( ACC_EEP_PEHD )
		|| Accessory_IsPresent( ACC_EEP_PHWD );
}

bool AccessoryDPP_SendRequest( bool filterLevel )
{
	ComQueue_Status	writeEeprom_Status;

	if (gRDEeprom.DPP_FilterLevel & 0x01)
		return true;

	// Salva i valori correnti
	gRDEeprom.DPP_FilterLevel	&= 0xFC;
	if (filterLevel)
		gRDEeprom.DPP_FilterLevel	|= 0x03;
	else
		gRDEeprom.DPP_FilterLevel	|= 0x01;

	// Accoda la richiesta di WriteEeprom per impostare i step motors
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, DPP_FilterLevel ),
		sizeof(gRDEeprom.DPP_FilterLevel),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valori precedenti
		gRDEeprom.DPP_FilterLevel	&= 0xFC;
		return false;
	}

	return true;
}

bool AccessoryDPP_Request( bool readFilterLevel )
{
	enum _State
	{
		State_Starting,
		State_Running,
		State_Completed,
	};

	_State	State		= State_Starting;
	bool	retValue	= false;
	bool	exit		= false;

	CLKTS::SuspendScreenSaver();

	if (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNo,
		CLMessageBoxGravity_Question,
		CLLocalitation::GetText( readFilterLevel ? CLTextId_DPP_FILTER_LEVEL : CLTextId_DPP_CALIBRATION ),
		CLLocalitation::GetText( CLTextId_PROCEDURE_STARTING_MESSAGE ) ) == CLMessageBoxResult_Yes)
	{
		CLMessageBoxForm::RenderPanel( CLMessageBoxGravity_Info,
			CLLocalitation::GetText( readFilterLevel ? CLTextId_DPP_FILTER_LEVEL : CLTextId_DPP_CALIBRATION ),
			CLLocalitation::GetText( CLTextId_PROCEDURE_RUNNING_MESSAGE ) );

		while (!exit)
		{
			int		touchX, touchY;

			// Processa le funzionalità del KTS
			CLKTS::Process();
			CLKTS::Pir_Process();
			
			switch (State)
			{
				case State_Starting:
					// Avvia richiesta
					if (!AccessoryDPP_SendRequest( readFilterLevel ))
					{
						CLLCDCommon::WriteDataPanel_DisplayError();
						exit		= true;
						retValue	= false;
						break;
					}
					State	= State_Running;
					continue;

				case State_Running:
					if (!(gRDEeprom.DPP_FilterLevel & 0x03))
						State	= State_Completed;
					continue;

				case State_Completed:
					CLLCDCommon::RenderPanelInfo( (char*) CLLocalitation::GetText( CLTextId_PROCEDURE_COMPLETED_MESSAGE ),
						0x65b483, RGBColor_White, RGBColor_Black,
						2000 );

					exit		= true;
					retValue	= true;
					break;
			}

			if (exit)
				break;

			if (Touched())
			{
				touchX	= ReadX();
				touchY	= ReadY();
			}
		}
	}
	
	CLKTS::ResumeScreenSaver();
	
	return retValue;
}

