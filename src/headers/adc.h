/*
 * adc.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#include "../headers/pcb.h"

#define ADC_FREC 10000

void ADCInit(void);

void SetServoStep(uint32_t step);

uint32_t GetServoStep(void);

uint32_t GetServoDelay(void);

#endif /* HEADERS_ADC_H_ */
