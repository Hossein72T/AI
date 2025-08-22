/* 
 * File:   sheduler.h
 * Author: Maurizio Colmone
 *
 * Created on 29 luglio 2013, 8.14
 */

#ifndef _SHEDULER_H
#define	_SHEDULER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_PROCESS_RUN  10   // numero massimo di processi in corso

typedef int (*CallBack_FUNC)();

//--- Definizione struttura dello sheduler
typedef struct {
   unsigned int  enable;
   unsigned int  countdown_0s1;
   unsigned int  value_timer_0s1;
   CallBack_FUNC call_function;  // puntatore alla funzione
}S_SHEDULER;

extern S_SHEDULER  sSheduler[MAX_PROCESS_RUN]; // massimo 8 processi


//---- proto  ---
extern void init_sheduler();
extern void process_sheduler();
extern int  insert_function_sheduler(CallBack_FUNC name_func, unsigned int sample);


#ifdef	__cplusplus
}
#endif

#endif	/* _SHEDULER_H */
