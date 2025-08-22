#include "CLTemperatureConfigForm.h"

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

#define	CLTemperatureConfigForm_ClimaPreHeaterOnOffButtonRectangle		7, 28, 113, 67
#define	CLTemperatureConfigForm_ClimaSummerOnOffButtonRectangle			7, 81, 113, 120
#define	CLTemperatureConfigForm_ClimaWinterOnOffButtonRectangle			7, 135, 113, 174

#define	CLTemperatureConfigForm_SunTemperature_FrameRectangle			119, 28, 216, 175
#define	CLTemperatureConfigForm_SunTemperature_UpButtonRectangle		170, 37, 210, 77
#define	CLTemperatureConfigForm_SunTemperature_DownButtonRectangle		171, 122, 211, 162
#define	CLTemperatureConfigForm_SunTemperature_ProgressBarRectangle		125, 37, 163, 137
#define	CLTemperatureConfigForm_SunTemperature_TextProgressPoint		124, 144
#define	CLTemperatureConfigForm_SunTemperature_IconPoint				181, 89

#define	CLTemperatureConfigForm_MoonTemperature_FrameRectangle			221, 28, 316, 175
#define	CLTemperatureConfigForm_MoonTemperature_UpButtonRectangle		271, 37, 311, 77
#define	CLTemperatureConfigForm_MoonTemperature_DownButtonRectangle		271, 122, 311, 162
#define	CLTemperatureConfigForm_MoonTemperature_ProgressBarRectangle	227, 37, 265, 137
#define	CLTemperatureConfigForm_MoonTemperature_TextProgressPoint		226, 144
#define	CLTemperatureConfigForm_MoonTemperature_IconPoint				281, 89

const int Sun_TemperatureIndex	= 0;
const int Sun_MinTemperature	= 15;
const int Sun_MaxTemperature	= 32;
const int Moon_TemperatureIndex	= 1;
const int Moon_MinTemperature	= 15;
const int Moon_MaxTemperature	= 32;

CLFormResult CLTemperatureConfigForm_Open( unsigned short options,
	byte formOptions )
{
	CLTemperatureConfigForm	form;

	return form.Open( options, formOptions );
}

// =============================================================================
// CLTemperatureConfigForm [class]
// -----------------------------------------------------------------------------
CLTemperatureConfigForm::CLTemperatureConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_ClimaPreHeaterOnOffButtonRectangle.Set( CLTemperatureConfigForm_ClimaPreHeaterOnOffButtonRectangle );
	m_ClimaSummerOnOffButtonRectangle.Set( CLTemperatureConfigForm_ClimaSummerOnOffButtonRectangle );
	m_ClimaWinterOnOffButtonRectangle.Set( CLTemperatureConfigForm_ClimaWinterOnOffButtonRectangle );

	m_TemperatureUpButtonRectangles[ 0 ].Set( CLTemperatureConfigForm_SunTemperature_UpButtonRectangle );
	m_TemperatureUpButtonRectangles[ 1 ].Set( CLTemperatureConfigForm_MoonTemperature_UpButtonRectangle );
	m_TemperatureDownButtonRectangles[ 0 ].Set( CLTemperatureConfigForm_SunTemperature_DownButtonRectangle );
	m_TemperatureDownButtonRectangles[ 1 ].Set( CLTemperatureConfigForm_MoonTemperature_DownButtonRectangle );
}

