/*
 * uart.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "../headers/uart.h"
#include <stdio.h>  // <-- 1. Necesitas incluir stdio.h para snprintf
#include <string.h> // <-- 2. Necesitas string.h para strlen

// Voltaje de referencia en Milivoltios
#define VREF_MV 3300
#define ADC_MAX_VAL 1023

void UARTInit(void){
	ConfigUART();
}

void SendValorADC(uint16_t valor){

	char buffer[20]; // Búfer para el texto

	// 1. Convertir el valor ADC (0-4095) a milivoltios (0-3300)
    // Usamos 'long long' temporalmente para asegurar que (valor * 3300)
    // no se desborde antes de la división, aunque (4095*3300) cabe en un uint32_t.
	uint32_t milivoltios = ((uint32_t)valor * VREF_MV) / ADC_MAX_VAL;

	// 2. Separar en parte entera (voltios) y fraccional (milivoltios)
	uint32_t voltios_int = milivoltios / 1000;

    // 3. Obtener los dos primeros dígitos de la fracción (para "X.YY V")
	uint32_t voltios_frac_2_digitos = (milivoltios % 1000) / 10;

	// 4. Formatear el texto
    //    %lu     = parte entera
    //    %02lu   = parte fraccional, con un '0' a la izquierda si es necesario
	snprintf(buffer, sizeof(buffer), "%lu.%02lu V\r\n",
             voltios_int,
             voltios_frac_2_digitos);

	// 5. Enviar la cadena de texto por UART
	for (int i = 0; i < strlen(buffer); i++) {
	      while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));
	      UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, buffer[i]);
	  }
}

void SendVelocidadServo(uint16_t valor_adc) {

    char buffer[30]; // Búfer para el texto

    // 1. Mapear el valor del ADC (0-4095) a un porcentaje (0-100)
    //    Usamos uint32_t para asegurar que (valor_adc * 100) no se desborde.
    uint32_t velocidad_pct = ((uint32_t)valor_adc * 100) / 4095;

    // 2. Formatear el texto
    snprintf(buffer, sizeof(buffer), "Velocidad: %lu%%\r\n", velocidad_pct);

    // 3. Enviar la cadena de texto por UART
    for (int i = 0; i < strlen(buffer); i++) {
          while (UART_CheckBusy((LPC_UART_TypeDef *)LPC_UART1));
          UART_SendByte((LPC_UART_TypeDef *)LPC_UART1, buffer[i]);
      }
}
