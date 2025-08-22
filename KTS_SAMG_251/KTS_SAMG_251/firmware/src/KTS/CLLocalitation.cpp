#include "CLLocalitation.h"
#include "CLLanguage_DE.h"
#include "CLLanguage_EN.h"
#include "CLLanguage_FR.h"
#include "CLLanguage_IT.h"
#include "CLLanguage_NL.h"
#include "CLLanguage_PT.h"
#include "CLLanguage_PL.h"
#include "CLLanguage_SL.h"
#include "CLLanguage_RO.h"
#include "CLLanguage_BG.h"
#include "CLLanguage_HU.h"
#include "CLLanguage_TR.h"
#include "CLFonts.h"

const char* CLText_NoText = NULL;

const char* CLFixedText_BPD		= "BPD";
const char* CLFixedText_ON		= "ON";
const char* CLFixedText_OFF		= "OFF";
const char* CLFixedText_OK		= "OK";
const char* CLFixedText_CAF		= "CAF";
const char* CLFixedText_CAP		= "CAP";
const char* CLFixedText_FSC		= "FSC";
const char* CLFixedText_RH		= "RH";
const char* CLFixedText_CO2		= "CO2";
const char* CLFixedText_PPM		= "ppm";
const char* CLFixedText_VOC		= "VOC";
const char* CLFixedText_AWP		= "AWP";
const char* CLFixedText_M3_H	= "m3/h";
const char* CLFixedText_Perc	= "%";
const char* CLFixedText_PA		= "Pa";
const char* CLFixedText_CRLF	= "\r\n";
const char CLFixedText_ugM3[]	= { FONT_SYMBOL_MICRO, 'g', '/', 'M', '3', '\0' };
const char* CLFixedText_IPHED	= "IPEHD";
const char* CLFixedText_PHED	= "PEHD";

// =============================================================================
// CLLocalitation [class]
// -----------------------------------------------------------------------------
int CLLocalitation::m_PrimaryLanguageId			= 0xFF;
char** CLLocalitation::m_PrimaryLanguageTexts	= NULL;
int CLLocalitation::m_SecondaryLanguageId		= 0xFF;
char** CLLocalitation::m_SecondaryLanguageTexts	= NULL;

void CLLocalitation::SetPrimaryLanguage( int languageId )
{
	m_PrimaryLanguageId		= languageId;
	m_PrimaryLanguageTexts	= (char**) GetLanguageTexts( languageId );
}

const char** CLLocalitation::GetLanguageTexts( int languageId )
{
	switch (languageId)
	{
		case CLLanguageId_NL:	return gLanguage_NLTexts;
		case CLLanguageId_EN:	return gLanguage_ENTexts;
		case CLLanguageId_FR:	return gLanguage_FRTexts;
		case CLLanguageId_DE:	return gLanguage_DETexts;
		case CLLanguageId_IT:	return gLanguage_ITTexts;
		case CLLanguageId_PT:	return gLanguage_PTTexts;
		case CLLanguageId_PL:	return gLanguage_PLTexts;
		case CLLanguageId_SL:	return gLanguage_SLTexts;
		case CLLanguageId_RO:	return gLanguage_ROTexts;
		case CLLanguageId_BG:	return gLanguage_BGTexts;
		case CLLanguageId_HU:	return gLanguage_HUTexts;
	}
	return NULL;
}

int CLLocalitation::GetPrimaryLanguageId()
{
	return m_PrimaryLanguageId;
}

const char** CLLocalitation::GetPrimaryLanguageTexts()
{
	return (const char**) m_PrimaryLanguageTexts;
}

void CLLocalitation::SetSecondaryLanguage( int languageId )
{
	m_SecondaryLanguageId		= languageId;
	m_SecondaryLanguageTexts	= (char**) GetLanguageTexts( languageId );
}

int CLLocalitation::GetSecondaryLanguageId()
{
	return m_SecondaryLanguageId;
}

const char** CLLocalitation::GetSecondaryLanguageTexts()
{
	return (const char**) m_SecondaryLanguageTexts;
}

const char* CLLocalitation::GetText( short id )
{
	char*	text	= NULL;
	if (m_PrimaryLanguageTexts != NULL)
	{
		if ((text = m_PrimaryLanguageTexts[ id ]) != NULL)
			return text;
	}
	if (m_SecondaryLanguageTexts != NULL)
	{
		if ((text = m_SecondaryLanguageTexts[ id ]) != NULL)
			return text;
	}
	return "";
}
// -----------------------------------------------------------------------------
// CLLocalitation [class]
// =============================================================================


