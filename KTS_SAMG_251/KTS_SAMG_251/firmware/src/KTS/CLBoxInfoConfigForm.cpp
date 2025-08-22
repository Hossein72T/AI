#include "CLBoxInfoConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"

CLFormResult CLBoxInfoConfigForm_Open( unsigned short options )
{
	CLBoxInfoConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLBoxInfoConfigForm [class]
// -----------------------------------------------------------------------------
CLBoxInfoConfigForm::CLBoxInfoConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	// Imposta i Config Buttons
	m_TReturnButtonRectangle.Set( 15, 30, 104, 69 );
	m_TFreshButtonRectangle.Set( 15, 80, 104, 119 );
	m_FiltersButtonRectangle.Set( 15, 130, 104, 169 );
	m_AccessoriesButtonRectangle.Set( 115, 30, 204, 69 );
	m_DefrostButtonRectangle.Set( 115, 80, 204, 119 );
	m_BypassButtonRectangle.Set( 115, 130, 204, 169 );
	m_ProbesButtonRectangle.Set( 215, 30, 304, 69 );
}

CLFormResult CLBoxInfoConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	m_Value			= gKTSEeprom.GetDesktopBoxInfo();
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
			// TReturn Button
			if (m_TReturnButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_TReturnButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_TReturn );
			}
			else
			// TFresh Button
			if (m_TFreshButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_TFreshButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_TFresh );
			}
			else
			// Filters Button
			if (m_FiltersButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_FiltersButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_Filters );
			}
			else
			// Accessories Button
			if (m_AccessoriesButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_AccessoriesButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_Accessories );
			}
			else
			// Defrost Button
			if (m_DefrostButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_DefrostButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_Defrost );
			}
			else
			// Bypass Button
			if (m_BypassButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BypassButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_Bypass );
			}
			else
			// Probes Button
			if (m_ProbesButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ProbesButtonRectangle );
				ReverseEnabled( CLBoxInfo_InfoId_Probes );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLBoxInfoConfigForm::Save( unsigned short options )
{
	if (!CLBoxInfo::Write( m_Value ))
	{
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess( 2000 );

	return true;
}

void CLBoxInfoConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_CONFIG_BOX_INFO ),
		NULL );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderConfigButtons();
}

void CLBoxInfoConfigForm::RenderConfigButtons()
{
	char			text[ 40 ];
	CLRectangle*	buttonRectangle	= NULL;

	CLLCDCommon::DrawGenericButton( m_TReturnButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_TReturn ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_TRETURN ) );

	CLLCDCommon::DrawGenericButton( m_TFreshButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_TFresh ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_TFRESH ) );

	CLLCDCommon::DrawGenericButton( m_FiltersButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_Filters ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_FILTERS ) );

	CLLCDCommon::DrawGenericButton( m_AccessoriesButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_Accessories ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_BOXINFO_ACCESSORY_CLIMA ) );

	CLLCDCommon::DrawGenericButton( m_DefrostButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_Defrost ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_DEFROST ) );

	CLLCDCommon::DrawGenericButton( m_BypassButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_Bypass ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_BYPASS ) );

	CLLCDCommon::DrawGenericButton( m_ProbesButtonRectangle,
		(IsEnabled( CLBoxInfo_InfoId_Probes ) ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
		CLLocalitation::GetText( CLTextId_PROBES ) );
}

void CLBoxInfoConfigForm::SetEnabled( CLBoxInfo_InfoId infoId, bool value )
{
	m_Value	&= ~infoId;
	if (value)
		m_Value	|= infoId;

	if (GetState() == CLState_Running)
		RenderConfigButtons();
}

void CLBoxInfoConfigForm::ReverseEnabled( CLBoxInfo_InfoId infoId )
{
	if (m_Value & infoId)
		m_Value	&= ~infoId;
	else
		m_Value	|= infoId;

	if (GetState() == CLState_Running)
		RenderConfigButtons();
}

bool CLBoxInfoConfigForm::IsEnabled( CLBoxInfo_InfoId infoId )
{
	return (m_Value & infoId ? true : false);
}
// -----------------------------------------------------------------------------
// CLBoxInfoConfigForm [class]
// =============================================================================

