 /*************************************************************************************
 *  file:			CLGraphics.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLGRAPHICS_H
#define __CLGRAPHICS_H

#include "CLCommon.h"
#include "TFTLCD.h"
#include <float.h>

// =============================================================================
// CLPoint [struct]
// =============================================================================
// Description: Punto
// -----------------------------------------------------------------------------
struct _PACK CLPoint
{
	public: CLPoint();
	public: CLPoint( short x, short y );

	private: short m_X;
	public: short GetX();
	public: void SetX( short value );

	private: short m_Y;
	public: short GetY();
	public: void SetY( short value );

	public: void Set( short x, short y );

	public: void MoveOffset( short x, short y );
};
// -----------------------------------------------------------------------------
// CLPoint [struct]
// =============================================================================

// =============================================================================
// CLRectangle [struct]
// =============================================================================
// Description: Rettangolo
// -----------------------------------------------------------------------------
struct _PACK CLRectangle
{
	public: CLRectangle( CLRectangle const & rectangle );
	public: CLRectangle();
	public: CLRectangle( short x1, short y1, short x2, short y2 );

	private: short m_X1;
	public: short GetX1() const;
	public: void SetX1( short value );

	private: short m_Y1;
	public: short GetY1() const;
	public: void SetY1( short value );

	private: short m_X2;
	public: short GetX2() const;
	public: void SetX2( short value );

	private: short m_Y2;
	public: short GetY2() const;
	public: void SetY2( short value );

	public: short GetHeight() const;
	public: short GetWidth() const;

	public: void Set1( short x1, short y1 );
	public: void Set2( short x2, short y2 );
	public: void SetSize( short width, short height );

	public: CLPoint GetPoint1() const;
	public: CLPoint GetPoint2() const;

	public: void Set( short x1, short y1, short x2, short y2 );
	public: void Set( const CLRectangle& rectangle );

	public: void Truncate( short x1, short y1, short x2, short y2 );
	public: void Truncate( const CLRectangle& rectangle );

	public: bool Contains( short x, short y ) const;
	public: void MoveOffset( short x, short y );

	public: void Inflate( short dx, short dy );
};
// -----------------------------------------------------------------------------
// CLRectangle [struct]
// =============================================================================

// =============================================================================
// CLDrawer [class]
// =============================================================================
// Description: Drawer
// -----------------------------------------------------------------------------
class _PACK CLDrawer
{
	public: enum DrawerType : byte
	{
		DrawerType_Image,
		DrawerType_Symbol,
	};

	public: virtual DrawerType GetDrawerType() = 0;
	public: virtual short GetWidth() = 0;
	public: virtual short GetHeight() = 0;
	public: virtual void Draw( const CLRectangle& rectangle,
		RGBColor backgroundColor = RGBColor_Empty, RGBColor foregroundColor = RGBColor_Empty ) = 0;

	public: void DrawXY( short x, short y,
		RGBColor backgroundColor = RGBColor_Empty, RGBColor foregroundColor = RGBColor_Empty );
};
// -----------------------------------------------------------------------------
// CLDrawer [class]
// =============================================================================

// =============================================================================
// CLImage [class]
// =============================================================================
// Description: Image
// -----------------------------------------------------------------------------
class _PACK CLImage
	: public CLDrawer
{
	public: enum ImageType : byte
	{
		ImageType_2Bit,
		ImageType_16Bit_565
	};

	public: CLImage( ImageType type,
		short width,
		short height,
		const unsigned char* data,
		const unsigned char* mask = NULL );

	public: virtual DrawerType GetDrawerType();

	private: ImageType m_Type;
	public: ImageType GetType();

	private: short m_Width;
	public: virtual short GetWidth();

	private: short m_Height;
	public: virtual short GetHeight();

	private: const unsigned char* m_Data;
	public: const unsigned char* GetData();

	private: const unsigned char* m_Mask;
	public: const unsigned char* GetMask();

	public: virtual void Draw( const CLRectangle& rectangle,
		RGBColor backgroundColor = RGBColor_Empty, RGBColor foregroundColor = RGBColor_Empty );
};
// -----------------------------------------------------------------------------
// CLImage [class]
// =============================================================================

// =============================================================================
// CLSymbol [class]
// =============================================================================
class _PACK CLSymbol
	: public CLDrawer
{
	public: virtual DrawerType GetDrawerType();
};
// -----------------------------------------------------------------------------
// CLSymbol [class]
// =============================================================================

const int CLGraphicStyleOptions_HAlign_Mask	= 0x0003;
const int CLGraphicStyleOptions_VAlign_Mask	= 0x000C;
const int CLGraphicStyleOptions_Font_Mask	= 0x0180;

// =============================================================================
// CLGraphicStyleOptions [enum]
// -----------------------------------------------------------------------------
// Description: Opzioni per lo stile grafico
// =============================================================================
enum CLGraphicStyleOptions : unsigned short
{
	CLGraphicStyleOptions_HAlign_Left		= 0x0000,
	CLGraphicStyleOptions_HAlign_Center		= 0x0001,
	CLGraphicStyleOptions_HAlign_Right		= 0x0002,
	CLGraphicStyleOptions_VAlign_Top		= 0x0000,
	CLGraphicStyleOptions_VAlign_Middle		= 0x0004,
	CLGraphicStyleOptions_VAlign_Bottom		= 0x0008,
	CLGraphicStyleOptions_Text_Underline	= 0x0010,
	CLGraphicStyleOptions_Text_MultiLine	= 0x0020,
	CLGraphicStyleOptions_BorderRound_No	= 0x0000,
	CLGraphicStyleOptions_BorderRound_Yes	= 0x0040,
	CLGraphicStyleOptions_Font_Current		= 0x0000,
	CLGraphicStyleOptions_Font_Small		= 0x0080,
	CLGraphicStyleOptions_Font_Big			= 0x0100,
	CLGraphicStyleOptions_TextAlignBy_Char	= 0x0000,
	CLGraphicStyleOptions_TextAlignBy_Pixel	= 0x0200,
	CLGraphicStyleOptions_Default			= CLGraphicStyleOptions_HAlign_Left | CLGraphicStyleOptions_VAlign_Top | CLGraphicStyleOptions_BorderRound_No | CLGraphicStyleOptions_Font_Current,
	CLGraphicStyleOptions_HVAlign_Center	= CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_VAlign_Middle
};

// =============================================================================
// CLGraphicStyle [struct]
// -----------------------------------------------------------------------------
// Description: Stile grafico
// =============================================================================
struct _PACK CLGraphicStyle
{
	CLGraphicStyle();
	CLGraphicStyle( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
		RGBColor maskBackgroundColor = RGBColor_Empty, RGBColor maskForegroundColor = RGBColor_Empty );
	CLGraphicStyle( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
		byte borderWidth, RGBColor borderColor,
		RGBColor maskBackgroundColor = RGBColor_Empty, RGBColor maskForegroundColor = RGBColor_Empty );

	void Set( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor );
	void Set( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
		byte borderWidth, RGBColor borderColor );
	void Set( CLGraphicStyle& style );
	void SetMask( RGBColor maskBackgroundColor, RGBColor maskForegroundColor );

	RGBColor BackgroundColor;
	RGBColor ForegroundColor;
	byte BorderWidth;
	RGBColor BorderColor;
	unsigned short Options;
	RGBColor MaskBackgroundColor;
	RGBColor MaskForegroundColor;
};

enum CLDrawBarOptions
{
	CLDrawBarOptions_Direction_Horizontal	= 0x00,
	CLDrawBarOptions_Direction_Vertical		= 0x01,
	CLDrawBarOptions_StartWith_Min			= 0x00,
	CLDrawBarOptions_StartWith_Max			= 0x02,
	CLDrawBarOptions_BarShape_Rectangle		= 0x00,
	CLDrawBarOptions_BarShape_Progressive	= 0x04,
	CLDrawBarOptions_Flip_No				= 0x00,
	CLDrawBarOptions_Flip_Yes				= 0x08,
	CLDrawBarOptions_Data_SingleOrMultiple	= 0x00,
	CLDrawBarOptions_Data_Range				= 0x10,

	CLDrawBarOptions_Default					= CLDrawBarOptions_Direction_Horizontal | CLDrawBarOptions_StartWith_Min | CLDrawBarOptions_BarShape_Rectangle | CLDrawBarOptions_Flip_No
};

// =============================================================================
// CLGraphics [class]
// -----------------------------------------------------------------------------
// Description: Funzioni grafiche
// =============================================================================
class CLGraphics
{
	// --------------------------------------
	// Primitive
	// --------------------------------------
	public: static void DrawBorder( const CLRectangle& rectangle, short options,
		byte borderWidth, RGBColor borderColor );

	public: static void DrawLine( short x1, short y1, short x2, short y2,
		RGBColor color );

	public: static RGBColor AdjustBrightness( RGBColor color, short level );

	// --------------------------------------
	// Draw Drawer
	// --------------------------------------
	public: static void Draw( const CLRectangle& rectangle,
		unsigned short options,
		CLDrawer* drawer,
		RGBColor drawerBackgroundColor = RGBColor_Empty, RGBColor drawerForegroundColor = RGBColor_Empty );

	// --------------------------------------
	// Draw Text
	// --------------------------------------
	private: static void _SetFont( unsigned short options );

	private: static void _DrawTextLine( short x, short y, short width, unsigned short options,
		const char* text, short textLength = -1 );

	private: static void _DrawText( const CLRectangle& rectangle, unsigned short options,
		const char* text );

	public: static void DrawText( short x, short y, unsigned short options,
		const char* text );

	public: static void DrawText( short x, short y, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		const char* text );
	
	public: static void DrawText( const CLRectangle& rectangle, unsigned short options,
		const char* text );

	public: static void DrawText( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		const char* text );

	public: static void DrawText( short x, short y, unsigned short options,
		const char* text, short charCount );

	public: static void DrawText( short x, short y, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		const char* text, short charCount );

	// --------------------------------------
	// DrawBox
	// --------------------------------------
	public: static void DrawBox( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor,
		byte borderWidth, RGBColor borderColor );

	public: static void DrawBox( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor );

	public: static void DrawBox( const CLRectangle& rectangle,
		CLGraphicStyle& style );

	// --------------------------------------
	// DrawBox With Text
	// --------------------------------------
	public: static void DrawBoxWithText( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		byte borderWidth, RGBColor borderColor,
		const char* text );

	public: static void DrawBoxWithText( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		const char* text );

	public: static void DrawBoxWithText( const CLRectangle& rectangle,
		CLGraphicStyle& style,
		const char* text );

	// --------------------------------------
	// DrawBox With Drawer
	// --------------------------------------
	public: static void DrawBoxWithDrawer( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		byte borderWidth, RGBColor borderColor,
		CLDrawer* drawer,
		RGBColor drawerBackgroundColor = RGBColor_Empty, RGBColor drawerForegroundColor = RGBColor_Empty );

	public: static void DrawBoxWithDrawer( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor, RGBColor foregroundColor,
		CLDrawer* drawer,
		RGBColor drawerBackgroundColor = RGBColor_Empty, RGBColor drawerForegroundColor = RGBColor_Empty );

	public: static void DrawBoxWithDrawer( const CLRectangle& rectangle,
		CLGraphicStyle& style,
		CLDrawer* drawer );

	// --------------------------------------
	// Draw ProgressBar
	// --------------------------------------
	private: static void _DrawProgressBar_CheckDataValue( float min, float max,
		float* values, byte valueCount,
		float currentValue, short& currentIndex );

	private: static void _DrawProgressBar_CheckDataRange( float min, float max,
		float* values, byte valueCount,
		float currentValue, short& currentIndex );

	private: static void _DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
		RGBColor backgroundColor, RGBColor barFalseColor, RGBColor* barTrueColors,
		float min, float max, float* values, byte valueCount,
		byte barSize, byte barSpaceSize,
		short* outPositions );

	public: static void DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
		RGBColor backgroundColor, RGBColor barFalseColor, RGBColor barTrueColor, 
		float min, float max, float value,
		byte barSize, byte barSpaceSize,
		short* outPosition = NULL );

	public: static void DrawProgressBarRange( const CLRectangle& rectangle, unsigned short options, 
		RGBColor backgroundColor, RGBColor barFalseColor, RGBColor barTrueColor, 
		float min, float max, float rangeValue0, float rangeValue1,
		byte barSize, byte barSpaceSize,
		short* outPositions = NULL );

	public: static void DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
		RGBColor backgroundColor, RGBColor barFalseColor, RGBColor* barTrueColors, 
		float min, float max, float* values, byte valueCount,
		byte barSize, byte barSpaceSize,
		short* outPositions = NULL );
};

#endif

