/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for inputTask */
osThreadId_t inputTaskHandle;
const osThreadAttr_t inputTask_attributes = {
  .name = "inputTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for lcdTask */
osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for outputTask03 */
osThreadId_t outputTask03Handle;
const osThreadAttr_t outputTask03_attributes = {
  .name = "outputTask03",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for HydroAcc04 */
osThreadId_t HydroAcc04Handle;
const osThreadAttr_t HydroAcc04_attributes = {
  .name = "HydroAcc04",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for lcdBackLightTimer */
osTimerId_t lcdBackLightTimerHandle;
const osTimerAttr_t lcdBackLightTimer_attributes = {
  .name = "lcdBackLightTimer"
};
/* Definitions for i2cMutex */
osMutexId_t i2cMutexHandle;
const osMutexAttr_t i2cMutex_attributes = {
  .name = "i2cMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void inputStartTask(void *argument);
void LcdStartTask(void *argument);
void outputStartTask(void *argument);
void HydroAccStartTask04(void *argument);
void lcdBackLightCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of i2cMutex */
  i2cMutexHandle = osMutexNew(&i2cMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of lcdBackLightTimer */
  lcdBackLightTimerHandle = osTimerNew(lcdBackLightCallback, osTimerOnce, NULL, &lcdBackLightTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of inputTask */
  inputTaskHandle = osThreadNew(inputStartTask, NULL, &inputTask_attributes);

  /* creation of lcdTask */
  lcdTaskHandle = osThreadNew(LcdStartTask, NULL, &lcdTask_attributes);

  /* creation of outputTask03 */
  outputTask03Handle = osThreadNew(outputStartTask, NULL, &outputTask03_attributes);

  /* creation of HydroAcc04 */
  HydroAcc04Handle = osThreadNew(HydroAccStartTask04, NULL, &HydroAcc04_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_inputStartTask */
/**
  * @brief  Function implementing the inputTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_inputStartTask */
void inputStartTask(void *argument)
{
  /* USER CODE BEGIN inputStartTask */
	     if(startTim7()!=HAL_OK){Error_Handler();}
	     if(startAdc2()!=HAL_OK){Error_Handler();}
		 if(startAdc1()!=HAL_OK){Error_Handler();}
		 //if(startTim2()!=HAL_OK){Error_Handler();}
		 if(startTim11()!=HAL_OK){Error_Handler();}
	     DS3231_Init(&hi2c1);

	    /* osMutexAcquire(i2cMutexHandle, osWaitForever); // try to acquire mutex
		// Здесь происходит защищенный доступ к ресурсу.
		 DS3231_SetTime(&rtc);
		 //Configure Alarm1
		 DS3231_ClearAlarm1();
		 DS3231_SetAlarm1(ALARM_MODE_ONCE_PER_SECOND, 0, 0, 0, 0);
		 DS3231_SetAlarm1(ALARM_MODE_SEC_MATCHED, 0, 0, 0, 30);
		 osDelay(10);
		 DS3231_GetTime(&rtc);
		 DS3231_ReadTemperature(&rtcTemp);
		 ReadRegister(DS3231_REG_STATUS, &regVal);
		    if(regVal & DS3231_STA_A1F)
		  {
		    regVal &= ~DS3231_STA_A1F;
		    WriteRegister(DS3231_REG_STATUS, regVal);
		  }
		// Отдаем "жетон".
		osMutexRelease(i2cMutexHandle);*/
		uint32_t uwTickOld=0;

  /* Infinite loop */
  for(;;)
  {

	  IwdgRefresh

	uint32_t tick = HAL_GetTick();

	if(abs(uwTickOld - tick)> ds3231TimeUpdateInterval){

	uwTickOld = tick;

    //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

    osMutexAcquire(i2cMutexHandle, osWaitForever); // try to acquire mutex
	DS3231_GetTime(&rtc); //refresh timeDate  with ds3231TimeUpdateInterval in systicks
	osMutexRelease(i2cMutexHandle);
	lcdUpdateFlag=1;

	}

	uint8_t x = scanPorts();//scan inputs for changes

	if (x != 0) lcdUpdateFlag=1;

	scanAdc();
	//scanFlow();
	updateEstimatePeriod(); //update estimate flows period if new data was received
	if(tim11Flag){
		tim11Flag=0;
		//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_3);
		startSpi();
		spiValueFlag = 1;
		frequencyCalcCapturedVal(&frequences[0],split32BitNum(spiRead[4],spiRead[5]));
		frequencyCalcCapturedVal(&frequences[1],split32BitNum(spiRead[7],spiRead[8]));
	}


	//if(!spiFlag){startSpi();}

	//if(spiFlag){spiFlag=0;}
    //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	//scanAdc();

/*

	if(adcEnableFlag){

scanAdc();

	}
*/
	//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

	getAC();
	checkCanFlags();
	osDelay(1);
  }
  /* USER CODE END inputStartTask */
}

/* USER CODE BEGIN Header_LcdStartTask */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LcdStartTask */
void LcdStartTask(void *argument)
{
  /* USER CODE BEGIN LcdStartTask */

	osMutexAcquire(i2cMutexHandle, osWaitForever);
	LCD_ini();
	osMutexRelease(i2cMutexHandle);
	osTimerStart(lcdBackLightTimerHandle, 2000000);
	uint8_t BBin=0;
  /* Infinite loop */
  for(;;)
  {

	  IwdgRefresh
	  HAL_IWDG_Refresh(&hiwdg);
	  if (moveSensor || blueButton){LCD_onLed(); osTimerStart(lcdBackLightTimerHandle, 120000); } //time lcd backLight off

	  //taskENTER_CRITICAL( );
	  if(lcdUpdateFlag){
	  switch(screenNum){

	  case(0):{
		  sprintf(&window[0][0],(char*)formatsShort[0],rtc.Hour,rtc.Min,rtc.Sec,rtc.Date,rtc.Month,rtc.Year);
		  sprintf(&window[1][0],(char*)formatsShort[32],waterLevel);
		  sprintf(&window[2][0],(char*)formatsShort[31],pressure);//RxData[0]);
		  sprintf(&window[3][0],(char*)formatsShort[39],countWaterSpent);//33],mainPumpTemp);//ackLevelSwitch);//27currentVfd);//33mainPumpTemp);//[25]lackLevelSwitch,drinkWaterSw,mainPumpState);
		  spiSig=0;
		 // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_2);
		  //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_3);
		 // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
		  break;
	  }

	  case(1):{
	  		  sprintf(&window[0][0],(char*)formatsShort[31],pressure);
	  		  sprintf(&window[1][0],(char*)formatsShort[29],mainFlow);
	  		  sprintf(&window[2][0],(char*)formatsShort[30],cycleFlow);//RxData[0]);
	  		  sprintf(&window[3][0],(char*)formatsShort[33],mainPumpTemp);//27currentVfd);//33mainPumpTemp);//[25]lackLevelSwitch,drinkWaterSw,mainPumpState);
	  		  break;
	  	  }
	  case(2):{
	  		  sprintf(&window[0][0],(char*)formatsShort[27],currentVfd);
	  		  sprintf(&window[1][0],(char*)formatsShort[25],lackLevelSwitch,drinkWaterSw,mainPumpState);
	  		  sprintf(&window[2][0],(char*)formatsShort[19],moveSensor,blueButton);//RxData[0]);
	  		  sprintf(&window[3][0],(char*)formatsShort[28],debugAdc);//27currentVfd);//33mainPumpTemp);//[25]lackLevelSwitch,drinkWaterSw,mainPumpState);
	  		  break;
	  	  }




	  }


	  IwdgRefresh
	  osMutexAcquire(i2cMutexHandle, osWaitForever); // try to acquire mutex



	       LCD_StringPos(&window[0][0],0,0);

	       LCD_StringPos(&window[1][0],0,1);

	       LCD_StringPos(&window[2][0],0,2);

	       LCD_StringPos(&window[3][0],0,3);

	  //lcdEnableFlag=0;
	  //adcEnableFlag =1;
	  //HAL_IWDG_Refresh(&hiwdg);



	  osMutexRelease(i2cMutexHandle);
	  lcdUpdateFlag=0;

	  }
      if(blueButton){BBin=1;}
      if(!blueButton && BBin){BBin = 0;screenNum++; }
	  if(screenNum>2){screenNum=0;}
	  IwdgRefresh
	  osDelay(1);

  }
  /* USER CODE END LcdStartTask */
}

/* USER CODE BEGIN Header_outputStartTask */
/**
* @brief Function implementing the outputTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_outputStartTask */
void outputStartTask(void *argument)
{
  /* USER CODE BEGIN outputStartTask */
  HAL_TIM_Base_Start_IT(&htim10);
  runCan();
  //uint16_t mainPumpWorkTime =0;
  float kTemp =0;
  float countWaterSpentOld=0;
  float diffWs=0;
  uint8_t secOld=0;
  uint8_t minOld=0;
  //uint32_t timePumpWorkWithautMainFlow = 9000; // tim10 150 Gz * 60 sec
  //uint32_t x=0;
  //uint8_t correctionFlag=0;

  /* Infinite loop */
  for(;;)
  {
	//HAL_IWDG_Refresh(&hiwdg);
	  calcCore();
	  TxData[0] = rtc.Hour;
	  TxData[1] = rtc.Min;
	  TxData[2] = rtc.Sec;
	  TxData[3] = rtc.Date;
	  TxData[4] = rtc.DaysOfWeek;
	  TxData[5] = rtc.Month;
	  TxData[6] = rtc.Year;

	  if (rtc.Min != minOld){minOld=rtc.Min;  transmitCan(0x0378, TxData);}

	  diffWs = countWaterSpent-countWaterSpentOld;
	  if( diffWs>1 ) {countWaterSpentOld=countWaterSpent; transmitCanFloat(0x0350, diffWs, 0);} // send Water Spent

	  if (rtc.Sec - secOld >2 || secOld - rtc.Sec>2){secOld=rtc.Sec; transmitCanFloat(0x0550,3.14,0);}// level Request

	  //transmitCan(0x0378, TxData);
	 //if(blueButton){mainPumpState=1;}else{mainPumpState=0;}

	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_RESET );
////////////////////////////////////////////////////////////////////


	 if (rtc.Hour == 20 || rtc.Hour == 10) {UVLampOn;}  // UV lalmp  from 10 to 12 and 20 to 22 Relay3
	 if (rtc.Hour == 22 || rtc.Hour == 12) {UVLampOff;}

	 //////////////////////////////check pressure on pressure accumulator/////////////////////////////





	 if(tim10Flag ==1){
		 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_3);
		 tim10Flag=0;
		 //correctionFlag =0;

		 kTemp = kTemp - (kTemp*0.000001);// decrease temp from time

		 //
		 if( mainPumpState || mainFlow!=0){
			 float sumFlows = mainFlow+cycleFlow;
			 float s = (10 - sumFlows)*0.001;

			 float k =  kTemp + (s);
			 k=k>200?200:k;
			 k=k<0?0:k;
			 kTemp = k; // increase decrease relatively flows
		 }
		 mainPumpTemp = kTemp + 16; //surrond shift;
		 if(mainPumpTemp>75){bypassValveOpen;}
		 if(mainPumpTemp<18){bypassValveClose;}
		 //if(mainPumpTemp>80){setPosition(1); correctionFlag =1;}
		 //if (mainPumpState && mainFlow < 0.1) {

			 //x++;
			 //if(x>=timePumpWorkWithautMainFlow){setPosition(1); osDelay(6000);x=0;}

			// }



	 }
//if(startButtonV){flushValveOpen;}
//if(stopButtonV){flushValveClose;}
	 //if(waterLevelFlag){connectVfdGroundOn;}else{connectVfdGroundOff;};
	 //setPosition(1);
	 //if(waterLevelFlag){if(!correctionFlag){setPosition(pressure);}}else{setPosition(1);} // check if low water level, set max pressure to stop pump
	 //if(waterLevelFlag && drinkWaterSw){drinkWaterPumpOn;}else{drinkWaterPumpOff;} // disable the drink water pump if low water level
	 //if(waterLevelFlag) {setPosition(pressure);}else{setPosition(1);}
IwdgRefresh

/////////////////////////////////////////////

	 //if(mainPumpState !=0){

		 //mainPumpWorkTime++;
		 //mainPumpTemp = mainPumpTemp + (10-mainFlow)*

		// if(mainFlow < 8 && mainFlow > 0){bypassValveOpen;}else{bypassValveClose;}
	// }else{mainPumpWorkTime =0;}
//drinkWaterPumpOn;
//if (blueButton) {bypassValveOpen;}else{bypassValveClose;}
//UVLampOn;
//reservOn;

  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_RESET );
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1,GPIO_PIN_RESET );
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,GPIO_PIN_RESET );
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,GPIO_PIN_RESET );




	  osDelay(1);

	  //if(ampPer>70) {HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_RESET );}else{HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET );}
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_RESET );
  }
  /* USER CODE END outputStartTask */
}

