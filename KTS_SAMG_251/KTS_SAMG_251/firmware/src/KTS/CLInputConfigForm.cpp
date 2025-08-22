#include "CLInputConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLInputOutput.h"

#define	CLInputConfigForm_PreviousButtonRectangle			161, 190, 204, 229
#define	CLInputConfigForm_NextButtonRectangle				215, 190, 258, 229

#define CLInputConfigForm_Input1ButtonRectangle				9, 30, 38, 89
#define CLInputConfigForm_Input2ButtonRectangle				9, 110, 38, 169
#define CLInputConfigForm_DisableButtonRectangle			53, 40, 115, 94
#define CLInputConfigForm_RegAirFlowButtonRectangle			124, 40, 305, 64
#define CLInputConfigForm_RegAirFlowProgressBarRectangle	124, 69, 266, 94
#define CLInputConfigForm_0VUnitStopButtonRectangle			92, 102, 193, 131
#define CLInputConfigForm_10VUnitStopButtonRectangle		205, 102, 306, 131
#define CLInputConfigForm_0VBypassOpenButtonRectangle		92, 138, 193, 167
#define CLInputConfigForm_10VBypassOpenButtonRectangle		205, 138, 306, 167
#define CLInputConfigForm_DataFrameRectangle				45, 30, 313, 173
#define CLInputConfigForm_UnitTextPoint						53, 111
#define CLInputConfigForm_BPDTextPoint						53, 147
#define CLInputConfigForm_InputMeasureTextPoint				270, 77

#define CLInputConfigForm_FireAlarmTitleTextPoint			49, 34
#define CLInputConfigForm_FireAlarmTitleTextLength			32

#if FIREALARM_ALL_CONFIGURATION == 1
#define CLInputConfigForm_Fire_NoFanRectangle				60, 50, 173, 107
#define CLInputConfigForm_Fire_MaxFanRectangle				186, 50, 299, 107
#define CLInputConfigForm_Fire_OnlyFanSupplyRectangle		60, 112, 173, 169
#define CLInputConfigForm_Fire_OnlyFanExtractRectangle		186, 112, 299, 169
#else
#define CLInputConfigForm_Fire_NoFanRectangle				118, 50, 231, 107
#endif

