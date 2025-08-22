#include "CLWeeklyDaysEditForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLMessageBoxForm.h"
#include "CLWeeklyMainForm.h"
#include "CLSpeedMode.h"
#include "CLWeekly.h"
#include "CLFranceTX.h"
#include "CLImages.h"

const RGBColor WeeklySelectionTime_ProgressBar_Color_BarTrue	= RGBColor_White;
const RGBColor WeeklySelectionTime_ProgressBar_Color_BarFalse	= RGBColor_Black;
const RGBColor WeeklySelectionTime_ProgressBar_Color_Background	= RGBColor_Black;

#define	CLWeeklyDaysEditForm_MainTitleRectangle					1, 1, 192, 20
#define	CLWeeklyDaysEditForm_SelectedDaysPoint					201, 2
#define	CLWeeklyDaysEditForm_StepFrameRectangle					8, 34, 311, 93
#define	CLWeeklyDaysEditForm_StepRectangle						8, 26, 311, 93
#define	CLWeeklyDaysEditForm_HoursAxisPoint						16, 155
#define	CLWeeklyDaysEditForm_HoursAxisRectangle					11, 155, 318, 172
#define	CLWeeklyDaysEditForm_HoursProgressBarRectangle			16, 99, 303, 152

// Step RangeCount
#define	CLWeeklyDaysEditForm_Step_RangeCount_TitlePoint				20, 26
#define	CLWeeklyDaysEditForm_Step_RangeCount_TextValuePoint			20, 60
#define	CLWeeklyDaysEditForm_Step_RangeCount_TextValueLength		4
#define	CLWeeklyDaysEditForm_Step_RangeCount_UpButtonRectangle		265, 48, 304, 87
#define	CLWeeklyDaysEditForm_Step_RangeCount_DownButtonRectangle	211, 48, 250, 87

// Step StartTime
#define	CLWeeklyDaysEditForm_Step_StartTime_TitlePoint			20, 26
#define	CLWeeklyDaysEditForm_Step_StartTime_TextValuePoint		20, 60
#define	CLWeeklyDaysEditForm_Step_StartTime_TextValueLength		11
#define	CLWeeklyDaysEditForm_Step_StartTime_UpButtonRectangle	265, 48, 304, 87
#define	CLWeeklyDaysEditForm_Step_StartTime_DownButtonRectangle	211, 48, 250, 87

// Step EndTime
#define	CLWeeklyDaysEditForm_Step_EndTime_TitlePoint			20, 26
#define	CLWeeklyDaysEditForm_Step_EndTime_TextValuePoint		20, 60
#define	CLWeeklyDaysEditForm_Step_EndTime_TextValueLength		11
#define	CLWeeklyDaysEditForm_Step_EndTime_UpButtonRectangle		265, 48, 304, 87
#define	CLWeeklyDaysEditForm_Step_EndTime_DownButtonRectangle	211, 48, 250, 87

// Step AirFlow
#define	CLWeeklyDaysEditForm_Step_AirFlow_TitlePoint						20, 26
#define	CLWeeklyDaysEditForm_Step_AirFlow_TextValuePoint					20, 60
#define	CLWeeklyDaysEditForm_Step_AirFlow_TextValueLength					9
#define	CLWeeklyDaysEditForm_Step_AirFlow_FranceTx_TMinusButtonRectangle	176, 48, 235, 87
#define	CLWeeklyDaysEditForm_Step_AirFlow_FranceTx_TPlusButtonRectangle		246, 48, 305, 87
#define	CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button1Rectangle		166, 48, 205, 87
#define	CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button2Rectangle		216, 48, 255, 87
#define	CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button3Rectangle		266, 48, 305, 87

// Step Unbalance
#define	CLWeeklyDaysEditForm_Step_Unbalance_TitlePoint						20, 26
#define	CLWeeklyDaysEditForm_Step_Unbalance_OnOffButtonRectangle			20, 48, 74, 87
#define	CLWeeklyDaysEditForm_Step_Unbalance_SupplyTextPoint					84, 48
#define	CLWeeklyDaysEditForm_Step_Unbalance_SupplyProgressBarRectangle		136, 48, 190, 63
#define	CLWeeklyDaysEditForm_Step_Unbalance_ExtractProgressBarRectangle		191, 48, 245, 63
#define	CLWeeklyDaysEditForm_Step_Unbalance_ExtractTextPoint				250, 50
#define	CLWeeklyDaysEditForm_Step_Unbalance_TextValuePoint					84, 70
#define	CLWeeklyDaysEditForm_Step_Unbalance_TextValueLength					14

