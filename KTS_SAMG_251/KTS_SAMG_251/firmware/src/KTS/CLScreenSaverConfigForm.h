 /*************************************************************************************
 *  file:			CLScreenSaverConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLScreenSaverConfigForm_h
#define __CLScreenSaverConfigForm_h

#include "CLForm.h"
#include "CLScreenSaver.h"

CLFormResult CLScreenSaverConfigForm_Open( unsigned short options );

// =============================================================================
// CLScreenSaverConfigForm [class]
// =============================================================================
// Description: Form per la configurazione dello screen saver
// -----------------------------------------------------------------------------
class _PACK CLScreenSaverConfigForm
	: public CLForm
{
	public: CLScreenSaverConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: bool m_Enabled;
	public: void SetEnabled( bool value );

	private: short m_Minutes;
	public: void SetMinutes( short value );

	private: bool IsDataChanged();

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOnOffButtons();
	private: void RenderMinutes();
};
// -----------------------------------------------------------------------------
// CLScreenSaverConfigForm [class]
// =============================================================================

#endif

