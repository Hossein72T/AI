#include "CLWeeklyMainForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLWeeklyViewForm.h"
#include "CLWeeklyEditForm.h"
#include "CLTemperatureConfigForm.h"
#include "CLSelectionAirFlowSpeed_ThreeSpeedForm.h"
#include "CLSpeedMode.h"
#include "CLWeekly.h"

#define	CLWeeklyMainForm_OnOffButtonRectangle		11, 32, 74, 112
#define	CLWeeklyMainForm_ProgramButtonRectangle		86, 32, 311, 66
#define	CLWeeklyMainForm_ViewButtonRectangle		86, 78, 311, 112
#define	CLWeeklyMainForm_ExtraSetFrameRectangle		10, 121, 310, 170

#define	CLWeeklyMainForm_SetTemperatureButtonRectangle	20, 129, 154, 163
#define	CLWeeklyMainForm_SetSpeedButtonRectangle		165, 129, 299, 163

CLFormResult CLWeeklyMainForm_Open( unsigned short options )
{
	CLWeeklyMainForm	form;

	return form.Open( options );
}

// =============================================================================
// CLWeeklyMainForm [class]
// -----------------------------------------------------------------------------
CLWeeklyMainForm::CLWeeklyMainForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_OnOffButtonRectangle.Set( CLWeeklyMainForm_OnOffButtonRectangle );

	m_ProgramButtonRectangle.Set( CLWeeklyMainForm_ProgramButtonRectangle );
	m_ViewButtonRectangle.Set( CLWeeklyMainForm_ViewButtonRectangle );
	m_SetTemperatureButtonRectangle.Set( CLWeeklyMainForm_SetTemperatureButtonRectangle );
	m_SetSpeedButtonRectangle.Set( CLWeeklyMainForm_SetSpeedButtonRectangle );
}

CLFormResult CLWeeklyMainForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetEnabled( Function_IsEnabled( ENAB_WEEKLY ) );
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
			// OnOff Button
			if (m_OnOffButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_OnOffButtonRectangle );
				SetEnabled( !m_Enabled );
			}
			else
			// Program Button
			if (m_ProgramButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ProgramButtonRectangle );

				formResult	= CLWeeklyEditForm_Open( CLFormOption_GoBackAfterWrite | CLFormOption_ShowWriteMesssages_All );
				if (formResult == CLFormResult_Home)
					break;

				RenderPage();
			}
			else
			// View Button
			if (m_ViewButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ViewButtonRectangle );

				formResult	= CLWeeklyViewForm_Open( CLFormOption_Default );
				if (formResult == CLFormResult_Home)
					break;

				RenderPage();
			}
			else
			// Temperature Button
			if (m_SetTemperatureButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_SetTemperatureButtonRectangle );

				formResult	= CLTemperatureConfigForm_Open( CLFormOption_GoBackAfterWrite | CLFormOption_ShowWriteMesssages_All,
					CLTemperatureConfigFormOption_Mode_DoubleTemperature );
				if (formResult == CLFormResult_Home)
					break;

				RenderPage();
			}
			else
			// Speed Button
			if (CanConfigThreeSpeed() && m_SetSpeedButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_SetSpeedButtonRectangle );

				ConfigThreeSpeed( options );
				RenderPage();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLWeeklyMainForm::CanConfigThreeSpeed()
{
#ifdef FRANCETX_ENABLED
	return (SpeedMode_GetType() == CLSpeedModeType_FranceTx ? false : true);
#else
	return true;
#endif
}

