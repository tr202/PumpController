/*
 * spiPotenciometr.c
 *
 *  Created on: 13 апр. 2021 г.
 *      Author: Marid
 */

#include "spiPotenciometr.h"


uint8_t data[2] = {17,0};


void setPosition(float pressure){                                // set potenciometr position in range 0.5 - 4,5 v from range 0-1 MPa

	          //data[1]=(uint8_t)(((204.0)*pressure)+25.0);
              data[1]=255;
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_RESET );
		      //osDelay(1);
			  HAL_SPI_Transmit_IT(&hspi2, data, 2);
			  //osDelay(3);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET );


}
