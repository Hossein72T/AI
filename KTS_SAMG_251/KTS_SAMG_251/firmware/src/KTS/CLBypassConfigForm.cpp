#include "CLBypassConfigForm.h"

#include "CLBypass.h"
#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLBypassConfigForm_AutomaticOnConfigButtonRectangle			11, 28, 156, 57
#define	CLBypassConfigForm_AutomaticOnStandbyConfigButtonRectangle	165, 28, 310, 57

#define	CLBypassConfigForm_PreviousButtonRectangle			161, 190, 204, 229
#define	CLBypassConfigForm_NextButtonRectangle				215, 190, 258, 229

#define	CLBypassConfigForm_ExternalControlMessageRectangle	11, 28, 309, 173

#define	CLBypassConfigForm_ManualFrameRectangle				11, 70, 309, 118
#define	CLBypassConfigForm_ManualFrameTitlePoint			17, 62
#define	CLBypassConfigForm_ManualOpenConfigButtonRectangle	26, 82, 155, 111
#define	CLBypassConfigForm_ManualCloseConfigButtonRectangle	165, 82, 294, 111

#define	CLBypassConfigForm_MinTemp_FrameRectangle			11, 127, 309, 173
#define	CLBypassConfigForm_MinTemp_FrameTitlePoint			20, 120
#define	CLBypassConfigForm_MinTemp_TempValuePoint			20, 147
#define	CLBypassConfigForm_MinTemp_TempValueLength			6
#define	CLBypassConfigForm_MinTemp_UpButtonRectangle		217, 140, 256, 169
#define	CLBypassConfigForm_MinTemp_DownButtonRectangle		165, 140, 204, 169

#define	CLBypassConfigForm_RotationFrameRectangle					11, 31, 309, 79
#define	CLBypassConfigForm_RotationFrameTitlePoint					17, 23
#define	CLBypassConfigForm_RotationClockwiseButtonRectangle			18, 42, 157, 71
#define	CLBypassConfigForm_RotationCounterclockwiseButtonRectangle	165, 41, 304, 70

