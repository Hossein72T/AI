 /*************************************************************************************
 *  File:         CLCommunicationManager.cpp
 *
 *  Author/Date:  Paolo Menchi 3/02/14
 *  
 *  Descrizione:  Funzioni per la gestione comunicazione tra KTS e RD2.0
 *
 *************************************************************************************/

#include "CLCommunicationManager.h"
#include "CLCommunication_Driver.h"
#include "CLKTS.h"

short gComLastReadMessageErrorCode = 0;

SComQueueRequest gComQueueRequests[ COM_QUEUE_MAX_REQUEST ];
int gComRequestCount;
int gComCurrentRequestIndex;

const unsigned long ComSerRequestTimeoutMilliseconds = 1500;
unsigned long gComSerRequestTimeoutPreviousMilliseconds;
unsigned long gComSerLastCallReadMessage;
ComReceiveMessageHandler gComReceiveMessageHandler = NULL;

// Tempo di attesa tra l'ultima ricezione e l'invio di una nuova richiesta
const unsigned long ComRFMTimeBetweenReceiveAndSendMilliseconds = 80;
unsigned long gComRFMLastReceivedMilliseconds;

void Com_Init( int baudRate )
{
	// Inizializza la seriale
	//Serial0.begin( baudRate );

	gComSerRequestTimeoutPreviousMilliseconds	= 0;
	gComCurrentRequestIndex						= -1;
	gComRequestCount							= 0;
	gComSerLastCallReadMessage					= 0;
	gComRFMLastReceivedMilliseconds				= 0;

	for (int counter = 0; counter < COM_QUEUE_MAX_REQUEST; counter++)
	{
		SComQueueRequest*	request	= &gComQueueRequests[ counter ];
		
		request->Free		= 1;
		request->Command	= COMMAND_EMPTY;
	}
}

void Com_SendRequest_TestUnit()
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

	txBuffer[IHM1_POS_CRC_LO]	= IRQT_CRC_LO;
	txBuffer[IHM1_TYPE_COMAND]	= COMMAND_TEST_UNIT;  
 	txBuffer[IRQT_TYPE_TEST]	= 'S';
	txBuffer[IRQT_DATA_1_TEST]	= 't';
	txBuffer[IRQT_DATA_2_TEST]	= 'a';
	
#if KTS_DEMO == 0
	// Invia la richiesta
	Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif
}

void Com_SendRequest_PollingBase()
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

	txBuffer[ IHM1_POS_CRC_LO ]		= IRQP_CRC_LO;
	txBuffer[ IHM1_TYPE_COMAND ]	= COMMAND_POLLING_BASE;  

	txBuffer[ IRQP_DATA_SEC ]			= gRTC.getSecond();
	txBuffer[ IRQP_DATA_MIN ]			= gRTC.getMinute();
	txBuffer[ IRQP_DATA_HOURS ]			= gRTC.getHour();
	txBuffer[ IRQP_DATA_WEEKDAY ]		= gRTC.getWeekday();
	
	txBuffer[ IRQP_DATA_DAY ]			= gRTC.getDay();
	txBuffer[ IRQP_DATA_MOUNTH ]		= gRTC.getMonth();
	txBuffer[ IRQP_DATA_YEAR ]			= gRTC.getYear();
	txBuffer[ IRQP_DATA_CENTURY ]		= gRTC.getCentury();

#if KTS_DEMO == 0
	// Invia la richiesta
	Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif
}

bool Com_SendRequest_ReadEeprom( EEepromSection eepromSection )
{
	switch (eepromSection)
	{
		case EEepromSection_Info:
			Com_SendRequest_ReadEeprom( Eeprom_Info_StartAddress, Eeprom_Info_Count );
			break;

		case EEepromSection_Configuration:
			Com_SendRequest_ReadEeprom( Eeprom_Configuration_StartAddress, Eeprom_Configuration_Count );
			break;

		case EEepromSection_SettingPar:
			Com_SendRequest_ReadEeprom( Eeprom_SettingPar_StartAddress, Eeprom_SettingPar_Count );
			break;

		case EEepromSection_SetTemp:
			Com_SendRequest_ReadEeprom( Eeprom_SetTemp_StartAddress, Eeprom_SetTemp_Count );
			break;

		case EEepromSection_DayProg:
			Com_SendRequest_ReadEeprom( Eeprom_DayProg_StartAddress, Eeprom_DayProg_Count );
			break;

		case EEepromSection_HWSetting:
			Com_SendRequest_ReadEeprom( Eeprom_HWSetting_StartAddress, Eeprom_HWSetting_Count );
			break;
			
		default:
			return false;
	}
	
	return true;
}