// Step Temperature
#define	CLWeeklyDaysEditForm_Step_Temperature_TitlePoint					20, 26
#define	CLWeeklyDaysEditForm_Step_Temperature_TextValuePoint				20, 60
#define	CLWeeklyDaysEditForm_Step_Temperature_TextValueLength				11
#define	CLWeeklyDaysEditForm_Step_Temperature_Button1Rectangle				217, 48, 256, 87
#define	CLWeeklyDaysEditForm_Step_Temperature_Button2Rectangle				265, 48, 304, 87

CLFormResult CLWeeklyDaysEditForm_Open( unsigned short options,
	SDAYPROG* days, byte selectedDays )
{
	CLWeeklyDaysEditForm	form;

	return form.Open( options,
		days, selectedDays );
}

// =============================================================================
// CLWeeklyDaysEditForm [class]
// -----------------------------------------------------------------------------
CLWeeklyDaysEditForm::CLWeeklyDaysEditForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_HoursProgressBarRectangle.Set( CLWeeklyDaysEditForm_HoursProgressBarRectangle );
	m_HoursBarSize	= (float) m_HoursProgressBarRectangle.GetWidth() / (float) 48;
}

CLFormResult CLWeeklyDaysEditForm::Open( unsigned short options,
	SDAYPROG* days, byte selectedDays )
{
	int				touchX, touchY;
	CLFormResult	formResult;
	short			firstDay	= -1;

	m_SelectedDays	= selectedDays;
	m_CurrentRange	= 0;
	m_CurrentStep	= CLStepId_SelectRangeCount;
	if (m_Day.numRange < 1 || m_Day.numRange > 4)
		m_Day.numRange	= 1;

	// Ricerca il primo day tra quelli selezionati
	for (int daysCounter = 0; daysCounter < 7; daysCounter++)
	{
		if (selectedDays & (1 << daysCounter))
		{
			firstDay	= daysCounter;
			break;
		}
	}

	if (firstDay == -1)
		return CLFormResult_None;

	// Inizializza i dati
	SetState( CLState_Initializing );
	memcpy( &m_Day, &days[ firstDay ], sizeof(SDAYPROG) );
	SetRangeCount( m_Day.numRange );
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();
	SelectRangeCount();

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

				if (m_CurrentStep == CLStepId_SelectUnbalance)
				{
					SelectTemperature();
				}
				else
				if (m_CurrentStep == CLStepId_SelectTemperature)
				{
					SelectAirFlow();
				}
				else
				if (m_CurrentStep == CLStepId_SelectAirFlow)
				{
					SelectEndTime();
				}
				else
				if (m_CurrentStep == CLStepId_SelectEndTime)
				{
					SelectStartTime();
				}
				else
				if (m_CurrentStep == CLStepId_SelectStartTime)
				{
					if (m_CurrentRange == 0)
					{
						SelectRangeCount();
					}
					else
					{
						m_CurrentRange--;
						SelectUnbalance();
					}
				}
				else
				if (m_CurrentStep == CLStepId_SelectRangeCount)
				{
					formResult	= CLFormResult_Back;
					break;
				}
			}
			else
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OkButtonRectangle );

				if (m_CurrentStep == CLStepId_SelectRangeCount)
				{
					m_CurrentRange	= 0;
					SelectStartTime();
				}
				else
				if (m_CurrentStep == CLStepId_SelectStartTime)
				{
					SelectEndTime();
				}
				else
				if (m_CurrentStep == CLStepId_SelectEndTime)
				{
					SelectAirFlow();
				}
				else
				if (m_CurrentStep == CLStepId_SelectAirFlow)
				{
					SelectTemperature();
				}
				else
				if (m_CurrentStep == CLStepId_SelectTemperature)
				{
					SelectUnbalance();
				}
				else
				if (m_CurrentStep == CLStepId_SelectUnbalance)
				{
					if (m_CurrentRange < m_Day.numRange - 1)
					{
						m_CurrentRange++;
						SelectStartTime();
					}
					else
					{
						// Imposta i nuovi dati
						for (int daysCounter = 0; daysCounter < 7; daysCounter++)
						{
							if (!(m_SelectedDays & (1 << daysCounter)))
								continue;

							memcpy( &days[ daysCounter ], &m_Day, sizeof(SDAYPROG) );
						}
						formResult	= CLFormResult_Ok;
						break;
					}
				}
			}
			else
			// Step Select RangeCount
			if (m_CurrentStep == CLStepId_SelectRangeCount)
			{
				if (m_StepButtonRectangle1.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle1 );

					while (Touched() != 0)
					{
						SetRangeCount( m_Day.numRange + 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( 150 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle1 );
				}
				else
				if (m_StepButtonRectangle2.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle2 );

					while (Touched() != 0)
					{
						SetRangeCount( m_Day.numRange - 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( 150 );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle2 );
				}
				else
					WaitForTouchRelease();
			}
			else
			// Step Select StartTime
			if (m_CurrentStep == CLStepId_SelectStartTime)
			{
				if (m_StepButtonRectangle1.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle1 );

					while (Touched() != 0)
					{
						SetStartTime( m_CurrentRange, m_Day.timeON[ m_CurrentRange ] + 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle1 );
				}
				else
				if (m_StepButtonRectangle2.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle2 );

					while (Touched() != 0)
					{
						SetStartTime( m_CurrentRange, (m_Day.timeON[ m_CurrentRange ] ? m_Day.timeON[ m_CurrentRange ] - 1 : 0) );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle2 );
				}
				else
					WaitForTouchRelease();
			}
			else
			// Step Select EndTime
			if (m_CurrentStep == CLStepId_SelectEndTime)
			{
				if (m_StepButtonRectangle1.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle1 );

					while (Touched() != 0)
					{
						SetEndTime( m_CurrentRange, m_Day.timeOFF[ m_CurrentRange ] + 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle1 );
				}
				else
				if (m_StepButtonRectangle2.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton_Pressed( m_StepButtonRectangle2 );

					while (Touched() != 0)
					{
						SetEndTime( m_CurrentRange, m_Day.timeOFF[ m_CurrentRange ] - 1 );
						CLKTS::Process();
						CLKTS::Pir_Process();
						delay( UpDownButtons_Delay );
					}

					CLLCDCommon::WaitButton_Unpressed( m_StepButtonRectangle2 );
				}
				else
					WaitForTouchRelease();
			}
			else
			// Step Select AirFlow
			if (m_CurrentStep == CLStepId_SelectAirFlow)
			{
				switch (SpeedMode_GetType())
				{
#ifdef FRANCETX_ENABLED
					case CLSpeedModeType_FranceTx:
						if (m_StepButtonRectangle1.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_StepButtonRectangle1 );
							SetAirFlow_FranceTx( m_CurrentRange, 0 );
						}
						else
						if (m_StepButtonRectangle2.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_StepButtonRectangle2 );
							SetAirFlow_FranceTx( m_CurrentRange, 1 );
						}
						else
							WaitForTouchRelease();
						break;
