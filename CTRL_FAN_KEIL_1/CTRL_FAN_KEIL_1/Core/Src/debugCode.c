/****************************************************************************

 File decicato al debug del codice con l'ausilio della seconda seriale

 ***************************************************************************/
#include <data.h>
#include <serial_protocol.h>

#ifdef _DEBUG_CODE

//------------------------------------------------
static BYTE speed[2] = {0, 0};
static int var_debug = 0;
static BYTE  sts_led = 0;

//------------------------------------------------
extern unsigned int Calculate_cksum16(BYTE *pbuff, int len);


//------------------------------------------------
// Stampa dati di debug
//------------------------------------------------
int PrintDebug()
{
    UINT8  buf[100];
    UINT8  pwrM[3];
    int len;

   
    len = sprintf(buf, "\r\nDEBUG ON:  nMotors:%d\r\n", sdata.numMotorsUnit);
    UART_WriteBuffer(UART2, buf, len);

    for(len=0; len < 250; len++) asm("nop");
    
    pwrM[0] = (sdata.StatusMotorsR &0x01);
    pwrM[1] = (sdata.StatusMotorsR >> 1) & 0x01;
    pwrM[2] = (sdata.StatusMotorsR >> 2) & 0x01;

    len = sprintf(buf, "Pwr->R1:%d  R2:%d  R3:%d\r\n", pwrM[0], pwrM[1], pwrM[2]);
    UART_WriteBuffer(UART2, buf, len);

    for(len=0; len < 250; len++) asm("nop");

    //------------------- CHECK TACHO ------------------------
    len = sprintf(buf, "RPM->R1:%d  R2:%d  R3:%d\r\n\n", sdata.rpmMotorsR[0], sdata.rpmMotorsR[1], sdata.rpmMotorsR[2]);
    UART_WriteBuffer(UART2, buf, len);

    pwrM[0] = (sdata.StatusMotorsF &0x01);
    pwrM[1] = (sdata.StatusMotorsF >> 1) & 0x01;
    pwrM[2] = (sdata.StatusMotorsF >> 2) & 0x01;
    len = sprintf(buf, "Pwr->F1:%d  F2:%d  F3:%d\r\n", pwrM[0], pwrM[1], pwrM[2]);
    UART_WriteBuffer(UART2, buf, len);

    for(len=0; len < 250; len++) asm("nop");
     //------------------- CHECK TACHO ------------------------
    len = sprintf(buf, "RPM->F1:%d  F2:%d  F3:%d\r\n", sdata.rpmMotorsF[0], sdata.rpmMotorsF[1], sdata.rpmMotorsF[2]);
    UART_WriteBuffer(UART2, buf, len);


    for(len=0; len < 250; len++) asm("nop");

    //------------------- CHECK  ADC ------------------------
    len = sprintf(buf, "10V_R:%2.2f  10V_F:%2.2f\r\n", (float)sdata.SpeedMotorsR_x100V/100,
                                                       (float)sdata.SpeedMotorsF_x100V/100);
    UART_WriteBuffer(UART2, buf, len);


    return 1; // tieni abilitata la funzione nello sheduler
}


#endif
