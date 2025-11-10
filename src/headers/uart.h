/*
 * uart.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_UART_H_
#define HEADERS_UART_H_

#include "lpc17xx_uart.h"
#include "../headers/pcb.h"

void UARTInit(void);
void SendValorADC(void);

#endif /* HEADERS_UART_H_ */
