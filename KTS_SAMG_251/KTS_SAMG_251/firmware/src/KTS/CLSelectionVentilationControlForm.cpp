#include "CLSelectionVentilationControlForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLVentilationControl.h"
#include "CLFunction.h"
#include "CLCAPCalibrationProcedureForm.h"

#define CLSelectionVentilationControlForm_CAFModeButtonRectangle		12, 60, 101, 94
#define CLSelectionVentilationControlForm_FSCModeButtonRectangle		116, 60, 205, 94
#define CLSelectionVentilationControlForm_CAPModeButtonRectangle		219, 60, 308, 94
#define CLSelectionVentilationControlForm_CAPCalibrationButtonRectangle	12, 115, 309, 172

CLFormResult CLSelectionVentilationControlForm_Open( unsigned short options )
{
	CLSelectionVentilationControlForm	form;

	return form.Open( options );
}

// =============================================================================
// CLSelectionSpeedMotorModeForm [class]
// -----------------------------------------------------------------------------
CLSelectionVentilationControlForm::CLSelectionVentilationControlForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_CAFModeButtonRectangle.Set( CLSelectionVentilationControlForm_CAFModeButtonRectangle );
	m_FSCModeButtonRectangle.Set( CLSelectionVentilationControlForm_FSCModeButtonRectangle );
	m_CAPModeButtonRectangle.Set( CLSelectionVentilationControlForm_CAPModeButtonRectangle );
	m_CAPCalibrationButtonRectangle.Set( CLSelectionVentilationControlForm_CAPCalibrationButtonRectangle );
}

CLFormResult CLSelectionVentilationControlForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_Options	= options;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetVentilationControl( VentilationControl_Get() );
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
				bool	doSave	= false;

				CLLCDCommon::WaitButton( m_OkButtonRectangle );

#if CUSTOMERID == CUSTOMERID_FA
				// Per FA avviamo la calibrazione
				if (m_VentilationControl == CLVentilationControl_CAP &&
					!CLKTS::Pressure_IsCalibrated())
				{
					if (CLCAPCalibrationProcedureForm_Open( CLFormOption_HideButton_Home ) == CLFormResult_Ok)
						doSave	= true;
				}
				else
					doSave	= true;
#else
				doSave	= true;
