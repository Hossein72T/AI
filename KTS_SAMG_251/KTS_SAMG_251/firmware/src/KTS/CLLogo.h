#ifndef _CLLogo_h
#define _CLLogo_h

#include "CLCommon.h"
#include "CLGraphics.h"

extern const unsigned short CLImage565_Logo[];
extern const short CLImage565_Logo_Width;
extern const short CLImage565_Logo_Height;
extern CLImage LogoImage;

// Definisci le posizioni del logo nel Display
#define ALIGNED_LOGO_CENTER    'C'
#define ALIGNED_LOGO_TOP       'T'
#define ALIGNED_LOGO_BOTTON    'B'
#define ALIGNED_LOGO_XY        '0'
#define MOVE_LOGO_XY           'M'  // ada ogni chiamata della funzione cambia la posizione

void logo( int x, int y, byte aligned );

#endif

