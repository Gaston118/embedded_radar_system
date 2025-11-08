/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "headers/servo.h"
#include "headers/sensor.h"
#include "headers/adc.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_gpio.h"
#include "headers/dac.h"
#include "headers/dma.h"
#include "stdio.h"

int main(void) {

	SystemInit();
	ServoInit();
	SensorInit();
	ADCInit();
	DMAInit();
	configDAC();

    while(1) {
    	SensorTrigger();
    	//MoverServoCompleto(GetServoStep(), GetServoDelay());
    	MoverServoUnPaso(GetServoStep(), GetServoDelay());
    	uint32_t adc_value = 0;
    	// Leer el valor convertido (esto limpia el flag DONE automáticamente)
    	adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_2);
    	SetServoStep(adc_value);
    	//printf("Distancia: %lu cm\n", GetLastDistance());
    }
    return 0 ;
}