#endif
				if (doSave && Save())
				{
					if (CLFormOption_CanExitAfterWrite( m_Options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( m_Options );
						break;
					}
				}
				RenderPage();
			}
			else
			// CAF Button
			if (VentilationControl_CanSelect( CLVentilationControl_CAF ) && m_CAFModeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_CAFModeButtonRectangle );
				SetVentilationControl( CLVentilationControl_CAF );
			}
			else
			// FSC Button
			if (VentilationControl_CanSelect( CLVentilationControl_FSC ) && m_FSCModeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_FSCModeButtonRectangle );
				SetVentilationControl( CLVentilationControl_FSC );
			}
			else
			// CAP Button
			if (VentilationControl_CanSelect( CLVentilationControl_CAP ) && m_CAPModeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_CAPModeButtonRectangle );
				SetVentilationControl( CLVentilationControl_CAP );
			}
			else
			// CAP Calibration Button
			if (VentilationControl_CanSelect( CLVentilationControl_CAP ) && ( m_VentilationControl == CLVentilationControl_CAP) && ( VentilationControl_Get() == CLVentilationControl_CAP ) && m_CAPCalibrationButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_CAPCalibrationButtonRectangle );
				formResult	= CLCAPCalibrationProcedureForm_Open( CLFormOption_ShowWriteMesssages_All | (m_Options & CLFormOption_AdminMode) );
				if (formResult == CLFormResult_Back ||
					formResult == CLFormResult_Home)
					break;

				RenderPage();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLSelectionVentilationControlForm::Save()
{
#ifdef FRANCETX_ENABLED
	if (m_VentilationControl != CLVentilationControl_CAF &&
		SpeedMode_GetType() == CLSpeedModeType_FranceTx)
	{
		// Visualizza il messaggio di scrittura in corso
		if (CLFormOption_CanShowWriteMessage_Starting( m_Options ))
			CLLCDCommon::WriteDataPanel_DisplayWriting();

		if (!CLKTS::WriteStepless( m_VentilationControl, 0 ))
		{
			// Visualizza il messaggio di errore
			if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayError();

			return false;
		}

		// Visualizza il messaggio di ok
		if (CLFormOption_CanShowWriteMessage_Success( m_Options ))
			CLLCDCommon::WriteDataPanel_DisplaySuccess();

		return true;
	}
#endif

	switch (SpeedMode_GetType())
	{
		case CLSpeedModeType_Stepless:

			// Visualizza il messaggio di scrittura in corso
			if (CLFormOption_CanShowWriteMessage_Starting( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayWriting();

			if (!CLKTS::WriteStepless( m_VentilationControl, 0 ))
			{
				// Visualizza il messaggio di errore
				if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
					CLLCDCommon::WriteDataPanel_DisplayError();

				return false;
			}

			// Visualizza il messaggio di ok
			if (CLFormOption_CanShowWriteMessage_Success( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplaySuccess();

			return true;

		case CLSpeedModeType_ThreeSpeed:
		{
			unsigned short	speedMotors[ 3 ];

			// Visualizza il messaggio di scrittura in corso
			if (CLFormOption_CanShowWriteMessage_Starting( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayWriting();

			CLKTS::Write_GetCurrentStepMotors( m_VentilationControl, speedMotors, 0, 2 );
			if (!CLKTS::WriteThreeSpeed( m_VentilationControl, speedMotors, 0 ))
			{
				// Visualizza il messaggio di errore
				if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
					CLLCDCommon::WriteDataPanel_DisplayError();

				return false;
			}

			// Visualizza il messaggio di ok
			if (CLFormOption_CanShowWriteMessage_Success( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplaySuccess();

			return true;
		}
	}

	return false;
}

bool CLSelectionVentilationControlForm::Save_Old()
{
	ComQueue_Status			writeEeprom_Status;
	CLVentilationControl	saveVentilationControl;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( m_Options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati prima del salvataggio
	saveVentilationControl	= VentilationControl_Get();

	//Imposta i nuovi dati
	Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) saveVentilationControl, false );
	Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) m_VentilationControl, true );

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
		sizeof(gRDEeprom.Enab_Fuction),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) m_VentilationControl, false );
		Function_SetEnabled( (_BIT_NUMBER_ENAB_FUCTIONS) saveVentilationControl, true );

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( m_Options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLSelectionVentilationControlForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_VENTILATION_CONTROL ),
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

	RenderSelectionButtons();
}

void CLSelectionVentilationControlForm::RenderSelectionButtons()
{
	CLLCDCommon::DrawGenericButton( m_CAFModeButtonRectangle,
		(!VentilationControl_CanSelect( CLVentilationControl_CAF ) ? GenericButtonStyle_Disabled_BigFont : (m_VentilationControl == CLVentilationControl_CAF ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont)),
		CLFixedText_CAF, VentilationControl_Get() == CLVentilationControl_CAF );
	CLLCDCommon::DrawGenericButton( m_FSCModeButtonRectangle,
		(!VentilationControl_CanSelect( CLVentilationControl_FSC ) ? GenericButtonStyle_Disabled_BigFont : (m_VentilationControl == CLVentilationControl_FSC ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont)),
		CLFixedText_FSC, VentilationControl_Get() == CLVentilationControl_FSC );
	CLLCDCommon::DrawGenericButton( m_CAPModeButtonRectangle,
		(!VentilationControl_CanSelect( CLVentilationControl_CAP ) ? GenericButtonStyle_Disabled_BigFont : (m_VentilationControl == CLVentilationControl_CAP ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont)),
		CLFixedText_CAP, VentilationControl_Get() == CLVentilationControl_CAP );
	CLLCDCommon::DrawGenericButton( m_CAPCalibrationButtonRectangle,
		(VentilationControl_Get() != CLVentilationControl_CAP || m_VentilationControl != CLVentilationControl_CAP ? GenericButtonStyle_Disabled_BigFont_Multiline : GenericButtonStyle_Normal_BigFont_Multiline),
		CLLocalitation::GetText( CLTextId_CAP_CALIBRATION_PROCEDURE ) );
}

void CLSelectionVentilationControlForm::SetVentilationControl( CLVentilationControl value )
{
	m_VentilationControl	= value;

	if (GetState() == CLState_Running)
		RenderSelectionButtons();
}
// -----------------------------------------------------------------------------
// CLSelectionSpeedMotorModeForm [class]
// =============================================================================


