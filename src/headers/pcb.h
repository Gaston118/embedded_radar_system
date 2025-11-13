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
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include <stdio.h>

void ConfigTIMER0(void);
void ConfigEINT0(void);

#endif /* HEADERS_PCB_H_ */
