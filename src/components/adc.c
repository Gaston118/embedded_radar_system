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

volatile uint8_t 	new_adc_value = 0;
volatile uint32_t 	adc_value = 0;

void ConfigADC(void){

	// ========== CONFIGURAMOS EINT0 ==========
	ConfigEINT0();

	PINSEL_CFG_Type pincfg = {0};

	// ========== CONFIGURACIÓN DEL PIN ADC (AD0.0 - P0.23) ==========
	pincfg.Portnum 		= 0;
	pincfg.Pinnum 		= 23;
	pincfg.Funcnum 		= 1;  // Función AD0.0
	pincfg.Pinmode 		= PINSEL_PINMODE_TRISTATE;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);

	ADC_Init(LPC_ADC, ADC_FREC);

	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);

	ADC_EdgeStartConfig(LPC_ADC, ADC_START_ON_FALLING);

	ADC_StartCmd(LPC_ADC, ADC_START_ON_EINT0);

	// Habilitar interrupción para el canal 0
	ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);

	NVIC_EnableIRQ(ADC_IRQn);
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
	NVIC_DisableIRQ(EINT0_IRQn);
}

void ADC_IRQHandler(void) {
    // Verificar si la conversión del canal 0 está completa
    if(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_0, ADC_DATA_DONE)) {

        // Leer el valor convertido (esto limpia el flag DONE automáticamente)
        adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0);

        new_adc_value = 1;
    }
}

uint8_t NewValueAdc(void) {
    if(new_adc_value) {
    	new_adc_value = 0;  // Limpiar el flag
        return 1;
    }
    return 0;
}

// Retorna el delta_pw en us para usar en MoverServo()
// ADC = 0    -> paso = 5us  (PASOS PEQUEÑOS, movimiento suave)
// ADC = 2047 -> paso = 25us (PASOS MEDIOS)
// ADC = 4095 -> paso = 50us (PASOS GRANDES, movimiento más brusco)
uint32_t ADC_GetServoStep(void) {
    // Mapeo: ADC (0-4095) -> Paso (5-50 us)
    uint32_t step_us = 5 + ((uint32_t)adc_value * 45) / 4095;

    if(step_us < 5) step_us = 5;    // Mínimo 5us
    if(step_us > 50) step_us = 50;  // Máximo 50us

    return step_us;
}
