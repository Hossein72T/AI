/*********************************************************************
 *
 * FileName:        events_tacho.c
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 *
 * Author/DATE:     Maurizio Colmone (dic. 2013)
 *
 * Company:         CLIMALOMBARDA
 *
 ********************************************************************/

#include "data.h"
#include "main.h"

//----------------------------------------------------------
#define PERSIST_CONNECT    8  //  6 * 0.8 sec. =  4,8 sec.
#define PERSIST_NO_PWR    36  // 36 * 0.8 sec. = 29,0 sec.
#define PERSIST_NO_TACHO  20  // 20 * 0.8 sec. = 16,0 sec.

//----------------------------------------------------------
BYTE persist_connect_motors_R[3] = {6,6,6};
BYTE persist_connect_motors_F[3] = {6,6,6};
BYTE persist_no_rpmR[3] = {0,0,0};
BYTE persist_no_rpmF[3] = {0,0,0};
BYTE persist_err_vout_speed[2] = {0,0};

BYTE startup_monitor = 0;

extern IWDG_HandleTypeDef hiwdg;

//==========================================================
//    Test Motors (sample 0,8 sec):
//  1: If 10V = Power on
//  2: If 10V but RPM < 50 = Alarm on
//
// StatusMotors#: 
//  7.---, 6.AlmM#3, 5.AlmM#2, 4.AmM#1, 3.Err_VoutSpeed, 2.PwrM#3, 1.PwrM#2, 0.PwrM#1
//                
//
//==========================================================
int test_motors()
{
    int i, nMotors_xRamo, lim_inf, lim_sup;
    unsigned int portB = 0, portC =0;
    char ReadMotorR[3] = {0, 0, 0};
    char ReadMotorF[3] = {0, 0, 0};

    

#if defined (_FW_DEMO_)
    int temp;

    ClearWDT(); // service the WDT
		HAL_IWDG_Refresh(&hiwdg);

    nMotors_xRamo = (sdata.numMotorsUnit >> 1);
    ReadMotorR[0] = 0;
    ReadMotorF[0] = 0;
    for(i=0; i < 3; i++) // massimo 3 motori per ramo
    {
        if(i <= nMotors_xRamo)
        {
            //-------- Motori ramo RETURN --------
            ReadMotorR[0] |= (1 << i); // PWR ON
            temp = sdata.SetSpeedMotorsR;
            if(temp)
               temp += i;
            sdata.rpmMotorsR[i] = (temp * 9);
             //-------- Motori ramo FRESH --------
            ReadMotorF[0] |= (1 << i); // PWR ON
            temp = sdata.SetSpeedMotorsF;
            sdata.rpmMotorsF[i] = (temp * 9);
        }else {
            sdata.rpmMotorsR[i] = 0;
            sdata.rpmMotorsF[i] = 0;
        }
    }
    sdata.StatusMotorsR = ReadMotorR[0];
    sdata.StatusMotorsF = ReadMotorF[0];
#else

    //ClearWDT(); // service the WDT
		HAL_IWDG_Refresh(&hiwdg);

    if((sdata.SetSpeedMotorsR < 60) && (sdata.SetSpeedMotorsF < 60) && (startup_monitor >= PERSIST_NO_PWR))
    {
         // siamo in condizione di Off, Non monitoriamo i motori
        sdata.StatusMotorsR &= ~0x08;
        sdata.StatusMotorsF &= ~0x08;
        for(i=0; i < 3; i++) {
            persist_no_rpmR[i] = 0;
            persist_no_rpmF[i] = 0;
        }
        return 1;
    }else {
        // allo start-up monitoriamo i motori per 8 secondi, questo per dare una segnalazione corretta
        if (startup_monitor <= PERSIST_NO_PWR)
            startup_monitor++;

        // Verifichiamo che l'uscita del segnale di comando dei motori è proporzionale
        // al comando dato dal modulo RD.
        //   sdata.SpeedMotorsR_x100V: 1000 = 10.00V
        //   sdata.SetSpeedMotorsR   : da 0 a 255
        i = sdata.SetSpeedMotorsR * 4;  // 255 = 10.20 V
        lim_inf = sdata.SpeedMotorsR_x100V  - (4 + (sdata.SetSpeedMotorsR / 3));  // lim_inf = sdata.SpeedMotorsR_x100V  - (4 + (sdata.SetSpeedMotorsR / 6)); La serie 8 sembra fuori tolleranza ?!? aumento il range Nicola 26/04/2016
        lim_sup = sdata.SpeedMotorsR_x100V  + (4 + (sdata.SetSpeedMotorsR / 3));  // lim_inf = sdata.SpeedMotorsR_x100V  - (4 + (sdata.SetSpeedMotorsR / 5)); La serie 8 sembra fuori tolleranza ?!? aumento il range Nicola 26/04/2016
        if((i > lim_sup) || (i < lim_inf)) {
            if(persist_err_vout_speed[0] < 12)
                persist_err_vout_speed[0]++;
            else
                sdata.StatusMotorsR |= 0x08; // 16 secondi
        }else {
            persist_err_vout_speed[0] = 0;
            sdata.StatusMotorsR &= ~0x08;
        }

        i = sdata.SetSpeedMotorsF * 4;  // 255 = 10.20 V
        lim_inf = sdata.SpeedMotorsF_x100V  - (4 + (sdata.SetSpeedMotorsF / 3)); // lim_inf = sdata.SpeedMotorsF_x100V  - (4 + (sdata.SetSpeedMotorsF / 6)); La serie 8 sembra fuori tolleranza ?!? aumento il range Nicola 26/04/2016
        lim_sup = sdata.SpeedMotorsF_x100V  + (4 + (sdata.SetSpeedMotorsF / 3)); // lim_sup = sdata.SpeedMotorsF_x100V  + (4 + (sdata.SetSpeedMotorsF / 5)); La serie 8 sembra fuori tolleranza ?!? aumento il range Nicola 26/04/2016
        if((i > lim_sup) || (i < lim_inf)) {
             if(persist_err_vout_speed[1] < 12)
                persist_err_vout_speed[1]++;
            else
                sdata.StatusMotorsF |= 0x08;  // 16 secondi
        }else {
            persist_err_vout_speed[1] = 0;
            sdata.StatusMotorsF &= ~0x08;
        }
    }

    /********* Gestione connessione al Power *********/
		
		if ( HAL_GPIO_ReadPin(MotorR1_10V_Port, MotorR1_10V))
			ReadMotorR[0] = 1; // MotorR1
		if ( HAL_GPIO_ReadPin(MotorR2_10V_Port, MotorR2_10V))
			ReadMotorR[1] = 1; // MotorR2
		if ( HAL_GPIO_ReadPin(MotorR3_10V_Port, MotorR3_10V))
			ReadMotorR[2] = 1; // MotorR3
		if ( HAL_GPIO_ReadPin(MotorF1_10V_Port, MotorF1_10V))
			ReadMotorF[0] = 1; // MotorF1
		if ( HAL_GPIO_ReadPin(MotorF2_10V_Port, MotorF2_10V))
			ReadMotorF[1] = 1; // MotorF2
		if ( HAL_GPIO_ReadPin(MotorF3_10V_Port, MotorF3_10V))
			ReadMotorF[2] = 1; // MotorF3
		
   /* // B7:PMR1, B8:PMR2, B9:PMR3,  B10:PFM2
    portB = PORTRead(IOPORT_B);
    // C6:PMF1, C8:PMF3,
    portC = PORTRead(IOPORT_C); 

    if(portB & (1 << 7))   ReadMotorR[0] = 1; // MotorR1
    if(portB & (1 << 8))   ReadMotorR[1] = 1; // MotorR2
    if(portB & (1 << 9))   ReadMotorR[2] = 1; // MotorR3
    if(portC & (1 << 6))   ReadMotorF[0] = 1; // MotorF1
    if(portB & (1 << 10))  ReadMotorF[1] = 1; // MotorF2
    if(portC & (1 << 8))   ReadMotorF[2] = 1; // MotorF3*/
    
    for(i=0; i <3; i++) {
        if(ReadMotorR[i]) {
            if(persist_connect_motors_R[i] < (PERSIST_CONNECT + 8))
                persist_connect_motors_R[i]++;         
        }else {
            if(persist_connect_motors_R[i])
                persist_connect_motors_R[i]--;
        }
        

        if(ReadMotorF[i]) {
            if(persist_connect_motors_F[i] < (PERSIST_CONNECT + 8))
                persist_connect_motors_F[i]++;
        }else {
            if(persist_connect_motors_F[i])
                persist_connect_motors_F[i]--;
        }
    }
    

    /********* Gestione Allarmi Motori Power e Tacho  *********/
    // bits: ...,[6.AlarmM#3],[5.AlarmM#2],[4.AlarmM#1],
    //       ...,[2.PowerM#3],[1.PowerM#2],[0.PowerM#1] 
    //  6, 5, 4: Il motore è configurato nell'unita', ma non ho nessuna
    //           rotazione nonostante ho una tensione di comando
    //           superiore a 1,95V.
    //           L'allarme si disattiva solo nello stato di VFans > 1,95V e
    //           se c'è rotazione
    //     
    //  2, 1, 0: Il motore è configurato nell'unita', ma non c'è il segnale
    //            di potenza (bit: 2,1,0).
    nMotors_xRamo = (sdata.numMotorsUnit >> 1);    

    for(i=0; i < 3; i++) // massimo 3 motori per ramo
    {
        if(i <= nMotors_xRamo)
        {
            //-------- Motori ramo RETURN --------
            if(persist_connect_motors_R[i] >= PERSIST_CONNECT)
                sdata.StatusMotorsR |= (1 << i); // PWR ON
            else if (persist_connect_motors_R[i] <= 1)
                sdata.StatusMotorsR &= ~(1 << i);

     
            if(sdata.SpeedMotorsR_x100V >= 195)
            {
                if(sdata.rpmMotorsR[i] < 60) {
                    if(persist_no_rpmR[i] < PERSIST_NO_TACHO)
                        persist_no_rpmR[i]++;
                    else
                        sdata.StatusMotorsR |= (0x10 << i);
                }else {
                    sdata.StatusMotorsR &= ~(0x10 << i);
                    persist_no_rpmR[i] = 0;
                }
            }

            //-------- Motori ramo FRESH --------
            if(persist_connect_motors_F[i] >= PERSIST_CONNECT)
                sdata.StatusMotorsF |= (1 << i);
            else if (persist_connect_motors_F[i] <= 1)
                sdata.StatusMotorsF &= ~(1 << i);

            if(sdata.SpeedMotorsF_x100V >= 195)
            {
                if(sdata.rpmMotorsF[i] < 60) {
                    if(persist_no_rpmF[i] < PERSIST_NO_TACHO)
                        persist_no_rpmF[i]++;
                    else
                        sdata.StatusMotorsF |= (0x10 << i);
                }else {
                    sdata.StatusMotorsF &= ~(0x10 << i);
                    persist_no_rpmF[i] = 0;
                }
            }
        }else {
            sdata.StatusMotorsR &= ~(1 << i);
            sdata.StatusMotorsR &= ~(0x10 << i);
            sdata.StatusMotorsF &= ~(1 << i);
            sdata.StatusMotorsF &= ~(0x10 << i);
        }

    }
#endif
    return 1; // tieni abilitata la funzione nello sheduler
}