#endif
					default:
						if (m_StepButtonRectangle1.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_StepButtonRectangle1 );
							SetAirFlow_ThreeSpeed( m_CurrentRange, 0 );
						}
						else
						if (m_StepButtonRectangle2.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_StepButtonRectangle2 );
							SetAirFlow_ThreeSpeed( m_CurrentRange, 1 );
						}
						else
						if (m_StepButtonRectangle3.Contains( touchX, touchY ))
						{
							CLLCDCommon::WaitButton( m_StepButtonRectangle3 );
							SetAirFlow_ThreeSpeed( m_CurrentRange, 2 );
						}
						else
							WaitForTouchRelease();
						break;
				}
			}
			else
			// Step Select Temperature
			if (m_CurrentStep == CLStepId_SelectTemperature)
			{
				if (m_StepButtonRectangle1.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_StepButtonRectangle1 );
					SetTemperature( m_CurrentRange, 0 );
				}
				else
				if (m_StepButtonRectangle2.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_StepButtonRectangle2 );
					SetTemperature( m_CurrentRange, 1 );
				}
				else
					WaitForTouchRelease();
			}
			else
			// Step Select Unbalance
			if (m_CurrentStep == CLStepId_SelectUnbalance)
			{
				if (m_StepButtonRectangle1.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_StepButtonRectangle1 );
					SetUnbalance( m_CurrentRange, GET2BITVALUE( m_Day.ConfigImbal, m_CurrentRange ) ? 0 : 1 );
				}
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLWeeklyDaysEditForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Render SelectedDays
	CLWeeklySupport::RenderSelectedDays( CLWeeklyDaysEditForm_SelectedDaysPoint, m_SelectedDays );

	RenderStep();
	RenderAllTimeProgressBar();
}

