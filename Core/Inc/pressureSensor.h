/*
 * pressureSensor.h
 *
 *  Created on: Dec 14, 2020
 *      Author: Marid
 */

#ifndef INC_PRESSURESENSOR_H_
#define INC_PRESSURESENSOR_H_

#include "main.h"



float getPressureCurrent(uint16_t adc, float range);
float mapPressure(uint16_t adc);

#endif /* INC_PRESSURESENSOR_H_ */
