/*
 * timers.c
 *
 *  Created on: 9 nov. 2025
 *      Author: Tomás
 */

#include "../headers/timers.h"

// --------------------------------- TIMER 0 - DAC -----------------------------------------------
// ------------------------------------------------------------------------------------------------------
void ConfigDACTimer(){
	TIM_TIMERCFG_Type timercfg0 = {0};
	TIM_MATCHCFG_Type matchcfg = {0};

	timercfg0.PrescaleOption = TIM_PRESCALE_USVAL;
	timercfg0.PrescaleValue = 1000; // 1 ms
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timercfg0);

	// MAT0.0 DEFINIDO POR EL PERIODO, ES EL QUE SE PONE EN ALTO.
	matchcfg.MatchChannel = 0;
	matchcfg.IntOnMatch = ENABLE;
	matchcfg.ResetOnMatch = ENABLE;
	matchcfg.StopOnMatch = DISABLE;
	matchcfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchcfg.MatchValue = DAC_REFRESH_RATE;
	TIM_ConfigMatch(LPC_TIM0, &matchcfg);
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIM_Cmd(LPC_TIM0, ENABLE);
	NVIC_SetPriority(TIMER0_IRQn, 2);
}

void TIMER0_IRQHandler(void){
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)){
		TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
		uint32_t valor_bruto = muestras[index_buffer];
		uint32_t valor = (valor_bruto >> 4) & 0xFFF;
		uint32_t valor_to_dac = valor >> 2;

		DAC_UpdateValue(LPC_DAC, valor_to_dac);
		SendValorADC((uint16_t)valor_to_dac);
		SendVelocidadServo((uint16_t)valor);
		index_buffer++;
		if (index_buffer >= ADC_BUFFER_SIZE){
		index_buffer = 0;
		}
	}
}

// --------------------------------- TIMER 2 - SERVOMOTOR -----------------------------------------------
// ------------------------------------------------------------------------------------------------------
void ConfigServoTimer(void){
	TIM_TIMERCFG_Type timercfg2 = {0};
	TIM_MATCHCFG_Type matchcfg = {0};

	timercfg2.PrescaleOption = TIM_PRESCALE_USVAL;
	timercfg2.PrescaleValue = 1; // 1 us
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timercfg2);

	// MAT2.0 DEFINIDO POR EL PERIODO, ES EL QUE SE PONE EN ALTO.
	matchcfg.MatchChannel = 0;
	matchcfg.IntOnMatch = DISABLE;
	matchcfg.ResetOnMatch = ENABLE;
	matchcfg.StopOnMatch = DISABLE;
	matchcfg.ExtMatchOutputType = TIM_EXTMATCH_HIGH;
	matchcfg.MatchValue = SERVO_PULSE_CYCLE; // 20k us = 20 ms
	TIM_ConfigMatch(LPC_TIM2, &matchcfg);

	// MAT2.1 DEFINIDO POR EL DUTY CYCLE, ES EL QUE SE PONE EN BAJO.
	matchcfg.MatchChannel = 1;
	matchcfg.IntOnMatch = ENABLE;
	matchcfg.ResetOnMatch = DISABLE;
	matchcfg.StopOnMatch = DISABLE;
	matchcfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchcfg.MatchValue = SERVO_PW_CENTER;
	TIM_ConfigMatch(LPC_TIM2, &matchcfg);


	// MAT2.2 SE ENCARGA DE MOVER EL SERVO LLAMANDO A LAS FUNCIONES CORRESPONDIENTES.
	matchcfg.MatchChannel = 2;
	matchcfg.IntOnMatch = DISABLE;
	matchcfg.ResetOnMatch = DISABLE;
	matchcfg.StopOnMatch = DISABLE;
	matchcfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchcfg.MatchValue = 10000;
	TIM_ConfigMatch(LPC_TIM2, &matchcfg);

	LPC_TIM2->EMR &= ~(1 << 0); // Iniciar MAT2.0 en bajo
	NVIC_EnableIRQ(TIMER2_IRQn);
	TIM_Cmd(LPC_TIM2, ENABLE);
	NVIC_SetPriority(TIMER2_IRQn, 0);
}

void TIMER2_IRQHandler(void){
	if(TIM_GetIntStatus(LPC_TIM2, TIM_MR2_INT)){ // INTERRUPCIÓN DE MAT2.2
		TIM_ClearIntPending(LPC_TIM2, TIM_MR2_INT);
		//MoverServoUnPaso(GetServoStep(), GetServoDelay());
	}
	if(TIM_GetIntStatus(LPC_TIM2, TIM_MR1_INT)){ // INTERRRUPCION DE MAT2.1
		TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);
		LPC_TIM2->EMR &= ~(1 << 0); // BAJO MAT2.0
	}
}

// ------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------
