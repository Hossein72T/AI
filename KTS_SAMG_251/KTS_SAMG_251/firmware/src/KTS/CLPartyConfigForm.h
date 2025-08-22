 /*************************************************************************************
 *  file:			CLPartyConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLPartyConfigForm_h
#define __CLPartyConfigForm_h

#include "CLForm.h"

CLFormResult CLPartyConfigForm_Open( unsigned short options );

// =============================================================================
// CLPartyConfigForm [class]
// =============================================================================
// Description: Form per la configurazione della modalità party
// -----------------------------------------------------------------------------
class _PACK CLPartyConfigForm
	: public CLForm
{
	public: CLPartyConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_Minutes_ProgressiveTouchUpDown;

	private: bool m_Enabled;
	public: void SetEnabled( bool value );

	private: byte m_Minutes;
	public: void SetMinutes( int value );

	private: bool IsDataChanged();

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOnOffButtons();
	private: void RenderMinutes();

	private: void RenderOkButton();
};
// -----------------------------------------------------------------------------
// CLPartyConfigForm [class]
// =============================================================================

#endif

