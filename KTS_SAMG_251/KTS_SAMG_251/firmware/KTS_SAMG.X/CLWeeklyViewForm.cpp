#include "CLWeeklyViewForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLWeeklyMainForm.h"
#include "CLTouch.h"
#include "CLSpeedMode.h"
#include "CLWeekly.h"

#define	CLWeeklyViewForm_HoursAxisPoint						16, 155
#define	CLWeeklyViewForm_HoursProgressBarRectangle			16, 120, 303, 152
#define	CLWeeklyViewForm_Range1InfoRectangle				15, 22, 87, 114
#define	CLWeeklyViewForm_Range2InfoRectangle				87, 22, 159, 114
#define	CLWeeklyViewForm_Range3InfoRectangle				159, 22, 231, 114
#define	CLWeeklyViewForm_Range4InfoRectangle				231, 22, 303, 114

#define	CLWeeklyViewForm_Range1StartTimeTextPoint			19, 25
#define	CLWeeklyViewForm_Range1StartTimeTextLength			5
#define	CLWeeklyViewForm_Range1EndTimeTextPoint				19, 40
#define	CLWeeklyViewForm_Range1EndTimeTextLength			5
#define	CLWeeklyViewForm_Range1AirFlowSpeedText1Point		19, 55
#define	CLWeeklyViewForm_Range1AirFlowSpeedText1Length		8
#define	CLWeeklyViewForm_Range1AirFlowSpeedText2Point		19, 70
#define	CLWeeklyViewForm_Range1AirFlowSpeedText2Length		8
#define	CLWeeklyViewForm_Range1SupplyUnbalanceRectangle		19, 85, 50, 97
#define	CLWeeklyViewForm_Range1ExtractUnbalanceRectangle	52, 85, 83, 97
#define	CLWeeklyViewForm_Range1UnbalanceTextPoint			19, 99
#define	CLWeeklyViewForm_Range1UnbalanceTextLength			8
#define	CLWeeklyViewForm_Range1TemperatureIconPoint			64, 29

CLFormResult CLWeeklyViewForm_Open( unsigned short options )
{
	CLWeeklyViewForm	form;

	return form.Open( options );
}

