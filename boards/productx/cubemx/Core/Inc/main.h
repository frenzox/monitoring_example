/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define UNUSED_Pin GPIO_PIN_13
#define UNUSED_GPIO_Port GPIOC
#define UNUSEDC14_Pin GPIO_PIN_14
#define UNUSEDC14_GPIO_Port GPIOC
#define UNUSEDC15_Pin GPIO_PIN_15
#define UNUSEDC15_GPIO_Port GPIOC
#define HEARTBEAT_LED_Pin GPIO_PIN_0
#define HEARTBEAT_LED_GPIO_Port GPIOA
#define UNUSEDA1_Pin GPIO_PIN_1
#define UNUSEDA1_GPIO_Port GPIOA
#define UNUSEDA2_Pin GPIO_PIN_2
#define UNUSEDA2_GPIO_Port GPIOA
#define UNUSEDA3_Pin GPIO_PIN_3
#define UNUSEDA3_GPIO_Port GPIOA
#define UNUSEDA4_Pin GPIO_PIN_4
#define UNUSEDA4_GPIO_Port GPIOA
#define UNUSEDA5_Pin GPIO_PIN_5
#define UNUSEDA5_GPIO_Port GPIOA
#define UNUSEDA6_Pin GPIO_PIN_6
#define UNUSEDA6_GPIO_Port GPIOA
#define UNUSEDA7_Pin GPIO_PIN_7
#define UNUSEDA7_GPIO_Port GPIOA
#define ADC_TEMP_Pin GPIO_PIN_0
#define ADC_TEMP_GPIO_Port GPIOB
#define UNUSEDB1_Pin GPIO_PIN_1
#define UNUSEDB1_GPIO_Port GPIOB
#define UNUSEDB2_Pin GPIO_PIN_2
#define UNUSEDB2_GPIO_Port GPIOB
#define UNUSEDB10_Pin GPIO_PIN_10
#define UNUSEDB10_GPIO_Port GPIOB
#define UNUSEDB11_Pin GPIO_PIN_11
#define UNUSEDB11_GPIO_Port GPIOB
#define UNUSEDB12_Pin GPIO_PIN_12
#define UNUSEDB12_GPIO_Port GPIOB
#define UNUSEDB13_Pin GPIO_PIN_13
#define UNUSEDB13_GPIO_Port GPIOB
#define UNUSEDB14_Pin GPIO_PIN_14
#define UNUSEDB14_GPIO_Port GPIOB
#define UNUSEDB15_Pin GPIO_PIN_15
#define UNUSEDB15_GPIO_Port GPIOB
#define UNUSEDA8_Pin GPIO_PIN_8
#define UNUSEDA8_GPIO_Port GPIOA
#define UNUSEDA9_Pin GPIO_PIN_9
#define UNUSEDA9_GPIO_Port GPIOA
#define UNUSEDA10_Pin GPIO_PIN_10
#define UNUSEDA10_GPIO_Port GPIOA
#define UNUSEDA11_Pin GPIO_PIN_11
#define UNUSEDA11_GPIO_Port GPIOA
#define UNUSEDA12_Pin GPIO_PIN_12
#define UNUSEDA12_GPIO_Port GPIOA
#define UNUSEDA13_Pin GPIO_PIN_13
#define UNUSEDA13_GPIO_Port GPIOA
#define UNUSEDA14_Pin GPIO_PIN_14
#define UNUSEDA14_GPIO_Port GPIOA
#define UNUSEDA15_Pin GPIO_PIN_15
#define UNUSEDA15_GPIO_Port GPIOA
#define UNUSEDB3_Pin GPIO_PIN_3
#define UNUSEDB3_GPIO_Port GPIOB
#define UNUSEDB4_Pin GPIO_PIN_4
#define UNUSEDB4_GPIO_Port GPIOB
#define UNUSEDB5_Pin GPIO_PIN_5
#define UNUSEDB5_GPIO_Port GPIOB
#define UNUSEDB6_Pin GPIO_PIN_6
#define UNUSEDB6_GPIO_Port GPIOB
#define UNUSEDB7_Pin GPIO_PIN_7
#define UNUSEDB7_GPIO_Port GPIOB
#define UNUSEDB8_Pin GPIO_PIN_8
#define UNUSEDB8_GPIO_Port GPIOB
#define UNUSEDB9_Pin GPIO_PIN_9
#define UNUSEDB9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