CLFormResult CLInputConfigForm_Open( unsigned short options )
{
	CLInputConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLInputConfigForm [class]
// -----------------------------------------------------------------------------
CLInputConfigForm::CLInputConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
	m_PreviousButtonRectangle.Set( CLInputConfigForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( CLInputConfigForm_NextButtonRectangle );

	m_Input1ButtonRectangle.Set( CLInputConfigForm_Input1ButtonRectangle );
	m_Input2ButtonRectangle.Set( CLInputConfigForm_Input2ButtonRectangle );

	m_DisableButtonRectangle.Set( CLInputConfigForm_DisableButtonRectangle );
	m_RegAirFlowButtonRectangle.Set( CLInputConfigForm_RegAirFlowButtonRectangle );
	m_RegAirFlowProgressBarRectangle.Set( CLInputConfigForm_RegAirFlowProgressBarRectangle );
	
	m_0VUnitStopButtonRectangle.Set( CLInputConfigForm_0VUnitStopButtonRectangle );
	m_10VUnitStopButtonRectangle.Set( CLInputConfigForm_10VUnitStopButtonRectangle );
	m_0VBypassOpenButtonRectangle.Set( CLInputConfigForm_0VBypassOpenButtonRectangle );
	m_10VBypassOpenButtonRectangle.Set( CLInputConfigForm_10VBypassOpenButtonRectangle );

	m_FireNoFanButtonRectangle.Set( CLInputConfigForm_Fire_NoFanRectangle );
#if FIREALARM_ALL_CONFIGURATION == 1
	m_FireMaxFanButtonRectangle.Set( CLInputConfigForm_Fire_MaxFanRectangle );
	m_FireOnlyFanExtractButtonRectangle.Set( CLInputConfigForm_Fire_OnlyFanExtractRectangle );
	m_FireOnlyFanSupplyButtonRectangle.Set( CLInputConfigForm_Fire_OnlyFanSupplyRectangle );
#endif
}

CLFormResult CLInputConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_SaveInputMeasures[ 0 ]	= -1;
	m_SaveInputMeasures[ 1 ]	= -1;
	m_CurrentPowerON			= gRDEeprom.Set_Power_ON;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetInput( 0, gRDEeprom.Set_Input[ 0 ] );
	SetInput( 1, gRDEeprom.Set_Input[ 1 ] );
	SelectInput( 0, false );
	SetState( CLState_Running );

	// Visualizza il form
	m_Page.SetPageCount( 2 );
	m_Page.Go( 0 );
	SelectInput( m_SelectedInputIndex, true );

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
			if (!m_Page.IsLast() && m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage();
			}
			else
			// Previous Button
			if (!m_Page.IsFirst() && m_PreviousButtonRectangle.Contains( touchX, touchY ))
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

				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						if ( gRDEeprom.Set_Input[ 0 ] == INP_0V_UNIT_STOP )
						{
							CLKTS::Pir_Strategy = true;
							CLKTS::Pir_Strategy_Counter = millis();
							CLKTS::WritePowerOn( CLFormOption_ShowWriteMesssages_Error, CLKTSPowerMode_Off);
						}
						else
						{
							CLKTS::Pir_Strategy = false;
						}
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
			}
			else
			// Input1 Button
			if (m_Input1ButtonRectangle.Contains( touchX, touchY ) && m_SelectedInputIndex != 0)
			{
				CLLCDCommon::WaitButton( m_Input1ButtonRectangle );
				SelectInput( 0, true );
			}
			else
			// Input2 Button
			if (m_Input2ButtonRectangle.Contains( touchX, touchY ) && m_SelectedInputIndex != 1)
			{
				CLLCDCommon::WaitButton( m_Input2ButtonRectangle );
				SelectInput( 1, true );
			}
			else
			if (m_Page.GetValue() == 0)
			{
				// Disable Button
				if (m_DisableButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_DisableButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_DISABLE );
				}
				else
				// 0VUnitStop Button
				if (m_0VUnitStopButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_0VUnitStopButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_0V_UNIT_STOP );
				}
				else
				// 10VUnitStop Button
				if (m_10VUnitStopButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_10VUnitStopButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_UNIT_STOP );
				}
				else
				// RegAirFlow Button
				if (m_RegAirFlowButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_RegAirFlowButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_REG_AIR_FLOW );
				}
				else
				// 0VBypassOpen Button
				if (m_0VBypassOpenButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_0VBypassOpenButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_0V_BYPASS_OPEN );
				}
				else
				// 12VBypassOpen Button
				if (m_10VBypassOpenButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_10VBypassOpenButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_BYPASS_OPEN );
				}
				else
					WaitForTouchRelease();
			}
			else
			if (m_Page.GetValue() == 1)
			{
				// FireNoFan Button
				if (m_FireNoFanButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FireNoFanButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_ALM_FIRE_UNIT_STOP );
				}
				else
#if FIREALARM_ALL_CONFIGURATION == 1
				// FireMaxFan Button
				if (m_FireMaxFanButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FireMaxFanButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_ALM_FIRE_VENT_MAX );
				}
				else
				// OnlyFanExtract Button
				if (m_FireOnlyFanExtractButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FireOnlyFanExtractButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_ALM_FIRE_ONLY_EXTRACT );
				}
				else
				// OnlyFanSupply Button
				if (m_FireOnlyFanSupplyButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_FireOnlyFanSupplyButtonRectangle );
					SetInput( m_SelectedInputIndex, INP_12V_ALM_FIRE_ONLY_SUPPLY );
				}
				else
#endif
					WaitForTouchRelease();
			}
			else
				WaitForTouchRelease();
		}

		if (m_Page.GetValue() == 0)
			RenderInputMeasure( false );
    }

	return formResult;
}