void CLWeeklyDaysEditForm::RenderStep_StaticObject()
{
	char	text[ 40 ];

	// Draw Step Frame
	CLGraphics::DrawBox( CLRectangle( CLWeeklyDaysEditForm_StepRectangle ), CLGraphicStyleOptions_Default,
		RGBColor_Black );
	CLGraphics::DrawBox( CLRectangle( CLWeeklyDaysEditForm_StepFrameRectangle ),
		GenericForm_Group_Style );

	// Display Title
	if (m_CurrentStep != CLStepId_SelectRangeCount)
	{
		sprintf( text, "%s %d",
			CLLocalitation::GetText( CLTextId_SET_RANGE ),
			m_CurrentRange + 1 );
	}
	else
		text[ 0 ]	= '\0';

	CLGraphics::DrawBoxWithText( CLRectangle( CLWeeklyDaysEditForm_MainTitleRectangle ),
		GenericForm_Title_BigFont_Style,
		text );

	// Render/Clear HoursAxis
	if (m_CurrentStep != CLStepId_SelectRangeCount)
	{
		CLWeeklySupport::RenderHoursAxis( CLWeeklyDaysEditForm_HoursAxisPoint,
			RGBColor_Black, RGBColor_White );
	}
	else
	{
		CLGraphics::DrawBox( CLRectangle( CLWeeklyDaysEditForm_HoursAxisRectangle ), CLGraphicStyleOptions_Default,
			RGBColor_Black );
	}

	switch (m_CurrentStep)
	{
		case CLStepId_SelectRangeCount:

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_RangeCount_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_SET_NBR_OF_RANGES ) );

			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1, GenericButtonStyle_Normal_UpDown,
				&UpMonoImage );
			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle2, GenericButtonStyle_Normal_UpDown,
				&DownMonoImage );
			break;

		case CLStepId_SelectStartTime:

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_StartTime_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_START_TIME ) );

			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1, GenericButtonStyle_Normal_UpDown,
				&UpMonoImage );
			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle2, GenericButtonStyle_Normal_UpDown,
				&DownMonoImage );
			break;

		case CLStepId_SelectEndTime:
			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_EndTime_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_END_TIME ) );

			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1, GenericButtonStyle_Normal_UpDown,
				&UpMonoImage );
			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle2, GenericButtonStyle_Normal_UpDown,
				&DownMonoImage );
			break;

		case CLStepId_SelectAirFlow:

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_AirFlow_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_AIR_FLOW ) );
			break;

		case CLStepId_SelectTemperature:
			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Temperature_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_TEMPERATURE ) );
			break;

		case CLStepId_SelectUnbalance:
			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Unbalance_TitlePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				CLLocalitation::GetText( CLTextId_UNBALANCE_AIRFLOW ) );

			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Unbalance_SupplyTextPoint, CLGraphicStyleOptions_Font_Small,
				Temperature_Cold_Color, RGBColor_White,
				CLLocalitation::GetText( CLTextId_SUPPLY ), 6 );
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Unbalance_ExtractTextPoint, CLGraphicStyleOptions_Font_Small,
				Temperature_Hot_Color, RGBColor_White,
				CLLocalitation::GetText( CLTextId_EXTRACT ), 7 );
			break;
	}
}

void CLWeeklyDaysEditForm::RenderStep_DynamicObject()
{
	char	text[ 40 ];

	switch (m_CurrentStep)
	{
		case CLStepId_SelectRangeCount:
			sprintf( text, "%d", m_Day.numRange );

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_RangeCount_TextValuePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				text, CLWeeklyDaysEditForm_Step_RangeCount_TextValueLength );
			break;

		case CLStepId_SelectStartTime:
			Weekly_GetTextStartTime( text, &m_Day, m_CurrentRange );

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_StartTime_TextValuePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				text, CLWeeklyDaysEditForm_Step_StartTime_TextValueLength );

			RenderTimeProgressBar( m_CurrentRange );
			break;

		case CLStepId_SelectEndTime:
			Weekly_GetTextEndTime( text, &m_Day, m_CurrentRange  );

			// Draw Step Title
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_EndTime_TextValuePoint, CLGraphicStyleOptions_Font_Big,
				GenericForm_Title_BigFont_Style.BackgroundColor, GenericForm_Title_BigFont_Style.ForegroundColor,
				text, CLWeeklyDaysEditForm_Step_EndTime_TextValueLength );

			RenderTimeProgressBar( m_CurrentRange );
			break;

		case CLStepId_SelectAirFlow:

			switch (SpeedMode_GetType())
			{
#ifdef FRANCETX_ENABLED
				case CLSpeedModeType_FranceTx:
				{
					byte	classIndex;

					FranceTx_DecodeState( FranceTx_GetState(), &classIndex );

					CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1,
						(GET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange ) == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
						 FranceTx_GetText( text, classIndex, 0 ) );

					CLLCDCommon::DrawGenericButton( m_StepButtonRectangle2,
						(GET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange ) == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
						FranceTx_GetText( text, classIndex, 1 ) );
					break;
				}
