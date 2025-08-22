/*********************************************************************
 *
 * FileName:        adc_driver.c
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
#include <stdbool.h>
#include "main.h"

//------------------------------------------------------------------------------
unsigned int    AverageResultADC[2] = {0, 0};
unsigned int    new_convertion  = 0;
unsigned long   AccResultADC[2] = {0, 0};
unsigned int    sample = 0;

unsigned int value_speed_F = 0; // channel1
unsigned int value_speed_R = 0; // channel2

extern volatile bool ADC1_Conversion_Complete;
extern ADC_HandleTypeDef hadc1;

// indice degli array AverageResultADC[], AccResultADC[]..
#define IDX_V_SPEED_F         0
#define IDX_V_SPEED_R   			1

void initAdc()
 {
    HAL_ADCEx_InjectedStart_IT(&hadc1);
 }
 
void Adc_result()
 {
   unsigned int offset;	// Buffer offset to point to the base of the idle buffer
   int i;

   if(ADC1_Conversion_Complete)
   {
				value_speed_F =  HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1);
		    value_speed_R =   HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_2);
		    value_speed_F = ( 1023 * value_speed_F ) / 4095;
		    value_speed_R = ( 1023 * value_speed_R ) / 4095;
		 
        
        AccResultADC[IDX_V_SPEED_F] += value_speed_F;
		    AccResultADC[IDX_V_SPEED_R] += value_speed_R;

        sample += 1;

        if(sample >= 128) {
            AverageResultADC[IDX_V_SPEED_F] =  AccResultADC[IDX_V_SPEED_F] >> 7;
            AverageResultADC[IDX_V_SPEED_R] =  AccResultADC[IDX_V_SPEED_R] >> 7;

            AccResultADC[IDX_V_SPEED_F] >>= 4;
            AccResultADC[IDX_V_SPEED_R] >>= 4;
            sample >>= 4;

            // Fondo scala 11.00V,  quindi per visualizzare x100V occorre:
            sdata.SpeedMotorsR_x100V = (unsigned long)((unsigned long)AverageResultADC[IDX_V_SPEED_R] * 14) / 13;
            sdata.SpeedMotorsF_x100V = (unsigned long)((unsigned long)AverageResultADC[IDX_V_SPEED_F] * 14) / 13;

        }
        ADC1_Conversion_Complete = false;
				HAL_ADCEx_InjectedStart_IT(&hadc1);
    }
}


 
 

 /**********
  * E O F 
  **********/
