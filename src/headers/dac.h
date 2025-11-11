/*
 * dac.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */
#ifndef HEADERS_DAC_H_
#define HEADERS_DAC_H_

#include "lpc17xx_dac.h"
#include "../headers/timers.h"
#include "../headers/pcb.h"

#define DAC_REFRESH_RATE 5000

void DACInit(void);

#endif /* HEADERS_DAC_H_ */
