#ifndef _CLIKTS
/*
  
 *****************************************************************************
 ********************* ATTENTION *********************************************
 ****************** FILE MODIFIED ********************************************
 ******************** WITH  BILLY  INIT **************************************
 *****************************************************************************
 *****************************************************************************
 
  
  TFTLCD.cpp - chipKit library support for 16bit (W)QVGA LCD Boards
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
                -       ILI9341  new (marzo 2015)

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

#include "TFTLCD.h"

#define RGBColor_MAKEColorHigh( rgbColor ) ((unsigned char) ((rgbColor & 0x00F80000) >> 16) | ((rgbColor & 0x0000FC00) >> 13))
#define RGBColor_MAKEColorLow( rgbColor ) ((unsigned char) ((rgbColor & 0x0000FC00) >> 5)  | ((rgbColor & 0x000000F8) >> 3))

//-------------------------------------------------
#define  HX8347     0x00
#define  ILI9341    0x01

static char DriverLCD = HX8347;

byte orient = LANDSCAPE;

//================================================
TFTLCD::TFTLCD()
{
}

//================================================
TFTLCD::TFTLCD(int RS, int WR,int CS, int RST )
{
    disp_y_size=319;
}

//================================================
void TFTLCD::LCD_Writ_Bus(char VH,char VL)
{   
    
    PIOA_REGS->PIO_CODR = 0xFE007882;
    PIOA_REGS->PIO_SODR = ((VL&0x1)<<1) | (((VL&0x2)>> 1)<<7) | (((VL&0x10)>>4)<<31) | (((VL&0x20)>>5)<<30) | (((VL&0x40)>>6)<<29) | (((VL&0x80)>>7)<<28) | (((VH&0x2)>>1)<<14) | (((VH&0x4)>>2)<<13) | (((VH&0x8)>>3)<<12) | (((VH&0x10)>>4)<<11) | (((VH&0x20)>>5)<<27) | (((VH&0x40)>>6)<<26) | (((VH&0x80)>>7)<<25);
    
    PIOB_REGS->PIO_CODR = 0x0000C008;
    PIOB_REGS->PIO_SODR = (((VL&0x4)>> 2)<<15) | (((VL&0x8)>> 3)<<14) | ((VH&0x1)<<3);
            
    WR_Clear();
    WR_Set();
}

//================================================
void TFTLCD::LCD_Write_COM(char VL)  
{   
    RS_Clear();
    LCD_Writ_Bus(0x00,VL);
}

//================================================
void TFTLCD::LCD_Write_DATA(char VH,char VL)
{
    RS_Set();
    LCD_Writ_Bus(VH,VL);
}

//================================================
void TFTLCD::main_W_com_data(char com1,int dat1)
{
    LCD_Write_COM(com1);
    LCD_Write_DATA(dat1>>8,dat1);
}


//================================================
// Dobbiamo leggere l'eeprom, in base al tipo di 
// dato letto carico il suo driver.
//================================================
void TFTLCD::InitLCD(byte set_orientation, char *sDriverIC)
{
    
    orient = set_orientation;

    // al momento abbiamo 2 tipi di driver IC:
    //
    //   driver LCD :      code eeprom   
    // -------------:-------------------------
    //     HX8347   : 0xFF, 0xFF, 0xFF, 0xFF (gestito fino a marzo 2015)
    //    ILI9341   : ' 9',  '3',  '4',  '1' (nuovo driver da marzo 2015)
    DriverLCD = HX8347;
        
    if((sDriverIC[0] == '9') && 
       (sDriverIC[1] == '3') && 
       (sDriverIC[2] == '4') &&
       (sDriverIC[3] == '1')) 
       DriverLCD = ILI9341;

    if(DriverLCD == ILI9341) {
        //-------- Reset LCD DRIVER -------- 
        RESET_Set(); // RESET chip LCD
        SYSTICK_DelayMs ( 50 ); 
       
        RESET_Clear();
        SYSTICK_DelayMs ( 120 );
    
        RESET_Set();
        SYSTICK_DelayMs ( 120);

        CS_Clear();

        //----------------Start Initial Sequence-------------
        LCD_Write_COM(0xCB); 
        LCD_Write_DATA(0x00, 0x39);
        LCD_Write_DATA(0x00, 0x2C);
        LCD_Write_DATA(0x00, 0x00);
        LCD_Write_DATA(0x00, 0x34);
        LCD_Write_DATA(0x00, 0x02);
	
        LCD_Write_COM(0xCF); 
        LCD_Write_DATA(0x00, 0x00);
        LCD_Write_DATA(0x00, 0x81);
        LCD_Write_DATA(0x00, 0x30);
	
        LCD_Write_COM(0xE8); 
        LCD_Write_DATA(0x00, 0x85);
        LCD_Write_DATA(0x00, 0x10);
        LCD_Write_DATA(0x00, 0x7A);
	
        LCD_Write_COM(0xEA); 
        LCD_Write_DATA(0x00, 0x00);
        LCD_Write_DATA(0x00, 0x00);
	
        LCD_Write_COM(0xED); 
        LCD_Write_DATA(0x00, 0x64);
        LCD_Write_DATA(0x00, 0x03);  
        LCD_Write_DATA(0x00, 0x12);
        LCD_Write_DATA(0x00, 0x81);
	
        LCD_Write_COM(0xF7); 
        LCD_Write_DATA(0x00, 0x20);

        LCD_Write_COM(0xC0); 	      //Power control 
        LCD_Write_DATA(0x00, 0x21);       //VRH[5:0] 

        LCD_Write_COM(0xC1);              //Power control 
        LCD_Write_DATA(0x00, 0x11);       //SAP[2:0];BT[3:0]

        LCD_Write_COM(0xC5);              //VCM control 
        LCD_Write_DATA(0x00, 0x3F); 
        LCD_Write_DATA(0x00, 0x3C); 

        LCD_Write_COM(0xC7);              //VCM control2 
        LCD_Write_DATA(0x00, 0Xa7); 

        LCD_Write_COM(0x36);  
        if(orient == LANDSCAPE)	// horizontal										
          LCD_Write_DATA(0x00, 0x49);	// memory access control MY=1, MX=1, MV=0, BGR=1 X68 define se tela vai ficar deitada ou em pÃ©
        else                   	// vertical
          LCD_Write_DATA(0x00, 0x48);	// memory access control MY=0, MX=0, MV=1, BGR=1 X68 define se tela vai ficar deitada ou em pÃ©
                                // Flip Imagem display altere B5 | B6 | B7 do registrador 36H encontrado na pagina 78/79 do datasheet


        LCD_Write_COM(0x3a);             // Memory Access Control 
        LCD_Write_DATA(0x00, 0x05); 

        LCD_Write_COM(0xB1);             // frame control
        LCD_Write_DATA(0x00, 0x00); 
        LCD_Write_DATA(0x00, 0x1B); 

        LCD_Write_COM(0xF2);            // 3Gamma Function Disable 
        LCD_Write_DATA(0x00, 0x00);
 
        LCD_Write_COM(0x26);            //Gamma curve selected 
        LCD_Write_DATA(0x00, 0x01); 

        LCD_Write_COM(0xE0); //Set Gamma 
        LCD_Write_DATA(0x00, 0x0F); 
        LCD_Write_DATA(0x00, 0x23); 
        LCD_Write_DATA(0x00, 0x1F); 
        LCD_Write_DATA(0x00, 0x0B); 
        LCD_Write_DATA(0x00, 0x0E); 
        LCD_Write_DATA(0x00, 0x08); 
        LCD_Write_DATA(0x00, 0x4B); 
        LCD_Write_DATA(0x00, 0XA8); 
        LCD_Write_DATA(0x00, 0x3B); 
        LCD_Write_DATA(0x00, 0x0A); 
        LCD_Write_DATA(0x00, 0x14); 
        LCD_Write_DATA(0x00, 0x06); 
        LCD_Write_DATA(0x00, 0x10); 
        LCD_Write_DATA(0x00, 0x09); 
        LCD_Write_DATA(0x00, 0x00); 

        LCD_Write_COM(0xE1); //Set Gamma 
        LCD_Write_DATA(0x00, 0x00); 
        LCD_Write_DATA(0x00, 0x1C); 
        LCD_Write_DATA(0x00, 0x20); 
        LCD_Write_DATA(0x00, 0x04); 
        LCD_Write_DATA(0x00, 0x10); 
        LCD_Write_DATA(0x00, 0x08); 
        LCD_Write_DATA(0x00, 0x34); 
        LCD_Write_DATA(0x00, 0x47); 
        LCD_Write_DATA(0x00, 0x44);   
        LCD_Write_DATA(0x00, 0x05); 
        LCD_Write_DATA(0x00, 0x0B); 
        LCD_Write_DATA(0x00, 0x09); 
        LCD_Write_DATA(0x00, 0x2F); 
        LCD_Write_DATA(0x00, 0x36); 
        LCD_Write_DATA(0x00, 0x0F); 

        LCD_Write_COM(0x11); //Exit Sleep
        SYSTICK_DelayMs ( 120 );
        LCD_Write_COM(0x29); //Display on       
      
    }else { 
      
      /********************
       *     HX8347
       ********************/
        
      RESET_Set(); // RESET chip LCD
      SYSTICK_DelayMs ( 5 ); 
       
      RESET_Clear();
      SYSTICK_DelayMs ( 15 );
    
      RESET_Set();
      SYSTICK_DelayMs ( 15);

      CS_Clear();
	
      //-------------------------------------------------------------------------
      //---------------- BILLY INITIALIZE CODE ----------------------------------
      //-------------------------------------------------------------------------
	
      //Driving ability Setting 
      main_W_com_data(0xEA,0x0000); //PTBA[15:8] 
      main_W_com_data(0xEB,0x0020); //PTBA[7:0] 
      main_W_com_data(0xEC,0x003C); //STBA[15:8] 
      main_W_com_data(0xED,0x00C4); //STBA[7:0] 
      main_W_com_data(0xE8,0x0048); //OPON[7:0] 
      main_W_com_data(0xE9,0x0038); //OPON1[7:0] 
      main_W_com_data(0xF1,0x0001); //OTPS1B 
      main_W_com_data(0xF2,0x0008); //GEN 

      //Gamma 2.2 Setting 
      main_W_com_data(0x40,0x0001); // 
      main_W_com_data(0x41,0x0007); // 
      main_W_com_data(0x42,0x0009); // 
      main_W_com_data(0x43,0x0019); // 
      main_W_com_data(0x44,0x0017); // 
      main_W_com_data(0x45,0x0020); // 
      main_W_com_data(0x46,0x0018); // 
      main_W_com_data(0x47,0x0061); // 
      main_W_com_data(0x48,0x0000); // 
      main_W_com_data(0x49,0x0010); // 
      main_W_com_data(0x4A,0x0017); // 
      main_W_com_data(0x4B,0x0019); // 
      main_W_com_data(0x4C,0x0014); // 

      main_W_com_data(0x50,0x001F); // 
      main_W_com_data(0x51,0x0028); // 
      main_W_com_data(0x52,0x0026); // 
      main_W_com_data(0x53,0x0036); // 
      main_W_com_data(0x54,0x0038); // 
      main_W_com_data(0x55,0x003E); // 
      main_W_com_data(0x56,0x001E); // 
      main_W_com_data(0x57,0x0067); // 
      main_W_com_data(0x58,0x000B); // 
      main_W_com_data(0x59,0x0006); // 
      main_W_com_data(0x5A,0x0008); // 
      main_W_com_data(0x5B,0x000F); // 
      main_W_com_data(0x5C,0x001F); // 
      main_W_com_data(0x5D,0x00CC); // 

      //Power Voltage Setting 
      main_W_com_data(0x1B,0x001B); //VRH=4.65V 
      main_W_com_data(0x1A,0x0001); //BT (VGH~15V,VGL~-10V,DDVDH~5V) 
      main_W_com_data(0x24,0x0070); //VMH(VCOM High voltage ~4.2V) 
      main_W_com_data(0x25,0x0058); //VML(VCOM Low voltage -1.2V) 
      //VCOM offset/// 
      main_W_com_data(0x23,0x0093); //for Flicker adjust //can reload from OTP 
      //Power on Setting 
      main_W_com_data(0x18,0x0036); //I/P_RADJ,N/P_RADJ, Normal mode 70Hz 
      main_W_com_data(0x19,0x0001); //OSC_EN='1', start Osc 
      main_W_com_data(0x01,0x0002); //DP_STB='0', out deep sleep  INVON =1
      main_W_com_data(0x1F,0x0088);// GAS=1, VOMG=00, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=0
      SYSTICK_DelayMs ( 5 );
      main_W_com_data(0x1F,0x0080);// GAS=1, VOMG=00, PON=0, DK=0, XDK=0, DVDH_TRI=0, STB=0
      SYSTICK_DelayMs ( 5 );
      main_W_com_data(0x1F,0x0090);// GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
      SYSTICK_DelayMs ( 5 );
      main_W_com_data(0x1F,0x00D0);// GAS=1, VOMG=10, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
      SYSTICK_DelayMs ( 5 );

      //262k/65k color selection 
      main_W_com_data(0x17,0x0005); //default 0x06 262k color // 0x05 65k color 
      //SET PANEL 
      main_W_com_data(0x36,0x000B); //SS_P, GS_P,REV_P,BGR_P 09
      //Display ON Setting 
      main_W_com_data(0x28,0x0038); //GON=1, DTE=1, D=1000
      SYSTICK_DelayMs ( 40 );
      main_W_com_data(0x28,0x003F); //GON=1, DTE=1, D=1100 

      main_W_com_data(0x02,0x0000); 
      main_W_com_data(0x03,0x0000); 
      main_W_com_data(0x04,0x0000); 
      main_W_com_data(0x05,0x00EF); 

      main_W_com_data(0x06,0x0000); 
      main_W_com_data(0x07,0x0000); 
      main_W_com_data(0x08,0x0001); 
      main_W_com_data(0x09,0x003F); 

      LCD_Write_COM(0x22); //Start GRAM write 
	
      //-------------------------------------------------------------------------
      //------------------- END BILLY INITIALIZE CODE ---------------------------
      //-------------------------------------------------------------------------
    }
    
    		
    CS_Set();

    setColor(255, 255, 255);
    setBackColor(0, 0, 0);
    m_CurrentFont			= NULL;
    m_CurrentFontCodePage	= NULL;
}