// =============================================================================
// CLWeeklyViewForm [class]
// -----------------------------------------------------------------------------
CLWeeklyViewForm::CLWeeklyViewForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_PreviousButtonRectangle.Set( ViewForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( ViewForm_NextButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
}

CLFormResult CLWeeklyViewForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetDay( 0 );
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
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				formResult	= CLFormResult_Ok;
				break;
			}
			else
			// Next Button
			if (m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				SetDay( (m_Day == 6 ? 0 : m_Day + 1) );
			}
			else
			// Previous Button
			if (m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				SetDay( (m_Day == 0 ? 6 : m_Day - 1) );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLWeeklyViewForm::RenderPage()
{
	char		text[ 40 ];
	char		speedValueText[ 15 ];
	char*		speedValueUnit;
	CLRectangle	hoursProgressBarRectangle( CLWeeklyViewForm_HoursProgressBarRectangle );
	CLPoint		startTimeTextOffset( CLWeeklyViewForm_Range1StartTimeTextPoint );
	CLPoint		endTimeTextOffset( CLWeeklyViewForm_Range1EndTimeTextPoint );
	CLPoint		airFlowText1Offset( CLWeeklyViewForm_Range1AirFlowSpeedText1Point );
	CLPoint		airFlowText2Offset( CLWeeklyViewForm_Range1AirFlowSpeedText2Point );
	CLPoint		unbalanceTextOffset( CLWeeklyViewForm_Range1UnbalanceTextPoint );
	CLPoint		temperatureIconOffset( CLWeeklyViewForm_Range1TemperatureIconPoint );
	CLRectangle	range1InfoRectangle( CLWeeklyViewForm_Range1InfoRectangle );
	CLRectangle	supplyUnbalanceRectangle( CLWeeklyViewForm_Range1SupplyUnbalanceRectangle );
	CLRectangle	extractUnbalanceRectangle( CLWeeklyViewForm_Range1ExtractUnbalanceRectangle );
	CLPoint		supplyUnbalanceOffset( supplyUnbalanceRectangle.GetX1(), supplyUnbalanceRectangle.GetY1() );
	CLPoint		extractUnbalanceOffset( extractUnbalanceRectangle.GetX1(), extractUnbalanceRectangle.GetY1() );
	SDAYPROG*	day				= &gRDEeprom.sDayProg[ m_Day ];
	float		hoursBarSize	= (float) hoursProgressBarRectangle.GetWidth() / (float) 48;

	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( Weekly_GetDayName( m_Day ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Next Button
    CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Previous Button
    CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Render HoursAxis
	CLWeeklySupport::RenderHoursAxis( CLWeeklyViewForm_HoursAxisPoint,
		RGBColor_Black, RGBColor_White );

	// Render Range Progress Bars
	for (byte rangesCounter = 0; rangesCounter < day->numRange; rangesCounter++)
	{
		short		maxValue;
		RGBColor	barColor	= CLGraphics::AdjustBrightness( WeeklyTime_ProgressBar_Color_BarTrue, -(rangesCounter * 10) );
		CLRectangle	hourProgressBarRectangle;

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
		hourProgressBarRectangle.Set( hoursProgressBarRectangle.GetX1() + ((float) day->timeON[ rangesCounter ] * hoursBarSize), hoursProgressBarRectangle.GetY1(),
			hoursProgressBarRectangle.GetX1() + ((float) (day->timeOFF[ rangesCounter ]) * hoursBarSize), hoursProgressBarRectangle.GetY2() );
		CLGraphics::DrawProgressBar( hourProgressBarRectangle,
			CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_StartWith_Max,
			WeeklyTime_ProgressBar_Color_Background, WeeklyTime_ProgressBar_Color_BarFalse, barColor,
			0, maxValue, GET2BITVALUE( day->ConfigSpeed, rangesCounter ) + 1,
			1, 0 );

		CLGraphics::DrawBorder( hourProgressBarRectangle, CLGraphicStyleOptions_Default,
			1, RGBColor_White );

		//hourProgressBarRectangle.Set( hourProgressBarRectangle.GetX1() + 1, hourProgressBarRectangle.GetY2() + 2,
		//	hourProgressBarRectangle.GetX2() - 2, hourProgressBarRectangle.GetY2() + 3 );

		//CLGraphics::DrawBox( hourProgressBarRectangle, CLGraphicStyleOptions_BorderRound_No, RGBColor_White );
	}

	startTimeTextOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	endTimeTextOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	airFlowText1Offset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	airFlowText2Offset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	unbalanceTextOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	temperatureIconOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	supplyUnbalanceOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );
	extractUnbalanceOffset.MoveOffset( -range1InfoRectangle.GetX1(), -range1InfoRectangle.GetY1() );

	// Render Range Info
	for (byte rangesCounter = 0; rangesCounter < gRDEeprom.sDayProg[ m_Day ].numRange; rangesCounter++)
	{
		CLRectangle	rangeInfoRectangle;
		
		switch (rangesCounter)
		{
			case 0:
				rangeInfoRectangle.Set( CLWeeklyViewForm_Range1InfoRectangle );
				break;
			case 1:
				rangeInfoRectangle.Set( CLWeeklyViewForm_Range2InfoRectangle );
				break;
			case 2:
				rangeInfoRectangle.Set( CLWeeklyViewForm_Range3InfoRectangle );
				break;
			case 3:
				rangeInfoRectangle.Set( CLWeeklyViewForm_Range4InfoRectangle );
				break;
		}

		// Draw group Box
		CLGraphics::DrawBox( rangeInfoRectangle,
			GenericForm_Group_Style );

		// Draw StartTime
		Weekly_GetTextStartTime( text, day, rangesCounter );
		CLGraphics::DrawText( rangeInfoRectangle.GetX1() + startTimeTextOffset.GetX(), rangeInfoRectangle.GetY1() + startTimeTextOffset.GetY(), CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			text, CLWeeklyViewForm_Range1StartTimeTextLength );

		// Draw EndTime
		Weekly_GetTextEndTime( text, day, rangesCounter );
		CLGraphics::DrawText( rangeInfoRectangle.GetX1() + endTimeTextOffset.GetX(), rangeInfoRectangle.GetY1() + endTimeTextOffset.GetY(), CLGraphicStyleOptions_Font_Small,
			RGBColor_Black, RGBColor_White,
			text, CLWeeklyViewForm_Range1EndTimeTextLength );

		// Draw AirFlow Speed
		Weekly_GetTextAirFlowSpeed( speedValueText, day, rangesCounter, false );
		speedValueUnit	= (char*) CLKTS::GetSpeedMeasureUnit();

		if (strlen( speedValueText ) + strlen( speedValueUnit ) + 1 > CLWeeklyViewForm_Range1AirFlowSpeedText1Length)
		{
			CLGraphics::DrawText( rangeInfoRectangle.GetX1() + airFlowText1Offset.GetX(), rangeInfoRectangle.GetY1() + airFlowText1Offset.GetY(), CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				speedValueText, CLWeeklyViewForm_Range1AirFlowSpeedText1Length );
			CLGraphics::DrawText( rangeInfoRectangle.GetX1() + airFlowText2Offset.GetX(), rangeInfoRectangle.GetY1() + airFlowText2Offset.GetY(), CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				speedValueUnit, CLWeeklyViewForm_Range1AirFlowSpeedText2Length );
		}
		else
		{
			sprintf( text, "%s %s", speedValueText, speedValueUnit );
			CLGraphics::DrawText( rangeInfoRectangle.GetX1() + airFlowText1Offset.GetX(), rangeInfoRectangle.GetY1() + airFlowText1Offset.GetY(), CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, CLWeeklyViewForm_Range1AirFlowSpeedText1Length );
			CLGraphics::DrawText( rangeInfoRectangle.GetX1() + airFlowText2Offset.GetX(), rangeInfoRectangle.GetY1() + airFlowText2Offset.GetY(), CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				"", CLWeeklyViewForm_Range1AirFlowSpeedText2Length );
		}

		// Draw Temperature Icon (Sun/Moon)
		if (GET2BITVALUE( day->ConfigTemp, rangesCounter ) == 0)
			CLLCDCommon::DrawSunIcon( rangeInfoRectangle.GetX1() + temperatureIconOffset.GetX(), rangeInfoRectangle.GetY1() + temperatureIconOffset.GetY(),
				RGBColor_Black, RGBColor_SunIcon_Pen );
		else
			CLLCDCommon::DrawMoonIcon( rangeInfoRectangle.GetX1() + temperatureIconOffset.GetX(), rangeInfoRectangle.GetY1() + temperatureIconOffset.GetY(),
				RGBColor_Black, RGBColor_MoonIcon_Pen );

		// Draw Unbalance
		if (GET2BITVALUE( day->ConfigImbal, rangesCounter ) != 0)
		{
			CLGraphics::DrawProgressBar( CLRectangle( rangeInfoRectangle.GetX1() + supplyUnbalanceOffset.GetX(), rangeInfoRectangle.GetY1() + supplyUnbalanceOffset.GetY(),
				rangeInfoRectangle.GetX1() + supplyUnbalanceOffset.GetX() + supplyUnbalanceRectangle.GetWidth() - 1, rangeInfoRectangle.GetY1() + supplyUnbalanceOffset.GetY() + supplyUnbalanceRectangle.GetHeight() - 1 ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_StartWith_Max,
				TemperatureCold_ProgressBar_Color_Background, TemperatureCold_ProgressBar_Color_BarFalse, TemperatureCold_ProgressBar_Color_BarTrue,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] > 0 ? gRDEeprom.Set_Imbalance[ 0 ] : 0),
				1, 0 );
			CLGraphics::DrawProgressBar( CLRectangle( rangeInfoRectangle.GetX1() + extractUnbalanceOffset.GetX(), rangeInfoRectangle.GetY1() + extractUnbalanceOffset.GetY(),
				rangeInfoRectangle.GetX1() + extractUnbalanceOffset.GetX() + extractUnbalanceRectangle.GetWidth() - 1, rangeInfoRectangle.GetY1() + extractUnbalanceOffset.GetY() + extractUnbalanceRectangle.GetHeight() - 1 ),
				CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_StartWith_Min,
				TemperatureHot_ProgressBar_Color_Background, TemperatureHot_ProgressBar_Color_BarFalse, TemperatureHot_ProgressBar_Color_BarTrue,
				0, 70, (gRDEeprom.Set_Imbalance[ 0 ] < 0 ? abs( gRDEeprom.Set_Imbalance[ 0 ] ) : 0),
				1, 0 );

			Weekly_GetTextUnbalance( text, day, rangesCounter );
			CLGraphics::DrawText( rangeInfoRectangle.GetX1() + unbalanceTextOffset.GetX(), rangeInfoRectangle.GetY1() + unbalanceTextOffset.GetY(), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
				RGBColor_Black, RGBColor_White,
				text, CLWeeklyViewForm_Range1UnbalanceTextLength );
		}
	}

}

void CLWeeklyViewForm::SetDay( byte value )
{
	if (value > 6)
		value	= 6;

	m_Day	 = value;

	if (GetState() == CLState_Running)
		RenderPage();
}
// -----------------------------------------------------------------------------
// CLWeeklyViewForm [class]
// =============================================================================


