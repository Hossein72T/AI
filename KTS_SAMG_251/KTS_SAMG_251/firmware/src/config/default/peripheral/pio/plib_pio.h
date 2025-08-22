/*******************************************************************************
  PIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_pio.h

  Summary:
    PIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (PIO) module.

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

#ifndef PLIB_PIO_H
#define PLIB_PIO_H

#include "device.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for INT1 pin ***/
#define INT1_Set()               (PIOB_REGS->PIO_SODR = (1<<12))
#define INT1_Clear()             (PIOB_REGS->PIO_CODR = (1<<12))
#define INT1_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<12))
#define INT1_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<12))
#define INT1_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<12))
#define INT1_Get()               ((PIOB_REGS->PIO_PDSR >> 12) & 0x1)
#define INT1_PIN                  PIO_PIN_PB12
#define INT1_InterruptEnable()   (PIOB_REGS->PIO_IER = (1<<12))
#define INT1_InterruptDisable()  (PIOB_REGS->PIO_IDR = (1<<12))

/*** Macros for RXD_WIFI pin ***/
#define RXD_WIFI_Get()               ((PIOA_REGS->PIO_PDSR >> 4) & 0x1)
#define RXD_WIFI_PIN                  PIO_PIN_PA4

/*** Macros for TXD_WIFI pin ***/
#define TXD_WIFI_Get()               ((PIOA_REGS->PIO_PDSR >> 3) & 0x1)
#define TXD_WIFI_PIN                  PIO_PIN_PA3

/*** Macros for LED_PROG pin ***/
#define LED_PROG_Set()               (PIOA_REGS->PIO_SODR = (1<<0))
#define LED_PROG_Clear()             (PIOA_REGS->PIO_CODR = (1<<0))
#define LED_PROG_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<0))
#define LED_PROG_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<0))
#define LED_PROG_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<0))
#define LED_PROG_Get()               ((PIOA_REGS->PIO_PDSR >> 0) & 0x1)
#define LED_PROG_PIN                  PIO_PIN_PA0

/*** Macros for DB0 pin ***/
#define DB0_Set()               (PIOA_REGS->PIO_SODR = (1<<1))
#define DB0_Clear()             (PIOA_REGS->PIO_CODR = (1<<1))
#define DB0_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<1))
#define DB0_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<1))
#define DB0_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<1))
#define DB0_Get()               ((PIOA_REGS->PIO_PDSR >> 1) & 0x1)
#define DB0_PIN                  PIO_PIN_PA1

/*** Macros for MISO_RFM pin ***/
#define MISO_RFM_Get()               ((PIOA_REGS->PIO_PDSR >> 5) & 0x1)
#define MISO_RFM_PIN                  PIO_PIN_PA5

/*** Macros for DB1 pin ***/
#define DB1_Set()               (PIOA_REGS->PIO_SODR = (1<<7))
#define DB1_Clear()             (PIOA_REGS->PIO_CODR = (1<<7))
#define DB1_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<7))
#define DB1_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<7))
#define DB1_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<7))
#define DB1_Get()               ((PIOA_REGS->PIO_PDSR >> 7) & 0x1)
#define DB1_PIN                  PIO_PIN_PA7

/*** Macros for NFC_INT pin ***/
#define NFC_INT_Set()               (PIOA_REGS->PIO_SODR = (1<<8))
#define NFC_INT_Clear()             (PIOA_REGS->PIO_CODR = (1<<8))
#define NFC_INT_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<8))
#define NFC_INT_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<8))
#define NFC_INT_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<8))
#define NFC_INT_Get()               ((PIOA_REGS->PIO_PDSR >> 8) & 0x1)
#define NFC_INT_PIN                  PIO_PIN_PA8
#define NFC_INT_InterruptEnable()   (PIOA_REGS->PIO_IER = (1<<8))
#define NFC_INT_InterruptDisable()  (PIOA_REGS->PIO_IDR = (1<<8))

/*** Macros for DB2 pin ***/
#define DB2_Set()               (PIOB_REGS->PIO_SODR = (1<<15))
#define DB2_Clear()             (PIOB_REGS->PIO_CODR = (1<<15))
#define DB2_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<15))
#define DB2_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<15))
#define DB2_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<15))
#define DB2_Get()               ((PIOB_REGS->PIO_PDSR >> 15) & 0x1)
#define DB2_PIN                  PIO_PIN_PB15