//================================================
void TFTLCD::setXY(word x1, word y1, word x2, word y2)
{
    int tmp;

    if (orient==LANDSCAPE)
    {
	tmp=x1;
	x1=y1;
	y1=disp_y_size-tmp;
	tmp=x2;
	x2=y2;
	y2=disp_y_size-tmp;
	tmp=y1;
	y1=y2;
        y2=tmp;
    }
   
    if(DriverLCD == ILI9341) {
	// Column address 
	LCD_Write_COM(0x2A);
	LCD_Write_DATA(0x00, x1>>8);    // SC[15:8]  Start Column
	LCD_Write_DATA(0x00, x1);       // SC[7:0]
	LCD_Write_DATA(0x00, x2>>8);    // EC[15:8]  End Column
	LCD_Write_DATA(0x00, x2);   	// EC[7:0]
	
        // Page/Row address 
	LCD_Write_COM(0x2B);
	LCD_Write_DATA(0x00, y1>>8);  	// Row address start2
	LCD_Write_DATA(0x00, y1);	// Row address start1
	LCD_Write_DATA(0x00, y2>>8);  	// Row address end2
	LCD_Write_DATA(0x00, y2);	// Row address end1
	
	LCD_Write_COM(0x2C);            // Memory Write      

    }else {
     
       /********************
        *     HX8347
        ********************/     
	main_W_com_data(0x02,x1>>8);    // Column address start2
	main_W_com_data(0x03,x1);	// Column address start1
	main_W_com_data(0x04,x2>>8);    // Column address end2
	main_W_com_data(0x05,x2);	// Column address end1
	main_W_com_data(0x06,y1>>8);    // Row address start2
	main_W_com_data(0x07,y1);	// Row address start1
	main_W_com_data(0x08,y2>>8);    // Row address end2
	main_W_com_data(0x09,y2);	// Row address end1
	LCD_Write_COM(0x22);      
   }
		
}

