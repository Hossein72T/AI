/*************************************************************************************
*  file:			CLGraphics.cpp
*
*  Author/Date:	Paolo Menchi marzo 2014
*
*  Descrizione:	...
*
*************************************************************************************/

#ifdef _CLIKTS
#include "CLIKTS.h"
#endif

#include "CLGraphics.h"
#include "CLKTS.h"
#include <string.h>
#include "CLFonts.h"

// =============================================================================
// CLRectangle [struct]
// -----------------------------------------------------------------------------
CLRectangle::CLRectangle()
{
	m_X1	=
	m_Y1	=
	m_X2	=
	m_Y2	= 0;
}

CLRectangle::CLRectangle( const CLRectangle& rectangle )
{
	m_X1	= rectangle.m_X1;
	m_Y1	= rectangle.m_Y1;
	m_X2	= rectangle.m_X2;
	m_Y2	= rectangle.m_Y2;
}

CLRectangle::CLRectangle( short x1, short y1, short x2, short y2 )
{
	m_X1	= x1;
	m_Y1	= y1;
	m_X2	= x2;
	m_Y2	= y2;
}

short CLRectangle::GetX1() const
{
	return m_X1;
}

void CLRectangle::SetX1( short value )
{
	m_X1	= value;
}

short CLRectangle::GetY1() const
{
	return m_Y1;
}

void CLRectangle::SetY1( short value )
{
	m_Y1	= value;
}

short CLRectangle::GetX2() const
{
	return m_X2;
}

void CLRectangle::SetX2( short value )
{
	m_X2	= value;
}

short CLRectangle::GetY2() const
{
	return m_Y2;
}

void CLRectangle::SetY2( short value )
{
	m_Y2	= value;
}

void CLRectangle::Set1( short x1, short y1 )
{
	m_X1	= x1;
	m_Y1	= y1;
}

void CLRectangle::Set2( short x2, short y2 )
{
	m_X2	= x2;
	m_Y2	= y2;
}

void CLRectangle::SetSize( short width, short height )
{
	m_X2	= (width > 0 ? m_X1 + width - 1 : m_X1);
	m_Y2	= (height > 0 ? m_Y1 + height - 1 : m_Y1);
}

short CLRectangle::GetHeight() const
{
	return m_Y2 - m_Y1 + 1;
}

short CLRectangle::GetWidth() const
{
	return m_X2 - m_X1 + 1;
}

CLPoint CLRectangle::GetPoint1() const
{
	return CLPoint( m_X1, m_Y1 );
}

CLPoint CLRectangle::GetPoint2() const
{
	return CLPoint( m_X2, m_Y2 );
}

void CLRectangle::Set( short x1, short y1, short x2, short y2 )
{
	m_X1	= x1;
	m_Y1	= y1;
	m_X2	= x2;
	m_Y2	= y2;
}

void CLRectangle::Set( const CLRectangle& rectangle )
{
	m_X1	= rectangle.m_X1;
	m_Y1	= rectangle.m_Y1;
	m_X2	= rectangle.m_X2;
	m_Y2	= rectangle.m_Y2;
}

void CLRectangle::Truncate( short x1, short y1, short x2, short y2 )
{
	if (m_X1 < x1)
		m_X1	= x1;
	if (m_Y1 < y1)
		m_Y1	= y1;
	if (m_X2 > x2)
		m_X2	= x2;
	if (m_Y2 > y2)
		m_Y2	= y2;
}

void CLRectangle::Truncate( const CLRectangle& rectangle )
{
	if (m_X1 < rectangle.m_X1)
		m_X1	= rectangle.m_X1;
	if (m_Y1 < rectangle.m_Y1)
		m_Y1	= rectangle.m_Y1;
	if (m_X2 > rectangle.m_X2)
		m_X2	= rectangle.m_X2;
	if (m_Y2 > rectangle.m_Y2)
		m_Y2	= rectangle.m_Y2;
}

bool CLRectangle::Contains( short x, short y ) const
{
	return x >= m_X1 && x <= m_X2 && y >= m_Y1 && y <= m_Y2;
}

void CLRectangle::MoveOffset( short x, short y )
{
	m_X1	+= x;
	m_Y1	+= y;
	m_X2	+= x;
	m_Y2	+= y;
}

void CLRectangle::Inflate( short dx, short dy )
{
	m_X1	-= dx;
	m_Y1	-= dy;
	m_X2	+= dx;
	m_Y2	+= dy;
}
// -----------------------------------------------------------------------------
// CLRectangle [struct]
// =============================================================================

// =============================================================================
// CLPoint [struct]
// -----------------------------------------------------------------------------
CLPoint::CLPoint()
{
	m_X	=
	m_Y	= 0;
}

CLPoint::CLPoint( short x, short y )
{
	m_X	= x;
	m_Y	= y;
}

short CLPoint::GetX()
{
	return m_X;
}

void CLPoint::SetX( short value )
{
	m_X	= value;
}

short CLPoint::GetY()
{
	return m_Y;
}

void CLPoint::SetY( short value )
{
	m_Y	= value;
}

void CLPoint::MoveOffset( short x, short y )
{
	m_X	+= x;
	m_Y	+= y;
}

void CLPoint::Set( short x, short y )
{
	m_X	= x;
	m_Y	= y;
}
// -----------------------------------------------------------------------------
// CLPoint [struct]
// =============================================================================

