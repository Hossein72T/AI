#include "CLProbesSettingsForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"
#include "CLAccessory.h"

#define	CLProbesSettingsForm_NRAnalogProbesTextPoint		16, 38
#define	CLProbesSettingsForm_NRAnalogProbes2ButtonRectangle	181, 28, 210, 57
#define	CLProbesSettingsForm_NRAnalogProbes3ButtonRectangle	228, 28, 257, 57
#define	CLProbesSettingsForm_NRAnalogProbes4ButtonRectangle	275, 28, 304, 57

CLFormResult CLProbesSettingsForm_Open( unsigned short options )
{
	CLProbesSettingsForm	form;

	return form.Open( options );
}

// =============================================================================
// CLProbesSettingsForm [class]
// -----------------------------------------------------------------------------
CLProbesSettingsForm::CLProbesSettingsForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_NRAnalogProbes2ButtonRectangle.Set( CLProbesSettingsForm_NRAnalogProbes2ButtonRectangle );
	m_NRAnalogProbes3ButtonRectangle.Set( CLProbesSettingsForm_NRAnalogProbes3ButtonRectangle );
	m_NRAnalogProbes4ButtonRectangle.Set( CLProbesSettingsForm_NRAnalogProbes4ButtonRectangle );
}

CLFormResult CLProbesSettingsForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetProbeCount( gRDEeprom.numNTC );
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
			// NRAnalogProbes2 Button
			if (m_NRAnalogProbes2ButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NRAnalogProbes2ButtonRectangle );

				SetProbeCount( 2 );
			}
			else
			// NRAnalogProbes3 Button
			if (m_NRAnalogProbes3ButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NRAnalogProbes3ButtonRectangle );

				SetProbeCount( 3 );
			}
			else
			// NRAnalogProbes4 Button
			if (m_NRAnalogProbes4ButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NRAnalogProbes4ButtonRectangle );

				SetProbeCount( 4 );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLProbesSettingsForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveNumNTC;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveNumNTC	= gRDEeprom.numNTC;

	// Imposta i nuovi dati
	gRDEeprom.numNTC	= m_ProbeCount;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, numNTC ),
		sizeof(gRDEeprom.numNTC),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		gRDEeprom.numNTC	= saveNumNTC;

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

void CLProbesSettingsForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_PROBES_SETTINGS ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// NR Analog Probes
	CLGraphics::DrawText( CLProbesSettingsForm_NRAnalogProbesTextPoint, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		"NR. T. ANALOG." );
	
	RenderDynamicObjects();
}

void CLProbesSettingsForm::RenderDynamicObjects()
{
	CLLCDCommon::DrawGenericButton( m_NRAnalogProbes2ButtonRectangle,
		(m_ProbeCount == 2 ?  GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont), "2" );
	CLLCDCommon::DrawGenericButton( m_NRAnalogProbes3ButtonRectangle,
		(m_ProbeCount == 3 ?  GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont), "3" );
	CLLCDCommon::DrawGenericButton( m_NRAnalogProbes4ButtonRectangle,
		(m_ProbeCount == 4 ?  GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont), "4" );
}

void CLProbesSettingsForm::SetProbeCount( byte value )
{
	if (value < 2)
		value	= 2;
	else
	if (value > 4)
		value	= 4;

	m_ProbeCount	= value;

	if (GetState() == CLState_Running)
		RenderDynamicObjects();
}
// -----------------------------------------------------------------------------
// CLProbesSettingsForm [class]
// =============================================================================