bool CLInputConfigForm::Save( unsigned short options )
{
	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Se non e' andata a buon fine, message + home
	if (!Input_Write( m_SetInputs[ 0 ], m_SetInputs[ 1 ] ))
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

void CLInputConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_INPUT_CONFIG ),
		&m_Page );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Tasto Previous
	CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
		(m_Page.IsFirst() ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont) );

	// Tasto Next
	CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
		(m_Page.IsLast() ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont) );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	// Data Frame
	CLGraphics::DrawBox( CLRectangle( CLInputConfigForm_DataFrameRectangle ), 
		GenericForm_Group_Style );

	switch (m_Page.GetValue())
	{
		case 0:
			CLGraphics::DrawText( CLInputConfigForm_UnitTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_UNIT ) );

			CLGraphics::DrawText( CLInputConfigForm_BPDTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLFixedText_BPD );

			break;

		case 1:
			CLGraphics::DrawText( CLInputConfigForm_FireAlarmTitleTextPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_FIREALARM_FIRE_ALARM ), CLInputConfigForm_FireAlarmTitleTextLength );
			break;
	}
	RenderInputButtons();
	SelectInput( m_SelectedInputIndex, false );
}

void CLInputConfigForm::RenderInputButtons()
{
	CLLCDCommon::DrawGenericButton( m_Input1ButtonRectangle,
		(m_SelectedInputIndex == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		"1" );
	CLLCDCommon::DrawGenericButton( m_Input2ButtonRectangle,
		(m_SelectedInputIndex == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		"2" );
}

void CLInputConfigForm::RenderInputConfigButtons()
{
	CLLCDCommon::DrawGenericButton( m_DisableButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_DISABLE ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_DISABLE ) );
	
	CLLCDCommon::DrawGenericButton( m_0VUnitStopButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_0V_UNIT_STOP ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_INPUT_CONFIG_0V_STOP ) );

	CLLCDCommon::DrawGenericButton( m_10VUnitStopButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_UNIT_STOP ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_INPUT_CONFIG_10V_STOP ) );

	CLLCDCommon::DrawGenericButton( m_0VBypassOpenButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_0V_BYPASS_OPEN ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_INPUT_CONFIG_0V_OPEN ) );

	CLLCDCommon::DrawGenericButton( m_10VBypassOpenButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_BYPASS_OPEN ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_INPUT_CONFIG_10V_OPEN ) );

	CLLCDCommon::DrawGenericButton( m_RegAirFlowButtonRectangle,
		(m_SetInputs[ m_SelectedInputIndex ] == INP_REG_AIR_FLOW ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
		CLLocalitation::GetText( CLTextId_INPUT_CONFIG_REG_AIR_FLOW ) );
}

void CLInputConfigForm::RenderInputMeasure( bool forceRefresh )
{
	byte		value			= (m_SelectedInputIndex == 0 ? gKTSData.InputMeasure1 : gKTSData.InputMeasure2);
	RGBColor	barColor		= (value < 50 ? 0xE0E0E0 : InputMeausure_ProgressBar_Color_BarTrue);
	short		inputMeasure	= (m_SelectedInputIndex == 0 ? (int) gKTSData.InputMeasure1 : (int) gKTSData.InputMeasure2);

	if (m_CurrentPowerON != gRDEeprom.Set_Power_ON || m_SaveInputMeasures[ m_SelectedInputIndex ] != inputMeasure || forceRefresh)
	{
		char	text[ 10 ];

		sprintf( text, "%d%%", inputMeasure );

		CLGraphics::DrawText( CLInputConfigForm_InputMeasureTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			text, 4 );

		m_SaveInputMeasures[ m_SelectedInputIndex ]	= inputMeasure;

		CLGraphics::DrawProgressBar( m_RegAirFlowProgressBarRectangle, CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Min,
			InputMeausure_ProgressBar_Color_Background,
			InputMeausure_ProgressBar_Color_BarFalse, (gRDEeprom.Set_Power_ON == CLKTSPowerMode_Off ? InputMeausure_ProgressBar_Color_PowerOff_BarTrue : InputMeausure_ProgressBar_Color_BarTrue),
			0, 100, value,
			4, 2 );

		m_CurrentPowerON	= gRDEeprom.Set_Power_ON;
	}
}

