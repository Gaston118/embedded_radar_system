/*
 * uart.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_UART_H_
#define HEADERS_UART_H_

#include "lpc17xx_uart.h"
#include <stdio.h>
#include <string.h>
#include "../headers/pcb.h"

#define VREF_MV 3300
#define ADC_MAX_VAL 1023

void UARTInit(void);
void SendValorADC(uint16_t valor);
void SendVelocidadServo(uint16_t valor_adc);
void SendDistancia(uint32_t distancia_cm);

#endif /* HEADERS_UART_H_ */
