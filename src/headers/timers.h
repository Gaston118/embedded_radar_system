/*
 * timers.h
 *
 *  Created on: 9 nov. 2025
 *      Author: Tomás
 */

#ifndef HEADERS_TIMERS_H_
#define HEADERS_TIMERS_H_

#include "lpc17xx_timer.h"
#include "../headers/servo.h"
#include "../headers/dac.h"
#include "../headers/dma.h"
#include "../headers/uart.h"

void ConfigServoTimer();
void ConfigSensorTimer();
void ConfigDACTimer();

#endif /* HEADERS_TIMERS_H_ */
