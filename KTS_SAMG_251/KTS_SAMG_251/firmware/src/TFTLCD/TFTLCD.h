/*
 *****************************************************************************
 ********************* ATTENTION *********************************************
 ****************** FILE MODIFIED ********************************************
 ******************** WITH  BILLY  INIT **************************************
 *****************************************************************************
 *****************************************************************************
 
  
  TFTLCD.h - chipKit library support for 16bit (W)QVGA LCD Boards
  Copyright (C)2010-2011 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the Arduino demo-code provided
  by ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  This library was originally made especially for the 3.2" TFT LCD Screen Module: 
  ITDB02-3.2 by ITead studio, but has later been expanded to support multiple
  modules. This library has been designed to use 16bit mode, so it will not 
  work with 8bit modules.

  Supported controllers:
		-	HX8347-A
		-	ILI9325D
		-	ILI9327
		-	SSD1289

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef TFTLCD_h
#define TFTLCD_h

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "definitions.h"

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT   0
#define LANDSCAPE  1

#define ASPECT_4x3	0	// Legacy
#define ASPECT_16x9	1	// Legacy

typedef unsigned long RGBColor;

#define RGBColor_Make( r, g, b ) (RGBColor) ((RGBColor) r << 16) | ((RGBColor) g << 8) | ((RGBColor) b)
#define Color565_Make( rgbColor ) (unsigned int) ((rgbColor & 0x00F80000) >> 8) | ((rgbColor & 0x0000FC00) >> 5) | ((rgbColor & 0x000000F8) >> 3)

const RGBColor RGBColor_Empty	= 0xFF000000;
const RGBColor RGBColor_Black	= 0x000000;
const RGBColor RGBColor_White	= 0xFFFFFF;
const RGBColor RGBColor_Red		= 0xFF0000;
const RGBColor RGBColor_Green	= 0x00FF00;
const RGBColor RGBColor_Blue	= 0x0000FF;

struct FontCodePage
{
	public: unsigned short Code;
	public: const unsigned short* CharMaps;
};

struct Font
{
	public: unsigned char Height;
	public: unsigned char Width;
	public: byte BytePerChar;
	public: short CharCount;
	public: const unsigned char* Chars;
	public: unsigned char CodePageCount;
	public: FontCodePage* CodePages;
};

class TFTLCD
{
	public:
		TFTLCD();
		TFTLCD(int RS, int WR,int CS, int RST);
		//void InitLCD(byte orientation=PORTRAIT, char *sDriverIC);
        void InitLCD(byte set_orientation, char* sDriverIC);
		void clrScr();
		void drawPixel(int x, int y);
		void drawLine(int x1, int y1, int x2, int y2);
		void fillScr(byte r, byte g, byte b);
		void drawRect(int x1, int y1, int x2, int y2);
		void drawRoundRect(int x1, int y1, int x2, int y2);
		void fillRect(int x1, int y1, int x2, int y2);
		void fillRoundRect(int x1, int y1, int x2, int y2);
		void drawCircle(int x, int y, int radius);
		void fillCircle(int x, int y, int radius);
		void setColor(byte r, byte g, byte b);
		void setRGBColor( RGBColor rgbColor );
		RGBColor getRGBColor();
		void setBackColor(byte r, byte g, byte b);
		void setRGBBackColor( RGBColor rgbColor );
		RGBColor getRGBBackColor();
		void print(const char *st, int x, int y, int deg=0);
		void printWidth( const char *st, int x, int y, int numChar, int deg = 0 );
		void printNumI(long num, int x, int y);
		void printNumF(double num, byte dec, int x, int y);

		void setFont( Font* font, int codePage );
		Font* getFont();
		int getFontCodePage();
		uint8_t getFontXSize();
		uint8_t getFontYSize();
		bool hasChar( char character );

		void drawBitmap( int x, int y, int sx, int sy, 
			const unsigned short* data,
			const unsigned char* mask = NULL, RGBColor maskBackgroundColor = RGBColor_Empty,
			RGBColor maskForegroundColor = RGBColor_Empty,
			int scale = 1 );
		void drawBitmap(int x, int y, int sx, int sy, const unsigned short* data, int deg, int rox, int roy);
		void drawBitmapMono( int x, int y, int sx, int sy, const unsigned char* data,
			RGBColor backgroundColor, RGBColor foregroundColor );

		int getWidth();
		int getHeight();
		int getMaxX();
		int getMaxY();
		int getMinX();
		int getMinY();

	protected:
		byte fcolorr,fcolorg,fcolorb;
		byte bcolorr,bcolorg,bcolorb;
		byte orient;
		long disp_y_size;
		uint16_t B_RS, B_WR, B_CS, B_RST;
		//_current_font	cfont;

		Font* m_CurrentFont;
		FontCodePage* m_CurrentFontCodePage;
 
		//byte m_Mirror;
		short m_SetX1;
		short m_SetY1;
		short m_SetX2;
		short m_SetY2;
		short m_SetCurrentX;
		short m_SetCurrentY;

		const byte* GetFontChar( byte character, bool returnNullIfNotExist = false );

		void LCD_Writ_Bus(char VH,char VL);
		void LCD_Write_COM(char VL);
		void LCD_Write_DATA(char VH,char VL);
		void main_W_com_data(char com1,int dat1);
		void setPixel(byte r,byte g,byte b);
		void drawHLine(int x, int y, int l);
		void drawVLine(int x, int y, int l);
		void printChar(byte c, int x, int y);
		void setXY(word x1, word y1, word x2, word y2);
		void rotateChar(byte c, int x, int y, int pos, int deg);
};

#endif