void TFTLCD::drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
	    tmp=x1;
	    x1=x2;
	    x2=tmp;
	}
	if (y1>y2)
	{
	    tmp=y1;
	    y1=y2;
	    y2=tmp;
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void TFTLCD::drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void TFTLCD::fillRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (orient==PORTRAIT)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			drawHLine(x1, y1+i, x2-x1 + 1 );
			drawHLine(x1, y2-i, x2-x1 + 1 );
		}
	}
	else
	{
		for (int i=0; i<((x2-x1)/2)+1; i++)
		{
			drawVLine(x1+i, y1, y2-y1 + 1 );
			drawVLine(x2-i, y1, y2-y1 + 1 );
		}
	}
}

void TFTLCD::fillRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1 + 1 );
				drawHLine(x1, y2-i, x2-x1 + 1 );
			}
		}
	}
}

void TFTLCD::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);
 
	CS_Clear();
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(ch,cl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(ch,cl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(ch,cl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(ch,cl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(ch,cl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(ch,cl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(ch,cl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(ch,cl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(ch,cl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(ch,cl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(ch,cl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(ch,cl);
	}
	CS_Set();
	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
}

void TFTLCD::fillCircle(int x, int y, int radius)
{
	CS_Clear();
	for(int y1=-radius; y1<=radius; y1++) 
		for(int x1=-radius; x1<=radius; x1++) 
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				setXY(x+x1, y+y1, x+x1, y+y1);
				LCD_Write_DATA(((fcolorr&248)|fcolorg>>5),((fcolorg&28)<<3|fcolorb>>3));
			}
	CS_Set();
	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
}

void TFTLCD::clrScr()
{
	long i;
	
	CS_Clear();
	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
	RS_Set();
	for (i=0; i<(240*(disp_y_size+1)); i++)
	{
		LCD_Writ_Bus(0,0);
	}
	CS_Set();
}

void TFTLCD::fillScr(byte r, byte g, byte b)
{
	long i;
	char ch, cl;
	
	ch=((r&248)|g>>5);
	cl=((g&28)<<3|b>>3);

	CS_Clear();
	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
	RS_Set();
	for (i=0; i<(240*(disp_y_size+1)); i++)
	{
		LCD_Writ_Bus(ch,cl);
	}
	CS_Set();
}

void TFTLCD::setColor(byte r, byte g, byte b)
{
	fcolorr=r;
	fcolorg=g;
	fcolorb=b;
}

void TFTLCD::setRGBColor( RGBColor rgbColor )
{
	fcolorr	= (byte) ((rgbColor >> 16) & 0xFFL);
	fcolorg	= (byte) ((rgbColor >> 8) & 0xFF);
	fcolorb	= (byte) (rgbColor & 0xFF);
}

RGBColor TFTLCD::getRGBColor()
{
	return ((RGBColor) fcolorr << 16) | ((RGBColor) fcolorg << 8) | ((RGBColor) fcolorb);
}

void TFTLCD::setBackColor(byte r, byte g, byte b)
{
	bcolorr=r;
	bcolorg=g;
	bcolorb=b;
}

void TFTLCD::setRGBBackColor( RGBColor rgbColor )
{
	bcolorr	= (byte) ((rgbColor >> 16) & 0xFFL);
	bcolorg	= (byte) ((rgbColor >> 8) & 0xFF);
	bcolorb	= (byte) (rgbColor & 0xFF);
}

RGBColor TFTLCD::getRGBBackColor()
{
	return ((RGBColor) bcolorr << 16) | ((RGBColor) bcolorg << 8) | ((RGBColor) bcolorb);
}

void TFTLCD::setPixel(byte r,byte g,byte b)
{
	LCD_Write_DATA(((r&248)|g>>5),((g&28)<<3|b>>3));
}

void TFTLCD::drawPixel(int x, int y)
{
	CS_Clear();
	setXY(x, y, x, y);
	setPixel(fcolorr, fcolorg, fcolorb);
	CS_Set();
	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
}

void TFTLCD::drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		CS_Clear();
		delta=(double(y2-y1)/double(x2-x1));
		ty=double(y1);
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(ch, cl);
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				setXY(i, int(ty+0.5), i, int(ty+0.5));
				LCD_Write_DATA(ch, cl);
        		ty=ty+delta;
			}
		}
		CS_Set();
	}
	else
	{
		CS_Clear();
		delta=(float(x2-x1)/float(y2-y1));
		tx=float(x1);
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA(ch, cl);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		setXY(int(tx+0.5), i, int(tx+0.5), i);
				LCD_Write_DATA(ch, cl);
        		tx=tx+delta;
			}
        }
		CS_Set();
	}

	if (orient==PORTRAIT)
		setXY(0,0,239,disp_y_size);
	else
		setXY(0,0,disp_y_size,239);
}

void TFTLCD::drawHLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	CS_Clear();
	setXY(x, y, x+l-1, y);
	for (int i=0; i<l; i++)
	{
		LCD_Write_DATA(ch, cl);
	}
	CS_Set();
}

void TFTLCD::drawVLine(int x, int y, int l)
{
	char ch, cl;
	
	ch=((fcolorr&248)|fcolorg>>5);
	cl=((fcolorg&28)<<3|fcolorb>>3);

	CS_Clear();
	setXY(x, y, x, y+l-1);
	for (int i=0; i<l; i++)
	{
		LCD_Write_DATA(ch, cl);
	}
	CS_Set();
}

void TFTLCD::printChar(byte c, int x, int y)
{
	byte i,j,ch;
	const byte* fontCharPtr;

	if (m_CurrentFont == NULL || m_CurrentFontCodePage == NULL)
		return;

	CS_Clear();
  
	if (orient==PORTRAIT)
	{
		setXY( x, y, x + m_CurrentFont->Width - 1, y + m_CurrentFont->Height - 1 );
	  
		fontCharPtr = GetFontChar( c );
		for(j = 0; j < ((m_CurrentFont->Width / 8) * m_CurrentFont->Height); j++)
		{
			ch=*fontCharPtr;
			for(i=0;i<8;i++)
			{   
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
			fontCharPtr++;
		}
	}
	else
	{
		fontCharPtr = GetFontChar( c );

		for(j = 0; j < ((m_CurrentFont->Width / 8) * m_CurrentFont->Height); j += (m_CurrentFont->Width / 8 ))
		{
			setXY( x, y + (j / (m_CurrentFont->Width / 8)), x + m_CurrentFont->Width - 1, y + (j / (m_CurrentFont->Width / 8)));
			for (int zz = (m_CurrentFont->Width / 8) - 1; zz >= 0; zz--)
			{
				ch = *(fontCharPtr + zz);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<i))!=0)   
					{
						setPixel(fcolorr, fcolorg, fcolorb);
					} 
					else
					{
						setPixel(bcolorr, bcolorg, bcolorb);
					}   
				}
			}
			fontCharPtr += (m_CurrentFont->Width / 8);
		}
	}
	CS_Set();
}

