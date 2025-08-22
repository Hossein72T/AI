#include "CLLogo.h"
#include "CLKTS.h"

CLImage LogoImage( CLImage::ImageType_16Bit_565,
	CLImage565_Logo_Width, CLImage565_Logo_Height,
	(const unsigned char*) CLImage565_Logo );

/**********************************************************************
  Stampa il Logo, con la possibilitÃ  di scegliere la posizione o passando
  le coordinate x-y oppure in altri 4 modi differenti:
  
      ALIGNED_LOGO_CENTER    'C' allinea l'immagine al centro.
      ALIGNED_LOGO_TOP       'T'
      ALIGNED_LOGO_BOTTON    'B'
      ALIGNED_LOGO_XY        '0'
      MOVE_LOGO_XY           'M'  Ad ogni chiamata di funzione cambia la posizione
  
  N.B: Dimensioni Dislay   320 x 240 
 **********************************************************************/
void logo( int x, int y, byte aligned )
{
	unsigned short*	pLogo;
	int				pos_x = x, pos_y = y;
  
	pLogo = (unsigned short *) LogoImage.GetData();

	switch (aligned)
	{
		case ALIGNED_LOGO_CENTER:  
			pos_x	= (gLCD.getMaxX() - LogoImage.GetWidth()) >> 1; 
			pos_y	= (gLCD.getMaxY() - LogoImage.GetHeight()) >> 1;  
			break;  
     
		case ALIGNED_LOGO_TOP:    
			pos_x	= (gLCD.getMaxX() - LogoImage.GetWidth()) >> 1;
			pos_y	= 0;   
			break; 
     
		case ALIGNED_LOGO_BOTTON:  
			pos_x	= (gLCD.getMaxX() - LogoImage.GetWidth()) >> 1;; 
			pos_y	= gLCD.getMaxY() - LogoImage.GetHeight();
			break; 
     
		case MOVE_LOGO_XY:
			//pos_x	= random( gLCD.getMaxX() - LogoImage.GetWidth() );
			//pos_y	= random( gLCD.getMaxY() - LogoImage.GetHeight() );
            pos_x	= randint( gLCD.getMaxX() - LogoImage.GetWidth() );
			pos_y	= randint( gLCD.getMaxY() - LogoImage.GetHeight() );
			break;
     
		default:
			pos_x = x;         
			pos_y = y;
			break;    
	} 
  
	// N.B: Dimensioni Dislay   320 x 240 
	// protezione x  
	if (x > gLCD.getMaxX() - LogoImage.GetWidth())
		pos_x = gLCD.getMaxX() - LogoImage.GetWidth();
	
	// protezione y
	if (y > gLCD.getMaxY() - LogoImage.GetHeight())
		pos_y = gLCD.getMaxY() - LogoImage.GetHeight(); 
  
	// Clear the screen with white
	gLCD.fillScr(255, 255, 255); 

	// print the immage
	gLCD.drawBitmap( pos_x, pos_y,
		LogoImage.GetWidth(), LogoImage.GetHeight(),
		(unsigned short*) pLogo );
}

