#include "CLLCDCommon.h"
#include "CLLocalitation.h"
#include "CLTouch.h"
#include "CLFonts.h"
#include "CLMessageBoxForm.h"
#include "CLKTS.h"
#include "CLImages.h"

// Template GenericForm
CLRectangle GenericForm_Data_Rectangle( 0, 0, 319, 179 );
CLGraphicStyle GenericForm_Data_Style( CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_VAlign_Top | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small,
	RGBColor_Black, RGBColor_White,
	(byte) 1, RGBColor_Blue );

CLGraphicStyle GenericForm_Group_Style( CLGraphicStyleOptions_Default | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_BorderRound_Yes,
	RGBColor_Black, RGBColor_White,
	(byte) 1, 0xA9A9A9  );
CLGraphicStyle GenericForm_GroupDisabled_Style( CLGraphicStyleOptions_Default | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_BorderRound_Yes,
	RGBColor_Black, 0xC9C9C9,
	(byte) 1, 0xA9A9A9  );

CLRectangle GenericForm_Title_Rectangle( 1, 1, 318, 22 );
CLGraphicStyle GenericForm_Title_BigFont_Style( CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big,
	RGBColor_Black, RGBColor_White );
CLGraphicStyle GenericForm_Title_SmallFont_Style( CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small,
	RGBColor_Black, RGBColor_White );

// Template ViewForm
CLRectangle ViewForm_PreviousButtonRectangle( 140, 190, 190, 229 );
CLRectangle ViewForm_NextButtonRectangle( 200, 190, 250, 229 );
CLRectangle ViewForm_BackButtonRectangle( 120, 190, 190, 229 );

// Template EditForm
CLRectangle EditForm_SaveButtonRectangle( 0, 190, 70, 229 );
CLRectangle EditForm_OkButtonRectangle( 0, 190, 70, 229 );
CLRectangle EditForm_BackButtonRectangle( 80, 190, 150, 229 );

// Generic Template
CLRectangle Form_HomeButtonRectangle( 264, 184, 314, 234 );

CLGraphicStyle GenericButtonStyle_NormalBlack_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
	RGBColor_Black, RGBColor_White,
	(byte) 1, RGBColor_Button_Border,
	RGBColor_Black, RGBColor_White );

CLGraphicStyle GenericButtonStyle_Normal_UpDown( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes,
	0x404080, RGBColor_UpDownIcon_Pen,
	(byte) 1, RGBColor_Button_Border,
	0x404080, RGBColor_UpDownIcon_Pen );
CLGraphicStyle GenericButtonStyle_Disabled_UpDown( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes,
	0x404080, 0xA9A9A9,
	(byte) 1, RGBColor_Button_Border,
	0x404080, 0xA9A9A9 );

CLGraphicStyle GenericButtonStyle_Normal_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x404080, RGBColor_White,
	(byte) 1, RGBColor_Button_Border,
	0x404080, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Selected_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x51BD51, RGBColor_White,
	(byte) 2, RGBColor_White,
	0x51BD51, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Disabled_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x09092E, 0xC9C9C9,
	(byte) 1, 0x8A8A8A,
	0x09092E, 0xC9C9C9 );

CLGraphicStyle GenericButtonStyle_Normal_SmallFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x404080, RGBColor_White,
	(byte) 1, RGBColor_Button_Border,
	0x404080, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Selected_SmallFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x51BD51, RGBColor_White,
	(byte) 2, RGBColor_White,
	0x51BD51, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Disabled_SmallFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel,
	0x09092E, 0xC9C9C9,
	(byte) 1, 0x8A8A8A,
	0x09092E, 0xC9C9C9 );

CLGraphicStyle GenericButtonStyle_Normal_SmallFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x404080, RGBColor_White,
	(byte) 1, RGBColor_Button_Border,
	0x404080, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Selected_SmallFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x51BD51, RGBColor_White,
	(byte) 2, RGBColor_White,
	0x51BD51, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Disabled_SmallFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x09092E, 0xC9C9C9,
	(byte) 1, 0x8A8A8A,
	0x09092E, 0xC9C9C9 );

CLGraphicStyle GenericButtonStyle_Normal_BigFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x404080, RGBColor_White,
	(byte) 1, RGBColor_Button_Border,
	0x404080, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Selected_BigFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x51BD51, RGBColor_White,
	(byte) 2, RGBColor_White,
	0x51BD51, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Disabled_BigFont_Multiline( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x09092E, 0xC9C9C9,
	(byte) 1, 0x8A8A8A,
	0x09092E, 0xC9C9C9 );

