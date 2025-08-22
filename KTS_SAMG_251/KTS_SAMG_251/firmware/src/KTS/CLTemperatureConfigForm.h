 /*************************************************************************************
 *  file:			CLTemperatureConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLTemperatureConfigForm_h
#define __CLTemperatureConfigForm_h

#include "CLForm.h"

#define CLTemperatureConfigFormOption_MaskMode		0x03
//#define CLTemperatureConfigFormOption_MaskConfig	0x04

enum CLTemperatureConfigFormOption
{
	CLTemperatureConfigFormOption_Mode_Auto					= 0x00,
	CLTemperatureConfigFormOption_Mode_SingleTemperature	= 0x01,
	CLTemperatureConfigFormOption_Mode_DoubleTemperature	= 0x02
};

CLFormResult CLTemperatureConfigForm_Open( unsigned short options,
	byte formOptions );

// =============================================================================
// CLTemperatureConfigForm [class]
// =============================================================================
// Description: Form per la configurazione delle temperature
// -----------------------------------------------------------------------------
class _PACK CLTemperatureConfigForm
	: public CLForm
{
	public: CLTemperatureConfigForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_ClimaSummerOnOffButtonRectangle;
	private: CLRectangle m_ClimaPreHeaterOnOffButtonRectangle;
	private: CLRectangle m_ClimaWinterOnOffButtonRectangle;

	private: CLRectangle m_TemperatureUpButtonRectangles[ 2 ];
	private: CLRectangle m_TemperatureDownButtonRectangles[ 2 ];

	private: enum CLMode
	{
		CLMode_SingleTemperature	= 0,
		CLMode_DoubleTemperature	= 1
	};
	private: CLMode m_Mode;

	private: byte m_FormOptions;

	private: bool m_ClimaPreHeaterEnabled;
	public: void SetClimaPreHeaterEnabled( bool value );

	private: bool m_ClimaWinterEnabled;
	public: void SetClimaWinterEnabled( bool value );

	private: bool m_ClimaSummerEnabled;
	public: void SetClimaSummerEnabled( bool value );

	private: short m_Temperatures[ 2 ];
	public: void SetTemperature( byte index, short value );

	public: CLFormResult Open( unsigned short options,
		byte formOptions );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderButtons();

	private: void RenderTemperatureButtons( byte index );
	private: void RenderTemperatureProgressBar( byte index );
};
// -----------------------------------------------------------------------------
// CLTemperatureConfigForm [class]
// =============================================================================

#endif

