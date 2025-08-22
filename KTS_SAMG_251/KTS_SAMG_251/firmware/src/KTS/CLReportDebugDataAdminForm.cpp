//-------------------------------------------------------------
//-------------------------------------------------------------
//------------------ ReportDates --------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------

#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLReportDebugDataAdminForm.h"
#include "CLCommunicationManager.h"
#include "RDProtocol.h"
#include "CLAccessory.h"
#include "CLTouch.h"
#include "CLLocalitation.h"
#include "CLBypass.h"
#include "CLFunction.h"

// TODO: Utilizzare la CLGraphics

//--------------------------------------------------------------
#define Y_ROW1             50
#define Y_ROW2             70
#define Y_ROW3             90
#define Y_ROW4            110
#define Y_ROW5            130
#define Y_ROW6            150
#define Y_ROW7            170
#define Y_ROW8            190
//--------------------------------------------------------------

#define	CLReportDebugDataAdminForm_TESTIPHED_ConfigButtonRectangle			228, 113, 308, 163 


const unsigned long ReportDataDebug_RequestMilliseconds = 2500;
uint8_t CO2_1_Accuracy = 0;
uint8_t CO2_2_Accuracy = 0;

CLFormResult CLReportDebugDataAdminForm_Open( unsigned short options )
{
	CLReportDebugDataAdminForm	form;

	return form.Open( options );
}

void CLReportDebugDataAdminForm_ResponseCallback( byte* rxBuffer, void* userData )
{
	CLReportDebugDataAdminForm*	reportDebugDataForm	= (CLReportDebugDataAdminForm*) userData;

	if (reportDebugDataForm == NULL)
		return;

	reportDebugDataForm->Level_Link_Sensor =  rxBuffer[IRSD_LEV_LINK_CAP];
	reportDebugDataForm->Measures_Pressure =  (int)(((int)rxBuffer[IRSD_MEASUR_PA_HI] << 8) +  rxBuffer[IRSD_MEASUR_PA_LO]); // 2 Byte

	reportDebugDataForm->FeedBk_VoutF = ((float) (rxBuffer[IRSD_FEEDBK_VOUT_F_LO] | ((unsigned int) rxBuffer[IRSD_FEEDBK_VOUT_F_HI] << 8))) / 100.0;
	reportDebugDataForm->FeedBk_VoutR = ((float) (rxBuffer[IRSD_FEEDBK_VOUT_R_LO] | ((unsigned int) rxBuffer[IRSD_FEEDBK_VOUT_R_HI] << 8))) / 100.0;
	reportDebugDataForm->Rpm_FanR[0]  = rxBuffer[IRSD_RPM_MOTOR_R1_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_R1_HI] << 8);
	reportDebugDataForm->Rpm_FanR[1]  = rxBuffer[IRSD_RPM_MOTOR_R2_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_R2_HI] << 8);
	reportDebugDataForm->Rpm_FanR[2]  = rxBuffer[IRSD_RPM_MOTOR_R3_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_R3_HI] << 8);
	reportDebugDataForm->Rpm_FanF[0]  = rxBuffer[IRSD_RPM_MOTOR_F1_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_F1_HI] << 8);
	reportDebugDataForm->Rpm_FanF[1]  = rxBuffer[IRSD_RPM_MOTOR_F2_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_F2_HI] << 8);
	reportDebugDataForm->Rpm_FanF[2]  = rxBuffer[IRSD_RPM_MOTOR_F3_LO] | ((unsigned int)rxBuffer[IRSD_RPM_MOTOR_F3_HI] << 8);

	reportDebugDataForm->Status_FanR  = rxBuffer[IRSD_STATUS_MOTORS_R];
	reportDebugDataForm->Status_FanF  = rxBuffer[IRSD_STATUS_MOTORS_F];

	reportDebugDataForm->PreHeater_LinkLevel		= rxBuffer[ IRSD_LEV_LINK_PREHEATER ];
	reportDebugDataForm->Heater_LevelLink			= rxBuffer[ IRSD_LEV_LINK_HEATER ];
	reportDebugDataForm->Cooler_LevelLink			= rxBuffer[ IRSD_LEV_LINK_COOLER ];
	reportDebugDataForm->PreHeater_Status			= rxBuffer[ IRSD_STATUS_PREHEATER ];
	reportDebugDataForm->Heater_Status				= rxBuffer[ IRSD_STATUS_HEATER ];
	reportDebugDataForm->Cooler_Status				= rxBuffer[ IRSD_STATUS_COOLER ];
	reportDebugDataForm->Heater_WaterTemperature	= ((float) MAKEWORD( rxBuffer, IRSD_MEASURE_TW_HEAT_HI, IRSD_MEASURE_TW_HEAT_LO ) / 10);
	reportDebugDataForm->Heater_AirTemperature		= ((float) MAKEWORD( rxBuffer, IRSD_MEASURE_TA_HEAT_HI, IRSD_MEASURE_TA_HEAT_LO ) / 10);
	reportDebugDataForm->Cooler_WaterTemperature	= ((float) MAKEWORD( rxBuffer, IRSD_MEASURE_TW_COOL_HI, IRSD_MEASURE_TW_COOL_LO ) / 10);
	reportDebugDataForm->Cooler_AirTemperature		= ((float) MAKEWORD( rxBuffer, IRSD_MEASURE_TA_COOL_HI, IRSD_MEASURE_TA_COOL_LO ) / 10);
	reportDebugDataForm->MeasureAirflow				= ((word) MAKEWORD( rxBuffer, IRSD_MEASURE_AIRFLOW_HI, IRSD_MEASURE_AIRFLOW_LO ));

	reportDebugDataForm->ReceivedData	= 1;
    
    reportDebugDataForm->CAPR_LinkLevel = rxBuffer[ IRSD_LEV_LINK_CAPR ];
    reportDebugDataForm->CAPS_LinkLevel = rxBuffer[ IRSD_LEV_LINK_CAPS ];
    reportDebugDataForm->CAPR_Status = rxBuffer[ IRSD_STATUS_CAPR ];
    reportDebugDataForm->CAPS_Status = rxBuffer[ IRSD_STATUS_CAPS ];
    
    reportDebugDataForm->MeasureAirflow_CAPR = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_AF_CAPR_HI, IRSD_MEASUR_AF_CAPR_LO ));
    reportDebugDataForm->MeasureAirflow_CAPS = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_AF_CAPS_HI, IRSD_MEASUR_AF_CAPS_LO ));
    reportDebugDataForm->Measures_Pressure_CAPR = (int)(((int)rxBuffer[IRSD_MEASUR_PA_CAPR_HI] << 8) +  rxBuffer[IRSD_MEASUR_PA_CAPR_LO]); // 2 Byte
    reportDebugDataForm->Measures_Pressure_CAPS =  (int)(((int)rxBuffer[IRSD_MEASUR_PA_CAPS_HI] << 8) +  rxBuffer[IRSD_MEASUR_PA_CAPS_LO]);
    
    reportDebugDataForm->Measure_CO2_1 = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_CO2_1_HI, IRSD_MEASUR_CO2_1_LO ));
    reportDebugDataForm->Measure_VOC_1 = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_VOC_1_HI, IRSD_MEASUR_VOC_1_LO ));
    reportDebugDataForm->Measure_RH_1 = rxBuffer[ IRSD_MEASUR_RH_1 ];
    reportDebugDataForm->Measure_CO2_2 = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_CO2_2_HI, IRSD_MEASUR_CO2_2_LO ));
    reportDebugDataForm->Measure_RH_2 = rxBuffer[ IRSD_MEASUR_RH_2 ];
    reportDebugDataForm->Firm_Ver_CO2_1 = rxBuffer[ IRSD_FIRM_VER_CO2_1 ];
    reportDebugDataForm->Firm_Ver_CO2_2 = rxBuffer[ IRSD_FIRM_VER_CO2_2 ];
    reportDebugDataForm->CO2_1_LinkLevel = rxBuffer[ IRSD_LEV_LINK_CO2_1 ];
    reportDebugDataForm->CO2_2_LinkLevel = rxBuffer[ IRSD_LEV_LINK_CO2_2 ];
    reportDebugDataForm->Measure_IAQ_1 = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_IAQ_1_HI, IRSD_MEASUR_IAQ_1_LO )) & 0x0FFF;
    reportDebugDataForm->Measure_IAQ_2 = ((word) MAKEWORD( rxBuffer, IRSD_MEASUR_IAQ_2_HI, IRSD_MEASUR_IAQ_2_LO )) & 0x0FFF;
    reportDebugDataForm->IAQ_1_Accuracy = (rxBuffer[ IRSD_MEASUR_IAQ_1_HI ] >> 4) & 3;
    reportDebugDataForm->IAQ_2_Accuracy = (rxBuffer[ IRSD_MEASUR_IAQ_2_HI ] >> 4) & 3;
    reportDebugDataForm->CO2_1_Status = rxBuffer[ IRSD_STATUS_CO2_1 ];
    reportDebugDataForm->CO2_2_Status = rxBuffer[ IRSD_STATUS_CO2_2 ];
    reportDebugDataForm->CO2_1_Accuracy = rxBuffer[ IRSD_ACCURACY_CO2_1 ] & 3;
    reportDebugDataForm->CO2_2_Accuracy = rxBuffer[ IRSD_ACCURACY_CO2_2 ] & 3;
    
    CO2_1_Accuracy = reportDebugDataForm->CO2_1_Accuracy;
    CO2_2_Accuracy = reportDebugDataForm->CO2_2_Accuracy;
}

