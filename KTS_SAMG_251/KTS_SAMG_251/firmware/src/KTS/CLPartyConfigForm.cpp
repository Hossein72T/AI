#include "CLPartyConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"

#define	CLPartyConfigForm_OnOffButtonRectangle	15, 35, 84, 94
#define	CLPartyConfigForm_UpButtonRectangle		230, 49, 289, 88
#define	CLPartyConfigForm_DownButtonRectangle	230, 110, 289, 149
#define	CLPartyConfigForm_MinutesFrameRectangle	93, 35, 304, 164
#define	CLPartyConfigForm_TextMinutesPoint		99, 90

CLFormResult CLPartyConfigForm_Open( unsigned short options )
{
	CLPartyConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLPartyConfigForm [class]
// -----------------------------------------------------------------------------
CLPartyConfigForm::CLPartyConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLPartyConfigForm_OnOffButtonRectangle );

	m_UpButtonRectangle.Set( CLPartyConfigForm_UpButtonRectangle );
	m_DownButtonRectangle.Set( CLPartyConfigForm_DownButtonRectangle );

	m_Minutes_ProgressiveTouchUpDown.Set( 120, 5, 80, 12, 50, 10 );

}

CLFormResult CLPartyConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	RenderPage();

	// Imposta i valori correnti
	SetEnabled( Function_IsEnabled( ENAB_BOOST ) );
	SetMinutes( gRDEeprom.Set_TimeBoost );

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

				m_Minutes_ProgressiveTouchUpDown.Reset();
				while (m_Minutes_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Minutes_ProgressiveTouchUpDown.CanIncrement())
						SetMinutes( (int) m_Minutes + 5 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_UpButtonRectangle );
			}
			else
			// Off Button
			if (m_DownButtonRectangle.Contains( touchX, touchY ) && m_Enabled)
			{
				CLLCDCommon::WaitButton_Pressed( m_DownButtonRectangle );

				m_Minutes_ProgressiveTouchUpDown.Reset();
				while (m_Minutes_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Minutes_ProgressiveTouchUpDown.CanIncrement())
						SetMinutes( (int) m_Minutes - 5 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLPartyConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	for (int stepsCounter = 0; stepsCounter < 2; stepsCounter++)
	{
		byte	saveSet_TimeBoost;
		bool	saveBoostEnabled;

		// Effettua la prima richiesta
		if (stepsCounter == 0)
		{
			// Salva temporaneamente il valore dei minuti
			saveSet_TimeBoost	= gRDEeprom.Set_TimeBoost;

			//Imposta il nuovo valore
			gRDEeprom.Set_TimeBoost	= m_Minutes;

			// Accoda la richiesta di WriteEeprom
			KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_TimeBoost ),
				sizeof(gRDEeprom.Set_TimeBoost),
				&writeEeprom_Status );
		}
		else
		{
			// Salva temporaneamente il valore di attivazione boost
			saveBoostEnabled	= Function_IsEnabled( ENAB_BOOST );

			//Imposta il nuovo valore
			Function_SetEnabled( ENAB_BOOST, m_Enabled );

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
				gRDEeprom.Set_TimeBoost	= saveSet_TimeBoost;
			else
				Function_SetEnabled( ENAB_BOOST, saveBoostEnabled );
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

void CLPartyConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SET_PARTY_TIMER ),
		NULL );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Ok
	RenderOkButton();

	// Draw minutes Frame
	CLGraphics::DrawBox( CLRectangle( CLPartyConfigForm_MinutesFrameRectangle ),
		GenericForm_Group_Style );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderOnOffButtons();
	RenderMinutes();
}

void CLPartyConfigForm::RenderOnOffButtons()
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

void CLPartyConfigForm::RenderOkButton()
{
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		(IsDataChanged() ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont) );
}

void CLPartyConfigForm::RenderMinutes()
{
	char	text[ 15 ];

	sprintf( text, "%d %s", m_Minutes, CLLocalitation::GetText( CLTextId_MINUTE_ABBR ) );
	CLGraphics::DrawText( CLPartyConfigForm_TextMinutesPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 7 );
}

void CLPartyConfigForm::SetEnabled( bool value )
{
	if (value == m_Enabled)
		return;

	m_Enabled	= value;
	RenderOnOffButtons();
	RenderOkButton();
}

void CLPartyConfigForm::SetMinutes( int value )
{
	if (value > 240)
		value	= 15;
	else
	if (value < 15)
		value	= 240;

	m_Minutes	= value;
	RenderMinutes();
	RenderOkButton();
}

bool CLPartyConfigForm::IsDataChanged()
{
	return (m_Enabled != Function_IsEnabled( ENAB_BOOST ) || m_Minutes != gRDEeprom.Set_TimeBoost);
}
// -----------------------------------------------------------------------------
// CLPartyConfigForm [class]
// =============================================================================

