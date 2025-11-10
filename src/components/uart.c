/*
 * uart.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "../headers/uart.h"

void UARTInit(void){
	ConfigUART();
}

void SendValorADC(uint16_t valor){
	// 1. Convertimos la dirección de 'valor' a un puntero a byte (uint8_t*).
	uint8_t *data_ptr = (uint8_t*)&valor;

	// 2. Iteramos 2 veces (ya que sizeof(uint16_t) es 2 bytes).
	for (int i = 0; i < sizeof(uint8_t); i++) {
	      // 3. Espera a que UART1 esté lista para transmitir (busy-wait).
	        // (Casting a LPC_UART_TypeDef* como en tu ejemplo)
	      while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));

	      // 4. Envía el byte actual.
	      // El Cortex-M3 es little-endian, así que esto enviará
	      // primero el byte menos significativo (LSB).
	      UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, data_ptr[i]);
	  }
}
