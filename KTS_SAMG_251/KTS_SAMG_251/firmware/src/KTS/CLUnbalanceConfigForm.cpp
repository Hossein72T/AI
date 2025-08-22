#include "CLUnbalanceConfigForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"

#define CLUnbalanceConfigForm_OnOffButtonRectangle			15, 35, 84, 94
#define CLUnbalanceConfigForm_DataFrameRectangle			93, 35, 304, 164
#define CLUnbalanceConfigForm_UpButtonRectangle				257, 44, 296, 83
#define CLUnbalanceConfigForm_DownButtonRectangle			257, 116, 296, 155
#define CLUnbalanceConfigForm_SupplyTextRectangle			100, 44, 219, 63
#define CLUnbalanceConfigForm_ExtractTextRectangle			100, 136, 219, 155
#define CLUnbalanceConfigForm_ValueTextPoint				101, 91
#define CLUnbalanceConfigForm_SupplyProgressBarRectangle	228, 44, 248, 99
#define CLUnbalanceConfigForm_ExtractProgressBarRectangle	228, 100, 248, 155

CLFormResult CLUnbalanceConfigForm_Open( unsigned short options )
{
	CLUnbalanceConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLUnbalanceConfigForm [class]
// -----------------------------------------------------------------------------
CLUnbalanceConfigForm::CLUnbalanceConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLUnbalanceConfigForm_OnOffButtonRectangle );

	m_UpButtonRectangle.Set( CLUnbalanceConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLUnbalanceConfigForm_DownButtonRectangle );
}

CLFormResult CLUnbalanceConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetEnabled( Function_IsEnabled( ENAB_IMBALANCE ) );
	SetValue( gRDEeprom.Set_Imbalance[ 0 ] );
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
				CLLCDCommon::WaitButton( m_OkButtonRectangle );

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
			// On Button
			if (m_OnOffButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OnOffButtonRectangle );
				SetEnabled( !m_Enabled );
			}
			else
			// Up Button
			if (m_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetValue( m_Value + 5 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Down Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetValue( m_Value - 5 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLUnbalanceConfigForm::Save( unsigned short options )
{
	signed char		saveSet_Imbalance;
	bool			saveImbalanceIsEnabled;
	ComQueue_Status	writeEeprom_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	for (int stepsCounter = 0; stepsCounter < 2; stepsCounter++)
	{
		// Effettua la prima richiesta
		if (stepsCounter == 0)
		{
			// Salva temporaneamente i dati correnti
			saveSet_Imbalance	= gRDEeprom.Set_Imbalance[ 0 ];

			//Imposta il nuovo valore
			gRDEeprom.Set_Imbalance[ 0 ]	= m_Value;

			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_Imbalance ),
				sizeof(gRDEeprom.Set_Imbalance),
				&writeEeprom_Status );
		}
		else
		{
			// Salva temporaneamente i dati correnti
			saveImbalanceIsEnabled	= Function_IsEnabled( ENAB_IMBALANCE );

			//Imposta il nuovo valore
			Function_SetEnabled( ENAB_IMBALANCE, m_Enabled );

			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
				sizeof(gRDEeprom.Enab_Fuction),
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
			if (stepsCounter == 0)
				gRDEeprom.Set_Imbalance[ 0 ]	= saveSet_Imbalance;
			else
				Function_SetEnabled( ENAB_IMBALANCE, saveImbalanceIsEnabled );

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

void CLUnbalanceConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SET_UNBALANCE ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Minutes Frame
	CLGraphics::DrawBox( CLRectangle( CLUnbalanceConfigForm_DataFrameRectangle ), 
		GenericForm_Group_Style );

	CLGraphics::DrawBoxWithText( CLRectangle( CLUnbalanceConfigForm_SupplyTextRectangle ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Font_Small,
		Temperature_Cold_Color, RGBColor_White,
		CLLocalitation::GetText( CLTextId_SUPPLY ) );
	CLGraphics::DrawBoxWithText( CLRectangle( CLUnbalanceConfigForm_ExtractTextRectangle ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Font_Small,
		Temperature_Hot_Color, RGBColor_White,
		CLLocalitation::GetText( CLTextId_EXTRACT ) );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderOnOffButtons();
	RenderProgressBar();
}

void CLUnbalanceConfigForm::RenderOnOffButtons()
{
	// On/Off Button
	CLLCDCommon::DrawGenericButton( m_OnOffButtonRectangle,
		(m_Enabled ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(m_Enabled ? CLFixedText_ON : CLFixedText_OFF) );

	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );
	RenderProgressBar();
}

void CLUnbalanceConfigForm::RenderProgressBar()
{
	char	text[ 10 ];

	CLGraphics::DrawProgressBar( CLRectangle( CLUnbalanceConfigForm_SupplyProgressBarRectangle ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_StartWith_Max | CLDrawBarOptions_BarShape_Progressive,
		TemperatureCold_ProgressBar_Color_Background, TemperatureCold_ProgressBar_Color_BarFalse, TemperatureCold_ProgressBar_Color_BarTrue,
		0, 70, (m_Value > 0 ? m_Value : 0),
		4, 2 );
	CLGraphics::DrawProgressBar( CLRectangle( CLUnbalanceConfigForm_ExtractProgressBarRectangle ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive,
		TemperatureHot_ProgressBar_Color_Background, TemperatureHot_ProgressBar_Color_BarFalse, TemperatureHot_ProgressBar_Color_BarTrue,
		0, 70, (m_Value < 0 ? abs(m_Value) : 0),
		4, 2 );

	sprintf( text, "%d %%", m_Value );
	CLGraphics::DrawText( CLUnbalanceConfigForm_ValueTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, (m_Value < 0 ? Temperature_Hot_Color : m_Value > 0 ? Temperature_Cold_Color : RGBColor_White),
		text, 7 );
}

void CLUnbalanceConfigForm::SetEnabled( bool value )
{
	m_Enabled	= value;

	if (GetState() == CLState_Running)
		RenderOnOffButtons();
}

void CLUnbalanceConfigForm::SetValue( signed char value )
{
	if (value < -70)
		value	= -70;
	else
	if (value > 70)
		value	= 70;

	m_Value	= value;

	if (GetState() == CLState_Running)
		RenderProgressBar();
}
// -----------------------------------------------------------------------------
// CLUnbalanceConfigForm [class]
// =============================================================================


