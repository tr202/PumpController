/*
 * current.c
 *
 *  Created on: Apr 14, 2021
 *      Author: Marid
 */


#include "current.h"

const float stepCurrent = 3.3/4095;
float voltCurrent =0;

float getCurrentVfd(uint16_t adc){

	voltCurrent = adc*stepCurrent;
	return (voltCurrent / 0.04);


}
