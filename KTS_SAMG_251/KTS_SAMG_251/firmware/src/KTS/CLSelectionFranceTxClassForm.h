 /*************************************************************************************
 *  file:			CLSelectionFranceTxClassForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionFranceTxClassForm_h
#define __CLSelectionFranceTxClassForm_h

#include "CLForm.h"

#ifdef FRANCETX_ENABLED

CLFormResult CLSelectionFranceTxClassForm_Open( const char* mainTitle,
	const char* subTitle,
	byte& value );

// =============================================================================
// CLSelectionFranceTxClassForm [class]
// =============================================================================
// Description: Form per la selezione della classe dell'appartamento in Francia
// -----------------------------------------------------------------------------
const int CLFranceApartmentClassCount = 5;

class _PACK CLSelectionFranceTxClassForm
	: public CLForm
{
	public: CLSelectionFranceTxClassForm( const char* mainTitle,
		const char* subTitle );

	// Buttons
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_TxButtonRectangles[ CLFranceApartmentClassCount ];

	private: const char* m_MainTitle;
	private: const char* m_SubTitle;

	private: byte m_Value;
	public: void SetValue( byte value );
	public: byte GetValue();

	public: CLFormResult Open( byte& value );

	private: void RenderPage();
	private: void RenderClassButtons();
};
// -----------------------------------------------------------------------------
// CLSelectionFranceTxClassForm [class]
// =============================================================================

#endif

#endif

