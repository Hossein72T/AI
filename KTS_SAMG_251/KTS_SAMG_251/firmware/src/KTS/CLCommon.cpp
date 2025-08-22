#include "CLCommon.h"

#include "CLCommunicationManager.h"
#include "CLKTS.h"

// =============================================================================
// CLCommon [class]
// -----------------------------------------------------------------------------
void CLCommon::String_AppendCharacters( char* text, char character, int maxLength )
{
	char	temp[ 2 ];
	temp[ 0 ]	= character;
	temp[ 1 ]	= '\0';

	while (strlen( text ) < maxLength)
		strcat( text, temp );
}

int CLCommon::PercentageToM3H( float percentage /* 0-1 */ )
{
	return (int) ((float) CLKTS::AirFlow_GetMax() * percentage);
}

char* ByteToHexString( char* buffer, char* prefix, int length )
{
	static char text[ 512 ];
	char*	ptrBuffer	= buffer;
	const char* hexValues = "0123456789ABCDEF";

	sprintf( text, "%s (%d) [", prefix, length );
    for (int counter = 0; counter < length; counter++, ptrBuffer++)
	{
		char	textHex[ 8 ];
		textHex[ 0 ]	= hexValues[ (((*ptrBuffer) >> 4) & 0x0F) ];
		textHex[ 1 ]	= hexValues[ (*ptrBuffer) & 0x0F ];
 		textHex[ 2 ]	= ' ';
		textHex[ 3 ]	= '\0';
		strcat( text, textHex );
	}

	strcat( text, "]\n\r" );

	return text;
}
// -----------------------------------------------------------------------------
// CLCommon [class]
// =============================================================================