CLGraphicStyle GenericButtonStyle_On_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x00C900, RGBColor_Black,
	(byte) 1, RGBColor_White,
	0x00C900, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Off_BigFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0xA10000, RGBColor_White,
	(byte) 1, RGBColor_White,
	0xA10000, RGBColor_White );

CLGraphicStyle GenericButtonStyle_On_SmallFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0x00C900, RGBColor_White,
	(byte) 1, RGBColor_White,
	0x00C900, RGBColor_White );
CLGraphicStyle GenericButtonStyle_Off_SmallFont( CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
	0xA10000, RGBColor_White,
	(byte) 1, RGBColor_White,
	0xA10000, RGBColor_White );

#define CLLCDCommon_WriteDataPanelRectangle			15, 85, 304, 144
#define CLLCDCommon_WriteErrorCodePanelRectangle	15, 160, 304, 190
#define CLLCDCommon_PanelInfoRectangle				15, 85, 304, 144

void CLLCDCommon::DrawArrowButton( short x, short y, CLDrawArrowButtonDirection direction )
{
	RGBColor	saveColor	= gLCD.getRGBColor();

	gLCD.setRGBColor( RGBColor_Button_Background );

	switch (direction)
	{
		case CLDrawArrowButtonDirection_Right:
			for(int i=0; i< 27 ;i++)
				gLCD.drawLine(x+1+i ,y+1+i, x+1+i , y+54-i);

			gLCD.setRGBColor( RGBColor_Button_Border );

			gLCD.drawLine(x+1 ,y+1, x+1 , y+54);
			gLCD.drawLine(x+1 ,y+1, x+27 , y+27);
			gLCD.drawLine(x+1 ,y+54, x+27 , y+28);
			break;

		case CLDrawArrowButtonDirection_Left:
			for(int i=0; i< 27 ;i++)
				gLCD.drawLine(x+40-i ,y+1+i, x+40-i , y+54-i);

			gLCD.setRGBColor( RGBColor_Button_Border );

			gLCD.drawLine(x+40 ,y+1, x+40 , y+54);
			gLCD.drawLine(x+40 ,y+1, x+14 , y+27);
			gLCD.drawLine(x+40 ,y+54, x+14 , y+28);
			break;

		case CLDrawArrowButtonDirection_Up:
			gLCD.setColor(64, 64, 128);
			gLCD.fillRoundRect(x, y, x+41, y+41);
			gLCD.setColor(255, 255, 255);
			gLCD.drawRoundRect(x, y, x+41, y+41);
			gLCD.setColor(128, 128, 255);
			for (int i=0; i<15; i++)
				gLCD.drawLine(x+10+(i/1.5), y+29-i, x+31-(i/1.5), y+29-i);
			break;

		case CLDrawArrowButtonDirection_Down:
			gLCD.setColor(64, 64, 128);
			gLCD.fillRoundRect(x, y, x+41, y+41);
			gLCD.setColor(255, 255, 255);
			gLCD.drawRoundRect(x, y, x+41, y+41);
			gLCD.setColor(128, 128, 255);
			for (int i=0; i<15; i++)
				gLCD.drawLine(x+10+(i/1.5), y+13+i, x+31-(i/1.5), y+13+i);
			break;
	}
	gLCD.setRGBColor( saveColor );
}

void CLLCDCommon::DrawHomeButton( short x, short y )
{
	RGBColor	saveColor	= gLCD.getRGBColor();
	// (264, 184, 314, 234)
	gLCD.setRGBColor( RGBColor_Button_Background );
	//gLCD.fillCircle( 289, 209, 26 );
	gLCD.fillCircle( x + 26 - 1, y + 26 - 1, 26 );

	gLCD.setRGBColor( RGBColor_Button_Border );
//	gLCD.drawCircle( 289, 209, 26 );
//	gLCD.fillRect( 276, 209, 301 , 226 );
	gLCD.drawCircle( x + 26 - 1, y + 26 - 1, 26 );
	gLCD.fillRect( x + 12, y + 25, x + 37, y + 42 );

	for (int i = 0; i < 19; i++)
		gLCD.drawLine( (x + 7) + i, (y + 24) - i, (x + 43) - i , (y + 24) - i );
//		gLCD.drawLine( 271+i, 208-i, 307-i , 208-i );

	gLCD.setRGBColor( RGBColor_Button_Background );
	gLCD.fillRect( x + 26, y + 35, x + 33, y + 42 );
//	gLCD.fillRect( 290, 219, 297, 226 );

	gLCD.setRGBColor( saveColor );
}

