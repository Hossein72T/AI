#ifndef _CLIKTS

/****c*
 *  NAME
 *    Pcf8563 Real Time Clock support routines
 *  AUTHOR
 *    Joe Robertson, jmr
 *    orbitalair@bellsouth.net
 *    http://orbitalair.wikispaces.com/Arduino
 *  CREATION DATE
 *    9/24/06,  init - built off of usart demo.  using mikroC
 *  NOTES
 *  HISTORY
 *    10/14/06 ported to CCS compiler, jmr
 *    2/21/09  changed all return values to hex val and not bcd, jmr
 *    1/10/10  ported to arduino, jmr
 *    2/14/10  added 3 world date formats, jmr
 *  TODO
 *    x Add Euro date format
 *    Add short time (hh:mm) format
 *    Add 24h/12h format
 *    Add timer support
 ******
 *  Robodoc embedded documentation.
 *  http://www.xs4all.nl/~rfsber/Robo/robodoc.html
 */

#include "Rtc_Pcf8563.h"

extern volatile APP_TRANSFER_STATUS transferStatus;

Rtc_Pcf8563::Rtc_Pcf8563(void)
{
	Rtcc_Addr = RTCC_R>>1;	
}

void Rtc_Pcf8563::initClock(byte firstTime, byte language, byte screensaverON, byte screensaverMin, byte desktopBoxInfo )
{  
  byte Screensaver;
  	  
  _firstTime = firstTime & 0x07;
  
	_language = language; 
  
  //if(CLKTSType>2)
  //  _CLKTSType = 0;                    //------------------------  BASIC
  //else
  //  _CLKTSType = CLKTSType;
  
  if(screensaverMin>10 || screensaverMin==0)
    _screensaverMin = DEFAULT_SCREENSAVER_MIN;
  else
    _screensaverMin = screensaverMin;
    
  if(screensaverON>1)
    _screensaverON = DEFAULT_SCREENSAVER;
  else
    _screensaverON = screensaverON;
  
  if(_screensaverON==0)
    Screensaver = 0;
  else
    Screensaver = _screensaverMin;

  m_DesktopBoxInfo	= desktopBoxInfo;
    
  //if(centkWh>31 || centkWh==0)
  //  _centkWh= DEFAULT_CENTkWh;
  //else
  //  _centkWh = centkWh;
  
  //dinCent = _CLKTSType + ((_centkWh<<2) & 0x7C);
         
  m_DaylightSavingTime = 0;
  
  // By default  01/01/2012   00.00.00
 
  memset ( Send_Buff, 0, sizeof(Send_Buff));
  Send_Buff[6] = 1; Send_Buff[7] = 3; Send_Buff[8] = 1; Send_Buff[9] = 0x14;
  Send_Buff[10] = 0x80 + (desktopBoxInfo & 0x7f);
  Send_Buff[11] = 0x80 + (_language & 0x07);
  // ora legale Ã¨ il bit 4 di day alarm    (MSB) AE, -, -, OL, SC, SC, SC, SC (LSB)    OL=ora legale, SC=Screensaver  -->  dEFAULT zero
  Send_Buff[12] = 0x80 + (Screensaver & 0x0f);
  Send_Buff[13] = 0x80 + (_firstTime & 0x07);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 16);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

/* Private internal functions, but useful to look at if you need a similar func. */
byte Rtc_Pcf8563::decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

byte Rtc_Pcf8563::bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}


void Rtc_Pcf8563::clearStatus()
{
    
  memset ( Send_Buff, 0, sizeof(Send_Buff));
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 3);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::setTime(byte hour, byte minute, byte sec)
{
    
  Send_Buff[0] = RTCC_SEC_ADDR;
  Send_Buff[1] = decToBcd(sec);
  Send_Buff[2] = decToBcd(minute);
  Send_Buff[3] = decToBcd(hour);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 4);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::setDate(byte day, byte weekday, byte mon, byte century, byte year)
{ 
	/* year val is 00 to 99, xx
	   with the highest bit of month = century
	   0=20xx
	   1=19xx
	 */
	month = decToBcd(mon);
	if (century == 1){
		month |= RTCC_CENTURY_MASK;
	}	
	else {
		month &= ~RTCC_CENTURY_MASK;
	}
  
  Send_Buff[0] = RTCC_DAY_ADDR;
  Send_Buff[1] = decToBcd(day);
  Send_Buff[2] = decToBcd(weekday);
  Send_Buff[3] = month;
  Send_Buff[4] = decToBcd(year);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 5);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