CLFormResult CLBypassConfigForm_Open( unsigned short options )
{
	CLBypassConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLBypassConfigForm [class]
// -----------------------------------------------------------------------------
CLBypassConfigForm::CLBypassConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
	m_PreviousButtonRectangle.Set( CLBypassConfigForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( CLBypassConfigForm_NextButtonRectangle );

	// Imposta i Config Buttons
	m_AutomaticOnConfigButtonRectangle.Set( CLBypassConfigForm_AutomaticOnConfigButtonRectangle );
	m_AutomaticOnStandbyConfigButtonRectangle.Set( CLBypassConfigForm_AutomaticOnStandbyConfigButtonRectangle );
	m_ManualOpenConfigButtonRectangle.Set( CLBypassConfigForm_ManualOpenConfigButtonRectangle );
	m_ManualCloseConfigButtonRectangle.Set( CLBypassConfigForm_ManualCloseConfigButtonRectangle );

	m_MinTemperature_UpButtonRectangle.Set( CLBypassConfigForm_MinTemp_UpButtonRectangle );
	m_MinTemperature_DownButtonRectangle.Set( CLBypassConfigForm_MinTemp_DownButtonRectangle );

	m_ClockwiseRotationButtonRectangle.Set( CLBypassConfigForm_RotationClockwiseButtonRectangle );
	m_CounterclockwiseRotationButtonRectangle.Set( CLBypassConfigForm_RotationCounterclockwiseButtonRectangle );
}

CLFormResult CLBypassConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetConfig( (CLBypassConfig) gRDEeprom.Config_Bypass );
	SetMinTemperature( Bypass_GetMinTemperature() );
	SetRotation( gRDEeprom.RotazioneBypass );
	SetState( CLState_Running );

	m_Options	= options;

	// Visualizza il form
	m_Page.SetPageCount( ((m_Options & CLFormOption_AdminMode) != 0 ? 2 : 1) );
	m_Page.Go( 0 );
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
			// Next Button
			if ((m_Options & CLFormOption_AdminMode) != 0 && m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage();
			}
			else
			// Previous Button
			if ((m_Options & CLFormOption_AdminMode) != 0 && m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				if (m_Page.GoPrevious())
					RenderPage();
			}
			else
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OkButtonRectangle );

				if (Save())
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
			if (m_Page.GetValue() == 0)
			{
				// AutomaticOnConfig Button
				if (m_Config != BPD_EXT_CTRL && m_AutomaticOnConfigButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_AutomaticOnConfigButtonRectangle );
					SetConfig( CLBypassConfig_AutomaticOn );
				}
				else
				// AutomaticOnStandbyConfig Button
				if (m_Config != BPD_EXT_CTRL && m_AutomaticOnStandbyConfigButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_AutomaticOnStandbyConfigButtonRectangle );
					SetConfig( CLBypassConfig_AutomaticOnStandby );
				}
				else
				// ManualOpenConfig Button
				if (m_Config != BPD_EXT_CTRL && m_ManualOpenConfigButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ManualOpenConfigButtonRectangle );
					SetConfig( CLBypassConfig_ManualOpen );
				}
				else
				// ManualCloseConfig Button
				if (m_Config != BPD_EXT_CTRL && m_ManualCloseConfigButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ManualCloseConfigButtonRectangle );
					SetConfig( CLBypassConfig_ManualClose );
				}
				// MinTemperature Up Button
				if (m_Config != BPD_EXT_CTRL && m_MinTemperature_UpButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_MinTemperature_UpButtonRectangle );

					while (Touched() != 0)
					{
						SetMinTemperature( m_MinTemperature + .5 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( UpDownButtons_Delay );
                        SYSTICK_DelayMs ( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_MinTemperature_UpButtonRectangle );
				}
				else
				// MinTemperature Down Button
				if (m_Config != BPD_EXT_CTRL && m_MinTemperature_DownButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_MinTemperature_DownButtonRectangle );

					while (Touched() != 0)
					{
						SetMinTemperature( m_MinTemperature - .5 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						//delay( UpDownButtons_Delay );
                        SYSTICK_DelayMs ( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_MinTemperature_DownButtonRectangle );
				}
				else
					WaitForTouchRelease();
			}
			else
			if (m_Page.GetValue() == 1)
			{
				// Clockwise Button
				if (m_ClockwiseRotationButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ClockwiseRotationButtonRectangle );
					SetRotation( CLBypassRotation_Clockwise );
				}
				else
				// Counterclockwise Button
				if (m_CounterclockwiseRotationButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_CounterclockwiseRotationButtonRectangle );
					SetRotation( CLBypassRotation_Counterclockwise );
				}
				else
					WaitForTouchRelease();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLBypassConfigForm::Save()
{
	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( m_Options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Scrive la MinTemperature
	if (m_MinTemperature != Bypass_GetMinTemperature() )
	{
		if (!Bypass_WriteMinTemperature( m_MinTemperature ))
		{
			// Visualizza il messaggio di errore
			if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayError();

			return false;
		}
	}

	// Scrive la Configurazione
	if (m_Config != gRDEeprom.Config_Bypass)
	{
		if (!Bypass_Write( m_Config ))
		{
			// Visualizza il messaggio di errore
			if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayError();

			return false;
		}
	}

	// Scrive la Rotazione
	if ((m_Options & CLFormOption_AdminMode) && m_Rotation != gRDEeprom.RotazioneBypass)
	{
		if (!Bypass_WriteRotation( m_Rotation ))
		{
			// Visualizza il messaggio di errore
			if (CLFormOption_CanShowWriteMessage_Error( m_Options ))
				CLLCDCommon::WriteDataPanel_DisplayError();

			return false;
		}
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( m_Options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLBypassConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_BPD_SETTINGS ),
		((m_Options & CLFormOption_AdminMode) != 0 ? &m_Page : NULL) );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	if ((m_Options & CLFormOption_AdminMode) != 0)
	{
		// Tasto Previous
		CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
			GenericButtonStyle_Normal_BigFont );

		// Tasto Next
		CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
			GenericButtonStyle_Normal_BigFont );
	}

	switch (m_Page.GetValue())
	{
		case 0:
			if (m_Config == BPD_EXT_CTRL)
			{
				CLGraphics::DrawBoxWithText( CLRectangle( CLBypassConfigForm_ExternalControlMessageRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
					RGBColor_Black, 0xFDE333,
					(byte) 1, 0xFFBD11,
					CLLocalitation::GetText( CLTextId_BYPASS_OPERATED_BY_EXT_INPUT ) );
			}
			else
			{
				// Manual Frame
				CLGraphics::DrawBox( CLRectangle( CLBypassConfigForm_ManualFrameRectangle ),
					GenericForm_Group_Style );

				CLGraphics::DrawText( CLBypassConfigForm_ManualFrameTitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
					RGBColor_Black, RGBColor_White,
					CLLocalitation::GetText( CLTextId_MANUAL ) );

				// MinTemperature Frame
				CLGraphics::DrawBox( CLRectangle( CLBypassConfigForm_MinTemp_FrameRectangle ),
					GenericForm_Group_Style );

				CLGraphics::DrawText( CLBypassConfigForm_MinTemp_FrameTitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
					RGBColor_Black, RGBColor_White,
					CLLocalitation::GetText( CLTextId_BYPASS_MIN_EXT_TEMPERATURE ) );

				RenderConfigButtons();
				RenderMinTemperature();
			}
			break;

		case 1:
			// Rotation Frame
			CLGraphics::DrawBox( CLRectangle( CLBypassConfigForm_RotationFrameRectangle ),
				GenericForm_Group_Style );

			CLGraphics::DrawText( CLBypassConfigForm_RotationFrameTitlePoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				"ROTATION" );

			RenderRotationButtons();
			break;
	}
}

