 /*************************************************************************************
 *  file:			CLReferenceTSettingForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLReferenceTSettingForm_h
#define __CLReferenceTSettingForm_h

#include "CLForm.h"

CLFormResult CLReferenceTSettingForm_Open( unsigned short options );

// =============================================================================
// CLReferenceTSettingForm [class]
// =============================================================================
// Description: Form per la configurazione dell'accesorio DXD
// -----------------------------------------------------------------------------
class _PACK CLReferenceTSettingForm
	: public CLForm
{
	public: CLReferenceTSettingForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_ReferenceProbe_ReturnButtonRectangle;
	private: CLRectangle m_ReferenceProbe_SupplyButtonRectangle;

	private: CLRectangle m_DeltaTemperature_UpButtonRectangle;
	private: CLRectangle m_DeltaTemperature_DownButtonRectangle;

	private: CLRectangle m_Delay_UpButtonRectangle;
	private: CLRectangle m_Delay_DownButtonRectangle;

	private: byte m_RefTSetting;
	private: float m_DeltaTemperature;

	public: void SelectProbeReturn();
	public: bool IsProbeReturnSelected();

	public: void SelectProbeSupply();
	public: bool IsProbeSupplySelected();

	public: void SetDeltaTemperature( float value );
	
	public: void SetDelay( short value );
	public: short GetDelay();

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderReferenceProbeButtons();
	private: void RenderDeltaTemperature( bool redrawAllPanel );
	private: void RenderDelay();
};
// -----------------------------------------------------------------------------
// CLReferenceTSettingForm [class]
// =============================================================================

#endif

