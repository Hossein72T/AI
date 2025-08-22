 /*************************************************************************************
 *  file:			CLBoxInfoConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLBoxInfoConfigForm_h
#define __CLBoxInfoConfigForm_h

#include "CLForm.h"
#include "CLBoxInfo.h"

CLFormResult CLBoxInfoConfigForm_Open( unsigned short options );

// =============================================================================
// CLBoxInfoConfigForm [class]
// =============================================================================
// Description: Form per la configurazione del BoxInfo
// -----------------------------------------------------------------------------
class _PACK CLBoxInfoConfigForm
	: public CLForm
{
	public: CLBoxInfoConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_TReturnButtonRectangle;
	private: CLRectangle m_TFreshButtonRectangle;
	private: CLRectangle m_FiltersButtonRectangle;
	private: CLRectangle m_AccessoriesButtonRectangle;
	private: CLRectangle m_DefrostButtonRectangle;
	private: CLRectangle m_BypassButtonRectangle;
	private: CLRectangle m_ProbesButtonRectangle;

	private: byte m_Value;
	private: void SetEnabled( CLBoxInfo_InfoId infoId, bool value );
	private: void ReverseEnabled( CLBoxInfo_InfoId infoId );
	private: bool IsEnabled( CLBoxInfo_InfoId infoId );

	private: bool Save( unsigned short options );
	private: bool IsDataChanged();
	private: bool Close( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderConfigButtons();
};
// -----------------------------------------------------------------------------
// CLBoxInfoConfigForm [class]
// =============================================================================

#endif

