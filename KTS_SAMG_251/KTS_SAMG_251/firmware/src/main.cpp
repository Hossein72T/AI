/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

/************************************************************************************************
 *
 *                                    Software Touchscreen
 *
 ************************************************************************************************

 * Note: accessory supported AWP,PEHD,PHWD,EHD,HWD,CWD,RH,CO2

 * Version: 2.0

 * Date: 27/12/2012

 * Author:  Paolo Menchi

 * Hardware requirements:
    - Electronics Boards Touchscreen v 1.0 - 1.1 - 1.2 - 1.3 - 1.4 with bootloader pre-burned
    - USB cable

 * Library required:
   - TFTLCD (LCD driver HX8347-D)
   - Rtc_Pcf8563    (Real Time Clock by I2C)
   - Wire

+--------+----------+-----------+----------------------------------------------------------------+
  Author |FirmwareVersion[]|    Date   |                  Descripions
+--------+----------+-----------+----------------------------------------------------------------+
  Andrea   prova 3    ??/??/??    - sistemato comando manuale accessori
           prova 2                - ora legale automatica funzionante
+--------+----------+-----------+----------------------------------------------------------------+
  Andrea     1.4      27/12/12
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.5      22/03/13   - Aumentato il DESCRIPTOR_WEEK da 102 a 120.
            (EVO)                - Riconoscimento delle vecchie versioni MB es: 1.4 ed auto_adattamento
                                 - Inserito la funzione SUMMER e WINTER
                                 - Aggiunto direttive di compilazione per unificare i progetti
                                 - Migliorato il settaggio Weekly
                                 - Inserito la visualizzazione T_Fresh nel BOX DESTOP, tolto [Euro KW/h]
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.6      18/04/13   - Corretto piccoli difetti di visualizzazione. es: BOX DESKTOP)
                                 - Aumentato il tempo di aggancio con il KTS
                                 - Inserito versione DEMO sotto direttiva DI COMPILAZIONE
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.7      31/05/13   - Inserito le modifiche x la gestione del BAK. Ovvero poter spegnere
                        (BAK)      e config. il bypass anche da remoto.
                                   Modificate le funzioni:
                                     1. Control_panel().
                                     2. Read_Descriptor().

                      22/07/13    - Inserito PASSWORD SERVICE per NL: 88940
                                  - Corretto errore visualiz. Histeresis TEMP. < EHD_Set2() >
                      10/09/13    - Inserito Logo UE sotto direttiva di compilazione.
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.8      19/10/13    - Inseriti i testi in Francese
                                  - Inserita la 6 lingua il Portoghese
                      14/11/13    - Aumentato i tempi pdi ricerca dell'UNITA'
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.9      15/11/13    - Cambiata l'impostazione dello sbilanciamento +/- 70%

+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.10     30/11/13    - Inserite le modifiche per l'impostazione a Pressione costante
                                  - Inserito il menu di <Report Data> nel service.
+--------+----------+-----------+----------------------------------------------------------------+
  Maury      1.11                 - Inserito password dopo screenserver()
+--------+----------+-----------+----------------------------------------------------------------+

-[ 2.00 ]-+----------+-----------------------------------------------------------------------------

> Paolo     --/--/--   - Revisione totale del codice.
                       - Supporto della nuova elettronica.
                       - Persa la totale compatibità con le vecchie versioni.

-[ 2.01 ]-+----------+-----------------------------------------------------------------------------

> Paolo     11/07/14   - Eliminato il controllo sull'accessorio DPS nel caso di gestione del filtro.
                       - Icone max VOC/CO2/RH.
                       - Nel caso in cui il weekly program è attivo, non è più possibile mettere in
                         off la macchina.
                       - Risolto il problema screensaver, kts::process.
-[ 2.02 ]-+----------+-----------------------------------------------------------------------------

> Paolo     21/07/14   - Menù "Accessory Manager" --> "Disconnect Accessory"
                       - BoxInfo: CO2 Max 2000 -> 4000
                       - Menù "Temperature Config" --> "Clima Settings"
                       - In clima settings splittata la voce Heater on/off, in PreHeater e
                         PostHeater

-[ 2.03 ]-+----------+-----------------------------------------------------------------------------

> Paolo     01/08/14    - Gestione del campo di eeprom IncreaseSpeed_RH_CO2
                        - Modificato il valore di RM Min da 20 a 2
                        - Aggiunta la possibilità di entrare nel menù di service avanzato, premendo
                          per 5 secondi la voce di menù service e digitando la password di backdoor.
                        - Aggiunto in data debug IRSD_MEASURE_AIRFLOW

-[ 2.04 ]-+----------+-----------------------------------------------------------------------------

> Paolo     25/08/14   - Corretto codifica Type_func (0 = Basic, 1 = Extra)

-[ 2.05 ]-+----------+-----------------------------------------------------------------------------

> Paolo     28/08/14   - Bypass: aggiunto il campo MinTemperature nel form di config
                       - Histeresis: corretto problema dei valori passati all'rd (*10)
                       - Histeresis: è possibile impostare le temperature con delta di 0.5
                       - Histeresis: alzati i limiti -/+ in 12 gradi

-[ 2.06 ]-+----------+-----------------------------------------------------------------------------

> Paolo     03/09/14   - BoxInfo: sistemato problema nella visualizzazione del PEHD
                       - KTS: ogni 4 secondi viene fatta una richiesta di DataDebug

-[ 2.07 ]-+----------+-----------------------------------------------------------------------------

> Paolo     04/09/14   - CAP: aggiunta proprietà MaxPressure in SCLUnitModel, per determinare la
                         massima pressione a seconda del modello.
                       - Defrost: sistemato problema nel form di debug sullo stato di defrost
                       - Configurazione: aggiunta configurazione FranceAir Italia

-[ 2.08 ]-+----------+-----------------------------------------------------------------------------

> Paolo     15/09/14   - Sistemato nel form delle info la configurazione della unit
                         ('A' parte da 1 invece che da 0).

-[ 2.09 ]-+----------+-----------------------------------------------------------------------------

> Paolo     03/10/14   - Per le serie 3 la scritta dell'accessorio PEHD rimane PHED, mentre per la
                         serie 5 è IPHED

-[ 2.10 ]-+----------+-----------------------------------------------------------------------------

> Paolo     28/11/14   - Tolto il discorso di premere 5 secondi, per entrare in modalità admin.
                       - Quando il modbus è attivo, la schermata dei dati di debug non visualizza le
                         informazioni relative al CAP/CAF
-[ 2.11 ]-+----------+-----------------------------------------------------------------------------

> Paolo     24/02/15   - Integrata procedura di collaudo

-[ 2.12 ]-+----------+-----------------------------------------------------------------------------

> Paolo     30/03/2015 - Modifiche al report data (togliere i dati sensibili)
> Paolo                - Aggiungere nella configurazione admin (pwd: 02015) senso rot. bypass

-[ 2.13 ]-+----------+-----------------------------------------------------------------------------

> Paolo     07/04/2015 - Aggiunto il nuovo driver LCD per funzionare con il vecchio KTS e quello
                         nuovo
-[ 2.43 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     10/12/2024 - Added PIR strategy
 
-[ 2.44 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     23/01/2025 - CAPS-CAPR management
 
-[ 2.45 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     27/02/2025 - Added AIR SENSOR1 and AIR SENSOR2 debug information

-[ 2.47 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     13/03/2025 - Added Clean Event strategy for SENSOR board

-[ 2.48 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     29/03/2025 - changed CO2 stepless indication from ORANGE to GREY

[ 2.49 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     15/04/2025 - changed CO2 range from 600 ppm to 1500 ppm
				  - changed CO2 airflow range from 30% to 100%
				  - update MainForm and Main.cpp to solve problem of rendering when WEEKLY + PIR strategy occour.

[ 2.50 ]-+----------+-----------------------------------------------------------------------------

> Nicola / Zakaria     16/04/2025 - Merged files from version 2.48 and 2.49
*/
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <cassert>

