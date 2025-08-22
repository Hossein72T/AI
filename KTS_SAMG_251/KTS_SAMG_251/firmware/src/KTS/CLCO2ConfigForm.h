 /*************************************************************************************
 *  file:			CLCO2ConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLCO2ConfigForm_h
#define __CLCO2ConfigForm_h

#include "CLForm.h"

CLFormResult CLCO2ConfigForm_Open( unsigned short options );

// =============================================================================
// CLCO2ConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle soglie CO2
// -----------------------------------------------------------------------------
class _PACK CLCO2ConfigForm
	: public CLForm
{
	public: CLCO2ConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_UpButtonRectangle;
	private: CLRectangle m_DownButtonRectangle;
        
        private: CLRectangle m_UpButtonRectangle_CO2;
	private: CLRectangle m_DownButtonRectangle_CO2;

	private: unsigned short m_Value;
    private: byte m_Value1;
	public: void SetValue( unsigned short value);
    public: void SetValue1( byte value);

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderDynamicObjects();
};
// -----------------------------------------------------------------------------
// CLCO2ConfigForm [class]
// =============================================================================

#endif

