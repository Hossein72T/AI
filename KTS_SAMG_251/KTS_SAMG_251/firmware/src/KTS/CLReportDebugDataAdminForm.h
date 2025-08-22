 /*************************************************************************************
 *  file:			CLReportDebugDataAdminForm.h
 *
 *  Author/Date:	Paolo Menchi
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLReportDebugDataAdminForm_h
#define __CLReportDebugDataAdminForm_h

#include "CLForm.h"

CLFormResult CLReportDebugDataAdminForm_Open( unsigned short options );

// =============================================================================
// CLReportDebugDataAdminForm [class]
// =============================================================================
// Description: Form per la visualizzazione dei dati di debug per Admin
// -----------------------------------------------------------------------------
class _PACK CLReportDebugDataAdminForm
	: public CLForm
{
	public: CLReportDebugDataAdminForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_TestIPEHD;
	private: bool m_FirstRequestDebugData;
	private: bool m_AdminMode;

	// Page
	private: CLPage m_Page;

	public: byte ReceivedData;

	// [Page 0] STATUS MOTORS
	public: int Measures_Pressure;
    public: int Measures_Pressure_CAPS;
    public: int Measures_Pressure_CAPR;
	public: word Rpm_FanR[3];
	public: word Rpm_FanF[3];
	public: float FeedBk_VoutF;
	public: float FeedBk_VoutR;

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
	public: float Cooler_AirTemperature;
	private: byte m_RefTSetting; //Test IPEHD (bit 6)

	// [Page 3] CAP/CAF Data
	public: byte Status_FanR;
	public: byte Status_FanF;
	public: byte Level_Link_Sensor;
	public: word MeasureAirflow;
    
    public: word MeasureAirflow_CAPS;
    public: word MeasureAirflow_CAPR;
    
    public: byte CAPS_LinkLevel;
	public: byte CAPR_LinkLevel;
    public: byte CAPS_Status;
	public: byte CAPR_Status;
    
    public: word Measure_CO2_1;
    public: word Measure_VOC_1;
    public: byte Measure_RH_1;
    public: word Measure_CO2_2;
    public: byte Measure_RH_2;
    public: byte Firm_Ver_CO2_1;
    public: byte Firm_Ver_CO2_2;
    public: byte CO2_1_LinkLevel;
    public: byte CO2_2_LinkLevel;
    public: word Measure_IAQ_1;
    public: word Measure_IAQ_2;
    public: byte CO2_1_Status;
	public: byte CO2_2_Status;
    public: byte CO2_1_Accuracy;
    public: byte CO2_2_Accuracy;
    public: byte IAQ_1_Accuracy;
    public: byte IAQ_2_Accuracy;
    
	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderData();
};
// -----------------------------------------------------------------------------
// CLReportDebugDataAdminForm [class]
// =============================================================================

#endif