/* set the alarm values
 * whenever the clock matches these values an int will
 * be sent out pin 3 of the Pcf8563 chip
 */
void Rtc_Pcf8563::setAlarm(byte min, byte hour, byte day, byte weekday)
{
	if (min <99) { min = decToBcd(min); min &= ~RTCC_ALARM; }
	else { min = 0x0; min |= RTCC_ALARM; }
	
	if (hour <99) { hour = decToBcd(hour); hour &= ~RTCC_ALARM; }
	else { hour = 0x0; hour |= RTCC_ALARM; }
	
	if (day <99) { day = decToBcd(day); day &= ~RTCC_ALARM; }
	else { day = 0x0; day |= RTCC_ALARM; }
	
	if (weekday <99) { weekday = decToBcd(weekday); weekday &= ~RTCC_ALARM; }
	else { weekday = 0x0; weekday |= RTCC_ALARM; }
	
	//set status2 AF val to zero 
	status2 &= ~RTCC_ALARM_AF;
	//enable the interrupt
	status2 |= RTCC_ALARM_AIE;
	
  //enable the interrupt
  
  Send_Buff[0] = RTCC_STAT2_ADDR;
  Send_Buff[1] = status2;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
  //TODO bounds check  the inputs first
  
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR;
  Send_Buff[1] = min;
  Send_Buff[2] = hour;
  Send_Buff[3] = day;
  Send_Buff[4] = weekday;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 5);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::clearAlarm()
{
	//set status2 AF val to zero to reset alarm 
  status2 &= ~RTCC_ALARM_AF;
	//turn off the interrupt
  status2 &= ~RTCC_ALARM_AIE;
		
  Send_Buff[0] = RTCC_STAT2_ADDR;
  Send_Buff[1] = status2;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::getDate()
{  
	
    ackData = RTCC_DAY_ADDR;
    transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
    FLEXCOM4_TWI_WriteRead(Rtcc_Addr, &ackData, 1,  &Send_Buff[0], 4);
    while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
    day = bcdToDec(Send_Buff[0] & 0x3f);
    weekday = bcdToDec(Send_Buff[1] & 0x07);
    month = Send_Buff[2];
    if (month & RTCC_CENTURY_MASK) {
		century = 1;
	}
	else {
		century = 0;
	}
    month = month & 0x1f;
	month = bcdToDec(month);
    year = bcdToDec(Send_Buff[3]);
    
}

void Rtc_Pcf8563::getTime()
{  

    ackData = RTCC_STAT1_ADDR;
    transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
    FLEXCOM4_TWI_WriteRead(Rtcc_Addr, &ackData, 1,  &Send_Buff[0], 5);
    while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
    status1 = Send_Buff[0];
    status2 = Send_Buff[1];
    sec = bcdToDec(Send_Buff[2] & 0x7f);
    minute = bcdToDec(Send_Buff[3] & 0x7f);
    hour = bcdToDec(Send_Buff[4] & 0x3f);
    
}



/*-------------------------- EEPROM --------------------------------  */

void Rtc_Pcf8563::getEEPROM()
{  	
	byte ScreensaverLegale;
	byte Screensaver;
	byte temp;
  
    ackData = RTCC_ALRM_MIN_ADDR;
    transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
    FLEXCOM4_TWI_WriteRead(Rtcc_Addr, &ackData, 1,  &Send_Buff[0], 4);
    while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
    m_DesktopBoxInfo	= Send_Buff[0] & 0x7f;	// contiene le info del desktop Box da visualizzare (7 bit)
    _language = (Send_Buff[1] & 0x3f);           // corrisponde a hour alarm , 6 bit totali :               [3..0]
    ScreensaverLegale = (Send_Buff[2] & 0x3f);     // corrisponde a day alarm  , 6 bit totali
    _firstTime = (Send_Buff[3] & 0x07);          // corrisponde a week alarm , 3 bit totali
    
    if(CHECK_BIT(ScreensaverLegale,4)==1)
        m_DaylightSavingTime =1;
    else
        m_DaylightSavingTime =0;
         
    Screensaver = ScreensaverLegale & 0x0f;
         
    if(Screensaver>10)
    {
        _screensaverMin = DEFAULT_SCREENSAVER_MIN;
        _screensaverON = DEFAULT_SCREENSAVER;
    }
    else if(Screensaver==0)
    {
        _screensaverMin = DEFAULT_SCREENSAVER_MIN;
        _screensaverON = 0;
    }
    else
    {
        _screensaverMin = Screensaver;
        _screensaverON = 1;
    }
}


void Rtc_Pcf8563::setFirstTime(byte firstTime)
{
  	
  _firstTime = firstTime & 0x07;
  
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR+3;
  Send_Buff[1] = 0x80 + _firstTime;
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::setLanguage(byte language)
{
	_language	= language;
  
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR+1;
  Send_Buff[1] = 0x80 + (_language & 0x07);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

void Rtc_Pcf8563::setScreensaver(byte screensaverON, byte screensaverMin)
{
  byte Screensaver;
  
  _screensaverMin = screensaverMin & 0x0f;
    
  if(screensaverON>1)
    _screensaverON = DEFAULT_SCREENSAVER;
  else
    _screensaverON = screensaverON;
  
  if(_screensaverON==0)
    Screensaver = 0;
  else
    Screensaver = _screensaverMin;
  
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR+2;
  Send_Buff[1] = 0x80 +  ((m_DaylightSavingTime<<4)&0x10) + (Screensaver & 0x0f);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}

//void Rtc_Pcf8563::setCentkWh(byte centkWh)
//{
//  byte dinCent;
//  Wire.beginTransmission(Rtcc_Addr);	// Issue I2C start signal
//  Wire.send(RTCC_ALRM_MIN_ADDR);   
//  	
//  if(centkWh>31 || centkWh==0)
//    _centkWh= DEFAULT_CENTkWh;
//  else
//    _centkWh = centkWh;
//  dinCent = _CLKTSType + ((_centkWh<<2) & 0x7C); 
//  Wire.send(0x80 + (dinCent & 0x7f)); 					
//  Wire.endTransmission(); 
//}
               
void Rtc_Pcf8563::setDesktopBoxInfo( byte value )
{
  
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR;
  Send_Buff[1] = 0x80 + (value & 0x7f);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
  m_DesktopBoxInfo	= (value & 0x7f);
} 

void Rtc_Pcf8563::setDaylightSavingTime( byte daylightSavingTime )
{
  byte Screensaver;
  
  if(_screensaverON==0)
    Screensaver = 0;
  else
    Screensaver = _screensaverMin;
    	
  if(daylightSavingTime >1)
    m_DaylightSavingTime = 1;
  else
    m_DaylightSavingTime = daylightSavingTime;
    
  Send_Buff[0] = RTCC_ALRM_MIN_ADDR+2;
  Send_Buff[1] = 0x80 + ((m_DaylightSavingTime<<4)&0x10) + (Screensaver & 0x0f);
  transferStatus = APP_TRANSFER_STATUS_IN_PROGRESS;
  FLEXCOM4_TWI_Write(Rtcc_Addr, &Send_Buff[0], 2);
  while ( transferStatus != APP_TRANSFER_STATUS_SUCCESS) { };
  
}
 
/*-------------------------- EEPROM --------------------------------  */


char *Rtc_Pcf8563::formatTime(byte style)
{
	getTime();
	switch (style) {
		case RTCC_TIME_HM:
			strOut[0] = '0' + (hour / 10);
		 	strOut[1] = '0' + (hour % 10);
		 	strOut[2] = ':';
			strOut[3] = '0' + (minute / 10);
		 	strOut[4] = '0' + (minute % 10);
		 	strOut[5] = '\0';
			break;
		case RTCC_TIME_HMS:
		default:
			strOut[0] = '0' + (hour / 10);
		 	strOut[1] = '0' + (hour % 10);
		 	strOut[2] = ':';
			strOut[3] = '0' + (minute / 10);
		 	strOut[4] = '0' + (minute % 10);
		 	strOut[5] = ':';
			strOut[6] = '0' + (sec / 10);
		 	strOut[7] = '0' + (sec % 10);
		 	strOut[8] = '\0';
 			break;
		}
 	return strOut;
}
 

char *Rtc_Pcf8563::formatDate(byte style)
{
	getDate();
	
		switch (style) {
		
		case RTCC_DATE_ASIA:
			//do the asian style, yyyy-mm-dd
			if ( century == 1 ){
			 	strDate[0] = '1';
			 	strDate[1] = '9';
		 	}
			else {
				strDate[0] = '2';
				strDate[1] = '0';
			}
			strDate[2] = '0' + (year / 10 );
		 	strDate[3] = '0' + (year % 10);
		 	strDate[4] = '-';	
			strDate[5] = '0' + (month / 10);
		 	strDate[6] = '0' + (month % 10);
		 	strDate[7] = '-';
			strDate[8] = '0' + (day / 10);
		 	strDate[9] = '0' + (day % 10);
		 	strDate[10] = '\0';
			break;
		case RTCC_DATE_US: 
	  //the pitiful US style, mm/dd/yyyy
			strDate[0] = '0' + (month / 10);
		 	strDate[1] = '0' + (month % 10);
		 	strDate[2] = '/';
			strDate[3] = '0' + (day / 10);
		 	strDate[4] = '0' + (day % 10);
		 	strDate[5] = '/';
		 	if ( century == 1 ){
			 	strDate[6] = '1';
			 	strDate[7] = '9';
		 	}
			else {
				strDate[6] = '2';
				strDate[7] = '0';
			}
			strDate[8] = '0' + (year / 10 );
		 	strDate[9] = '0' + (year % 10);
		 	strDate[10] = '\0';
		 	break;
		case RTCC_DATE_WORLD:
		default:
			//do the world style, dd-mm-yyyy
			strDate[0] = '0' + (day / 10);
		 	strDate[1] = '0' + (day % 10);
		 	strDate[2] = '-';
			strDate[3] = '0' + (month / 10);
		 	strDate[4] = '0' + (month % 10);
		 	strDate[5] = '-';
			
		 	if ( century == 1 ){
			 	strDate[6] = '1';
			 	strDate[7] = '9';
		 	}
			else {
				strDate[6] = '2';
				strDate[7] = '0';
			}
			strDate[8] = '0' + (year / 10 );
		 	strDate[9] = '0' + (year % 10);
		 	strDate[10] = '\0';
			break; 	
		
	}
 	return strDate;
}

byte Rtc_Pcf8563::getSecond() {	
	return sec;	
}

byte Rtc_Pcf8563::getMinute() {
	return minute;
}

byte Rtc_Pcf8563::getHour() {
	return hour;
}

byte Rtc_Pcf8563::getDay() {
	return day;
}

byte Rtc_Pcf8563::getMonth() {
	return month;
}

byte Rtc_Pcf8563::getYear() {
	return year;
}

byte Rtc_Pcf8563::getCentury() {
	return century;
}

byte Rtc_Pcf8563::getWeekday() {
	return weekday;
}

byte Rtc_Pcf8563::getStatus1() {
	return status1;
}

byte Rtc_Pcf8563::getStatus2() {
	return status2;
}

/*---------------- EEPROM functions ------------*/

byte Rtc_Pcf8563::getFirstTime(){
        return _firstTime;
}
                
byte Rtc_Pcf8563::getLanguage(){
        return _language;
}
                
byte Rtc_Pcf8563::getScreensaverON(){
        return _screensaverON;
}
                
byte Rtc_Pcf8563::getScreensaverMin(){
        return _screensaverMin;
}
                
//byte Rtc_Pcf8563::getCentkWh(){
//        return _centkWh;
//}
//
//byte Rtc_Pcf8563::getCLKTSType(){
//        return _CLKTSType;
//}

byte Rtc_Pcf8563::getDesktopBoxInfo()
{
	return m_DesktopBoxInfo;
}

byte Rtc_Pcf8563::getDaylightSavingTime(){
        return m_DaylightSavingTime;
}

#endif

