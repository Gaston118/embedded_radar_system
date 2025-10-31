/*
 * adc.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#define ADC_FREC 100000 	// 100KHz

void ConfigADC(void);
void ConfigEINT0(void);
uint8_t NewValueAdc(void);
uint32_t ADC_GetServoStep(void);

#endif /* HEADERS_ADC_H_ */