CLFormResult CLTemperatureConfigForm::Open( unsigned short options,
	byte formOptions )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Imposta la modalità di editing
	m_FormOptions	= formOptions;
	switch (m_FormOptions & CLTemperatureConfigFormOption_MaskMode)
	{
		case CLTemperatureConfigFormOption_Mode_SingleTemperature:
			m_Mode	= CLMode_SingleTemperature;
			break;

		case CLTemperatureConfigFormOption_Mode_DoubleTemperature:
			m_Mode	= CLMode_DoubleTemperature;
			break;

		default:
			m_Mode	= (Function_IsEnabled( ENAB_WEEKLY ) ? CLMode_DoubleTemperature : CLMode_SingleTemperature);
			break;
	}

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetClimaPreHeaterEnabled( Function_IsEnabled( ENAB_PREHEATING ) );
	SetClimaSummerEnabled( Function_IsEnabled( ENAB_COOLING ) );
	SetClimaWinterEnabled( Function_IsEnabled( ENAB_HEATING ) );

	
	switch (m_Mode)
	{
		case CLMode_DoubleTemperature:
			SetTemperature( Sun_TemperatureIndex, gRDEeprom.SetPointTemp[ Sun_TemperatureIndex ] / 10 );
			SetTemperature( Moon_TemperatureIndex, gRDEeprom.SetPointTemp[ Moon_TemperatureIndex ] / 10 );
			break;
		
		case CLMode_SingleTemperature:
			SetTemperature( Sun_TemperatureIndex, gRDEeprom.SetPointTemp[ Sun_TemperatureIndex ] / 10 );
			break;
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
			bool	exitForm	= false;

			touchX	= ReadX();
			touchY	= ReadY();

			while (true)
			{
				// Home Button
				if (m_HomeButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_HomeButtonRectangle );
					formResult	= CLFormResult_Home;
					exitForm	= true;
					break;
				}

				// Back Button
				if (m_BackButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_BackButtonRectangle );
					formResult	= CLFormResult_Back;
					exitForm	= true;
					break;
				}

				// Ok Button
				if (m_OkButtonRectangle.Contains( touchX, touchY ))
				{
					if (Save( options ))
					{
						if (CLFormOption_CanExitAfterWrite( options ))
						{
							formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
							exitForm	= true;
							break;
						}
					}
					RenderPage();
					break;
				}

				// Sun Up Button
				if (m_TemperatureUpButtonRectangles[ Sun_TemperatureIndex ].Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_TemperatureUpButtonRectangles[ Sun_TemperatureIndex ] );

					while (Touched() != 0)
					{
						SetTemperature( Sun_TemperatureIndex, m_Temperatures[ Sun_TemperatureIndex ] + 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( 120 );
                        SYSTICK_DelayMs ( 120 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_TemperatureUpButtonRectangles[ Sun_TemperatureIndex ] );
					break;
				}

				// Sun Down Button
				if (m_TemperatureDownButtonRectangles[ Sun_TemperatureIndex ].Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_TemperatureDownButtonRectangles[ Sun_TemperatureIndex ] );

					while (Touched() != 0)
					{
						SetTemperature( Sun_TemperatureIndex, m_Temperatures[ Sun_TemperatureIndex ] - 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( 120 );
                        SYSTICK_DelayMs ( 120 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_TemperatureDownButtonRectangles[ Sun_TemperatureIndex ] );
					break;
				}

				if (m_Mode == CLMode_DoubleTemperature)
				{
					// Moon Up Button
					if (m_TemperatureUpButtonRectangles[ Moon_TemperatureIndex ].Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton_Pressed( m_TemperatureUpButtonRectangles[ Moon_TemperatureIndex ] );

						while (Touched() != 0)
						{
							SetTemperature( Moon_TemperatureIndex, m_Temperatures[ Moon_TemperatureIndex ] + 1 );
							CLKTS::Process();
							CLKTS::Pir_Process();
							//delay( 120 );
                            SYSTICK_DelayMs ( 120 );
						}

						CLLCDCommon::WaitButton_Unpressed( m_TemperatureUpButtonRectangles[ Moon_TemperatureIndex ] );
						break;
					}

					// Moon Down Button
					if (m_TemperatureDownButtonRectangles[ Moon_TemperatureIndex ].Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton_Pressed( m_TemperatureDownButtonRectangles[ Moon_TemperatureIndex ] );

						while (Touched() != 0)
						{
							SetTemperature( Moon_TemperatureIndex, m_Temperatures[ Moon_TemperatureIndex ] - 1 );
							CLKTS::Process();
							CLKTS::Pir_Process();
							//delay( 120 );
                            SYSTICK_DelayMs ( 120 );
						}

						CLLCDCommon::WaitButton_Unpressed( m_TemperatureDownButtonRectangles[ Moon_TemperatureIndex ] );
						break;
					}
				}

				// Pre Heathear OnOff Button
				if ((Accessory_IsPresent( ACC_EEP_PEHD ) || Accessory_IsPresent( ACC_EEP_PHWD )) &&
					m_ClimaPreHeaterOnOffButtonRectangle.Contains( touchX, touchY ))
				{
				
					CLLCDCommon::WaitButton( m_ClimaPreHeaterOnOffButtonRectangle );
					SetClimaPreHeaterEnabled( !m_ClimaPreHeaterEnabled );
					break;
				}

				// Summer OnOff Button
				if ((Accessory_HasCooler() || (gRDEeprom.Set_Output[ 0 ] & 0x07) == 4 || (gRDEeprom.Set_Output[ 1 ] & 0x07) == 4 ) &&
					m_ClimaSummerOnOffButtonRectangle.Contains( touchX, touchY ))
				{
				
					CLLCDCommon::WaitButton( m_ClimaSummerOnOffButtonRectangle );
					SetClimaSummerEnabled( !m_ClimaSummerEnabled );
					break;
				}

				// Winter OnOff Button
				if ((Accessory_HasHeather() || Accessory_IsPresent( ACC_EEP_SSR ) || (gRDEeprom.Set_Output[ 0 ] & 0x07) == 4 || (gRDEeprom.Set_Output[ 1 ] & 0x07) == 4) &&
					m_ClimaWinterOnOffButtonRectangle.Contains( touchX, touchY ))
				{
				
					CLLCDCommon::WaitButton( m_ClimaWinterOnOffButtonRectangle );
					SetClimaWinterEnabled( !m_ClimaWinterEnabled );
					break;
				}

				// Touch non gestito
				WaitForTouchRelease();
				break;
			}

			if (exitForm)
				break;
		}
	}

	return formResult;
}