#endif
				default:
				{
					byte	value	= GET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange );

					CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1,
						(value == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
						 "1" );
					CLLCDCommon::DrawGenericButton( m_StepButtonRectangle2,
						(value == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
						 "2" );
					CLLCDCommon::DrawGenericButton( m_StepButtonRectangle3,
						(value == 2 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
						 "3" );
					break;
				}
				break;
			}

			Weekly_GetTextAirFlowSpeed( text, &m_Day, m_CurrentRange, true );
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_AirFlow_TextValuePoint, (VentilationControl_Get() == CLVentilationControl_CAF ? CLGraphicStyleOptions_Font_Small : CLGraphicStyleOptions_Font_Big),
				RGBColor_Black, RGBColor_White,
				text, CLWeeklyDaysEditForm_Step_AirFlow_TextValueLength );

			RenderTimeProgressBar( m_CurrentRange );
			break;

		case CLStepId_SelectTemperature:
		{
			byte	value	= GET2BITVALUE( m_Day.ConfigTemp, m_CurrentRange );

			// Draw Sun Temperature Button 
			CLGraphics::DrawBox( m_StepButtonRectangle1,
				(value == 0 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont) );
			CLGraphics::Draw( m_StepButtonRectangle1, CLGraphicStyleOptions_HVAlign_Center,
				&SunMonoImage, (value == 0 ? GenericButtonStyle_Selected_BigFont.BackgroundColor : GenericButtonStyle_Normal_BigFont.BackgroundColor), (value == 0 ? RGBColor_White : RGBColor_SunIcon_Pen) );

			// Draw Moon Temperature Button 
			CLGraphics::DrawBox( m_StepButtonRectangle2,
				(value == 1 ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont) );
			CLGraphics::Draw( m_StepButtonRectangle2, CLGraphicStyleOptions_HVAlign_Center,
				&MoonMonoImage, (value == 1 ? GenericButtonStyle_Selected_BigFont.BackgroundColor : GenericButtonStyle_Normal_BigFont.BackgroundColor), (value == 1 ? RGBColor_White : RGBColor_MoonIcon_Pen) );

			// Draw Temperature Text
			Weekly_GetTextTemperature( text, &m_Day, m_CurrentRange );
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Temperature_TextValuePoint, CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, CLWeeklyDaysEditForm_Step_Temperature_TextValueLength );
			break;
		}

		case CLStepId_SelectUnbalance:
		{
			byte	value	= GET2BITVALUE( m_Day.ConfigImbal, m_CurrentRange );

			CLLCDCommon::DrawGenericButton( m_StepButtonRectangle1,
				value == 0 ? GenericButtonStyle_Off_BigFont : GenericButtonStyle_On_BigFont,
				value == 0 ? CLFixedText_OFF : CLFixedText_ON );

			Weekly_GetTextUnbalance( text, &m_Day, m_CurrentRange );
			CLGraphics::DrawText( CLWeeklyDaysEditForm_Step_Unbalance_TextValuePoint, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center,
				RGBColor_Black, RGBColor_White,
				text, CLWeeklyDaysEditForm_Step_Unbalance_TextValueLength );

			CLGraphics::DrawProgressBar( CLRectangle( CLWeeklyDaysEditForm_Step_Unbalance_SupplyProgressBarRectangle ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Max,
				TemperatureCold_ProgressBar_Color_Background, TemperatureCold_ProgressBar_Color_BarFalse, TemperatureCold_ProgressBar_Color_BarTrue,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] > 0 ? gRDEeprom.Set_Imbalance[ 0 ] : 0),
				2, 1 );
			CLGraphics::DrawProgressBar( CLRectangle( CLWeeklyDaysEditForm_Step_Unbalance_ExtractProgressBarRectangle ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_BarShape_Progressive | CLDrawBarOptions_StartWith_Min,
				TemperatureHot_ProgressBar_Color_Background, TemperatureHot_ProgressBar_Color_BarFalse, TemperatureHot_ProgressBar_Color_BarTrue,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] < 0 ? abs( gRDEeprom.Set_Imbalance[ 0 ] ) : 0),
				2, 1 );
			break;
		}
	}
}

