#include "CLSelectionDateForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLSelectionDateForm_DayUpButtonRectangle		40, 61, 79, 100
#define	CLSelectionDateForm_DayDownButtonRectangle		40, 120, 79, 159
#define	CLSelectionDateForm_MonthUpButtonRectangle		123, 61, 162, 100
#define	CLSelectionDateForm_MonthDownButtonRectangle	123, 120, 162, 159
#define	CLSelectionDateForm_YearUpButtonRectangle		217, 61, 256, 100
#define	CLSelectionDateForm_YearDownButtonRectangle		217, 120, 256, 159
#define	CLSelectionDateForm_DateTextPoint				47, 34

CLFormResult CLSelectionDateForm_Open( unsigned short options,
	const char* mainTitle, CLDateTime& date, CLDateTime* minDate, CLDateTime* maxDate )
{
	CLSelectionDateForm	form;

	return form.Open( options, mainTitle, date, minDate, maxDate );
}

// =============================================================================
// CLSelectionDateForm [class]
// -----------------------------------------------------------------------------
CLSelectionDateForm::CLSelectionDateForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_DayUpButtonRectangle.Set( CLSelectionDateForm_DayUpButtonRectangle );
	m_DayDownButtonRectangle.Set( CLSelectionDateForm_DayDownButtonRectangle );
	m_MonthUpButtonRectangle.Set( CLSelectionDateForm_MonthUpButtonRectangle );
	m_MonthDownButtonRectangle.Set( CLSelectionDateForm_MonthDownButtonRectangle );
	m_YearUpButtonRectangle.Set( CLSelectionDateForm_YearUpButtonRectangle );
	m_YearDownButtonRectangle.Set( CLSelectionDateForm_YearDownButtonRectangle );

	m_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 20, 1 );
}

CLFormResult CLSelectionDateForm::Open( unsigned short options, const char* mainTitle,
	CLDateTime& date, CLDateTime* minDate, CLDateTime* maxDate )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_MinValue	= (minDate == NULL ? CLDateTime( 1, 1, 0 ) : *minDate);
	m_MaxValue	= (maxDate == NULL ? CLDateTime( 31, 12, 9000 ) : *maxDate);

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( date );
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage( options, mainTitle );

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage( options, mainTitle );
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (CLFormOption_IsHomeButtonShow( options ) && m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (CLFormOption_IsBackButtonShow( options ) && m_BackButtonRectangle.Contains( touchX, touchY ))
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

				formResult	= CLFormResult_Ok;
				date.Set( m_Value );
				break;
			}
			else
			// DayUp Button
			if (m_DayUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DayUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetDay( (short) m_Value.GetDay() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DayUpButtonRectangle );
			}
			else
			// DayDown Button
			if (m_DayDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_DayDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetDay( (short) m_Value.GetDay() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_DayDownButtonRectangle );
			}
			else
			// MonthUp Button
			if (m_MonthUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_MonthUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetMonth( (short) m_Value.GetMonth() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_MonthUpButtonRectangle );
			}
			else
			// MonthDown Button
			if (m_MonthDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_MonthDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetMonth( (short) m_Value.GetMonth() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_MonthDownButtonRectangle );
			}
			else
			// YearUp Button
			if (m_YearUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_YearUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetYear( (short) m_Value.GetYear() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_YearUpButtonRectangle );
			}
			else
			// YearDown Button
			if (m_YearDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_YearDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetYear( (short) m_Value.GetYear() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_YearDownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLSelectionDateForm::RenderPage( unsigned short options, const char* mainTitle )
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( mainTitle,
		NULL );

	// Display Home Button
	if (CLFormOption_IsHomeButtonShow( options ))
		CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	if (CLFormOption_IsBackButtonShow( options ))
		CLLCDCommon::DrawBackButton( m_BackButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Day buttons
	CLLCDCommon::DrawGenericButton( m_DayUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_DayDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	// Month buttons
	CLLCDCommon::DrawGenericButton( m_MonthUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_MonthDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	// Year buttons
	CLLCDCommon::DrawGenericButton( m_YearUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_YearDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );
	RenderDate();
}

void CLSelectionDateForm::RenderDate()
{
	char	text[ 20 ];

	sprintf( text, "%02d / %02d / %04d", m_Value.GetDay(), m_Value.GetMonth(), m_Value.GetYear() );

	CLGraphics::DrawText( CLSelectionDateForm_DateTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 14 );
}

void CLSelectionDateForm::SetValue( CLDateTime value )
{
	if (value < m_MinValue)
		value	= m_MinValue;
	else
	if (value > m_MaxValue)
		value	= m_MaxValue;

	m_Value.Set( value );

	if (GetState() == CLState_Running)
		RenderDate();
}

void CLSelectionDateForm::SetDay( short value )
{
	if (value > CLDateTime::GetDaysOfMonth( m_Value.GetYear(), m_Value.GetMonth() ))
		value	= 1;
	else
	if (value < 1)
		value	= CLDateTime::GetDaysOfMonth( m_Value.GetYear(), m_Value.GetMonth() );

	CLDateTime	newValue( m_Value );
	newValue.SetDay( value );
	SetValue( newValue );
}

void CLSelectionDateForm::SetMonth( short value )
{
	if (value > 12)
		value	= 1;
	else
	if (value < 1)
		value	= 12;

	CLDateTime	newValue( m_Value );
	newValue.SetMonth( value );
	SetValue( newValue );
}

void CLSelectionDateForm::SetYear( short value )
{
	if (value < 0)
		value	= 0;

	CLDateTime	newValue( m_Value );
	newValue.SetYear( value );
	SetValue( newValue );
}
// -----------------------------------------------------------------------------
// CLSelectionDateForm [class]
// =============================================================================

