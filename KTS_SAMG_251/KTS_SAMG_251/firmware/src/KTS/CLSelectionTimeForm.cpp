#include "CLSelectionTimeForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLImages.h"

#define	CLSelectionTimeForm_HourUpButtonRectangle			55, 61, 94, 100
#define	CLSelectionTimeForm_HourDownButtonRectangle			55, 120, 94, 159
#define	CLSelectionTimeForm_MinuteUpButtonRectangle			136, 61, 175, 100
#define	CLSelectionTimeForm_MinuteDownButtonRectangle		136, 120, 175, 159
#define	CLSelectionTimeForm_SecondUpButtonRectangle			216, 61, 255, 100
#define	CLSelectionTimeForm_SecondDownButtonRectangle		216, 120, 255, 159
#define	CLSelectionTimeForm_TimeTextPoint					60, 34

CLFormResult CLSelectionTimeForm_Open( unsigned short options,
	const char* mainTitle, CLDateTime& time )
{
	CLSelectionTimeForm	form;

	return form.Open( options, mainTitle, time );
}

// =============================================================================
// CLSelectionTimeForm [class]
// -----------------------------------------------------------------------------
CLSelectionTimeForm::CLSelectionTimeForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_HourUpButtonRectangle.Set( CLSelectionTimeForm_HourUpButtonRectangle );
	m_HourDownButtonRectangle.Set( CLSelectionTimeForm_HourDownButtonRectangle );
	m_MinuteUpButtonRectangle.Set( CLSelectionTimeForm_MinuteUpButtonRectangle );
	m_MinuteDownButtonRectangle.Set( CLSelectionTimeForm_MinuteDownButtonRectangle );
	m_SecondUpButtonRectangle.Set( CLSelectionTimeForm_SecondUpButtonRectangle );
	m_SecondDownButtonRectangle.Set( CLSelectionTimeForm_SecondDownButtonRectangle );

	m_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 20, 1 );
}

CLFormResult CLSelectionTimeForm::Open( unsigned short options, const char* mainTitle,
	CLDateTime& time )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( time );
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
				time.Set( m_Value );
				break;
			}
			else
			// HourUp Button
			if (m_HourUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_HourUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetHour( (short) m_Value.GetHour() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_HourUpButtonRectangle );
			}
			else
			// HourDown Button
			if (m_HourDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_HourDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetHour( (short) m_Value.GetHour() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_HourDownButtonRectangle );
			}
			else
			// MinuteUp Button
			if (m_MinuteUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_MinuteUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetMinute( (short) m_Value.GetMinute() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_MinuteUpButtonRectangle );
			}
			else
			// MinuteDown Button
			if (m_MinuteDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_MinuteDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetMinute( (short) m_Value.GetMinute() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_MinuteDownButtonRectangle );
			}
			else
			// SecondUp Button
			if (m_SecondUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_SecondUpButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetSecond( (short) m_Value.GetSecond() + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_SecondUpButtonRectangle );
			}
			else
			// SecondDown Button
			if (m_SecondDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_SecondDownButtonRectangle );

				m_ProgressiveTouchUpDown.Reset();
				while (m_ProgressiveTouchUpDown.InWhile())
				{
					if (m_ProgressiveTouchUpDown.CanIncrement())
						SetSecond( (short) m_Value.GetSecond() - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_SecondDownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLSelectionTimeForm::RenderPage( unsigned short options, const char* mainTitle )
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

	// Hour buttons
	CLLCDCommon::DrawGenericButton( m_HourUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_HourDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	// Minute buttons
	CLLCDCommon::DrawGenericButton( m_MinuteUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_MinuteDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	// Second buttons
	CLLCDCommon::DrawGenericButton( m_SecondUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_SecondDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown,
		&DownMonoImage );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderTime();
}

void CLSelectionTimeForm::RenderTime()
{
	char	text[ 15 ];

	sprintf( text, "%02d : %02d : %02d", m_Value.GetHour(), m_Value.GetMinute(), m_Value.GetSecond() );

	CLGraphics::DrawText( CLSelectionTimeForm_TimeTextPoint, CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black, RGBColor_White,
		text, 12 );
}

void CLSelectionTimeForm::SetValue( CLDateTime value )
{
	m_Value.Set( value );

	if (GetState() == CLState_Running)
		RenderTime();
}

void CLSelectionTimeForm::SetHour( short value )
{
	if (value > 23)
		value	= 0;
	else
	if (value < 0)
		value	= 23;

	CLDateTime	newValue( m_Value );
	newValue.SetHour( value );
	SetValue( newValue );
}

void CLSelectionTimeForm::SetMinute( short value )
{
	if (value > 59)
		value	= 0;
	else
	if (value < 0)
		value	= 59;

	CLDateTime	newValue( m_Value );
	newValue.SetMinute( value );
	SetValue( newValue );
}

void CLSelectionTimeForm::SetSecond( short value )
{
	if (value > 59)
		value	= 0;
	else
	if (value < 0)
		value	= 59;

	CLDateTime	newValue( m_Value );
	newValue.SetSecond( value );
	SetValue( newValue );
}
// -----------------------------------------------------------------------------
// CLSelectionTimeForm [class]
// =============================================================================

