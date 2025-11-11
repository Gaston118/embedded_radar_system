/*
 * sensor.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "../headers/sensor.h"

volatile uint16_t index_buffer_distance = 0;

void SensorInit(void){
	ConfigSensorTimer();
	ConfigSensorECHO();
	ConfigSensorTRIGGER();
}

void SensorTrigger(void){
	static uint32_t last_trigger_time = 0;
	// Evita sobre-disparo (mínimo 60 ms entre mediciones)
	if ((LPC_TIM3->TC - last_trigger_time) < SENSOR_PERIOD)
	    return;
	last_trigger_time = LPC_TIM3->TC;

	// PUEDE SER QUE HAYA QUE MANEJAR EL FLANCO Y CAP COMPLETA ACA.

    GPIO_SetValue(TRIG_PORT, TRIG_MASK);    // Subir pin
    uint32_t start = LPC_TIM3->TC;
    while ((LPC_TIM3->TC - start) < 10);	// 10uS
    GPIO_ClearValue(TRIG_PORT, TRIG_MASK); 	// Bajar pin
}