// =============================================================================
// CLReportDebugDataAdminForm [class]
// -----------------------------------------------------------------------------
CLReportDebugDataAdminForm::CLReportDebugDataAdminForm()
	: m_Page( 10 )
{
	Level_Link_Sensor	=  0;
	Measures_Pressure	=  0;
    Measures_Pressure_CAPS = 0;
    Measures_Pressure_CAPR = 0;
	Status_FanR			= 0;
	Status_FanF			= 0;
	FeedBk_VoutF		= 0;
	FeedBk_VoutR		= 0;
	Rpm_FanR[ 0 ]		= 0;
	Rpm_FanR[ 1 ]		= 0;
	Rpm_FanR[ 2 ]		= 0;
	Rpm_FanF[ 0 ]		= 0;
	Rpm_FanF[ 1 ]		= 0;
	Rpm_FanF[ 2 ]		= 0;

	PreHeater_LinkLevel		= 0;
	Heater_LevelLink		= 0;
	Cooler_LevelLink		= 0;
	PreHeater_Status		= 0;
	Heater_Status			= 0;
	Cooler_Status			= 0;
	Heater_WaterTemperature	= 0;
	Heater_AirTemperature	= 0;
	Cooler_WaterTemperature	= 0;
    
    CAPS_LinkLevel = 0;
	CAPR_LinkLevel = 0;
    CAPS_Status = 0;
	CAPR_Status = 0;
    
    Measure_CO2_1 = 0;
    Measure_VOC_1 = 0;
    Measure_RH_1 = 0;
    Measure_CO2_2 = 0;
    Measure_RH_2 = 0;
    Firm_Ver_CO2_1 = 0;
    Firm_Ver_CO2_2 = 0;
    CO2_1_LinkLevel = 0;
    CO2_2_LinkLevel = 0;
    Measure_IAQ_1 = 0;
    Measure_IAQ_2 = 0;
    CO2_1_Status = 0;
	CO2_2_Status = 0;
    CO2_1_Accuracy = 0;
    CO2_2_Accuracy = 0;
    IAQ_1_Accuracy = 0;
    IAQ_2_Accuracy = 0;
    
	m_FirstRequestDebugData	= true;

	m_HomeButtonRectangle.Set( ::Form_HomeButtonRectangle );
	m_PreviousButtonRectangle.Set( ViewForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( ViewForm_NextButtonRectangle );
	m_BackButtonRectangle.Set( 0, 190, 70, 229 );
}

CLFormResult CLReportDebugDataAdminForm::Open( unsigned short options )
{
	int				touchX, touchY;
	unsigned long	previousTimerRefresh;
	ComQueue_Status	dataDebugRequestStatus;
	int				dataDebugRequestQueueIndex	= -1;
	CLFormResult	formResult;
	m_RefTSetting	= gRDEeprom.RefTSetting;

	previousTimerRefresh	= 0;
	ReceivedData			= 0;
	m_AdminMode				= options & CLFormOption_AdminMode;

	RenderPage();

	while (true)
	{
		// Processa le funzionalitÃ  del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		// Se esiste una richiesta in pendente, controlla se Ã¨ ancora in esecuzione, altrimenti refresh dei dati
		if (dataDebugRequestQueueIndex != -1)
		{
			if (!COM_REQUEST_ISRUNNING( dataDebugRequestStatus ))
			{
				dataDebugRequestQueueIndex	= -1;
				m_FirstRequestDebugData		= false;
				RenderData();
			}
		}

		// Se scade il tempo di attesa, accoda la richiesta di dati di debug
		if (millis() - previousTimerRefresh >= ReportDataDebug_RequestMilliseconds ||
			millis() < previousTimerRefresh)
		{
			// Se non e' gia' accodata, accoda la richiesta di Debug Data
			if (dataDebugRequestQueueIndex == -1)
			{
				dataDebugRequestQueueIndex	= ComQueue_AddDataDebugRequest( &dataDebugRequestStatus, CLReportDebugDataAdminForm_ResponseCallback );
				if (dataDebugRequestQueueIndex != -1)
					gComQueueRequests[ dataDebugRequestQueueIndex ].UserData	= this;
			}

			previousTimerRefresh	= millis();
		}

		if (Touched())
		{
			bool	exitForm	= false;
			touchX	= ReadX();
			touchY	= ReadY();

			if (m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// BACK button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			// NEXT button
			else
			if (m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage();

				// Reset timer
				previousTimerRefresh	= millis();
			}
			// PREVIOUS button
			else
			if (m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				if (m_Page.GoPrevious())
					RenderPage();

				previousTimerRefresh	= millis();
			}
			// TEST IPEHD button
			else
			if (m_Page.GetValue() == 2)
			{
			if (m_TestIPEHD.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_TestIPEHD );

				if(bitRead( m_RefTSetting, 6 ) == 0)
				   bitSet( m_RefTSetting, 6 );
				
					
				previousTimerRefresh	= millis();
				
				if (Save( options ))
					{
						if (CLFormOption_CanExitAfterWrite( options ))
						{
							formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
							exitForm	= true;
							break;
						}
					}
				
			}
			else
				WaitForTouchRelease();
			}
			else
				WaitForTouchRelease();
		}
	}

	// Se esiste una richiesta in coda, l'annulla
	if (dataDebugRequestQueueIndex == -1)
	{
		ComQueue_RemoveRequest( dataDebugRequestQueueIndex, true );
		dataDebugRequestQueueIndex	= -1;
	}

	return formResult;
}

bool CLReportDebugDataAdminForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveRefTSetting;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveRefTSetting			= gRDEeprom.RefTSetting;

	// Imposta i nuovi dati
	gRDEeprom.RefTSetting		= m_RefTSetting;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, RefTSetting),
		sizeof(gRDEeprom.RefTSetting),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.RefTSetting		= saveRefTSetting;
		

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


