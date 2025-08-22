 /*************************************************************************************
 *  file:			CLLCDCommon.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLLCDCommon_h
#define __CLLCDCommon_h

#include "TFTLCD.h"
#include "CLGraphics.h"
#include "CLCommon.h"
#include "CLKTS.h"
#include "CLFonts.h"
#include "CLProcedure.h"
#include "RDAlarms.h"

#define HIGH_BRIGHTESS    60
#define LOW_BRIGHTESS     1200

enum CLDrawArrowButtonDirection
{
	CLDrawArrowButtonDirection_Left,
	CLDrawArrowButtonDirection_Right,
	CLDrawArrowButtonDirection_Up,
	CLDrawArrowButtonDirection_Down
};

const RGBColor RGBColor_Button_Background			= 0x404080;
const RGBColor RGBColor_Button_SelectedBackground	= 0x51BD51;
const RGBColor RGBColor_Button_DisabledForeground	= 0xC9C9C9;
const RGBColor RGBColor_Button_Border				= RGBColor_White;
const RGBColor RGBColor_Button_Text					= RGBColor_White;
const RGBColor RGBColor_Button_PressedBorder		= RGBColor_Red;
const RGBColor RGBColor_SunIcon_Pen					= 0xECD62C;
const RGBColor RGBColor_MoonIcon_Pen				= 0xBACBE1;
const RGBColor RGBColor_UpDownIcon_Pen				= 0xC4C8DF;

const RGBColor InputMeausure_ProgressBar_Color_PowerOff_BarTrue		= RGBColor_Red;
const RGBColor InputMeausure_ProgressBar_Color_BarTrue				= RGBColor_Green;
const RGBColor InputMeausure_ProgressBar_Color_BarFalse				= 0x606060;
const RGBColor InputMeausure_ProgressBar_Color_Background			= RGBColor_Black;

//const RGBColor ProgressBar_Color_BarTrueIncreaseCO2_RH	= 0xFF7300; // orange
const RGBColor ProgressBar_Color_BarTrueIncreaseCO2_RH	= 0xC0BEB9; // grey

const RGBColor CAF_FSC_ProgressBar_Color_BarTrue	= RGBColor_Green;
const RGBColor CAF_FSC_ProgressBar_Color_BarTrueIncreaseCO2_RH	= ProgressBar_Color_BarTrueIncreaseCO2_RH;
const RGBColor CAF_FSC_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor CAF_FSC_ProgressBar_Color_Background	= RGBColor_Black;

//const RGBColor CAP_ProgressBar_Color_BarTrue	= 0xA38F5A;
const RGBColor CAP_ProgressBar_Color_BarTrue	= 0xffcb3d; // Ori FFE08C
const RGBColor CAP_ProgressBar_Color_BarTrueIncreaseCO2_RH	= ProgressBar_Color_BarTrueIncreaseCO2_RH;
const RGBColor CAP_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor CAP_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor CO2_ProgressBar_Color_BarTrue	= RGBColor_Green;
const RGBColor CO2_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor CO2_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor VOC_ProgressBar_Color_BarTrue	= RGBColor_Green;
const RGBColor VOC_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor VOC_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor RH_ProgressBar_Color_BarTrue		= RGBColor_Green;
const RGBColor RH_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor RH_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor Temperature_Hot_Color	= 0xFF9421;
const RGBColor Temperature_Cold_Color	= 0x3296ED;

const RGBColor Temperature_ProgressBar_Color_BarTrue	= RGBColor_Green;
const RGBColor Temperature_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor Temperature_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor TemperatureHot_ProgressBar_Color_BarTrue		= Temperature_Hot_Color;
const RGBColor TemperatureHot_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor TemperatureHot_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor TemperatureCold_ProgressBar_Color_BarTrue	= Temperature_Cold_Color;
const RGBColor TemperatureCold_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor TemperatureCold_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor WeeklyTime_ProgressBar_Color_BarTrue		= RGBColor_Green;
const RGBColor WeeklyTime_ProgressBar_Color_BarFalse	= 0x606060;
const RGBColor WeeklyTime_ProgressBar_Color_Background	= RGBColor_Black;

const RGBColor PowerOnOff_Icon_Color_On		= 0x00FF00;
const RGBColor PowerOnOff_Icon_Color_Off	= 0xFF1919;

const int UpDownButtons_Delay	= 80;

// Template GenericForm
extern CLRectangle		GenericForm_Title_Rectangle;
extern CLGraphicStyle	GenericForm_Title_BigFont_Style;
const int				GenericForm_Title_BigFont_MaxLength		= 19;
const int				GenericForm_Title_SmallFont_MaxLength	= 39;
extern CLGraphicStyle	GenericForm_Title_SmallFont_Style;

extern CLRectangle		GenericForm_Data_Rectangle;
extern CLGraphicStyle	GenericForm_Data_Style;

extern CLGraphicStyle	GenericForm_Group_Style;
extern CLGraphicStyle	GenericForm_GroupDisabled_Style;

// Template ViewForm
extern CLRectangle ViewForm_PreviousButtonRectangle;
extern CLRectangle ViewForm_NextButtonRectangle;
extern CLRectangle ViewForm_BackButtonRectangle;

// Template EditForm
extern CLRectangle EditForm_SaveButtonRectangle;
extern CLRectangle EditForm_OkButtonRectangle;
extern CLRectangle EditForm_BackButtonRectangle;

// Generic Template
extern CLRectangle Form_HomeButtonRectangle;

extern CLGraphicStyle GenericButtonStyle_NormalBlack_BigFont;

extern CLGraphicStyle GenericButtonStyle_Normal_UpDown;
extern CLGraphicStyle GenericButtonStyle_Disabled_UpDown;

extern CLGraphicStyle GenericButtonStyle_Normal_BigFont;
extern CLGraphicStyle GenericButtonStyle_Disabled_BigFont;
extern CLGraphicStyle GenericButtonStyle_Selected_BigFont;
extern CLGraphicStyle GenericButtonStyle_Normal_BigFont_Multiline;
extern CLGraphicStyle GenericButtonStyle_Disabled_BigFont_Multiline;
extern CLGraphicStyle GenericButtonStyle_Selected_BigFont_Multiline;

extern CLGraphicStyle GenericButtonStyle_Normal_SmallFont;
extern CLGraphicStyle GenericButtonStyle_Disabled_SmallFont;
extern CLGraphicStyle GenericButtonStyle_Selected_SmallFont;
extern CLGraphicStyle GenericButtonStyle_Normal_SmallFont_Multiline;
extern CLGraphicStyle GenericButtonStyle_Disabled_SmallFont_Multiline;
extern CLGraphicStyle GenericButtonStyle_Selected_SmallFont_Multiline;

extern CLGraphicStyle GenericButtonStyle_On_BigFont;
extern CLGraphicStyle GenericButtonStyle_Off_BigFont;

extern CLGraphicStyle GenericButtonStyle_On_SmallFont;
extern CLGraphicStyle GenericButtonStyle_Off_SmallFont;

enum CLCloseFormMessageBoxResult
{
	CLCloseFormMessageBoxResult_SaveAndClose,
	CLCloseFormMessageBoxResult_Close,
	CLCloseFormMessageBoxResult_Cancel
};

class CLLCDCommon
{
	public: static void DrawArrowButton( short x, short y, CLDrawArrowButtonDirection direction );
	public: static void DrawHomeButton( short x, short y );

	public: static void DrawPreviousButton( const CLRectangle& rectangle, CLGraphicStyle& style );
	public: static void DrawNextButton( const CLRectangle& rectangle, CLGraphicStyle& style );
	public: static void DrawBackButton( const CLRectangle& rectangle, CLGraphicStyle& style );
	public: static void DrawCancelButton( const CLRectangle& rectangle, CLGraphicStyle& style );
	public: static void DrawSaveButton( const CLRectangle& rectangle, CLGraphicStyle& style );
	public: static void DrawOkButton( const CLRectangle& rectangle, CLGraphicStyle& style );

	public: static void DrawButtonMark( const CLRectangle& rectangle, RGBColor boxColor );
	public: static void DrawButtonMark( short x1, short y1, short x2, short y2, RGBColor boxColor );

	public: static void DrawGenericButton( const CLRectangle& rectangle, CLGraphicStyle& style, const char* text, bool showMark = false );
	public: static void DrawGenericButton( const CLRectangle& rectangle, CLGraphicStyle& style, CLDrawer* drawer, bool showMark = false );

	public: static void WaitButton( const CLRectangle& rectangle );
	public: static void WaitButton_Pressed( const CLRectangle& rectangle );
	public: static void WaitButton_Unpressed( const CLRectangle& rectangle );

	public: static void DrawMenuItem( CLProcedureId procedureId,
		const CLRectangle& menuItemButtonRectangle,
		CLGraphicStyle& style );

	public: static void WriteDataPanel_DisplayWriting();
	public: static void WriteDataPanel_DisplaySuccess( int delayTime = 3000 );
	public: static void WriteDataPanel_DisplayError( ComQueue_Status* status = NULL, int delayTime = 3000 );

	public: static void DrawFlag_Italy( short x, short y );
	public: static void DrawFlag_Germany( short x, short y );
	public: static void DrawFlag_France( short x, short y );
	public: static void DrawFlag_Netherlands( short x, short y );
	public: static void DrawFlag_UnitedKingdom( short x, short y );
	public: static void DrawFlag_Portughese( short x, short y );
	public: static void DrawFlag_Polish( short x, short y );
	public: static void DrawFlag_Slovenia( short x, short y );
	public: static void DrawFlag_Hungary( short x, short y );
	public: static void DrawFlag_Bulgaria( short x, short y );
	public: static void DrawFlag_Romania( short x, short y );

	public: static void DrawOnOffIcon( short x, short y, RGBColor color );

	public: static void DrawMoonIcon( short x, short y, RGBColor backgroundColor, RGBColor penColor );
	public: static void DrawSunIcon( short x, short y, RGBColor backgroundColor, RGBColor penColor );

	public: static void DrawDateTimeBox( short x, short y );
	
	public: static void DrawWeeklyIcon( short x, short y, RGBColor color = RGBColor_White );

	public: static CLCloseFormMessageBoxResult MessageBoxCloseForm( bool dataChanged, bool discardChanges );
	public: static void DrawRFMSignalIcon( short x, short y, int signalLevel );

	public: enum CLPanelInfoType
	{
		CLPanelInfoType_Info,
		CLPanelInfoType_Error,
		CLPanelInfoType_War
	};

	public: static void RenderPanelInfo( const char* message,
		RGBColor backgroundColor, RGBColor foregroundColor,
		RGBColor borderColor,
		int delayTime = 0 );

	public: static void RenderFireConfiguration( CLRectangle& rectangle,
		byte configuration );
};

#endif