//=========================================================
//         --- Gestione dei leds (sample 0.6sec.) ---
// La scheda non fa ragionamenti per pilotare i Leds, è il
// modulo RD che dice che cosa si deve accendere. Solo in caso
// di comunicazione KO, fa lampeggiare il Leds ROSSO.
//
// Descrizione dei bits della variabile  'sdata.StatusLeds'
// dopo il polling RD:
//
//  [1,0] LED 3 GIALLO (11=none, 10=ON FIXED, 01=Toggle, 00=OFF)
//  [3,2] LED 4 ROSS0  (11=none, 10=ON FIXED, 01=Toggle, 00=OFF)
//  [5,4] LED 1 VERDE  (11=none, 10=ON FIXED, 01=Toggle, 00=OFF)
//  [7,6] LED 2 VERDE  (11=none, 10=ON FIXED, 01=Toggle, 00=OFF)
//
//  PINS:  RB4:LED_1 ,RC4:LED_2 ,RC5:LED_3 , RA9:LED_4
//   
//=========================================================
int leds_admin()
{

    if(countdown_link_ko == 0) {
        // In caso di comunicazione KO
         //mPORTAToggleBits(BIT_9);        // LED_RED BLINK  : ON
			    HAL_GPIO_TogglePin(Led4_Port, Led4 );
    }else {
        countdown_link_ko--;

        // --- LED_1: GREEN ----
        //  [5,4] (11= none, 10= ON, 01=Toggle, 00 = OFF)
        if(sdata.StatusLeds &  (1 << 4))
            //mPORTBToggleBits(BIT_4);
				    HAL_GPIO_TogglePin(Led1_Port, Led1);
        else if (sdata.StatusLeds &  (1 << 5))
            //mPORTBSetBits(BIT_4);
				    HAL_GPIO_WritePin(Led1_Port, Led1, GPIO_PIN_SET);
        else
            //mPORTBClearBits(BIT_4);
				    HAL_GPIO_WritePin(Led1_Port, Led1, GPIO_PIN_RESET);

        // --- LED_2: GREEN  ----
        //  [7,6] (11= none, 10= ON, 01=Toggle, 00 = OFF)
        if(sdata.StatusLeds &  (1 << 6))
            //mPORTCToggleBits(BIT_4);
				    HAL_GPIO_TogglePin(Led2_Port, Led2 );
        else if (sdata.StatusLeds &  (1 << 7))
            //mPORTCSetBits(BIT_4);
				    HAL_GPIO_WritePin(Led2_Port, Led2, GPIO_PIN_SET);
        else
            //mPORTCClearBits(BIT_4);
				    HAL_GPIO_WritePin(Led2_Port, Led2, GPIO_PIN_RESET);

         // --- LED_3: YELLOW----
        //  [1,0] (11= none, 10= ON, 01=Toggle, 00 = OFF)
        if(sdata.StatusLeds &  0x01)
            //mPORTCToggleBits(BIT_5);
				    HAL_GPIO_TogglePin(Led3_Port, Led3 );
        else if (sdata.StatusLeds & 0x02)
            //mPORTCSetBits(BIT_5);
				    HAL_GPIO_WritePin(Led3_Port, Led3, GPIO_PIN_SET);
        else
            //mPORTCClearBits(BIT_5);
				    HAL_GPIO_WritePin(Led3_Port, Led3, GPIO_PIN_RESET);

        // --- LED_4: RED ----
        //  [3,2] (11= none, 10= ON, 01=Toggle, 00 = OFF)
        if(sdata.StatusLeds & (1 << 2))
            //mPORTAToggleBits(BIT_9);
				    HAL_GPIO_TogglePin(Led4_Port, Led4 );
        else if (sdata.StatusLeds &  (1 << 3))
            //mPORTASetBits(BIT_9);
				    HAL_GPIO_WritePin(Led4_Port, Led4, GPIO_PIN_SET);
        else
            //mPORTAClearBits(BIT_9);
				    HAL_GPIO_WritePin(Led4_Port, Led4, GPIO_PIN_RESET);
      
    }

   

    return 1; // tieni abilitata la funzione nello sheduler
}

/*********
 * E O F
 *********/
