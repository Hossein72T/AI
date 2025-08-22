 /*************************************************************************************
 *  file:			CLPirDelayUpdateConfigForm.h
 *
 *  Author/Date:	Zakaria taleb bendiab February 2022
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLPirDelayUpdateConfigForm_h
#define __CLPirDelayUpdateConfigForm_h

#include "CLForm.h"

#define PIR_UPDATE_DELAY_MIN	3
#define PIR_UPDATE_DELAY_MAX	30

CLFormResult CLPirDelayUpdateConfigForm_Open( unsigned short options );

// =============================================================================
// CLPirDelayUpdateConfigForm [class]
// =============================================================================
// Description: Form per la configurazione dello PIR delay
// -----------------------------------------------------------------------------
class _PACK CLPirDelayUpdateConfigForm
	: public CLForm
{
	public: CLPirDelayUpdateConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;

	private: short m_Minutes;
	public: void SetMinutes( short value );

	//private: bool IsDataChanged();

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderMinutes();
};
// -----------------------------------------------------------------------------
// CLPirDelayUpdateConfigForm [class]
// =============================================================================

#endif

