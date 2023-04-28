/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "lcd.h"
#include "stm32_ds3231.h"
#include "var_types_global.h"
#include "inputs.h"
#include "analogValuesRead.h"
#include "frequences.h"
#include "pressureSensor.h"
#include "spiPotenciometr.h"
#include "waterLevelSensor.h"
#include "current.h"
#include "canUserLayer.h"
#include "spiUser.h"

#include "adc.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdbool.h>
#include "math.h"




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
#define UserButton_Pin GPIO_PIN_13
#define UserButton_GPIO_Port GPIOC
#define BypassValveR1_Pin GPIO_PIN_0
#define BypassValveR1_GPIO_Port GPIOC
#define FlushValveR2_Pin GPIO_PIN_1
#define FlushValveR2_GPIO_Port GPIOC
#define hudroAccRestoreR3_Pin GPIO_PIN_2
#define hudroAccRestoreR3_GPIO_Port GPIOC
#define uvLampR4_Pin GPIO_PIN_3
#define uvLampR4_GPIO_Port GPIOC
#define pressureSensorCH0_Pin GPIO_PIN_0
#define pressureSensorCH0_GPIO_Port GPIOA
#define currentSensor_Pin GPIO_PIN_1
#define currentSensor_GPIO_Port GPIOA
#define greenLed1_Pin GPIO_PIN_2
#define greenLed1_GPIO_Port GPIOA
#define greenLed2_Pin GPIO_PIN_3
#define greenLed2_GPIO_Port GPIOA
#define levelSensor_Pin GPIO_PIN_4
#define levelSensor_GPIO_Port GPIOA
#define greenLed_Pin GPIO_PIN_5
#define greenLed_GPIO_Port GPIOA
#define mainPumpOn_Pin GPIO_PIN_6
#define mainPumpOn_GPIO_Port GPIOA
#define debugAdc_Pin GPIO_PIN_7
#define debugAdc_GPIO_Port GPIOA
#define spi2CS_Pin GPIO_PIN_12
#define spi2CS_GPIO_Port GPIOB
#define startButton_Pin GPIO_PIN_8
#define startButton_GPIO_Port GPIOC
#define stopButton_Pin GPIO_PIN_9
#define stopButton_GPIO_Port GPIOC
#define greenLed3_Pin GPIO_PIN_10
#define greenLed3_GPIO_Port GPIOA
#define MainFlow_Pin GPIO_PIN_15
#define MainFlow_GPIO_Port GPIOA
#define motionSensor_Pin GPIO_PIN_2
#define motionSensor_GPIO_Port GPIOD
#define bypassFlow_Pin GPIO_PIN_3
#define bypassFlow_GPIO_Port GPIOB
#define drinkFilterPumpControlSwitch_Pin GPIO_PIN_4
#define drinkFilterPumpControlSwitch_GPIO_Port GPIOB
#define lackLevel_Pin GPIO_PIN_5
#define lackLevel_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