// =============================================================================
// CLDrawer [class]
// -----------------------------------------------------------------------------
void CLDrawer::DrawXY( short x, short y,
		RGBColor backgroundColor, RGBColor foregroundColor )
{
	Draw( CLRectangle( x, y, x + GetWidth() - 1, y + GetHeight() - 1 ),
		backgroundColor, foregroundColor );
}
// -----------------------------------------------------------------------------
// CLDrawer [class]
// =============================================================================

// =============================================================================
// CLImage [class]
// -----------------------------------------------------------------------------
CLImage::CLImage( ImageType type,
	short width,
	short height,
	const unsigned char* data,
	const unsigned char* mask )
{
	m_Type		= type;
	m_Width		= width;
	m_Height	= height;
	m_Data		= data;
	m_Mask		= mask;
}

CLDrawer::DrawerType CLImage::GetDrawerType()
{
	return CLDrawer::DrawerType_Image;
}

CLImage::ImageType CLImage::GetType()
{
	return m_Type;
}

short CLImage::GetWidth()
{
	return m_Width;
}

short CLImage::GetHeight()
{
	return m_Height;
}

const unsigned char* CLImage::GetData()
{
	return m_Data;
}

const unsigned char* CLImage::GetMask()
{
	return m_Mask;
}
#include "CLLogo.h"

void CLImage::Draw( const CLRectangle& rectangle,
		RGBColor backgroundColor,
		RGBColor foregroundColor )
{
	// Draw Image
	switch (GetType())
	{
		case CLImage::ImageType_2Bit:
			if (backgroundColor == RGBColor_Empty)
				backgroundColor	= gLCD.getRGBBackColor();
			if (foregroundColor == RGBColor_Empty)
				foregroundColor	= gLCD.getRGBColor();

			gLCD.drawBitmapMono( rectangle.GetX1(), rectangle.GetY1(),
				GetWidth(), GetHeight(), GetData(),
				backgroundColor, foregroundColor );
			break;

		case CLImage::ImageType_16Bit_565:
			gLCD.drawBitmap( rectangle.GetX1(), rectangle.GetY1(),
				GetWidth(), GetHeight(),
				(unsigned short*) GetData(),
				GetMask(),
				backgroundColor );
			break;
	}
}
// -----------------------------------------------------------------------------
// CLImage [class]
// =============================================================================

// =============================================================================
// CLSymbol [class]
// -----------------------------------------------------------------------------
CLDrawer::DrawerType CLSymbol::GetDrawerType()
{
	return CLDrawer::DrawerType_Symbol;
}
// -----------------------------------------------------------------------------
// CLSymbol [class]
// =============================================================================

// =============================================================================
// CLGraphicStyle [struct]
// -----------------------------------------------------------------------------
CLGraphicStyle::CLGraphicStyle()
{
	this->Options			= CLGraphicStyleOptions_Default;
	this->BackgroundColor	= RGBColor_Black;
	this->ForegroundColor	= RGBColor_White;
	this->BorderWidth		= 0;
	this->BorderColor		= RGBColor_Empty;
}

CLGraphicStyle::CLGraphicStyle( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
	RGBColor maskBackgroundColor, RGBColor maskForegroundColor )
{
	Set( options, backgroundColor, foregroundColor );
	SetMask( maskBackgroundColor, maskForegroundColor );
}

CLGraphicStyle::CLGraphicStyle( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
	byte borderWidth, RGBColor borderColor,
	RGBColor maskBackgroundColor, RGBColor maskForegroundColor )
{
	Set( options, backgroundColor, foregroundColor, borderWidth, borderColor );
	SetMask( maskBackgroundColor, maskForegroundColor );
}

void CLGraphicStyle::Set( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor )
{
	this->Options			= options;
	this->BackgroundColor	= backgroundColor;
	this->ForegroundColor	= foregroundColor;
	this->BorderWidth		= 0;
	this->BorderColor		= RGBColor_Empty;
}

void CLGraphicStyle::Set( unsigned short options, RGBColor backgroundColor, RGBColor foregroundColor,
	byte borderWidth, RGBColor borderColor )
{
	this->Options			= options;
	this->BackgroundColor	= backgroundColor;
	this->ForegroundColor	= foregroundColor;
	this->BorderWidth		= borderWidth;
	this->BorderColor		= borderColor;
}

void CLGraphicStyle::SetMask( RGBColor maskBackgroundColor, RGBColor maskForegroundColor )
{
	this->MaskBackgroundColor	= maskBackgroundColor;
	this->MaskForegroundColor	= maskForegroundColor;
}

void CLGraphicStyle::Set( CLGraphicStyle& style )
{
	this->Options			= style.Options;
	this->BackgroundColor	= style.BackgroundColor;
	this->ForegroundColor	= style.ForegroundColor;
	this->BorderWidth		= style.BorderWidth;
	this->BorderColor		= style.BorderColor;
}
// -----------------------------------------------------------------------------
// CLGraphicStyle [struct]
// =============================================================================

// =============================================================================
// CLGraphics [class]
// -----------------------------------------------------------------------------

