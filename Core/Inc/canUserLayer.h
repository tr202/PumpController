/*
 * canUserLayer.h
 *
 *  Created on: 18 апр. 2021 г.
 *      Author: Marid
 */

#ifndef INC_CANUSERLAYER_H_
#define INC_CANUSERLAYER_H_

#include "main.h"

char trans_str[128];

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
extern uint8_t TxData[8];
extern uint8_t RxData[8];
uint32_t TxMailbox;
extern uint8_t levelSensorDataflag;

void runCan(void);
void transmitCan(uint32_t stdId, uint8_t* txData);
void transmitCanFloat(uint32_t id, float num, uint8_t pos);
extern CAN_FilterTypeDef  sFilterConfig;
void checkCanFlags(void);
void getFloatPosCan(char* floatPtr, uint8_t pos);

#endif /* INC_CANUSERLAYER_H_ */
