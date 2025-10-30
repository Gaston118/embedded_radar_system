/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "headers/servo.h"

int main(void) {

	SystemInit();
	ServoInit();

    while(1) {
    	MoverServo(10, 10000); // PASO = 10us - DELAY = 10ms
    }
    return 0 ;
}