#include "CLCommon.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLLocalitation.h"
#include "CLFonts.h"
#include "CLScreensaver.h"
#include "CLCommunicationManager.h"
#include "CLLogo.h"
#include "CLMessageBoxForm.h"
#include "CLPowerOffForm.h"
#include "CLMainForm.h"
#include "CLBoxInfo.h"
#include "CLWeekly.h"
#include "CLAccessory.h"
#include "eeprom.h"
#include "CLCommunication_Driver.h"
#include "RFM73.h"
#include "CLKTSConnectForm.h"
#include "CLFireAlarmForm.h"
#include "CLKTSStartupForm.h"

/**/

volatile APP_TRANSFER_STATUS transferStatus;
volatile bool txThresholdEventReceived = false;
volatile bool rxThresholdEventReceived = false;
volatile uint32_t nBytesRead = 0;
uint8_t rxBuffer[256];
extern _PCA9500 PCA9500;
volatile bool FLEXCOM2_Ready = false;

void APP_TWI4_Callback(uintptr_t context )
{
    APP_TRANSFER_STATUS* transferStatus1 = (APP_TRANSFER_STATUS*)context;

    if(FLEXCOM4_TWI_ErrorGet() == FLEXCOM_TWI_ERROR_NONE)
    {
        if (transferStatus1)
        {
            *transferStatus1 = APP_TRANSFER_STATUS_SUCCESS;
        }
    }
    else
    {
        if (transferStatus1)
        {
            *transferStatus1 = APP_TRANSFER_STATUS_ERROR;
        }
    }
}

