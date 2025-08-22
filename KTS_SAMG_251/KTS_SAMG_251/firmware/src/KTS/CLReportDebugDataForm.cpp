//-------------------------------------------------------------
//-------------------------------------------------------------
//------------------ ReportDates --------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------

#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLReportDebugDataForm.h"
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
//--------------------------------------------------------------

const unsigned long ReportDataDebug_RequestMilliseconds = 2500;

CLFormResult CLReportDebugDataForm_Open( unsigned short options )
{
	CLReportDebugDataForm	form;

	return form.Open( options );
}

void ResponseCallback( byte* rxBuffer, void* userData )
{
	CLReportDebugDataForm*	reportDebugDataForm	= (CLReportDebugDataForm*) userData;

	if (reportDebugDataForm == NULL)
		return;

	reportDebugDataForm->Level_Link_Sensor =  rxBuffer[IRSD_LEV_LINK_CAP];

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

	reportDebugDataForm->ReceivedData	= 1;
}

// =============================================================================
// CLReportDebugDataForm [class]
// -----------------------------------------------------------------------------
CLReportDebugDataForm::CLReportDebugDataForm()
	: m_Page( 5 )
{
	Level_Link_Sensor		= 0;
	Status_FanR				= 0;
	Status_FanF				= 0;

	PreHeater_LinkLevel		= 0;
	Heater_LevelLink		= 0;
	Cooler_LevelLink		= 0;
	PreHeater_Status		= 0;
	Heater_Status			= 0;
	Cooler_Status			= 0;
	Heater_WaterTemperature	= 0;
	Heater_AirTemperature	= 0;
	Cooler_WaterTemperature	= 0;

	m_FirstRequestDebugData	= true;

	m_HomeButtonRectangle.Set( ::Form_HomeButtonRectangle );
	m_PreviousButtonRectangle.Set( ViewForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( ViewForm_NextButtonRectangle );
	m_BackButtonRectangle.Set( 0, 190, 70, 229 );
}

CLFormResult CLReportDebugDataForm::Open( unsigned short options )
{
	int				touchX, touchY;
	unsigned long	previousTimerRefresh;
	ComQueue_Status	dataDebugRequestStatus;
	int				dataDebugRequestQueueIndex	= -1;
	CLFormResult	formResult;

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
		
		// Se esiste una richiesta pendente, controlla se Ã¨ ancora in esecuzione, altrimenti refresh dei dati
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
				dataDebugRequestQueueIndex	= ComQueue_AddDataDebugRequest( &dataDebugRequestStatus, ResponseCallback );
				if (dataDebugRequestQueueIndex != -1)
					gComQueueRequests[ dataDebugRequestQueueIndex ].UserData	= this;
			}

			previousTimerRefresh	= millis();
		}

		if (Touched())
		{
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

void CLReportDebugDataForm::RenderPage()
{
	char*	pageTitle	= NULL;

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
		case 0: // Page 1 - Accessory Clima 1

			// Imposta il titolo della pagina
			pageTitle	= (char*) "ACC. CLIMA";

			// Draw Cooler Box
			CLGraphics::DrawBox( CLRectangle( 6, 40, 313, 100 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0x4297D4 );

			gLCD.print( "COOLER  :", 18, 48 );
			gLCD.print( "COMMAND :", 18, 64 );
			gLCD.print( "LINK LEVEL :", 146, 64 );
			gLCD.print( "T. WATER:", 18, 80 );

			// Draw Heater Box
			CLGraphics::DrawBox( CLRectangle( 6, 108, 313, 168 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0xFF0000 );

			gLCD.print( "HEATER  :", 18, 116 );
			gLCD.print( "COMMAND :", 18, 132 );
			gLCD.print( "LINK LEVEL :", 146, 132 );
			gLCD.print( "T. WATER:", 18, 148 );
			break;

		case 1: // Page 2 - Accessory Clima 2

			// Imposta il titolo della pagina
			pageTitle	= (char*) "ACC. CLIMA";

			// Draw PreHeater Box
			CLGraphics::DrawBox( CLRectangle( 6, 40, 313, 100 ), CLGraphicStyleOptions_BorderRound_Yes,
				RGBColor_Black,
				2, 0xE6B800 );

			gLCD.print( "PHEATER :", 18, 48 );
			gLCD.print( "COMMAND :", 18, 64 );
			gLCD.print( "LINK LEVEL :", 146, 64 );
			break;

		case 2: // Page 3 - Bypass

			// Imposta il titolo della pagina
			pageTitle	= (char*) CLLocalitation::GetText( CLTextId_BYPASS );

			gLCD.print( "CONFIG         :", 18, 48 );
			gLCD.print( "STATUS         :", 18, 64 );
			gLCD.print( "TFRESH         :", 18, 80 );
			gLCD.print( "TRETURN        :", 18, 96 );
			gLCD.print( "MIN TEMP. EXT. :", 18, 112 );
			break;

		case 3: // Page 4 - CAP/CAF DATA
			// Imposta il titolo della pagina
			pageTitle	= (char*) "CAP/CAF DATA";

			gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			if (Accessory_IsPresent( ACC_EEP_MBUS ) && !m_AdminMode)
			{
				CLGraphics::DrawText( CLRectangle( 15, Y_ROW1, 305, Y_ROW5 ), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle,
					RGBColor_Black, RGBColor_White,
					CLLocalitation::GetText( CLTextId_DATA_AVAILABLE_FROM_MODBUS ) );
			}
			else
			{
				gLCD.print( CLLocalitation::GetText( CLTextId_PRESSURE_SENSOR ), 15,  Y_ROW1 );
				gLCD.print( CLLocalitation::GetText( CLTextId_LEVEL_LINK_SENSOR ), 15,  Y_ROW2 );
			
				if (VentilationControl_Get() == CLVentilationControl_CAP)
					gLCD.print( CLLocalitation::GetText( CLTextId_SETPOINT_PRESSURE ), 15,  Y_ROW3 );
				else
					gLCD.print( "SETPOINT AIRFLOW..:", 15,  Y_ROW3 );
			}
			break;

		case 4: // Page 5 - UNIT STATUS
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

void CLReportDebugDataForm::RenderData()
{
	int		setP;
	char	text[ 40 ];

    gLCD.setRGBColor( RGBColor_White );
    gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );

	switch (m_Page.GetValue())
	{
		case 0: // Page 1 - Accessory Clima 1/2

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

			sprintf( text, "%-4.1f", Cooler_WaterTemperature );
			CLGraphics::DrawText( 90, 80, CLGraphicStyleOptions_Default,
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
			}
			else
			{
				CLGraphics::DrawText( 18, 148, CLGraphicStyleOptions_Default,
					"T. WATER:" );
				sprintf( text, "%-4.1f:", Heater_WaterTemperature );
			}
			CLGraphics::DrawText( 90, 148, CLGraphicStyleOptions_Default,
				text );
			break;

		case 1: // Page 2 - Accessory Clima 2/2

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

		case 2: // Page 3 - Bypass

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

			sprintf( text, "%-4.1f", ((float) gRDEeprom.Bypass_minTempExt) / 10.0 );
			CLGraphics::DrawText( 154, 112, CLGraphicStyleOptions_Default,
				text );
			break;

		case 3: // Page 4 - CAP/CAF Data

			if (!Accessory_IsPresent( ACC_EEP_MBUS ) || m_AdminMode)
			{
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
			}

			break;

		case 4: // Page 5 - UNIT STATUS
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
// CLReportDebugDataForm [class]
// =============================================================================