void CLInputConfigForm::SetInput( byte index, byte value )
{
	m_SetInputs[ index ]	= value;

	if (GetState() == CLState_Running)
	{
		switch (m_Page.GetValue())
		{
			case 0:
				RenderInputConfigButtons();
				break;

			case 1:
				RenderFireConfigButtons();
				break;
		}
	}
}

void CLInputConfigForm::SelectInput( byte index, bool focusSelectedPage )
{
	m_SelectedInputIndex	= index;

	if (GetState() == CLState_Running)
	{
		if (focusSelectedPage)
		{
			switch (m_SetInputs[ m_SelectedInputIndex ])
			{
				case INP_12V_ALM_FIRE_UNIT_STOP:
				case INP_12V_ALM_FIRE_ONLY_SUPPLY:
				case INP_12V_ALM_FIRE_ONLY_EXTRACT:
				case INP_12V_ALM_FIRE_VENT_MAX:
					m_Page.Go( 1 );
					RenderPage();
					return;

				default:
					m_Page.Go( 0 );
					RenderPage();
					return;
			}
		}

		switch (m_Page.GetValue())
		{
			case 0:
				RenderInputConfigButtons();
				RenderInputMeasure( true );
				break;

			case 1:
				RenderFireConfigButtons();
				break;
		}
	}
}

void CLInputConfigForm::RenderFireConfigButtons()
{
	CLGraphics::DrawBox( m_FireNoFanButtonRectangle,
		CLGraphicStyleOptions_BorderRound_Yes,
		RGBColor_Black, (m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_UNIT_STOP ? 2 : 1),
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_UNIT_STOP ? RGBColor_Green : 0x808080) );
	CLLCDCommon::RenderFireConfiguration( m_FireNoFanButtonRectangle, INP_12V_ALM_FIRE_UNIT_STOP );

#if FIREALARM_ALL_CONFIGURATION == 1

	CLGraphics::DrawBox( m_FireMaxFanButtonRectangle,
		CLGraphicStyleOptions_BorderRound_Yes,
		RGBColor_Black, (m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_VENT_MAX ? 2 : 1),
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_VENT_MAX ? RGBColor_Green : 0x808080) );
	CLLCDCommon::RenderFireConfiguration( m_FireMaxFanButtonRectangle, INP_12V_ALM_FIRE_VENT_MAX );

	CLGraphics::DrawBox( m_FireOnlyFanExtractButtonRectangle,
		CLGraphicStyleOptions_BorderRound_Yes,
		RGBColor_Black, (m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_ONLY_EXTRACT ? 2 : 1),
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_ONLY_EXTRACT ? RGBColor_Green : 0x808080) );
	CLLCDCommon::RenderFireConfiguration( m_FireOnlyFanExtractButtonRectangle, INP_12V_ALM_FIRE_ONLY_EXTRACT );

	CLGraphics::DrawBox( m_FireOnlyFanSupplyButtonRectangle,
		CLGraphicStyleOptions_BorderRound_Yes,
		RGBColor_Black, (m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_ONLY_SUPPLY ? 2 : 1),
		(m_SetInputs[ m_SelectedInputIndex ] == INP_12V_ALM_FIRE_ONLY_SUPPLY ? RGBColor_Green : 0x808080) );
	CLLCDCommon::RenderFireConfiguration( m_FireOnlyFanSupplyButtonRectangle, INP_12V_ALM_FIRE_ONLY_SUPPLY );

#endif
}
// -----------------------------------------------------------------------------
// CLInputConfigForm [class]
// =============================================================================

