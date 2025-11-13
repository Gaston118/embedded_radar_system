/*
 * adc.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_adc.h"
#include "../headers/adc.h"
#include "stdio.h"

volatile uint32_t servo_step_us 	= 10;    	// Paso inicial
volatile uint32_t servo_delay_ms 	= 10;   	// Velocidad inicial

void ADCInit(){
	ConfigADC1();
	ConfigEINT0(); // MODO EINT0, funciones modularizadas en pcb.c
}

//void ADC_IRQHandler(void) {
//    // Verificar si la conversión del canal 0 está completa
//    if(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_2, ADC_DATA_DONE)) {
//    	uint32_t adc_value = 0;
//        // Leer el valor convertido (esto limpia el flag DONE automáticamente)
//        adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_2);
//        printf("ADC\n");
//        SetServoStep(adc_value);
//        LPC_ADC->ADGDR; //Lectura de bandera de status para sincronizar.
//    }
//}

void SetServoStep(uint32_t adc_value) {
	uint32_t step_us = 10 + ((uint32_t)adc_value * 45) / 4095;

	if(step_us < 10) step_us = 10;  // Mínimo 10us
	if(step_us > 50) step_us = 50;  // Máximo 50us

	servo_step_us = step_us;
}

uint32_t GetServoStep(void){
	//printf("Step: %lu\n", servo_step_us);
	return servo_step_us;
}

uint32_t GetServoDelay(void){
	return servo_delay_ms;
}
