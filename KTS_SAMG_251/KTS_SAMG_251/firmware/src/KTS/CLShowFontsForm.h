 /*************************************************************************************
 *  file:			CLShowFontsForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2017
 *
 *  Descrizione:	...
 *
 *************************************************************************************/
#include "CLCommon.h"

#if KTS_SHOWFONTSFORM == 1

#ifndef __CLShowFontsForm_h
#define __CLShowFontsForm_h

#include "CLForm.h"

CLFormResult CLShowFontsForm_Open();

// =============================================================================
// CLShowFontsForm [class]
// =============================================================================
// Description: Form per la visualizzazione dei set di caratteri
// -----------------------------------------------------------------------------
class _PACK CLShowFontsForm
	: public CLForm
{
	public: CLShowFontsForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_TextRectangle;

	private: Font* m_SelectedFont;

	public: CLFormResult Open();
	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLShowFontsForm [class]
// =============================================================================

#endif

#endif

