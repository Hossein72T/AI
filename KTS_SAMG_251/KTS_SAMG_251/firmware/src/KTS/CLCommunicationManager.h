 /*************************************************************************************
 *  file: CLCommunicationManager.h
 *
 *  Author/Date: Paolo Menchi 04/02/2014
 *  
 *  Descrizione:   Funzioni per la gestione comunicazione tra KTS e RD2.0
 *
 *  Esempio:
 *        
 *************************************************************************************/
 
#ifndef __CLCommunicationManager_H
#define __CLCommunicationManager_H

#include "CLCommon.h"
#include "RDEeprom.h"
#include "RDProtocol.h"

typedef void (*ComQueueResponseCallback)( byte* rxBuffer, void* userData );
typedef void (*ComReceiveMessageHandler)( byte* rxBuffer, unsigned short deviceId );
extern ComReceiveMessageHandler gComReceiveMessageHandler;
extern short gComLastReadMessageErrorCode;

struct _PACK ComQueue_Status
{
	byte	Status;
	union
	{
		byte WriteEeprom_IRSW_RESULT_W;
	};
};


// --------------------------
// Queue
// --------------------------
struct _PACK SComQueueRequest
{
	char Command;
	
	struct
	{
		byte Free		: 1;
		byte Priority	: 3;
	} _PACK;

	union
	{
		struct
		{
			byte StartAddress;
			byte Count;
		} _PACK ReadEeprom;
		struct
		{
			byte StartAddress;
			byte Count;
		} _PACK WriteEeprom;
	};

	ComQueue_Status* StatusAddress;
	ComQueueResponseCallback ResponseCallback;
	void* UserData;
};

#define COM_QUEUE_MAX_REQUEST	7

extern SComQueueRequest gComQueueRequests[ COM_QUEUE_MAX_REQUEST ];
extern int gComRequestCount;
extern int gComCurrentRequestIndex;

// --------------------------
// EEprom
// --------------------------
typedef enum
{
	EEepromSection_Info,
	EEepromSection_Configuration,
	EEepromSection_SettingPar,
	EEepromSection_SetTemp,
	EEepromSection_DayProg,
	EEepromSection_HWSetting
} EEepromSection;

#define Eeprom_Info_StartAddress			offsetof( S_EEPROM, AddrUnit )
#define Eeprom_Info_EndAddress				(offsetof( S_EEPROM, cntUpdate_info ) + sizeof(gRDEeprom.cntUpdate_info) - 1)
#define Eeprom_Info_Count					((Eeprom_Info_EndAddress - Eeprom_Info_StartAddress) + 1)

#define Eeprom_Configuration_StartAddress	offsetof( S_EEPROM, numMotors )
#define Eeprom_Configuration_EndAddress		(offsetof( S_EEPROM, size2_free ) + sizeof(gRDEeprom.size2_free) - 1)
#define Eeprom_Configuration_Count			((Eeprom_Configuration_EndAddress - Eeprom_Configuration_StartAddress) + 1)

#define Eeprom_SettingPar_StartAddress		offsetof( S_EEPROM, Set_Power_ON )
#define Eeprom_SettingPar_EndAddress		(offsetof( S_EEPROM, cntUpdate_SettingPar ) + sizeof(gRDEeprom.cntUpdate_SettingPar) - 1)
#define Eeprom_SettingPar_Count				((Eeprom_SettingPar_EndAddress - Eeprom_SettingPar_StartAddress) + 1)

#define Eeprom_SetTemp_StartAddress			offsetof( S_EEPROM, Bypass_minTempExt )
#define Eeprom_SetTemp_EndAddress			(offsetof( S_EEPROM, cntUpdate_SetTemp ) + sizeof(gRDEeprom.cntUpdate_SetTemp) - 1)
#define Eeprom_SetTemp_Count				((Eeprom_SetTemp_EndAddress - Eeprom_SetTemp_StartAddress) + 1)