/*** Macros for DB3 pin ***/
#define DB3_Set()               (PIOB_REGS->PIO_SODR = (1<<14))
#define DB3_Clear()             (PIOB_REGS->PIO_CODR = (1<<14))
#define DB3_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<14))
#define DB3_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<14))
#define DB3_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<14))
#define DB3_Get()               ((PIOB_REGS->PIO_PDSR >> 14) & 0x1)
#define DB3_PIN                  PIO_PIN_PB14

/*** Macros for DB4 pin ***/
#define DB4_Set()               (PIOA_REGS->PIO_SODR = (1<<31))
#define DB4_Clear()             (PIOA_REGS->PIO_CODR = (1<<31))
#define DB4_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<31))
#define DB4_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<31))
#define DB4_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<31))
#define DB4_Get()               ((PIOA_REGS->PIO_PDSR >> 31) & 0x1)
#define DB4_PIN                  PIO_PIN_PA31

/*** Macros for MOSI_RFM pin ***/
#define MOSI_RFM_Get()               ((PIOA_REGS->PIO_PDSR >> 6) & 0x1)
#define MOSI_RFM_PIN                  PIO_PIN_PA6

/*** Macros for CSN_RFM pin ***/
#define CSN_RFM_Set()               (PIOA_REGS->PIO_SODR = (1<<16))
#define CSN_RFM_Clear()             (PIOA_REGS->PIO_CODR = (1<<16))
#define CSN_RFM_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<16))
#define CSN_RFM_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<16))
#define CSN_RFM_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<16))
#define CSN_RFM_Get()               ((PIOA_REGS->PIO_PDSR >> 16) & 0x1)
#define CSN_RFM_PIN                  PIO_PIN_PA16

/*** Macros for DB5 pin ***/
#define DB5_Set()               (PIOA_REGS->PIO_SODR = (1<<30))
#define DB5_Clear()             (PIOA_REGS->PIO_CODR = (1<<30))
#define DB5_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<30))
#define DB5_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<30))
#define DB5_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<30))
#define DB5_Get()               ((PIOA_REGS->PIO_PDSR >> 30) & 0x1)
#define DB5_PIN                  PIO_PIN_PA30

/*** Macros for DB6 pin ***/
#define DB6_Set()               (PIOA_REGS->PIO_SODR = (1<<29))
#define DB6_Clear()             (PIOA_REGS->PIO_CODR = (1<<29))
#define DB6_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<29))
#define DB6_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<29))
#define DB6_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<29))
#define DB6_Get()               ((PIOA_REGS->PIO_PDSR >> 29) & 0x1)
#define DB6_PIN                  PIO_PIN_PA29

/*** Macros for DB7 pin ***/
#define DB7_Set()               (PIOA_REGS->PIO_SODR = (1<<28))
#define DB7_Clear()             (PIOA_REGS->PIO_CODR = (1<<28))
#define DB7_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<28))
#define DB7_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<28))
#define DB7_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<28))
#define DB7_Get()               ((PIOA_REGS->PIO_PDSR >> 28) & 0x1)
#define DB7_PIN                  PIO_PIN_PA28

/*** Macros for SCK_RFM pin ***/
#define SCK_RFM_Get()               ((PIOA_REGS->PIO_PDSR >> 15) & 0x1)
#define SCK_RFM_PIN                  PIO_PIN_PA15

/*** Macros for LUX pin ***/
#define LUX_Set()               (PIOA_REGS->PIO_SODR = (1<<23))
#define LUX_Clear()             (PIOA_REGS->PIO_CODR = (1<<23))
#define LUX_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<23))
#define LUX_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<23))
#define LUX_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<23))
#define LUX_Get()               ((PIOA_REGS->PIO_PDSR >> 23) & 0x1)
#define LUX_PIN                  PIO_PIN_PA23

/*** Macros for USB_DP pin ***/
#define USB_DP_Get()               ((PIOA_REGS->PIO_PDSR >> 22) & 0x1)
#define USB_DP_PIN                  PIO_PIN_PA22

