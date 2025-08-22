 /*************************************************************************************
 *  file:			CLDscDelayUpdateConfigForm.h
 *
 *  Author/Date:	Zakaria taleb bendiab November 2021
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLDscDelayUpdateConfigForm_h
#define __CLDscDelayUpdateConfigForm_h

#include "CLForm.h"

#define DSC_UPDATE_DELAY_MIN	3
#define DSC_UPDATE_DELAY_MAX	60

CLFormResult CLDscDelayUpdateConfigForm_Open( unsigned short options );

// =============================================================================
// CLDscDelayUpdateConfigForm [class]
// =============================================================================
// Description: Form per la configurazione dello DSC sdcard Update Delay
// -----------------------------------------------------------------------------
class _PACK CLDscDelayUpdateConfigForm
	: public CLForm
{
	public: CLDscDelayUpdateConfigForm();

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
// CLDscDelayUpdateConfigForm [class]
// =============================================================================

#endif