// --------------------------------------
// Draw Drawer
// --------------------------------------
void CLGraphics::Draw( const CLRectangle& rectangle, unsigned short options,
	CLDrawer* drawer,
	RGBColor drawerBackgroundColor, RGBColor drawerForegroundColor )
{
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();

	if (drawer == NULL)
	{
		gLCD.setRGBColor( gLCD.getRGBBackColor() );
		gLCD.fillRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );
	}
	else
	{
		short		drawerX, drawerY;

		// Calcola la y 
		switch (options & CLGraphicStyleOptions_VAlign_Mask)
		{
			case CLGraphicStyleOptions_VAlign_Middle:
				if (drawer->GetHeight() > rectangle.GetHeight())
					drawerY	= rectangle.GetY1();
				else
					drawerY	= rectangle.GetY1() + ((rectangle.GetHeight() - drawer->GetHeight()) >> 1);
				break;

			case CLGraphicStyleOptions_VAlign_Bottom:
				if (drawer->GetHeight() > rectangle.GetHeight())
					drawerY	= rectangle.GetY1();
				else
					drawerY	= rectangle.GetY2() - drawer->GetHeight() + 1;
				break;

			default:
				drawerY	= rectangle.GetY1();
				break;
		}

		// Calcola la x
		switch (options & CLGraphicStyleOptions_HAlign_Mask)
		{
			case CLGraphicStyleOptions_HAlign_Center:
				if (drawer->GetWidth() > rectangle.GetWidth())
					drawerX	= rectangle.GetX1();
				else
					drawerX	= rectangle.GetX1() + ((rectangle.GetWidth() - drawer->GetWidth()) >> 1);
				break;

			case CLGraphicStyleOptions_HAlign_Right:
				if (drawer->GetWidth() > rectangle.GetWidth())
					drawerX	= rectangle.GetX1();
				else
					drawerX	= rectangle.GetX2() - drawer->GetWidth() + 1;
				break;

			default:
				drawerX	= rectangle.GetX1();
				break;
		}

		// Fill Area
		gLCD.setRGBColor( gLCD.getRGBBackColor() );

		// Fill Upper Area
		if ((drawerY - rectangle.GetY1()) > 0)
			gLCD.fillRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), drawerY - 1 );

		// Fill Lower Area
		if (drawerY + drawer->GetHeight() - 1 < rectangle.GetY2())
			gLCD.fillRect( rectangle.GetX1(), drawerY + drawer->GetHeight(), rectangle.GetX2(), rectangle.GetY2() );

		// Fill Left Area
		if ((drawerX - rectangle.GetX1()) > 0)
			gLCD.fillRect( rectangle.GetX1(), drawerY, drawerX - 1, drawerY + drawer->GetHeight() - 1 );

		// Fill Right Area
		if (drawerX + drawer->GetWidth() - 1 < rectangle.GetX2())
			gLCD.fillRect( drawerX + drawer->GetWidth(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );

		drawer->DrawXY( drawerX, drawerY, drawerBackgroundColor, drawerForegroundColor );
	}

	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setRGBBackColor( saveBackgroundColor );
}

// --------------------------------------
// Draw Text
// --------------------------------------
void CLGraphics::_DrawTextLine( short x, short y, short width, unsigned short options,
	const char* text, short textLength )
{
	short		leftSpace;
	short		rightSpace;
	RGBColor	foregroundColor	= gLCD.getRGBColor();
	short		maxCharPerLine;
	short		marginLeft;
	short		marginRight;
	RGBColor	currentForegroundColor	= gLCD.getRGBColor();

	if (textLength == -1)
		textLength	= strlen( text );

	if (width == -1)
		width	= textLength * gLCD.getFontXSize();

	maxCharPerLine	= width / gLCD.getFontXSize();
	marginLeft		= (width - (maxCharPerLine * gLCD.getFontXSize())) >> 1;
	marginRight		= (width - (maxCharPerLine * gLCD.getFontXSize())) - marginLeft;

	if (textLength >= maxCharPerLine)
	{
		textLength	= maxCharPerLine;
		leftSpace	= marginLeft;
		rightSpace	= marginRight;
	}
	else
	{
		switch (options & CLGraphicStyleOptions_HAlign_Mask)
		{
			case CLGraphicStyleOptions_HAlign_Center:
				if (options & CLGraphicStyleOptions_TextAlignBy_Pixel)
				{
					leftSpace	= (width - (textLength * gLCD.getFontXSize())) >> 1;
					rightSpace	= width - (textLength * gLCD.getFontXSize()) - leftSpace;
				}
				else
				{
					leftSpace	= (maxCharPerLine - textLength) >> 1;
					rightSpace	= (maxCharPerLine - textLength) - leftSpace;
					leftSpace	= marginLeft + (leftSpace * gLCD.getFontXSize());
					rightSpace	= marginRight + (rightSpace * gLCD.getFontXSize());
				}
				break;

			case CLGraphicStyleOptions_HAlign_Right:
				if (options & CLGraphicStyleOptions_TextAlignBy_Pixel)
				{
					leftSpace	= width - (textLength * gLCD.getFontXSize());
					rightSpace	= 0;
				}
				else
				{
					leftSpace	= marginLeft + marginRight + ((maxCharPerLine - textLength) * gLCD.getFontXSize());
					rightSpace	= 0;
				}
				break;

			default:
				if (options & CLGraphicStyleOptions_TextAlignBy_Pixel)
				{
					leftSpace	= 0;
					rightSpace	= width - (textLength * gLCD.getFontXSize());
				}
				else
				{
					leftSpace	= 0;
					rightSpace	= marginLeft + marginRight + ((maxCharPerLine - textLength) * gLCD.getFontXSize());
				}
				break;
		}
	}

	gLCD.setRGBColor( gLCD.getRGBBackColor() );
	if (leftSpace)
		gLCD.fillRect( x, y, x + leftSpace, y + gLCD.getFontYSize() - 1 );
	if (rightSpace)
		gLCD.fillRect( x + (width - 1) - rightSpace, y, x + (width - 1), y + gLCD.getFontYSize() - 1 );

	gLCD.setRGBColor( currentForegroundColor );
	gLCD.printWidth( text, x + leftSpace, y, textLength );
}

