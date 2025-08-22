#include "CLKTSEeprom.h" 

// =============================================================================
// CLEeprom [class]
// -----------------------------------------------------------------------------
CLKTSEeprom::CLKTSEeprom()
{
	// Set default values
	m_ScreensaverEnabled	= 0;
	m_ScreensaverMinutes	= 5;
	m_Language				= 0;
	m_DesktopBoxInfo		= 0;
	m_DaylightSavingTime	= 0;
	m_DeviceID				= 0;
}

void CLKTSEeprom::ReadEeprom()
{
	ReadEeprom_FirstTime();
	ReadEeprom_Language();
	ReadEeprom_DesktopBoxInfo();
	ReadEeprom_ScreenSaver();
	ReadEeprom_DaylightSavingTime();
	ReadEeprom_RFMChannel();
	ReadEeprom_DeviceID();
}

void CLKTSEeprom::SetScreensaver( bool enabled, byte minutes )
{
	m_ScreensaverEnabled	= (enabled ? 1 : 0);
	m_ScreensaverMinutes	= minutes & 0x0F;
	
	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData1 );
	WriteAddress( CLKTSEepromAddress_KTSData2 );
}

bool CLKTSEeprom::GetScreensaverEnabled()
{
	return (m_ScreensaverEnabled ? true : false);
}

byte CLKTSEeprom::GetScreensaverMinutes()
{
	return m_ScreensaverMinutes;
}

void CLKTSEeprom::ReadEeprom_ScreenSaver()
{
	m_ScreensaverEnabled	= (EEPROM_read_byte( CLKTSEepromAddress_KTSData1 ) & 0x01);
	m_ScreensaverMinutes	= (EEPROM_read_byte( CLKTSEepromAddress_KTSData2 ) & 0x0F);
}

void CLKTSEeprom::SetLanguage( byte value )
{
	m_Language	= value;

	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData2 );
}

byte CLKTSEeprom::GetLanguage()
{
	return m_Language;
}

void CLKTSEeprom::ReadEeprom_Language()
{
	m_Language	= ((EEPROM_read_byte( CLKTSEepromAddress_KTSData2 ) >> 4) & 0x0F);
}

void CLKTSEeprom::SetDaylightSavingTime( bool value )
{
	m_DaylightSavingTime	= (value ? 1 : 0);
	
	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData1 );
}

bool CLKTSEeprom::GetDaylightSavingTime()
{
	return (m_DaylightSavingTime ? true : false);
}

void CLKTSEeprom::ReadEeprom_DaylightSavingTime()
{
	m_DaylightSavingTime	= ((EEPROM_read_byte( CLKTSEepromAddress_KTSData1 ) >> 1) & 0x01);
}

void CLKTSEeprom::SetDesktopBoxInfo( byte value )
{
	m_DesktopBoxInfo	= value;
	
	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData3 );
}

byte CLKTSEeprom::GetDesktopBoxInfo()
{
	return m_DesktopBoxInfo;
}

void CLKTSEeprom::ReadEeprom_DesktopBoxInfo()
{
	m_DesktopBoxInfo	= EEPROM_read_byte( CLKTSEepromAddress_KTSData3 );
}

void CLKTSEeprom::SetRFMChannel( byte value )
{
	m_RFMChannel	= value;
	
	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData4 );
}

byte CLKTSEeprom::GetRFMChannel()
{
	return m_RFMChannel;
}

void CLKTSEeprom::ReadEeprom_RFMChannel()
{
	m_RFMChannel	= EEPROM_read_byte( CLKTSEepromAddress_KTSData4 ) & 0x7F;
}

void CLKTSEeprom::SetFirstTime( bool value )
{
	m_FirstTime	= (value ? 0x0F : 0x0A);

	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_KTSData1 );
}

bool CLKTSEeprom::GetFirstTime()
{
	return (m_FirstTime == 0x0A ? false : true);
}

void CLKTSEeprom::ReadEeprom_FirstTime()
{
	m_FirstTime	= (EEPROM_read_byte( CLKTSEepromAddress_KTSData1 ) >> 2) & 0x0F;
}

void CLKTSEeprom::SetDeviceID( unsigned short value )
{
	m_DeviceID	= value;

	// Write Eeprom
	WriteAddress( CLKTSEepromAddress_DeviceID1 );
	WriteAddress( CLKTSEepromAddress_DeviceID2 );
}

unsigned short CLKTSEeprom::GetDeviceID()
{
	return m_DeviceID;
}

void CLKTSEeprom::ReadEeprom_DeviceID()
{
	m_DeviceID	= ((unsigned short) EEPROM_read_byte( CLKTSEepromAddress_DeviceID2 ) << 8) |
		(unsigned short) EEPROM_read_byte( CLKTSEepromAddress_DeviceID1 );
}

void CLKTSEeprom::WriteAddress( int address )
{
	switch (address)
	{
		case CLKTSEepromAddress_KTSData1:
			EEPROM_write_byte( CLKTSEepromAddress_KTSData1,
				((m_FirstTime & 0x0F) << 2) |
				((m_DaylightSavingTime & 0x01) << 1) |
				(m_ScreensaverEnabled & 0x01) );
			break;

		case CLKTSEepromAddress_KTSData2:
			EEPROM_write_byte( CLKTSEepromAddress_KTSData2,
				((m_Language & 0x0F) << 4) |
				(m_ScreensaverMinutes & 0x0F) );
			break;

		case CLKTSEepromAddress_KTSData3:
			EEPROM_write_byte( CLKTSEepromAddress_KTSData3,
				m_DesktopBoxInfo );
			break;

		case CLKTSEepromAddress_KTSData4:
			EEPROM_write_byte( CLKTSEepromAddress_KTSData4,
				m_RFMChannel & 0x7F );
			break;

		case CLKTSEepromAddress_DeviceID1:
			EEPROM_write_byte( CLKTSEepromAddress_DeviceID1,
				(byte) (m_DeviceID & 0xFF) );
			break;

		case CLKTSEepromAddress_DeviceID2:
			EEPROM_write_byte( CLKTSEepromAddress_DeviceID2,
				(byte) ((m_DeviceID >> 8) & 0xFF) );
			break;
	}
}

void CLKTSEeprom::Reset()
{
	EEPROM_write_byte( CLKTSEepromAddress_KTSData1, 0xFF );
	EEPROM_write_byte( CLKTSEepromAddress_KTSData2, 0xFF );
	EEPROM_write_byte( CLKTSEepromAddress_KTSData3, 0xFF );
	EEPROM_write_byte( CLKTSEepromAddress_KTSData4, 0xFF );
	EEPROM_write_byte( CLKTSEepromAddress_DeviceID1, 0xFF );
	EEPROM_write_byte( CLKTSEepromAddress_DeviceID2, 0xFF );
}
// -----------------------------------------------------------------------------
// CLKTSEeprom [class]
// =============================================================================
 



