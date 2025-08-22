#include "CLCleanEventForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"

#define	CLCleanEventForm_OnOffButtonRectangle	15, 35, 84, 94
#define	CLCleanEventForm_UpButtonRectangle		230, 49, 289, 88
#define	CLCleanEventForm_DownButtonRectangle	230, 110, 289, 149
#define	CLCleanEventForm_DaysFrameRectangle	93, 35, 304, 164
#define	CLCleanEventForm_TextDaysPoint		99, 90

CLFormResult CLCleanEventForm_Open( unsigned short options )
{
	CLCleanEventForm	form;

	return form.Open( options );
}

// =============================================================================
// CLCleanEventForm [class]
// -----------------------------------------------------------------------------
CLCleanEventForm::CLCleanEventForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLCleanEventForm_OnOffButtonRectangle );

	m_UpButtonRectangle.Set( CLCleanEventForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLCleanEventForm_DownButtonRectangle );

	m_Days_ProgressiveTouchUpDown.Set( 120, 5, 80, 12, 50, 10 );

}

CLFormResult CLCleanEventForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	RenderPage();

	// Imposta i valori correnti
	SetEnabled( Function_IsEnabled( ENAB_CLEAN_EVENT ) );
	SetDays( gRDEeprom.Clean_Event_Delay );

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
			if (m_OkButtonRectangle.Contains( touchX, touchY ) && IsDataChanged())
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
			if (m_UpButtonRectangle.Contains( touchX, touchY ) && m_Enabled)
			{
				CLLCDCommon::WaitButton_Pressed( m_UpButtonRectangle );

				m_Days_ProgressiveTouchUpDown.Reset();
				while (m_Days_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Days_ProgressiveTouchUpDown.CanIncrement())
						SetDays( true );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Down Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ) && m_Enabled)
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				m_Days_ProgressiveTouchUpDown.Reset();
				while (m_Days_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Days_ProgressiveTouchUpDown.CanIncrement())
						SetDays( false );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLCleanEventForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	for (int stepsCounter = 0; stepsCounter < 2; stepsCounter++)
	{
		byte	saveSet_TimeCleanEvent;
		bool	saveCleanEventEnabled;

		// Effettua la prima richiesta
		if (stepsCounter == 0)
		{
			// Salva temporaneamente il valore dei minuti
			saveSet_TimeCleanEvent	= gRDEeprom.Clean_Event_Delay;

			//Imposta il nuovo valore
			gRDEeprom.Clean_Event_Delay	= m_Days;

			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Clean_Event_Delay ),
				sizeof(gRDEeprom.Clean_Event_Delay),
				&writeEeprom_Status );
		}
		else
		{
			// Salva temporaneamente il valore di attivazione boost
			saveCleanEventEnabled	= Function_IsEnabled( ENAB_CLEAN_EVENT );

			//Imposta il nuovo valore
			Function_SetEnabled( ENAB_CLEAN_EVENT, m_Enabled );

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
				gRDEeprom.Clean_Event_Delay	= saveSet_TimeCleanEvent;
			else
				Function_SetEnabled( ENAB_CLEAN_EVENT, saveCleanEventEnabled );
			break;
		}
	}

	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
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

void CLCleanEventForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SET_CLEAN_EVENT_DELAY ),
		NULL );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Ok
	RenderOkButton();

	// Draw minutes Frame
	CLGraphics::DrawBox( CLRectangle( CLCleanEventForm_DaysFrameRectangle ),
		GenericForm_Group_Style );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderOnOffButtons();
	RenderDays();
}

void CLCleanEventForm::RenderOnOffButtons()
{
	// On/Off Button
	CLLCDCommon::DrawGenericButton( m_OnOffButtonRectangle,
		(m_Enabled ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(m_Enabled ? CLFixedText_ON : CLFixedText_OFF) );

	CLLCDCommon::DrawGenericButton( m_UpButtonRectangle,
		(m_Enabled ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DownButtonRectangle,
		(m_Enabled ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&DownMonoImage );
}

void CLCleanEventForm::RenderOkButton()
{
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		(IsDataChanged() ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont) );
}

void CLCleanEventForm::RenderDays()
{
	char	text[ 15 ];

	sprintf( text, "%d %s", m_Days, CLLocalitation::GetText( CLTextId_DAYS_ABBR ) );
	CLGraphics::DrawText( CLCleanEventForm_TextDaysPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 7 );
}

void CLCleanEventForm::SetEnabled( bool value )
{
	if (value == m_Enabled)
		return;

	m_Enabled	= value;
	RenderOnOffButtons();
	RenderOkButton();
}

void CLCleanEventForm::SetDays(  bool value )
{
	if ( value )
    {
        if (m_Days == 30)
            m_Days = 60;
        else
            if (m_Days == 60)
                m_Days = 90;
            else
                if (m_Days == 0)
                    m_Days = 30;
    }
    else
    {
        if (m_Days == 60)
            m_Days = 30;
        else
            if (m_Days == 90)
                m_Days = 60;
    }
    
    if ( (m_Days != 30) && (m_Days != 60) && (m_Days != 90))
        m_Days = 30;
    
	RenderDays();
	RenderOkButton();
}

bool CLCleanEventForm::IsDataChanged()
{
	return (m_Enabled != Function_IsEnabled( ENAB_CLEAN_EVENT ) || m_Days != gRDEeprom.Clean_Event_Delay);
}
// -----------------------------------------------------------------------------
// CLPartyConfigForm [class]
// =============================================================================

