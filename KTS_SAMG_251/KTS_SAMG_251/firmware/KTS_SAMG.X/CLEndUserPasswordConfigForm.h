 /*************************************************************************************
 *  file:			CLEndUserPasswordConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLEndUserPasswordConfigForm_h
#define __CLEndUserPasswordConfigForm_h

#include "CLForm.h"

CLFormResult CLEndUserPasswordConfigForm_Open( unsigned short options );

// =============================================================================
// CLEndUserPasswordConfigForm [class]
// =============================================================================
// Description: Form per la configurazione della password dell'utente finale
// -----------------------------------------------------------------------------
class _PACK CLEndUserPasswordConfigForm
	: public CLForm
{
	public: CLEndUserPasswordConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_ChangePasswordButtonRectangle;

	private: CLGraphicStyle m_ChangePasswordNormalButtonStyle;

	private: bool m_PasswordEnabled;

	public: void SetEnabled( bool value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOnOffButton();
};
// -----------------------------------------------------------------------------
// CLEndUserPasswordConfigForm [class]
// =============================================================================

#endif

