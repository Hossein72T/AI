/*********************************************************************
 *
 * FileName:        pwm.c
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
 * 
 *
 ********************************************************************/


#include "data.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern uint16_t Tim1_Pwm_Load;

void SetDutyCyclePwm(unsigned int valuePwmR, unsigned int valuePwmF);
extern void Set_TIM1_Duty_Cycle_Channel1 ( unsigned int duty );
extern void Set_TIM1_Duty_Cycle_Channel2 ( unsigned int duty );

// Period needed for timer 3 to generated freq_PWM ~ 2.2KHZ
// FreqPWM = (10MHz PBCLK / (16 * PERIOD_T3) = KHz
// #define PERIOD_T3   2268 // 280

//======================================================
// Configura i 2 outputCompare come PWM
//======================================================
void initPwm(void)
{
    
	//SetDutyCyclePwm(400, 400 );
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);  
}

//======================================================
//  Cambia i duty dei due comandi ai motori.
//  Il duty_max sarà 90%. per avere 10.0V in uscita ai motori.
//
//      value_PWM | %_PWM | out_10V
//    ------------+-------+------------
//          0       0.0%    0.00V
//         52      18.4%    2.06V
//        101      35.7%    4.00V
//        202      71.4%    8.00V
//        255      90.1%   10.10V
//
//======================================================
void SetDutyCyclePwm(unsigned int valuePwmR, unsigned int valuePwmF)
{
     /*if(valuePwmR > 255)
         valuePwmR = 255;
     if(valuePwmF > 255)
         valuePwmF = 255;*/
    
		valuePwmR = valuePwmR * 8;
	  valuePwmF = valuePwmF * 8;
	
    if(valuePwmR > 2043)
         valuePwmR = 2043;
     if(valuePwmF > 2043)
         valuePwmF = 2043;

     //SetDCOC4PWM(valuePwmR);
     //SetDCOC5PWM(valuePwmF);
		 Set_TIM1_Duty_Cycle_Channel1 ( valuePwmR );
		 Set_TIM1_Duty_Cycle_Channel2 ( valuePwmF );
}

/********
 * E O F
 ********/
