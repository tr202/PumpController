/*
 * canUserLayer.c
 *
 *  Created on: 18 апр. 2021 г.
 *      Author: Marid
 */


#include "canUserLayer.h"

char trans_str[128] = {0,};

//CAN_TxHeaderTypeDef TxHeader;
//CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8] = {0,};
uint8_t RxData[8] = {0,};
uint32_t TxMailbox = 0;

CAN_FilterTypeDef  sFilterConfig = {

  .FilterBank = 0,
  .FilterMode = CAN_FILTERMODE_IDMASK,
  .FilterScale = CAN_FILTERSCALE_32BIT,
  .FilterIdHigh = 0x0000,
  .FilterIdLow = 0x0000,
  .FilterMaskIdHigh = 0x0000,
  .FilterMaskIdLow = 0x0000,
  .FilterFIFOAssignment = CAN_RX_FIFO0,
  .FilterActivation = ENABLE
};

uint8_t levelSensorDataflag=0;


void checkCanFlags(void){

	if (levelSensorDataflag!=0){

	}
}



void getFloatPosCan(char* floatPtr, uint8_t pos){

	         *floatPtr = RxData[pos];
		  	 *(floatPtr+1) = RxData[pos+1];
		  	 *(floatPtr+2) = RxData[pos+2];
		  	 *(floatPtr+3) = RxData[pos+3];

}




void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	while (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) !=0){

    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
    {
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        if(RxHeader.StdId == 0x0450)
        {
        	getFloatPosCan(waterLevelPtr,3);
        	waterLevelEstimateTime = 5000;
        	//snprintf(trans_str, 128, "ID %04lX %d\n", RxHeader.StdId, RxData[0]);
        	//HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 100);
        }
        else if(RxHeader.StdId == 0x0126)
        {
        	//snprintf(trans_str, 128, "ID %04lX %d\n", RxHeader.StdId, RxData[0]);
        	//HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 100);
        }
    }
}
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    uint32_t er = HAL_CAN_GetError(hcan);
    //sprintf(trans_str,"ER CAN %lu %08lX", er, er);
    //HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 100);
    //osDelay(1000);
}



void runCan(void){
  //HAL_UART_Transmit(&huart1, (uint8_t*)"CAN\n", 4, 100);

  TxHeader.StdId = 0x0378;
  TxHeader.ExtId = 0;
  TxHeader.RTR = CAN_RTR_DATA; //CAN_RTR_REMOTE
  TxHeader.IDE = CAN_ID_STD;   // CAN_ID_EXT
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = 0;


  for(uint8_t i = 0; i < 8; i++)
  {
      TxData[i] = (i + 10);
  }


  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE);
}


void transmitCanFloat(uint32_t id, float num, uint8_t pos){

	char* ptr = (char*)&num;

	TxData[pos] = *ptr;
	TxData[pos+1] = *(ptr+1);
	TxData[pos+2] = *(ptr+2);
	TxData[pos+3] = *(ptr+3);

	transmitCan(id,TxData);
}



void transmitCan(uint32_t stdId, uint8_t* txData){


	  TxHeader.StdId = stdId;

	  //if(TxMailbox<2) {TxMailbox++;}else{TxMailbox=0;}

//TxMailbox=2;

      //

      if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, txData, &TxMailbox) != HAL_OK)
      {
    	  //HAL_UART_Transmit(&huart1, (uint8_t*)"ER SEND\n", 8, 100);
      }
      while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0);

     /* osDelay(500);


	  TxHeader.StdId = 0x0126;
	  TxData[0] = 100;

      while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0);

      if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
      {
    	  //HAL_UART_Transmit(&huart1, (uint8_t*)"ER SEND\n", 8, 100);
      }

      osDelay(500);
*/
}


































