#include "CLReferenceTSettingForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLTouch.h"
#include "CLImages.h"
#include "CLAccessory.h"

#define CLReferenceTSettingForm_ReferenceProbe_PanelRectangle			4, 31, 313, 75
#define CLReferenceTSettingForm_ReferenceProbe_TitlePoint				12, 25
#define CLReferenceTSettingForm_ReferenceProbe_ReturnButtonRectangle	12, 41, 155, 69
#define CLReferenceTSettingForm_ReferenceProbe_SupplyButtonRectangle	163, 41, 306, 68

#define CLReferenceTSettingForm_DeltaTemperature_PanelRectangle			4, 86, 313, 124
#define CLReferenceTSettingForm_DeltaTemperature_TitlePoint				12, 80
#define CLReferenceTSettingForm_DeltaTemperature_ValuePoint				11, 99
#define CLReferenceTSettingForm_DeltaTemperature_ValueLength			10
#define CLReferenceTSettingForm_DeltaTemperature_DownButtonRectangle	218, 93, 257, 117
#define CLReferenceTSettingForm_DeltaTemperature_UpButtonRectangle		267, 93, 306, 117

#define CLReferenceTSettingForm_Delay_PanelRectangle					4, 135, 313, 173
#define CLReferenceTSettingForm_Delay_TitlePoint						11, 129
#define CLReferenceTSettingForm_Delay_ValuePoint						11, 148
#define CLReferenceTSettingForm_Delay_ValueLength						10
#define CLReferenceTSettingForm_Delay_DownButtonRectangle				218, 142, 257, 166
#define CLReferenceTSettingForm_Delay_UpButtonRectangle					267, 142, 306, 166

CLFormResult CLReferenceTSettingForm_Open( unsigned short options )
{
	CLReferenceTSettingForm	form;

	return form.Open( options );
}

// =============================================================================
// CLReferenceTSettingForm [class]
// -----------------------------------------------------------------------------
CLReferenceTSettingForm::CLReferenceTSettingForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_ReferenceProbe_ReturnButtonRectangle.Set( CLReferenceTSettingForm_ReferenceProbe_ReturnButtonRectangle );
	m_ReferenceProbe_SupplyButtonRectangle.Set( CLReferenceTSettingForm_ReferenceProbe_SupplyButtonRectangle );

	m_DeltaTemperature_UpButtonRectangle.Set( CLReferenceTSettingForm_DeltaTemperature_UpButtonRectangle );
	m_DeltaTemperature_DownButtonRectangle.Set( CLReferenceTSettingForm_DeltaTemperature_DownButtonRectangle );

	m_Delay_UpButtonRectangle.Set( CLReferenceTSettingForm_Delay_UpButtonRectangle );
	m_Delay_DownButtonRectangle.Set( CLReferenceTSettingForm_Delay_DownButtonRectangle );
}

