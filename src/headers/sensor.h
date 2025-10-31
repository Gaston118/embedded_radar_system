/*
 * sensor.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_SENSOR_H_
#define HEADERS_SENSOR_H_

#define BUFFER_SIZE  	256    		 // N muestras guardadas
#define AHB_SRAM0_BASE  0x2007C000
#define TRIGGER_PULSE 	10 			// 10 us
#define NEXT_TRIGGER_IN 10000		// 10 ms
#define DIST_BUFFER   	((volatile uint32_t*)AHB_SRAM0_BASE)

void SensorInit(void);

void ConfigCaptureSensor(void);

void ConfigTimerSensor(void);


#endif /* HEADERS_SENSOR_H_ */