void TFTLCD::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	const byte* fontCharPtr;
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	CS_Clear();

	fontCharPtr = GetFontChar( c );
	for (j = 0; j < m_CurrentFont->Height; j++)
	{
		for (int zz = 0; zz < (m_CurrentFont->Width / 8); zz++)
		{
			ch = *(fontCharPtr + zz);
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*m_CurrentFont->Width))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*m_CurrentFont->Width))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel(fcolorr, fcolorg, fcolorb);
				} 
				else  
				{
					setPixel(bcolorr, bcolorg, bcolorb);
				}   
			}
		}
		fontCharPtr += (m_CurrentFont->Width / 8);
	}
	CS_Set();
}

void TFTLCD::printWidth(const char *st, int x, int y, int numChar, int deg)
{
	int stl, i;

	stl = strlen(st);
	if (stl > numChar)
		stl	= numChar;

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=240-(stl*m_CurrentFont->Width);
	if (x==CENTER)
		x=(240-(stl*m_CurrentFont->Width))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*m_CurrentFont->Width);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*m_CurrentFont->Width))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(m_CurrentFont->Width)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void TFTLCD::print(const char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=240-(stl*m_CurrentFont->Width);
	if (x==CENTER)
		x=(240-(stl*m_CurrentFont->Width))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*m_CurrentFont->Width);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*m_CurrentFont->Width))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(m_CurrentFont->Width)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void TFTLCD::printNumI(long num, int x, int y)
{
  char buf[25];
  char st[27];
  bool neg = false;
  int c=0;
  
  if (num==0)
  {
	  st[0]=48;
	  st[1]=0;
  }
  else
  {
	  if (num<0)
	  {
		neg = true;
		num=-num;
	  }
	  
	  while (num>0)
	  {
		buf[c]=48+(num % 10);
		c++;
		num=(num-(num % 10))/10;
	  }
	  buf[c]=0;
	  
	  if (neg)
	  {
		st[0]=45;
	  }
	  
	  for (int i=0; i<c; i++)
	  {
		st[i+neg]=buf[c-i-1];
	  }
	  st[c+neg]=0;
  }

  print(st,x,y);
}