void Com_SendRequest_ReadEeprom( byte startAddress, byte count )
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];
	
	txBuffer[ IHM1_POS_CRC_LO ]   = IRQR_CRC_LO;
	txBuffer[ IHM1_TYPE_COMAND ]  = COMMAND_READ_EEPROM;  

	txBuffer[ IRQR_ADDR_BYTE_START_EEP ]	= startAddress;  
	txBuffer[ IRQR_ADDR_NUM_BYTE_EEP ]		= count;  
	
#if KTS_DEMO == 0
	// Invia la richiesta
	Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif

#if KTS_DEBUG == 1
	gKTSGlobal.KTSDebug_ReadEepromCount++;
#endif
}

bool Com_SendRequest_WriteEeprom( EEepromSection eepromSection )
{
	switch (eepromSection)
	{
		case EEepromSection_Info:
			Com_SendRequest_WriteEeprom( Eeprom_Info_StartAddress, Eeprom_Info_Count );
			break;
			
		case EEepromSection_SettingPar:
			Com_SendRequest_WriteEeprom( Eeprom_SettingPar_StartAddress, Eeprom_SettingPar_Count );
			break;

		case EEepromSection_SetTemp:
			Com_SendRequest_WriteEeprom( Eeprom_SetTemp_StartAddress, Eeprom_SetTemp_Count );
			break;

		case EEepromSection_DayProg:
			Com_SendRequest_WriteEeprom( Eeprom_DayProg_StartAddress, Eeprom_DayProg_Count );
			break;
			
		case EEepromSection_HWSetting:
			Com_SendRequest_WriteEeprom( Eeprom_HWSetting_StartAddress, Eeprom_HWSetting_Count );
			break;

		default:
			return false;
	}
	
	return true;
}

void Com_SendRequest_WriteEeprom( byte startAddress, byte count )
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

	if (((int) startAddress + (int) count) <= sizeof(S_EEPROM))
	{
		txBuffer[ IHM1_POS_CRC_LO ]   = IRQR_CRC_LO + count;
		txBuffer[ IHM1_TYPE_COMAND ]  = COMMAND_WRITE_EEPROM;  

		txBuffer[ IRQW_ADDR_BYTE_START_EEP ]	= startAddress;
		txBuffer[ IRQW_ADDR_NUM_BYTE_EEP ]		= count;
	
		memcpy( txBuffer + IRQW_START_DATA_EEPROM, ((byte*) (&gRDEeprom)) + startAddress, count );
	
#if KTS_DEMO == 0
		// Invia la richiesta
		Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif

#if KTS_DEBUG == 1
		gKTSGlobal.KTSDebug_WriteEepromCount++;
#endif
	}
}

void Com_SendRequest_DataDebug()
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

	txBuffer[ IHM1_POS_CRC_LO ]   = IRQD_CRC_LO;
	txBuffer[ IHM1_TYPE_COMAND ]  = COMMAND_DATA_DEBUG;  

#if KTS_DEMO == 0
	// Invia la richiesta
	Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif
}

void Com_SendRequest_AssignId()
{
	byte	txBuffer[ MAX_SERIAL_BUFFER_LENGHT ];

	txBuffer[ IHM1_POS_CRC_LO ]		= IRAI_CRC_LO;
	txBuffer[ IHM1_TYPE_COMAND ]	= COMMAND_ASSIGN_ID_KTS;  
	txBuffer[ IRAI_NUMBER_ID_LO ]	= (byte) (gKTSEeprom.GetDeviceID() & 0xFF);
	txBuffer[ IRAI_NUMBER_ID_HI ]	= (byte) (gKTSEeprom.GetDeviceID() >> 8);
	txBuffer[ IRAI_NONE_0 ]			=
	txBuffer[ IRAI_NONE_1 ]			= 0;

#if KTS_DEMO == 0
	// Invia la richiesta
	Write_Message( txBuffer, gKTSGlobal.ComLinkType );
#endif
}

