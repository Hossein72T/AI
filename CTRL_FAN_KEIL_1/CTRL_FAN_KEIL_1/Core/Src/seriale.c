/*********************************************************************
 *
 * FileName:        seriale.c
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
#include "serial_protocol.h"
#include "data.h"

//--------------------------------------------------------------------
#define DIM_BUFF_TX     64
#define TIME_15SEC      30  // il counter gira con sample di 0.5 sec. quindi 15 sec. = 30*0,5 sec.

//--------------------------------------------------------------------
BYTE buff_tx[DIM_BUFF_TX];

int countdown_link_ko = TIME_15SEC;

//--------------------------------------------------------------------
extern void EnableMuxTacho ();
extern void DisableMuxTacho ();
extern void SetDutyCyclePwm(unsigned int valuePwmR, unsigned int valuePwmF);
extern void UART_WriteBuffer( unsigned char *pbuff, int len);

//===================================================================
// Calcola la somma del contenuto di un buffer e ritorna il complemento.
// len = .._CRC_LO  ovvero 2 byte in meno della lunghezza del messaggio
//===================================================================
unsigned int Calculate_cksum16(BYTE *pbuff, int len)
{
    int i;
    unsigned int cks16;

    for(i=0, cks16=0; i <len; i++)
        cks16 += pbuff[i];

    return ~cks16;
}

//===================================================================
// Func: FillHeadMessage
//===================================================================
void FillHeadMessagePoll()
{
    int i;
    for(i=0; i < DIM_BUFF_TX; i++)
        buff_tx[i] = 0;

     buff_tx[IHM_START_MSG_0]   = PROTO_START_MSG_0;
     buff_tx[IHM_START_MSG_1]   = PROTO_START_MSG_1;
     buff_tx[IHM_POS_CRC_LO]    = IRS_CMD_F_CRC_LO;
     buff_tx[IHM_ADDR_RECEIVER] = ADDR_RD_UNIT;
     buff_tx[IHM_TYPE_COMAND]   = COMAND_POLLING_CTRL_FAN;

}

//===================================================================
// vengono visionati tutti i messaggi che girano sulla uart 1.
// e in caso rispondi al modulo RD
//===================================================================
void messages_administrator()
{
    int len, i;
    unsigned int cks16_calc, cks_16_buff = 0;
    
    if(countDownEndU1RX == COUNTDOWN_UARTRX_DISABLE)
        return;

    if(countDownEndU1RX)
        countDownEndU1RX--;
    else {
        //--- Scaduto il tempo andiamo ad analizzare il messaggio ---
        countDownEndU1RX = COUNTDOWN_UARTRX_DISABLE;
        len = count_U1RX;
        count_U1RX = 0;

//------------------------------------------------------x_dbg
//        UART_WriteBuffer(UART2, U1_buffRX, len);
//        return;
//------------------------------------------------------x_dbg
        
        // 1. Se il messaggio non ha l'itestazione giusta scarta
        if ((U1_buffRX[IHM_START_MSG_0] != PROTO_START_MSG_0) || (U1_buffRX[IHM_START_MSG_1] != PROTO_START_MSG_1))
            return;

        // 2. Se il messaggio ha lunghezza divera, scarta
        if (U1_buffRX[IHM_POS_CRC_LO] != (len - 2))
            return;

        // 3. Se il messaggio non ha l'indirizzo del Receiver CTRL_FAN, non rispondere non è per me.
        if (U1_buffRX[IHM_ADDR_RECEIVER] != ADDR_CTRL_FAN)
            return;

        // 4. Controlla Il CKSUM, se sbagliato non rispondere.
        cks16_calc = Calculate_cksum16(&U1_buffRX[0], U1_buffRX[IHM_POS_CRC_LO]);
        i = U1_buffRX[IHM_POS_CRC_LO];
        cks_16_buff = (unsigned int)(U1_buffRX[i+1] << 8) & 0xFF00;
        cks_16_buff |= U1_buffRX[i];
        cks16_calc &= 0x0FFFF; // strano ma la vede come una U32


        if(cks16_calc != cks_16_buff)            
            return;
               

        switch(U1_buffRX[IHM_TYPE_COMAND]){
            /** richiesta di misure e stati **/
            case COMAND_POLLING_CTRL_FAN:
                countdown_link_ko = TIME_15SEC; // ricarichiamo il timer a 15 secondi

                // se sono cambiati i valori del PWM, impostiamo il nuovo comando.
                if (((unsigned int)U1_buffRX[IRQ_CMD_F_SPEED_FANS_R] != sdata.SetSpeedMotorsR) ||
                    ((unsigned int)U1_buffRX[IRQ_CMD_F_SPEED_FANS_F] != sdata.SetSpeedMotorsF)) {
                    sdata.SetSpeedMotorsR = ((unsigned int)U1_buffRX[IRQ_CMD_F_SPEED_FANS_R] & 0x00FF);
                    sdata.SetSpeedMotorsF = ((unsigned int)U1_buffRX[IRQ_CMD_F_SPEED_FANS_F] & 0x00FF);

                    SetDutyCyclePwm(sdata.SetSpeedMotorsR, sdata.SetSpeedMotorsF);

                    if((sdata.SetSpeedMotorsR > 50) || (sdata.SetSpeedMotorsF > 50))
                        EnableMuxTacho();
                    else
                        DisableMuxTacho();
                }
             
                sdata.StatusLeds      = U1_buffRX[IRQ_CMD_F_STATUS_LEDS];
                sdata.numPulse_xround = U1_buffRX[IRQ_CMD_F_NPULSE_XROUND];
                sdata.numMotorsUnit   = U1_buffRX[IRQ_CMD_F_NUM_MOTORS];

                /** Elaboriamo la Risposta da inviare al modulo RD **/
                FillHeadMessagePoll();
                buff_tx[IRS_CMD_F_STATUS_FAN_R]     = sdata.StatusMotorsR & 0x7F;
                buff_tx[IRS_CMD_F_STATUS_FAN_F]     = sdata.StatusMotorsF & 0x7F;
                buff_tx[IRS_CMD_F_FEEDBK_VOUT_R_LO] = (BYTE)(sdata.SpeedMotorsR_x100V & 0x0FF);
                buff_tx[IRS_CMD_F_FEEDBK_VOUT_R_HI] = (BYTE)(sdata.SpeedMotorsR_x100V >> 8);
                buff_tx[IRS_CMD_F_FEEDBK_VOUT_F_LO] = (BYTE)(sdata.SpeedMotorsF_x100V & 0x0FF);
                buff_tx[IRS_CMD_F_FEEDBK_VOUT_F_HI] = (BYTE)(sdata.SpeedMotorsF_x100V >> 8);


                buff_tx[IRS_CMD_F_RPM_FAN_R1_LO] = (BYTE)(sdata.rpmMotorsR[0] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_R1_HI] = (BYTE)(sdata.rpmMotorsR[0] >> 8);
                buff_tx[IRS_CMD_F_RPM_FAN_R2_LO] = (BYTE)(sdata.rpmMotorsR[1] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_R2_HI] = (BYTE)(sdata.rpmMotorsR[1] >> 8);
                buff_tx[IRS_CMD_F_RPM_FAN_R3_LO] = (BYTE)(sdata.rpmMotorsR[2] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_R3_HI] = (BYTE)(sdata.rpmMotorsR[2] >> 8);

                buff_tx[IRS_CMD_F_RPM_FAN_F1_LO] = (BYTE)(sdata.rpmMotorsF[0] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_F1_HI] = (BYTE)(sdata.rpmMotorsF[0] >> 8);
                buff_tx[IRS_CMD_F_RPM_FAN_F2_LO] = (BYTE)(sdata.rpmMotorsF[1] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_F2_HI] = (BYTE)(sdata.rpmMotorsF[1] >> 8);
                buff_tx[IRS_CMD_F_RPM_FAN_F3_LO] = (BYTE)(sdata.rpmMotorsF[2] & 0x0FF);
                buff_tx[IRS_CMD_F_RPM_FAN_F3_HI] = (BYTE)(sdata.rpmMotorsF[2] >> 8);

                // versione FW 1,... Cifra + significativa
                buff_tx[IRS_CMD_F_RPM_VERSION_FW_H] = versionCode[1];
                buff_tx[IRS_CMD_F_RPM_VERSION_FW_L] = versionCode[0];

                len = IRS_CMD_F_CRC_LO;
                cks16_calc = Calculate_cksum16(&buff_tx[0], len);

                buff_tx[IRS_CMD_F_CRC_LO] = (BYTE)(cks16_calc & 0x0FF);
                buff_tx[IRS_CMD_F_CRC_HI] = (BYTE)(cks16_calc >> 8);


                UART_WriteBuffer( &buff_tx[0], (len + 2));
            break;

        }
    }
}
