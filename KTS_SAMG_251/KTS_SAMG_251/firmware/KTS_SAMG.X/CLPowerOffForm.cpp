#include "CLPowerOffForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLFunction.h"
#include "CLWeeklyMainForm.h"
#include "CLWeekly.h"
#include "CLAlarm.h"
#include "CLCommunication_Driver.h"

#define	CLPowerOffForm_PowerOnButton		7, 38, 68, 104
#define	CLPowerOffForm_DateTimePoint		238, 200
#define	CLPowerOffForm_WeeklyIconPoint		145, 38
#define	CLPowerOffForm_TemperatureIconPoint	120, 38

extern bool Debounce;
bool Clean_Event_Power_Off = false;

CLFormResult CLPowerOffForm_Open()
{
	CLPowerOffForm	form;

	return form.Open();
}

// =============================================================================
// CLPowerOffForm [class]
// -----------------------------------------------------------------------------
CLPowerOffForm::CLPowerOffForm()
{
	m_PowerOnButtonRectangle.Set( CLPowerOffForm_PowerOnButton );
}

CLFormResult CLPowerOffForm::Open()
{
	int				touchX, touchY;
	CLFormResult	formResult;
	unsigned long	displayDatePreviousMilliseconds = millis();

	//analogWrite( pBACKLIGHT, (HIGH_BRIGHTESS - 10) );
    TC0_CH1_CompareASet (HIGH_BRIGHTESS + 600 );

	RenderPage();

	while (true)
	{
		CLKTS::Pir_Process();
		
		// Se l'unità è in fire alarm o richiede un riarmo, allora esce
		if (IsFireAlarm() || gRDEeprom.manual_Reset)
		{
			formResult				= CLFormResult_None;
			gKTSGlobal.RunningMode	= CLKTSRunningMode_FireAlarm;
			break;
		}

		// Se l'unità è in power on, allora esce
		if (gRDEeprom.Set_Power_ON == CLKTSPowerMode_On)
		{
			formResult				= CLFormResult_None;
			gKTSGlobal.RunningMode	= CLKTSRunningMode_Running;
			break;
		}

		// Nel caso in cui si è connessi in RFM e non si riceve una risposta da più di un minuto
		// significa connessione persa, ritorna al form di connessione
		if (CLKTS::IsMissingRFMSignal())
		{
			gKTSGlobal.RunningMode	= CLKTSRunningMode_Initializing;
			formResult				= CLFormResult_Ok;
			break;
		}

		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		if(gRDEeprom.Type_func != CLKTSType_BASIC)
		{
			if (millis() - displayDatePreviousMilliseconds >= 1000 ||
				millis() < displayDatePreviousMilliseconds)
			{
				CLLCDCommon::DrawDateTimeBox( CLPowerOffForm_DateTimePoint );
				displayDatePreviousMilliseconds	= millis();
			}
		}
		
		CLKTS::Pir_Process();
        
        if ( (gKTSData.Status_Unit & 0x4000 ) == 0x4000 ) // CleanEvent activated
        {
            Clean_Event_Power_Off = true;
            CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_On); // turn Device ON
        }
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// PowerOn Button
			if (m_PowerOnButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PowerOnButtonRectangle );

				if (CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_On ))
				{
					formResult	= CLFormResult_Ok;
					CLKTS::Pir_Strategy_Counter = millis();
                    Debounce = false;
					break;
				}
				RenderPage();
			}
			else
			// WeeklyProgrammmer Button
			//if (Function_IsEnabled( ENAB_WEEKLY ) && m_WeeklyProgrammerButtonRectangle.Contains( touchX, touchY ))
			//{
			//	CLLCDCommon::WaitButton( m_WeeklyProgrammerButtonRectangle );

			//	formResult	= CLWeeklyMainForm_Open( CLFormOption_GoBackAfterWrite | CLFormOption_ShowWriteMesssages_All );
			//	if (formResult == CLFormResult_Home)
			//		break;

			//	RenderPage();
			//}
			//else
				WaitForTouchRelease();
		}

		if (Function_IsEnabled( ENAB_WEEKLY ))
		{
			CLLCDCommon::DrawWeeklyIcon( CLPowerOffForm_WeeklyIconPoint );
			if (Weekly_Status_GetTemperatureIndex( gKTSData.Status_Weekly ) == 0)
				CLLCDCommon::DrawSunIcon( CLPowerOffForm_TemperatureIconPoint, RGBColor_Black, RGBColor_SunIcon_Pen );
			else
				CLLCDCommon::DrawMoonIcon( CLPowerOffForm_TemperatureIconPoint, RGBColor_Black, RGBColor_MoonIcon_Pen );
		}
		//else
		//{
		//	CLPoint	point( CLPowerOffForm_WeeklyIconPoint );
		//	gLCD.setColor( 0, 0, 0 );
		//	gLCD.fillRect( point.GetX(), point.GetY(), point.GetX() + 20, point.GetY() + 20 );
		//	gLCD.setColor(255,255,255);
		//}

    }

	return formResult;
}

void CLPowerOffForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Display PowerOn Button
	CLLCDCommon::DrawOnOffIcon( m_PowerOnButtonRectangle.GetX1(), m_PowerOnButtonRectangle.GetY1(),
		PowerOnOff_Icon_Color_Off );

	//if (Function_IsEnabled( ENAB_WEEKLY ))
	//{
	//	CLLCDCommon::DrawGenericButton( m_WeeklyProgrammerButtonRectangle,
	//		GenericButtonStyle_Normal_SmallFont,
	//		CLLocalitation::GetText( CLTextId_WEEKLY_PROGRAMMER ) );
	//}
}
// -----------------------------------------------------------------------------
// CLPowerOffForm [class]
// =============================================================================