CLFormResult CLReferenceTSettingForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	m_RefTSetting	= gRDEeprom.RefTSetting;
	SetDeltaTemperature( ((float) gRDEeprom.DeltaTemp_Supply) / 10.0f );
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
			bool	exitForm	= false;

			touchX	= ReadX();
			touchY	= ReadY();

			while (true)
			{
				// Home Button
				if (m_HomeButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_HomeButtonRectangle );
					formResult	= CLFormResult_Home;
					exitForm	= true;
					break;
				}

				// Back Button
				if (m_BackButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_BackButtonRectangle );
					formResult	= CLFormResult_Back;
					exitForm	= true;
					break;
				}

				// Ok Button
				if (m_OkButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_OkButtonRectangle );

					if (Save( options ))
					{
						if (CLFormOption_CanExitAfterWrite( options ))
						{
							formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
							exitForm	= true;
							break;
						}
					}
					RenderPage();
					break;
				}

				// ReferenceProbe Return Button
				if (m_ReferenceProbe_ReturnButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ReferenceProbe_ReturnButtonRectangle );
					SelectProbeReturn();
					break;
				}

				// ReferenceProbe Supply Button
				if (m_ReferenceProbe_SupplyButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ReferenceProbe_SupplyButtonRectangle );
					SelectProbeSupply();
					break;
				}

				// DeltaTemperature Up Button
				if (IsProbeSupplySelected() && m_DeltaTemperature_UpButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_DeltaTemperature_UpButtonRectangle );

					while (Touched() != 0)
					{
						SetDeltaTemperature( m_DeltaTemperature + 0.5f );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( 120 );
                        SYSTICK_DelayMs ( 120 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_DeltaTemperature_UpButtonRectangle );
					break;
				}

				// DeltaTemperature Down Button
				if (IsProbeSupplySelected() && m_DeltaTemperature_DownButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_DeltaTemperature_DownButtonRectangle );

					while (Touched() != 0)
					{
						SetDeltaTemperature( m_DeltaTemperature - 0.5f );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( 120 );
                        SYSTICK_DelayMs ( 120 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_DeltaTemperature_DownButtonRectangle );
					break;
				}

				if (Accessory_IsPresent( ACC_EEP_DXD ))
				{
					// Delay Up Button
					if (m_Delay_UpButtonRectangle.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton_Pressed( m_Delay_UpButtonRectangle );

						while (Touched() != 0)
						{
							SetDelay( GetDelay() + 1 );
							CLKTS::Process();
							CLKTS::Pir_Process();
							//delay( 120 );
                            SYSTICK_DelayMs ( 120 );
						}

						CLLCDCommon::WaitButton_Unpressed( m_Delay_UpButtonRectangle );
						break;
					}

					// Delay Down Button
					if (m_Delay_DownButtonRectangle.Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton_Pressed( m_Delay_DownButtonRectangle );

						while (Touched() != 0)
						{
							SetDelay( GetDelay() - 1 );
							CLKTS::Process();
							CLKTS::Pir_Process();
							//delay( 120 );
                            SYSTICK_DelayMs ( 120 );
						}

						CLLCDCommon::WaitButton_Unpressed( m_Delay_DownButtonRectangle );
						break;
					}
				}

				// Touch non gestito
				WaitForTouchRelease();
				break;
			}

			if (exitForm)
				break;
		}
    }

	return formResult;
}

bool CLReferenceTSettingForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveRefTSetting;
	byte			saveDeltaTemp_Supply;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveDeltaTemp_Supply	= gRDEeprom.DeltaTemp_Supply;
	saveRefTSetting			= gRDEeprom.RefTSetting;

	// Imposta i nuovi dati
	gRDEeprom.DeltaTemp_Supply	= (byte) (m_DeltaTemperature * 10);
	gRDEeprom.RefTSetting		= m_RefTSetting;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof(S_EEPROM, RefTSetting),
		sizeof(gRDEeprom.RefTSetting) + sizeof(gRDEeprom.DeltaTemp_Supply),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.RefTSetting		= saveRefTSetting;
		gRDEeprom.DeltaTemp_Supply	= saveDeltaTemp_Supply;

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

void CLReferenceTSettingForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_REFERENCE_T_SETTING ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	// ReferenceProbe Panel
	CLGraphics::DrawBox( CLRectangle( CLReferenceTSettingForm_ReferenceProbe_PanelRectangle ), 
		GenericForm_Group_Style );

	CLGraphics::DrawText( CLReferenceTSettingForm_ReferenceProbe_TitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_DXDSETTINGS_REFERENCEPROBE ) );

	// Delay Panel
	if (Accessory_IsPresent( ACC_EEP_DXD ))
	{
		CLGraphics::DrawBox( CLRectangle( CLReferenceTSettingForm_Delay_PanelRectangle ), 
			GenericForm_Group_Style );

		CLGraphics::DrawText( CLReferenceTSettingForm_Delay_TitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			CLLocalitation::GetText( CLTextId_DXDSETTINGS_DELAY ) );
	}

	RenderReferenceProbeButtons();
	RenderDeltaTemperature( true );
	RenderDelay();
}

