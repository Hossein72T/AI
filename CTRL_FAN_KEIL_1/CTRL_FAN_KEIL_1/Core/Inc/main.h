/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

#define Led1 GPIO_PIN_3
#define Led1_Port GPIOA
#define Led2 GPIO_PIN_4
#define Led2_Port GPIOA
#define Led3 GPIO_PIN_5
#define Led3_Port GPIOA
#define Led4 GPIO_PIN_12
#define Led4_Port GPIOA

#define Sel_B GPIO_PIN_10
#define Sel_B_Port GPIOB
#define Sel_A GPIO_PIN_11
#define Sel_A_Port GPIOB
#define Enab_2Y GPIO_PIN_12
#define Enab_2Y_Port GPIOB
#define Enab_1Y GPIO_PIN_13
#define Enab_1Y_Port GPIOB

#define TACHO_F_Pin GPIO_PIN_6
#define TACHO_F_GPIO_Port GPIOA
#define TACHO_R_Pin GPIO_PIN_7
#define TACHO_R_GPIO_Port GPIOA

#define MotorR1_10V GPIO_PIN_11
#define MotorR1_10V_Port GPIOA
#define MotorR2_10V GPIO_PIN_0
#define MotorR2_10V_Port GPIOB
#define MotorR3_10V GPIO_PIN_8
#define MotorR3_10V_Port GPIOB
#define MotorF1_10V GPIO_PIN_10
#define MotorF1_10V_Port GPIOA
#define MotorF2_10V GPIO_PIN_1
#define MotorF2_10V_Port GPIOB
#define MotorF3_10V GPIO_PIN_9
#define MotorF3_10V_Port GPIOB

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
