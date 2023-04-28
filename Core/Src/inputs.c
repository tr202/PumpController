/*
 * inputs.c
 *
 *  Created on: Apr 8, 2021
 *      Author: Marid
 */

#include "inputs.h"

const uint16_t cycles =100; //number of read input pin cycles to generate inputActiveLevel

const portTypedef ports[6] = {

		{.Pin = UserButton_Pin,   .Port=UserButton_GPIO_Port,      .activePinState = GPIO_PIN_RESET, .inputName = userButton,   .cycles = 100,    },   //0
		{.Pin = startButton_Pin,  .Port =  startButton_GPIO_Port,  .activePinState = GPIO_PIN_RESET, .inputName = startButton,  .cycles = cycles,},    //1
		{.Pin = stopButton_Pin,  .Port =  stopButton_GPIO_Port,   .activePinState = GPIO_PIN_RESET, .inputName = stopButton,  .cycles = cycles,},     //2
		{.Pin = lackLevel_Pin, .Port =  lackLevel_GPIO_Port, .activePinState = GPIO_PIN_SET, .inputName = lackLevel, .cycles = cycles,},             //3
		{.Pin = motionSensor_Pin, .Port =  motionSensor_GPIO_Port, .activePinState = GPIO_PIN_SET,   .inputName = motionSensor, .cycles = cycles,},    //4
		{.Pin = drinkFilterPumpControlSwitch_Pin, .Port =  drinkFilterPumpControlSwitch_GPIO_Port, .activePinState = GPIO_PIN_RESET, .inputName = drinkFilterPumpControlSwitch, .cycles = cycles,}, //5

};

//portTypedef  *portsPtr=ports;

inputStateTypedef inputsStates[6] = {

		{.count=0, .state = (ports[0].activePinState == GPIO_PIN_RESET)? 0:1},
		{.count=0, .state = (ports[1].activePinState == GPIO_PIN_RESET)? 0:1},
		{.count=0, .state = (ports[2].activePinState == GPIO_PIN_RESET)? 0:1},
		{.count=0, .state = (ports[3].activePinState == GPIO_PIN_RESET)? 0:1},
		{.count=0, .state = (ports[4].activePinState == GPIO_PIN_RESET)? 0:1},
		{.count=0, .state = (ports[5].activePinState == GPIO_PIN_RESET)? 0:1},

};

const uint16_t portStateLenght = 6;


uint8_t scanPorts(void)
{
	uint8_t x=0;
	for (uint16_t i=0;i<portStateLenght;i++)
			 {
			 x = (x==0 ? checkPort(ports[i],&inputsStates[i]):1);
			 }
return x;
}

uint8_t checkPort(const portTypedef port, inputStateTypedef* input)
{

	uint8_t updateFlag =0;

		if(HAL_GPIO_ReadPin(port.Port, port.Pin) != port.activePinState)
		{
			input->count=0; if(input->state !=0) {input->state=0; updateFlag=1;}
		}
		else
		{
			if((input->count) >= (port.cycles))
			{
				if(input->state != 1){input->state =1; updateFlag=1;};
			}
			else
				{

				if (input->count < cycles) {input->count++;}
				}
		}

return updateFlag;
}








