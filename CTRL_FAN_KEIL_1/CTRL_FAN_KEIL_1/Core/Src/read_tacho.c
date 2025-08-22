/*********************************************************************
 *
 * FileName:        read_tacho.c
 *
 * Processor:       
 *
 * Complier:        
 *                 
 *
 * Author/DATE:     Maurizio Colmone (dic. 2013)
 *
 * Company:         CLIMALOMBARDA
 *
 ********************************************************************/

#include "data.h"
#include "main.h"

//----------------------------------------------------------------------
#define PERIOD_T2  0xFFFF


//--------------------- Variabili Globali ---------------------------------------
BYTE iTacho = 0;      // index Motors R Pulse selct:  0=Tacho_R1, 1=Tacho_R2, 2=Tacho_R3
                      // index Motors F Pulse selct:  0=Tacho_F1, 1=Tacho_F2, 2=Tacho_F3

BYTE upgradeValueTachoR = 0, upgradeValueTachoF = 0;

volatile int nSampleTacho_R = 0;
volatile int nSampleTacho_F = 0;

int countdown_change_iTacho = 0;

unsigned long tmr2_Start_TachoF[3] = {0,0,0};
unsigned long tmr2_TachoF[3]       = {0,0,0};
unsigned long tmr2_Start_TachoR[3] = {0,0,0};
unsigned long tmr2_TachoR[3]       = {0,0,0};

unsigned long tmr2_INT1 = 0;
unsigned long tmr2_INT2 = 0;

unsigned int  cnt_overflow_T2 = 0;        // conta gli overflow del timer 2, in modo da gestire 32 bit. per gli ICP
unsigned int  min_time_readTH = 50;

BYTE EnabMuxTacho = 1;

extern TIM_HandleTypeDef htim2;

extern int ReadTimer2 ( void );

//===================================================
// Disabilita il multiplexer CD74HC153M
//===================================================
void EnableMuxTacho ()
{  
    EnabMuxTacho = 1;
    HAL_GPIO_WritePin(Enab_2Y_Port, Enab_2Y, GPIO_PIN_RESET);    //!ENAB_2Y = 0
    HAL_GPIO_WritePin(Enab_1Y_Port, Enab_1Y, GPIO_PIN_RESET);    //!ENAB_1Y = 0
}

//===================================================
// Abilita il multiplexer CD74HC153M
//===================================================
void DisableMuxTacho ()
{
    int i=0;

    if(EnabMuxTacho)  {
        EnabMuxTacho = 0;
        HAL_GPIO_WritePin(Enab_2Y_Port, Enab_2Y, GPIO_PIN_SET);    //!ENAB_2Y = 1
        HAL_GPIO_WritePin(Enab_1Y_Port, Enab_1Y, GPIO_PIN_SET);    //!ENAB_1Y = 1

        for(i=0; i < 3; i++) {
            sdata.rpmMotorsR[i] = 0;
            sdata.rpmMotorsF[i] = 0;
        }

        nSampleTacho_F = 0;
        nSampleTacho_R = 0;
        upgradeValueTachoR = 0;
        upgradeValueTachoF = 0;
        cnt_overflow_T2 = 0;
    }
}

//======================================================
// Inizailizza i Moduli di IC1 & IC2
//  - Capture Every falling edge
//  - Interrupt on 1 Capture
//  - Use Timer 2 source
//  - Capture Falling Edge First
//
// Note: A causa dell'ultilizzo del timer 3 per i PWM,
//       e non potendo ritardare il clock del ICP, occorre
//       utilizzare il timer 2 in lettura e contando gli
//       overflow per gestire i 32 bit.
//======================================================
void init_ReadTacho()
{

    // Abilita i canali MUX1 & MUX2 e inizia con i canali 1C0 , 2C0.
    HAL_GPIO_WritePin(Sel_A_Port, Sel_A, GPIO_PIN_RESET);     //   SEL_A = 0
    HAL_GPIO_WritePin(Sel_B_Port, Sel_B, GPIO_PIN_RESET);     //   SEL_B = 0
    EnableMuxTacho ();

    iTacho = 0;
    countdown_change_iTacho = 0;

		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 3);
	  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
		HAL_TIM_Base_Start_IT(&htim2);

}

//======================================================
// Timer 2 interrupt handler, overflow  1.6777 sec.
//======================================================
void Timer2Handler(void)
{
    
    cnt_overflow_T2++;

}

//======================================================
// INT2: read  Tacho_R#
//=======================================================
void INT2InterruptHandler(void)
{
    unsigned int readT2;
    unsigned long tmr2;


    readT2 = ReadTimer2();

    tmr2  = (unsigned long)(cnt_overflow_T2 << 16) & 0xFFFF0000;
    tmr2 |= readT2;

    // overflow : 17592 sec. :4h53'
    if(nSampleTacho_R == 0)
        tmr2_Start_TachoR[iTacho] = tmr2;
    else if (nSampleTacho_R == 5)
        tmr2_TachoR[iTacho] = tmr2;

    // filtro software
    if((tmr2 - tmr2_INT2) > min_time_readTH)
        nSampleTacho_R++;

    tmr2_INT2 = tmr2;

}


//======================================================
// INT2: read  Tacho_F#
//======================================================
void INT1InterruptHandler(void)
{
    unsigned int readT2;
    unsigned long tmr2;

    readT2 = ReadTimer2(); // leggiamo i tick del timer 2

    tmr2  = (unsigned long)(cnt_overflow_T2 << 16) & 0xFFFF0000;
    tmr2 |= readT2;

    // overflow : 17592 sec. :4h53'
    if(nSampleTacho_F == 0)
        tmr2_Start_TachoF[iTacho] = tmr2;
    else if (nSampleTacho_F == 5)
        tmr2_TachoF[iTacho] = tmr2;

     // filtro software
    if((tmr2 - tmr2_INT1) > min_time_readTH)
        nSampleTacho_F++;

    tmr2_INT1 = tmr2;

}



