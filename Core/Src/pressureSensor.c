/*
 * pressureSensor.c
 *
 *  Created on: Dec 14, 2020
 *      Author: Marid
 */
#include "pressureSensor.h"

const float Vps=3.3;     // [V]
const float Rps=180; //ohm

const uint16_t adcOn4Ma = 880; // 4 ma 0 mpa
const uint16_t adcOnXMa = 2890; // 13.33 ma 0.6 mpa
const float xMa = 13.33;
const uint8_t range = 1;
const float step = (adcOnXMa-adcOn4Ma)/0.6;//3350 adc's 0,1 mpa

float getPressureCurrent(uint16_t adc, float range) //1 mPa 1,013 bar
{
	float VoutPs=adc*(Vps/4095.0); // calc for ntc
	float currentPs = VoutPs/Rps;
	return ((range/0.016)*(currentPs-0.004));//most be current - 0,004 4ma

}


float mapPressure(uint16_t adc){

	if(adc<=850){
		return 0;
	}else{
		return (adc-850)/3350.0;
	}
}
