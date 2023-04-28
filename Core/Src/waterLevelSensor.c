/*
 * waterLevelSensor.c
 *
 *  Created on: Apr 13, 2021
 *      Author: Marid
 */


#include "waterLevelSensor.h"

    const float Vws=3.3;     // [V]
	const float Rws=180.0; //ohm
	const float rangeWs = 2.0; //m
	const float rangeLitresWs = (750/155)*200; //

/*float getWaterLevel(uint16_t adcValue){


	{
		float VoutWs=adcValue*(Vws/4095.0); // calc for ntc
		float currentWs = VoutWs/Rws;
//return VoutWs;
		return ((rangeLitresWs/0.016)*(currentWs-0.004));//most be current - 0,004 4ma

	}


}*/

float getWaterLevel(uint16_t adcValue){
	if(adcValue<=1020){
		return 0;
	}else{
		return (adcValue-1030)/3.76;
	}
}

