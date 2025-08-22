#ifndef __CLFranceTX_h
#define __CLFranceTX_h

#include "CLCommon.h"

#ifdef FRANCETX_ENABLED

const short FranceTx_ClassCount = 5;
const short FranceTx_StepMotorsFSC_CAF_StateIndex = 2;

extern short FranceTx_Classes[ FranceTx_ClassCount ][ 2 ];


// Funzioni per la gestione della modalità France TX
char* FranceTx_GetText( char* text, byte classIndex );
char* FranceTx_GetText( char* text, byte classIndex, byte subClassIndex );

bool FranceTx_GetClassIndexFromPercentage( byte percentage, byte& classIndex, byte& classSubIndex );
byte FranceTx_GetPercentageFromClassIndex( byte classIndex, byte classSubIndex );

unsigned short FranceTx_EncodeState( byte classIndex );
bool FranceTx_DecodeState( unsigned short value, byte* classIndex );

bool FranceTx_CanSelect();
bool FranceTx_IsEnabled();
void FranceTx_SetState( unsigned short value );
unsigned short FranceTx_GetState();
#endif

#endif

