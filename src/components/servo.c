/*
 * servo.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "../headers/servo.h"

volatile uint32_t msTicks = 0;

void ServoInit(void){
	PINSEL_CFG_Type pincfg = {0};

	pincfg.Portnum 		= 0; 	// PUERTO 0
	pincfg.Pinnum 		= 6; 	// P0.6
	pincfg.Funcnum 		= 3; 	// MODE MAT2.0
	pincfg.Pinmode 		= PINSEL_PINMODE_TRISTATE;
	pincfg.OpenDrain 	= 0;
	PINSEL_ConfigPin(&pincfg);	// CONFIGURAMOS MAT2.0 (PWM PARA MOTOR)

	SysTick_Config(SystemCoreClock / 1000); // CONSIDERANDO CLOCK A 100MHz
	ConfigServoTimer();
}

void ConfigServoTimer(void){
	TIM_TIMERCFG_Type timercfg = {0};
	TIM_MATCHCFG_Type matchcfg = {0};

	timercfg.PrescaleOption = TIM_PRESCALE_USVAL;
	timercfg.PrescaleValue = 1; // 1 us
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timercfg);

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

	LPC_TIM2->EMR &= ~(1 << 0); // Iniciar MAT2.0 en bajo
	NVIC_EnableIRQ(TIMER2_IRQn);
	TIM_Cmd(LPC_TIM2, ENABLE);
}

void ServoSetPulse(uint32_t pw){
	if(pw < SERVO_PW_MIN) pw = SERVO_PW_MIN;
	if(pw > SERVO_PW_MAX) pw = SERVO_PW_MAX;
	TIM_UpdateMatchValue(LPC_TIM2, 1, pw);
}

void MoverServo(uint32_t delta_pw, uint32_t d_ms){
	for(uint32_t pw = SERVO_PW_MIN; pw <= SERVO_PW_MAX; pw = pw + delta_pw){
		ServoSetPulse(pw);
		delay_ms(d_ms);
	}
	for (int32_t pw = SERVO_PW_MAX; pw >= (int32_t)SERVO_PW_MIN; pw = pw - delta_pw){
		ServoSetPulse(pw);
		delay_ms(d_ms);
	}
}

void delay_ms(uint32_t ms) {
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}

void SysTick_Handler(void) {
	// SysTick Handler: incrementa cada 1 ms CONSIDERANDO CLOCK 100MHz
    msTicks++;
}

void TIMER2_IRQHandler(void){
	if(TIM_GetIntStatus(LPC_TIM2, TIM_MR1_INT)){ // INTERRRUPCION DE MAT2.1
		TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);

		LPC_TIM2->EMR &= ~(1 << 0); // BAJO MAT2.0
	}
}
