/*
 * inputs.h
 *
 *  Created on: Apr 8, 2021
 *      Author: Marid
 */

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_

#include "main.h"

#define userButton 0
#define startButton 1
#define stopButton 2
#define lackLevel 3
#define motionSensor 4
#define drinkFilterPumpControlSwitch 5



typedef struct
{
GPIO_TypeDef* Port;
uint16_t Pin;
uint16_t cycles;
GPIO_PinState activePinState;
uint8_t inputName;
} portTypedef;

typedef struct
{
uint16_t count;
uint8_t state;
} inputStateTypedef;



const uint16_t cycles; //number of read input pin cycles to generate inputActiveLevel

const portTypedef ports[6];
extern inputStateTypedef inputsStates[6];
const uint16_t portStateLenght;


uint8_t scanPorts(void);
uint8_t checkPort(const portTypedef port, inputStateTypedef* input);




#endif /* INC_INPUTS_H_ */
