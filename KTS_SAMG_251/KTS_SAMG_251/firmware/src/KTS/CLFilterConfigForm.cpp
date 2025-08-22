#include "CLFilterConfigForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLFunction.h"
#include "CLImages.h"
#include "CLMessageBoxForm.h"
#include "CLAccessory.h"

#define CLFilterConfigForm_OffButtonRectangle		12, 30, 81, 69
#define CLFilterConfigForm_DPSButtonRectangle		12, 81, 81, 120
#define CLFilterConfigForm_DPPButtonRectangle		12, 132, 81, 171

#define CLFilterConfigForm_DetailFrameRectangle		90, 30, 310, 171

#define CLFilterConfigForm_DPSFrameRectangle		CLFilterConfigForm_DetailFrameRectangle
#define CLFilterConfigForm_DPSDaysValuePoint		98, 79
#define CLFilterConfigForm_DPSDaysValueLength		7
#define CLFilterConfigForm_DPSDaysTextPoint			99, 104
#define CLFilterConfigForm_DPSDaysTextLength		15
#define CLFilterConfigForm_DPSPlusButtonRectangle	230, 49, 289, 88
#define CLFilterConfigForm_DPSMinusButtonRectangle	230, 110, 289, 149

#define CLFilterConfigForm_DPP_Threshold_FrameRectangle			90, 30, 184, 171
#define CLFilterConfigForm_DPP_Threshold_ProgressBarRectangle	97, 49, 132, 139
#define CLFilterConfigForm_DPP_Threshold_TextPoint				97, 149
#define CLFilterConfigForm_DPP_Threshold_TextLength				5
#define CLFilterConfigForm_DPP_Threshold_PlusButtonRectangle	139, 49, 178, 88
#define CLFilterConfigForm_DPP_Threshold_MinusButtonRectangle	139, 100, 178, 139
#define CLFilterConfigForm_DPP_Calibration_FrameRectangle		190, 30, 310, 97
#define CLFilterConfigForm_DPP_Calibration_ButtonRectangle		270, 52, 304, 86
#define CLFilterConfigForm_DPP_Calibration_TextPoint			195, 61
#define CLFilterConfigForm_DPP_Calibration_TextLength			4
#define CLFilterConfigForm_DPP_FilterLevel_FrameRectangle		190, 104, 310, 171
#define CLFilterConfigForm_DPP_FilterLevel_ButtonRectangle		270, 128, 304, 162
#define CLFilterConfigForm_DPP_FilterLevel_TextPoint			195, 137
#define CLFilterConfigForm_DPP_FilterLevel_TextLength			4