void CLBypassConfigForm::RenderConfigButtons()
{
	if (m_Page.GetValue() == 0 && m_Config != BPD_EXT_CTRL)
	{
		char			text[ 40 ];
		CLRectangle*	buttonRectangle	= NULL;

		Bypass_GetConfigText( text, CLBypassConfig_AutomaticOn, false );
		CLLCDCommon::DrawGenericButton( m_AutomaticOnConfigButtonRectangle,
			(m_Config == CLBypassConfig_AutomaticOn ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
			text );

		Bypass_GetConfigText( text, CLBypassConfig_AutomaticOnStandby, false );
		CLLCDCommon::DrawGenericButton( m_AutomaticOnStandbyConfigButtonRectangle,
			(m_Config == CLBypassConfig_AutomaticOnStandby ? GenericButtonStyle_Selected_SmallFont_Multiline : GenericButtonStyle_Normal_SmallFont_Multiline),
			text );

		Bypass_GetConfigText( text, CLBypassConfig_ManualOpen, false );
		CLLCDCommon::DrawGenericButton( m_ManualOpenConfigButtonRectangle,
			(m_Config == CLBypassConfig_ManualOpen ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
			CLLocalitation::GetText( CLTextId_OPEN ) );

		Bypass_GetConfigText( text, CLBypassConfig_ManualClose, false );
		CLLCDCommon::DrawGenericButton( m_ManualCloseConfigButtonRectangle,
			(m_Config == CLBypassConfig_ManualClose ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
			CLLocalitation::GetText( CLTextId_CLOSED ) );
	}
}

void CLBypassConfigForm::RenderMinTemperature()
{
	if (m_Page.GetValue() == 0 && m_Config != BPD_EXT_CTRL)
	{
		char	text[ 12 ];

		// Visualizza la temperatura
		sprintf( text, "%2.1f %c",
			m_MinTemperature,
			FONT_SYMBOL_DEGREES );
		CLGraphics::DrawText( CLBypassConfigForm_MinTemp_TempValuePoint, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Left,
			RGBColor_Black, RGBColor_White,
			text, CLBypassConfigForm_MinTemp_TempValueLength );

		// Visualizza i pulsanti
		CLLCDCommon::DrawGenericButton( m_MinTemperature_UpButtonRectangle,
			GenericButtonStyle_Normal_UpDown,
			&UpMonoImage );
		CLLCDCommon::DrawGenericButton( m_MinTemperature_DownButtonRectangle,
			GenericButtonStyle_Normal_UpDown,
			&DownMonoImage );
	}
}

void CLBypassConfigForm::SetConfig( CLBypassConfig value )
{
	m_Config	= value;

	if (GetState() == CLState_Running)
		RenderConfigButtons();
}

void CLBypassConfigForm::SetMinTemperature( float value )
{
	if (value < 12.0f)
		value	= 12.0f;
	else
	if (value > 35.0f)
		value	= 35.0f;

	m_MinTemperature	= value;

	if (GetState() == CLState_Running)
		RenderMinTemperature();
}

void CLBypassConfigForm::SetRotation( byte value )
{
	m_Rotation	= value;

	if (GetState() == CLState_Running)
		RenderRotationButtons();
}

void CLBypassConfigForm::RenderRotationButtons()
{
	if (m_Page.GetValue() == 1)
	{
		CLLCDCommon::DrawGenericButton( m_ClockwiseRotationButtonRectangle,
			(m_Rotation == CLBypassRotation_Clockwise ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
			"CLOCKWISE" );

		CLLCDCommon::DrawGenericButton( m_CounterclockwiseRotationButtonRectangle,
			(m_Rotation == CLBypassRotation_Counterclockwise ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
			"COUNTERCLOCKWISE" );
	}
}
// -----------------------------------------------------------------------------
// CLBypassConfigForm [class]
// =============================================================================