/* USER CODE BEGIN Header_HydroAccStartTask04 */
/**
* @brief Function implementing the HydroAcc04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HydroAccStartTask04 */
void HydroAccStartTask04(void *argument)
{
  /* USER CODE BEGIN HydroAccStartTask04 */
  uint8_t beginRestore =0;
  uint32_t restoreTime =10000;
  uint32_t restoreElapsedTime =0;
  uint8_t button = 0;
  uint8_t start=0;
  uint8_t corrFlag=0;
  uint8_t hydroRestoreFlag =0;
  uint8_t flushFlag =0;
  uint32_t flushElapsedTime =0;
	/* Infinite loop */
  for(;;)
  {

	  if(rtc.Hour==0){hydroRestoreFlag =0;flushFlag =0;} ////reset flags///
	  /////////////////////////////////////////////////////////////////////Discharge of stagnant water from a end line /////////////////
	  if(rtc.Hour ==1 && rtc.Min==1 && flushElapsedTime==0 && flushFlag ==0){
		  flushFlag=1;
		  flushElapsedTime = 12000;
		  flushValveOpen;

	  }
	  if(flushElapsedTime<=0){flushValveClose;}else{flushElapsedTime--;}

	  ///////////////////////////////////////////////////////////Restoration of the initial air pressure in the accumulator///////////////////////////////////////////////////////// resore Hudro////////////////////////////////////////////////
	  if ((rtc.DaysOfWeek == 2 || rtc.DaysOfWeek == 5) && rtc.Hour == 1 && rtc.Min ==2 && hydroRestoreFlag ==0 && restoreElapsedTime ==0){
		  hydroRestoreFlag =1;
		  restoreElapsedTime =30000;
		  hydroAccRestoreOpen;

	  }
	  if(restoreElapsedTime<=0){hydroAccRestoreClose;}else{restoreElapsedTime--;}

	  //if(startButtonV){flushValveOpen;}
	  //if(stopButtonV){flushValveClose;}
	  //if(startButtonV){if (button==0){button=1;}}
	  //if(stopButtonV){flushValveClose;beginRestore=0;dacCorrectFlag=0;}

	  //if(startButtonV){button=1;}
	  //if(!startButtonV && button){button = 0; start =1;}

	  	 // if(startButtonV){hydroAccRestoreOpen;}else{hydroAccRestoreClose;}
	  	  //if(stopButtonV){flushValveOpen;}else{flushValveClose;}


	  	  //if(stopButtonV){UVLampOn;}else{UVLampOff;}

	    // if (rtc.Hour == 0) {restoreAccumFlag = 0;}
	 	 //if ((!restoreAccumFlag && !mainPumpState && pressure>0.3 && rtc.Hour == 1 && rtc.Min == 0) || start) // Restore air pressure on hydroaccumulator
	 	// {



	 		 //flushValveOpen;
	 		 /////////////////////////////////////////////////old procedure////////////////////////
					// start=0;
					// beginRestore =1;
				    //elapsedTime = restoreTimeAfterPressureDown05;
					//restoreAccumFlag=1;
	 		 //////////////////////////////////////////////////////////////////////////////////////

	 	// }

	 	/* if(beginRestore && spiSigAcc)
	 	 {

	 		 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);

	 	     dacCorrectFlag=200;

	 			 //HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET);

	 			 //HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);


	 		 dacCorrectValue =4095;
	 		 spiSigAcc =0;
	 		 flushValveOpen;
	 	 }

	 	 if (pressure < 0.2 && elapsedTime>0 && beginRestore)
	 	 {
	 		elapsedTime--;

	 	 }else if (pressure < 0.2 && elapsedTime<=0 && beginRestore)
	 	 {
	 		 beginRestore =0;
	 		 flushValveClose;
	 		 dacCorrectFlag=0;
	 	 }*/



	  osDelay(1);
  }
  /* USER CODE END HydroAccStartTask04 */
}

/* lcdBackLightCallback function */
void lcdBackLightCallback(void *argument)
{
  /* USER CODE BEGIN lcdBackLightCallback */
	if (LCD_getBackLightState()){LCD_offLed();screenNum=0;} /////////////////////////////////////// LCD OFF Backlight /////////////////////////////////////
  /* USER CODE END lcdBackLightCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
