 /*************************************************************************************
 *  file:			CLUnbalanceConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/
#ifndef __CLUnbalanceConfigForm_h
#define __CLUnbalanceConfigForm_h

#include "CLForm.h"

CLFormResult CLUnbalanceConfigForm_Open( unsigned short options );

// =============================================================================
// CLUnbalanceConfigForm [class]
// =============================================================================
// Description: Form per la configurazione dell'unbalance mode
// -----------------------------------------------------------------------------
class _PACK CLUnbalanceConfigForm
	: public CLForm
{
	public: CLUnbalanceConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: bool m_Enabled;
	public: void SetEnabled( bool value );

	private: signed char m_Value;
	public: void SetValue( signed char value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderOnOffButtons();
	private: void RenderProgressBar();
};
// -----------------------------------------------------------------------------
// CLUnbalanceConfigForm [class]
// =============================================================================

#endif