void CLLCDCommon::WaitButton_Pressed( const CLRectangle& rectangle )
{
	gLCD.setRGBColor( RGBColor_Button_PressedBorder );
	gLCD.drawRoundRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );
}

void CLLCDCommon::WaitButton_Unpressed( const CLRectangle& rectangle )
{
	gLCD.setRGBColor( RGBColor_Button_Border );
	gLCD.drawRoundRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );
}

void CLLCDCommon::WaitButton( const CLRectangle& rectangle )
{
	WaitButton_Pressed( rectangle );
	WaitForTouchRelease();
	WaitButton_Unpressed( rectangle );
}

void CLLCDCommon::DrawPreviousButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		"<<" );
}

void CLLCDCommon::DrawNextButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		">>" );
}

void CLLCDCommon::DrawBackButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		CLLocalitation::GetText( CLTextId_BACK ) );
}

void CLLCDCommon::DrawCancelButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		CLLocalitation::GetText( CLTextId_CANCEL ) );
}

void CLLCDCommon::DrawSaveButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		CLLocalitation::GetText( CLTextId_SAVE ) );
}

void CLLCDCommon::DrawOkButton( const CLRectangle& rectangle, CLGraphicStyle& style )
{
	CLGraphics::DrawBoxWithText( rectangle,
		style,
		CLFixedText_OK );
}

void CLLCDCommon::DrawButtonMark( const CLRectangle& rectangle, RGBColor boxColor )
{
	CLGraphics::DrawBox( CLRectangle( rectangle.GetX2() - 5, rectangle.GetY2() - 5, rectangle.GetX2(), rectangle.GetY2() ), CLGraphicStyleOptions_BorderRound_Yes,
		boxColor,
		1, boxColor );
}

void CLLCDCommon::DrawButtonMark( short x1, short y1, short x2, short y2, RGBColor boxColor )
{
	CLGraphics::DrawBox( CLRectangle( x2 - 5, y2 - 5, x2, y2 ), CLGraphicStyleOptions_BorderRound_Yes,
		boxColor,
		1, boxColor );
}

void CLLCDCommon::DrawGenericButton( const CLRectangle& rectangle,
	CLGraphicStyle& style,
	const char* text,
	bool showMark )
{
    CLGraphics::DrawBoxWithText( rectangle,
		style,
		text );

	if (showMark)
		DrawButtonMark( rectangle, style.BorderColor );
}

//void CLLCDCommon::DrawGenericButton( short x1, short y1, short x2, short y2,
//	CLGraphicStyle& style,
//	const char* text,
//	bool showMark )
//{
//	CLGraphics::DrawBoxWithText( x1, y1, x2, y2,
//		style,
//		text );
//	if (showMark)
//		DrawButtonMark( x1, y1, x2, y2, style.BorderColor );
//}

void CLLCDCommon::DrawGenericButton( const CLRectangle& rectangle,
	CLGraphicStyle& style,
	CLDrawer* drawer,
	bool showMark )
{
    CLGraphics::DrawBoxWithDrawer( rectangle,
		style,
		drawer );
	if (showMark)
		DrawButtonMark( rectangle, style.BorderColor );
}

//void CLLCDCommon::DrawGenericButton( short x1, short y1, short x2, short y2,
//	CLGraphicStyle& style,
//	CLDrawer* drawer,
//	bool showMark )
//{
//    CLGraphics::DrawBoxWithDrawer( CLRectangle( x1, y1, x2, y2 ),
//		style,
//		drawer );
//	if (showMark)
//		DrawButtonMark( x1, y1, x2, y2, style.BorderColor );
//}

