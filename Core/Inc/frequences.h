/*
 * frequences.h
 *
 *  Created on: Apr 13, 2021
 *      Author: Marid
 */

#ifndef INC_FREQUENCES_H_
#define INC_FREQUENCES_H_
#include "main.h"

typedef struct
{
TIM_HandleTypeDef* tim;
uint32_t channel;
uint32_t CCRx[2];
float frequence;
uint8_t namePos;
uint8_t compFlag;
uint16_t liveTime;
uint8_t sensorType;
float flow;
}frequencyCalcTypedef;

extern frequencyCalcTypedef frequences[2];


//RatesCalculation//
typedef struct
{
float regectionRate;
float recyclingRate;
float membraneFlow;
}ratesCalculationTypedef;


ratesCalculationTypedef rates;
uint8_t globalTim2Flag;

HAL_StatusTypeDef startTim2(void);
void scanFlow(void);
void frequencyCalcCapturedVal(frequencyCalcTypedef* fr, uint32_t CapturedVal);
void updateEstimatePeriod(void);
#endif /* INC_FREQUENCES_H_ */