bool CLWeeklyMainForm::ConfigThreeSpeed( unsigned short options )
{
	unsigned short	newSet_StepMotors[ 4 ];

	if (!CanConfigThreeSpeed())
		return false;

	// Impostiamo i valori correnti
	SpeedMode_Speed_GetValues( VentilationControl_Get(), newSet_StepMotors );

	if (CLSelectionAirFlowSpeed_ThreeSpeedForm_Open( CLFormOption_Default,
		VentilationControl_Get(),
		newSet_StepMotors ) != CLFormResult_Ok)
	{
		return false;
	}

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	if (!SpeedMode_Speed_Write( VentilationControl_Get(),
		SpeedMode_GetType(),
		newSet_StepMotors,
		SpeedMode_Speed_GetIndex() ))
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

bool CLWeeklyMainForm::Save( unsigned short options )
{
	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	if (!Function_Write( ENAB_WEEKLY, m_Enabled ))
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

void CLWeeklyMainForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_WEEKLY_SETTINGS ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Program Button
    CLLCDCommon::DrawGenericButton( m_ProgramButtonRectangle,
		GenericButtonStyle_Normal_BigFont,
		CLLocalitation::GetText( CLTextId_PROGRAM ) );

	// View Button
    CLLCDCommon::DrawGenericButton( m_ViewButtonRectangle,
		GenericButtonStyle_Normal_BigFont,
		CLLocalitation::GetText( CLTextId_VIEW ) );

	// Extra Frame
	CLGraphics::DrawBox( CLRectangle( CLWeeklyMainForm_ExtraSetFrameRectangle ), 
		GenericForm_Group_Style );

	// Temperature Button
    CLLCDCommon::DrawGenericButton( m_SetTemperatureButtonRectangle,
		GenericButtonStyle_Normal_SmallFont,
		CLLocalitation::GetText( CLTextId_CLIMA_SETTINGS ) );

	RenderButtons();
}

void CLWeeklyMainForm::RenderButtons()
{
	// On/Off Button
	CLLCDCommon::DrawGenericButton( m_OnOffButtonRectangle,
		(m_Enabled ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(m_Enabled ? CLFixedText_ON : CLFixedText_OFF) );

	// Speed Button
    CLLCDCommon::DrawGenericButton( m_SetSpeedButtonRectangle,
		(CanConfigThreeSpeed() ? GenericButtonStyle_Normal_SmallFont : GenericButtonStyle_Disabled_SmallFont),
		CLLocalitation::GetText( CLTextId_SPEED ) );
}

void CLWeeklyMainForm::SetEnabled( bool value )
{
	if (value == m_Enabled)
		return;

	m_Enabled	= value;

	if (GetState() == CLState_Running)
		RenderButtons();
}
// -----------------------------------------------------------------------------
// CLWeeklyMainForm [class]
// =============================================================================

// =============================================================================
// CLWeeklySupport [class]
// -----------------------------------------------------------------------------
void CLWeeklySupport::RenderSelectedDays( short x, short y, byte value )
{
	char	dayShortName[ 2 ];
	CLGraphics::DrawBox( CLRectangle( x, y, x + (1 + (16 * 7) + 1), y + 16 + 2 ), CLGraphicStyleOptions_Default,
		RGBColor_Black,
		1, RGBColor_White );

	dayShortName[ 1]	= '\0';
	x++, y++;
	for (int daysCounter = 0; daysCounter < 7; daysCounter++, x += 16)
	{
		RGBColor	backgroundColor;
		RGBColor	foregroundColor;
		if (value & (1 << daysCounter))
		{
			backgroundColor	= 0x404080; //RGBColor_Button_SelectedBackground;
			foregroundColor	= RGBColor_White;
		}
		else
		{
			backgroundColor	= RGBColor_Black;
			foregroundColor	= 0x737373;
		}

		dayShortName[ 0 ]	= Weekly_GetDayName( daysCounter )[ 0 ];
		CLGraphics::DrawText( x, y, CLGraphicStyleOptions_Font_Big,
			backgroundColor, foregroundColor,
			dayShortName );
	}
}

void CLWeeklySupport::RenderHoursAxis( short x, short y,
	RGBColor backgroundColor, RGBColor foregroundColor )
{
	char		hourText[ 3 ];
	Font*		saveFont		= gLCD.getFont();
	RGBColor	saveColor		= gLCD.getRGBColor();
	RGBColor	saveBackColor	= gLCD.getRGBBackColor();
	short		lineX			= x;

	gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
	gLCD.setRGBColor( foregroundColor );
	gLCD.setRGBBackColor( backgroundColor );

	gLCD.drawLine( x, y, x + 288, y );

	for (short hoursCounter = 0; hoursCounter <= 24; hoursCounter++, lineX += 12)
	{
		gLCD.drawLine( lineX, y , lineX, y + 5 ); 
		if (hoursCounter % 2 == 0)
		{
			sprintf( hourText, "%d", hoursCounter );
			if (hoursCounter < 10)
				gLCD.print( hourText, lineX - 2, y + 6 );
			else
				gLCD.print( hourText, lineX - 6, y + 6 );
		}
	}

	gLCD.setRGBColor( saveColor );
	gLCD.setRGBBackColor( saveBackColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
 }
// -----------------------------------------------------------------------------
// CLWeeklySupport [class]
// =============================================================================

