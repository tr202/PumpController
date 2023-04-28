/*
 * var_types_global.c
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: Marid
 */

#include "var_types_global.h"

/////////////////////////////////Flags////////////////////
 uint8_t tim10Flag=0;
 uint8_t tim11Flag=0;
 uint8_t restoreAccumFlag=0;
 /////////////////////////////////////////////////////////

 _RTC rtc = {
     .Year = 21, .Month = 5, .Date = 13,
     .DaysOfWeek = WEDNESDAY,
     .Hour =5, .Min = 59, .Sec = 00
 };

 uint8_t regVal;
 float rtcTemp;

 uint8_t lcdEnableFlag = 0;
 uint8_t adcEnableFlag = 1;

 const uint32_t ds3231TimeUpdateInterval = 500;
 const uint32_t adcUpdateInterval = 500;
 uint8_t lcdUpdateFlag=0;

 const char *formatsShort[] = {
 		"%02d:%02d:%02d  %02d.%02d.20%2d", //0
 		"Atendado        TDS",//1
 		"Concentrate %.1fppm",//2
 		"Permeate %.1fppm   ",//3
 		"Reserved %.2f      ",//4
 		"Membr pres %.2f MPa",//5
 		"Water temp %.2f C  ",//6
        "Feed press %.2f MPa",//7

 		"Feed %.2f l/m       ",//8
 		"Drain %.2f l/m      ",//9
 		"Recycle %.2f l/m    ",//10
 		"Permeate %.2f l/m   ",//11
 		"Membrane %.2f l/m   ",//12
 		"Recycling %.2f%%    ",//13
 		"Permeate %.2f%%     ",//14
 		"     Input states   ",//15
 		"Blue button %u      ",//16
 		"Start %u Stop %u    ",//17
 		"High %u Low %u float",//18
 		"Motion %u BlueB %u  ",//19
 		"En progreso      TDS",//20
 		"Atendado  AUTO   TDS",//21
 		"Atendado  MANUAL TDS",//22
 		"En progreso AUTO TDS",//23
 		"En progreso  MAN TDS",//24
		"lack %u drSw %u M %u",//25
		"Pressure %.2f MPa   ",//26
		"Current %.4f DL     ",//27
		"DebugAdc %u         ",//28
		"Main %.2f l/m       ",//29
		"Cycle %.2f l/m      ",//30
		"Press %.2f MPa      ",//31
		"Volume %.2f L       ",//32
		"Pump temp %.2f      ",//33
		"flag %u sig %u %u   ",//34
		"Ps %u Da %u Lev %u  ",//35
		"Hb %u lb %u         ",//36
		"Hbb %u lbb %u       ",//37
		"Leack %u            ",//38
		"Spent %.5f L        " //39



 };


 char window[20][30] = {
       // 012345678901234567890123456789
		{"00:00:00   0.00.2000"},
		{"  row1              "},
		{"  row2              "},
		{"  row3              "},
	    //{"  row4              "},
		//{"  row5              "},
	    //{"  row6              "},

};

int cint = 10;

float waterLevel=0;
char* waterLevelPtr = (char*)&waterLevel;
uint32_t waterLevelEstimateTime=0;
uint8_t lackLevelSwitch=0;
float pressure=0;
float mainFlow=0;
float mainSpentLitres=0;
uint8_t flagWaterSpent=0;
float cycleFlow=0;
float mainPumpTemp =0;
uint16_t debugAdc =0;
uint8_t drinkWaterSw=0;
uint8_t waterLevelFlag=0;
uint8_t mainPumpState=0;
float currentVfd = 0;
uint8_t blueButton=0;
uint8_t startButtonV=0;
uint8_t stopButtonV=0;
uint8_t moveSensor =0;
uint8_t screenNum=0;
const outPortTypedef outs[5]={

		{.Port = GPIOC, .Pin = GPIO_PIN_0},
		{.Port = GPIOC, .Pin = GPIO_PIN_1},
		{.Port = GPIOC, .Pin = GPIO_PIN_2},
		{.Port = GPIOC, .Pin = GPIO_PIN_3},
		{.Port = GPIOB, .Pin = GPIO_PIN_14}
};

uint8_t toggleFlag (uint8_t flag)
{
if(flag==0){return 1;}else{return 0;}
}

void calcCore(void){

	if (waterLevelEstimateTime ==0) {waterLevel =0;}else{waterLevelEstimateTime--;}
	//waterLevel = getWaterLevel(spiRead[2]);//getWaterLevel(adcAverageValues[2]);
	lackLevelSwitch  = spiRead[3];//inputsStates[3].state;
	float p = mapPressure(spiRead[0]);//getPressureCurrent(adcAverageValues[0],1);
	pressure = p>=0?p:0;
	mainFlow = frequences[0].flow;
	//mainSpentLitres = mainSpentLitres+waterSpent;
	if(waterLevel<750)flagWaterSpent=0;
	if(waterLevel==750 && flagWaterSpent ==0)countWaterSpent=0;flagWaterSpent=1;
	cycleFlow = frequences[1].flow;
	debugAdc = adcAverageValues[1];
	drinkWaterSw = inputsStates[5].state;
	if(waterLevel<-100 || lackLevelSwitch){waterLevelFlag =0;}else{waterLevelFlag=1;} //water level flag
	currentVfd = getCurrentVfd(ampPer);//getCurrentVfd(ampPer);
	if(currentVfd>1.0) {mainPumpState=1;HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET );}else{mainPumpState=0;HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_SET );} //mainPumpState

	blueButton = inputsStates[0].state;

	startButtonV = inputsStates[1].state;
	stopButtonV = inputsStates[2].state;
	moveSensor = inputsStates[motionSensor].state;

}


























