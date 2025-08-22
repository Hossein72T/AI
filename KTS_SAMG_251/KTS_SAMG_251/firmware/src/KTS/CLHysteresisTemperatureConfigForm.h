 /*************************************************************************************
 *  file:			CLHysteresisTemperatureConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLHysteresisTemperatureConfigForm_h
#define __CLHysteresisTemperatureConfigForm_h

#include "CLForm.h"

CLFormResult CLHysteresisTemperatureConfigForm_Open( unsigned short options );

// =============================================================================
// CLHysteresisTemperatureConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle isteresi delle temperature
// -----------------------------------------------------------------------------
class _PACK CLHysteresisTemperatureConfigForm
	: public CLForm
{
	public: CLHysteresisTemperatureConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_HotButtonRectangle;
	private: CLRectangle m_ColdButtonRectangle;

	private: CLRectangle m_High_UpButtonRectangle;
	private: CLRectangle m_High_DownButtonRectangle;
	private: CLRectangle m_Low_UpButtonRectangle;
	private: CLRectangle m_Low_DownButtonRectangle;

	private: CLRectangle m_LinesRectangle;

	enum CLTemperatureType
	{
		CLTemperatureType_Hot	= 0,
		CLTemperatureType_Cold	= 1
	};

	private: bool m_AWPIsPresent;
	private: float m_CurrentTemperature;
	private: CLTemperatureType m_TemperatureType;
	public: void SelectTemperatureType( CLTemperatureType temperatureType );
	private: void RenderTemperatureType();

	private: float m_MinValue;
	private: float m_MaxValue;
	private: float m_HighValues[ 2 ];
	private: float m_LowValues[ 2 ];

	public: void SetTemperature( CLTemperatureType temperatureType,
		float lowValue, float highValue );
	public: void SetHighTemperature( CLTemperatureType temperatureType,
		float value );

	private: bool Save( unsigned short options );

	public: CLFormResult Open( unsigned short options );

	private: void RenderPage();
	private: void RenderProgressBar();
};
// -----------------------------------------------------------------------------
// CLHysteresisTemperatureConfigForm [class]
// =============================================================================

#endif