void TFTLCD::printNumF(double num, byte dec, int x, int y)
{
  char buf[25];
  char st[27];
  bool neg=false;
  int c=0;
  int c2;
  unsigned long inum;
  
  if (num==0)
  {
	  st[0]=48;
	  st[1]=46;
	  for (int i=0; i<dec; i++)
		  st[2+i]=48;
	  st[2+dec]=0;
  }
  else
  {
	  if (num<0)
	  {
		neg=true;
		num=-num;
	  }
	  
	  if (dec<1)
		dec=1;
	  if (dec>5)
		dec=5;
	  
	  inum=long(num*pow(10,dec));
	  
	  while (inum>0)
	  {
		buf[c]=48+(inum % 10);
		c++;
		inum=(inum-(inum % 10))/10;
	  }
	  if ((num<1) and (num>0))
	  {
		  buf[c]=48;
		  c++;
	  }
	  buf[c]=0;
	  
	  if (neg)
	  {
		st[0]=45;
	  }
	  
	  c2=neg;
	  for (int i=0; i<c; i++)
	  {
		st[c2]=buf[c-i-1];
		c2++;
		if ((c-(c2-neg))==dec)
		{
		  st[c2]=46;
		  c2++;
		}
	  }
	  st[c2]=0;
  }

  print(st,x,y);
}

