/*
 * pcb.c
 *
 *  Created on: 9 nov. 2025
 *      Author: Tomás
 */

#include "../headers/pcb.h"

volatile uint16_t index = 0;

const uint16_t simulacion_echo_us[200] = {
    // --- TRAMO 1: Objeto a 20 cm (1160 us) | 67 muestras ---
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
    1160, 1160, 1160, 1160, 1160, 1160, 1160, // Fin de las 67 muestras

    // --- TRAMO 2: Objeto a 6 cm (348 us) | 20 muestras ---
    348, 348, 348, 348, 348, 348, 348, 348, 348, 348,
    348, 348, 348, 348, 348, 348, 348, 348, 348, 348,

    // --- TRAMO 3: Objeto a 15cm (870 us) | 40 muestras ---
	870, 870, 870, 870, 870, 870, 870, 870, 870, 870,
	870, 870, 870, 870, 870, 870, 870, 870, 870, 870,
	870, 870, 870, 870, 870, 870, 870, 870, 870, 870,
	870, 870, 870, 870, 870, 870, 870, 870, 870, 870,

    // --- TRAMO 4: Objeto a 11 cm (638 us) | 73 muestras restantes ---
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638, 638, 638, 638, 638, 638, 638, 638,
    638, 638, 638 // Fin de las 73 muestras
};

void configGPIO(void){
	// P0.6 COMO GPIO
	PINSEL_CFG_Type pincfg = {0};

	pincfg.Portnum 		= 0;
	pincfg.Pinnum 		= 6; // P2.10 como gpio
	pincfg.Funcnum 		= 0;  // Función gpio
	pincfg.Pinmode 		= PINSEL_PINMODE_TRISTATE;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);
	GPIO_SetDir(0, (1 << 6), 1);
	GPIO_ClearValue(0, (1 << 6));
}

void ConfigEINT0(void){
	PINSEL_CFG_Type pincfg = {0};
	EXTI_InitTypeDef exticfg = {0};

	// ========== CONFIGURACIÓN DEL PIN EINT0 (P2.10) ==========
	pincfg.Portnum 		= 2;
	pincfg.Pinnum 		= 10; // P2.10 como EINT0
	pincfg.Funcnum 		= 1;  // Función EINT0
	pincfg.Pinmode 		= PINSEL_PINMODE_PULLDOWN;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);

	EXTI_Init();

	exticfg.EXTI_Line = EXTI_EINT0;  					// EINT0
	exticfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;  		// Sensible a flancos
	exticfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;  // Flanco descendente
	EXTI_Config(&exticfg);

	NVIC_EnableIRQ(EINT0_IRQn);
}

void ConfigTIMER0(void){
	TIM_TIMERCFG_Type timer;
	TIM_MATCHCFG_Type match;

	timer.PrescaleOption = TIM_PRESCALE_USVAL;
	timer.PrescaleValue = 1;

	match.MatchChannel = 0;
	match.IntOnMatch = ENABLE;
	match.ResetOnMatch = ENABLE;
	match.StopOnMatch = ENABLE;
	match.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	match.MatchValue = 0;

	TIM_ConfigMatch(LPC_TIM0, &match);
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&timer);
	NVIC_EnableIRQ(TIMER0_IRQn);

}

void TIMER0_IRQHandler(void){
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)){
		TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
		GPIO_ClearValue(0, (1 << 6));
	}
}
void EINT0_IRQHandler(void) {
    EXTI_ClearEXTIFlag(EXTI_EINT0);
    TIM_UpdateMatchValue(LPC_TIM0, 0,simulacion_echo_us[index]);
    index++;
    if(index == 200){
    	index = 0;
    }
    TIM_ResetCounter(LPC_TIM0);
    TIM_Cmd(LPC_TIM0, ENABLE);
    GPIO_SetValue(0, (1 << 6));
}

