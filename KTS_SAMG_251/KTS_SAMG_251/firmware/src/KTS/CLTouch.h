 /*************************************************************************************
 *  file:			CLTouch.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLTouch_h
#define __CLTouch_h

#include "CLCommon.h"
#include "TFTLCD.h"

// Taratura
extern int Y_Offset;
extern int Y_Max;
extern int X_Offset;
extern int X_Max;

// global variable X and Y, the coordinates of the point pressed
extern int X_GLOBAL;
extern int Y_GLOBAL;

int Touched();
void WaitForTouchRelease();
int ReadX();
int ReadY();
int ReadXY();

#endif

