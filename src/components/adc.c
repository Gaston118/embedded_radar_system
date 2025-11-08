/*
 * adc.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "../headers/adc.h"
#include "stdio.h"

volatile uint32_t servo_step_us 	= 40;    	// Paso inicial
volatile uint32_t servo_delay_ms 	= 10;   	// Velocidad inicial

void ADCInit(){
	ConfigADC1(); // MODO EINT0
}

void ConfigADC1(void){

	// ========== CONFIGURAMOS EINT0 ==========
	ConfigEINT0();

	PINSEL_CFG_Type pincfg = {0};

	// ========== CONFIGURACIÓN DEL PIN ADC (AD0.0 - P0.23) ==========
	pincfg.Portnum 		= 0;
	pincfg.Pinnum 		= 25;
	pincfg.Funcnum 		= 1;  // Función AD0.2
	pincfg.Pinmode 		= 0;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);
	ADC_Init(LPC_ADC, ADC_FREC);
	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_2, ENABLE);
	ADC_BurstCmd(LPC_ADC, ENABLE);
	// Habilitar interrupción para el canal 0
	ADC_IntConfig(LPC_ADC, ADC_ADINTEN2, DISABLE);
	//ADC_PowerdownCmd(LPC_ADC, 0);
	//NVIC_EnableIRQ(ADC_IRQn);
}

void ConfigEINT0(void){
	PINSEL_CFG_Type pincfg = {0};
	EXTI_InitTypeDef exticfg = {0};

	// ========== CONFIGURACIÓN DEL PIN EINT0 (P2.10) ==========
	pincfg.Portnum 		= 2;
	pincfg.Pinnum 		= 10;
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

void ADC_IRQHandler(void) {
    // Verificar si la conversión del canal 0 está completa
    if(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_2, ADC_DATA_DONE)) {
    	uint32_t adc_value = 0;
        // Leer el valor convertido (esto limpia el flag DONE automáticamente)
        adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_2);
        printf("ADC\n");
        SetServoStep(adc_value);
        LPC_ADC->ADGDR;
    }
}

void EINT0_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    //ADC_StartCmd(LPC_ADC,ADC_START_NOW);

    printf("EINT0\n");
}

void SetServoStep(uint32_t adc_value) {
	uint32_t step_us = 5 + ((uint32_t)adc_value * 35) / 4095;

	if(step_us < 5) step_us = 5;    // Mínimo 5us
	if(step_us > 40) step_us = 40;  // Máximo 50us

	servo_step_us = step_us;
}

uint32_t GetServoStep(void){
	//printf("Step: %lu\n", servo_step_us);
	return servo_step_us;
}

uint32_t GetServoDelay(void){
	return servo_delay_ms;
}