void TFTLCD::setFont( Font* font, int codePage )
{
	if (font == NULL)
	{
		m_CurrentFont			= NULL;
		m_CurrentFontCodePage	= NULL;
	}
	else
	{
		m_CurrentFontCodePage	= NULL;
		m_CurrentFont			= font;

		for (int codePagesCounter = 0; codePagesCounter < m_CurrentFont->CodePageCount; codePagesCounter++)
		{
			if (m_CurrentFont->CodePages[ codePagesCounter ].Code == codePage)
			{
				m_CurrentFontCodePage	= &m_CurrentFont->CodePages[ codePagesCounter ];
				break;
			}
		}

		if (m_CurrentFontCodePage == NULL && m_CurrentFont->CodePages != NULL && m_CurrentFont->CodePageCount > 0)
			m_CurrentFontCodePage	= &m_CurrentFont->CodePages[ 0 ];
	}
}

Font* TFTLCD::getFont()
{
	return m_CurrentFont;
}

int TFTLCD::getFontCodePage()
{
	return m_CurrentFontCodePage == NULL ? 0 : m_CurrentFontCodePage->Code;
}

const byte* TFTLCD::GetFontChar( byte character, bool returnNullIfNotExist )
{
	unsigned short	charIndex	= m_CurrentFontCodePage->CharMaps[ character ];

	if (charIndex == 0xFFFF)
	{
		if (returnNullIfNotExist)
			return NULL;

		charIndex	= m_CurrentFontCodePage->CharMaps[ 0x20 ];
	}

	return (const byte*) (m_CurrentFont->Chars + charIndex * m_CurrentFont->BytePerChar);
}

