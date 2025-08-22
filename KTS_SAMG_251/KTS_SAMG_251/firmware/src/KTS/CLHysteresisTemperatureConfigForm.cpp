#include "CLHysteresisTemperatureConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLAccessory.h"
#include "CLImages.h"
#include "CLTemperature.h"

#define	CLHysteresisTemperatureConfigForm_HotButtonRectangle		9, 25, 81, 54
#define	CLHysteresisTemperatureConfigForm_ColdButtonRectangle		9, 65, 81, 94
#define	CLHysteresisTemperatureConfigForm_GroupFrameRectangle		87, 24, 311, 174
#define	CLHysteresisTemperatureConfigForm_ProgressBarRectangle		139, 29, 167, 170
#define	CLHysteresisTemperatureConfigForm_LinesRectangle			169, 29, 201, 170
#define	CLHysteresisTemperatureConfigForm_MinValuePoint				93, 150
#define	CLHysteresisTemperatureConfigForm_MiddleValuePoint			93, 94
#define	CLHysteresisTemperatureConfigForm_MaxValuePoint				93, 37
#define	CLHysteresisTemperatureConfigForm_High_GroupFrameRectangle	203, 29, 262, 93
#define	CLHysteresisTemperatureConfigForm_High_TitleRectangle		207, 42, 258, 57
#define	CLHysteresisTemperatureConfigForm_High_ValueRectangle		207, 64, 258, 79
#define	CLHysteresisTemperatureConfigForm_High_UpButtonRectangle	268, 29, 307, 58
#define	CLHysteresisTemperatureConfigForm_High_DownButtonRectangle	268, 64, 307, 93
#define	CLHysteresisTemperatureConfigForm_Low_GroupFrameRectangle	203, 106, 262, 170
#define	CLHysteresisTemperatureConfigForm_Low_TitleRectangle		207, 120, 258, 135
#define	CLHysteresisTemperatureConfigForm_Low_ValueRectangle		207, 142, 258, 157
#define	CLHysteresisTemperatureConfigForm_Low_UpButtonRectangle		268, 106, 307, 135
#define	CLHysteresisTemperatureConfigForm_Low_DownButtonRectangle	268, 141, 307, 170

#define	CLHysteresisTemperatureConfigForm_High_LineY				64
#define	CLHysteresisTemperatureConfigForm_Low_LineY					142

CLFormResult CLHysteresisTemperatureConfigForm_Open( unsigned short options )
{
	CLHysteresisTemperatureConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLHysteresisTemperatureConfigForm [class]
// -----------------------------------------------------------------------------
CLHysteresisTemperatureConfigForm::CLHysteresisTemperatureConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_HotButtonRectangle.Set( CLHysteresisTemperatureConfigForm_HotButtonRectangle );
	m_ColdButtonRectangle.Set( CLHysteresisTemperatureConfigForm_ColdButtonRectangle );

	m_High_UpButtonRectangle.Set( CLHysteresisTemperatureConfigForm_High_UpButtonRectangle );
	m_High_DownButtonRectangle.Set( CLHysteresisTemperatureConfigForm_High_DownButtonRectangle );
	m_Low_UpButtonRectangle.Set( CLHysteresisTemperatureConfigForm_Low_UpButtonRectangle );
	m_Low_DownButtonRectangle.Set( CLHysteresisTemperatureConfigForm_Low_DownButtonRectangle );

	m_LinesRectangle.Set( CLHysteresisTemperatureConfigForm_LinesRectangle );
}

CLFormResult CLHysteresisTemperatureConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_AWPIsPresent			= Accessory_IsPresent( ACC_EEP_AWP ) || Accessory_IsPresent( ACC_EEP_P1CO2 ) || Accessory_IsPresent( ACC_EEP_P1CO2 );
	m_CurrentTemperature	= Temperature_Get();
	m_LowValues[ 0 ]		= 0;
	m_HighValues[ 0 ]		= 1;
	m_LowValues[ 1 ]		= 0;
	m_HighValues[ 1 ]		= 1;
	m_MinValue				= m_CurrentTemperature - 12.0f;
	m_MaxValue				= m_CurrentTemperature + 12.0f;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SelectTemperatureType( (Accessory_IsPresent( ACC_EEP_HWD ) || Accessory_IsPresent( ACC_EEP_EHD ) || Accessory_IsPresent( ACC_EEP_SSR )) ? CLTemperatureType_Hot : CLTemperatureType_Cold );
	
	if (m_AWPIsPresent)
	{
		SetTemperature( CLTemperatureType_Hot, m_CurrentTemperature + Hysteresis_GetAWPHot( CLHysteresisLimitType_On ),
			m_CurrentTemperature + Hysteresis_GetAWPHot( CLHysteresisLimitType_Off ) );
		SetTemperature( CLTemperatureType_Cold, m_CurrentTemperature + Hysteresis_GetAWPCold( CLHysteresisLimitType_Off ),
			m_CurrentTemperature + Hysteresis_GetAWPCold( CLHysteresisLimitType_On ) );
	}
	else
	{
		SetTemperature( CLTemperatureType_Hot, m_CurrentTemperature + Hysteresis_GetHot( CLHysteresisLimitType_On ),
			m_CurrentTemperature + Hysteresis_GetHot( CLHysteresisLimitType_Off ) );
		SetTemperature( CLTemperatureType_Cold, m_CurrentTemperature + Hysteresis_GetCold( CLHysteresisLimitType_Off ),
			m_CurrentTemperature + Hysteresis_GetCold( CLHysteresisLimitType_On ) );
	}
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			else
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
			}
			else
			// Hot Button
			if ((Accessory_IsPresent( ACC_EEP_HWD ) || Accessory_IsPresent( ACC_EEP_EHD ) || Accessory_IsPresent( ACC_EEP_SSR )) &&
				m_HotButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HotButtonRectangle );

				SelectTemperatureType( CLTemperatureType_Hot );
			}
			else
			// Cold Button
			if (Accessory_IsPresent( ACC_EEP_CWD ) && m_ColdButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ColdButtonRectangle );

				SelectTemperatureType( CLTemperatureType_Cold );
			}
			else
			// High Up Button
			if (m_High_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_High_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetTemperature( m_TemperatureType, m_LowValues[ m_TemperatureType ],
						m_HighValues[ m_TemperatureType ] + 0.5f );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_High_UpButtonRectangle );
			}
			else
			// High Down Button
			if (m_High_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_High_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetTemperature( m_TemperatureType, m_LowValues[ m_TemperatureType ],
						m_HighValues[ m_TemperatureType ] - 0.5f );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_High_DownButtonRectangle );
			}
			else
			// Low Up Button
			if (m_Low_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_Low_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetTemperature( m_TemperatureType, m_LowValues[ m_TemperatureType ] + 0.5f,
						m_HighValues[ m_TemperatureType ] );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_Low_UpButtonRectangle );
			}
			else
			// Low Down Button
			if (m_Low_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_Low_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetTemperature( m_TemperatureType, m_LowValues[ m_TemperatureType ] - 0.5f,
						m_HighValues[ m_TemperatureType ] );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_Low_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
	}

	return formResult;
}

bool CLHysteresisTemperatureConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	signed char		saveHister_Temp_Hot[ 2 ];
	signed char		saveHister_Temp_Cold[ 2 ];

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	if (m_AWPIsPresent)
	{
		// Salva temporaneamente i dati correnti
		saveHister_Temp_Cold[ 0 ]	= gRDEeprom.hister_AWP_Temp_Cold[ 0 ];
		saveHister_Temp_Cold[ 1 ]	= gRDEeprom.hister_AWP_Temp_Cold[ 1 ];
		saveHister_Temp_Hot[ 0 ]	= gRDEeprom.hister_AWP_Temp_Hot[ 0 ];
		saveHister_Temp_Hot[ 1 ]	= gRDEeprom.hister_AWP_Temp_Hot[ 1 ];

		// Imposta i nuovi dati
		Hysteresis_SetAWPCold( CLHysteresisLimitType_Off,(m_LowValues[ CLTemperatureType_Cold ] - m_CurrentTemperature) );
		Hysteresis_SetAWPCold( CLHysteresisLimitType_On, (m_HighValues[ CLTemperatureType_Cold ] - m_CurrentTemperature) );
		Hysteresis_SetAWPHot( CLHysteresisLimitType_Off, (m_HighValues[ CLTemperatureType_Hot ] - m_CurrentTemperature) );
		Hysteresis_SetAWPHot( CLHysteresisLimitType_On,  (m_LowValues[ CLTemperatureType_Hot ] - m_CurrentTemperature) );

		// Accoda la richiesta di WriteEeprom
		KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, hister_AWP_Temp_Hot),
			sizeof(gRDEeprom.hister_AWP_Temp_Hot) + sizeof(gRDEeprom.hister_AWP_Temp_Cold),
			&writeEeprom_Status );
	}
	else
	{
		saveHister_Temp_Cold[ 0 ]	= gRDEeprom.hister_Temp_Cold[ 0 ];
		saveHister_Temp_Cold[ 1 ]	= gRDEeprom.hister_Temp_Cold[ 1 ];
		saveHister_Temp_Hot[ 0 ]	= gRDEeprom.hister_Temp_Hot[ 0 ];
		saveHister_Temp_Hot[ 1 ]	= gRDEeprom.hister_Temp_Hot[ 1 ];

		// Imposta i nuovi dati
		Hysteresis_SetCold( CLHysteresisLimitType_Off, (m_LowValues[ CLTemperatureType_Cold ] - m_CurrentTemperature) );
		Hysteresis_SetCold( CLHysteresisLimitType_On, (m_HighValues[ CLTemperatureType_Cold ] - m_CurrentTemperature) );
		Hysteresis_SetHot( CLHysteresisLimitType_Off, (m_HighValues[ CLTemperatureType_Hot ] - m_CurrentTemperature) );
		Hysteresis_SetHot( CLHysteresisLimitType_On, (m_LowValues[ CLTemperatureType_Hot ] - m_CurrentTemperature) );

		KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, hister_Temp_Hot),
			sizeof(gRDEeprom.hister_Temp_Hot) + sizeof(gRDEeprom.hister_Temp_Cold),
			&writeEeprom_Status );
	}

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		if (m_AWPIsPresent)
		{
			gRDEeprom.hister_AWP_Temp_Cold[ 0 ]	= saveHister_Temp_Cold[ 0 ];
			gRDEeprom.hister_AWP_Temp_Cold[ 1 ]	= saveHister_Temp_Cold[ 1 ];
			gRDEeprom.hister_AWP_Temp_Hot[ 0 ]	= saveHister_Temp_Hot[ 0 ];
			gRDEeprom.hister_AWP_Temp_Hot[ 1 ]	= saveHister_Temp_Hot[ 1 ];
		}
		else
		{
			gRDEeprom.hister_Temp_Cold[ 0 ]	= saveHister_Temp_Cold[ 0 ];
			gRDEeprom.hister_Temp_Cold[ 1 ]	= saveHister_Temp_Cold[ 1 ];
			gRDEeprom.hister_Temp_Hot[ 0 ]	= saveHister_Temp_Hot[ 0 ];
			gRDEeprom.hister_Temp_Hot[ 1 ]	= saveHister_Temp_Hot[ 1 ];
		}

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLHysteresisTemperatureConfigForm::RenderPage()
{
	char	text[ 40 ];

	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_HYSTER_TEMPSET ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	// Group
	CLGraphics::DrawBox( CLRectangle( CLHysteresisTemperatureConfigForm_GroupFrameRectangle ), 
		GenericForm_Group_Style );

	// Print Min Temperature
	sprintf( text, "%2.1f%c", m_MinValue, FONT_SYMBOL_DEGREES );
	CLGraphics::DrawText( CLHysteresisTemperatureConfigForm_MinValuePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text, 5 );

	// Print Middle Temperature
	sprintf( text, "%2.1f%c", m_CurrentTemperature, FONT_SYMBOL_DEGREES );
	CLGraphics::DrawText( CLHysteresisTemperatureConfigForm_MiddleValuePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text, 5 );

	// Print Max Temperature
	sprintf( text, "%2.1f%c", m_MaxValue, FONT_SYMBOL_DEGREES );
	CLGraphics::DrawText( CLHysteresisTemperatureConfigForm_MaxValuePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text, 5 );

	// High
	CLGraphics::DrawBox( CLRectangle( CLHysteresisTemperatureConfigForm_High_GroupFrameRectangle ), 
		GenericForm_Group_Style );

	CLLCDCommon::DrawGenericButton( m_High_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	
	CLLCDCommon::DrawGenericButton( m_High_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	// Low
	CLGraphics::DrawBox( CLRectangle( CLHysteresisTemperatureConfigForm_Low_GroupFrameRectangle ), 
		GenericForm_Group_Style );

	CLLCDCommon::DrawGenericButton( m_Low_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	
	CLLCDCommon::DrawGenericButton( m_Low_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	RenderTemperatureType();
	RenderProgressBar();
}

void CLHysteresisTemperatureConfigForm::RenderProgressBar()
{
	char	text[ 10 ];
	short	outPositions[ 2 ];

	if (m_TemperatureType == CLTemperatureType_Hot)
	{
		float		values[ 2 ];
		RGBColor	barTrueColors[ 2 ];

		values[ 0 ]			= m_LowValues[ m_TemperatureType ];
		values[ 1 ]			= m_HighValues[ m_TemperatureType ];
		barTrueColors[ 0 ]	= TemperatureHot_ProgressBar_Color_BarTrue;
		barTrueColors[ 1 ]	= TemperatureHot_ProgressBar_Color_BarTrue;

		CLGraphics::DrawProgressBar( CLRectangle( CLHysteresisTemperatureConfigForm_ProgressBarRectangle ),
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_StartWith_Max | CLDrawBarOptions_Data_Range,
			TemperatureHot_ProgressBar_Color_Background, TemperatureHot_ProgressBar_Color_BarFalse, barTrueColors,
			m_MinValue - 2.0f, m_MaxValue + 2.0f, values, 2,
			2, 1,
			outPositions );
	}
	else
	{
		float		values[ 2 ];
		RGBColor	barTrueColors[ 2 ];

		values[ 0 ]			= m_LowValues[ m_TemperatureType ];
		values[ 1 ]			= m_HighValues[ m_TemperatureType ];
		barTrueColors[ 0 ]	= TemperatureCold_ProgressBar_Color_BarTrue;
		barTrueColors[ 1 ]	= TemperatureCold_ProgressBar_Color_BarTrue;

		CLGraphics::DrawProgressBar( CLRectangle( CLHysteresisTemperatureConfigForm_ProgressBarRectangle ),
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_StartWith_Max | CLDrawBarOptions_Data_Range,
			TemperatureCold_ProgressBar_Color_Background, TemperatureCold_ProgressBar_Color_BarFalse, barTrueColors,
			m_MinValue - 2.0f, m_MaxValue + 2.0f, values, 2,
			2, 1,
			outPositions );
	}

	CLGraphics::DrawBox( CLRectangle( CLHysteresisTemperatureConfigForm_LinesRectangle ), CLGraphicStyleOptions_Default,
		RGBColor_Black );

	if (outPositions[ 1 ] >= 0)
	{
		CLGraphics::DrawLine( m_LinesRectangle.GetX1(), m_LinesRectangle.GetY2() - outPositions[ 1 ], m_LinesRectangle.GetX2(), CLHysteresisTemperatureConfigForm_High_LineY,
			RGBColor_White );
	}

	if (outPositions[ 0 ] >= 0)
	{
		CLGraphics::DrawLine( m_LinesRectangle.GetX1(), m_LinesRectangle.GetY2() - outPositions[ 0 ], m_LinesRectangle.GetX2(), CLHysteresisTemperatureConfigForm_Low_LineY,
			RGBColor_White );
	}

	sprintf( text, "%2.1f %c", m_HighValues[ m_TemperatureType ], FONT_SYMBOL_DEGREES );
	CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_High_ValueRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );

	sprintf( text, "%2.1f %c", m_LowValues[ m_TemperatureType ], FONT_SYMBOL_DEGREES );
	CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_Low_ValueRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );
}

void CLHysteresisTemperatureConfigForm::SetTemperature( CLTemperatureType temperatureType,
	float lowValue, float highValue )
{
	if (highValue == m_HighValues[ temperatureType ])
	{
		if (lowValue < m_MinValue)
			lowValue	= m_MinValue;
		if (lowValue >= m_HighValues[ temperatureType ])
			lowValue	= m_HighValues[ temperatureType ] - 0.5f;
	}
	else
	if (lowValue == m_LowValues[ temperatureType ])
	{
		if (highValue > m_MaxValue)
			highValue	= m_MaxValue;
		if (highValue <= m_LowValues[ temperatureType ])
			highValue	= m_LowValues[ temperatureType ] + 0.5f;
	}
	else
	{
		if (lowValue < m_MinValue)
			lowValue	= m_MinValue;
		if (highValue > m_MaxValue)
			highValue	= m_MaxValue;

		if (lowValue >= highValue)
			lowValue	= highValue - 0.5f;
		if (highValue <= lowValue)
			highValue	= lowValue;
	}

	m_LowValues[ temperatureType ]	= lowValue;
	m_HighValues[ temperatureType ]	= highValue;

	if (GetState() == CLState_Running && temperatureType == m_TemperatureType)
		RenderProgressBar();
}

void CLHysteresisTemperatureConfigForm::SelectTemperatureType( CLTemperatureType value )
{
	if (value > CLTemperatureType_Cold)
		value	= CLTemperatureType_Cold;

	m_TemperatureType	= value;

	if (GetState() == CLState_Running)
		RenderTemperatureType();
}

void CLHysteresisTemperatureConfigForm::RenderTemperatureType()
{
	if (Accessory_IsPresent( ACC_EEP_HWD ) || Accessory_IsPresent( ACC_EEP_EHD ) || Accessory_IsPresent( ACC_EEP_SSR ))
	{
		CLLCDCommon::DrawGenericButton( m_HotButtonRectangle,
			(m_TemperatureType == CLTemperatureType_Hot ? GenericButtonStyle_Selected_BigFont: GenericButtonStyle_Normal_BigFont),
			CLLocalitation::GetText( CLTextId_HOT ) );
	}
	else
	{
		CLLCDCommon::DrawGenericButton( m_HotButtonRectangle,
			GenericButtonStyle_Disabled_BigFont,
			CLLocalitation::GetText( CLTextId_HOT ) );
	}

	if (Accessory_IsPresent( ACC_EEP_CWD ))
	{
		CLLCDCommon::DrawGenericButton( m_ColdButtonRectangle,
			(m_TemperatureType == CLTemperatureType_Cold ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
			CLLocalitation::GetText( CLTextId_COLD ) );
	}
	else
	{
		CLLCDCommon::DrawGenericButton( m_ColdButtonRectangle,
			GenericButtonStyle_Disabled_BigFont,
			CLLocalitation::GetText( CLTextId_COLD ) );
	}

	switch (m_TemperatureType)
	{
		case CLTemperatureType_Hot:
			CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_High_TitleRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				CLFixedText_OFF );

			CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_Low_TitleRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				CLFixedText_ON );
			break;

		case CLTemperatureType_Cold:
			CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_High_TitleRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				CLFixedText_ON );

			CLGraphics::DrawBoxWithText( CLRectangle( CLHysteresisTemperatureConfigForm_Low_TitleRectangle ), CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				CLFixedText_OFF );
			break;
	}
	RenderProgressBar();
}
// -----------------------------------------------------------------------------
// CLHysteresisTemperatureConfigForm [class]
// =============================================================================

