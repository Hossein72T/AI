#include "CLWeeklyEditForm.h"

#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLTouch.h"
#include "CLWeeklyDaysEditForm.h"
#include "CLWeekly.h"

#define CLWeeklyEditForm_Day_MondayButtonRectangle		17, 30, 101, 64
#define CLWeeklyEditForm_Day_TwesdayButtonRectangle		117, 30, 201, 64
#define CLWeeklyEditForm_Day_WednesdayButtonRectangle	218, 30, 302, 64
#define CLWeeklyEditForm_Day_ThursdayButtonRectangle	17, 81, 101, 115
#define CLWeeklyEditForm_Day_FridayButtonRectangle		117, 81, 201, 115
#define CLWeeklyEditForm_Day_SaturdayButtonRectangle	218, 81, 302, 115
#define CLWeeklyEditForm_Day_SundayButtonRectangle		218, 133, 302, 167
#define CLWeeklyEditForm_CopyButtonRectangle			0, 137, 89, 176
#define CLWeeklyEditForm_PasteButtonRectangle			98, 137, 194, 176
#define CLWeeklyEditForm_EditButtonRectangle			160, 190, 230, 229
#define CLWeeklyEditForm_Panel1Rectangle				0, 126, 207, 179
#define CLWeeklyEditForm_Panel2Rectangle				0, 127, 206, 179

CLFormResult CLWeeklyEditForm_Open( unsigned short options )
{
	CLWeeklyEditForm	form;

	return form.Open( options );
}

// =============================================================================
// CLWeeklyEditForm [class]
// -----------------------------------------------------------------------------
CLWeeklyEditForm::CLWeeklyEditForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_DaysButtonRectangles[ 0 ].Set( CLWeeklyEditForm_Day_SundayButtonRectangle );
	m_DaysButtonRectangles[ 1 ].Set( CLWeeklyEditForm_Day_MondayButtonRectangle );
	m_DaysButtonRectangles[ 2 ].Set( CLWeeklyEditForm_Day_TwesdayButtonRectangle );
	m_DaysButtonRectangles[ 3 ].Set( CLWeeklyEditForm_Day_WednesdayButtonRectangle );
	m_DaysButtonRectangles[ 4 ].Set( CLWeeklyEditForm_Day_ThursdayButtonRectangle );
	m_DaysButtonRectangles[ 5 ].Set( CLWeeklyEditForm_Day_FridayButtonRectangle );
	m_DaysButtonRectangles[ 6 ].Set( CLWeeklyEditForm_Day_SaturdayButtonRectangle );

	m_CopyButtonRectangle.Set( CLWeeklyEditForm_CopyButtonRectangle );
	m_PasteButtonRectangle.Set( CLWeeklyEditForm_PasteButtonRectangle );
	m_EditButtonRectangle.Set( CLWeeklyEditForm_EditButtonRectangle );
}

