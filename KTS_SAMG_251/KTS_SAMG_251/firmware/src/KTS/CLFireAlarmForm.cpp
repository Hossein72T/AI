#include "CLFireAlarmForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"
#include "CLAlarm.h"

#define	CLFireAlarmForm_AlarmActiveRectangle				4, 30, 157, 116

#define	CLFireAlarmForm_ConfigurationAlarmPanelRectangle	162, 30, 315, 116
#define	CLFireAlarmForm_ConfigurationAlarmTitlePoint		165, 34
#define	CLFireAlarmForm_ConfigurationAlarmTitleLength		18
#define	CLFireAlarmForm_ConfigurationAlarmImageRectangle	180, 56, 293, 113

#define	CLFireAlarmForm_RearmPanelRectangle					4, 121, 315, 235
#define	CLFireAlarmForm_RearmPanelTextRectangle				12, 128, 306, 182
#define	CLFireAlarmForm_RearmButtonRectangle				67, 189, 246, 228

CLFormResult CLFireAlarmForm_Open( unsigned short options )
{
	CLFireAlarmForm	form;

	return form.Open( options );
}

// =============================================================================
// CLFireAlarmForm [class]
// -----------------------------------------------------------------------------
CLFireAlarmForm::CLFireAlarmForm()
{
	m_RearmButtonRectangle.Set( CLFireAlarmForm_RearmButtonRectangle );
}

CLFormResult CLFireAlarmForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;
	bool			isFireAlarm;
	byte			fireAlarm;

	// Inizializza i dati
	SetState( CLState_Initializing );
	isFireAlarm		= IsFireAlarm();
	fireAlarm		= GetCurrentFireAlarm();
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	while (true)
	{
		// Nel caso in cui si è connessi in RFM e non si riceve una risposta da più di un minuto
		// significa connessione persa, ritorna al form di connessione
		if (CLKTS::IsMissingRFMSignal())
		{
			gKTSGlobal.RunningMode	= CLKTSRunningMode_Initializing;
			formResult				= CLFormResult_Ok;
			break;
		}

		if ((isFireAlarm != IsFireAlarm() || fireAlarm != GetCurrentFireAlarm())
			&& gRDEeprom.manual_Reset)
		{
			isFireAlarm	= IsFireAlarm();
			fireAlarm	= GetCurrentFireAlarm();
			RenderPage();
		}

		// Se l'unità non è in fire alarm e non richiede un riarmo, allora esce
		if (!IsFireAlarm() && !gRDEeprom.manual_Reset)
		{
			// Controlla che se l'unità è in power off, allora esce
			if (gRDEeprom.Set_Power_ON == CLKTSPowerMode_Off)
				gKTSGlobal.RunningMode	= CLKTSRunningMode_PowerOff;
			else
				gKTSGlobal.RunningMode	= CLKTSRunningMode_Running;

			formResult	= CLFormResult_None;
			break;
		}

		RenderDynamicObjects();

		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (m_RearmButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_RearmButtonRectangle );

				Save( options );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLFireAlarmForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveManual_Reset;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveManual_Reset	= gRDEeprom.manual_Reset;

	// Imposta i nuovi dati
	gRDEeprom.manual_Reset	= 0;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, manual_Reset ),
		sizeof(gRDEeprom.manual_Reset),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.manual_Reset	= saveManual_Reset;

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

void CLFireAlarmForm::RenderPage()
{
	CLRectangle	configurationImageRectangle( CLFireAlarmForm_ConfigurationAlarmImageRectangle );
	
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_FIREALARM_FIRE_ALARM ),
		NULL );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	// Alarm Active Box
	if (IsFireAlarm())
	{
		CLGraphics::DrawBoxWithText( CLRectangle( CLFireAlarmForm_AlarmActiveRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
			RGBColor_Red, RGBColor_White, 1,
			RGBColor_White,
			CLLocalitation::GetText( CLTextId_FIREALARM_ALARM_ACTIVATED ) );
	}
	else
	{
		CLGraphics::DrawBoxWithText( CLRectangle( CLFireAlarmForm_AlarmActiveRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
			RGBColor_Green, RGBColor_White, 1,
			RGBColor_White,
			CLLocalitation::GetText( CLTextId_FIREALARM_ALARM_DEACTIVATED ) );
	}

	// Configuration Alarm Panel
	CLGraphics::DrawBox( CLRectangle( CLFireAlarmForm_ConfigurationAlarmPanelRectangle ),
		GenericForm_Group_Style );

	CLGraphics::DrawText( CLFireAlarmForm_ConfigurationAlarmTitlePoint, CLGraphicStyleOptions_TextAlignBy_Pixel| CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_FIREALARM_CONFIGURATION ), CLFireAlarmForm_ConfigurationAlarmTitleLength );	

	switch (GetCurrentFireAlarm())
	{
		case ALM_SMOKE_VENT_OFF:
			CLLCDCommon::RenderFireConfiguration( configurationImageRectangle, INP_12V_ALM_FIRE_UNIT_STOP );
			break;
		case ALM_SMOKE_VENT_MAX:
			CLLCDCommon::RenderFireConfiguration( configurationImageRectangle, INP_12V_ALM_FIRE_VENT_MAX );
			break;
		case ALM_SMOKE_ONLY_EXT:
			CLLCDCommon::RenderFireConfiguration( configurationImageRectangle, INP_12V_ALM_FIRE_ONLY_EXTRACT );
			break;
		case ALM_SMOKE_ONLY_SUP:
			CLLCDCommon::RenderFireConfiguration( configurationImageRectangle, INP_12V_ALM_FIRE_ONLY_SUPPLY );
			break;
	}

	// Rearm Panel
	CLGraphics::DrawBox( CLRectangle( CLFireAlarmForm_RearmPanelRectangle ),
		GenericForm_Group_Style );

	CLGraphics::DrawBoxWithText( CLRectangle( CLFireAlarmForm_RearmPanelTextRectangle ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_FIREALARM_REARM_MESSAGE ) );	

	// Draw Rearm Button
	CLLCDCommon::DrawGenericButton( m_RearmButtonRectangle, GenericButtonStyle_Normal_BigFont,
		CLLocalitation::GetText( CLTextId_FIREALARM_REARM ) );
	
	RenderDynamicObjects();
}

void CLFireAlarmForm::RenderDynamicObjects()
{
}
// -----------------------------------------------------------------------------
// CLFireAlarmForm [class]
// =============================================================================

