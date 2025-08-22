 /*************************************************************************************
 *  file:			CLSelectionLanguageForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionLanguageForm_h
#define __CLSelectionLanguageForm_h

#include "CLForm.h"
#include "CLLocalitation.h"

CLFormResult CLSelectionLanguageForm_Open( unsigned short options );

// =============================================================================
// CLSelectionLanguageForm [class]
// =============================================================================
// Description: Form per la selezione della lingua
// -----------------------------------------------------------------------------
class _PACK CLSelectionLanguageForm
	: public CLForm
{
	public: CLSelectionLanguageForm();

	// Styles
	private: CLGraphicStyle m_FlagButtonStyle_Normal;
	private: CLGraphicStyle m_FlagButtonStyle_Selected;

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;

	private: CLRectangle m_FlagsButtons[ 6 ];
	private: byte m_FlagsLanguagesIds[ CLLanguageId__COUNT ];
	private: byte m_FlagCount;
	private: byte m_CurrentFlagsIndex;
	private: CLPage m_Page;

	public: void SelectFlag( byte flagIndex );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage( unsigned short options );
	private: void RenderFlagButton( byte index, bool selected );
	private: void RenderMainTitle();
	private: void RenderOkButton();
};
// -----------------------------------------------------------------------------
// CLSelectionLanguageForm [class]
// =============================================================================

#endif

