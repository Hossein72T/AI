 /*************************************************************************************
 *  file:			CLKTSConnectForm.h
 *
 *  Author/Date:	Paolo Menchi maggio 2015
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLKTSConnectForm_h
#define __CLKTSConnectForm_h

#include "CLForm.h"

CLFormResult CLKTSConnectForm_Open();

// =============================================================================
// CLKTSConnectForm [class]
// =============================================================================
// Description: Form del KTS per la connessione
// -----------------------------------------------------------------------------
class _PACK CLKTSConnectForm
	: public CLForm
{
	public: CLKTSConnectForm();

	// Buttons
	private: CLRectangle m_RFMSettingsButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: enum CLMode
	{
		CLMode_TryConnect,
		CLMode_Error
	};
	private: CLMode m_Mode;

	public: CLFormResult Open();

	private: void RenderPage();
};
// -----------------------------------------------------------------------------
// CLKTSConnectForm [class]
// =============================================================================

#endif

