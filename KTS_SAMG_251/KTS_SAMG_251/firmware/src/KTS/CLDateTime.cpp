#include "CLDateTime.h"
#include "CLKTS.h"

byte CLDate_DayPerMonth[ 12 ] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int CLDate_mArr[ 12 ] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

// =============================================================================
// CLDateTime [class]
// -----------------------------------------------------------------------------
CLDateTime::CLDateTime()
{
	Set( 1, 1, 0, 0, 0, 0 );
}

CLDateTime::CLDateTime( const CLDateTime& dateTime )
{
	Set( dateTime );
}

CLDateTime::CLDateTime( byte day, byte month, unsigned short year )
{
	SetDate( day, month, year );
	SetTime( (byte) 0, (byte) 0, (byte) 0 );
}

CLDateTime::CLDateTime( byte day, byte month, unsigned short year,
	byte hour, byte minute, byte second )
{
	Set( day, month, year, hour, minute, second );
}

//CLDateTime::CLDateTime( byte hour, byte minute, byte second )
//{
//	Set( hour, minute, second );
//}

byte CLDateTime::GetDay()
{
	return m_Day;
}

void CLDateTime::SetDay( byte value )
{
	SetDate( value, m_Month, m_Year );
}

byte CLDateTime::GetMonth()
{
	return m_Month;
}

void CLDateTime::SetMonth( byte value )
{
	SetDate( m_Day, value, m_Year );
}

unsigned short CLDateTime::GetYear()
{
	return m_Year;
}

void CLDateTime::SetYear( unsigned short value )
{
	SetDate( m_Day, m_Month, value );
}

byte CLDateTime::GetHour()
{
	return m_Hour;
}

void CLDateTime::SetHour( byte value )
{
	SetTime( value, m_Minute, m_Second );
}

byte CLDateTime::GetMinute()
{
	return m_Minute;
}

void CLDateTime::SetMinute( byte value )
{
	SetTime( m_Hour, value, m_Second );
}

byte CLDateTime::GetSecond()
{
	return m_Second;
}

void CLDateTime::SetSecond( byte value )
{
	SetTime( m_Hour, m_Minute, value );
}

void CLDateTime::Set( const CLDateTime& dateTime )
{
	m_Day		= dateTime.m_Day;
	m_Month		= dateTime.m_Month;
	m_Year		= dateTime.m_Year;
	m_Hour		= dateTime.m_Hour;
	m_Minute	= dateTime.m_Minute;
	m_Second	= dateTime.m_Second;
}

void CLDateTime::SetDate( byte day, byte month, unsigned short year )
{
	if (day < 1)
		day	= 1;
	else
	if (day > 31)
		day	= 31;

	if (month < 1)
		month	= 1;
	else
	if (month > 12)
		month	= 12;

	if (month == 2)
	{
		if (year % 4)
		{
			if (day > 28)
				day	= 28;
		}
		else
		{
			if (day > 29)
				day	= 29;
		}
	}
	else
	{
		if (day > CLDate_DayPerMonth[ month - 1 ])
			day	= CLDate_DayPerMonth[ month - 1 ];
	}

	m_Day	= day;
	m_Month	= month;
	m_Year	= year;
}

void CLDateTime::Set( byte day, byte month, unsigned short year,
	byte hour, byte minute, byte second )
{
	SetDate( day, month, year );
	SetTime( hour, minute, second );
}

void CLDateTime::SetTime( byte hour, byte minute, byte second )
{
	if (hour < 0)
		hour	= 0;
	else
	if (hour > 23)
		hour	= 23;

	if (minute < 0)
		minute	= 0;
	else
	if (minute > 59)
		minute	= 59;

	if (second < 0)
		second	= 0;
	else
	if (second > 59)
		second	= 59;

	m_Hour		= hour;
	m_Minute	= minute;
	m_Second	= second;
}

bool CLDateTime::IsLeapYear( short year )
{
	if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)))
		return true;
	return false;
}

byte CLDateTime::GetDaysOfMonth( short year, byte month )
{
	if (month == 2)
		return (IsLeapYear( year ) ? 29 : 28);

	return CLDate_DayPerMonth[ month - 1 ];
}

CLDateTime CLDateTime::GetNow()
{
	CLDateTime	dateTime;
	
	//gRTC.getDate();
	//gRTC.getTime();
	dateTime.Set( gRTC.getDay(), gRTC.getMonth(), (unsigned short) (gRTC.getCentury() == 0 ? 2000 : 1900) + gRTC.getYear(),
		gRTC.getHour(), gRTC.getMinute(), gRTC.getSecond() );

	return dateTime;
}

byte CLDateTime::GetDayOfWeek()
{
	return GetDayOfWeek( m_Day, m_Month, m_Year );
}

