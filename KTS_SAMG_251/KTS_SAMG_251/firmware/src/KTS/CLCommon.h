 /*************************************************************************************
 *  file:			CLCommon.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLCommon_H
#define __CLCommon_H

#include "CLKTSDefines.h"
#include "Rtc_Pcf8563.h"
#include <stdio.h>

// Di default è abilitata solo la configurazione di ventilazione OFF
#define FIREALARM_ALL_CONFIGURATION 0

/*-------------------------------------------------------------------------------------------------
  [1] Selezione del CUSTOMER, impostare la macro CUSTOMERID con il customer interessato
*------------------------------------------------------------------------------------------------*/
#define CUSTOMERID_FA	0
#define CUSTOMERID_NL	1
#define CUSTOMERID_UE	2
#define CUSTOMERID_CL	3
#define CUSTOMERID_FS	4
#define CUSTOMERID_FT	5
#define CUSTOMERID_FAI	6
#define CUSTOMERID_CV	7
#define CUSTOMERID_AC	8
#define CUSTOMERID_WE	9
#define CUSTOMERID_AL	10
#define CUSTOMERID_SIG	11
#define CUSTOMERID_AV	12
#define CUSTOMERID_IN	13
#define CUSTOMERID_TL	14

#define LANGUAGE_DISABLED ((1 << CLLanguageId_BG) | (1 << CLLanguageId_HU) | (1 << CLLanguageId_RO))

// Modificare il define presente in CLBuildConfiguration.h
#include "CLBuildConfiguration.h"

#ifdef _CLIKTS
	#ifdef CUSTOMERID
	#undef CUSTOMERID
	#endif

	#ifdef KTS_SHOWFONTSFORM
	#undef KTS_SHOWFONTSFORM
	#endif
	#define KTS_SHOWFONTSFORM	0

	#ifdef KTS_DEBUG
	#undef KTS_DEBUG
	#endif
	#define KTS_DEBUG	0

	#if defined KTSCLI_FA
	#define CUSTOMERID	CUSTOMERID_FA
	#elif defined KTSCLI_FAI
	#define CUSTOMERID	CUSTOMERID_FAI
	#elif defined KTSCLI_FS
	#define CUSTOMERID	CUSTOMERID_FS
	#elif defined KTSCLI_FT
	#define CUSTOMERID	CUSTOMERID_FT
	#elif defined KTSCLI_NL
	#define CUSTOMERID	CUSTOMERID_NL
	#elif defined KTSCLI_CL
	#define CUSTOMERID	CUSTOMERID_CL
	#elif defined KTSCLI_CV
	#define CUSTOMERID	CUSTOMERID_CV
	#elif defined KTSCLI_AC
	#define CUSTOMERID	CUSTOMERID_AC
	#elif defined KTSCLI_WE
	#define CUSTOMERID	CUSTOMERID_WE
	#elif defined KTSCLI_AL
	#define CUSTOMERID	CUSTOMERID_AL
	#elif defined KTSCLI_SIG
	#define CUSTOMERID	CUSTOMERID_SIG
	#elif defined KTSCLI_UE
	#define CUSTOMERID	CUSTOMERID_UE
	#elif defined KTSCLI_AV
	#define CUSTOMERID	CUSTOMERID_AV
	#elif defined KTSCLI_IN
	#define CUSTOMERID	CUSTOMERID_IN
	#elif defined KTSCLI_TL
	#define CUSTOMERID	CUSTOMERID_TL
	#else
	#pragma message( "Nessuno Cliente selezionato" )
	#endif
#endif

#if CUSTOMERID == CUSTOMERID_CL

// Configurazione del language
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_AV

// Configurazione del language
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_FA

// Abilita tutte le configurazioni di allarme fuoco
#ifdef FIREALARM_ALL_CONFIGURATION
#undef FIREALARM_ALL_CONFIGURATION
#endif
#define FIREALARM_ALL_CONFIGURATION 1

// Abilita la gestione della classe TX
#define FRANCETX_ENABLED

// Configurazione del language
#define LANGUAGE_ENABLED	((1 << CLLanguageId_FR) | (1 << CLLanguageId_EN) | (1 << CLLanguageId_PT))
#define LANGUAGE_PRIMARY	CLLanguageId_FR
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_FAI

// Configurazione del language
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_FS

// Configurazione dei languages
#define LANGUAGE_ENABLED	((1 << CLLanguageId_EN) | (1 << CLLanguageId_PL))
#define LANGUAGE_PRIMARY	CLLanguageId_PL
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_FT

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_NL

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_DE
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_CV

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_NL
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_AC

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_WE

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_DE
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_AL

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_DE
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_SIG

// Configurazione dei languages
#define LANGUAGE_ENABLED	0xFFFF
#define LANGUAGE_PRIMARY	CLLanguageId_EN
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_IN

// Configurazione dei languages
#define LANGUAGE_ENABLED	0xFFFF
#define LANGUAGE_PRIMARY	CLLanguageId_EN
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_TL

// Configurazione dei languages
#define LANGUAGE_ENABLED	0xFFFF
#define LANGUAGE_PRIMARY	CLLanguageId_NL
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#elif CUSTOMERID == CUSTOMERID_UE

// Configurazione dei languages
#define LANGUAGE_ENABLED	(0xFFFF & (~LANGUAGE_DISABLED))
#define LANGUAGE_PRIMARY	CLLanguageId_IT
#define LANGUAGE_SECONDARY	CLLanguageId_EN

#endif

#define MAKEWORD( _Buffer, _HiIndex, _LoIndex ) ((word) (_Buffer[ _HiIndex ] << 8) | (word) _Buffer[ _LoIndex ])
#define MAKEINT( _Buffer, _HiIndex, _LoIndex ) ((int) (_Buffer[ _HiIndex ] << 8) | (int) _Buffer[ _LoIndex ])
#define MAKESHORT( _Buffer, _HiIndex, _LoIndex ) ((short) (_Buffer[ _HiIndex ] << 8) | (short) _Buffer[ _LoIndex ])
#define MAX( n1, n2 ) (n1 > n2 ? n1 : n2)
#define MIN( n1, n2 ) (n1 < n2 ? n1 : n2)

#define GET2BITVALUE( value, index ) ((value >> (index << 1)) & 0x03)
#define SET2BITVALUE( value, index, bitValue ) (value & ~(0x03 << (index * 2))) | (bitValue << (index * 2))


#if KTS_DEBUG == 1
#define SERVICE_PASSWORD_OFF
#endif

// =============================================================================
// CLCommon [class]
// =============================================================================
// Description: Common Functions
// -----------------------------------------------------------------------------
class CLCommon
{
	public: static void String_AppendCharacters( char* text, char character, int maxLength );
	public: static int PercentageToM3H( float percentage );
	public: static char* ByteToHexString( char* buffer, char* prefix, int length );
};

// -----------------------------------------------------------------------------
// CLKTSCommon [class]
// =============================================================================

#endif