void CLReferenceTSettingForm::RenderReferenceProbeButtons()
{
	CLLCDCommon::DrawGenericButton( m_ReferenceProbe_SupplyButtonRectangle,
		(IsProbeSupplySelected() ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_SUPPLY ) );
	CLLCDCommon::DrawGenericButton( m_ReferenceProbe_ReturnButtonRectangle,
		(IsProbeReturnSelected() ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_RETURN ) );
}

void CLReferenceTSettingForm::RenderDeltaTemperature( bool redrawAllPanel )
{
	char	text[ 20 ];

	if (redrawAllPanel)
	{
		// DeltaTemperature Panel
		CLGraphics::DrawBox( CLRectangle( CLReferenceTSettingForm_DeltaTemperature_PanelRectangle ), 
			(IsProbeSupplySelected() ? GenericForm_Group_Style : GenericForm_GroupDisabled_Style) );

		CLGraphics::DrawText( CLReferenceTSettingForm_DeltaTemperature_TitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, (IsProbeSupplySelected() ? RGBColor_White : 0xC9C9C9),
			CLLocalitation::GetText( CLTextId_DXDSETTINGS_DELTATEMPERATURE ) );
	}

	sprintf( text, "%2.1f%c", m_DeltaTemperature, FONT_SYMBOL_DEGREES );

	CLGraphics::DrawText( CLReferenceTSettingForm_DeltaTemperature_ValuePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, (IsProbeSupplySelected() ? RGBColor_White : 0xC9C9C9),
		text, CLReferenceTSettingForm_DeltaTemperature_ValueLength );

	CLLCDCommon::DrawGenericButton( m_DeltaTemperature_UpButtonRectangle,
		(IsProbeSupplySelected() ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DeltaTemperature_DownButtonRectangle,
		(IsProbeSupplySelected() ? GenericButtonStyle_Normal_UpDown : GenericButtonStyle_Disabled_UpDown),
		&DownMonoImage );
}

void CLReferenceTSettingForm::RenderDelay()
{
	if (!Accessory_IsPresent( ACC_EEP_DXD ))
		return;

	char	text[ 20 ];

	sprintf( text, "%d %s", 30 + GetDelay() * 10, CLLocalitation::GetText( CLTextId_SECOND_ABBR ) );

	CLGraphics::DrawText( CLReferenceTSettingForm_Delay_ValuePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, CLReferenceTSettingForm_Delay_ValueLength );

	CLLCDCommon::DrawGenericButton( m_Delay_UpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_Delay_DownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );
}

void CLReferenceTSettingForm::SelectProbeReturn()
{
	bitSet( m_RefTSetting, 1 );
	if (GetState() == CLState_Running)
	{
		RenderReferenceProbeButtons();
		RenderDeltaTemperature( true );
	}
}

bool CLReferenceTSettingForm::IsProbeReturnSelected()
{
	return bitRead( m_RefTSetting, 1 ) ? true : false;
}

void CLReferenceTSettingForm::SelectProbeSupply()
{
	bitClear( m_RefTSetting, 1 );
	if (GetState() == CLState_Running)
	{
		RenderReferenceProbeButtons();
		RenderDeltaTemperature( true );
	}
}

bool CLReferenceTSettingForm::IsProbeSupplySelected()
{
	return bitRead( m_RefTSetting, 1 ) ? false : true;
}

void CLReferenceTSettingForm::SetDeltaTemperature( float value )
{
	if (value < 0.5f)
		value	= 0.5f;
	else
	if (value > 20.0f)
		value	= 20.0f;

	m_DeltaTemperature	= value;

	if (GetState() == CLState_Running)
		RenderDeltaTemperature( false );
}

void CLReferenceTSettingForm::SetDelay( short value )
{
	if (value < 0)
		value	= 0;
	else
	if (value > 15)
		value	= 15;

	m_RefTSetting	= ((m_RefTSetting & 0xC3) | (value << 2)) & 0xFF;
	
	if (GetState() == CLState_Running)
		RenderDelay();
}

short CLReferenceTSettingForm::GetDelay()
{
	return (short) ((m_RefTSetting & 0x3C) >> 2);
}
// -----------------------------------------------------------------------------
// CLReferenceTSettingForm [class]
// =============================================================================

