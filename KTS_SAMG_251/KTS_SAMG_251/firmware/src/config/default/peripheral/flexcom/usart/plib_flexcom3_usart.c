/*******************************************************************************
  FLEXCOM3 USART PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_flexcom3_usart.c

  Summary:
    FLEXCOM3 USART PLIB Implementation File

  Description
    This file defines the interface to the FLEXCOM3 USART
    peripheral library. This library provides access to and control of the
    associated peripheral instance.

  Remarks:
    None.
*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "plib_flexcom3_usart.h"
#include "interrupts.h"

// *****************************************************************************
// *****************************************************************************
// Section: FLEXCOM3 USART Implementation
// *****************************************************************************
// *****************************************************************************

FLEXCOM_USART_OBJECT flexcom3UsartObj;

void static FLEXCOM3_USART_ErrorClear( void )
{
    uint8_t dummyData = 0u;

    if (USART3_REGS->US_CSR & (US_CSR_OVRE_Msk | US_CSR_FRAME_Msk | US_CSR_PARE_Msk))
    {
        USART3_REGS->US_CR = US_CR_RSTSTA_Msk;

        /* Flush existing error bytes from the RX FIFO */
        while (USART3_REGS->US_CSR & US_CSR_RXRDY_Msk)
        {
            dummyData = (USART3_REGS->US_RHR & US_RHR_RXCHR_Msk);
        }
    }

    /* Ignore the warning */
    (void)dummyData;
}



void FLEXCOM3_InterruptHandler( void )
{
    /* Channel status */
    uint32_t channelStatus = USART3_REGS->US_CSR;

    USART3_REGS->US_PTCR = US_PTCR_ERRCLR_Msk;

    if ((USART3_REGS->US_PTSR & US_PTSR_RXTEN_Msk) && (channelStatus & US_CSR_ENDRX_Msk))
    {
        if(flexcom3UsartObj.rxBusyStatus == true)
        {
            flexcom3UsartObj.rxBusyStatus = false;
            USART3_REGS->US_PTCR = US_PTCR_RXTDIS_Msk;
            USART3_REGS->US_IDR = US_IDR_ENDRX_Msk;

            if( flexcom3UsartObj.rxCallback != NULL )
            {
                flexcom3UsartObj.rxCallback(flexcom3UsartObj.rxContext);
            }
        }
    }

    if ((USART3_REGS->US_PTSR & US_PTSR_TXTEN_Msk) && (channelStatus & US_CSR_ENDTX_Msk))
    {
        if(flexcom3UsartObj.txBusyStatus == true)
        {
            flexcom3UsartObj.txBusyStatus = false;
            USART3_REGS->US_PTCR = US_PTCR_TXTDIS_Msk;
            USART3_REGS->US_IDR = US_IDR_ENDTX_Msk;

            if( flexcom3UsartObj.txCallback != NULL )
            {
                flexcom3UsartObj.txCallback(flexcom3UsartObj.txContext);
            }
        }
    }
}

void FLEXCOM3_USART_Initialize( void )
{
    /* Set FLEXCOM USART operating mode */
    FLEXCOM3_REGS->FLEXCOM_MR = FLEXCOM_MR_OPMODE_USART;

    /* Reset FLEXCOM3 USART */
    USART3_REGS->US_CR = (US_CR_RSTRX_Msk | US_CR_RSTTX_Msk | US_CR_RSTSTA_Msk);

    /* Enable FLEXCOM3 USART */
    USART3_REGS->US_CR = (US_CR_TXEN_Msk | US_CR_RXEN_Msk);

    /* Configure FLEXCOM3 USART mode */
    USART3_REGS->US_MR = ((US_MR_USCLKS_MCK) | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | (1 << US_MR_OVER_Pos));

    /* Configure FLEXCOM3 USART Baud Rate */
    //USART3_REGS->US_BRGR = US_BRGR_CD(130) /*| US_BRGR_FP(1)*/;
    USART3_REGS->US_BRGR = US_BRGR_CD(120) /*| US_BRGR_FP(1)*/;

    /* Initialize instance object */
    flexcom3UsartObj.rxBuffer = NULL;
    flexcom3UsartObj.rxSize = 0;
    flexcom3UsartObj.rxProcessedSize = 0;
    flexcom3UsartObj.rxBusyStatus = false;
    flexcom3UsartObj.rxCallback = NULL;
    flexcom3UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;
    flexcom3UsartObj.txBuffer = NULL;
    flexcom3UsartObj.txSize = 0;
    flexcom3UsartObj.txProcessedSize = 0;
    flexcom3UsartObj.txBusyStatus = false;
    flexcom3UsartObj.txCallback = NULL;
}

