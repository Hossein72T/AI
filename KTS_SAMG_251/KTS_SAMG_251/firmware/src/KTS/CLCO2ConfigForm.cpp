#include "CLCO2ConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLCO2ConfigForm_UpButtonRectangle			97, 47, 137, 87
#define	CLCO2ConfigForm_DownButtonRectangle			97, 123, 137, 163
#define	CLCO2ConfigForm_ProgressBarFrameRectangle	17, 35, 150, 176   // 17, 40, 231, 156
#define	CLCO2ConfigForm_ProgressBarRectangle		30, 38, 73, 150   // 30, 71, 219, 110
#define	CLCO2ConfigForm_TextProgressPoint			20, 158  // 30, 119

#define	CLCO2ConfigForm_ProgressBarFrameRectangle_C02	169, 35, 303, 176
#define	CLCO2ConfigForm_UpButtonRectangle_CO2		249, 47, 289, 87
#define	CLCO2ConfigForm_DownButtonRectangle_CO2		249, 123, 289, 163
#define	CLCO2ConfigForm_ProgressBarRectangle_CO2	182, 38, 225, 150
#define	CLCO2ConfigForm_TextProgressPoint_CO2	        172, 158

CLFormResult CLCO2ConfigForm_Open( unsigned short options )
{
	CLCO2ConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLCO2ConfigForm [class]
// -----------------------------------------------------------------------------
CLCO2ConfigForm::CLCO2ConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_UpButtonRectangle.Set( CLCO2ConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLCO2ConfigForm_DownButtonRectangle );
        
    m_UpButtonRectangle_CO2.Set( CLCO2ConfigForm_UpButtonRectangle_CO2 );
	m_DownButtonRectangle_CO2.Set( CLCO2ConfigForm_DownButtonRectangle_CO2 );
}

CLFormResult CLCO2ConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( gRDEeprom.SetPoint_CO2);
    SetValue1( gRDEeprom.SetPoint_Airflow_CO2);
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
			// Up Button CO2
			if (m_UpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				while (Touched() != 0)
				{
					SetValue( m_Value + 50 );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Down Button CO2
			if (m_DownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				while (Touched() != 0)
				{
					SetValue( m_Value - 50 );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
            else
            // Up Button Airflow
			if (m_UpButtonRectangle_CO2.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle_CO2 );

				while (Touched() != 0)
				{
					SetValue1( m_Value1 + 1 );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle_CO2 );
			}
            else
            // Down Button Airflow
			if (m_DownButtonRectangle_CO2.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle_CO2 );

				while (Touched() != 0)
				{
					SetValue1( m_Value1 - 1 );
					CLKTS::Process();
					//delay( UpDownButtons_Delay );
                    SYSTICK_DelayMs ( UpDownButtons_Delay );
					CLKTS::Pir_Process();
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle_CO2 );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLCO2ConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	unsigned short	saveSetPoint_CO2;
    byte	        saveSetPoint_Airflow_CO2;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveSetPoint_CO2	= gRDEeprom.SetPoint_CO2;
    saveSetPoint_Airflow_CO2 = gRDEeprom.SetPoint_Airflow_CO2;

	// Imposta i nuovi dati
	gRDEeprom.SetPoint_CO2	= m_Value;
    gRDEeprom.SetPoint_Airflow_CO2 = m_Value1;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, SetPoint_CO2 ),
		sizeof(gRDEeprom.SetPoint_CO2),
		&writeEeprom_Status );

    KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, SetPoint_Airflow_CO2 ),
    sizeof(gRDEeprom.SetPoint_Airflow_CO2),
    &writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.SetPoint_CO2	= saveSetPoint_CO2;
                gRDEeprom.SetPoint_Airflow_CO2 = saveSetPoint_Airflow_CO2;

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

void CLCO2ConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SET_CO2_THRESHOLD ),
		NULL );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	CLGraphics::DrawBox( CLRectangle( CLCO2ConfigForm_ProgressBarFrameRectangle ),
		GenericForm_Group_Style );
        CLGraphics::DrawBox( CLRectangle( CLCO2ConfigForm_ProgressBarFrameRectangle_C02 ),
		GenericForm_Group_Style );

	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &DownMonoImage );

        CLLCDCommon::DrawGenericButton( m_UpButtonRectangle_CO2,
		GenericButtonStyle_Normal_UpDown, &UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle_CO2,
		GenericButtonStyle_Normal_UpDown, &DownMonoImage );

	RenderDynamicObjects();
}

void CLCO2ConfigForm::RenderDynamicObjects()
{
	char	text[ 12 ];

	// Progress Bar CO2
	CLGraphics::DrawProgressBar( CLRectangle( CLCO2ConfigForm_ProgressBarRectangle ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
		CO2_ProgressBar_Color_Background, CO2_ProgressBar_Color_BarFalse, CO2_ProgressBar_Color_BarTrue,
		0, CLKTS::CO2_GetMax(), m_Value,
		4, 2 );

        // Progress Bar Airflow
	CLGraphics::DrawProgressBar( CLRectangle( CLCO2ConfigForm_ProgressBarRectangle_CO2 ),
		CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
		CO2_ProgressBar_Color_Background, CO2_ProgressBar_Color_BarFalse, CO2_ProgressBar_Color_BarTrue,
		0, 100, m_Value1,
		4, 2 );

	sprintf( text, "%d ppm", m_Value );

	CLGraphics::DrawText( CLCO2ConfigForm_TextProgressPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text, 8 );

        sprintf( text, "%d %%", m_Value1 );

	CLGraphics::DrawText( CLCO2ConfigForm_TextProgressPoint_CO2, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text, 8 );
}

void CLCO2ConfigForm::SetValue( unsigned short value)
{
	if (value < CLKTS::CO2_GetMin())
		value	= CLKTS::CO2_GetMin();
	else
	if (value > CLKTS::CO2_GetMax())
		value	= CLKTS::CO2_GetMax();

	m_Value	= value;
	if (GetState() == CLState_Running)
		RenderDynamicObjects();
}

void CLCO2ConfigForm::SetValue1( byte value)
{
	if (value < 30)
		value	= 30;
	else
	if (value > 100)
		value	= 100;

	m_Value1 = value;
	if (GetState() == CLState_Running)
		RenderDynamicObjects();
}

// -----------------------------------------------------------------------------
// CLCO2ConfigForm [class]
// =============================================================================

