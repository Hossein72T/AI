/*********************************************************************
 *
 * FileName:        uart_driver.c
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

#include "uart_driver.h"
#include "main.h"
#include <stdbool.h>

#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)


//======================================================
BYTE U1_buffRX[128];
BYTE count_U1RX = 0;
BYTE U2_buffRX[128];
BYTE count_U2RX = 0;

uint8_t rcvd = 0;

extern UART_HandleTypeDef huart1;
extern volatile bool Data_transmited;

unsigned int countDownEndU1RX = COUNTDOWN_UARTRX_DISABLE;
unsigned int countDownEndU2RX = COUNTDOWN_UARTRX_DISABLE;

void initUart()
{
    HAL_UART_Receive_IT(&huart1, &rcvd, 1);
}

//======================================================
// Invia una stringa di caratteri
//======================================================
void UART_WriteBuffer( unsigned char *pbuff, int len)
{
		
		HAL_UART_Transmit_IT(&huart1, pbuff, len);
	
    while(!Data_transmited)
        ;
		Data_transmited = false;
}


//======================================================
// UART 1 interrupt handler, set at priority level 3
//======================================================
void IntUart1Handler(void)
{

    // RX interrupt
		U1_buffRX[count_U1RX] = rcvd;
		count_U1RX++;
		count_U1RX &= 0x7F;
		
		rcvd = 0;
		HAL_UART_Receive_IT(&huart1, &rcvd, 1);
	
		// ricarichiamo il contatore, alla scadenza andiamo ad analizzare il messaggio
		countDownEndU1RX = COUNTDOWN_LOAD_VALUE;

}


//======================================================
// UART 2 interrupt handler, set at priority level 3
//======================================================
/*void IntUart2Handler(void)
{
    int i;

    asm ("ei");

    // RX interrupt
    if(INTGetFlag(INT_SOURCE_UART_RX(UART2)))
    {
        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(UART2));
        for(i=0; i <128; i++) {
            if (UARTReceivedDataIsAvailable(UART2))
            {
                U2_buffRX[count_U2RX] = UARTGetDataByte(UART2);
                count_U2RX++;
                count_U2RX &= 0x7F;
            }else
                break;
        }

        // ricarichiamo il contatore, alla scadenza andiamo ad analizzare il messaggio 
        countDownEndU2RX = COUNTDOWN_LOAD_VALUE;
      
    }

    // We don't care about TX interrupt
    if (INTGetFlag(INT_SOURCE_UART_TX(UART2)))
    {
        INTClearFlag(INT_SOURCE_UART_TX(UART2));
    }
}
*/

/*********
 * E O F
 *********/