void usart0_ReadEventHandler(FLEXCOM_USART_EVENT event, uintptr_t context )
{
    uint32_t nBytesAvailable = 0;
    
    if (event == FLEXCOM_USART_EVENT_READ_THRESHOLD_REACHED)
    {
        /* Receiver should atleast have the thershold number of bytes in the ring buffer */
        nBytesAvailable = FLEXCOM0_USART_ReadCountGet();
        
        nBytesRead += FLEXCOM0_USART_Read((uint8_t*)&rxBuffer[nBytesRead], nBytesAvailable);
        
        rxThresholdEventReceived = true;
    }
}

void usart0_WriteEventHandler(FLEXCOM_USART_EVENT event, uintptr_t context )
{
    txThresholdEventReceived = true;
}

void Systick_handler(uintptr_t context)
{

}

void RFM73_Spi_Callback ( uintptr_t context)
{
     FLEXCOM2_Ready = true;
}

/**/

// *****************************************************************************
//const byte PASSW_FIRST_TIME     = 5;        // Choose: 0 to 7 included

#define PASSW_NOT_FIRST_TIME	5
#define BAUDRATE				9600
int index1;
long seed1 = 0;

//******************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    SYSTICK_TimerCallbackSet(&Systick_handler, (uintptr_t) NULL);
    SYSTICK_TimerStart ( );
    
    transferStatus = APP_TRANSFER_STATUS_ERROR;
    
	/* Register the TWIHS Callback with transfer status as context */
    FLEXCOM4_TWI_CallbackRegister( APP_TWI4_Callback, (uintptr_t)&transferStatus );
    
    /* Register callback functions for UART0 */
    FLEXCOM0_USART_WriteCallbackRegister(usart0_WriteEventHandler, (uintptr_t) NULL);
    FLEXCOM0_USART_ReadCallbackRegister(usart0_ReadEventHandler, (uintptr_t) NULL);
    
    /* Let's enable notifications to get notified when the TX buffer is empty */
    FLEXCOM0_USART_WriteThresholdSet(FLEXCOM0_USART_WriteBufferSizeGet());
    /* Enable notifications */
    FLEXCOM0_USART_WriteNotificationEnable(true, false);
    
    /* set a threshold value to receive a callback after every 1 characters are received */
    FLEXCOM0_USART_ReadThresholdSet(1);
    /* Enable RX event notifications */
    FLEXCOM0_USART_ReadNotificationEnable(true, false);
    
    FLEXCOM2_SPI_CallbackRegister( RFM73_Spi_Callback, 0 );
    
    TC0_CH1_CompareStart ( );
    
    SYSTICK_DelayMs ( 500 );
    
    char type_LCD[ 4 ] = { '9','3','4','1' };
        
        //EEPROM_write_byte( 243, 0x28 );
        //EEPROM_write_byte( 244, 0x4B );
        //EEPROM_write_byte( 245, 0x3 );
        //EEPROM_write_byte( 246, 0x1 );
        //EEPROM_write_byte( 247, 0xFF );
        EEPROM_write_byte( 248, 0x39 );
        EEPROM_write_byte( 249, 0x33 );
        EEPROM_write_byte( 250, 0x34 );
        EEPROM_write_byte( 251, 0x31 );
        //EEPROM_write_byte( 252, 0x53 );
        //EEPROM_write_byte( 253, 0x2B );
        //EEPROM_write_byte( 254, 0x5A );
        
        if ( EEPROM_read_byte( 240 ) != 0x55 )
        {
          EEPROM_write_byte( 240, 0x55 );
          EEPROM_write_byte( 243, 0x28 );
          EEPROM_write_byte( 244, 0x4B );
          EEPROM_write_byte( 245, 0x3 );
          EEPROM_write_byte( 246, 0x1 );
          EEPROM_write_byte( 247, 0xFF );
          EEPROM_write_byte( 248, 0x39 );
          EEPROM_write_byte( 249, 0x33 );
          EEPROM_write_byte( 250, 0x34 );
          EEPROM_write_byte( 251, 0x31 );
          //EEPROM_write_byte( 252, 0x53 );
          EEPROM_write_byte( 253, 0x2B );
          EEPROM_write_byte( 254, 0x5A );
        }
        
	// inizialize random generator
    ADC_ChannelsEnable( ADC_CH4_MASK );
    ADC_ConversionStart( );
    while ( !ADC_ChannelResultIsReady( ADC_CH4 )) {};
    seed1 = ADC_ChannelResultGet( ADC_CH4 );
    ADC_ChannelsDisable( ADC_CH4_MASK );
        
    // EEprom Write Protect PIN
    PCA9500.WP = 1;
    PCA9500_write( PCA9500 );    
	// get all the "EEPROM" value from RTC
	gRTC.getEEPROM();

	// ------------------------------------------------
	// Controlla se è la prima volta di avvio del KTS
	// ------------------------------------------------
	gKTSEeprom.ReadEeprom_FirstTime();

	// ------------------------------------------------
	// Legge o inizializza la eeprom
	// ------------------------------------------------
        
	// Se è presente una configurazione nel RTC e non nella eeprom,   S'il y a une configuration dans le RTC et pas dans l'eeprom
	// allora copia i valori nella eeprom                             puis copiez les valeurs dans l'eeprom
	if (gKTSEeprom.GetFirstTime() && gRTC.getFirstTime() == PASSW_NOT_FIRST_TIME)
	{
		gKTSEeprom.SetDaylightSavingTime( gRTC.getDaylightSavingTime() );
		gKTSEeprom.SetLanguage( gRTC.getLanguage() );
		gKTSEeprom.SetScreensaver( gRTC.getScreensaverON(), gRTC.getScreensaverMin() );
		gKTSEeprom.SetDesktopBoxInfo( gRTC.getDesktopBoxInfo() );
		gKTSEeprom.SetRFMChannel( RFM_CHANNELS_MIN );
		gKTSEeprom.SetDeviceID( CLKTS::GenerateDeviceID() );
		gKTSEeprom.SetFirstTime( false );
		gRTC.setFirstTime( 0xFF );
	}
    
    gKTSEeprom.SetDeviceID( CLKTS::GenerateDeviceID() );
	// Non è la prima esecuzione      Ce n'est pas la première exécution
	if (!gKTSEeprom.GetFirstTime())
	{
		// Legge tutti i dati dalla eeprom
		gKTSEeprom.ReadEeprom();

		// Check dei dati, aggiusta se necessario

		// Controlla il range dello screen saver
		if (gKTSEeprom.GetScreensaverMinutes() < SCREENSAVER_MINUTES_MIN)
		{
			gKTSEeprom.SetScreensaver( gKTSEeprom.GetScreensaverEnabled(),
				SCREENSAVER_MINUTES_MIN );
		}
		else
		if (gKTSEeprom.GetScreensaverMinutes() > SCREENSAVER_MINUTES_MAX)
		{
			gKTSEeprom.SetScreensaver( gKTSEeprom.GetScreensaverEnabled(),
				SCREENSAVER_MINUTES_MAX );
		}

		// Controlla l'id della lingua
		if (gKTSEeprom.GetLanguage() >= CLLanguageId__COUNT)
			gKTSEeprom.SetLanguage( LANGUAGE_PRIMARY );

		// Controlla il range del rfm channel
		if (gKTSEeprom.GetRFMChannel() < RFM_CHANNELS_MIN)
			gKTSEeprom.SetRFMChannel( RFM_CHANNELS_MIN );
		else
		if (gKTSEeprom.GetRFMChannel() > RFM_CHANNELS_MAX)
			gKTSEeprom.SetRFMChannel( RFM_CHANNELS_MAX );
	}
	// E' la prima esecuzione    C'est la première exécution
	else   
	{
		// Imposta data e ora iniziali
		gRTC.setDate( 1, 3, 1, 1, 14 );
		gRTC.setTime( 0, 0, 0 );
		gRTC.getTime();
		gRTC.getDate();

		// Set eeprom default value.
		gKTSEeprom.SetDaylightSavingTime( false );
		gKTSEeprom.SetLanguage( LANGUAGE_PRIMARY );
		gKTSEeprom.SetScreensaver( false, SCREENSAVER_MINUTES_MIN );
		gKTSEeprom.SetDesktopBoxInfo( CLBoxInfo_InfoId_TFresh | CLBoxInfo_InfoId_TReturn );
		gKTSEeprom.SetRFMChannel( RFM_CHANNELS_MIN );
		gKTSEeprom.SetDeviceID( CLKTS::GenerateDeviceID() );
                gKTSEeprom.SetFirstTime( false );
                EEPROM_write_byte( 248, 0x39 );
                EEPROM_write_byte( 249, 0x33 );
                EEPROM_write_byte( 250, 0x34 );
                EEPROM_write_byte( 251, 0x31 );
                EEPROM_write_byte( 252, 0x53 );
	}

	// ------------------------------------------------
	// Inizializza modulo RFM
	// ------------------------------------------------
	init_port_RFM();
	RFM73_Initialize(gKTSEeprom.GetRFMChannel(), POWER_NEG_10DBM,  DATA_RATE_250KBPS); 
	sdata_wi.deviceId	= gKTSEeprom.GetDeviceID();

	// ------------------------------------------------
	// Inizializza il modulo della Seriale
	// ------------------------------------------------
	Com_Init( BAUDRATE );

    TC0_CH1_CompareASet (HIGH_BRIGHTESS);

	// DONE PROG LED, ACTIVE ONLY IN FIRST TIME ROUTINE TO SHOW THE CORRECT PROG
	LED_PROG_Clear();

	// DONE PROG LED, ACTIVE ONLY IN FIRST TIME ROUTINE TO SHOW THE CORRECT PROG
	LED_PROG_Set();

	// ------------------------------------------------
	// Inizializza LCD
	// ------------------------------------------------
	for(int i=0; i < 4; i++)
		type_LCD[ i ] = EEPROM_read_byte( CLKTSEepromAddress_ControlLCD1 + i );
  
	gLCD.InitLCD( LANDSCAPE, type_LCD );

	// Clear the screen
	gLCD.clrScr();
	gLCD.setFont( &CLBigFont, CLKTS::GetCodePage() );

	// Inizializza i dati globali
	CLKTS::Initialize();

	// DONE PROG LED, ACTIVE ONLY IN FIRST TIME ROUTINE TO SHOW THE CORRECT PROG
	if (gKTSEeprom.GetFirstTime())
    {
		LED_PROG_Set();
    }

	CLKTSStartupForm_Open();

	// DONE PROG LED, ACTIVE ONLY IN FIRST TIME ROUTINE TO SHOW THE CORRECT PROG
	if (gKTSEeprom.GetFirstTime())
	{
		LED_PROG_Clear();
		SYSTICK_DelayMs ( 500 );
	}

	CLKTS::AdjustDaylightSavingTime();
	
    CLKTS::Pir_Strategy_Counter = millis();
         
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        switch (gKTSGlobal.RunningMode)
        {
            case CLKTSRunningMode_Initializing:
                Initialize();
                break;

            case CLKTSRunningMode_Running:
                if (!gKTSEeprom.GetFirstTime())
                {
                    gKTSGlobal.FirstRunningTime	= false;
                }
                else   
                {      
                    gKTSGlobal.FirstRunningTime	= true;
                }

                CLMainForm_Open();
                break;

            case CLKTSRunningMode_FireAlarm:
                CLFireAlarmForm_Open( CLFormOption_Default );
                break;

            case CLKTSRunningMode_PowerOff:
                if (Weekly_Status_IsActive( gKTSData.Status_Weekly ) && gRDEeprom.Set_Input[ 0 ] != INP_0V_UNIT_STOP)
                    CLMainForm_Open();
                else
                    CLPowerOffForm_Open();
                break;
        }
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

long random1( long range1, long range2 )
{
	// TODO: Da rivedere
	return (range1 + rand());
}

void randomSeed( unsigned int seed )
{
	srand( seed );   // should only be called once
}

int random2( void )
{
	return rand();
}

int randint(int n) {
    
  int end;
  int r;
  
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    assert (n <= RAND_MAX);

    // Chop off all of the values that would cause skew...
    end = RAND_MAX / n; // truncate skew
    assert (end > 0);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    
    while ((r = rand()) >= end);

    return r % n;
  }
}

void Initialize()
{
	CLKTSConnectForm_Open();

	// DONE PROG LED, ACTIVE ONLY IN FIRST TIME ROUTINE TO SHOW THE CORRECT PROG
	LED_PROG_Clear();
}

void RFM73_Ready( void)
{
    while ( !FLEXCOM2_Ready ) {};
    FLEXCOM2_Ready = false;
}

/*******************************************************************************
 End of File
*/

