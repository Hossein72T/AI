  /*************************************************************************************
 *  file:			CLOutputConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLOutputConfigForm_h
#define __CLOutputConfigForm_h

#include "CLForm.h"

CLFormResult CLOutputConfigForm_Open( unsigned short options );

// =============================================================================
// CLOutputConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle porte di output
// -----------------------------------------------------------------------------
class _PACK CLOutputConfigForm
	: public CLForm
{
	public: CLOutputConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_Output1ButtonRectangle;
	private: CLRectangle m_Output2ButtonRectangle;

	private: CLRectangle m_EventDisableButtonRectangle;
	private: CLRectangle m_EventBypassOpenButtonRectangle;
	private: CLRectangle m_EventUnitRunButtonRectangle;
	private: CLRectangle m_EventUnitFaultButtonRectangle;
	private: CLRectangle m_EventValveButtonRectangle;
	private: CLRectangle m_EventSumWinButtonRectangle;
	private: CLRectangle m_EventMaxSpeedButtonRectangle;

	private: CLRectangle m_Action1ButtonRectangle;
	private: CLRectangle m_Action2ButtonRectangle;

	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;

	private: CLGraphicStyle m_ActionSelectedButtonStyle;
	private: CLGraphicStyle m_ActionNormalButtonStyle;

	private: CLPage m_Page;

	private: byte m_SelectedOutputIndex;
	private: byte m_SetOutputs[ 2 ];

	public: void SelectOutput( byte index );
	public: void SetOutput( byte index, byte value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOutputButtons();
	private: void RenderOutputConfigButtons();
};
// -----------------------------------------------------------------------------
// CLOutputConfigForm [class]
// =============================================================================

#endif