/*** Macros for USB_DM pin ***/
#define USB_DM_Get()               ((PIOA_REGS->PIO_PDSR >> 21) & 0x1)
#define USB_DM_PIN                  PIO_PIN_PA21

/*** Macros for Y_P_YU pin ***/
#define Y_P_YU_Get()               ((PIOA_REGS->PIO_PDSR >> 17) & 0x1)
#define Y_P_YU_PIN                  PIO_PIN_PA17
#define Y_P_YU_Set()               (PIOA_REGS->PIO_SODR = (1<<17))
#define Y_P_YU_Clear()             (PIOA_REGS->PIO_CODR = (1<<17))
#define Y_P_YU_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<17))
#define Y_P_YU_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<17))

/*** Macros for X_N_XL pin ***/
#define X_N_XL_Get()               ((PIOA_REGS->PIO_PDSR >> 18) & 0x1)
#define X_N_XL_PIN                  PIO_PIN_PA18
#define Y_P_XL_Set()               (PIOA_REGS->PIO_SODR = (1<<18))
#define Y_P_XL_Clear()             (PIOA_REGS->PIO_CODR = (1<<18))
#define Y_P_XL_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<18))
#define Y_P_XL_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<18))

/*** Macros for Y_N_YD pin ***/
#define Y_N_YD_Get()               ((PIOA_REGS->PIO_PDSR >> 19) & 0x1)
#define Y_N_YD_PIN                  PIO_PIN_PA19
#define Y_P_YD_Set()               (PIOA_REGS->PIO_SODR = (1<<19))
#define Y_P_YD_Clear()             (PIOA_REGS->PIO_CODR = (1<<19))
#define Y_P_YD_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<19))
#define Y_P_YD_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<19))

/*** Macros for X_P_XR pin ***/
#define X_P_XR_Get()               ((PIOA_REGS->PIO_PDSR >> 20) & 0x1)
#define X_P_XR_PIN                  PIO_PIN_PA20
#define Y_P_XR_Set()               (PIOA_REGS->PIO_SODR = (1<<20))
#define Y_P_XR_Clear()             (PIOA_REGS->PIO_CODR = (1<<20))
#define Y_P_XR_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<20))
#define Y_P_XR_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<20))

/*** Macros for PRESEN_VIN pin ***/
#define PRESEN_VIN_Get()               ((PIOB_REGS->PIO_PDSR >> 0) & 0x1)
#define PRESEN_VIN_PIN                  PIO_PIN_PB0

/*** Macros for SENS_TEMP pin ***/
#define SENS_TEMP_Get()               ((PIOB_REGS->PIO_PDSR >> 1) & 0x1)
#define SENS_TEMP_PIN                  PIO_PIN_PB1

/*** Macros for VBUS_5V pin ***/
#define VBUS_5V_Get()               ((PIOB_REGS->PIO_PDSR >> 2) & 0x1)
#define VBUS_5V_PIN                  PIO_PIN_PB2

/*** Macros for DB8 pin ***/
#define DB8_Set()               (PIOB_REGS->PIO_SODR = (1<<3))
#define DB8_Clear()             (PIOB_REGS->PIO_CODR = (1<<3))
#define DB8_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<3))
#define DB8_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<3))
#define DB8_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<3))
#define DB8_Get()               ((PIOB_REGS->PIO_PDSR >> 3) & 0x1)
#define DB8_PIN                  PIO_PIN_PB3

/*** Macros for DB9 pin ***/
#define DB9_Set()               (PIOA_REGS->PIO_SODR = (1<<14))
#define DB9_Clear()             (PIOA_REGS->PIO_CODR = (1<<14))
#define DB9_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<14))
#define DB9_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<14))
#define DB9_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<14))
#define DB9_Get()               ((PIOA_REGS->PIO_PDSR >> 14) & 0x1)
#define DB9_PIN                  PIO_PIN_PA14

/*** Macros for DB10 pin ***/
#define DB10_Set()               (PIOA_REGS->PIO_SODR = (1<<13))
#define DB10_Clear()             (PIOA_REGS->PIO_CODR = (1<<13))
#define DB10_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<13))
#define DB10_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<13))
#define DB10_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<13))
#define DB10_Get()               ((PIOA_REGS->PIO_PDSR >> 13) & 0x1)
#define DB10_PIN                  PIO_PIN_PA13

