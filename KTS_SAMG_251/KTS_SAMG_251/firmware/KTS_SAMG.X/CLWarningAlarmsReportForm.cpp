#include "CLWarningAlarmsReportForm.h"
#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLLocalitation.h"
#include "CLAccessory.h"
#include "CLFunction.h"

#define CLWarningAlarmsReportForm_ResetButtonRectangle	0, 190, 90, 229
#define CLWarningAlarmsReportForm_FilterTextPoint		10, 35

CLFormResult CLWarningAlarmsReportForm_Open( unsigned short options )
{
	CLWarningAlarmsReportForm	form;

	return form.Open( options );
}

// =============================================================================
// CLWarningAlarmsReportForm [class]
// -----------------------------------------------------------------------------
CLWarningAlarmsReportForm::CLWarningAlarmsReportForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_ResetButtonRectangle.Set( CLWarningAlarmsReportForm_ResetButtonRectangle );
}

CLFormResult CLWarningAlarmsReportForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_FilterInAlarm	= gKTSGlobal.FilterInAlarm;

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
			if (m_FilterInAlarm && m_ResetButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ResetButtonRectangle );

				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
				break;
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLWarningAlarmsReportForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	long			saveTime_lastCloggedFilers;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveTime_lastCloggedFilers			= gRDEeprom.time_lastCloggedFilers;

	// Imposta i nuovi dati
	if (Function_IsEnabled( ENAB_CTRL_FILTER ) && Function_IsEnabled( ENAB_DPP ))
		gRDEeprom.time_lastCloggedFilers	= 0;
	else
		gRDEeprom.time_lastCloggedFilers	= gRDEeprom.hour_runnig;

	// Accoda la richiestga di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, time_lastCloggedFilers ),
		sizeof(gRDEeprom.time_lastCloggedFilers),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non Ã¨ andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.time_lastCloggedFilers	= saveTime_lastCloggedFilers;

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

void CLWarningAlarmsReportForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Data Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_WARNINGS_REPORT ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	if (m_FilterInAlarm)
    {
		CLGraphics::DrawText( CLWarningAlarmsReportForm_FilterTextPoint, CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			CLLocalitation::GetText( CLTextId_RECOMMEND_TO_CHANGE_FILTERS ) );

		// Draw Reset Button
		CLGraphics::DrawBoxWithText( m_ResetButtonRectangle, GenericButtonStyle_Normal_BigFont,
			CLLocalitation::GetText( CLTextId_RESET ) );
    }
}
// -----------------------------------------------------------------------------
// CLWarningAlarmsReportForm [class]
// =============================================================================