// ---------------------------------------------------------------
// Receive Response
// ---------------------------------------------------------------
char Com_ReceiveResponse()
{
#if KTS_DEMO == 0
	int  retValue;

	if (!(millis() - gComSerLastCallReadMessage >= 6 ||
		millis() < gComSerLastCallReadMessage))
		return COMMAND_EMPTY;

	gComSerLastCallReadMessage	= millis();

	retValue  = Read_Message();
	if (retValue == BUFFER_RX_EMPY || retValue == RUN_DOWNLOAD)
		return COMMAND_EMPTY;

	// Se il pacchetto non è con lo stesso deviceId, scarto il msg
	// ma lo notifico all'handler
	if (gKTSGlobal.ComLinkType == BY_WIRELESS &&
		sdata_wi.receivedDeviceId != gKTSEeprom.GetDeviceID())
	{
		if (gComReceiveMessageHandler != NULL)
			gComReceiveMessageHandler( sRxBuffer, sdata_wi.receivedDeviceId );

		return COMMAND_EMPTY;
	}

	return sRxBuffer[ IHM1_TYPE_COMAND ];
#else
	return COMMAND_EMPTY;
#endif
}

// ---------------------------------------------------------------
// Manage Queue
// ---------------------------------------------------------------
int ComQueue_AddRequest( byte command,
	byte priority,
	ComQueue_Status* statusAddress,
	ComQueueResponseCallback responseCallback )
{
	for (int counter = 0; counter < COM_QUEUE_MAX_REQUEST; counter++)
	{
		SComQueueRequest*	request	= &gComQueueRequests[ counter ];

		if (request->Free == 1)
		{
			request->Free				= 0;
			request->Command			= command;
			request->Priority			= priority;
			request->StatusAddress		= statusAddress;
			request->ResponseCallback	= responseCallback;
			request->UserData			= NULL;
			gComRequestCount++;

			if (statusAddress != NULL)
				statusAddress->Status	= COM_REQUEST_STATUS_QUEUED;

			return counter;
		}
	}

	if (statusAddress != NULL)
		statusAddress->Status	= COM_REQUEST_STATUS_QUEUE_ERROR;
	
	return -1;
}

bool ComQueue_RemoveRequest( int index, bool cancel )
{
	if (index >= 0 && index < COM_QUEUE_MAX_REQUEST && !gComQueueRequests[ index ].Free)
	{
		SComQueueRequest*	request	= &gComQueueRequests[ index ];

		if (request->StatusAddress != NULL
			&& request->StatusAddress->Status && cancel)
			request->StatusAddress->Status	= COM_REQUEST_STATUS_CANCELED;

		request->Free			= 1;
		request->Command		= COMMAND_EMPTY;
		request->StatusAddress	= NULL;
		gComRequestCount--;
		return true;
	}
	
	return false;
}

int ComQueue_AddTestRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	return ComQueue_AddRequest( COMMAND_TEST_UNIT, COM_REQUEST_PRIORITY_TEST, statusAddress, responseCallback );
}

int ComQueue_AddPollingBaseRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	return ComQueue_AddRequest( COMMAND_POLLING_BASE, COM_REQUEST_PRIORITY_POLLINGBASE, statusAddress, responseCallback );
}

int ComQueue_AddReadEepromRequest( EEepromSection eepromSection, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	switch (eepromSection)
	{
		case EEepromSection_Info:
			return ComQueue_AddReadEepromRequest( Eeprom_Info_StartAddress, Eeprom_Info_Count, statusAddress, responseCallback );

		case EEepromSection_Configuration:
			return ComQueue_AddReadEepromRequest( Eeprom_Configuration_StartAddress, Eeprom_Configuration_Count, statusAddress, responseCallback );

		case EEepromSection_SettingPar:
			return ComQueue_AddReadEepromRequest( Eeprom_SettingPar_StartAddress, Eeprom_SettingPar_Count, statusAddress, responseCallback );

		case EEepromSection_SetTemp:
			return ComQueue_AddReadEepromRequest( Eeprom_SetTemp_StartAddress, Eeprom_SetTemp_Count, statusAddress, responseCallback );

		case EEepromSection_DayProg:
			return ComQueue_AddReadEepromRequest( Eeprom_DayProg_StartAddress, Eeprom_DayProg_Count, statusAddress, responseCallback );

		case EEepromSection_HWSetting:
			return ComQueue_AddReadEepromRequest( Eeprom_HWSetting_StartAddress, Eeprom_HWSetting_Count, statusAddress, responseCallback );
	}
	
	return false;
}

