/*
 *
 */

// Includes
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "headers/pcb.h"
#include "stdio.h"

/* * Array de simulación de tiempos de Echo.
 * Total de muestras: 200
 * Unidad: Microsegundos (us)
 * Lógica: Tiempo = Distancia * 58
 */

int main(void) {
	ConfigEINT0();
	ConfigTIMER0();

    while(1) {
    	__WFI;
    }
    return 0 ;
}
