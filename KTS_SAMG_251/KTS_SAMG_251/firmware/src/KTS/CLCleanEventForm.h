 /*************************************************************************************
 *  file:			CLCleanEventForm.h
 *
 *  Author/Date:	Zakari marzo 2025
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLCleanEventForm_h
#define __CLCleanEventForm_h

#include "CLForm.h"

CLFormResult CLCleanEventForm_Open( unsigned short options );

// =============================================================================
// CLCleanEventForm [class]
// =============================================================================
// Description: Form per la configurazione della modalità Clean Event
// -----------------------------------------------------------------------------
class _PACK CLCleanEventForm
	: public CLForm
{
	public: CLCleanEventForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: CLProgressiveTouchUpDown m_Days_ProgressiveTouchUpDown;

	private: bool m_Enabled;
	public: void SetEnabled( bool value );

	private: byte m_Days;
	public: void SetDays( bool value);

	private: bool IsDataChanged();

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOnOffButtons();
	private: void RenderDays();

	private: void RenderOkButton();
};
// -----------------------------------------------------------------------------
// CLCleanEventForm [class]
// =============================================================================

#endif