int ComQueue_AddReadEepromRequest( byte startAddress, byte count, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	int			index;
	SComQueueRequest*	request;
	
	if ((index = ComQueue_AddRequest( COMMAND_READ_EEPROM, COM_REQUEST_PRIORITY_READEEPROM, statusAddress, responseCallback )) == -1)
		return -1;

	request								= &gComQueueRequests[ index ];
	request->ReadEeprom.StartAddress	= startAddress;
	request->ReadEeprom.Count			= count;

	return index;
}

int ComQueue_AddWriteEepromRequest( EEepromSection eepromSection, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	switch (eepromSection)
	{
		case EEepromSection_Info:
			return ComQueue_AddWriteEepromRequest( Eeprom_Info_StartAddress, Eeprom_Info_Count, statusAddress, responseCallback );
			
		case EEepromSection_SettingPar:
			return ComQueue_AddWriteEepromRequest( Eeprom_SettingPar_StartAddress, Eeprom_SettingPar_Count, statusAddress, responseCallback );

		case EEepromSection_SetTemp:
			return ComQueue_AddWriteEepromRequest( Eeprom_SetTemp_StartAddress, Eeprom_SetTemp_Count, statusAddress, responseCallback );

		case EEepromSection_DayProg:
			return ComQueue_AddWriteEepromRequest( Eeprom_DayProg_StartAddress, Eeprom_DayProg_Count, statusAddress, responseCallback );

		case EEepromSection_HWSetting:
			return ComQueue_AddWriteEepromRequest( Eeprom_HWSetting_StartAddress, Eeprom_HWSetting_Count, statusAddress, responseCallback );
	}
	
	return false;
}

int ComQueue_AddWriteEepromRequest( byte startAddress, byte count, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	int					index;
	SComQueueRequest*	request;

	if ((index = ComQueue_AddRequest( COMMAND_WRITE_EEPROM, COM_REQUEST_PRIORITY_WRITEEEPROM, statusAddress, responseCallback )) == -1)
		return -1;

	request								= &gComQueueRequests[ index ];
	request->WriteEeprom.StartAddress	= startAddress;
	request->WriteEeprom.Count			= count;
	if (statusAddress != NULL)
		memset( statusAddress, 0, sizeof(ComQueue_Status) );

	return index;
}

int ComQueue_AddDataDebugRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	return ComQueue_AddRequest( COMMAND_DATA_DEBUG, COM_REQUEST_PRIORITY_DATADEBUG, statusAddress, responseCallback );
}

int ComQueue_AddAssignId( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback )
{
	return ComQueue_AddRequest( COMMAND_ASSIGN_ID_KTS,
		COM_REQUEST_PRIORITY_DATADEBUG,
		statusAddress,
		responseCallback );
}

// TODO: Vedere se si riesce a spostarla in CLKTS --> da spostare in TestUnitForm, ma??? (posso ricevere delle risposte senza richiesta, da valutare)
void ComQueue_ReceivedResponse( byte* rxBuffer )
{
	if (gComReceiveMessageHandler != NULL)
		gComReceiveMessageHandler( rxBuffer, gKTSEeprom.GetDeviceID() );

    switch (sRxBuffer[ IHM1_TYPE_COMAND ])
	{
		case COMMAND_TEST_UNIT:
			//   messaggio di inizio test: 's', 'm', 8, 'T', 'S' ,'t', 'a', CK_16
			//   messaggio di   fine test: 's', 'm', 8, 'T', 'E' ,'n', 'd', CK_16
			if ((rxBuffer[IRQT_TYPE_TEST] == 'S') && (rxBuffer[IRQT_DATA_1_TEST] == 't'))
			{
				gKTSGlobal.DisableTX = 'D';
				DisablePinTX();
			}
			else if	((rxBuffer[IRQT_TYPE_TEST] == 'E') && (rxBuffer[IRQT_DATA_1_TEST] == 'n'))
			{
				gKTSGlobal.DisableTX = 0;
				EnablePinTX();
			}
			else
			{
				gKTSGlobal.DataTest[ 0 ]	= rxBuffer[ IRQT_TYPE_TEST ];
				gKTSGlobal.DataTest[ 1 ]	= rxBuffer[ IRQT_DATA_1_TEST ];
				gKTSGlobal.DataTest[ 2 ]	= rxBuffer[ IRQT_DATA_2_TEST ];
			}
			break;
	}
}