/*** Macros for DB11 pin ***/
#define DB11_Set()               (PIOA_REGS->PIO_SODR = (1<<12))
#define DB11_Clear()             (PIOA_REGS->PIO_CODR = (1<<12))
#define DB11_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<12))
#define DB11_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<12))
#define DB11_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<12))
#define DB11_Get()               ((PIOA_REGS->PIO_PDSR >> 12) & 0x1)
#define DB11_PIN                  PIO_PIN_PA12

/*** Macros for DB12 pin ***/
#define DB12_Set()               (PIOA_REGS->PIO_SODR = (1<<11))
#define DB12_Clear()             (PIOA_REGS->PIO_CODR = (1<<11))
#define DB12_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<11))
#define DB12_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<11))
#define DB12_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<11))
#define DB12_Get()               ((PIOA_REGS->PIO_PDSR >> 11) & 0x1)
#define DB12_PIN                  PIO_PIN_PA11

/*** Macros for SDA pin ***/
#define SDA_Get()               ((PIOB_REGS->PIO_PDSR >> 10) & 0x1)
#define SDA_PIN                  PIO_PIN_PB10

/*** Macros for SCL pin ***/
#define SCL_Get()               ((PIOB_REGS->PIO_PDSR >> 11) & 0x1)
#define SCL_PIN                  PIO_PIN_PB11

/*** Macros for TX pin ***/
#define TX_Get()               ((PIOA_REGS->PIO_PDSR >> 10) & 0x1)
#define TX_PIN                  PIO_PIN_PA10

/*** Macros for RX pin ***/
#define RX_Get()               ((PIOA_REGS->PIO_PDSR >> 9) & 0x1)
#define RX_PIN                  PIO_PIN_PA9

/*** Macros for SWO pin ***/
#define SWO_Get()               ((PIOB_REGS->PIO_PDSR >> 5) & 0x1)
#define SWO_PIN                  PIO_PIN_PB5

/*** Macros for DB13 pin ***/
#define DB13_Set()               (PIOA_REGS->PIO_SODR = (1<<27))
#define DB13_Clear()             (PIOA_REGS->PIO_CODR = (1<<27))
#define DB13_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<27))
#define DB13_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<27))
#define DB13_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<27))
#define DB13_Get()               ((PIOA_REGS->PIO_PDSR >> 27) & 0x1)
#define DB13_PIN                  PIO_PIN_PA27

/*** Macros for DB14 pin ***/
#define DB14_Set()               (PIOA_REGS->PIO_SODR = (1<<26))
#define DB14_Clear()             (PIOA_REGS->PIO_CODR = (1<<26))
#define DB14_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<26))
#define DB14_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<26))
#define DB14_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<26))
#define DB14_Get()               ((PIOA_REGS->PIO_PDSR >> 26) & 0x1)
#define DB14_PIN                  PIO_PIN_PA26

/*** Macros for SWDIO pin ***/
#define SWDIO_Get()               ((PIOB_REGS->PIO_PDSR >> 6) & 0x1)
#define SWDIO_PIN                  PIO_PIN_PB6

/*** Macros for SWDCLK pin ***/
#define SWDCLK_Get()               ((PIOB_REGS->PIO_PDSR >> 7) & 0x1)
#define SWDCLK_PIN                  PIO_PIN_PB7

/*** Macros for DB15 pin ***/
#define DB15_Set()               (PIOA_REGS->PIO_SODR = (1<<25))
#define DB15_Clear()             (PIOA_REGS->PIO_CODR = (1<<25))
#define DB15_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<25))
#define DB15_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<25))
#define DB15_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<25))
#define DB15_Get()               ((PIOA_REGS->PIO_PDSR >> 25) & 0x1)
#define DB15_PIN                  PIO_PIN_PA25

/*** Macros for CS pin ***/
#define CS_Set()               (PIOB_REGS->PIO_SODR = (1<<13))
#define CS_Clear()             (PIOB_REGS->PIO_CODR = (1<<13))
#define CS_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<13))
#define CS_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<13))
#define CS_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<13))
#define CS_Get()               ((PIOB_REGS->PIO_PDSR >> 13) & 0x1)
#define CS_PIN                  PIO_PIN_PB13

