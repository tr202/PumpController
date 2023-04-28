/*
 * spiUser.c
 *
 *  Created on: Apr 30, 2021
 *      Author: Marid
 */


#include "spiUser.h"


/* Buffer used for transmission */
uint16_t aTxBuffer[17] = {0,};

/* Buffer used for reception */
uint16_t aRxBuffer[17]={0,};

/* transfer state */
__IO uint32_t wTransferState;// = TRANSFER_WAIT;

//#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)


uint8_t spiValueFlag =0;
uint8_t spiFlag=1;
uint8_t spiSig=0;
uint8_t spiSigAcc=0;
uint8_t spiSigMainTicks=0;
uint16_t spiRead[16]={0,};
float countWaterSpent=0;
float waterSpent=0;
uint16_t* waterSpentPtr = (uint16_t*)&waterSpent;

uint32_t split32BitNum(uint16_t high, uint16_t low)
{
uint32_t t = high;


return (t<<16)+low;

}


void spiGetData(void){

	for(uint8_t x =0; x<16;x++){
		spiRead[x]=	aRxBuffer[x];
		}
	    getFloatPos(waterSpentPtr, 10);
}



void getFloatPos(uint16_t* floatPtr, uint8_t pos){

	         *floatPtr = spiRead[10];
	         *(floatPtr+1)=spiRead[11];
	         if (waterSpent >=0 && waterSpent < 10) // spiErrorfilter
	         {countWaterSpent = countWaterSpent + waterSpent;}
		  	 //*(floatPtr+2) = spiRead[pos+1]>>8;
		  	 //*(floatPtr+3) = spiRead[pos+1];

}



void startSpi (void){

	spiGetData();
//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);


	spiFlag=0;
	//aTxBuffer[0] = rtc.Sec;
	//aTxBuffer[1] = 45;
	//aTxBuffer[2] = 34;
	//aTxBuffer[3] = 99;
		//LCD_StringPos("sp",0,15);



	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	//osDelay(4);
	 if (HAL_SPI_TransmitReceive_DMA(&hspi2, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, 17) != HAL_OK)
	  {
	    /* Transfer error in transmission process */
		 LCD_StringPos("SPI ERROR",0,0);
	    Error_Handler();
	  }



}



void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  if(hspi->Instance == SPI2) {
	  spiFlag=1;
	  spiSig=1;
	  spiSigAcc=1;
	  spiSigMainTicks=1;
	  wTransferState = TRANSFER_COMPLETE;
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  };
  //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_2);

 // spiFlag=1;
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxRxCpltCallback should be implemented in the user file
   */
}

HAL_StatusTypeDef startTim11(void){

	return HAL_TIM_Base_Start_IT(&htim11);
}

/* switch (wTransferState)
 {
   case TRANSFER_COMPLETE :
     ##-3- Compare the sent and received buffers ##############################
     if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE))
     {
        Processing Error
       Error_Handler();
     }
     break;
   default :
     Error_Handler();
     break;
 }*/




/*
 static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength)
 {
   while (BufferLength--)
   {
     if ((*pBuffer1) != *pBuffer2)
     {
       return BufferLength;
     }
     pBuffer1++;
     pBuffer2++;
   }

   return 0;
 }
*/