#define Eeprom_DayProg_StartAddress			offsetof( S_EEPROM, sDayProg )
#define Eeprom_DayProg_EndAddress			(offsetof( S_EEPROM, cntUpdate_dayProg ) + sizeof(gRDEeprom.cntUpdate_dayProg) - 1)
#define Eeprom_DayProg_Count				((Eeprom_DayProg_EndAddress - Eeprom_DayProg_StartAddress) + 1)

#define Eeprom_HWSetting_StartAddress		offsetof( S_EEPROM, numMotors )
#define Eeprom_HWSetting_EndAddress			(offsetof( S_EEPROM, size2_free ) + sizeof(gRDEeprom.size2_free) - 1)
#define Eeprom_HWSetting_Count				((Eeprom_HWSetting_EndAddress - Eeprom_HWSetting_StartAddress) + 1)

// --------------------------
// Command
// --------------------------
#define COMMAND_EMPTY '\0'

#define COM_REQUEST_PRIORITY_TEST			1
#define COM_REQUEST_PRIORITY_READEEPROM		2
#define COM_REQUEST_PRIORITY_WRITEEEPROM	3
#define COM_REQUEST_PRIORITY_POLLINGBASE	4
#define COM_REQUEST_PRIORITY_DATADEBUG		6

// --------------------------
// Status
// --------------------------
#define COM_REQUEST_STATUS_QUEUED						0x00
#define COM_REQUEST_STATUS_QUEUE_ERROR					0x01
#define COM_REQUEST_STATUS_WAITING_RESPONSE				0x02
#define COM_REQUEST_STATUS_COMPLETED					0x03
#define COM_REQUEST_STATUS_TIMEOUT						0x04
#define COM_REQUEST_STATUS_CANCELED						0x05

#define COM_READEEPROM_STATUS_RESPONSE_ERROR			0x06

#define COM_WRITEEEPROM_STATUS_RESPONSE_ZONEERROR		0x07
#define COM_WRITEEEPROM_STATUS_RESPONSE_DATAERROR		0x08
#define COM_WRITEEEPROM_STATUS_RESPONSE_DEVICEBUSY		0x09
#define COM_WRITEEEPROM_STATUS_RESPONSE_UNKNOWERROR		0x10

#define COM_REQUEST_ISRUNNING( status ) (status.Status == COM_REQUEST_STATUS_QUEUED || status.Status == COM_REQUEST_STATUS_WAITING_RESPONSE ? true : false)

// ----------
// Prototypes
// ----------
void Com_Init( int baudRate );
void Com_SendRequest_PollingBase();
bool Com_SendRequest_ReadEeprom( EEepromSection eepromSection );
void Com_SendRequest_ReadEeprom( byte startAddress, byte count );
bool Com_SendRequest_WriteEeprom( EEepromSection eepromSection );
void Com_SendRequest_WriteEeprom( byte startAddress, byte count );
void Com_SendRequest_DataDebug();
void Com_SendRequest_AssignId();
void Com_SendRequest_TestUnit();
char Com_ReceiveResponse();

void Com_SendRequest_Debug( char* data );
void Com_SendRequest_Debug( byte* data, short count );

// Queue Manage
int ComQueue_ContainsCommand( byte command );
int ComQueue_ContainsCommand( byte command, ComQueueResponseCallback responseCallback );
bool ComQueue_RemoveRequest( int index, bool cancel );
void ComQueue_Process();
int ComQueue_AddRequest( byte command, byte priority, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue Polling Base
int ComQueue_AddPollingBaseRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue Read Eeprom
int ComQueue_AddReadEepromRequest( EEepromSection eepromSection, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );
int ComQueue_AddReadEepromRequest( byte startAddress, byte count, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue Write Eeprom
int ComQueue_AddWriteEepromRequest( EEepromSection eepromSection, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );
int ComQueue_AddWriteEepromRequest( byte startAddress, byte count, ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue Data Debug
int ComQueue_AddDataDebugRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue Test
int ComQueue_AddTestRequest( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

// Add Queue AssignId
int ComQueue_AddAssignId( ComQueue_Status* statusAddress, ComQueueResponseCallback responseCallback );

#endif