/*** Macros for RS pin ***/
#define RS_Set()               (PIOA_REGS->PIO_SODR = (1<<24))
#define RS_Clear()             (PIOA_REGS->PIO_CODR = (1<<24))
#define RS_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<24))
#define RS_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<24))
#define RS_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<24))
#define RS_Get()               ((PIOA_REGS->PIO_PDSR >> 24) & 0x1)
#define RS_PIN                  PIO_PIN_PA24

/*** Macros for WR pin ***/
#define WR_Set()               (PIOB_REGS->PIO_SODR = (1<<8))
#define WR_Clear()             (PIOB_REGS->PIO_CODR = (1<<8))
#define WR_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<8))
#define WR_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<8))
#define WR_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<8))
#define WR_Get()               ((PIOB_REGS->PIO_PDSR >> 8) & 0x1)
#define WR_PIN                  PIO_PIN_PB8

/*** Macros for RESET pin ***/
#define RESET_Set()               (PIOB_REGS->PIO_SODR = (1<<9))
#define RESET_Clear()             (PIOB_REGS->PIO_CODR = (1<<9))
#define RESET_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<9))
#define RESET_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<9))
#define RESET_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<9))
#define RESET_Get()               ((PIOB_REGS->PIO_PDSR >> 9) & 0x1)
#define RESET_PIN                  PIO_PIN_PB9

/*** Macros for CE_BME688 pin ***/
#define CE_BME688_Set()               (PIOA_REGS->PIO_SODR = (1<<2))
#define CE_BME688_Clear()             (PIOA_REGS->PIO_CODR = (1<<2))
#define CE_BME688_Toggle()            (PIOA_REGS->PIO_ODSR ^= (1<<2))
#define CE_BME688_OutputEnable()      (PIOA_REGS->PIO_OER = (1<<2))
#define CE_BME688_InputEnable()       (PIOA_REGS->PIO_ODR = (1<<2))
#define CE_BME688_Get()               ((PIOA_REGS->PIO_PDSR >> 2) & 0x1)
#define CE_BME688_PIN                  PIO_PIN_PA2

/*** Macros for WIFI_READY pin ***/
#define WIFI_READY_Set()               (PIOB_REGS->PIO_SODR = (1<<4))
#define WIFI_READY_Clear()             (PIOB_REGS->PIO_CODR = (1<<4))
#define WIFI_READY_Toggle()            (PIOB_REGS->PIO_ODSR ^= (1<<4))
#define WIFI_READY_OutputEnable()      (PIOB_REGS->PIO_OER = (1<<4))
#define WIFI_READY_InputEnable()       (PIOB_REGS->PIO_ODR = (1<<4))
#define WIFI_READY_Get()               ((PIOB_REGS->PIO_PDSR >> 4) & 0x1)
#define WIFI_READY_PIN                  PIO_PIN_PB4