bool CLTemperatureConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	short			saveSetPointTemp[ 2 ];
	bool			saveClimaPreHeaterFunctionIsEnabled;
	bool			saveClimaSummerFunctionIsEnabled;
	bool			saveClimaWinterFunctionIsEnabled;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	for (int stepsCounter = 0; stepsCounter < 2; stepsCounter++)
	{
		switch (stepsCounter)
		{
			// Salva i set point della temperatura
			case 0:
				// Salva temporaneamente i dati correnti
				memcpy( saveSetPointTemp, gRDEeprom.SetPointTemp, sizeof(saveSetPointTemp) );

				// Imposta i nuovi dati
				gRDEeprom.SetPointTemp[ 0 ]	= m_Temperatures[ 0 ] * 10;
				if (m_Mode == CLMode_DoubleTemperature)
					gRDEeprom.SetPointTemp[ 1 ]	= m_Temperatures[ 1 ] * 10;

				// Accoda la richiesta di WriteEeprom
				KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, SetPointTemp),
					sizeof(gRDEeprom.SetPointTemp),
					&writeEeprom_Status );
				break;

			// Salva l'impostazione summer/winter
			case 1:
				saveClimaPreHeaterFunctionIsEnabled	= Function_IsEnabled( ENAB_PREHEATING );
				saveClimaSummerFunctionIsEnabled	= Function_IsEnabled( ENAB_COOLING );
				saveClimaWinterFunctionIsEnabled	= Function_IsEnabled( ENAB_HEATING );

				Function_SetEnabled( ENAB_PREHEATING, m_ClimaPreHeaterEnabled );
				Function_SetEnabled( ENAB_COOLING, m_ClimaSummerEnabled );
				Function_SetEnabled( ENAB_HEATING, m_ClimaWinterEnabled );

				// Accoda la richiesta di WriteEeprom
				KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, Enab_Fuction),
					sizeof(gRDEeprom.Enab_Fuction),
					&writeEeprom_Status );
				break;
		}

		// Aspetta l'elaborazione della richiesta
		while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
			CLKTS::Process();
		
		CLKTS::Pir_Process();
		
		// Se non e' andata a buon fine, message + home
		if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
		{
			switch (stepsCounter)
			{
				case 0:
					// Rispristina valore precedente
					memcpy( gRDEeprom.SetPointTemp, saveSetPointTemp, sizeof(saveSetPointTemp) );
					break;

				case 1:
					Function_SetEnabled( ENAB_COOLING, saveClimaSummerFunctionIsEnabled );
					Function_SetEnabled( ENAB_PREHEATING, saveClimaPreHeaterFunctionIsEnabled );
					Function_SetEnabled( ENAB_HEATING, saveClimaWinterFunctionIsEnabled );
					break;
			}

			// Visualizza il messaggio di errore
			if (CLFormOption_CanShowWriteMessage_Error( options ))
				CLLCDCommon::WriteDataPanel_DisplayError();

			return false;
		}
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLTemperatureConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_CLIMA_SETTINGS ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	RenderButtons();

	// Sun
	CLGraphics::DrawBox( CLRectangle( CLTemperatureConfigForm_SunTemperature_FrameRectangle ), 
		GenericForm_Group_Style );

	RenderTemperatureButtons( Sun_TemperatureIndex );
	RenderTemperatureProgressBar( Sun_TemperatureIndex );

	if (m_Mode == CLMode_DoubleTemperature)
	{
		// Sun
		CLLCDCommon::DrawSunIcon( CLTemperatureConfigForm_SunTemperature_IconPoint,
			RGBColor_Black, RGBColor_SunIcon_Pen );

		// Moon
		CLGraphics::DrawBox( CLRectangle( CLTemperatureConfigForm_MoonTemperature_FrameRectangle ), 
			GenericForm_Group_Style );

		CLLCDCommon::DrawMoonIcon( CLTemperatureConfigForm_MoonTemperature_IconPoint,
			RGBColor_Black, RGBColor_MoonIcon_Pen );

		RenderTemperatureButtons( Moon_TemperatureIndex );
		RenderTemperatureProgressBar( Moon_TemperatureIndex );
	}
}

