/****h*
 *  NAME
 *    External Real Time Clock support routines
 *  AUTHOR
 *    Joe Robertson, jmr
 *    orbitalair@bellsouth.net
 *    http://orbitalair.wikispaces.com/Arduino
 *  CREATION DATE
 *    1/2/10,  init - built off of pic gRTC code
 *  NOTES
 *  HISTORY
 *    1/2/10  ported to arduino compiler, jmr
 *    2/14/10 added 3 world date formats, jmr
 *  TODO
 *  
 ******
 *  Robodoc embedded documentation.
 *  http://www.xs4all.nl/~rfsber/Robo/robodoc.html
 */
 
#include "definitions.h"
#include <string.h>

#ifndef Rtc_Pcf8563_H
#define Rtc_Pcf8563_H


#define DEFAULT_DesktopBoxInfo	0
#define DEFAULT_SCREENSAVER		0	// Choose: ON, OFF
#define DEFAULT_SCREENSAVER_MIN	5	// Choose: 1 to 10 included (minute)


/* the read and write values for pcf8563 rtcc */
/* these are adjusted for arduino */
#define RTCC_R 	0xa3
#define RTCC_W 	0xa2

#define RTCC_SEC 			1
#define RTCC_MIN 			2
#define RTCC_HR 			3
#define RTCC_DAY 			4
#define RTCC_WEEKDAY	5
#define RTCC_MONTH 		6
#define RTCC_YEAR 		7
#define RTCC_CENTURY 	8

/* register addresses in the gRTC */
#define RTCC_STAT1_ADDR			0x0
#define RTCC_STAT2_ADDR			0x01
#define RTCC_SEC_ADDR  			0x02
#define RTCC_MIN_ADDR 			0x03
#define RTCC_HR_ADDR 			0x04
#define RTCC_DAY_ADDR 			0x05
#define RTCC_WEEKDAY_ADDR		0x06
#define RTCC_MONTH_ADDR 		0x07
#define RTCC_YEAR_ADDR 			0x08
#define RTCC_ALRM_MIN_ADDR 	    0x09

/* setting the alarm flag to 0 enables the alarm.
 * set it to 1 to disable the alarm for that value. 
 */
#define RTCC_ALARM				0x80
#define RTCC_ALARM_AIE 			0x02
#define RTCC_ALARM_AF 			0x04
/* optional val for no alarm setting */
#define RTCC_NO_ALARM			99    

#define RTCC_CENTURY_MASK 		0x80

/* date format flags */
#define RTCC_DATE_WORLD			0x01
#define RTCC_DATE_ASIA			0x02
#define RTCC_DATE_US			0x04
/* time format flags */
#define RTCC_TIME_HMS			0x01
#define RTCC_TIME_HM			0x02

#ifdef _CLIKTS
struct SEepromData
{
    byte m_FirstTime;
    byte m_Language;
    byte m_ScreensaverON;
    byte m_ScreensaverMin;
    byte m_DaylightSavingTime;
    byte m_DesktopBoxInfo;
};
#endif

/* arduino class */
class Rtc_Pcf8563 {
	public:
		Rtc_Pcf8563();

		void initClock(byte firstTime, byte language, byte screensaverON, byte screensaverMin, byte desktopBoxInfo );	/* zero out all values, disable all alarms */
		void clearStatus();	/* set both status bytes to zero */
		
		void getDate();			/* get date vals to local vars */
		void setDate(byte day, byte weekday, byte month, byte century, byte year);
		void getTime();    /* get time vars + 2 status bytes to local vars */
		void setTime(byte hour, byte minute, byte sec);

		void setFirstTime( byte firstTime );

		void setAlarm(byte min, byte hour, byte day, byte weekday); /* set alarm vals, 99=ignore */
		void clearAlarm();	/* clear alarm flag and interrupt */
		
		byte getSecond();
		byte getMinute();
		byte getHour();
		byte getDay();
		byte getMonth();
		byte getYear();
		byte getCentury();
		byte getWeekday();
		byte getStatus1();
		byte getStatus2();
  
        void getEEPROM();     /* refresh the EEPROM value */
        byte getFirstTime();
		
		/*get a output string, these call getTime/getDate for latest vals */
		char *formatTime( byte style = RTCC_TIME_HM );
		/* date supports 3 styles as listed in the wikipedia page about world date/time. */
		char *formatDate( byte style = RTCC_DATE_WORLD );

		void setDesktopBoxInfo( byte value );
        byte getDesktopBoxInfo();

        void setScreensaver(byte screensaverON, byte screensaverMin);
        byte getScreensaverON();
        byte getScreensaverMin();

		void setLanguage(byte language);
        byte getLanguage();

		void setDaylightSavingTime( byte daylightSavingTime );
        byte getDaylightSavingTime();

	private:
		char strOut[9];
		char strDate[11];
		
		int Rtcc_Addr;

#ifdef _CLIKTS
		SEepromData m_EepromData;
#else
		/* methods */
		byte decToBcd(byte value);
		byte bcdToDec(byte value);
		/* time variables */
		byte hour;
		byte minute;
		byte sec;
		byte day;
		byte weekday;
		byte month;
		byte year;
		/* support */
		byte status1;
		byte status2;
		byte century;

		/* EEPROM */
        byte _firstTime;
        byte _language;
        byte _screensaverON;
        byte _screensaverMin;
        byte m_DaylightSavingTime;
        byte m_DesktopBoxInfo;
        
        byte Send_Buff[20];
        uint8_t ackData;
#endif

};

#endif

