 /*************************************************************************************
 *  file:			CLEepromResetForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	Form per resettare i valori della eeprom
 *
 *************************************************************************************/

#ifndef __CLEepromResetForm_h
#define __CLEepromResetForm_h

#include "CLForm.h"

CLFormResult CLEepromResetForm_Open( unsigned short options );

// =============================================================================
// CLEepromResetForm [class]
// =============================================================================
// Description: Form per reset eeprom
// -----------------------------------------------------------------------------
class _PACK CLEepromResetForm
	: public CLForm
{
	public: CLEepromResetForm();

	// Buttons
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLEepromResetForm [class]
// =============================================================================

#endif

