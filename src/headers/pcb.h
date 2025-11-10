/*
 * pcb.h
 *
 *  Created on: 9 nov. 2025
 *      Author: Tomás
 */

#ifndef HEADERS_PCB_H_
#define HEADERS_PCB_H_

#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "../headers/adc.h"
#include <stdio.h>

void ConfigSERVO(void);
void ConfigEINT0(void);
void ConfigADC1(void);
void ConfigDAC(void);
void ConfigUART(void);

#endif /* HEADERS_PCB_H_ */