uint8_t TFTLCD::getFontXSize()
{
	return m_CurrentFont != NULL ? m_CurrentFont->Width : 0;
}

uint8_t TFTLCD::getFontYSize()
{
	return m_CurrentFont != NULL ? m_CurrentFont->Height : 0;
}

bool TFTLCD::hasChar( char character )
{
	return GetFontChar( character, true ) != NULL ? true : false;
}

void TFTLCD::drawBitmapMono( int x, int y, int sx, int sy, const unsigned char* data,
	RGBColor backgroundColor, RGBColor foregroundColor )
{
	int				tx, ty, tc;
	char			foregroundH	= RGBColor_MAKEColorHigh( foregroundColor );
	char			foregroundL	= RGBColor_MAKEColorLow( foregroundColor );
	char			backgroundH	= RGBColor_MAKEColorHigh( backgroundColor );
	char			backgroundL	= RGBColor_MAKEColorLow( backgroundColor );
	unsigned char*	currentData	= (unsigned char*) data;
	byte			mask;

	if (orient==PORTRAIT)
	{
		mask	= 0x80;

		CS_Clear();
		setXY(x, y, x+sx-1, y+sy-1);
		for (tc=0; tc<(sx*sy); tc++)
		{
			if ((*currentData) & mask)
				LCD_Write_DATA( foregroundH, foregroundL );
			else
				LCD_Write_DATA( backgroundH, backgroundL );

			mask >>= 1;
			if (!mask)
			{
				currentData++;
				mask	= 0x80;
			}
		}
		CS_Set();
	}
	else
	{
		CS_Clear();
		for (ty=0; ty<sy; ty++)
		{
			short	lastRowBit	= ((sx * (ty + 1)) - 1);
			
			currentData	= (unsigned char*) data + (lastRowBit / 8) - 1 + (lastRowBit % 8 == 0 ? 0 : 1);
			mask		= (0x80 >> (lastRowBit % 8)) & 0xFF;

			setXY(x, y+ty, x+sx-1, y+ty);
			for (tx=sx; tx>=0; tx--)
			{
				if (*currentData & mask)
					LCD_Write_DATA( foregroundH, foregroundL );
				else
					LCD_Write_DATA( backgroundH, backgroundL );

				mask <<= 1;
				if (!(mask & 0xFF))
				{
					currentData--;
					mask	= 0x01;
				}
			}
		}
		CS_Set();
	}
}

