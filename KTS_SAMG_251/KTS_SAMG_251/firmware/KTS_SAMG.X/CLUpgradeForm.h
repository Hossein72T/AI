 /*************************************************************************************
 *  file:			CLUpgradeForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLUpgradeForm_h
#define __CLUpgradeForm_h

#include "CLForm.h"
#include "CLKTS.h"

CLFormResult CLUpgradeForm_Open( unsigned short options );

// =============================================================================
// CLUpgradeForm [class]
// =============================================================================
// Description: Form per l'aggiornamento del KTS in PLUS
// -----------------------------------------------------------------------------
class _PACK CLUpgradeForm
	: public CLForm
{
	public: CLUpgradeForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;
	private: CLRectangle m_DINExtraButtonRectangle;

	private: CLKTSType m_KTSType;
	private: unsigned long m_KeygenPassword;
	private: char m_Password[ 5 ];

	private: long GeneratePassword( char* password );

	public: void SetKTSType( CLKTSType value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderButtons();
};
// -----------------------------------------------------------------------------
// CLUpgradeForm [class]
// =============================================================================

#endif

