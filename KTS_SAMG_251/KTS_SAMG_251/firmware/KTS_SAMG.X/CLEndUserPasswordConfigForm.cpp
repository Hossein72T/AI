#include "CLEndUserPasswordConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLPasswordForm.h"

#define CLEndUserPasswordConfigForm_OnOffButtonRectangle			15, 70, 84, 129
#define CLEndUserPasswordConfigForm_ChangePasswordButtonRectangle	98, 70, 306, 129

CLFormResult CLEndUserPasswordConfigForm_Open( unsigned short options )
{
	CLEndUserPasswordConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLEndUserPasswordConfigForm [class]
// -----------------------------------------------------------------------------
CLEndUserPasswordConfigForm::CLEndUserPasswordConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLEndUserPasswordConfigForm_OnOffButtonRectangle );
	m_ChangePasswordButtonRectangle.Set( CLEndUserPasswordConfigForm_ChangePasswordButtonRectangle );

	m_ChangePasswordNormalButtonStyle.Set( GenericButtonStyle_Normal_BigFont );
	m_ChangePasswordNormalButtonStyle.Options	|= CLGraphicStyleOptions_Text_MultiLine;
}

CLFormResult CLEndUserPasswordConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetEnabled( Function_IsEnabled( ENAB_PASSWORD ) );
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
			// AutomaticConfig Button
			if (m_OnOffButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OnOffButtonRectangle );
				SetEnabled( !m_PasswordEnabled );
			}
			else
			// ChangePassword Button
			if (m_ChangePasswordButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ChangePasswordButtonRectangle );

				CLKTS::ChangePassword( false );
				RenderPage();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLEndUserPasswordConfigForm::Save( unsigned short options )
{
	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	if (!Function_Write( ENAB_PASSWORD, m_PasswordEnabled ))
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

void CLEndUserPasswordConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back BUtton
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_PASSWORD ),
		NULL );

	// ChangePassword Button
	CLLCDCommon::DrawGenericButton( m_ChangePasswordButtonRectangle,
		m_ChangePasswordNormalButtonStyle,
		CLLocalitation::GetText( CLTextId_CHANGE_PASSWORD ) );

	RenderOnOffButton();
}

void CLEndUserPasswordConfigForm::RenderOnOffButton()
{
	// OnOff Button
	CLLCDCommon::DrawGenericButton( m_OnOffButtonRectangle,
		(m_PasswordEnabled ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(m_PasswordEnabled ? CLFixedText_ON : CLFixedText_OFF) );
}

void CLEndUserPasswordConfigForm::SetEnabled( bool value )
{
	m_PasswordEnabled	= value;

	if (GetState() == CLState_Running)
		RenderOnOffButton();
}

// -----------------------------------------------------------------------------
// CLOutputConfigForm [class]
// =============================================================================



