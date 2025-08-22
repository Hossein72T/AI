#ifndef __CLDateTime_h
#define __CLDateTime_h

#include "CLCommon.h"

// =============================================================================
// CLDateTime [class]
// =============================================================================
// Description: Classe data
// -----------------------------------------------------------------------------
class _PACK CLDateTime
{
	public: CLDateTime();
	public: CLDateTime( const CLDateTime& dateTime );
	public: CLDateTime( byte day, byte month, unsigned short year );
	public: CLDateTime( byte day, byte month, unsigned short year,
		byte hour, byte minute, byte second = 0);

	private: byte m_Day;
	public: byte GetDay();
	public: void SetDay( byte value );

	private: byte m_Month;
	public: byte GetMonth();
	public: void SetMonth( byte value );

	private: unsigned short m_Year;
	public: unsigned short GetYear();
	public: void SetYear( unsigned short value );

	private: byte m_Hour;
	public: byte GetHour();
	public: void SetHour( byte value );

	private: byte m_Minute;
	public: byte GetMinute();
	public: void SetMinute( byte value );

	private: byte m_Second;
	public: byte GetSecond();
	public: void SetSecond( byte value );

	public: void Set( const CLDateTime& dateTime );
	public: void Set( byte day, byte month, unsigned short year,
		byte hour, byte minute, byte second = 0 );
	public: void SetDate( byte day, byte month, unsigned short year );
	public: void SetTime( byte hour, byte minute, byte second = 0 );

	public: byte GetDayOfWeek();
	public: static byte GetDayOfWeek( byte day, byte month, unsigned short year );

	public: unsigned long GetTotalSeconds();

	public: static CLDateTime GetNow();
	public: static bool IsLeapYear( short year );
	public: static byte GetDaysOfMonth( short year, byte month );

	CLDateTime& operator=( const CLDateTime& dateTime );
	bool operator==( const CLDateTime& dateTime ) const;
	bool operator!=( const CLDateTime& dateTime ) const;
	bool operator>( const CLDateTime& dateTime ) const;
	bool operator<( const CLDateTime& dateTime ) const;
	bool operator>=( const CLDateTime& dateTime ) const;
	bool operator<=( const CLDateTime& dateTime ) const;
};
// -----------------------------------------------------------------------------
// CLDateTime [class]
// =============================================================================

#endif

