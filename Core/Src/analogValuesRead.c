/*
 * analogValuesRead.c
 *
 *  Created on: Apr 10, 2021
 *      Author: Marid
 */

#include "analogValuesRead.h"
#include "cmsis_os.h"

//ADC
uint16_t adcChannelsValues[15]={0,};
uint32_t lengthOfAdcChannelsValues = 15;
uint8_t adc1ReadyFlag=0;
uint8_t adc2ReadyFlag=0;
uint16_t adcAverageValues[3] = {0,};
uint8_t adcAverageValuesLength = 3;
uint16_t shiftedData[2]={0,};
uint32_t adc = 0;
uint32_t adcPr = 0;
uint32_t adcPr1 = 0;
uint8_t adcExpiredFlag=1;




//AC
uint32_t aver=0;
uint32_t averOld=0;
const uint16_t per=200;
uint16_t perCount=0;
uint16_t amp=0;
uint16_t ampPer=0;
float ampPerAverage=0;
uint16_t ampUp=0;
uint16_t ampDown=0;
uint16_t pogr=10;
uint16_t currentArray[10]={0,};
uint8_t currentArraycounter =0;
uint8_t tim7Flag=0;
uint32_t sum=0;
const uint32_t lengthOfAdcAcValues = 20000;
uint16_t adcAcValues[20000]={0,};
uint16_t upV[20000]={0,};
uint16_t dV[20000]={0,};

void getAC(void)
{
	if(adc2ReadyFlag)
	{
		adc2ReadyFlag=0;tim7Flag=0;
		uint16_t au=adcAcValues[0];
		uint16_t ad=adcAcValues[0];
		uint32_t aup=0;
		uint32_t adow =0;
		uint32_t cup=0;
		uint32_t cdow=0;
		for(uint16_t q = 1;q<20000;q++){

		if(adcAcValues[q]>2048){aup = aup + adcAcValues[q]; cup++;}else{adow = adow + adcAcValues[q];cdow++;}
		//aup = aup + (adcAcValues[q]>2048)?adcAcValues[q]:2048;
		//adow = adow + (adcAcValues[q]<2048)?adcAcValues[q]:2048;
		//au=au<adcAcValues[q]?adcAcValues[q]:au;
		//ad=ad>adcAcValues[q]?adcAcValues[q]:ad;
		}
		aup = aup/cup;
		adow = adow/cdow;
		ampPer=(aup-adow);///20000;//au-ad;

		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	}


}


/*
void getAC(void)

{



	if(adc2ReadyFlag)//tim7Flag)
	{
   // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

	aver = HAL_ADC_GetValue(&hadc2);
	adc2ReadyFlag =0; tim7Flag=0;
    HAL_ADC_Start_IT(&hadc2);



	if (averOld>aver && averOld-aver>pogr) {ampDown=aver;}
	if (aver>averOld && aver-averOld>pogr) {ampUp = aver;}
    averOld = aver;
    perCount++;

    if (perCount<per)
    {
    	if(amp<ampUp-ampDown)
    	{
    		amp=ampUp-ampDown;
    	}

    }else

    {
    	perCount=0; ampPer=amp;amp=0;
    	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
    }


    //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);}



    //currentArray[currentArraycounter]=ampPer;
    //if(currentArraycounter<10){currentArraycounter++;}else{currentArraycounter=0;}
    //sum=0;
   // for(uint8_t q=0;q<10;q++){
   // sum=sum+currentArray[q];

   // }
    ampPerAverage = ampPer;//um/10.0;
    //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
    }
}
*/

void scanAdc (void)
{

//getAC();//if(tim7Flag){tim7Flag=0;getAC();}
if(adc1ReadyFlag !=0 || adcExpiredFlag !=0)
	  {
		               adc1ReadyFlag = 0; adcExpiredFlag = 0;

		               adcAverageValues[0] = (adcChannelsValues[0]+adcChannelsValues[3]+adcChannelsValues[6]+adcChannelsValues[9]+adcChannelsValues[12])/5; //pressure
		               adcAverageValues[1] = (adcChannelsValues[1]+adcChannelsValues[4]+adcChannelsValues[7]+adcChannelsValues[10]+adcChannelsValues[13])/5; //debug
		               adcAverageValues[2] = (adcChannelsValues[2]+adcChannelsValues[5]+adcChannelsValues[8]+adcChannelsValues[11]+adcChannelsValues[14])/5; // level
//getArray_getMedian(adcChannelsValues,1,3,5);

                       //__HAL_ADC_CLEAR_FLAG(&hadc1, EOF);

		  	 	  	   //if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcChannelsValues, lengthOfAdcChannelsValues)!=HAL_OK){};
		  	 	  	   //adcEnableFlag = 0;
		  	 	  	  // lcdEnableFlag = 1;

	  }


}



uint16_t getArray_getMedian(uint16_t* dataForShift,u16 dataPositionInArray,u16 dataPeriodInArray, u16 dataLen){

	//uint16_t shiftedData[dataLen]={0,};
	for(uint16_t i =0; i<dataLen;i++){
		shiftedData[i]=dataForShift[(i*dataPeriodInArray) + dataPositionInArray];
	}
	return getMedianNum(shiftedData, dataLen);

}

uint16_t getMedianNum(uint16_t* bArray, uint16_t iFilterLen)
{
      uint16_t bTab[iFilterLen];
      for (uint8_t i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      uint16_t i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++)
      {
      for (i = 0; i < iFilterLen - j - 1; i++)
          {
        if (bTab[i] > bTab[i + 1])
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}



void tim7Callback(void)
{
	tim7Flag=1;//getAC();
	//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{


	    if(hadc->Instance == ADC1){
        adc1ReadyFlag =1;
	    }else if (hadc->Instance == ADC2){

	    	adc2ReadyFlag =1;
	    }



}

HAL_StatusTypeDef startTim7(void){

	return HAL_TIM_Base_Start_IT(&htim7);
}

HAL_StatusTypeDef startAdc2(void){

	//return HAL_ADC_Start_IT(&hadc2);

	return HAL_ADC_Start_DMA(&hadc2, (uint32_t*)&adcAcValues, lengthOfAdcAcValues);
}

HAL_StatusTypeDef startAdc1(void){

	return HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcChannelsValues, lengthOfAdcChannelsValues);
}