void CLGraphics::_DrawText( const CLRectangle& rectangle, unsigned short options,
	const char* text )
{
	static byte	lineInfos[ 20 ];
	byte		lineCount;
	short		textY;
	RGBColor	currentForegroundColor	= gLCD.getRGBColor();
	CLRectangle	rectangle2	= rectangle;

	rectangle2.Truncate( 0, 0, gLCD.getMaxX(), gLCD.getMaxY() );

	lineCount	= 0;

	if (options & CLGraphicStyleOptions_Text_MultiLine)
	{
		byte	maxCharPerLine	= rectangle2.GetWidth() / gLCD.getFontXSize();
		byte	maxLineCount	= rectangle2.GetHeight() / gLCD.getFontYSize();
		char*	ptrText			= (char*) text;
		char*	ptrStartLine	= (char*) text;
		short	textLineLength;

		// Scansiona la stringa
		while (*ptrStartLine)
		{
			// Cerca la fine della linea (eol/null)
			textLineLength	= 0;

			while (true)
			{
				if (!*ptrText)
				{
					textLineLength	= ptrText - ptrStartLine;
					break;
				}
				else
				if ((*ptrText == '\r' && *(ptrText + 1) == '\n') ||
					(*ptrText == '\n' && *(ptrText + 1) == '\r'))
				{
					textLineLength	= ptrText - ptrStartLine;
					ptrText	+= 2;
					break;
				}
				else
				if (*ptrText == '\n' || *ptrText == '\r')
				{
					textLineLength	= ptrText - ptrStartLine;
					ptrText++;
					break;
				}
				else
					ptrText++;
			}

			// Break line
			int	remaingChar			= textLineLength;
			int	paragraphLineCount	= 0;
			while (remaingChar > 0)
			{
				int		renderWidth;
				char*	ptrEndLine;

				// Skip space dalla 2 linea
				while (paragraphLineCount && *ptrStartLine == ' ')
					ptrStartLine++, remaingChar--;

				if (remaingChar > maxCharPerLine)
				{
					renderWidth	= maxCharPerLine;

					// Cerca il punto della stringa da spezzare
					ptrEndLine	= ptrStartLine + renderWidth;
					while (ptrEndLine > ptrStartLine)
					{
						if (strchr( " +-/*;])}<>=", *ptrEndLine ))
							break;
						ptrEndLine--;
					}
					while (ptrEndLine > ptrStartLine)
					{
						if (!strchr( " +-/*;])}<>=", *ptrEndLine ))
							break;
						ptrEndLine--;
					}

					if (ptrEndLine != ptrStartLine)
						renderWidth	= (ptrEndLine) - ptrStartLine + 1;
				}
				else
					renderWidth	= remaingChar;

				lineInfos[ lineCount++ ]	= renderWidth << 1 | (paragraphLineCount == 0 ? 1 : 0);
				remaingChar					-= renderWidth;
				paragraphLineCount++;
				ptrStartLine				+= renderWidth;

				if (lineCount == 20 || lineCount == maxLineCount)
					break;
			}
			if (lineCount == 20 || lineCount == maxLineCount)
				break;

			ptrStartLine	= ptrText;
		}
	}
	else
		lineCount	= 1;

	// Calcola la y iniziale
	switch (options & CLGraphicStyleOptions_VAlign_Mask)
	{
		case CLGraphicStyleOptions_VAlign_Middle:
			textY	= rectangle2.GetY1() + ((rectangle2.GetHeight() - (lineCount * gLCD.getFontYSize())) >> 1);
			break;

		case CLGraphicStyleOptions_VAlign_Bottom:
			textY	= rectangle2.GetY1() + rectangle2.GetHeight() - (lineCount * gLCD.getFontYSize());
			break;

		default:
			textY	= rectangle2.GetY1();
			break;
	}

	if ((textY - 1 - rectangle2.GetY1()) > 0)
	{
		gLCD.setRGBColor( gLCD.getRGBBackColor() );
		gLCD.fillRect( rectangle2.GetX1(), rectangle2.GetY1(), rectangle2.GetX2(), textY - 1 );
		gLCD.setRGBColor( currentForegroundColor );
	}

	if (options & CLGraphicStyleOptions_Text_MultiLine)
	{
		char*	ptrStartLine	= (char*) text;

		for (int linesCounter = 0; linesCounter < lineCount; linesCounter++)
		{
			byte	lineWidth	= lineInfos[ linesCounter ] >> 1;

			// Skip space dalla 2 linea
			while (!(lineInfos[ linesCounter ] & 0x01) && *ptrStartLine == ' ')
				ptrStartLine++;

			// Render Line
			_DrawTextLine( rectangle2.GetX1(), textY, rectangle2.GetWidth(),
				options,
				ptrStartLine, lineWidth );
		
			// Prepare Next line
			ptrStartLine	+= lineWidth;
			textY			+= gLCD.getFontYSize();

			if ((*ptrStartLine == '\r' && *(ptrStartLine + 1) == '\n') ||
				(*ptrStartLine == '\n' && *(ptrStartLine + 1) == '\r'))
			{
				ptrStartLine	+= 2;
			}
			else
			if (*ptrStartLine == '\n' || *ptrStartLine == '\r')
			{
				ptrStartLine++;
			}
		}
	}
	else
	{
		// Render Line
		_DrawTextLine( rectangle2.GetX1(), textY, rectangle2.GetWidth(),
			options,
			text );
		textY	+= gLCD.getFontYSize();
	}

	if (textY <= rectangle2.GetY2())
	{
		gLCD.setRGBColor( gLCD.getRGBBackColor() );
		gLCD.fillRect( rectangle2.GetX1(), textY, rectangle2.GetX2(), rectangle2.GetY2() );
		gLCD.setRGBColor( currentForegroundColor );
	}
}

