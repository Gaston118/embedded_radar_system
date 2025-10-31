/*
 * adc.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#define ADC_FREC 100000 	// 100KHz

void ADCInit(uint8_t modo);

void ConfigADC0(void);

void ConfigADC1(void);

void ConfigEINT0(void);

void SetServoStep(uint32_t step);

uint32_t GetServoStep(void);

uint32_t GetServoDelay(void);

#endif /* HEADERS_ADC_H_ */