void CLReportDebugDataAdminForm::RenderPage()
{
	char*	pageTitle	= NULL;
    char	text[ 40 ];

	gLCD.clrScr();  // clear screen.
	gLCD.setFont( &CLBigFont, CLKTS::GetCodePage() );

	// Draw Data Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Tasto Previous
    CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Tasto Next
    CLLCDCommon::DrawNextButton( m_NextButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Tasto Back
    CLLCDCommon::DrawBackButton( m_BackButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

    gLCD.setRGBColor( RGBColor_White );
    gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );

    switch (m_Page.GetValue())
    {
		case 0: // Page 1 - STATUS MOTORS
			/*
				STATUS MOTORS  (2/2)
				Motors R       Motors F
				COMAND: 8.55 V COMAND: 8.43 V
				RPM_R1: 2300   RPM_F1: 2300
				RPM_R2: 2247   RPM_F2: 2305
				RPM_R1: NO_PWR RPM_F1: NO_PWR
			*/

			// Imposta il titolo della pagina
			pageTitle	= (char*) "MOTORS STATUS";

			//                   x1, y1, x2,  y2
			gLCD.drawRoundRect(5, 40,  155, 150);
			gLCD.print("MOTORS R ", 55,  Y_ROW1);
			gLCD.print("COMMAND: ", 10,   Y_ROW2);
			gLCD.print("RPM R1 : ", 10,   Y_ROW3);
			gLCD.print("RPM R2 : ", 10,   Y_ROW4);
			gLCD.print("RPM R3 : ", 10,   Y_ROW5);

			//                   x1, y1, x2,  y2
			gLCD.drawRoundRect(160, 40,  310, 150);
			gLCD.print("MOTORS F ", 205, Y_ROW1);
			gLCD.print("COMMAND: ", 165,  Y_ROW2);
			gLCD.print("RPM F1 : ", 165,  Y_ROW3);
			gLCD.print("RPM F2 : ", 165,  Y_ROW4);
			gLCD.print("RPM F3 : ", 165,  Y_ROW5);
			break;

		case 1: // Page 2 - Accessory Clima 1

			// Imposta il titolo della pagina
			pageTitle	= (char*) "ACC. CLIMA";

			// Draw Cooler Box
			CLGraphics::DrawBox( CLRectangle( 6, 40, 313, 100 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0x4297D4 );

			gLCD.print( "COOLER  :", 18, 48 );
			gLCD.print( "COMMAND :", 18, 64 );
			gLCD.print( "LINK LEVEL :", 146, 64 );
			gLCD.print( "T. AIR  :",  18, 80 );
			gLCD.print( "T. WATER:", 180, 80 );
			// Draw Heater Box
			CLGraphics::DrawBox( CLRectangle( 6, 108, 313, 168 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0xFF0000 );

			gLCD.print( "HEATER  :", 18, 116 );
			gLCD.print( "COMMAND :", 18, 132 );
			gLCD.print( "LINK LEVEL :", 146, 132 );
			gLCD.print( "T. AIR  :", 18, 148 );
			break;

		case 2: // Page 3 - Accessory Clima 2

			// Imposta il titolo della pagina
			pageTitle	= (char*) "ACC. CLIMA";

			// Draw PreHeater Box
			CLGraphics::DrawBox( CLRectangle( 6, 40, 313, 100 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0xE6B800 );

			gLCD.print( "PHEATER :", 18, 48 );
			gLCD.print( "COMMAND :", 18, 64 );
			gLCD.print( "LINK LEVEL :", 146, 64 );
			
			// Draw Internal PreHeater Box
			CLGraphics::DrawBox( CLRectangle( 6, 108, 313, 168 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0xE6B800 );

			gLCD.print( "INT. PHEATER", 18, 116 );
			// gLCD.print( "COMMAND :", 18, 132 ); andiamo ad abilitarlo quando ci passiamo il comando
			// TEST Button
			m_TestIPEHD.Set( CLReportDebugDataAdminForm_TESTIPHED_ConfigButtonRectangle );
			CLLCDCommon::DrawGenericButton( m_TestIPEHD, GenericButtonStyle_Selected_SmallFont,	"TEST" );
			break;

		case 3: // Page 4 - Bypass

			// Imposta il titolo della pagina
			pageTitle	= (char*) CLLocalitation::GetText( CLTextId_BYPASS );

			gLCD.print( "CONFIG         :", 18, 48 );
			gLCD.print( "STATUS         :", 18, 64 );
			gLCD.print( "TFRESH         :", 18, 80 );
			gLCD.print( "TRETURN        :", 18, 96 );
			gLCD.print( "TSUPPLY        :", 18, 112 );
			gLCD.print( "TEXHAUST       :", 18, 128 );
			gLCD.print( "MIN TEMP. EXT. :", 18, 144 );
			break;

		case 4: // Page 5 - CAP/CAF DATA
			// Imposta il titolo della pagina
			pageTitle	= (char*) "CAP/CAF DATA";

			gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			gLCD.print( CLLocalitation::GetText( CLTextId_PRESSURE_SENSOR ), 15,  Y_ROW1 );
			gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  Y_ROW2 );
			
			if (VentilationControl_Get() == CLVentilationControl_CAP)
				gLCD.print( CLLocalitation::GetText( CLTextId_SETPOINT_PRESSURE ), 15,  Y_ROW3 );
			else
				gLCD.print( "SETPOINT AIRFLOW:", 15,  Y_ROW3 );

			gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_PRESSURE ), 15,  Y_ROW4 );
            
            memset ( text, 0, sizeof(text));
			//gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ), 15,  Y_ROW5 );
            strcat (text, CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ));
            strcat (text, ":");
            gLCD.print( text, 15,  Y_ROW5 );
			break;
        
        case 5: // Page 6 - CAPS DATA
			// Imposta il titolo della pagina
			pageTitle	= (char*) "CAPS DATA";

			gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			gLCD.print( CLLocalitation::GetText( CLTextId_PRESSURE_SENSOR ), 15,  Y_ROW1 );
			gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  Y_ROW2 );
			
			//if (VentilationControl_Get() == CLVentilationControl_CAP)
				gLCD.print( CLLocalitation::GetText( CLTextId_SETPOINT_PRESSURE ), 15,  Y_ROW3 );
			//else
				//gLCD.print( "SETPOINT AIRFLOW:", 15,  Y_ROW3 );
            
            memset ( text, 0, sizeof(text));
			gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_PRESSURE ), 15,  Y_ROW4 );
            strcat (text, CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ));
            strcat (text, ":");
			//gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ), 15,  Y_ROW5 );
            gLCD.print( text, 15,  Y_ROW5 );

			break;
         
        case 6: // Page 7 - CAPR DATA
			// Imposta il titolo della pagina
			pageTitle	= (char*) "CAPR DATA";

			gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			gLCD.print( CLLocalitation::GetText( CLTextId_PRESSURE_SENSOR ), 15,  Y_ROW1 );
			gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  Y_ROW2 );
			
			//if (VentilationControl_Get() == CLVentilationControl_CAP)
				gLCD.print( CLLocalitation::GetText( CLTextId_SETPOINT_PRESSURE ), 15,  Y_ROW3 );
			//else
				//gLCD.print( "SETPOINT AIRFLOW:", 15,  Y_ROW3 );

			gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_PRESSURE ), 15,  Y_ROW4 );
            memset ( text, 0, sizeof(text));
			//gLCD.print( CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ), 15,  Y_ROW5 );
            strcat (text, CLLocalitation::GetText( CLTextId_MEASURE_AIRFLOW ));
            strcat (text, ":");
            gLCD.print( text, 15,  Y_ROW5 );
			break;
            
		case 7: // Page 8 - AIR SENSOR 1
			// Imposta il titolo della pagina
			pageTitle	= (char*) "AIR SENSOR1";
            
            gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			gLCD.print( CLLocalitation::GetText( CLTextId_AIR_SENSOR_STATE ), 15,  38 );
			gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  54 );
            gLCD.print( CLLocalitation::GetText( CLTextId_CO2_VALUE ), 15,  70 );
            gLCD.print( CLLocalitation::GetText( CLTextId_VOC_VALUE ), 15,  86 );
            gLCD.print( CLLocalitation::GetText( CLTextId_RH_VALUE ), 15,  102 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_SENSOR_ACCURRACY ), 15,  118 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_QUALITY ), 15,  134 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_QUALITY_PRECISION ), 15,  150 );
            //gLCD.print( CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ), 15,  166 );
            memset ( text, 0, sizeof(text));
            strcat ( text , CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ));
            strcat ( text , ":");
            gLCD.print( text, 15,  166 );
			break;
        
         case 8: // Page 9 - AIR SENSOR 2
			// Imposta il titolo della pagina
			pageTitle	= (char*) "AIR SENSOR2";
            
            gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			gLCD.print( CLLocalitation::GetText( CLTextId_AIR_SENSOR_STATE ), 15,  38 );
			gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  54 );
            gLCD.print( CLLocalitation::GetText( CLTextId_CO2_VALUE ), 15,  70 );
            gLCD.print( CLLocalitation::GetText( CLTextId_VOC_VALUE ), 15,  86 );
            gLCD.print( CLLocalitation::GetText( CLTextId_RH_VALUE ), 15,  102 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_SENSOR_ACCURRACY ), 15,  118 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_QUALITY ), 15,  134 );
            gLCD.print( CLLocalitation::GetText( CLTextId_AIR_QUALITY_PRECISION ), 15,  150 );
            //gLCD.print( CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ), 15,  166 );
            memset ( text, 0, sizeof(text));
            strcat ( text , CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ));
            strcat ( text , ":");
            gLCD.print( text, 15,  166 );
			break;
            
        case 9: // Page 10 - STATUS UNIT
			// Imposta il titolo della pagina
			pageTitle	= (char*) "UNIT STATUS";
			break;    

	}

	// Display Title
	gLCD.setFont( &CLBigFont, CLKTS::GetCodePage() );
	RenderFormTitle( pageTitle,
		&m_Page );

	if (ReceivedData)
		RenderData();
}

