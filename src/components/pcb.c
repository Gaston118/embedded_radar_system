/*
 * pcb.c
 *
 *  Created on: 9 nov. 2025
 *      Author: Tomás
 */

#include "../headers/pcb.h"

void ConfigSERVO(){
	PINSEL_CFG_Type pincfg = {0};

	pincfg.Portnum 		= 0;
	pincfg.Pinnum 		= 6; 	// P0.6 como MAT2.0 para salida a servo
	pincfg.Funcnum 		= 3; 	// MODE MAT2.0
	pincfg.Pinmode 		= PINSEL_PINMODE_TRISTATE;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);	// CONFIGURAMOS MAT2.0 (PWM PARA MOTOR)
}

void ConfigADC1(void){
	PINSEL_CFG_Type pincfg = {0};

	// ========== CONFIGURACIÓN DEL PIN ADC (AD0.0 - P0.23) ==========
	pincfg.Portnum 		= 0;
	pincfg.Pinnum 		= 25; //P0.25 como ADC
	pincfg.Funcnum 		= 1;  // Función AD0.2
	pincfg.Pinmode 		= 0;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);
	ADC_Init(LPC_ADC, ADC_FREC);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE);
	ADC_BurstCmd(LPC_ADC, ENABLE);
	//Habilitar interrupción para el canal 0
	//ADC_IntConfig(LPC_ADC, ADC_ADINTEN2, ENABLE);
	//ADC_PowerdownCmd(LPC_ADC, 0);
	//NVIC_EnableIRQ(ADC_IRQn);
}

void ConfigEINT0(void){
	PINSEL_CFG_Type pincfg = {0};
	EXTI_InitTypeDef exticfg = {0};

	// ========== CONFIGURACIÓN DEL PIN EINT0 (P2.10) ==========
	pincfg.Portnum 		= 2;
	pincfg.Pinnum 		= 10; // P2.10 como EINT0
	pincfg.Funcnum 		= 1;  // Función EINT0
	pincfg.Pinmode 		= PINSEL_PINMODE_PULLUP;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);

	EXTI_Init();

	exticfg.EXTI_Line = EXTI_EINT0;  					// EINT0
	exticfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;  		// Sensible a flancos
	exticfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;  // Flanco descendente
	EXTI_Config(&exticfg);

	// NO habilitamos la interrupción de EINT0 en el NVIC
	// porque solo queremos usarla para disparar el ADC
	NVIC_EnableIRQ(EINT0_IRQn);
}

void ConfigDAC(){
	PINSEL_CFG_Type cfgpin = {0};

	cfgpin.Portnum = 0;
	cfgpin.Pinnum = 26; // P0.26 como AOUT/DAC
	cfgpin.Funcnum = 2;
	cfgpin.Pinmode = PINSEL_PINMODE_TRISTATE;
	cfgpin.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&cfgpin);

	DAC_Init(LPC_DAC);
	DAC_SetBias(LPC_DAC, 1);
}

void ConfigUART(void) {
    PINSEL_CFG_Type pincfg;
    pincfg.Funcnum = 1;
    pincfg.Portnum = 0;
    pincfg.Pinnum = 15;  // P0.15 como TXD1

    PINSEL_ConfigPin(&pincfg);

    UART_CFG_Type uartcfg;

    // Configuración de la velocidad de transmisión y otros parámetros de UART
    uartcfg.Baud_rate = 9600;
    uartcfg.Databits = UART_DATABIT_8;
    uartcfg.Parity = UART_PARITY_NONE;
    uartcfg.Stopbits = UART_STOPBIT_1;

    // Inicializar UART1 con la configuración especificada (casting a LPC_UART_TypeDef*)
    UART_Init((LPC_UART_TypeDef *)LPC_UART1, &uartcfg);

    // Habilitar la transmisión UART (casting a LPC_UART_TypeDef*)
    UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1, ENABLE);
}

void EINT0_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    // ADC_StartCmd(LPC_ADC,ADC_START_NOW);
    printf("EINT0\n");
}

