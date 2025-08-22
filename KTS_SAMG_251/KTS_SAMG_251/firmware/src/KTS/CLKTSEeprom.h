 /*************************************************************************************
 *  file:			CLKTSEeprom.h
 *
 *  Author/Date:	Paolo Menchi aprile 2015
 *
 *  Descrizione:	Contiene le procedure ad alto livello per accedere alle informazioni
 *                  su eeprom
 *
 *************************************************************************************/

#ifndef _CLKTSEeprom_H
#define _CLKTSEeprom_H

#include "eeprom.h"

// EEPROM MAP
// Address Bits		Description
// ======= ======== =======================================
// 243     -------0	ScreenSaverEnabled
//         ------1- DaylightSavingTime
//         --5432-- FirstTime (1111 = true (0x0F), 1010 (0x0A) = false)
//         76------ <Not used>
// 244     ----3210	ScreenSaverMinutes
//         7654---- Language
// 245     76543210 DesktopBoxInfo
// 246     -6543210 RFMChannel
//         7------- <Not used>
// 248     76543210 ControlLCD
// 249     76543210 ControlLCD
// 250     76543210 ControlLCD
// 251     76543210 ControlLCD
// 252     76543210 ControlLCD
// 253     76543210 Device ID (low)
// 254     76543210 Device ID (high)

// Eeprom address
enum CLKTSEepromAddress
{
	CLKTSEepromAddress_KTSData1		= 243,
	CLKTSEepromAddress_KTSData2		= 244,
	CLKTSEepromAddress_KTSData3		= 245,
	CLKTSEepromAddress_KTSData4		= 246,
	CLKTSEepromAddress_ControlLCD1	= 248,
	CLKTSEepromAddress_ControlLCD2	= 249,
	CLKTSEepromAddress_ControlLCD3	= 250,
	CLKTSEepromAddress_ControlLCD4	= 251,
	CLKTSEepromAddress_ControlLCD5	= 252,
	CLKTSEepromAddress_DeviceID1	= 253,
	CLKTSEepromAddress_DeviceID2	= 254
};

// =============================================================================
// CLKTSEeprom [class]
// =============================================================================
// Description: Accesso ai dati nella eeprom
// -----------------------------------------------------------------------------
class _PACK CLKTSEeprom
{
	public: CLKTSEeprom();

	public: void ReadEeprom();
	private: void WriteAddress( int address );

	// ScreenSaver
	private: byte m_ScreensaverEnabled;
	private: byte m_ScreensaverMinutes;

	public: void SetScreensaver( bool enabled, byte minutes );
	public: bool GetScreensaverEnabled();
	public: byte GetScreensaverMinutes();

	public: void ReadEeprom_ScreenSaver();

	// Language
	private: byte m_Language;

	public: void SetLanguage( byte value );
	public: byte GetLanguage();

	public: void ReadEeprom_Language();

	// DaylightSavingTime
	private: byte m_DaylightSavingTime;
	public: void SetDaylightSavingTime( bool value );
	public: bool GetDaylightSavingTime();

	public: void ReadEeprom_DaylightSavingTime();

	// DesktopBoxInfo
	private: byte m_DesktopBoxInfo;
	public: void SetDesktopBoxInfo( byte value );
	public: byte GetDesktopBoxInfo();

	public: void ReadEeprom_DesktopBoxInfo();

	// RFMChannel
	private: byte m_RFMChannel;
	public: void SetRFMChannel( byte value );
	public: byte GetRFMChannel();

	public: void ReadEeprom_RFMChannel();

	// FirstTime
	private: byte m_FirstTime;
	public: void SetFirstTime( bool value );
	public: bool GetFirstTime();

	// Device ID
	private: unsigned short m_DeviceID;
	public: void SetDeviceID( unsigned short value );
	public: unsigned short GetDeviceID();

	public: void ReadEeprom_DeviceID();

	public: void ReadEeprom_FirstTime();

	public: static void Reset();
};
// -----------------------------------------------------------------------------
// CLKTSEeprom [class]
// =============================================================================

#endif


