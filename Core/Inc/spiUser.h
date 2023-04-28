/*
 * spiUser.h
 *
 *  Created on: Apr 30, 2021
 *      Author: Marid
 */

#ifndef INC_SPIUSER_H_
#define INC_SPIUSER_H_
//#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)
#include "main.h"




/*  ///////////////////////////////////////////////////Transmitter Defines///////////////////////////////

#define pressureAdc aTxBuffer[0]
#define dacValue  aTxBuffer[1]
#define levelAdc  aTxBuffer[2]
#define leackState  aTxBuffer[3]
#define mainFlowHighByte  aTxBuffer[4]
#define mainFlowLowByte  aTxBuffer[5]
#define res  aTxBuffer[6]
#define bypassFlowHighByte  aTxBuffer[7]
#define bypassFlowLowByte  aTxBuffer[8]
#define debugAdc aTxBuffer[9]

//#define aTxBuffer[10] res10
//#define aTxBuffer[11] res11
//#define aTxBuffer[12] res12
//#define aTxBuffer[13] res13
//#define aTxBuffer[14] res14
//#define aTxBuffer[15] res15

*/

#define pressureAdc aRxBuffer[0]
#define dacValue  aRxBuffer[1]
#define levelAdc  aRxBuffer[2]
#define leackState  aRxBuffer[3]
#define mainFlowHighByte  aRxBuffer[4]
#define mainFlowLowByte  aRxBuffer[5]
#define res  aRxBuffer[6]
#define bypassFlowHighByte  aRxBuffer[7]
#define bypassFlowLowByte  aRxBuffer[8]
#define debugAcp aRxBuffer[9]


#define   dacCorrectFlag  aTxBuffer[0]
#define   dacCorrectValue  aTxBuffer[1]
	//aTxBuffer[2] = 34;
	//aTxBuffer[3] = 99;



enum
{
  TRANSFER_WAIT,
  TRANSFER_COMPLETE,
  TRANSFER_ERROR
};



extern uint8_t spiValueFlag;
extern uint8_t spiFlag;
extern uint8_t spiSig;
extern uint8_t spiSigAcc;
extern uint8_t spiSigMainTicks;
extern float countWaterSpent;
extern float waterSpent;
extern uint16_t* waterSpentPtr;

uint16_t spiRead[16];
/* Buffer used for transmission */
uint16_t aTxBuffer[17];// = "****SPI - Two Boards communication based on DMA **** SPI Message ******** SPI Message ******** SPI Message ****";

/* Buffer used for reception */
uint16_t aRxBuffer[17];

/* transfer state */
__IO uint32_t wTransferState;// = TRANSFER_WAIT;

//#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)

//static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);
void startSpi (void);
void spiGetData(void);
uint32_t split32BitNum(uint16_t high, uint16_t low);
HAL_StatusTypeDef startTim11(void);
void getFloatPos(uint16_t* floatPtr, uint8_t pos);
#endif /* INC_SPIUSER_H_ */