byte CLDateTime::GetDayOfWeek( byte day, byte month, unsigned short year )
{
	int week;

	week	= (year % 100);
	week	= week * 1.25;
	week	+= day;
	week	+= CLDate_mArr[ month - 1 ];

	if (((year % 4) == 0) && (month < 3))
		week	-= 1;
	
	while (week > 7)
		week	-= 7;

	if (week == 7)
		week	= 0;

	return (byte) week;
}
unsigned long CLDateTime::GetTotalSeconds()
{
	unsigned long	totalDays	= 0;

	// Years
	for (short yearsCounter = 0; yearsCounter < m_Year - 1; yearsCounter++)
		totalDays	+= (IsLeapYear( yearsCounter ) ? 366 : 365);

	// Months
	for (int monthsCounter = 1; monthsCounter < m_Month; monthsCounter++)
		totalDays	+= GetDaysOfMonth( m_Year, monthsCounter );

	// Days
	totalDays	+= m_Day;

	// Total Seconds
	return (totalDays * 86400UL) +  (m_Hour * 3600UL) + (m_Minute * 60UL) + m_Second;
}

CLDateTime& CLDateTime::operator=( const CLDateTime& dateTime )
{
	Set( dateTime );
	return *this;
}

bool CLDateTime::operator==( const CLDateTime& dateTime ) const
{
	return (dateTime.m_Hour == m_Hour && dateTime.m_Minute == m_Minute && dateTime.m_Second == m_Second &&
		dateTime.m_Day == m_Day && dateTime.m_Month == m_Month && dateTime.m_Year == m_Year);
}

bool CLDateTime::operator!=( const CLDateTime& dateTime ) const
{
	return (dateTime.m_Hour != m_Hour || dateTime.m_Minute != m_Minute || dateTime.m_Second != m_Second ||
		dateTime.m_Day != m_Day || dateTime.m_Month != m_Month || dateTime.m_Year != m_Year);
}

bool CLDateTime::operator>( const CLDateTime& dateTime ) const
{
	if (m_Year > dateTime.m_Year)
		return true;
	if (m_Year < dateTime.m_Year)
		return false;
	if (m_Month > dateTime.m_Month)
		return true;
	if (m_Month < dateTime.m_Month)
		return false;
	if (m_Day > dateTime.m_Day)
		return true;
	if (m_Day < dateTime.m_Day)
		return false;
	if (m_Hour > dateTime.m_Hour)
		return true;
	if (m_Hour < dateTime.m_Hour)
		return false;
	if (m_Minute > dateTime.m_Minute)
		return true;
	if (m_Minute < dateTime.m_Minute)
		return false;
	if (m_Second > dateTime.m_Second)
		return true;
	return false;
}

bool CLDateTime::operator<( const CLDateTime& dateTime ) const
{
	if (m_Year < dateTime.m_Year)
		return true;
	if (m_Year > dateTime.m_Year)
		return false;
	if (m_Month < dateTime.m_Month)
		return true;
	if (m_Month > dateTime.m_Month)
		return false;
	if (m_Day < dateTime.m_Day)
		return true;
	if (m_Day > dateTime.m_Day)
		return false;
	if (m_Hour < dateTime.m_Hour)
		return true;
	if (m_Hour > dateTime.m_Hour)
		return false;
	if (m_Minute < dateTime.m_Minute)
		return true;
	if (m_Minute > dateTime.m_Minute)
		return false;
	if (m_Second < dateTime.m_Second)
		return true;
	return false;
}

bool CLDateTime::operator>=( const CLDateTime& dateTime ) const
{
	if (m_Year >= dateTime.m_Year)
		return true;
	if (m_Year < dateTime.m_Year)
		return false;
	if (m_Month >= dateTime.m_Month)
		return true;
	if (m_Month < dateTime.m_Month)
		return false;
	if (m_Day >= dateTime.m_Day)
		return true;
	if (m_Day < dateTime.m_Day)
		return false;
	if (m_Hour >= dateTime.m_Hour)
		return true;
	if (m_Hour < dateTime.m_Hour)
		return false;
	if (m_Minute >= dateTime.m_Minute)
		return true;
	if (m_Minute < dateTime.m_Minute)
		return false;
	if (m_Second >= dateTime.m_Second)
		return true;
	return false;
}

bool CLDateTime::operator<=( const CLDateTime& dateTime ) const
{
	if (m_Year <= dateTime.m_Year)
		return true;
	if (m_Year > dateTime.m_Year)
		return false;
	if (m_Month <= dateTime.m_Month)
		return true;
	if (m_Month > dateTime.m_Month)
		return false;
	if (m_Day <= dateTime.m_Day)
		return true;
	if (m_Day > dateTime.m_Day)
		return false;
	if (m_Hour <= dateTime.m_Hour)
		return true;
	if (m_Hour > dateTime.m_Hour)
		return false;
	if (m_Minute <= dateTime.m_Minute)
		return true;
	if (m_Minute <= dateTime.m_Minute)
		return false;
	if (m_Second > dateTime.m_Second)
		return true;
	return false;
}
// -----------------------------------------------------------------------------
// CLDateTime [class]
// =============================================================================

