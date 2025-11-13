/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "lpc17xx_adc.h"

#include "headers/servo.h"
#include "headers/sensor.h"
#include "headers/adc.h"
#include "headers/dac.h"
#include "headers/dma.h"
#include "headers/pcb.h"

int main(void) {

	SystemInit();
	ServoInit();
	SensorInit();
	ADCInit();
	DMAInit();
	DACInit();
	UARTInit();

    while(1) {
    	MoverServoUnPaso(GetServoStep(), GetServoDelay());
    	uint32_t adc_value = 0;
    	adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_2);
    	SetServoStep(adc_value);
    }
    return 0 ;
}