void CLLCDCommon::DrawMenuItem( CLProcedureId procedureId,
		const CLRectangle& menuItemButtonRectangle,
		CLGraphicStyle& menuItemstyle )
{
	char*	text;

	switch (procedureId)
	{
		case CLProcedureId_ScreenCalibrationForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_TOUCH_CALIBRATION );
			break;

		case CLProcedureId_AccessoryManagerForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_DISCONNECT_ACCESSORY );
			break;

		case CLProcedureId_BypassConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_BPD_SETTINGS );
			break;

		case CLProcedureId_UnbalanceConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_UNBALANCE_AIRFLOW );
			break;

		case CLProcedureId_EndUserPasswordConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_PASSWORD_SETTINGS );
			break;

		case CLProcedureId_ServicePasswordChangeForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CHANGE_PASSWORD );
			break;

		case CLProcedureId_BoxInfoConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CONFIG_BOX_INFO );
			break;

		case CLProcedureId_InputConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_INPUT_CONFIG );
			break;

		case CLProcedureId_OutputConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_OUTPUT_CONFIG );
			break;

		case CLProcedureId_FilterConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_FILTER_SETTINGS );
			break;

		case CLProcedureId_CO2ConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CO2_SETTINGS );
			break;

		case CLProcedureId_ReferenceTSetting:
			text	= (char*) CLLocalitation::GetText( CLTextId_REFERENCE_T_SETTING );
			break;

		case CLProcedureId_VOCConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_VOC_CONFIG );
			break;

		case CLProcedureId_HysteresisTemperatureConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_TEMPERATURE_HYSTERESIS );
			break;

		case CLProcedureId_SelectionLanguageForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_SELECTION_LANGUAGE );
			break;

		case CLProcedureId_ScreenSaverConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CONFIG_SCREEN_SAVER );
			break;

		case CLProcedureId_SystemDateTimeConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_DATE_SETTINGS );
			break;

		case CLProcedureId_UpgradeForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_UPGRADE );
			break;

		case CLProcedureId_WeeklyMainForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_WEEKLY_PROGRAMMER );
			break;

		case CLProcedureId_ClimaSettingsForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CLIMA_SETTINGS );
			break;

		case CLProcedureId_SpeedModeConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_AIRFLOW_CONFIG );
			break;

		case CLProcedureId_RHConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_RH_SETTINGS );
			break;
		
		case CLProcedureId_DSCUpdateDelay:
			text	= (char*) CLLocalitation::GetText( CLTextId_DSC_DELAY_UPDATE );
			break;
			
		case CLProcedureId_PIRUpdateDelay:
			text	= (char*) CLLocalitation::GetText( CLTextId_PIR_DELAY_UPDATE );
			break;
            
		case CLProcedureId_CleanEventForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_CLEAN_EVENT_UPDATE );
			break;
            
		case CLProcedureId_PartyConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_PARTY_SETTINGS );
			break;

		case CLProcedureId_SettingsMenu:
			text	= (char*) CLLocalitation::GetText( CLTextId_SETTINGS );
			break;

		case CLProcedureId_ServiceMenu:
			text	= (char*) CLLocalitation::GetText( CLTextId_SERVICE );
			break;

#if KTS_SHOWFONTSFORM_ENABLED 
		case CLProcedureId_ShowFontsForm:
			text	= "SHOW FONTS";
			break;
#endif

		case CLProcedureId_InfoForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_INFO );
			break;

		case CLProcedureId_ReportDebugDataForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_REPORT_DATA );
			break;

		case CLProcedureId_ReportDebugDataAdminForm:
		{
			char	buffer[ 100 ];
			strcpy( buffer, (char*) CLLocalitation::GetText( CLTextId_REPORT_DATA ) );
			strcat( buffer, " (ADMIN)" );
			text	= buffer;
			break;
		}

		case CLProcedureId_SelectionVentilationControlForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_VENTILATION_CONTROL );
			break;

		case CLProcedureId_ProbesSettingsForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_PROBES_SETTINGS );
			break;

		case CLProcedureId_ModBusConfigForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_MODBUS_SETTINGS );
			break;

		case CLProcedureId_RFMChangeChannelForm:
			text	= (char*) CLLocalitation::GetText( CLTextId_RFM__CHANGE_CHANNEL );
			break;

		case CLProcedureId_EepromResetForm:
			text	= (char*)"EEPROM RESET";
            //strcat( text, "EEPROM RESET" );
			break;

		case CLProcedureId_TestUnitForm:
			text	= (char*)"TEST UNIT";
            //strcat( text, "TEST UNIT" );
			break;

		default:
			text	= (char*)"???????";
            //strcat( text, "???????" );
			break;
	}

	CLGraphics::DrawBoxWithText( menuItemButtonRectangle,
		menuItemstyle,
		text );
}

void CLLCDCommon::WriteDataPanel_DisplayWriting()
{
	RenderPanelInfo( (char*) CLLocalitation::GetText( CLTextId_WRITING_DATA ),
		0x778899, RGBColor_White, RGBColor_Black );
}

void CLLCDCommon::WriteDataPanel_DisplaySuccess( int delayTime )
{
	RenderPanelInfo( (char*) CLLocalitation::GetText( CLTextId_WRITING_DATA_COMPLETED ),
		0x65b483, RGBColor_White, RGBColor_Black,
		delayTime );
}

