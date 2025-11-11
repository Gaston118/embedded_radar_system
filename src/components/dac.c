/*
 * dac.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "../headers/dac.h"

void DACInit(){
	ConfigDAC(); //Modularizada en pcb.c
	ConfigDACTimer(); //Modularizada en timers.c
}


