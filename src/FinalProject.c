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
#include "headers/pcb.h"
#include "stdio.h"



int main(void) {

	SystemInit();
	ServoInit();
	SensorInit();
	ADCInit();
	DMAInit();
	DACInit();

    while(1) {
    	SensorTrigger();
    	//MoverServoCompleto(GetServoStep(), GetServoDelay());
    	__WFI();
    }
    return 0 ;
}