void CLTemperatureConfigForm::RenderButtons()
{
	CLGraphicStyle buttonStyleNormal( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
		RGBColor_Black, RGBColor_White,
		(byte) 1, RGBColor_White,
		RGBColor_Black );
	CLGraphicStyle buttonStyleDisabled( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
		RGBColor_Black, RGBColor_White,
		(byte) 1, 0x505050,
		RGBColor_Black, 0x505050 );
	CLGraphicStyle buttonStyleSelected( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
		0xD0EFAC, RGBColor_White,
		(byte) 2, 0xA0B784,
		0xD0EFAC );
	char	text[ 40 ];

	// PreHeater Button
	sprintf( text, "%s%s%s",
		CLLocalitation::GetText( CLTextId_PREHEATER ),
		CLFixedText_CRLF,
		(m_ClimaPreHeaterEnabled ? CLFixedText_ON : CLFixedText_OFF) );
	if (Accessory_HasPreCooler())
	{
		CLLCDCommon::DrawGenericButton( m_ClimaPreHeaterOnOffButtonRectangle,
			(m_ClimaPreHeaterEnabled ? GenericButtonStyle_On_SmallFont : GenericButtonStyle_Off_SmallFont),
			text );
	}
	else
	{
		CLLCDCommon::DrawGenericButton( m_ClimaPreHeaterOnOffButtonRectangle,
			GenericButtonStyle_Disabled_SmallFont,
			text );
	}

	// Summer Button
	CLLCDCommon::DrawGenericButton( m_ClimaSummerOnOffButtonRectangle,
		((!Accessory_HasCooler() && (gRDEeprom.Set_Output[ 0 ] & 0x07) != 4 && (gRDEeprom.Set_Output[ 1 ] & 0x07) != 4) ? buttonStyleDisabled : (m_ClimaSummerEnabled ? buttonStyleSelected : buttonStyleNormal)),
		&SummerImage );

	//sprintf( text, "%s%s%s",
	//	CLLocalitation::GetText( CLTextId_SUMMER ),
	//	CLFixedText_CRLF,
	//	(m_ClimaSummerEnabled ? CLFixedText_ON : CLFixedText_OFF) );
	//if (Accessory_IsPresent( ACC_EEP_CWD )
	//	|| Accessory_IsPresent( ACC_EEP_DXD ))
	//{
	//	CLLCDCommon::DrawGenericButton( m_ClimaSummerOnOffButtonRectangle,
	//		(m_ClimaSummerEnabled ? GenericButtonStyle_On_SmallFont : GenericButtonStyle_Off_SmallFont),
	//		text );
	//}
	//else
	//{
	//	CLLCDCommon::DrawGenericButton( m_ClimaSummerOnOffButtonRectangle,
	//		GenericButtonStyle_Disabled_SmallFont,
	//		text );
	//}

	// Winter Button
	CLLCDCommon::DrawGenericButton( m_ClimaWinterOnOffButtonRectangle,
		((!Accessory_HasHeather() && !Accessory_IsPresent( ACC_EEP_SSR ) && (gRDEeprom.Set_Output[ 0 ] & 0x07) != 4 && (gRDEeprom.Set_Output[ 1 ] & 0x07) != 4) ? buttonStyleDisabled : (m_ClimaWinterEnabled ? buttonStyleSelected : buttonStyleNormal)),
		&WinterImage );

	//sprintf( text, "%s%s%s",
	//	CLLocalitation::GetText( CLTextId_WINTER ),
	//	CLFixedText_CRLF,
	//	(m_ClimaWinterEnabled ? CLFixedText_ON : CLFixedText_OFF) );
	//if (Accessory_IsPresent( ACC_EEP_HWD )
	//	|| Accessory_IsPresent( ACC_EEP_EHD )
	//	|| Accessory_IsPresent( ACC_EEP_DXD ))
	//{
	//	CLLCDCommon::DrawGenericButton( m_ClimaWinterOnOffButtonRectangle,
	//		(m_ClimaWinterEnabled ? GenericButtonStyle_On_SmallFont : GenericButtonStyle_Off_SmallFont),
	//		text );
	//}
	//else
	//{
	//	CLLCDCommon::DrawGenericButton( m_ClimaWinterOnOffButtonRectangle,
	//		GenericButtonStyle_Disabled_SmallFont,
	//		text );
	//}

	RenderTemperatureButtons( Sun_TemperatureIndex );
	if (m_Mode == CLMode_DoubleTemperature)
		RenderTemperatureButtons( Moon_TemperatureIndex );
}