void CLWeeklyDaysEditForm::RenderStep()
{
	RenderStep_StaticObject();
	RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::RenderAllTimeProgressBar()
{
	CLGraphics::DrawBox( m_HoursProgressBarRectangle, CLGraphicStyleOptions_Default,
		RGBColor_Black );

	if (m_CurrentStep != CLStepId_SelectRangeCount)
	{
		for (byte rangesCounter = 0; rangesCounter <= m_CurrentRange; rangesCounter++)
			RenderTimeProgressBar( rangesCounter );
	}
}

void CLWeeklyDaysEditForm::RenderTimeProgressBar( byte range )
{
	if (range > m_Day.numRange)
		return;

	if (range == m_CurrentRange && (m_CurrentStep == CLStepId_SelectStartTime || m_CurrentStep == CLStepId_SelectEndTime))
	{
		byte		minValue;

		minValue	= (range == 0 ? 0 : m_Day.timeOFF[ range - 1 ]);

		CLGraphics::DrawProgressBarRange( CLRectangle( m_HoursProgressBarRectangle.GetX1() + ((float) minValue * m_HoursBarSize),
			m_HoursProgressBarRectangle.GetY1(),
			m_HoursProgressBarRectangle.GetX2(), m_HoursProgressBarRectangle.GetY2() ),
			CLDrawBarOptions_Direction_Horizontal,
			WeeklySelectionTime_ProgressBar_Color_Background, WeeklySelectionTime_ProgressBar_Color_BarFalse, WeeklySelectionTime_ProgressBar_Color_BarTrue,
			minValue, 48, m_Day.timeON[ range ], (m_CurrentStep == CLStepId_SelectStartTime ? m_Day.timeON[ range ] + 1 : m_Day.timeOFF[ range ]),
			1, 0 );
	}
	else
	{
		short		maxValue;
		RGBColor	barColor	= CLGraphics::AdjustBrightness( WeeklyTime_ProgressBar_Color_BarTrue, -(range * 10) );

		switch (SpeedMode_GetType())
		{
	#ifdef FRANCETX_ENABLED
			case CLSpeedModeType_FranceTx:
				maxValue	= 1;
				break;
	#endif
			default:
				maxValue	= 2;
				break;
		}

		maxValue++;
		CLGraphics::DrawProgressBar( CLRectangle( m_HoursProgressBarRectangle.GetX1() + ((float) m_Day.timeON[ range ] * m_HoursBarSize), m_HoursProgressBarRectangle.GetY1(),
			m_HoursProgressBarRectangle.GetX1() + ((float) (m_Day.timeOFF[ range ]) * m_HoursBarSize), m_HoursProgressBarRectangle.GetY2() ),
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_StartWith_Max,
			WeeklyTime_ProgressBar_Color_Background, WeeklyTime_ProgressBar_Color_BarFalse, barColor,
			0, maxValue, GET2BITVALUE( m_Day.ConfigSpeed, range ) + 1,
			4, 1 );
	}
}

void CLWeeklyDaysEditForm::SelectStartTime()
{
	m_CurrentStep	= CLStepId_SelectStartTime;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_StartTime_UpButtonRectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_StartTime_DownButtonRectangle );

	SetStartTime( m_CurrentRange, m_Day.timeON[ m_CurrentRange ] );
	RenderStep();
	RenderAllTimeProgressBar();
}

void CLWeeklyDaysEditForm::SetStartTime( byte range, byte value )
{
	byte	minValue;
	byte	maxValue;

	if (range >= m_Day.numRange)
		return;

	minValue	= (range == 0 ? 0 : m_Day.timeOFF[ range - 1 ]);
	maxValue	= 48 - (m_Day.numRange - range);

	if (value < minValue)
		value	= minValue;
	else
	if (value > maxValue)
		value	= maxValue;

	m_Day.timeON[ range ]	= value;
	if (range == m_CurrentRange)
		RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::SelectEndTime()
{
	m_CurrentStep	= CLStepId_SelectEndTime;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_EndTime_UpButtonRectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_EndTime_DownButtonRectangle );

	SetEndTime( m_CurrentRange, m_Day.timeOFF[ m_CurrentRange ] );
	RenderStep();
	RenderAllTimeProgressBar();
}