void CLReportDebugDataAdminForm::RenderData()
{
	int		setP;
	char	text[ 40 ];

    gLCD.setRGBColor( RGBColor_White );
    gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );

	switch (m_Page.GetValue())
	{
		case 0:	// Page 0 - STATUS MOTORS
			/*
			STATUS MOTORS  (2/2)
			y= 15          y=160
			CMD_MR: 8.55   CMD_MF: 8.43      x= 40
			rpm_R1: 2300   rpm_F1: 2300      x= 60
			rpm_R2: 2247   rpm_F2: 2305      x= 80
			rpm_R1: NO_PWR rpm_F1: NO_PWR    x=100
			*/

			// ramo R
			sprintf( text, "%.2f V", FeedBk_VoutR );
			CLGraphics::DrawText( 70, Y_ROW2, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			// status_FanR : bit: 7.none | 6.AlarmMR3 | 5.AlarmMR2 | 4.AlarmMR1 | 3.none | 2.PowerMR3 | 1.PowerMR2 | 0.PowerMR1
			if(Status_FanR & 0x01)
				sprintf( text, "%d", Rpm_FanR[ 0 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 70, Y_ROW3, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			if(Status_FanR & 0x02)
				sprintf( text, "%d", Rpm_FanR[ 1 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 70, Y_ROW4, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			if(Status_FanR & 0x04)
				sprintf( text, "%d", Rpm_FanR[ 2 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 70, Y_ROW5, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			// ramo F
			sprintf( text, "%.2f V", FeedBk_VoutF );
			CLGraphics::DrawText( 225, Y_ROW2, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			if(Status_FanF & 0x01)
				sprintf( text, "%d", Rpm_FanF[ 0 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 225, Y_ROW3, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			if(Status_FanF & 0x02)
				sprintf( text, "%d", Rpm_FanF[ 1 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 225, Y_ROW4, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );

			if(Status_FanF & 0x04)
				sprintf( text, "%d", Rpm_FanF[ 2 ] );
			else
				strcpy( text, "No Power" );
			CLGraphics::DrawText( 225, Y_ROW5, CLGraphicStyleOptions_HAlign_Left,
				text, 10 );
			break;

		case 1: // Page 1 - Accessory Clima 1/2

			// Cooler Box
			// ----------
			Accessory_GetStatusText( text, Cooler_Status );
			CLGraphics::DrawText( 90, 48, CLGraphicStyleOptions_HAlign_Left,
				text, 27 );

			Accessory_GetCommandText( text, Cooler_Status );
			CLGraphics::DrawText( 90, 64, CLGraphicStyleOptions_HAlign_Left,
				text, 4 );

			CLKTS::LevelLink_GetText( text, Cooler_LevelLink );
			CLGraphics::DrawText( 242, 64, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", Cooler_AirTemperature );
			CLGraphics::DrawText( 90, 80, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", Cooler_WaterTemperature );
			CLGraphics::DrawText( 252, 80, CLGraphicStyleOptions_Default,
				text );	

			// Heater Box
			// -----------
			Accessory_GetStatusText( text, Heater_Status );
			CLGraphics::DrawText( 90, 116, CLGraphicStyleOptions_HAlign_Left,
				text, 27 );

			Accessory_GetCommandText( text, Heater_Status );
			CLGraphics::DrawText( 90, 132, CLGraphicStyleOptions_HAlign_Left,
				text, 4 );

			CLKTS::LevelLink_GetText( text, Heater_LevelLink );
			CLGraphics::DrawText( 242, 132, CLGraphicStyleOptions_Default,
				text );

			// Air o Water
			if (bitRead( Heater_Status, 1 ))
			{
				CLGraphics::DrawText( 18, 148, CLGraphicStyleOptions_Default,
					"T. AIR  :" );
				sprintf( text, "%-4.1f", Heater_AirTemperature );
				CLGraphics::DrawText( 90, 148, CLGraphicStyleOptions_Default,
				text );
			}
			else
			{
				CLGraphics::DrawText( 18, 148, CLGraphicStyleOptions_Default,
					"T. AIR  :" );
				sprintf( text, "%-4.1f", Heater_AirTemperature );
				CLGraphics::DrawText( 90, 148, CLGraphicStyleOptions_Default,
				text );	
				
				CLGraphics::DrawText( 180, 148, CLGraphicStyleOptions_Default,
					"T. WATER:" );
				sprintf( text, "%-4.1f", Heater_WaterTemperature );
				CLGraphics::DrawText( 252, 148, CLGraphicStyleOptions_Default,
				text );	
			}
			break;

		case 2: // Page 2 - Accessory Clima 2/2

			// PreHeater Box
			// --------------
			Accessory_GetStatusText( text, PreHeater_Status );
			CLGraphics::DrawText( 90, 48, CLGraphicStyleOptions_HAlign_Left,
				text, 27 );

			Accessory_GetCommandText( text, PreHeater_Status );
			CLGraphics::DrawText( 90, 64, CLGraphicStyleOptions_HAlign_Left,
				text, 4 );

			CLKTS::LevelLink_GetText( text, PreHeater_LinkLevel );
			CLGraphics::DrawText( 242, 64, CLGraphicStyleOptions_Default,
				text );
			break;

		case 3: // Page 3 - Bypass

			Bypass_GetConfigText( text, gRDEeprom.Config_Bypass, true );
			CLGraphics::DrawText( 154, 48, CLGraphicStyleOptions_HAlign_Left,
				text, 19 );

			Bypass_GetStatusText( text, gKTSData.Status_Unit );
			CLGraphics::DrawText( 154, 64, CLGraphicStyleOptions_HAlign_Left,
				text, 19 );

			sprintf( text, "%-4.1f", gKTSData.Measure_Temp[ I_PROBE_FRESH ] );
			CLGraphics::DrawText( 154, 80, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", gKTSData.Measure_Temp[ I_PROBE_RETURN ] );
			CLGraphics::DrawText( 154, 96, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", gKTSData.Measure_Temp[ I_PROBE_SUPPLY ] );
			CLGraphics::DrawText( 154, 112, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", gKTSData.Measure_Temp[ I_PROBE_EXHAUST ] );
			CLGraphics::DrawText( 154, 128, CLGraphicStyleOptions_Default,
				text );

			sprintf( text, "%-4.1f", ((float) gRDEeprom.Bypass_minTempExt) / 10.0 );
			CLGraphics::DrawText( 154, 144, CLGraphicStyleOptions_Default,
				text );
			break;

		case 4: // Page 4 - CAP/CAF Data

			if(Accessory_IsPresent( ACC_EEP_PCAP ))
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_CONNECTED ), 185, Y_ROW1 );

				sprintf( text, "%2d/10", Level_Link_Sensor );
				gLCD.print( text, 185, Y_ROW2 );
			}
			else
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_INTERNAL ), 185, Y_ROW1 );
				gLCD.print( "--/--", 185, Y_ROW2 );
			}

			// RIGA 3
			switch (VentilationControl_Get())
			{
				case CLVentilationControl_CAP:
					sprintf( text, "%d %s",
						SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ),
						CLFixedText_PA );
					break;

				case CLVentilationControl_FSC:
					sprintf( text, "%d %%",
						SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ) );
					break;

				case CLVentilationControl_CAF:
					sprintf( text, "%d %s",
						CLCommon::PercentageToM3H( (float) SpeedMode_Speed_GetValue( VentilationControl_Get(), SpeedMode_Speed_GetIndex() ) / 100.0 ),
						CLFixedText_M3_H );
					break;
				
				default:
					*text	= '\0';
					break;
			}
			CLGraphics::DrawText( 185, Y_ROW3, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 8 );

			// RIGA 4
			if (Function_IsEnabled( ENAB_CAP ))
			{
				/*gLCD.print( "    Pa",185, Y_ROW4);
				if(Measures_Pressure < 10)
					gLCD.printNumI(Measures_Pressure,201, Y_ROW4);
				else if(Measures_Pressure < 100)
					gLCD.printNumI(Measures_Pressure,192, Y_ROW4);
				else
					gLCD.printNumI(Measures_Pressure,185, Y_ROW4);*/
                memset ( text, 0, sizeof(text));
                sprintf( text, "%4d Pa", Measures_Pressure );
                gLCD.print( text, 185, Y_ROW4 );
			}
			else
                gLCD.print( "- Pa",185, Y_ROW4);

            if (Function_IsEnabled( ENAB_CAP ))
			{
                sprintf( text, "- %s", CLFixedText_M3_H );
			CLGraphics::DrawText( 185, Y_ROW5, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );
            }
            else
            {
                sprintf( text, "%d %s",
                    MeasureAirflow, CLFixedText_M3_H );
                CLGraphics::DrawText( 185, Y_ROW5, CLGraphicStyleOptions_Font_Small,
                    RGBColor_Black, RGBColor_White,
                    text, 12 );
            }

			break;
        
        case 5: // Page 5 - CAPS Data

			if(Accessory_IsPresent( ACC_EEP_FLW1 ))
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_CONNECTED ), 185, Y_ROW1 );

				sprintf( text, "%2d/10", CAPS_LinkLevel );
				gLCD.print( text, 185, Y_ROW2 );
			}
			else
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_INTERNAL ), 185, Y_ROW1 );
				gLCD.print( "--/--", 185, Y_ROW2 );
			}

			// RIGA 3
            if(Accessory_IsPresent( ACC_EEP_FLW1 ))
            {
                sprintf( text, "%d %s", SpeedMode_Speed_GetValue( CLVentilationControl_CAP, 3 ), CLFixedText_PA );
            }
            else
            {
                sprintf( text, "- %s",  CLFixedText_PA );
            }
            
			CLGraphics::DrawText( 185, Y_ROW3, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 8 );

			// RIGA 4
            if(Accessory_IsPresent( ACC_EEP_FLW1 ))
            {
				/*gLCD.print( "    Pa",185, Y_ROW4);
				if(Measures_Pressure_CAPS < 10)
					gLCD.printNumI(Measures_Pressure_CAPS,201, Y_ROW4);
				else if(Measures_Pressure < 100)
					gLCD.printNumI(Measures_Pressure_CAPS,192, Y_ROW4);
				else
					gLCD.printNumI(Measures_Pressure_CAPS,175, Y_ROW4);*/
                memset ( text, 0, sizeof(text));
                sprintf( text, "%4d Pa", Measures_Pressure_CAPS );
                gLCD.print( text, 185, Y_ROW4 );
            }
            else
            {
                memset ( text, 0, sizeof(text));
                strcat( text, "- Pa");
                gLCD.print( text, 185, Y_ROW4 );
            }

			sprintf( text, "- %s", CLFixedText_M3_H );
			CLGraphics::DrawText( 185, Y_ROW5, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );

			break;
        
        case 6: // Page 6 - CAPR Data

			if(Accessory_IsPresent( ACC_EEP_FLW2 ))
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_CONNECTED ), 185, Y_ROW1 );

				sprintf( text, "%2d/10", CAPR_LinkLevel );
				gLCD.print( text, 185, Y_ROW2 );
			}
			else
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_INTERNAL ), 185, Y_ROW1 );
				gLCD.print( "--/--", 185, Y_ROW2 );
			}

			// RIGA 3
            if(Accessory_IsPresent( ACC_EEP_FLW2 ))
            {
                sprintf( text, "%d %s", SpeedMode_Speed_GetValue( CLVentilationControl_CAP, 1 ), CLFixedText_PA );
            }
            else
            {
                sprintf( text, "- %s",  CLFixedText_PA );
            }
			
			CLGraphics::DrawText( 185, Y_ROW3, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 8 );

			// RIGA 4
			
            if(Accessory_IsPresent( ACC_EEP_FLW2 ))
            {
				/*gLCD.print( "    Pa",185, Y_ROW4);
				if(Measures_Pressure_CAPS < 10)
					gLCD.printNumI(Measures_Pressure_CAPR,201, Y_ROW4);
				else if(Measures_Pressure < 100)
					gLCD.printNumI(Measures_Pressure_CAPR,192, Y_ROW4);
				else
					gLCD.printNumI(Measures_Pressure_CAPR,175, Y_ROW4);*/
                memset ( text, 0, sizeof(text));
                sprintf( text, "%4d Pa", Measures_Pressure_CAPR );
                gLCD.print( text, 185, Y_ROW4 );

            }
            else
            {
                memset ( text, 0, sizeof(text));
                strcat( text, "- Pa");
                gLCD.print( text, 185, Y_ROW4 );
            }
			
            sprintf( text, "- %s", CLFixedText_M3_H );
			CLGraphics::DrawText( 185, Y_ROW5, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 12 );

			break;
            
        case 7: // Page 7 - AIR SENSOR1
            
            if(Accessory_IsPresent( ACC_EEP_P1CO2 )) // AIR SENSOR1 CONNECTED
                {
                    gLCD.print( CLLocalitation::GetText( CLTextId_CONNECT ), 190, 38 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%2d", CO2_1_LinkLevel );
                    strcat (text , "/10");
                    gLCD.print( text, 190, 54 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%4d ppm", Measure_CO2_1 );
                    gLCD.print( text, 190, 70 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%4d ppm", Measure_VOC_1 );
                    gLCD.print( text, 190, 86 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%2d %", Measure_RH_1 );
                    gLCD.print( text, 190, 102 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%-1d", CO2_1_Accuracy );
                    gLCD.print( text, 190, 118 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%3d", Measure_IAQ_1 );
                    gLCD.print( text, 190, 134 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%-1d", IAQ_1_Accuracy );
                    gLCD.print( text, 190, 150 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%c.%c", (Firm_Ver_CO2_1 >> 4) + 48, (Firm_Ver_CO2_1 & 0xF) + 48);
                    gLCD.print( text, 190, 166 );
                }
            else
                {
                    gLCD.print( CLLocalitation::GetText( CLTextId_NOT_CONNECTED ), 190, 38 );
                    gLCD.print( "--/--", 190, 54 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- ppm");
                    gLCD.print( text, 190, 70 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- ppm");
                    gLCD.print( text, 190, 86 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- %");;
                    gLCD.print( text, 190, 102 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 118 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 134 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 150 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 166 );
                }
            break;
        
        case 8: // Page 8 - AIR SENSOR2
            
            if(Accessory_IsPresent( ACC_EEP_P2CO2 )) // AIR SENSOR1 CONNECTED
                {
                    gLCD.print( CLLocalitation::GetText( CLTextId_CONNECT ), 190, 38 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%2d", CO2_2_LinkLevel );
                    strcat (text , "/10");
                    gLCD.print( text, 190, 54 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%4d ppm", Measure_CO2_2 );
                    gLCD.print( text, 190, 70 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- ppm");
                    gLCD.print( text, 190, 86 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%2d %", Measure_RH_2 );
                    gLCD.print( text, 190, 102 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%-1d", CO2_2_Accuracy );
                    gLCD.print( text, 190, 118 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%3d", Measure_IAQ_2 );
                    gLCD.print( text, 190, 134 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%-1d", IAQ_2_Accuracy );
                    gLCD.print( text, 190, 150 );
                    
                    memset ( text, 0, sizeof(text));
                    sprintf( text, "%c.%c", (Firm_Ver_CO2_2 >> 4) + 48, (Firm_Ver_CO2_2 & 0xF) + 48);
                    gLCD.print( text, 190, 166 );
                }
            else
                {
                    gLCD.print( CLLocalitation::GetText( CLTextId_NOT_CONNECTED ), 190, 38 );
                    gLCD.print( "--/--", 190, 54 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- ppm");
                    gLCD.print( text, 190, 70 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- ppm");
                    gLCD.print( text, 190, 86 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "- %");;
                    gLCD.print( text, 190, 102 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 118 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 134 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 150 );
                    
                    memset ( text, 0, sizeof(text));
                    strcat( text, "-");
                    gLCD.print( text, 190, 166 );
                }
            break;
            
		case 9: //
		{
			char	text[ 40 ];

			sprintf( text, "[%c] BOOST MANUAL [%c] BOOST VOC    ",
				(KTSStatusUnit_UnitState_IsRUN_BOOST( gKTSData.Status_Unit ) ? 'X' : ' '),
				(KTSStatusUnit_IsVOCMax( gKTSData.Status_Unit ) ? 'X' : ' ') );
			CLGraphics::DrawText( 18, 48, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );

			sprintf( text, "[%c] BOOST CO2    [%c] BOOST RH     ",
				(KTSStatusUnit_IsCO2Max( gKTSData.Status_Unit ) ? 'X' : ' '),
				(KTSStatusUnit_IsRHMax( gKTSData.Status_Unit ) ? 'X' : ' ') );
			CLGraphics::DrawText( 18, 62, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );

			sprintf( text, "[%c] UNBALANCE    [%c] DEFROST",
				(KTSStatusUnit_UnitState_IsRUN_IMBALANCE( gKTSData.Status_Unit ) ? 'X' : ' '),
				(KTSStatusUnit_UnitState_IsRUN_DEFROST( gKTSData.Status_Unit ) ? 'X' : ' ') );
			CLGraphics::DrawText( 18, 76, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );
			
			sprintf( text, "[%c] IDLE         [%c] STANDBY",
				(KTSStatusUnit_UnitState_IsIDLE( gKTSData.Status_Unit ) ? 'X' : ' '),
				(KTSStatusUnit_UnitState_IsSTANDBY( gKTSData.Status_Unit ) ? 'X' : ' ') );
			CLGraphics::DrawText( 18, 90, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );

			sprintf( text, "[%c] POST VENT.   [%c] EXT FAN CTRL",
				(KTSStatusUnit_UnitState_IsRUN_POST_VENT( gKTSData.Status_Unit ) ? 'X' : ' '),
				(KTSStatusUnit_CmdFanInput( gKTSData.Status_Unit ) ? 'X' : ' ') );
			CLGraphics::DrawText( 18, 104, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );

			sprintf( text, "BPD STATUS: %s",
				(Bypass_GetStatus() == CLBypassStatus_Open ? CLLocalitation::GetText( CLTextId_OPEN ) : Bypass_GetStatus() == CLBypassStatus_Close ? CLLocalitation::GetText( CLTextId_CLOSED ) : CLLocalitation::GetText( CLTextId_CHANGING ) ) );
			CLGraphics::DrawText( 18, 132, CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, 36 );
			break;
		}
	}
}
// -----------------------------------------------------------------------------
// CLReportDebugDataAdminForm [class]
// =============================================================================