CLFormResult CLWeeklyEditForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_SelectedDays		= 0;
	m_SelectedDayCount	= 0;

	// Inizializza i dati
	SetState( CLState_Initializing );
	ClearSelectedDays();
	SetCopyMode( false, 0 );
	SetDays( gRDEeprom.sDayProg );
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
				bool	exitForm	= true;

				CLLCDCommon::WaitButton( m_BackButtonRectangle );

				if (Close( options ))
				{
					formResult	= CLFormResult_Back;
					break;
				}
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
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
			}
			else
			// Copy Button
			if (!m_CopyMode && m_SelectedDayCount == 1 && m_CopyButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_CopyButtonRectangle );

				for (int daysCounter = 0; daysCounter < 7; daysCounter++)
				{
					if (IsSelectedDay( daysCounter ))
					{
						SetCopyMode( !m_CopyMode, daysCounter );
						break;
					}
				}
			}
			else
			// Copy Button
			if (m_CopyMode && m_CopyButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_CopyButtonRectangle );
				SetCopyMode( false, 0 );
			}
			else
			// Paste Button
			if (m_PasteButtonRectangle.Contains( touchX, touchY ) && m_CopyMode && m_SelectedDayCount > 1)
			{
				CLLCDCommon::WaitButton( m_PasteButtonRectangle );

				for (int daysCounter = 0; daysCounter < 7; daysCounter++)
				{
					if (!(m_SelectedDays & (1 << daysCounter)))
						continue;

					memcpy( m_Days + daysCounter, m_Days + m_CopyModeDay, sizeof(SDAYPROG) );
				}
				SetCopyMode( false, 0 );
				ClearSelectedDays();
			}
			else
			// Edit Button
			if (m_EditButtonRectangle.Contains( touchX, touchY ) && !m_CopyMode && m_SelectedDayCount > 0)
			{
				CLLCDCommon::WaitButton( m_EditButtonRectangle );

				formResult	= CLWeeklyDaysEditForm_Open( CLFormOption_Default,
					m_Days, m_SelectedDays );

				if (formResult == CLFormResult_Home)
					break;

				RenderPage();
			}
			else
			// Days Buttons
			{
				bool	inDayButton	= false;

				for (int daysCounter = 0; daysCounter < 7; daysCounter++)
				{
					if (m_DaysButtonRectangles[ daysCounter ].Contains( touchX, touchY ) &&
						(!m_CopyMode || m_CopyModeDay != daysCounter))
					{
						CLLCDCommon::WaitButton( m_DaysButtonRectangles[ daysCounter ] );
						SelectDay( daysCounter, !IsSelectedDay( daysCounter ) );
						inDayButton	= true;
					}
				}

				if (!inDayButton)
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

bool CLWeeklyEditForm::Save( unsigned short options )
{
	byte		writeEeprom_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Se non e' andata a buon fine, message + home
	if (!Weekly_Write( m_Days ))
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

void CLWeeklyEditForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_WEEKLY_PROGRAMMER ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Angolo inferiore Sinistro
	CLGraphics::DrawBox( CLRectangle( CLWeeklyEditForm_Panel1Rectangle ),
		GenericForm_Title_BigFont_Style );
	CLGraphics::DrawBox( CLRectangle( CLWeeklyEditForm_Panel2Rectangle ), CLGraphicStyleOptions_Default,
		RGBColor_Black );

	RenderDaysButtons();
	RenderEditButtons();
}

void CLWeeklyEditForm::RenderDaysButtons()
{
	for (int daysCounter = 0; daysCounter < 7; daysCounter++)
	{
		const char*	dayName	= Weekly_GetDayName( daysCounter );
		
		if (m_CopyMode && m_CopyModeDay == daysCounter)
		{
			CLGraphics::DrawBoxWithText( m_DaysButtonRectangles[ daysCounter ],
				CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
				0xDAC77F, RGBColor_Black,
				1, RGBColor_Black,
				dayName );
		}
		else
		{
			CLLCDCommon::DrawGenericButton( m_DaysButtonRectangles[ daysCounter ],
				(bitRead( m_SelectedDays, daysCounter ) ? GenericButtonStyle_Selected_SmallFont : GenericButtonStyle_Normal_SmallFont),
				dayName );
		}
	}
}

void CLWeeklyEditForm::RenderEditButtons()
{
	CLLCDCommon::DrawGenericButton( m_CopyButtonRectangle,
		(m_CopyMode ? GenericButtonStyle_Selected_BigFont : (m_SelectedDayCount != 1 ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont)),
		CLLocalitation::GetText( CLTextId_COPY ) );

	CLLCDCommon::DrawGenericButton( m_PasteButtonRectangle,
		(m_CopyMode && m_SelectedDayCount > 1 ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont),
		CLLocalitation::GetText( CLTextId_PASTE ) );

	CLLCDCommon::DrawGenericButton( m_EditButtonRectangle,
		(!m_CopyMode && m_SelectedDayCount > 0 ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont),
		CLLocalitation::GetText( CLTextId_PROG ) );
}

void CLWeeklyEditForm::ClearSelectedDays()
{
	m_SelectedDays		= 0;
	m_SelectedDayCount	= 0;

	if (GetState() == CLState_Running)
		RenderDaysButtons();
}

void CLWeeklyEditForm::SelectDay( byte index, bool value )
{
	if (index >= 7)
		return;

	bitWrite( m_SelectedDays, index, value );

	m_SelectedDayCount	= 0;
	for (int daysCounter = 0; daysCounter < 7; daysCounter++)
	{
		if (m_SelectedDays & (1 << daysCounter))
			m_SelectedDayCount++;
	}

	RenderDaysButtons();
	RenderEditButtons();
}

bool CLWeeklyEditForm::IsSelectedDay( byte index )
{
	if (index >= 7)
		return false;

	return bitRead( m_SelectedDays, index );
}

void CLWeeklyEditForm::SetCopyMode( bool value, byte day )
{
	m_CopyMode		= value;
	m_CopyModeDay	= day;

	if (GetState() == CLState_Running)
	{
		RenderEditButtons();
		RenderDaysButtons();
	}
}

void CLWeeklyEditForm::SetDays( SDAYPROG* days )
{
	memcpy( m_Days, days, sizeof(m_Days) );
}

bool CLWeeklyEditForm::IsDataChanged()
{
	return memcmp( gRDEeprom.sDayProg, m_Days, sizeof(gRDEeprom.sDayProg) ) ? true : false;
}

bool CLWeeklyEditForm::Close( unsigned short options )
{
	switch (CLLCDCommon::MessageBoxCloseForm( IsDataChanged(), false ))
	{
		case CLCloseFormMessageBoxResult_Cancel:
			return false;

		case CLCloseFormMessageBoxResult_SaveAndClose:
			if (Save( options ))
				return true;
	}
	return true;
}
// -----------------------------------------------------------------------------
// CLWeeklyEditForm [class]
// =============================================================================

