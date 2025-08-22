 /*************************************************************************************
 *  file:			CLRFMScanner.h
 *
 *  Author/Date:	Paolo Menchi maggio 2015
 *
 *  Descrizione:	Funzioni per la scansione dei canali RFM
 *
 *************************************************************************************/

#ifndef __CLRFMScanner_h
#define __CLRFMScanner_h

#include "CLCommon.h"
#include "CLKTS.h"
#include "CLCommunicationManager.h"

// =============================================================================
// CLRFMScanner [class]
// =============================================================================
// Description: Classe per la scansione dei canali RFM
// -----------------------------------------------------------------------------
class _PACK CLRFMScanner
{
	public: enum CLChannelState
	{
		CLChannelState_Unknow,
		CLChannelState_InProgress,
		CLChannelState_Free,
		CLChannelState_Busy
	};

	public: CLRFMScanner();

	private: ComReceiveMessageHandler m_SaveComReceiveMessageHandler;
	private: CLKTSRunningMode m_SaveRunningMode;
	public: CLKTSRunningMode GetRunningMode();

	private: char m_SaveComLinkType;
	
	private: enum CLState
	{
		CLState_InProgress	= 0x01
	};

	private: byte m_State;
	private: unsigned short m_MaxMilliseconds;
	private: unsigned long m_CheckChannelStartTimer;
	private: byte m_Channel;
	private: byte m_ChannelState;
	private: bool m_CheckChannelPacketReceived;

	public: byte GetChannel();
	public: CLChannelState GetChannelState();
	public: static const char* GetChannelStateText( CLRFMScanner::CLChannelState state );

	public: bool IsInProgress();

	public: bool Scan( byte channel, unsigned short maxMilliseconds );
	public: bool Process();
	public: void Stop();

	public: void ComReceivedResponse( byte* rxBuffer, unsigned short deviceId );
};
// -----------------------------------------------------------------------------
// CLRFMScanner [class]
// =============================================================================

#endif

