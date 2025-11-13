/*
 * sensor.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_SENSOR_H_
#define HEADERS_SENSOR_H_

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "../headers/pcb.h"
#include "../headers/timers.h"

extern volatile uint16_t index_buffer_distance;

#define BUFFER_SIZE  	256    		 // N muestras guardadas
#define AHB_SRAM0_BASE  0x2007C000
#define DIST_BUFFER   	((volatile uint32_t*)AHB_SRAM0_BASE)
#define TRIG_PORT       0
#define TRIG_PIN        0
#define TRIG_MASK   	(1 << TRIG_PIN)
#define SENSOR_PERIOD 	60000

void SensorInit(void);
void SensorTrigger(void);

#endif /* HEADERS_SENSOR_H_ */
