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

	char buffer[20];

	uint32_t milivoltios = ((uint32_t)valor * VREF_MV) / ADC_MAX_VAL;

	uint32_t voltios_int = milivoltios / 1000;

	uint32_t voltios_frac_2_digitos = (milivoltios % 1000) / 10;

	snprintf(buffer, sizeof(buffer), "%lu.%02lu V\r\n",
             voltios_int,
             voltios_frac_2_digitos);

	for (int i = 0; i < strlen(buffer); i++) {
	      while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));
	      UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, buffer[i]);
	  }
}

void SendVelocidadServo(uint16_t valor_adc) {

    char buffer[30];

    uint32_t velocidad_pct = ((uint32_t)valor_adc * 100) / 4095;

    snprintf(buffer, sizeof(buffer), "Velocidad: %lu%%\r\n", velocidad_pct);

    for (int i = 0; i < strlen(buffer); i++) {
          while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));
          UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, buffer[i]);
      }
}

void SendDistancia(uint32_t distancia_cm) {

    char buffer[30];

    snprintf(buffer, sizeof(buffer), "Distancia: %lu cm\r\n", distancia_cm);

    for (int i = 0; i < strlen(buffer); i++) {
          while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));
          UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, buffer[i]);
      }
}