void CLLCDCommon::WriteDataPanel_DisplayError( ComQueue_Status* status, int delayTime )
{
	if (status != NULL)
	{
		char	text[ 20 ];
		char	tempText[ 20 ];

		sprintf( text, " (0x%02X", status->Status );
		if (status->WriteEeprom_IRSW_RESULT_W != 0)
		{
			strcat( text, "-" );
			tempText[ 0 ]	= status->WriteEeprom_IRSW_RESULT_W;
			tempText[ 1 ]	= '\0';
			strcat( text, tempText );
		}
		strcat( text, ")" );

		CLGraphics::DrawBoxWithText( CLRectangle( CLLCDCommon_WriteErrorCodePanelRectangle ),
			CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
			0xDA5757, RGBColor_White,
			1, RGBColor_Black,
			text );

	}

	RenderPanelInfo( CLLocalitation::GetText( CLTextId_WRITING_DATA_ERROR ),
		0xDA5757, RGBColor_White, RGBColor_Black,
		delayTime );
}

void CLLCDCommon::RenderPanelInfo( const char* text,
	RGBColor backgroundColor, RGBColor foregroundColor,
	RGBColor borderColor,
	int delayTime )
{
	CLGraphics::DrawBoxWithText( CLRectangle( CLLCDCommon_PanelInfoRectangle ),
		CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
		backgroundColor, foregroundColor,
		1, borderColor,
		text );

	if (delayTime > 0)
		CLKTS::Delay( delayTime );
}

void CLLCDCommon::DrawFlag_Italy( short x, short y )
{
   gLCD.setColor( 18, 124, 78 );  //Green
   gLCD.fillRect( x, y, x + 15, y + 38 );
   
   gLCD.setColor( 254, 23, 23 );  //Red
   gLCD.fillRect( x + 32, y, x + 47, y + 38 );
    
   gLCD.setColor( 255, 255, 255 );  //White
   gLCD.fillRect( x + 16, y, x + 31, y + 38 );
   
   gLCD.drawRect( x, y, x + 47, y + 38 );
}

void CLLCDCommon::DrawFlag_Germany( short x, short y )
{
   gLCD.setColor( 0, 0, 0 );  //Red
   gLCD.fillRect( x, y, x + 47, y + 12 );

   gLCD.setColor( 254, 23, 23 );  //Red
   gLCD.fillRect( x, y + 13, x + 47, y + 26 );
   
   gLCD.setColor( 255, 255, 17 );  //Yellow
   gLCD.fillRect( x, y + 25, x + 47, y + 38 );

   gLCD.setColor( 255, 255, 255);  
   gLCD.drawRect( x, y, x + 47, y + 38 );
}

void CLLCDCommon::DrawFlag_France( short x, short y )
{
   gLCD.setColor( 93, 89, 173 );  //Blue
   gLCD.fillRect( x, y, x + 15, y + 38 );
   
   gLCD.setColor( 254, 23, 23 );  //Red
   gLCD.fillRect( x + 32, y, x + 47, y + 38 );
    
   gLCD.setColor( 255, 255, 255);  //White
   gLCD.fillRect( x + 16, y, x + 31, y + 38 );
   
   gLCD.drawRect( x, y, x + 47, y + 38 );
}

void CLLCDCommon::DrawFlag_Netherlands( short x, short y )
{
   gLCD.setColor( 254, 23, 23 );  //Red
   gLCD.fillRect( x, y, x + 47, y + 13 );  
  
   gLCD.setColor( 93, 89, 173 );  //Blue
   gLCD.fillRect( x, y + 26, x + 47, y + 38 );
    
   gLCD.setColor( 255, 255, 255 );
   gLCD.fillRect( x, y + 13, x + 47, y + 26 );   //White

   gLCD.drawRect( x, y, x + 47, y + 38 );
}

