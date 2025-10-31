/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "headers/servo.h"
#include "headers/adc.h"

int main(void) {
	uint32_t delay_ms = 10;   // Velocidad inicial
	uint32_t step_us = 10;    // Paso inicial

	SystemInit();
	ServoInit();
	ConfigADC();

    while(1) {
    	if(NewValueAdc()){
    		step_us = ADC_GetServoStep();
    	}
    	MoverServo(step_us, delay_ms);
    }
    return 0 ;
}
