 /*************************************************************************************
 *  file:			CLTestUnitForm.h
 *
 *  Author/Date:
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLTestUnitForm_h
#define __CLTestUnitForm_h

#include "CLForm.h"

CLFormResult CLTestUnitForm_Open( unsigned short options );

// =============================================================================
// CLTestForm [class]
// =============================================================================
// Description: Form per la gestione della/e password
// -----------------------------------------------------------------------------
class _PACK CLTestUnitForm
	: public CLForm
{
	public: CLTestUnitForm();

	// Buttons
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_StartTestButtonRectangle;

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderData();

	private: bool SendTestMessage( unsigned short options );
};
// -----------------------------------------------------------------------------
// CLTestForm [class]
// =============================================================================

#endif