void CLLCDCommon::DrawFlag_UnitedKingdom( short x, short y )
{
   gLCD.setColor( 93, 89, 173 );  //Blue
   gLCD.fillRect( x, y, x + 47, y + 38 );
   
   gLCD.setColor( 255, 255, 255 );   // White
   gLCD.fillRect( x + 16, y, x + 31, y + 38 );
   gLCD.fillRect( x, y + 10, x + 47, y + 29 );
   
   for (int i = 0; i < 6; i++)
   {
      gLCD.drawLine( x + 34 + 2 * i, y + 9 - i, x + 47, y + 9 - i ); // alto a  destra
      gLCD.drawLine( x + 34 + 2 * i, y + 29 + i, x + 47, y + 29 + i ); // basso a  destra
     
      gLCD.drawLine( x, y + 9 - i, x + 13 - 2 * i, y + 9 - i ); // alto a  sinistra
      gLCD.drawLine( x, y + 29 + i, x + 13 - 2 * i, y + 29 + i ); // basso a  sinistra
   }
   
   gLCD.setColor( 254, 23, 23 );  //Red
   
   gLCD.fillRect( x + 19, y, x + 28, y + 38 );
   gLCD.fillRect( x, y + 15, x + 47, y + 24 );
   
   for (int i = 0; i < 7; i++)
   {
       gLCD.drawLine( constrain( x + 6 - 2 * i, x, x + 47 ), y + 27 + i, x + 13 - 2 * i, y + 27 + i ); // basso a  sinistra
       gLCD.drawLine( constrain( x + 6 - 2 * i, x, x + 47), y + 11 - i, x + 13 - 2 * i, y + 11 - i ); // alto a  sinistra
       
       gLCD.drawLine( x + 33 + 2 * i, y + 11 - i, constrain( x + 39 + 2 * i, x, x + 47), y + 11 - i ); // alto a  destra
       gLCD.drawLine( x + 33 + 2 * i, y + 27 + i, constrain( x + 39 + 2 * i, x, x + 47), y + 27 + i ); // basso a  destra
   }

   gLCD.setColor( 255, 255, 255 );  
   gLCD.drawRect( x, y, x + 47, y + 38 );
}

void CLLCDCommon::DrawFlag_Portughese( short x, short y )
{
   gLCD.setColor( 0, 96, 0 );  //Verde
   gLCD.fillRect( x, y, x + 20, y + 38 );
   
   gLCD.setColor( 254, 23, 23 );  //Red
   gLCD.fillRect( x + 21, y, x + 47, y + 38 );
    
   gLCD.setColor( 255, 255, 255 );  //White  
   gLCD.drawRect( x, y, x + 47, y + 38 );  
}

void CLLCDCommon::DrawFlag_Polish( short x, short y )
{
	CLRectangle	rectangle( x, y, x + 47, y + 38 );
	
	gLCD.setRGBColor( RGBColor_White );
	gLCD.fillRect( x, y, x + 48 - 1, y + 19 - 1 );

	gLCD.setRGBColor( RGBColor_Red );
	gLCD.fillRect( x, y + 19, x + 48 - 1, y + 38 - 1 );

	CLGraphics::DrawBorder( rectangle, CLGraphicStyleOptions_Default, 1, RGBColor_White );
}

void CLLCDCommon::DrawFlag_Slovenia( short x, short y )
{
	CLRectangle	rectangle( x, y, x + 47, y + 38 );

	CLGraphics::Draw( rectangle, CLGraphicStyleOptions_HVAlign_Center, &SlovenianFlagImage );
	CLGraphics::DrawBorder( rectangle, CLGraphicStyleOptions_Default, 1, RGBColor_White );
}

void CLLCDCommon::DrawFlag_Hungary( short x, short y )
{
	CLRectangle	rectangle( x, y, x + 47, y + 38 );
	
	CLGraphics::DrawBox( CLRectangle( x, y, x + 47, y + 12 ), CLGraphicStyleOptions_Default, 0xCD2A3E );
	CLGraphics::DrawBox( CLRectangle( x, y + 13, x + 47, y + 25 ), CLGraphicStyleOptions_Default, RGBColor_White );
	CLGraphics::DrawBox( CLRectangle( x, y + 26, x + 47, y + 38 ), CLGraphicStyleOptions_Default, 0x436F4D );

	CLGraphics::DrawBorder( rectangle, CLGraphicStyleOptions_Default, 1, RGBColor_White );
}

void CLLCDCommon::DrawFlag_Bulgaria( short x, short y )
{
	CLRectangle	rectangle( x, y, x + 47, y + 38 );
	
	CLGraphics::DrawBox( CLRectangle( x, y, x + 47, y + 12 ), CLGraphicStyleOptions_Default, RGBColor_White );
	CLGraphics::DrawBox( CLRectangle( x, y + 13, x + 47, y + 25 ), CLGraphicStyleOptions_Default, 0x00966E );
	CLGraphics::DrawBox( CLRectangle( x, y + 26, x + 47, y + 38 ), CLGraphicStyleOptions_Default, 0xD62612 );

	CLGraphics::DrawBorder( rectangle, CLGraphicStyleOptions_Default, 1, RGBColor_White );
}