//======================================================
// Gestione tacho dei motori, la funzione gira sotto
// scheduler ogni 0,2 sec
//======================================================
int managementTacho()
{
    BYTE numMotors_xRamo;
    unsigned long temp32;
    unsigned long time_nPulse =0;
    unsigned long quoziente   =0;

    // se i motori non hanno il comando esci dalla funzione.
    if(!EnabMuxTacho) 
        return 1;
    
    if(sdata.numPulse_xround == 0)
        sdata.numPulse_xround = 1;

    min_time_readTH = 200 / sdata.numPulse_xround;

    // ---- Read  motors Return ----
    if (nSampleTacho_R > 5)
    {
        // 1 Tick Timer23 = 0,256 * 10E-6 sec.
        // RPM = 60 / (nTick * 25,60 * 10E-6 sec)
        // da cui  60/ (25,6 * 10E-6)  si ha  2343750.
        if (tmr2_TachoR[iTacho] > tmr2_Start_TachoR[iTacho])
        {
            time_nPulse = tmr2_TachoR[iTacho] - tmr2_Start_TachoR[iTacho];
            quoziente   = 2343750L * 5;

            temp32 = quoziente / (time_nPulse * sdata.numPulse_xround);

            if(temp32 > 9999)
                temp32 = 9999;

            sdata.rpmMotorsR[iTacho] = (unsigned int)temp32;
            upgradeValueTachoR = 1;
        }else
            nSampleTacho_R = 0; // in caso di OVF
    }

    // ---- Read motors Fresh ----
    if (nSampleTacho_F > 5)
    {   // 1 Tick Timer23 = 0,256 * 10E-6 sec.
        // RPM = 60 / (nTick * 25,60 * 10E-6 sec)
        // da cui   60/ (25,6 * 10E-6) si ha  2343750.
        if (tmr2_TachoF[iTacho] > tmr2_Start_TachoF[iTacho])
        {
            time_nPulse = tmr2_TachoF[iTacho] - tmr2_Start_TachoF[iTacho];
            quoziente   = 2343750L * 5;

            temp32 = quoziente / (time_nPulse * sdata.numPulse_xround);

            if(temp32 > 9999)
                temp32 = 9999;

            sdata.rpmMotorsF[iTacho] = (unsigned int)temp32;
            upgradeValueTachoF = 1;
        }else
            nSampleTacho_F = 0;  // in caso di OVF
    }

    // ogni 2.2 sec., se vi sono altri motori sui rami, cambia indice
    countdown_change_iTacho++; 

    // Se dopo 2 secondi non c'è stato un IntCap#, oppure tutte e 2 ci sono stati,
    // vado comunque a campionare un'altro motore (se presente)
    if ((countdown_change_iTacho > 12) || (upgradeValueTachoF && upgradeValueTachoR))
    {
        countdown_change_iTacho = 0;

        // se non vi è stato neanche un interrupt rpm = 0
        if(!upgradeValueTachoR)
            sdata.rpmMotorsR[iTacho] = 0;

        if(!upgradeValueTachoF)
            sdata.rpmMotorsF[iTacho] = 0;
       
        nSampleTacho_F        = 0;
        nSampleTacho_R        = 0;
        upgradeValueTachoF    = 0;
        upgradeValueTachoR    = 0;

        numMotors_xRamo = (sdata.numMotorsUnit >> 1); // 1, 2, o 3

        if(numMotors_xRamo > 1)
        {
            iTacho++;

            if(iTacho >= numMotors_xRamo) 
                iTacho = 0;
            //------  Configurazione mux (CD74HC153M) -----------
            //      C#   |  SEl_B(RA10)| SEL_A(RA7)  |
            //  ---------+-------------+-------------+
            //      C0         0              0
            //      C1         0              1
            //      C2         1              0
            //      C3         1              1
            switch(iTacho) {
                case 0: // Motors R1 e F1
										HAL_GPIO_WritePin(Sel_A_Port, Sel_A, GPIO_PIN_RESET);     //   SEL_A = 0
										HAL_GPIO_WritePin(Sel_B_Port, Sel_B, GPIO_PIN_RESET);     //   SEL_B = 0
                break;

                case 1:  // Motors R2 e F2
										HAL_GPIO_WritePin(Sel_A_Port, Sel_A, GPIO_PIN_SET);     //   SEL_A = 1
										HAL_GPIO_WritePin(Sel_B_Port, Sel_B, GPIO_PIN_RESET);   //   SEL_B = 0
                break;

                case 2:  // Motors R3 e F3
										HAL_GPIO_WritePin(Sel_A_Port, Sel_A, GPIO_PIN_RESET);     //   SEL_A = 0
										HAL_GPIO_WritePin(Sel_B_Port, Sel_B, GPIO_PIN_SET);        //  SEL_B = 1
                break;              
            }

						HAL_GPIO_WritePin(Enab_2Y_Port, Enab_2Y, GPIO_PIN_RESET);    //!ENAB_2Y = 0
						HAL_GPIO_WritePin(Enab_1Y_Port, Enab_1Y, GPIO_PIN_RESET);    //!ENAB_1Y = 0
        }                  
    }

    
    return 1;  // teniamo la funzione viva
}




/*********
 * E O F
 *********/
