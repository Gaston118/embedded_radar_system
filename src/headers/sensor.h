/*
 * sensor.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_SENSOR_H_
#define HEADERS_SENSOR_H_

#define BUFFER_SIZE  	10
#define AHB_SRAM0_BASE  0x2007C000
#define DIST_BUFFER   	((volatile uint32_t*)AHB_SRAM0_BASE)
#define ANGLE_BUFFER_ADDR (AHB_SRAM0_BASE + (BUFFER_SIZE * sizeof(uint32_t)))
#define ANGLE_BUFFER    ((volatile uint32_t*)ANGLE_BUFFER_ADDR)

void SensorInit(void);

void ConfigCaptureSensor(void);

void ConfigTimerSensor(void);

void ConfigTriggerGPIO(void);

void SensorTrigger(void);

#endif /* HEADERS_SENSOR_H_ */