FLEXCOM_USART_ERROR FLEXCOM3_USART_ErrorGet( void )
{
    FLEXCOM_USART_ERROR errorStatus = flexcom3UsartObj.errorStatus;

    flexcom3UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;

    /* All errors are cleared, but send the previous error state */
    return errorStatus;
}

static void FLEXCOM3_USART_BaudCalculate(uint32_t srcClkFreq, uint32_t reqBaud, uint8_t overSamp, uint32_t* cd, uint32_t* fp, uint32_t* baudError)
{
    uint32_t actualBaud = 0;

    *cd = srcClkFreq / (reqBaud * 8 * (2 - overSamp));

    if (*cd > 0)
    {
        *fp = ((srcClkFreq / (reqBaud * (2 - overSamp))) - ((*cd) * 8));
        actualBaud = (srcClkFreq / (((*cd) * 8) + (*fp))) / (2 - overSamp);
        *baudError = ((100 * actualBaud)/reqBaud) - 100;
    }
}

bool FLEXCOM3_USART_SerialSetup( FLEXCOM_USART_SERIAL_SETUP *setup, uint32_t srcClkFreq )
{
    uint32_t baud = 0;
    uint32_t overSampVal = 0;
    uint32_t usartMode;
    uint32_t cd0, fp0, cd1, fp1, baudError0, baudError1;
    bool status = false;

    cd0 = fp0 = cd1 = fp1 = baudError0 = baudError1 = 0;

    if((flexcom3UsartObj.rxBusyStatus == true) || (flexcom3UsartObj.txBusyStatus == true))
    {
        /* Transaction is in progress, so return without updating settings */
        return false;
    }

    if (setup != NULL)
    {
        baud = setup->baudRate;

        if(srcClkFreq == 0)
        {
            srcClkFreq = FLEXCOM3_USART_FrequencyGet();
        }

        /* Calculate baud register values for 8x/16x oversampling values */

        FLEXCOM3_USART_BaudCalculate(srcClkFreq, baud, 0, &cd0, &fp0, &baudError0);
        FLEXCOM3_USART_BaudCalculate(srcClkFreq, baud, 1, &cd1, &fp1, &baudError1);

        if ( !(cd0 > 0 && cd0 <= 65535) && !(cd1 > 0 && cd1 <= 65535) )
        {
            /* Requested baud cannot be generated with current clock settings */
            return status;
        }

        if ( (cd0 > 0 && cd0 <= 65535) && (cd1 > 0 && cd1 <= 65535) )
        {
            /* Requested baud can be generated with both 8x and 16x oversampling. Select the one with less % error. */
            if (baudError1 < baudError0)
            {
                cd0 = cd1;
                fp0 = fp1;
                overSampVal = (1 << US_MR_OVER_Pos) & US_MR_OVER_Msk;
            }
        }
        else
        {
            /* Requested baud can be generated with either with 8x oversampling or with 16x oversampling. Select valid one. */
            if (cd1 > 0 && cd1 <= 65535)
            {
                cd0 = cd1;
                fp0 = fp1;
                overSampVal = (1 << US_MR_OVER_Pos) & US_MR_OVER_Msk;
            }
        }

        /* Configure FLEXCOM3 USART mode */
        usartMode = USART3_REGS->US_MR;
        usartMode &= ~(US_MR_CHRL_Msk | US_MR_MODE9_Msk | US_MR_PAR_Msk | US_MR_NBSTOP_Msk | US_MR_OVER_Msk);
        USART3_REGS->US_MR = usartMode | ((uint32_t)setup->dataWidth | (uint32_t)setup->parity | (uint32_t)setup->stopBits | overSampVal);

        /* Configure FLEXCOM3 USART Baud Rate */
        USART3_REGS->US_BRGR = US_BRGR_CD(cd0) | US_BRGR_FP(fp0);
        status = true;
    }

    return status;
}

