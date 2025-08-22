/******************************************************************************
 * File:   scheduler.c
 * Author: Maurizio C.
 *
 * Created on 27 luglio 2013, 14.18
 *
 * Il seguente file, è stato creato per poter gestire tutte quelle funzioni
 * che necessitano di girare a cadenza temporale regolare.
 * Utilizzando la funzione "insert_function_sheduler(.. , ..)"
 * è possibile abbinare un timer ad una funzione.
 * 
 * Ci sono due possibilità di funzionamento:
 *   1: Ciclo infinito di chiamate (full-time).
 *   2: Singola volta, scaduto il tempo la funzione non viene + richiamata (single-time).
 *
 *
 ******************************************************************************/

#include "sheduler.h"
#include "stdio.h"
#include "main.h"

//--- Numero massimo di processi che facciamo girare è 8 -----------------------
S_SHEDULER  sSheduler[MAX_PROCESS_RUN];
extern TIM_HandleTypeDef htim3;

/*-------------------------------------------------*
 * Function:
 *  init_scheduler
 *
 * Description:
 *  - Viene inizializzato il timer_1 COMPARE 100ms
 *    (Si ricorda che il timer_2 è impegnato per i PWM.)
 *  - viene inizializzato lo scheduler
 *-------------------------------------------------*/
void init_scheduler()
{
    int i;

    for(i=0; i < MAX_PROCESS_RUN; i++) {
       sSheduler[i].enable = 0;
       sSheduler[i].call_function   = NULL;
       sSheduler[i].countdown_0s1   = 0;
       sSheduler[i].value_timer_0s1 = 0;
    }

    HAL_TIM_Base_Start_IT(&htim3);

}

/*-------------------------------------------------*
 * Function:
 *  _T1Interrupt
 *
 * Description:
 *  L'interrupt si attiva ogni 100ms
 * 
 *-------------------------------------------------*/
// Configure the Timer 1 interrupt handler
void Timer3Handler(void)
{
    int i;

    for(i=0; i<MAX_PROCESS_RUN; i++)  {
        if(sSheduler[i].enable && sSheduler[i].countdown_0s1)
            sSheduler[i].countdown_0s1--;
    }
 
}



/*-------------------------------------------------*
 * Function:
 *  insert_function_sheduler
 *
 * Description:
 *  Inserisce una funzione nello schedulatore e
 *  un tempo, che allo scadere processa la funzione
 *  (mini kernel)
 *
 *-------------------------------------------------*/
int insert_function_sheduler(CallBack_FUNC name_func, unsigned int sample)
{
    int i, ret =-1;

    for(i=0; i < MAX_PROCESS_RUN; i++) {
        if(sSheduler[i].enable == 0)
        {
            sSheduler[i].enable = 1;
            sSheduler[i].call_function   = name_func;
            sSheduler[i].countdown_0s1   = sample;
            sSheduler[i].value_timer_0s1 = sample;
            ret = 0; // ok c'è spazio.
            break;
        }

    }

    return ret;
}


/*-------------------------------------------------*
 * Function:
 *  process_sheduler
 *
 * Description:
 *
 *
 *-------------------------------------------------*/
void process_sheduler()
{
    int i;
    int getvalue;

    for(i=0; i < MAX_PROCESS_RUN; i++) {
        if(sSheduler[i].enable && (sSheduler[i].countdown_0s1 == 0))
        {
            getvalue = (*sSheduler[i].call_function)();
            // se getvalue != 0 ricarico il timer per un altro giro.
            if(getvalue){
                sSheduler[i].countdown_0s1  =  sSheduler[i].value_timer_0s1;
            }else {
                //altrimenti cancello la funzione dallo SCHEDULER
                sSheduler[i].call_function = NULL;
                sSheduler[i].enable  = 0;
            }
        }
    }
}


/*** E O F ***/
