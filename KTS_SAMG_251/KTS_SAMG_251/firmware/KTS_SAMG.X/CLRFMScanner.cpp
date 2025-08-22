#include "CLRFMScanner.h"

#include "CLCommunication_Driver.h"
#include "CLCommunicationManager.h"
#include "RFM_driver.h"
#include "CLKTS.h"

CLRFMScanner* gScanner = NULL;

void ComReceivedResponse( byte* rxBuffer, unsigned short deviceId )
{
	if (gScanner == NULL)
		return;

	gScanner->ComReceivedResponse( rxBuffer, deviceId );
}

// =============================================================================
// CLRFMScanner [class]
// -----------------------------------------------------------------------------
CLRFMScanner::CLRFMScanner()
{
	m_Channel		= 0;
	m_State			= 0;
	m_ChannelState	= CLChannelState_Unknow;
}

byte CLRFMScanner::GetChannel()
{
	return m_Channel;
}

CLRFMScanner::CLChannelState CLRFMScanner::GetChannelState()
{
	return (CLChannelState) m_ChannelState;
}

bool CLRFMScanner::IsInProgress()
{
	return m_State & CLState_InProgress;
}

bool CLRFMScanner::Scan( byte channel,
	unsigned short maxMilliseconds )
{
	unsigned long	timeoutTimer	= millis();

	if (m_State & CLState_InProgress)
		return false;

	if (channel < RFM_CHANNELS_MIN)
		channel	= RFM_CHANNELS_MIN;
	else
	if (channel > RFM_CHANNELS_MAX)
		channel	= RFM_CHANNELS_MAX;

	if (maxMilliseconds <= 0)
		maxMilliseconds	= 1;

	// Entra in modalità scanning
	m_SaveRunningMode		= gKTSGlobal.RunningMode;
	gKTSGlobal.RunningMode	= CLKTSRunningMode_Scanning;

	// Attendiamo eventualmente svuotamento queue
	while (gComRequestCount > 0)
	{
		if (millis() - timeoutTimer > 4000)
		{
			// Ripristina stato
			gKTSGlobal.RunningMode	= m_SaveRunningMode;
			return false;
		}

		CLKTS::Process();
		CLKTS::Pir_Process();
	}

	// Impostiamo la comunicazione wireless
	m_SaveComLinkType			= gKTSGlobal.ComLinkType;
	gKTSGlobal.ComLinkType		= BY_WIRELESS;

	// Impostiamo il nuovo gestore ricezione messaggi
	m_SaveComReceiveMessageHandler	= gComReceiveMessageHandler;
	gComReceiveMessageHandler		= ::ComReceivedResponse;

	gScanner						= this;
	m_State							|= CLState_InProgress;
	m_Channel						= channel;
	m_ChannelState					= CLChannelState_InProgress;
	m_MaxMilliseconds				= maxMilliseconds;
	m_CheckChannelStartTimer		= millis();
	m_CheckChannelPacketReceived	= false;
	SetChannelNum( m_Channel );

	return true;
}

bool CLRFMScanner::Process()
{
	if (!(m_State & CLState_InProgress))
		return false;

	if (m_CheckChannelPacketReceived)
	{
		m_ChannelState	= CLChannelState_Busy;
		Stop();
	}
	else
	if (millis() - m_CheckChannelStartTimer >= m_MaxMilliseconds)
	{
		m_ChannelState	= CLChannelState_Free;
		Stop();
	}

	return true;
}

void CLRFMScanner::Stop()
{
	if (!(m_State & CLState_InProgress))
		return;

	// Attendiamo svuotamento queue
	while (gComRequestCount > 0)
	{
		CLKTS::Process();
		CLKTS::Pir_Process();
	}

	gScanner	= NULL;

	// Ripristina configurazione
	gComReceiveMessageHandler	= m_SaveComReceiveMessageHandler;
	gKTSGlobal.ComLinkType		= m_SaveComLinkType;
	gKTSGlobal.RunningMode		= m_SaveRunningMode;
	SetChannelNum( gKTSEeprom.GetRFMChannel() );

	if (m_ChannelState == CLChannelState_InProgress)
		m_ChannelState = CLChannelState_Unknow;

	m_State	&= ~CLState_InProgress;
}

CLKTSRunningMode CLRFMScanner::GetRunningMode()
{
	if (IsInProgress())
		return m_SaveRunningMode;

	return gKTSGlobal.RunningMode;
}

void CLRFMScanner::ComReceivedResponse( byte* rxBuffer, unsigned short deviceId )
{
	if (!(m_State & CLState_InProgress))
		return;

	m_CheckChannelPacketReceived	= true;
}

const char* CLRFMScanner::GetChannelStateText( CLRFMScanner::CLChannelState state )
{
	switch (state)
	{
		case CLChannelState_Unknow:		return "...";
		case CLChannelState_Free:		return CLLocalitation::GetText( CLTextId_RFM__CHANNEL_FREE );
		case CLChannelState_Busy:		return CLLocalitation::GetText( CLTextId_RFM__CHANNEL_BUSY );
		case CLChannelState_InProgress:	return CLLocalitation::GetText( CLTextId_RFM__CHANNEL_INPROGRESS );
	}
	return "";
}
// -----------------------------------------------------------------------------
// CLRFMScanner [class]
// =============================================================================