void CLLCDCommon::DrawFlag_Romania( short x, short y )
{
	CLRectangle	rectangle( x, y, x + 47, y + 38 );
	
	CLGraphics::DrawBox( CLRectangle( x, y, x + 15, y + 38 ), CLGraphicStyleOptions_Default, 0x002B7F );
	CLGraphics::DrawBox( CLRectangle( x + 16, y, x + 31, y + 38 ), CLGraphicStyleOptions_Default, 0xFCD116 );
	CLGraphics::DrawBox( CLRectangle( x + 32, y, x + 47, y + 38 ), CLGraphicStyleOptions_Default, 0xCE1126 );

	CLGraphics::DrawBorder( rectangle, CLGraphicStyleOptions_Default, 1, RGBColor_White );
}

void CLLCDCommon::DrawOnOffIcon( short x, short y, RGBColor color )
{
	gLCD.setRGBColor( color );
	gLCD.fillCircle( x + 30, y + 35, 30 );

	gLCD.setRGBColor( RGBColor_Black );
	gLCD.fillCircle( x + 30, y + 35, 21 );
	gLCD.fillRect( x + 20, y, x + 40, y + 20 );

	gLCD.setRGBColor( color );
	gLCD.fillRect( x + 25, y, x + 35, y + 38 );
}

void CLLCDCommon::DrawMoonIcon( short x, short y, RGBColor backgroundColor, RGBColor penColor )
{
	CLImage*	image	= &MoonMonoImage;

	image->DrawXY( x, y, backgroundColor, penColor );
	//CLGraphics::DrawMonoImage( x, y, CLImage2_Moon_Width, CLImage2_Moon_Height, CLGraphicStyleOptions_Default, CLImage2_Moon, backgroundColor, penColor );
}

void CLLCDCommon::DrawSunIcon( short x, short y, RGBColor backgroundColor, RGBColor penColor )
{
	CLImage*	image	= &SunMonoImage;

	image->DrawXY( x, y, backgroundColor, penColor );

	//CLGraphics::DrawMonoImage( x, y, CLImage2_Sun_Width, CLImage2_Sun_Height, CLGraphicStyleOptions_Default, CLImage2_Sun, backgroundColor, penColor );
}

void CLLCDCommon::DrawDateTimeBox( short x, short y )
{
	char	text[ 20 ];

	//gRTC.getDate();
	//gRTC.getTime();

	sprintf( text, "%02d:%02d %c%s",
		gRTC.getHour(),
		gRTC.getMinute(),
		(gKTSEeprom.GetDaylightSavingTime() ? '*' : ' '),
		CLLocalitation::GetText( CLTextId_SUN + gRTC.getWeekday() ) );
	CLGraphics::DrawText( x, y, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );

	sprintf( text, "%02d/%02d/%04d",
		gRTC.getDay(),
		gRTC.getMonth(),
		(gRTC.getCentury() == 0 ? 2000 : 1900) + gRTC.getYear() );
	CLGraphics::DrawText( x, y + 25, CLGraphicStyleOptions_Font_Small,
		RGBColor_Black, RGBColor_White,
		text );
}

void CLLCDCommon::DrawWeeklyIcon( short x, short y, RGBColor color )
{
	RGBColor	saveColor	= gLCD.getRGBColor();

	gLCD.setRGBColor( color );

	gLCD.drawCircle( x + 10, y + 10, 10 );
	gLCD.drawCircle( x + 10, y + 10, 9 );

	gLCD.drawLine( x + 10, y + 10, x + 19, y + 10 );
	gLCD.drawLine( x + 10, y + 9, x + 19, y + 9 );

	gLCD.drawLine( x + 10, y + 10, x + 10, y );
	gLCD.drawLine( x + 11, y + 10, x + 11, y );

	gLCD.setRGBColor( saveColor );
}

CLCloseFormMessageBoxResult CLLCDCommon::MessageBoxCloseForm( bool dataChanged, bool discardChanges )
{
	if (!dataChanged || discardChanges)
		return CLCloseFormMessageBoxResult_Close;

	switch (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNoCancel, CLMessageBoxGravity_Question,
		CLLocalitation::GetText( CLTextId_DATA_CHANGED ),
		CLLocalitation::GetText( CLTextId_SAVE_CHANGES ) ))
	{
		case CLMessageBoxResult_Yes:
			return CLCloseFormMessageBoxResult_SaveAndClose;

		case CLMessageBoxResult_Cancel:
			return CLCloseFormMessageBoxResult_Cancel;
	}

	return CLCloseFormMessageBoxResult_Close;
}

