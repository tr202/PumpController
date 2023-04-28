/*
 * analogValuesRead.h
 *
 *  Created on: Apr 10, 2021
 *      Author: Marid
 */

#ifndef INC_ANALOGVALUESREAD_H_
#define INC_ANALOGVALUESREAD_H_

#define ui8 uint8_t
#define ui16 uint16_t
#define ui32 uint32_t
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#include "main.h"
#include "math.h"
//ADC
uint16_t adcChannelsValues[15];
uint32_t lengthOfAdcChannelsValues;
uint8_t adc1ReadyFlag;
uint8_t adc2ReadyFlag;
uint16_t adcAverageValues[3];
uint8_t adcAverageValuesLength;
uint16_t shiftedData[2];
uint32_t adc;
uint32_t adcPr;
uint32_t adcPr1;
uint8_t adcExpiredFlag;
uint8_t adcMutex;
//AC
uint32_t aver;
uint32_t averOld;
uint16_t currentArray[10];
uint8_t currentArraycounter;
uint32_t sum;
const uint16_t per;
uint16_t perCount;

extern uint16_t amp;
extern uint16_t ampPer;
extern float ampPerAverage;
extern uint16_t ampUp;
extern uint16_t ampDown;
uint16_t pogr;

const uint32_t lengthOfAdcAcValues;
uint16_t adcAcValues[20000];


void scanAdc (void);
uint16_t getArray_getMedian(uint16_t* dataForShift,u16 dataPositionInArray,u16 dataPeriodInArray, u16 dataLen);
uint16_t getMedianNum(uint16_t* bArray, uint16_t iFilterLen);
HAL_StatusTypeDef startAdc1(void);
HAL_StatusTypeDef startAdc2(void);
HAL_StatusTypeDef startTim7(void);
void getAC(void);
void tim7Callback(void);
#endif /* INC_ANALOGVALUESREAD_H_ */