void CLGraphics::DrawText( short x, short y, unsigned short options,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();
	
	_SetFont( options );

	_DrawTextLine( x, y, -1, options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );

	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawText( short x, short y, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );
	_SetFont( options );

	_DrawTextLine( x, y, -1, options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawText( short x, short y, unsigned short options,
	const char* text, short charCount )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	_SetFont( options );

	_DrawTextLine( x, y, charCount * gLCD.getFontXSize(), options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawText( short x, short y, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	const char* text, short charCount )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	_SetFont( options );

	_DrawTextLine( x, y, charCount * gLCD.getFontXSize(), options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawText( const CLRectangle& rectangle, unsigned short options,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	_SetFont( options );

	_DrawText( rectangle, options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawText( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	_SetFont( options );

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	_DrawText( rectangle, options,
		text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

// --------------------------------------
// DrawBox
// --------------------------------------
void CLGraphics::DrawBox( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor,
	byte borderWidth, RGBColor borderColor )
{
	RGBColor	saveColor	= gLCD.getRGBColor();

	// Draw Background
	gLCD.setRGBColor( backgroundColor );
	if (options & CLGraphicStyleOptions_BorderRound_Yes)
		gLCD.fillRoundRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );
	else
		gLCD.fillRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );

	// Draw Border
	if (borderWidth)
	{
		DrawBorder( rectangle, options,
			borderWidth, borderColor );
	}

	gLCD.setRGBColor( saveColor );
}

void CLGraphics::DrawBox( const CLRectangle& rectangle, unsigned short options,
		RGBColor backgroundColor )
{
	DrawBox( rectangle, options,
		backgroundColor,
		0, RGBColor_Empty );
}

void CLGraphics::DrawBox( const CLRectangle& rectangle,
	CLGraphicStyle& style )
{
	DrawBox( rectangle, style.Options,
		style.BackgroundColor,
		style.BorderWidth, style.BorderColor );
}

// --------------------------------------
// DrawBox WithText
// --------------------------------------
void CLGraphics::_SetFont( unsigned short options )
{
	switch (options & CLGraphicStyleOptions_Font_Mask)
	{
		case CLGraphicStyleOptions_Font_Small:
			gLCD.setFont( &CLSmallFont, CLKTS::GetCodePage() );
			break;
		
		case CLGraphicStyleOptions_Font_Big:
			gLCD.setFont( &CLBigFont, CLKTS::GetCodePage() );
			break;
	}
}

void CLGraphics::DrawBoxWithText( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	byte borderWidth, RGBColor borderColor,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();
	CLRectangle	rectangle2			= rectangle;

	_SetFont( options );

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	if (borderWidth)
		rectangle2.Inflate( -borderWidth, -borderWidth );

	_DrawText( rectangle2, options,
			text );

	// Draw Border
	if (borderWidth)
	{
		rectangle2.Inflate( borderWidth, borderWidth );

		DrawBorder( rectangle2, options,
			borderWidth, borderColor );
	}

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawBoxWithText( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();

	_SetFont( options );

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	_DrawText( rectangle, options,
			text );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

void CLGraphics::DrawBoxWithText( const CLRectangle& rectangle,
	CLGraphicStyle& style,
	const char* text )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	Font*		saveFont			= gLCD.getFont();
	CLRectangle	rectangle2			= rectangle;

	_SetFont( style.Options );

	gLCD.setRGBBackColor( style.BackgroundColor );
	gLCD.setRGBColor( style.ForegroundColor );

	if (style.BorderWidth)
		rectangle2.Inflate( -style.BorderWidth, -style.BorderWidth );

	_DrawText( rectangle2, style.Options,
			text );

	// Draw Border
	if (style.BorderWidth)
	{
		rectangle2.Inflate( style.BorderWidth, style.BorderWidth );

		DrawBorder( rectangle2, style.Options,
			style.BorderWidth, style.BorderColor );
	}

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
	gLCD.setFont( saveFont, CLKTS::GetCodePage() );
}

// --------------------------------------
// DrawBox With Drawer
// --------------------------------------
void CLGraphics::DrawBoxWithDrawer( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	byte borderWidth, RGBColor borderColor,
	CLDrawer* drawer,
	RGBColor drawerBackgroundColor, RGBColor drawerForegroundColor )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	CLRectangle	rectangle2			= rectangle;

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	if (borderWidth)
		rectangle2.Inflate( -borderWidth, -borderWidth );

	Draw( rectangle2, options,
			drawer, drawerBackgroundColor, drawerForegroundColor );

	// Draw Border
	if (borderWidth)
	{
		rectangle2.Inflate( borderWidth, borderWidth );

		DrawBorder( rectangle2, options,
			borderWidth, borderColor );
	}

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
}

void CLGraphics::DrawBoxWithDrawer( const CLRectangle& rectangle, unsigned short options,
	RGBColor backgroundColor, RGBColor foregroundColor,
	CLDrawer* drawer,
	RGBColor drawerBackgroundColor, RGBColor drawerForegroundColor )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();

	gLCD.setRGBBackColor( backgroundColor );
	gLCD.setRGBColor( foregroundColor );

	Draw( rectangle, options,
			drawer, drawerBackgroundColor, drawerForegroundColor );

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
}

void CLGraphics::DrawBoxWithDrawer( const CLRectangle& rectangle,
	CLGraphicStyle& style,
	CLDrawer* drawer )
{
	RGBColor	saveBackgroundColor	= gLCD.getRGBBackColor();
	RGBColor	saveForegroundColor	= gLCD.getRGBColor();
	CLRectangle	rectangle2			= rectangle;

	gLCD.setRGBBackColor( style.BackgroundColor );
	gLCD.setRGBColor( style.ForegroundColor );

	if (style.BorderWidth)
		rectangle2.Inflate( -style.BorderWidth, -style.BorderWidth );

	Draw( rectangle2, style.Options,
			drawer, style.MaskBackgroundColor, style.MaskForegroundColor );

	// Draw Border
	if (style.BorderWidth)
	{
		rectangle2.Inflate( style.BorderWidth, style.BorderWidth );

		DrawBorder( rectangle2, style.Options,
			style.BorderWidth, style.BorderColor );
	}

	gLCD.setRGBBackColor( saveBackgroundColor );
	gLCD.setRGBColor( saveForegroundColor );
}

// --------------------------------------
// Draw ProgressBar
// --------------------------------------
void CLGraphics::_DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
	RGBColor backgroundColor, RGBColor barFalseColor, RGBColor* barTrueColors,
	float minValue, float maxValue, float* values, byte valueCount,
	byte barSize, byte barSpaceSize,
	short* outPositions )
{
	enum CLState
	{
		CLState_DrawBar,
		CLState_DrawSpace,
		CLState_DrawFill
	};

	if (barFalseColor == RGBColor_Empty)
		barFalseColor	= backgroundColor;

	short		progressBarSize			= (options & CLDrawBarOptions_Direction_Vertical ? rectangle.GetHeight() : rectangle.GetWidth());
	short		barCount;
	short		completedBarsCounter	= 0;
	CLState		state;
	float		currentValue;
	float		deltaValue;
	float		barHeightMax			= (options & CLDrawBarOptions_Direction_Vertical ? rectangle.GetWidth() : rectangle.GetHeight());
	float		barHeight				= (options & CLDrawBarOptions_StartWith_Max ? barHeightMax : 0);
	float		barHeightDelta			= (options & CLDrawBarOptions_StartWith_Max ? -1 : 1) * (barHeightMax / progressBarSize);
	RGBColor	saveColor				= gLCD.getRGBColor();
	short		relativeBarsCounter		= 0;
	short		currentDataIndex		= -1;

#ifdef _CLIKTS
	Climalombarda::KTS::CLIKTS::BeginUpdate();
#endif
	if (barSize < 1)
		barSize	= 1;

	// Calcolo dei parametri per la progressBar Progressive
	barHeightMax			= (options & CLDrawBarOptions_Direction_Vertical ? rectangle.GetWidth() : rectangle.GetHeight());
	barHeight				= 0;
	barHeightDelta			= barHeightMax / progressBarSize;

	barCount		= (progressBarSize - barSpaceSize) / (barSize + barSpaceSize);
	state			= CLState_DrawBar;
	currentValue	= minValue;
	deltaValue		= (maxValue - minValue) / progressBarSize;

	if (options & CLDrawBarOptions_Direction_Vertical)
	{
		int	y;
		int	dy;

		if (options & CLDrawBarOptions_StartWith_Max)
		{
			y	= rectangle.GetY2();
			dy	= -1;
		}
		else
		{
			y	= rectangle.GetY1();
			dy	= 1;
		}

		for (int barsCounter = 0; barsCounter < progressBarSize; barsCounter++, currentValue += deltaValue, y += dy, barHeight += barHeightDelta)
		{
			bool	inValue;

			currentValue	= constrain( currentValue, minValue, maxValue );
			barHeight		= constrain( barHeight, 0, barHeightMax );

			if (options & CLDrawBarOptions_Data_Range)
			{
				_DrawProgressBar_CheckDataRange( minValue, maxValue,
					values, valueCount,
					currentValue,
					currentDataIndex );
			}
			else
			{
				_DrawProgressBar_CheckDataValue( minValue, maxValue,
					values, valueCount,
					currentValue, currentDataIndex );
			}
			
			inValue	= (currentDataIndex >= 0);

			switch (state)
			{
				case CLState_DrawBar:
					if (options & CLDrawBarOptions_BarShape_Progressive)
					{
						if (options & CLDrawBarOptions_Flip_Yes)
						{
							gLCD.setRGBColor( backgroundColor );
							gLCD.drawLine( rectangle.GetX1() + barHeight + 1, y, rectangle.GetX2(), y );
							gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
							gLCD.drawLine( rectangle.GetX1(), y, rectangle.GetX1() + barHeight, y );
						}
						else
						{
							gLCD.setRGBColor( backgroundColor );
							gLCD.drawLine( rectangle.GetX1(), y, rectangle.GetX2() - (barHeight + 1), y );
							gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
							gLCD.drawLine( rectangle.GetX2() - barHeight, y, rectangle.GetX2(), y );
						}
					}
					else
					{
						gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
						gLCD.drawLine( rectangle.GetX1(), y, rectangle.GetX2(), y );
					}

					if (++relativeBarsCounter == barSize)
					{
						relativeBarsCounter	= 0;
						if (barSpaceSize)
							state	= CLState_DrawSpace;

						if (++completedBarsCounter == barCount)
							state	= CLState_DrawFill;
					}
					continue;

				case CLState_DrawSpace:
					gLCD.setRGBColor( backgroundColor );
					gLCD.drawLine( rectangle.GetX1(), y, rectangle.GetX2(), y );

					if (++relativeBarsCounter == barSpaceSize)
					{
						relativeBarsCounter	= 0;
						state				= CLState_DrawBar;
					}
					continue;

				case CLState_DrawFill:
					gLCD.setRGBColor( backgroundColor );
					if (options & CLDrawBarOptions_StartWith_Max)
						gLCD.fillRect( rectangle.GetX1(), rectangle.GetY1(), rectangle.GetX2(), y );
					else
						gLCD.fillRect( rectangle.GetX1(), y, rectangle.GetX2(), rectangle.GetY2() );

					barsCounter	= progressBarSize;
					continue;
			}
		}
	}
	else
	{
		int	x;
		int	dx;

		if (options & CLDrawBarOptions_StartWith_Max)
		{
			x	= rectangle.GetX2();
			dx	= -1;
		}
		else
		{
			x	= rectangle.GetX1();
			dx	= 1;
		}

		for (int barsCounter = 0; barsCounter < progressBarSize; barsCounter++, currentValue += deltaValue, x += dx, barHeight += barHeightDelta)
		{
			bool	inValue;

			if (currentValue > maxValue)
				currentValue	= maxValue;
			if (barHeight > barHeightMax)
				currentValue	= barHeightMax;

			if (options & CLDrawBarOptions_Data_Range)
			{
				_DrawProgressBar_CheckDataRange( minValue, maxValue,
					values, valueCount,
					currentValue,
					currentDataIndex );
			}
			else
			{
				_DrawProgressBar_CheckDataValue( minValue, maxValue,
					values, valueCount,
					currentValue, currentDataIndex );
			}
			
			inValue	= (currentDataIndex >= 0);

			switch (state)
			{
				case CLState_DrawBar:
					if (options & CLDrawBarOptions_BarShape_Progressive)
					{
						if (options & CLDrawBarOptions_Flip_Yes)
						{
							gLCD.setRGBColor( backgroundColor );
							gLCD.drawLine( x, rectangle.GetY1() + barHeight + 1, x, rectangle.GetY2() );
							gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
							gLCD.drawLine( x, rectangle.GetY1(), x, rectangle.GetY1() + barHeight );
						}
						else
						{
							gLCD.setRGBColor( backgroundColor );
							gLCD.drawLine( x, rectangle.GetY1(), x, rectangle.GetY2() - (barHeight + 1) );
							gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
							gLCD.drawLine( x, rectangle.GetY2() - barHeight, x, rectangle.GetY2() );
						}
					}
					else
					{
						gLCD.setRGBColor( inValue ? barTrueColors[ currentDataIndex ] : barFalseColor );
						gLCD.drawLine( x, rectangle.GetY1(), x, rectangle.GetY2() );
					}

					if (++relativeBarsCounter == barSize)
					{
						relativeBarsCounter	= 0;
						if (barSpaceSize)
							state	= CLState_DrawSpace;

						if (++completedBarsCounter == barCount)
							state	= CLState_DrawFill;
					}
					continue;

				case CLState_DrawSpace:
					gLCD.setRGBColor( backgroundColor );
					gLCD.drawLine( x, rectangle.GetY1(), x, rectangle.GetY2() );

					if (++relativeBarsCounter == barSpaceSize)
					{
						relativeBarsCounter	= 0;
						state				= CLState_DrawBar;
					}
					continue;

				case CLState_DrawFill:
					gLCD.setRGBColor( backgroundColor );
					if (options & CLDrawBarOptions_StartWith_Max)
						gLCD.fillRect( rectangle.GetX1(), rectangle.GetY1(), x, rectangle.GetY2() );
					else
						gLCD.fillRect( x, rectangle.GetY1(), rectangle.GetX2(), rectangle.GetY2() );

					barsCounter	= progressBarSize;
					continue;
			}
		}
	}

	if (outPositions != NULL)
	{
		for (int valuesCounter = 0; valuesCounter < valueCount; valuesCounter++)
		{
			if (values[ valuesCounter ] < minValue || values[ valuesCounter ] > maxValue)
				outPositions[ valuesCounter ]	= -1;
			else
				outPositions[ valuesCounter ]	= (int) (((values[ valuesCounter ] - minValue) / (maxValue - minValue)) * (float) progressBarSize);
		}
	}
#ifdef _CLIKTS
	Climalombarda::KTS::CLIKTS::EndUpdate();
#endif
}

void CLGraphics::_DrawProgressBar_CheckDataValue( float min, float max,
	float* values, byte valueCount,
	float currentValue,
	short& currentDataIndex )
{
	if (valueCount == 0 || currentDataIndex == -2)
	{
		currentDataIndex	= -2;
		return;
	}

	if (currentDataIndex == -1)
		currentDataIndex	= 0;

	while (true)
	{
		if (currentValue > values[ currentDataIndex ])
		{
			currentDataIndex++;
			if (currentDataIndex == valueCount)
			{
				currentDataIndex	= -2;
				return;
			}
		}
		else
			break;
	}
}

void CLGraphics::_DrawProgressBar_CheckDataRange( float min, float max,
	float* values, byte valueCount,
	float currentValue,
	short& currentDataIndex )
{
	if (valueCount < 1 || currentDataIndex == -2)
	{
		currentDataIndex	= -2;
		return;
	}

	if (currentValue < values[ 0 ])
	{
		currentDataIndex	= -1;
		return;
	}

	if (currentValue > values[ 1 ])
	{
		currentDataIndex	= -2;
		return;
	}

	currentDataIndex	= 0;
}

void CLGraphics::DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
	RGBColor backgroundColor, RGBColor barFalseColor, RGBColor barTrueColor,
	float min, float max, float value,
	byte barSize, byte barSpaceSize,
	short* outPosition )
{
	_DrawProgressBar( rectangle, options, 
		backgroundColor, barFalseColor, &barTrueColor,
		min, max, &value, 1,
		barSize, barSpaceSize,
		outPosition );
}

void CLGraphics::DrawProgressBar( const CLRectangle& rectangle, unsigned short options, 
	RGBColor backgroundColor, RGBColor barFalseColor, RGBColor* barTrueColors,
	float min, float max, float* values, byte valueCount,
	byte barSize, byte barSpaceSize,
	short* outPositions )
{
	_DrawProgressBar( rectangle, options, 
		backgroundColor, barFalseColor, barTrueColors,
		min, max, values, valueCount,
		barSize, barSpaceSize,
		outPositions );
}

void CLGraphics::DrawProgressBarRange( const CLRectangle& rectangle, unsigned short options, 
	RGBColor backgroundColor, RGBColor barFalseColor, RGBColor barTrueColor, 
	float min, float max, float rangeValue0, float rangeValue1,
	byte barSize, byte barSpaceSize,
	short* outPositions )
{
	RGBColor	barTrueColors[ 2 ];
	float		values[ 2 ];

	barTrueColors[ 0 ]	= barTrueColor;
	barTrueColors[ 1 ]	= barTrueColor;
	values[ 0 ]			= rangeValue0;
	values[ 1 ]			= rangeValue1;

	_DrawProgressBar( rectangle, options | CLDrawBarOptions_Data_Range, 
		backgroundColor, barFalseColor, barTrueColors,
		min, max, values, 2,
		barSize, barSpaceSize,
		outPositions );
}

// --------------------------------------
// Other
// --------------------------------------
void CLGraphics::DrawBorder( const CLRectangle& rectangle, short options,
	byte borderWidth, RGBColor borderColor )
{
	short	borderX1	= rectangle.GetX1(),
			borderY1	= rectangle.GetY1(),
			borderX2	= rectangle.GetX2(),
			borderY2	= rectangle.GetY2();

	gLCD.setRGBColor( borderColor );
	for (int bordersCounter = 0; bordersCounter < borderWidth; bordersCounter++)
	{
		if (options & CLGraphicStyleOptions_BorderRound_Yes && bordersCounter == 0)
			gLCD.drawRoundRect( borderX1, borderY1, borderX2, borderY2 );
		else
			gLCD.drawRect( borderX1, borderY1, borderX2, borderY2 );

		borderX1++;
		borderY1++;
		borderX2--;
		borderY2--;
	}
}

void CLGraphics::DrawLine( short x1, short y1, short x2, short y2,
	RGBColor color )
{
	RGBColor	saveColor	= gLCD.getRGBColor();
	gLCD.setRGBColor( color );
	gLCD.drawLine( x1, y1, x2, y2 );
	gLCD.setRGBColor( saveColor );
}

RGBColor CLGraphics::AdjustBrightness( RGBColor color, short level )
{
	short		value;
	RGBColor	newColor;

	// B
	value		= (color & 0x000000FF) + level;
	newColor	= constrain( value, 0 , 255 );
	
	// G
	value		= ((color >> 8) & 0x000000FF) + level;
	newColor	= newColor | (constrain( value, 0 , 255 ) << 8);

	// R
	value		= ((color >> 16) & 0x000000FF) + level;
	newColor	= newColor | (constrain( value, 0 , 255 ) << 16);

	return newColor;
}
// -----------------------------------------------------------------------------
// CLGraphics [class]
// =============================================================================

