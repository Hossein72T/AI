 /*************************************************************************************
 *  file:			CLReportDebugDataForm.h
 *
 *  Author/Date:	Paolo Menchi
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLReportDebugDataForm_h
#define __CLReportDebugDataForm_h

#include "CLForm.h"

CLFormResult CLReportDebugDataForm_Open( unsigned short options );

// =============================================================================
// CLReportDebugDataForm [class]
// =============================================================================
// Description: Form per la visualizzazione dei dati di debug
// -----------------------------------------------------------------------------
class _PACK CLReportDebugDataForm
	: public CLForm
{
	public: CLReportDebugDataForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: bool m_FirstRequestDebugData;
	private: bool m_AdminMode;

	// Page
	private: CLPage m_Page;

	public: byte ReceivedData;

	// [Page 1] Accessory Clima
	public: byte PreHeater_LinkLevel;
	public: byte Heater_LevelLink;
	public: byte Cooler_LevelLink;
	public: byte PreHeater_Status;
	public: byte Heater_Status;
	public: byte Cooler_Status;
	public: float Heater_WaterTemperature;
	public: float Heater_AirTemperature;
	public: float Cooler_WaterTemperature;

	// [Page 3] CAP/CAF Data
	public: byte Status_FanR;
	public: byte Status_FanF;
	public: byte Level_Link_Sensor;

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderData();
};
// -----------------------------------------------------------------------------
// CLReportDebugDataForm [class]
// =============================================================================

#endif