void CLTemperatureConfigForm::RenderTemperatureButtons( byte index )
{
	CLLCDCommon::DrawGenericButton( m_TemperatureUpButtonRectangles[ index ],
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	
	CLLCDCommon::DrawGenericButton( m_TemperatureDownButtonRectangles[ index ],
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );
}

void CLTemperatureConfigForm::RenderTemperatureProgressBar( byte index )
{
	char	text[ 15 ];

	switch (index)
	{
		case Sun_TemperatureIndex:
			CLGraphics::DrawProgressBar( CLRectangle( CLTemperatureConfigForm_SunTemperature_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				Temperature_ProgressBar_Color_Background, Temperature_ProgressBar_Color_BarFalse, Temperature_ProgressBar_Color_BarTrue,
				0, Sun_MaxTemperature, m_Temperatures[ Sun_TemperatureIndex ],
				4, 2 );

			sprintf( text, "%d %cC", m_Temperatures[ Sun_TemperatureIndex ], FONT_SYMBOL_DEGREES );
	
			CLGraphics::DrawText( CLTemperatureConfigForm_SunTemperature_TextProgressPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 5 );
			break;
				
		case Moon_TemperatureIndex:
			CLGraphics::DrawProgressBar( CLRectangle( CLTemperatureConfigForm_MoonTemperature_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				Temperature_ProgressBar_Color_Background, Temperature_ProgressBar_Color_BarFalse, Temperature_ProgressBar_Color_BarTrue,
				0, Moon_MaxTemperature, m_Temperatures[ Moon_TemperatureIndex ],
				4, 2 );

			sprintf( text, "%d %cC", m_Temperatures[ Moon_TemperatureIndex ], FONT_SYMBOL_DEGREES );
	
			CLGraphics::DrawText( CLTemperatureConfigForm_MoonTemperature_TextProgressPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 5 );
			break;
	}
}

void CLTemperatureConfigForm::SetClimaSummerEnabled( bool value )
{
	m_ClimaSummerEnabled	= value;
	if (value && m_ClimaWinterEnabled)
		SetClimaWinterEnabled( false );

	if (GetState() == CLState_Running)
		RenderButtons();
}

void CLTemperatureConfigForm::SetClimaWinterEnabled( bool value )
{
	m_ClimaWinterEnabled	= value;
	if (value && m_ClimaSummerEnabled)
		SetClimaSummerEnabled( false );

	if (GetState() == CLState_Running)
		RenderButtons();
}

void CLTemperatureConfigForm::SetClimaPreHeaterEnabled( bool value )
{
	m_ClimaPreHeaterEnabled	= value;

	if (GetState() == CLState_Running)
		RenderButtons();
}

void CLTemperatureConfigForm::SetTemperature( byte index, short value )
{
	switch (index)
	{
		case Sun_TemperatureIndex:
			if (value < Sun_MinTemperature)
				value	= Sun_MinTemperature;
			else
			if (value > Sun_MaxTemperature)
				value	= Sun_MaxTemperature;

			m_Temperatures[ index ]	= value;

			if (GetState() == CLState_Running)
				RenderTemperatureProgressBar( Sun_TemperatureIndex );
			break;
	
		case Moon_TemperatureIndex:
			if (value < Moon_MinTemperature)
				value	= Moon_MinTemperature;
			else
			if (value > Moon_MaxTemperature)
				value	= Moon_MaxTemperature;

			m_Temperatures[ index ]	= value;

			if (GetState() == CLState_Running)
				RenderTemperatureProgressBar( Moon_TemperatureIndex );
			break;

	}
}
// -----------------------------------------------------------------------------
// CLTemperatureConfigForm [class]
// =============================================================================