// *****************************************************************************
/* PIO Port

  Summary:
    Identifies the available PIO Ports.

  Description:
    This enumeration identifies the available PIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    PIO_PORT_A = PIOA_BASE_ADDRESS,
    PIO_PORT_B = PIOB_BASE_ADDRESS,
} PIO_PORT;

// *****************************************************************************
/* PIO Port Pins

  Summary:
    Identifies the available PIO port pins.

  Description:
    This enumeration identifies the available PIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    PIO_PIN_PA0 = 0,
    PIO_PIN_PA1 = 1,
    PIO_PIN_PA2 = 2,
    PIO_PIN_PA3 = 3,
    PIO_PIN_PA4 = 4,
    PIO_PIN_PA5 = 5,
    PIO_PIN_PA6 = 6,
    PIO_PIN_PA7 = 7,
    PIO_PIN_PA8 = 8,
    PIO_PIN_PA9 = 9,
    PIO_PIN_PA10 = 10,
    PIO_PIN_PA11 = 11,
    PIO_PIN_PA12 = 12,
    PIO_PIN_PA13 = 13,
    PIO_PIN_PA14 = 14,
    PIO_PIN_PA15 = 15,
    PIO_PIN_PA16 = 16,
    PIO_PIN_PA17 = 17,
    PIO_PIN_PA18 = 18,
    PIO_PIN_PA19 = 19,
    PIO_PIN_PA20 = 20,
    PIO_PIN_PA21 = 21,
    PIO_PIN_PA22 = 22,
    PIO_PIN_PA23 = 23,
    PIO_PIN_PA24 = 24,
    PIO_PIN_PA25 = 25,
    PIO_PIN_PA26 = 26,
    PIO_PIN_PA27 = 27,
    PIO_PIN_PA28 = 28,
    PIO_PIN_PA29 = 29,
    PIO_PIN_PA30 = 30,
    PIO_PIN_PA31 = 31,
    PIO_PIN_PB0 = 32,
    PIO_PIN_PB1 = 33,
    PIO_PIN_PB2 = 34,
    PIO_PIN_PB3 = 35,
    PIO_PIN_PB4 = 36,
    PIO_PIN_PB5 = 37,
    PIO_PIN_PB6 = 38,
    PIO_PIN_PB7 = 39,
    PIO_PIN_PB8 = 40,
    PIO_PIN_PB9 = 41,
    PIO_PIN_PB10 = 42,
    PIO_PIN_PB11 = 43,
    PIO_PIN_PB12 = 44,
    PIO_PIN_PB13 = 45,
    PIO_PIN_PB14 = 46,
    PIO_PIN_PB15 = 47,

    /* This element should not be used in any of the PIO APIs.
       It will be used by other modules or application to denote that none of the PIO Pin is used */
    PIO_PIN_NONE = -1

} PIO_PIN;

typedef  void (*PIO_PIN_CALLBACK) ( PIO_PIN pin, uintptr_t context);

void PIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: PIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t PIO_PortRead(PIO_PORT port);

void PIO_PortWrite(PIO_PORT port, uint32_t mask, uint32_t value);

uint32_t PIO_PortLatchRead ( PIO_PORT port );

void PIO_PortSet(PIO_PORT port, uint32_t mask);

void PIO_PortClear(PIO_PORT port, uint32_t mask);

void PIO_PortToggle(PIO_PORT port, uint32_t mask);

void PIO_PortInputEnable(PIO_PORT port, uint32_t mask);

void PIO_PortOutputEnable(PIO_PORT port, uint32_t mask);

void PIO_PortInterruptEnable(PIO_PORT port, uint32_t mask);

void PIO_PortInterruptDisable(PIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: Local Data types and Prototypes
// *****************************************************************************
// *****************************************************************************

typedef struct {

    /* target pin */
    PIO_PIN                 pin;

    /* Callback for event on target pin*/
    PIO_PIN_CALLBACK        callback;

    /* Callback Context */
    uintptr_t               context;

} PIO_PIN_CALLBACK_OBJ;

// *****************************************************************************
// *****************************************************************************
// Section: PIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void PIO_PinWrite(PIO_PIN pin, bool value)
{
    PIO_PortWrite((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), (uint32_t)(0x1) << (pin & 0x1f), (uint32_t)(value) << (pin & 0x1f));
}

static inline bool PIO_PinRead(PIO_PIN pin)
{
    return (bool)((PIO_PortRead((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5)))) >> (pin & 0x1F)) & 0x1);
}

static inline bool PIO_PinLatchRead(PIO_PIN pin)
{
    return (bool)((PIO_PortLatchRead((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5)))) >> (pin & 0x1F)) & 0x1);
}

static inline void PIO_PinToggle(PIO_PIN pin)
{
    PIO_PortToggle((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinSet(PIO_PIN pin)
{
    PIO_PortSet((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinClear(PIO_PIN pin)
{
    PIO_PortClear((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinInputEnable(PIO_PIN pin)
{
    PIO_PortInputEnable((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinOutputEnable(PIO_PIN pin)
{
    PIO_PortOutputEnable((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinInterruptEnable(PIO_PIN pin)
{
    PIO_PortInterruptEnable((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

static inline void PIO_PinInterruptDisable(PIO_PIN pin)
{
    PIO_PortInterruptDisable((PIO_PORT)(PIOA_BASE_ADDRESS + (0x200 * (pin>>5))), 0x1 << (pin & 0x1F));
}

bool PIO_PinInterruptCallbackRegister(
    PIO_PIN pin,
    const   PIO_PIN_CALLBACK callBack,
    uintptr_t context
);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_PIO_H
