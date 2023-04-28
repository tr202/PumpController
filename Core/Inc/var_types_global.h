/*
 * var_types_global.h
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: Marid
 */

#ifndef INC_VAR_TYPES_GLOBAL_H_
#define INC_VAR_TYPES_GLOBAL_H_


#include "main.h"

#define bypassValveOpen HAL_GPIO_WritePin(outs[0].Port,outs[0].Pin,GPIO_PIN_RESET)
#define bypassValveClose HAL_GPIO_WritePin(outs[0].Port,outs[0].Pin,GPIO_PIN_SET)
#define flushValveOpen HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET)
#define flushValveClose HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET)
#define hydroAccRestoreOpen HAL_GPIO_WritePin(outs[2].Port,outs[2].Pin,GPIO_PIN_RESET)
#define hydroAccRestoreClose HAL_GPIO_WritePin(outs[2].Port,outs[2].Pin,GPIO_PIN_SET)
#define UVLampOn HAL_GPIO_WritePin(outs[3].Port,outs[3].Pin,GPIO_PIN_RESET)
#define UVLampOff HAL_GPIO_WritePin(outs[3].Port,outs[3].Pin,GPIO_PIN_SET)
#define connectVfdGroundOn HAL_GPIO_WritePin(outs[4].Port,outs[4].Pin,GPIO_PIN_RESET)
#define connectVfdGroundOff HAL_GPIO_WritePin(outs[4].Port,outs[4].Pin,GPIO_PIN_SET)

#define  IwdgRefresh HAL_IWDG_Refresh(&hiwdg);

extern uint8_t tim10Flag;
extern uint8_t tim11Flag;
extern uint8_t restoreAccumFlag;

typedef struct
{
GPIO_TypeDef* Port;
uint16_t Pin;
GPIO_PinState pinState;
} outPortTypedef;

const outPortTypedef outs[5];


extern uint8_t lcdEnableFlag;
extern uint8_t adcEnableFlag;



extern _RTC rtc;
extern uint8_t regVal;
extern float rtcTemp;
const uint32_t ds3231TimeUpdateInterval;
const uint32_t adcUpdateInterval;
extern uint8_t lcdUpdateFlag;


const char *formatsShort[40];

extern char window[20][30];


extern float waterLevel;
extern char* waterLevelPtr;
extern uint32_t waterLevelEstimateTime;

extern uint8_t lackLevelSwitch;
extern float pressure;
extern float mainFlow;
extern float mainSpentLitres;
uint8_t flagWaterSpent;
extern float cycleFlow;
extern float mainPumpTemp;
extern uint16_t debugAdc;
extern uint8_t drinkWaterSw;
extern uint8_t waterLevelFlag;
extern uint8_t mainPumpState;
extern float  currentVfd;
extern uint8_t blueButton;
extern uint8_t startButtonV;
extern uint8_t stopButtonV;
extern  uint8_t moveSensor;
extern uint8_t screenNum;
void calcCore(void);
uint8_t toggleFlag (uint8_t flag);
//void setOut(char* name);


#endif /* INC_VAR_TYPES_GLOBAL_H_ */
