/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "headers/servo.h"
#include "headers/adc.h"

#define MODO_ADC 1 // SELECCIONAR MODO DISPARO ADC 0=BURST, 1=EINT0

int main(void) {

	SystemInit();
	ServoInit();
	ADCInit(MODO_ADC);

    while(1) {
    	MoverServoCompleto(GetServoStep(), GetServoDelay());
    }
    return 0 ;
}
