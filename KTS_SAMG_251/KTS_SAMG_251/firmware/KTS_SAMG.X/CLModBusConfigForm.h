 /*************************************************************************************
 *  file:			CLModBusConfigForm.h
 *
 *  Author/Date:	Paolo Menchi agosto 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLModBusConfigForm_h
#define __CLModBusConfigForm_h

#include "CLForm.h"

CLFormResult CLModBusConfigForm_Open( unsigned short options );

// =============================================================================
// CLModBusConfigForm [class]
// =============================================================================
// Description: Form per la configurazione del ModBus
// -----------------------------------------------------------------------------
class _PACK CLModBusConfigForm
	: public CLForm
{
	public: CLModBusConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_AddressUpButtonRectangle;
	private: CLRectangle m_AddressDownButtonRectangle;

	private: CLProgressiveTouchUpDown m_Address_ProgressiveTouchUpDown;

	private: short m_Address;
	public: void SetAddress( short value );

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderDynamicObjects();
};
// -----------------------------------------------------------------------------
// CLCO2ConfigForm [class]
// =============================================================================

#endif