void ComQueue_Process()
{
	char	receivedCommand;
	
	receivedCommand	= Com_ReceiveResponse();

	// Se esiste una richiesta in corso, controlla il timeout
	if (gComCurrentRequestIndex != -1)
	{
		SComQueueRequest*	request	= &gComQueueRequests[ gComCurrentRequestIndex ];
		ComQueue_Status*	status	= request->StatusAddress;
		
#if KTS_DEMO == 1
		if (request->Command == COMMAND_WRITE_EEPROM)
		{
			receivedCommand				= COMMAND_WRITE_EEPROM;
			sRxBuffer[ IRSW_RESULT_W ]	= '0';
		}
#endif

		// Non dovrebbe capitare, ma nel caso...
		if (request->Free)
			gComCurrentRequestIndex	= -1;
		else
		// Ok, response ricevuta
		if (receivedCommand != COMMAND_EMPTY && receivedCommand == request->Command)
		{
			// Aggiorna lo stato
			if (status != NULL)
			{
				switch (receivedCommand)
				{
					case COMMAND_READ_EEPROM:
						if (request->ReadEeprom.StartAddress == sRxBuffer[ IRSR_ADDR_BYTE_START_EEP ] &&
							request->ReadEeprom.Count == sRxBuffer[ IRSR_ADDR_NUM_BYTE_EEP ])
							status->Status	= COM_REQUEST_STATUS_COMPLETED;
						else
							status->Status	= COM_READEEPROM_STATUS_RESPONSE_ERROR;
						break;

					case COMMAND_WRITE_EEPROM:
#if KTS_DEBUG == 1
						gKTSGlobal.KTSDebug_LastWriteEepromResult	= sRxBuffer[ IRSW_RESULT_W ];
#endif

						switch (sRxBuffer[ IRSW_RESULT_W ])
						{
							case '0':
								status->Status						= COM_REQUEST_STATUS_COMPLETED;
#if KTS_DEBUG == 1
								gKTSGlobal.KTSDebug_WriteEepromOkCount++;
#endif
								break;
							
							case '1':
								status->Status	= COM_WRITEEEPROM_STATUS_RESPONSE_ZONEERROR;
#if KTS_DEBUG == 1
								gKTSGlobal.KTSDebug_WriteEepromErrorCount++;
#endif
								break;

							case '2':
								status->Status	= COM_WRITEEEPROM_STATUS_RESPONSE_DATAERROR;
#if KTS_DEBUG == 1
								gKTSGlobal.KTSDebug_WriteEepromErrorCount++;
#endif
								break;

							case '3':
								status->Status	= COM_WRITEEEPROM_STATUS_RESPONSE_DEVICEBUSY;
#if KTS_DEBUG == 1
								gKTSGlobal.KTSDebug_WriteEepromErrorCount++;
#endif
								break;

							default:
								status->Status	= COM_WRITEEEPROM_STATUS_RESPONSE_UNKNOWERROR;
#if KTS_DEBUG == 1
								gKTSGlobal.KTSDebug_WriteEepromErrorCount++;
#endif
								break;
						}
						status->WriteEeprom_IRSW_RESULT_W	= sRxBuffer[ IRSW_RESULT_W ];
						break;
						
					default:
						status->Status	= COM_REQUEST_STATUS_COMPLETED;
						break;
				}
			}
			
			if (request->ResponseCallback != NULL)
				(request->ResponseCallback)( sRxBuffer, request->UserData );
			
			gComRFMLastReceivedMilliseconds	= millis();
			ComQueue_ReceivedResponse( sRxBuffer );

			ComQueue_RemoveRequest( gComCurrentRequestIndex, false );
			gComCurrentRequestIndex	= -1;
		}
		else
		// Se superato il tempo di timeout
		if (millis() - gComSerRequestTimeoutPreviousMilliseconds >= ComSerRequestTimeoutMilliseconds ||
			millis() < gComSerRequestTimeoutPreviousMilliseconds)
		{
			if (status != NULL)
			{
				status->Status	= COM_REQUEST_STATUS_TIMEOUT;
#if KTS_DEBUG == 1
				gKTSGlobal.KTSDebug_WriteEepromErrorCount++;
#endif
			}
				
			ComQueue_RemoveRequest( gComCurrentRequestIndex, false );
			gComCurrentRequestIndex	= -1;
		}
		// Altrimenti esce, aspetto la risposta della richiesta corrente o eventualmente il timeout
		else
			return;
	}
	else
	{
		if (receivedCommand != COMMAND_EMPTY)
		{
			gComRFMLastReceivedMilliseconds	= millis();
			ComQueue_ReceivedResponse( sRxBuffer );
		}
	}

	if (gComRequestCount)
	{
		int	selectedRequestIndex	= -1;
		int	selectedRequestValue	= 0xff;

		// Nella modalità RFM attende ComRFMTimeBetweenRequestsMilliseconds
		// dall'ultima ricezione
		if (gKTSGlobal.ComLinkType == BY_WIRELESS &&
			millis() - gComRFMLastReceivedMilliseconds < ComRFMTimeBetweenReceiveAndSendMilliseconds)
		{
			return;
		}

		// Ricerca la request da inviare con la priority più bassa
		for (int counter = 0; counter < COM_QUEUE_MAX_REQUEST; counter++)
		{
			SComQueueRequest*	request	= &gComQueueRequests[ counter ];
		
			if (!request->Free)
			{
				// Non dovrebbe succedere ma se per qualche motivo succede, lo gestisco
				if (request->Command == COMMAND_EMPTY)
					ComQueue_RemoveRequest( gComCurrentRequestIndex, false );
				else
				{
					if (selectedRequestValue > request->Priority)
					{
						selectedRequestValue	= request->Priority;
						selectedRequestIndex	= counter;
					}
				}
			}
		}

		// Se è stata selezionata una richiesta, si procede al suo invio
		if (selectedRequestIndex != -1)
		{
			SComQueueRequest*	request	= &gComQueueRequests[ selectedRequestIndex ];
			ComQueue_Status*	status	= request->StatusAddress;

			gComCurrentRequestIndex	= selectedRequestIndex;

			if (status != NULL)
				status->Status	= COM_REQUEST_STATUS_WAITING_RESPONSE;
			
			switch (request->Command)
			{
				case COMMAND_READ_EEPROM:
					Com_SendRequest_ReadEeprom( request->ReadEeprom.StartAddress,
						request->ReadEeprom.Count );
					break;

				case COMMAND_WRITE_EEPROM:
					Com_SendRequest_WriteEeprom( request->WriteEeprom.StartAddress,
						request->WriteEeprom.Count );
					break;
					
				case COMMAND_DATA_DEBUG:
					Com_SendRequest_DataDebug();
					break;
					
				case COMMAND_POLLING_BASE:
					Com_SendRequest_PollingBase();
					break;
					
				case COMMAND_TEST_UNIT:
					Com_SendRequest_TestUnit();
					break;					

				case COMMAND_ASSIGN_ID_KTS:
					Com_SendRequest_AssignId();
					break;					
			}

			gComSerRequestTimeoutPreviousMilliseconds	= millis();
		}
	}

}

int ComQueue_ContainsCommand( byte command )
{
	// Scansione di tutte le request
	for (int counter = 0; counter < COM_QUEUE_MAX_REQUEST; counter++)
	{
		if (!gComQueueRequests[ counter ].Free && gComQueueRequests[ counter ].Command == command)
			return counter;
	}
	
	return -1;
}

int ComQueue_ContainsCommand( byte command, ComQueueResponseCallback responseCallback )
{
	// Scansione di tutte le request
	for (int counter = 0; counter < COM_QUEUE_MAX_REQUEST; counter++)
	{
		if (!gComQueueRequests[ counter ].Free &&
			gComQueueRequests[ counter ].Command == command &&
			gComQueueRequests[ counter ].ResponseCallback == responseCallback)
			return counter;
	}
	
	return -1;
}