void TFTLCD::drawBitmap( int x, int y, int sx, int sy,
	const unsigned short* data,
	const unsigned char* mask, RGBColor maskBackgroundColor, RGBColor maskForegroundColor,
	int scale )
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;
	unsigned int maskBackgroundColor565 = Color565_Make( maskBackgroundColor );
	unsigned int maskForegroundColor565 = Color565_Make( maskForegroundColor );

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
			CS_Clear();
			setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				if (mask != NULL)
				{
					if (!(mask[ tc / 8 ] & (7 - (tc % 8))))
						col	= (maskBackgroundColor == RGBColor_Empty ? data[ tc ] : maskBackgroundColor565);
					else
						col	= (maskForegroundColor == RGBColor_Empty ? data[ tc ] : maskForegroundColor565);
				}
				else
					col=data[ tc ];

				LCD_Write_DATA(col>>8,col & 0xff);
			}
			CS_Set();
		}
		else
		{
			CS_Clear();
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx-1; tx>=0; tx--)
				{
					int	pos	= (ty*sx)+tx;
					if (mask != NULL)
					{
						if (!(mask[ pos / 8 ] & (1 << (7 - (pos % 8)))))
							col	= (maskBackgroundColor == RGBColor_Empty ? data[ pos ] : maskBackgroundColor565);
						else
							col	= (maskForegroundColor == RGBColor_Empty ? data[ pos ] : maskForegroundColor565);
					}
					else
						col=data[pos];

					LCD_Write_DATA(col>>8,col & 0xff);
				}
			}
			CS_Set();
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
			CS_Clear();
			for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=data[(ty*sx)+tx];
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
			}
			CS_Set();
		}
		else
		{
			CS_Clear();
			for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx; tx>=0; tx--)
					{
						col=data[(ty*sx)+tx];
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
				}
			}
			CS_Set();
		}
	}
}

void TFTLCD::drawBitmap(int x, int y, int sx, int sy, const unsigned short* data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	byte r, g, b;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{
		CS_Clear();
		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
				col=data[(ty*sx)+tx];

				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
		CS_Set();
	}
}

int TFTLCD::getHeight()
{
	if (orient == LANDSCAPE)
		return 320;
	return 240;
}

int TFTLCD::getWidth()
{
	if (orient == LANDSCAPE)
		return 240;
	return 320;
}

int TFTLCD::getMaxX()
{
	if (orient == LANDSCAPE)
		return 319;
	return 239;
}

int TFTLCD::getMaxY()
{
	if (orient == LANDSCAPE)
		return 239;
	return 319;
}

int TFTLCD::getMinX()
{
	return 0;
}

int TFTLCD::getMinY()
{
	return 0;
}

#endif