void CLWeeklyDaysEditForm::SetEndTime( byte range, byte value )
{
	byte	minValue;
	byte	maxValue;

	if (range >= m_Day.numRange)
		return;

	minValue	= m_Day.timeON[ range ] + 1;
	maxValue	= 48 - (m_Day.numRange - (range + 1));

	if (value < minValue)
		value	= minValue;
	else
	if (value > maxValue)
		value	= maxValue;

	m_Day.timeOFF[ range ]	= value;

	if (range == m_CurrentRange)
		RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::SelectAirFlow()
{
	m_CurrentStep	= CLStepId_SelectAirFlow;

	switch (SpeedMode_GetType())
	{
#ifdef FRANCETX_ENABLED
		case CLSpeedModeType_FranceTx:
			SetAirFlow_FranceTx( m_CurrentRange, GET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange ) );
			break;
#endif
		default:
			SetAirFlow_ThreeSpeed( m_CurrentRange, GET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange ) );
	}

	RenderStep();
	RenderAllTimeProgressBar();
}

#ifdef FRANCETX_ENABLED

void CLWeeklyDaysEditForm::SetAirFlow_FranceTx( byte range, byte value )
{
	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_AirFlow_FranceTx_TMinusButtonRectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_AirFlow_FranceTx_TPlusButtonRectangle );

	if (value > 1)
		value	= 1;

	m_Day.ConfigSpeed	= SET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange, value );
	RenderStep_DynamicObject();
}

#endif

void CLWeeklyDaysEditForm::SetAirFlow_ThreeSpeed( byte range, byte value )
{
	if (value > 2)
		value	= 2;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button1Rectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button2Rectangle );
	m_StepButtonRectangle3.Set( CLWeeklyDaysEditForm_Step_AirFlow_ThreeSpeed_Button3Rectangle );

	m_Day.ConfigSpeed	= SET2BITVALUE( m_Day.ConfigSpeed, m_CurrentRange, value );
	RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::SelectTemperature()
{
	m_CurrentStep	= CLStepId_SelectTemperature;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_Temperature_Button1Rectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_Temperature_Button2Rectangle );

	SetTemperature( m_CurrentRange, GET2BITVALUE( m_Day.ConfigTemp, m_CurrentRange ) );
	RenderStep();
}

void CLWeeklyDaysEditForm::SetTemperature( byte range, byte value )
{
	if (value > 1)
		value	= 1;

	m_Day.ConfigTemp	= SET2BITVALUE( m_Day.ConfigTemp, m_CurrentRange, value );
	RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::SelectUnbalance()
{
	m_CurrentStep	= CLStepId_SelectUnbalance;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_Unbalance_OnOffButtonRectangle );

	SetUnbalance( m_CurrentRange, GET2BITVALUE( m_Day.ConfigImbal, m_CurrentRange ) );
	RenderStep();
}

void CLWeeklyDaysEditForm::SetUnbalance( byte range, byte value )
{
	if (value > 2)
		value	= 2;

	m_Day.ConfigImbal	= SET2BITVALUE( m_Day.ConfigImbal, m_CurrentRange, value );

	RenderStep_DynamicObject();
}

void CLWeeklyDaysEditForm::SelectRangeCount()
{
	m_CurrentStep	= CLStepId_SelectRangeCount;

	m_StepButtonRectangle1.Set( CLWeeklyDaysEditForm_Step_RangeCount_UpButtonRectangle );
	m_StepButtonRectangle2.Set( CLWeeklyDaysEditForm_Step_RangeCount_DownButtonRectangle );

	SetRangeCount( m_Day.numRange );
	RenderStep();
	RenderAllTimeProgressBar();
}

void CLWeeklyDaysEditForm::SetRangeCount( byte value )
{
	if (value < 1)
		value	= 1;
	else
	if (value > 4)
		value	= 4;

	m_Day.numRange	= value;
	if (GetState() == CLState_Running)
		RenderStep_DynamicObject();
}
// -----------------------------------------------------------------------------
// CLWeeklyDaysEditForm [class]
// =============================================================================