bool FLEXCOM3_USART_Read( void *buffer, const size_t size )
{
    bool status = false;
    uint8_t* pBuffer = (uint8_t*)buffer;

    if(pBuffer != NULL)
    {
        /* Check if receive request is in progress */
        if(flexcom3UsartObj.rxBusyStatus == false)
        {
            /* Clear errors that may have got generated when there was no active read request pending */
            FLEXCOM3_USART_ErrorClear();

            status = true;

            flexcom3UsartObj.rxBuffer = pBuffer;
            flexcom3UsartObj.rxSize = size;
            flexcom3UsartObj.rxProcessedSize = 0;
            flexcom3UsartObj.rxBusyStatus = true;
            flexcom3UsartObj.errorStatus = FLEXCOM_USART_ERROR_NONE;

            USART3_REGS->US_RPR = (uint32_t) buffer;
            USART3_REGS->US_RCR = (uint32_t) size;
            USART3_REGS->US_PTCR = US_PTCR_RXTEN_Msk;
            USART3_REGS->US_IER = US_IER_ENDRX_Msk;
        }
    }

    return status;
}

bool FLEXCOM3_USART_Write( void *buffer, const size_t size )
{
    bool status = false;
    uint8_t* pBuffer = (uint8_t *)buffer;

    if(pBuffer != NULL)
    {
        /* Check if transmit request is in progress */
        if(flexcom3UsartObj.txBusyStatus == false)
        {
            status = true;

            flexcom3UsartObj.txBuffer = pBuffer;
            flexcom3UsartObj.txSize = size;
            flexcom3UsartObj.txProcessedSize = 0;
            flexcom3UsartObj.txBusyStatus = true;


            USART3_REGS->US_TPR = (uint32_t) buffer;
            USART3_REGS->US_TCR = (uint32_t) size;
            USART3_REGS->US_PTCR = US_PTCR_TXTEN_Msk;
            USART3_REGS->US_IER = US_IER_ENDTX_Msk;

        }
    }

    return status;
}

void FLEXCOM3_USART_WriteCallbackRegister( FLEXCOM_USART_CALLBACK callback, uintptr_t context )
{
    flexcom3UsartObj.txCallback = callback;
    flexcom3UsartObj.txContext = context;
}

void FLEXCOM3_USART_ReadCallbackRegister( FLEXCOM_USART_CALLBACK callback, uintptr_t context )
{
    flexcom3UsartObj.rxCallback = callback;
    flexcom3UsartObj.rxContext = context;
}

bool FLEXCOM3_USART_WriteIsBusy( void )
{
    return flexcom3UsartObj.txBusyStatus;
}

bool FLEXCOM3_USART_ReadIsBusy( void )
{
    return flexcom3UsartObj.rxBusyStatus;
}

size_t FLEXCOM3_USART_WriteCountGet( void )
{
    return (flexcom3UsartObj.txSize - USART3_REGS->US_TCR);
}

size_t FLEXCOM3_USART_ReadCountGet( void )
{
    return (flexcom3UsartObj.rxSize - USART3_REGS->US_RCR);
}

bool FLEXCOM3_USART_ReadAbort(void)
{
    if (flexcom3UsartObj.rxBusyStatus == true)
    {
        /* Disable PDA channel transfer */
        USART3_REGS->US_RCR = (uint32_t) 0;
        USART3_REGS->US_PTCR = US_PTCR_RXTDIS_Msk;
        USART3_REGS->US_IDR = US_IDR_ENDRX_Msk;

        flexcom3UsartObj.rxBusyStatus = false;

        /* If required application should read the num bytes processed prior to calling the read abort API */
        flexcom3UsartObj.rxSize = flexcom3UsartObj.rxProcessedSize = 0;
    }

    return true;
}

