 /*************************************************************************************
 *  file:			CLSelectRFMChannelForm.h
 *
 *  Author/Date:	Paolo Menchi maggio 2015
 *
 *  Descrizione:	Form per la selezione del channel RFM
 *
 *************************************************************************************/

#ifndef __CLRFMSelectChannelForm_h
#define __CLRFMSelectChannelForm_h

#include "CLForm.h"
#include "CLKTS.h"
#include "CLCommunication_Driver.h"
#include "CLRFMScanner.h"

CLFormResult CLRFMSelectChannelForm_Open( unsigned short options,
	byte extOptions );

const int MaxSerialNumber = 4;

// =============================================================================
// CLRFMSelectChannelForm [class]
// =============================================================================
// Description: Form per la selezione del channel RFM
// -----------------------------------------------------------------------------
class _PACK CLRFMSelectChannelForm
	: public CLForm
{
	private: enum CLExtState
	{
		CLExtState_Default		= 0x00,
		CLExtState_KTSInvalid	= 0x01,
	};

	public: enum CLExtOption
	{
		CLExtOption_HighlightCurrentChannel	= 0x01,
		CLExtOption_NoAutoScanning			= 0x02
	};

	public: CLRFMSelectChannelForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_SelectedChannelUpButtonRectangle;
	private: CLRectangle m_SelectedChannelDownButtonRectangle;

	private: CLRectangle m_ScanButtonRectangle;

	private: CLProgressiveTouchUpDown m_Channel_ProgressiveTouchUpDown;
	private: unsigned short m_Options;
	private: byte m_ExtOptions;

	private: byte m_ExtState;
	private: byte m_ChannelStates[ RFM_CHANNELS_MAX ];

	public: CLFormResult Open( unsigned short options,
		byte extOptions );

	private: void RenderPage();
	private: void RenderDynamicObjects();
	
	private: byte m_FirstDisplayedChannel;
	private: byte m_SelectedChannel;
	private: void RefreshChannels();

	private: CLRFMScanner m_Scanner;
	private: byte m_Scanner_CurrentChannel;
	private: bool m_Scanner_InProgress;

	private: bool Scan_Start();
	private: void Scan_Stop();
	private: void Scan_Process();

	private: bool Save( unsigned short options );

	private: void SetSelectedChannel( byte channel );
};
// -----------------------------------------------------------------------------
// CLRFMSelectChannelForm [class]
// =============================================================================

#endif

