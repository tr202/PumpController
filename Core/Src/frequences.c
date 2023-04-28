/*
 * frequences.c
 *
 *  Created on: Apr 13, 2021
 *      Author: Marid
 */


#include "frequences.h"


frequencyCalcTypedef frequences[2] = {

		{.channel = TIM_CHANNEL_1, .tim = &htim2, .sensorType = 3},
		{.channel = TIM_CHANNEL_2, .tim = &htim2, .sensorType = 1}

};

ratesCalculationTypedef rates={0};
uint8_t globalTim2Flag =0;
uint8_t frequencesLength = 2;
uint32_t sysClock = 180000000;
uint32_t dividend=1000000;
uint16_t timeUnactivityToClearFrequency = 100;//osDelay Units*10 1/100 sec

void updateEstimatePeriod(void)
{
	if(spiSig)
	{
		spiSig=0;

		for(uint8_t q =0; q< frequencesLength;q++)
						  {
							  frequences[q].liveTime=timeUnactivityToClearFrequency;
						  }




	}

}

void frequencyCalcCapturedVal(frequencyCalcTypedef* fr, uint32_t CapturedVal)
{

if(CapturedVal>0){
fr->frequence = dividend /(CapturedVal*1.0);
switch(fr->sensorType)
{
case 1 : {fr->flow = fr->frequence/11;break;}
case 2 : {fr->flow = fr->frequence/6.6;break;}
case 3 : {fr->flow = (fr->frequence+8)/6;break;}
//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_6);
}
}else{fr->flow=0;}
for(uint8_t q =0; q< frequencesLength;q++)
				  {
					  if(frequences[q].liveTime!=0){frequences[q].liveTime--; }else{frequences[q].flow=0;}
				  }


}



void frequencyCalc(frequencyCalcTypedef* fr)
{
fr->frequence = dividend /((fr->CCRx[1]-fr->CCRx[0])*1.0);
switch(fr->sensorType)
{
case 1 : {fr->flow = fr->frequence/11;break;}
case 2 : {fr->flow = fr->frequence/6.6;break;}
case 3 : {fr->flow = (fr->frequence+8)/6;break;}
//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_6);
}
}

void getCapturedValue(frequencyCalcTypedef* fr)
{
	fr->CCRx[0]=fr->CCRx[1];
	fr->CCRx[1]=HAL_TIM_ReadCapturedValue(fr->tim,fr->channel);
	fr->liveTime = timeUnactivityToClearFrequency;
	fr->compFlag=0;
	frequencyCalc(fr);

}


void scanFlow(void){



if(globalTim2Flag)
		  {

		  	  globalTim2Flag=0;
			  for(uint8_t q =0; q< frequencesLength;q++)
				  {
					  if(frequences[q].compFlag!=0){getCapturedValue(&frequences[q]); }
				  }
		  }
 for(uint8_t q =0; q< frequencesLength;q++)
				  {
					  if(frequences[q].liveTime!=0){frequences[q].liveTime--; }else{frequences[q].flow=0;}
				  }



}


HAL_StatusTypeDef startTim2(void){
	    HAL_StatusTypeDef retVal = HAL_ERROR;
		if (HAL_TIM_Base_Start_IT(&htim2)==HAL_OK &&
		HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1) == HAL_OK &&
		HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2)==HAL_OK){retVal = HAL_OK; }else{retVal = HAL_ERROR;}
        return retVal;
}



void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) // колбек по захвату
{
      if (htim->Instance == TIM2){
    	  	globalTim2Flag=1;
        	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){frequences[0].compFlag=1;}
        	else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){frequences[1].compFlag=1;}

//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_6);

        }
}

