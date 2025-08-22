 /*************************************************************************************
 *  file:			CLFilterConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/
#ifndef __CLFilterConfigForm_h
#define __CLFilterConfigForm_h

#include "CLForm.h"

CLFormResult CLFilterConfigForm_Open( unsigned short options );

// =============================================================================
// CLFilterConfigForm [class]
// =============================================================================
// Description: Form per la configurazione dei filtri
// -----------------------------------------------------------------------------
class _PACK CLFilterConfigForm
	: public CLForm
{
	public: CLFilterConfigForm();

	private: unsigned short m_Options;

	enum CheckFilterType
	{
		CheckFilterType_Off,
		CheckFilterType_DPS,
		CheckFilterType_DPP
	};

	private: void Load();

	// CheckFilterType
	private: CheckFilterType m_CheckFilterType;
	public: void SetCheckFilterType( CheckFilterType value );

	// DPS
	private: byte m_DPS_Days;
	private: void SetDPS_Days( short value );

	// DPP
	private: byte m_DPP_Threshold;
	private: void SetDPP_Threshold( short value );

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	public: void DoVerify();

	private: void RenderPage();
	private: void RenderPageDynamicObjects();

	private: void RenderCheckFilterTypeButtons();
	private: void RenderCheckFilterType();

};
// -----------------------------------------------------------------------------
// CLFilterConfigForm [class]
// =============================================================================

#endif