void CLLCDCommon::DrawRFMSignalIcon( short x, short y, int signalLevel )
{
	if (signalLevel < 0)
		signalLevel	= 0;
	else
	if (signalLevel > 4)
		signalLevel	= 4;

	// Prima tacca level 1
	CLGraphics::DrawBox( CLRectangle( x + 9, y + 25, x + 12, y + 30 ), CLGraphicStyleOptions_Default,
		(signalLevel >= 1 ? RGBColor_White : 0x808080) );

	// Seconda tacca level 2
	CLGraphics::DrawBox( CLRectangle( x + 15, y + 22, x + 18, y + 30 ), CLGraphicStyleOptions_Default,
		(signalLevel >= 2 ? RGBColor_White : 0x808080) );

	// Terza tacca level 3
	CLGraphics::DrawBox( CLRectangle( x + 21, y + 18, x + 24, y + 30 ), CLGraphicStyleOptions_Default,
		(signalLevel >= 3 ? RGBColor_White : 0x808080) );

	// Quarta tacca level 4
	CLGraphics::DrawBox( CLRectangle( x + 27, y + 14, x + 30, y + 30 ), CLGraphicStyleOptions_Default,
		(signalLevel >= 4 ? RGBColor_White : 0x808080) );

	((CLImage*) &WirelessAntennaMonoImage)->DrawXY( x + 12, y + 3,
		RGBColor_Black, (signalLevel == 0 ? RGBColor_Red : RGBColor_White) );
}

void CLLCDCommon::RenderFireConfiguration( CLRectangle& rectangle,
	byte configuration )
{
	CLRectangle	houseFireRectangle;
	CLRectangle	supplyVentilationRectangle;
	CLRectangle	extractVentilationRectangle;

	// Draw House Fire
	houseFireRectangle.Set1( rectangle.GetX1() + (rectangle.GetWidth() / 2) - (CLImage565_HouseFire_Width / 2),
		rectangle.GetY1() + (rectangle.GetHeight() / 2) - (CLImage565_HouseFire_Height / 2) );
	houseFireRectangle.SetSize( CLImage565_HouseFire_Width, CLImage565_HouseFire_Height );
	CLGraphics::Draw( houseFireRectangle, CLGraphicStyleOptions_HVAlign_Center,
		&HouseFireImage );

	supplyVentilationRectangle.Set1( houseFireRectangle.GetX1() - CLImage565_FanOn_Width - 5,
			houseFireRectangle.GetY1() + (CLImage565_HouseFire_Height - CLImage565_FanOn_Height - CLImage565_AirSupply_Height) );
	supplyVentilationRectangle.SetSize( CLImage565_FanOn_Width, CLImage565_FanOn_Height );

	extractVentilationRectangle.Set1( houseFireRectangle.GetX1() + CLImage565_HouseFire_Width + 5,
			houseFireRectangle.GetY1() + (CLImage565_HouseFire_Height - CLImage565_FanOn_Height - CLImage565_AirExtract_Height) );
	extractVentilationRectangle.SetSize( CLImage565_FanOn_Width, CLImage565_FanOn_Height );

	switch (configuration)
	{
		case INP_12V_ALM_FIRE_UNIT_STOP:
			CLGraphics::Draw( supplyVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOffImage );
			CLGraphics::Draw( extractVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOffImage );
			break;

		case INP_12V_ALM_FIRE_VENT_MAX:
			CLGraphics::Draw( supplyVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOnImage );
			CLGraphics::Draw( extractVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOnImage );
			break;

		case INP_12V_ALM_FIRE_ONLY_EXTRACT:
			CLGraphics::Draw( supplyVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOffImage );
			CLGraphics::Draw( extractVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOnImage );
			break;

		case INP_12V_ALM_FIRE_ONLY_SUPPLY:
			CLGraphics::Draw( supplyVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOnImage );
			CLGraphics::Draw( extractVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
				&FanOffImage );
			break;
	}

	supplyVentilationRectangle.MoveOffset( 0, supplyVentilationRectangle.GetHeight() );
	CLGraphics::Draw( supplyVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
		&AirSupplyImage );

	extractVentilationRectangle.MoveOffset( 0, extractVentilationRectangle.GetHeight() );
	CLGraphics::Draw( extractVentilationRectangle, CLGraphicStyleOptions_HVAlign_Center,
		&AirExtractImage );
}