CLFormResult CLFilterConfigForm_Open( unsigned short options )
{
	CLFilterConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLFilterConfigForm [class]
// -----------------------------------------------------------------------------
CLFilterConfigForm::CLFilterConfigForm()
{
}

CLFormResult CLFilterConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_Options	= options;

	// Inizializza i dati
	SetState( CLState_Initializing );

	Load();

	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		else
			RenderPageDynamicObjects();
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			bool	touchedDispatched	= true;
			
			touchX	= ReadX();
			touchY	= ReadY();
			
			// Home Button
			if (CLRectangle( Form_HomeButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( Form_HomeButtonRectangle ) );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (CLRectangle( EditForm_BackButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( EditForm_BackButtonRectangle ) );
				formResult	= CLFormResult_Back;
				break;
			}
			else
			// Ok Button 
			if (CLRectangle( EditForm_OkButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( EditForm_OkButtonRectangle ) );

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
			// Off Button
			if (CLRectangle( CLFilterConfigForm_OffButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( CLFilterConfigForm_OffButtonRectangle ) );
				SetCheckFilterType( CheckFilterType_Off );
			}
			else
			// DPS Button
			if (CLRectangle( CLFilterConfigForm_DPSButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( CLFilterConfigForm_DPSButtonRectangle ) );
				SetCheckFilterType( CheckFilterType_DPS );
			}
			else
			// DPP Button
			if (CLRectangle( CLFilterConfigForm_DPPButtonRectangle ).Contains( touchX, touchY )
				&& Accessory_IsPresent( ACC_EEP_DPPV2 ))
			{
				CLLCDCommon::WaitButton( CLRectangle( CLFilterConfigForm_DPPButtonRectangle ) );
				SetCheckFilterType( CheckFilterType_DPP );
			}
			else
			// DPS: Up Button
			if (m_CheckFilterType == CheckFilterType_DPS
				&& CLRectangle( CLFilterConfigForm_DPSPlusButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( CLRectangle( CLFilterConfigForm_DPSPlusButtonRectangle ) );

				while (Touched() != 0)
				{
					SetDPS_Days( m_DPS_Days + 30 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( CLRectangle( CLFilterConfigForm_DPSPlusButtonRectangle ) );
			}
			else
			// DPS: Down Button
			if (m_CheckFilterType == CheckFilterType_DPS
				&& CLRectangle( CLFilterConfigForm_DPSMinusButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( CLRectangle( CLFilterConfigForm_DPSMinusButtonRectangle ) );

				while (Touched() != 0)
				{
					SetDPS_Days( m_DPS_Days - 30 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( CLRectangle( CLFilterConfigForm_DPSMinusButtonRectangle ) );
			}
			else
			// DPP: Threshold Plus Button
			if (m_CheckFilterType == CheckFilterType_DPP
				&& CLRectangle( CLFilterConfigForm_DPP_Threshold_PlusButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( CLRectangle( CLFilterConfigForm_DPP_Threshold_PlusButtonRectangle ) );

				while (Touched() != 0)
				{
					SetDPP_Threshold( m_DPP_Threshold + 5 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( CLRectangle( CLFilterConfigForm_DPP_Threshold_PlusButtonRectangle ) );
			}
			else
			// DPP: Threshold Minus Button
			if (m_CheckFilterType == CheckFilterType_DPP
				&& CLRectangle( CLFilterConfigForm_DPP_Threshold_MinusButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( CLRectangle( CLFilterConfigForm_DPP_Threshold_MinusButtonRectangle ) );

				while (Touched() != 0)
				{
					SetDPP_Threshold( m_DPP_Threshold - 5 );
					CLKTS::Process();
					CLKTS::Pir_Process();
					//delay( 140 );
                    SYSTICK_DelayMs ( 140 );
				}

				CLLCDCommon::WaitButton_Unpressed( CLRectangle( CLFilterConfigForm_DPP_Threshold_MinusButtonRectangle ) );
			}
			else
			// DPP: Calibration Button
			if (m_CheckFilterType == CheckFilterType_DPP
				&& CLRectangle( CLFilterConfigForm_DPP_Calibration_ButtonRectangle ).Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( CLRectangle( CLFilterConfigForm_DPP_Calibration_ButtonRectangle ) );
				if (Save( m_Options & ~CLFormOption_ShowWriteMesssages_Success ))
					AccessoryDPP_Request( false );

				CLKTS::Delay( 1500 );
				Load();
				RenderPage();
			}
			else
			// DPP: FilterLevel Button
			if (m_CheckFilterType == CheckFilterType_DPP
				&& m_Options & CLFormOption_AdminMode
				&& CLRectangle( CLFilterConfigForm_DPP_FilterLevel_ButtonRectangle ).Contains( touchX, touchY )
				&& gRDEeprom.DPP_CalibrationValue > 0)
			{
				CLLCDCommon::WaitButton( CLRectangle( CLFilterConfigForm_DPP_FilterLevel_ButtonRectangle ) );

				if (Save( m_Options & ~CLFormOption_ShowWriteMesssages_Success ))
					AccessoryDPP_Request( true );

				CLKTS::Delay( 1500 );
				Load();
				RenderPage();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

void CLFilterConfigForm::Load()
{
	SetState( CLState_Initializing );
	if (!Function_IsEnabled( ENAB_CTRL_FILTER ))
	{
		SetCheckFilterType( CheckFilterType_Off );
		SetDPS_Days( 30 );
		SetDPP_Threshold( 50 );
	}
	else
	if (Accessory_IsPresent( ACC_EEP_DPPV2 ) && Function_IsEnabled( ENAB_DPP ))
	{
		SetCheckFilterType( CheckFilterType_DPP );
		SetDPS_Days( 30 );
		SetDPP_Threshold( gRDEeprom.DPP_Threshold );
	}
	else
	{
		SetCheckFilterType( CheckFilterType_DPS );
		SetDPS_Days( gRDEeprom.gg_manut_Filter );
		SetDPP_Threshold( 50 );
	}
	SetState( CLState_Running );
}

byte WriteEepromAndWait( int offset,
	int count,
	ComQueue_Status* writeEeprom_Status )
{
	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offset,
		count,
		writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING((*writeEeprom_Status)))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	return writeEeprom_Status->Status;
}

/*	OFF ->	Function	ENAB_CTRL_FILTER	= false
			RDEprom		gg_manut_Filter		= 30
	DPS ->	Function	ENAB_CTRL_FILTER	= true
			Function	ENAB_FUNC_DPP		= false
			RDEprom		gg_manut_Filter		= <Days>
	DPP ->	Function	ENAB_CTRL_FILTER	= true
			Function	ENAB_FUNC_DPP		= true
			RDEprom		DPP_Settings		= <Threshold>
*/
bool CLFilterConfigForm::Save( unsigned short options )
{
	bool			saveResult	= true;
	ComQueue_Status	writeEeprom_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	switch (m_CheckFilterType)
	{
		case CLFilterConfigForm::CheckFilterType_Off:
		{
			bool			saveFunction_ENAB_CTRL_FILTER	= Function_IsEnabled( ENAB_CTRL_FILTER );
			bool			saveFunction_ENAB_DPP			= Function_IsEnabled( ENAB_DPP );
			unsigned short  saveRDEprom_gg_manut_Filter		= gRDEeprom.gg_manut_Filter;

			Function_SetEnabled( ENAB_CTRL_FILTER, false );
			Function_SetEnabled( ENAB_DPP, false );
			gRDEeprom.gg_manut_Filter	= 30;

			if (WriteEepromAndWait( offsetof( S_EEPROM, Enab_Fuction ),
				sizeof(gRDEeprom.Enab_Fuction),
				&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
			{
				saveResult	= false;
			}
			else
			{
				if (WriteEepromAndWait( offsetof( S_EEPROM, Enab_Fuction ),
					sizeof(gRDEeprom.Enab_Fuction),
					&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
				{
					saveResult	= false;
				}
			}

			if (!saveResult)
			{
				Function_SetEnabled( ENAB_CTRL_FILTER, saveFunction_ENAB_CTRL_FILTER );
				Function_SetEnabled( ENAB_DPP, saveFunction_ENAB_DPP );
				gRDEeprom.gg_manut_Filter	= saveRDEprom_gg_manut_Filter;
			}
			break;
		}

		case CLFilterConfigForm::CheckFilterType_DPS:
		{
			bool			saveFunction_ENAB_CTRL_FILTER	= Function_IsEnabled( ENAB_CTRL_FILTER );
			bool			saveFunction_ENAB_DPP			= Function_IsEnabled( ENAB_DPP );
			unsigned short  saveRDEprom_gg_manut_Filter		= gRDEeprom.gg_manut_Filter;
			bool			isDPS;

			isDPS	= Function_IsEnabled( ENAB_CTRL_FILTER ) && !Function_IsEnabled( ENAB_DPP );

			Function_SetEnabled( ENAB_CTRL_FILTER, true );
			Function_SetEnabled( ENAB_DPP, false );
			gRDEeprom.gg_manut_Filter	= m_DPS_Days;

			if (WriteEepromAndWait( offsetof( S_EEPROM, Enab_Fuction ),
				sizeof(gRDEeprom.Enab_Fuction),
				&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
			{
				saveResult	= false;
			}
			else
			{
				if (WriteEepromAndWait( offsetof( S_EEPROM, gg_manut_Filter ),
					sizeof(gRDEeprom.gg_manut_Filter),
					&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
				{
					saveResult	= false;
				}
			}

			if (!saveResult)
			{
				Function_SetEnabled( ENAB_CTRL_FILTER, saveFunction_ENAB_CTRL_FILTER );
				Function_SetEnabled( ENAB_DPP, saveFunction_ENAB_DPP );
				gRDEeprom.gg_manut_Filter	= saveRDEprom_gg_manut_Filter;
			}
			else
			{
				if (!isDPS)
				{
					gRDEeprom.time_lastCloggedFilers	= gRDEeprom.hour_runnig;
					// Accoda la richiestga di WriteEeprom
					WriteEepromAndWait( offsetof( S_EEPROM, time_lastCloggedFilers ),
						sizeof(gRDEeprom.time_lastCloggedFilers),
						&writeEeprom_Status );
				}
			}
			break;
		}

		case CLFilterConfigForm::CheckFilterType_DPP:
		{
			bool	saveFunction_ENAB_CTRL_FILTER	= Function_IsEnabled( ENAB_CTRL_FILTER );
			bool	saveFunction_ENAB_DPP			= Function_IsEnabled( ENAB_DPP );
			byte	saveRDEeprom_DPP_Threshold		= gRDEeprom.DPP_Threshold;
			byte	saveRDEeprom_DPP_FilterLevel	= gRDEeprom.DPP_FilterLevel;

			Function_SetEnabled( ENAB_CTRL_FILTER, true );
			Function_SetEnabled( ENAB_DPP, true );
			gRDEeprom.DPP_Threshold		= m_DPP_Threshold;

			if (!saveFunction_ENAB_CTRL_FILTER || !saveFunction_ENAB_DPP)
				gRDEeprom.DPP_FilterLevel	= 0;

			if (WriteEepromAndWait( offsetof( S_EEPROM, Enab_Fuction ),
				sizeof(gRDEeprom.Enab_Fuction),
				&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
			{
				saveResult	= false;
			}
			else
			{
				if (WriteEepromAndWait( offsetof( S_EEPROM, gg_manut_Filter ),
					sizeof(gRDEeprom.gg_manut_Filter),
					&writeEeprom_Status ) != COM_REQUEST_STATUS_COMPLETED)
				{
					saveResult	= false;
				}
			}

			if (!saveResult)
			{
				Function_SetEnabled( ENAB_CTRL_FILTER, saveFunction_ENAB_CTRL_FILTER );
				Function_SetEnabled( ENAB_DPP, saveFunction_ENAB_DPP );
				gRDEeprom.DPP_Threshold		= saveRDEeprom_DPP_Threshold;
				gRDEeprom.DPP_FilterLevel	= saveRDEeprom_DPP_FilterLevel;
			}
			else
			{
				if (gRDEeprom.time_lastCloggedFilers == 1)
					gRDEeprom.time_lastCloggedFilers = 1;
				else
				gRDEeprom.time_lastCloggedFilers	= 0;
				// Accoda la richiesta di WriteEeprom
				WriteEepromAndWait( offsetof( S_EEPROM, time_lastCloggedFilers ),
					sizeof(gRDEeprom.time_lastCloggedFilers),
					&writeEeprom_Status );
			}
			break;
		}

		default:
			saveResult	= false;
			break;
	}

	// Se non e' andata a buon fine, message + home
	if (!saveResult)
	{
		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError( &writeEeprom_Status );
		
		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLFilterConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_FILTER_SETTINGS ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( EditForm_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
	CLLCDCommon::DrawOkButton( EditForm_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderCheckFilterTypeButtons();
	RenderCheckFilterType();
}

void CLFilterConfigForm::RenderCheckFilterTypeButtons()
{
	// Off Button
	CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_OffButtonRectangle ),
		(m_CheckFilterType == CheckFilterType_Off ? GenericButtonStyle_Off_BigFont : GenericButtonStyle_Normal_BigFont),
		CLFixedText_OFF );

	// DPS Button
	CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPSButtonRectangle ),
		(m_CheckFilterType == CheckFilterType_DPS ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Normal_BigFont),
		&ClockMonoImage );

	// DPP Button
	CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPPButtonRectangle ),
		(!Accessory_IsPresent( ACC_EEP_DPPV2 ) ? GenericButtonStyle_Disabled_BigFont :  m_CheckFilterType == CheckFilterType_DPP ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Normal_BigFont),
		&PressureProbeMonoImage );
}

void CLFilterConfigForm::RenderCheckFilterType()
{
	CLGraphics::DrawBox( CLRectangle( CLFilterConfigForm_DetailFrameRectangle ),
		CLGraphicStyleOptions_BorderRound_No,
		RGBColor_Black );

	switch (m_CheckFilterType)
	{
		case CLFilterConfigForm::CheckFilterType_Off:
			break;

		case CLFilterConfigForm::CheckFilterType_DPS:
			// Detail Frame
			CLGraphics::DrawBox( CLRectangle( CLFilterConfigForm_DPSFrameRectangle ), 
				GenericForm_Group_Style );
			CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPSPlusButtonRectangle ),
				GenericButtonStyle_Normal_UpDown,
				&UpMonoImage );
			CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPSMinusButtonRectangle ),
				GenericButtonStyle_Normal_UpDown,
				&DownMonoImage );
			break;

		case CLFilterConfigForm::CheckFilterType_DPP:
			// Detail Frame
			CLGraphics::DrawBoxWithText( CLRectangle( CLFilterConfigForm_DPP_Threshold_FrameRectangle ),
				CLGraphicStyleOptions_Default | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				(byte) 1, 0x898989,
				CLLocalitation::GetText( CLTextId_DPP_THRESHOLD ) );
			CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPP_Threshold_PlusButtonRectangle ),
				GenericButtonStyle_Normal_UpDown,
				&UpMonoImage );
			CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPP_Threshold_MinusButtonRectangle ),
				GenericButtonStyle_Normal_UpDown,
				&DownMonoImage );

			CLGraphics::DrawBoxWithText( CLRectangle( CLFilterConfigForm_DPP_Calibration_FrameRectangle ), 
				CLGraphicStyleOptions_Default | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				(byte) 1, 0x898989,
				CLLocalitation::GetText( CLTextId_DPP_CALIBRATION ) );
			CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPP_Calibration_ButtonRectangle ),
				GenericButtonStyle_Normal_SmallFont,
				&PlayImage );

			if (m_Options & CLFormOption_AdminMode)
			{
				CLGraphics::DrawBoxWithText( CLRectangle( CLFilterConfigForm_DPP_FilterLevel_FrameRectangle ), 
					CLGraphicStyleOptions_Default | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
					RGBColor_Black, RGBColor_White,
					(byte) 1, 0x898989,
					CLLocalitation::GetText( CLTextId_DPP_FILTER_LEVEL ) );
				CLLCDCommon::DrawGenericButton( CLRectangle( CLFilterConfigForm_DPP_FilterLevel_ButtonRectangle ),
					gRDEeprom.DPP_CalibrationValue > 0 ? GenericButtonStyle_Normal_SmallFont : GenericButtonStyle_Disabled_SmallFont,
					&PlayImage );
			}
			break;
	}
}

void CLFilterConfigForm::RenderPageDynamicObjects()
{
	char	text[ 10 ];
	switch (m_CheckFilterType)
	{
		case CLFilterConfigForm::CheckFilterType_DPS:

			sprintf( text, "%d", m_DPS_Days );
			CLGraphics::DrawText( CLFilterConfigForm_DPSDaysValuePoint,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, CLFilterConfigForm_DPSDaysValueLength );

			CLGraphics::DrawText( CLFilterConfigForm_DPSDaysTextPoint,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_DAYS ),
				CLFilterConfigForm_DPSDaysTextLength );
			break;

		case CLFilterConfigForm::CheckFilterType_DPP:

			// Threshold
			CLGraphics::DrawProgressBar( CLRectangle( CLFilterConfigForm_DPP_Threshold_ProgressBarRectangle ),
				CLDrawBarOptions_Direction_Vertical | CLDrawBarOptions_BarShape_Rectangle | CLDrawBarOptions_StartWith_Max,
				RGBColor_Black, RGBColor_White, 0xB0B0B0,
				0, 100, m_DPP_Threshold,
				2, 2 );

			sprintf( text, "%d%%", m_DPP_Threshold );
			CLGraphics::DrawText( CLFilterConfigForm_DPP_Threshold_TextPoint,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
				RGBColor_Black, RGBColor_White,
				text, CLFilterConfigForm_DPP_Threshold_TextLength );

			// Calibration
			if (m_Options & CLFormOption_AdminMode)
			{
				if (gRDEeprom.DPP_CalibrationValue == 0)
					*text	= '\0';
				else
					sprintf( text, "%d%%", gRDEeprom.DPP_CalibrationValue );
			}
			else
			{
				if (gRDEeprom.DPP_CalibrationValue != 0)
					strcpy( text, CLFixedText_OK );
				else
					*text	= '\0';
			}

			CLGraphics::DrawText( CLFilterConfigForm_DPP_Calibration_TextPoint,
				CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
				RGBColor_Black, RGBColor_White,
				text, CLFilterConfigForm_DPP_Calibration_TextLength );

			if (m_Options & CLFormOption_AdminMode)
			{
				// FilterLevel
				int	filterLevel	= ((gRDEeprom.DPP_FilterLevel >> 2) & 0x3F) * 5;
				if (filterLevel == 0)
					strcpy( text, "---" );
				else
					sprintf( text, "%d%%", filterLevel );

				CLGraphics::DrawText( CLFilterConfigForm_DPP_FilterLevel_TextPoint,
					CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big,
					RGBColor_Black, RGBColor_White,
					text, CLFilterConfigForm_DPP_FilterLevel_TextLength );
			}
			break;
	}

}

void CLFilterConfigForm::SetCheckFilterType( CLFilterConfigForm::CheckFilterType value )
{
	if (value == m_CheckFilterType)
		return;

	m_CheckFilterType	= value;

	if (GetState() == CLState_Running)
	{
		RenderCheckFilterTypeButtons();
		RenderCheckFilterType();
	}
}

void CLFilterConfigForm::SetDPS_Days( short value )
{
	if (value < 0)
		value	= 180;
	else
	if (value > 180)
		value	= 0;

	m_DPS_Days	= value;

	if (GetState() == CLState_Running)
		RenderPageDynamicObjects();
}

void CLFilterConfigForm::SetDPP_Threshold( short value )
{
	if (value < 20)
		value	= 80;
	else
	if (value > 80)
		value	= 20;

	m_DPP_Threshold	= value;

	if (GetState() == CLState_Running)
		RenderPageDynamicObjects();
}
// -----------------------------------------------------------------------------
// CLFilterConfigForm [class]
// =============================================================================

