/*
 * servo.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "../headers/servo.h"
#include "../headers/sensor.h"

volatile uint32_t angulo = 0;
volatile uint32_t ms_ticks = 0;

void ServoInit(void){
	ConfigSERVO();
	SysTick_Config(SystemCoreClock / 1000); // CONSIDERANDO CLOCK A 100MHz
	ConfigServoTimer();
}

void ServoSetPulse(uint32_t pw){
	if(pw < SERVO_PW_MIN) pw = SERVO_PW_MIN;
	if(pw > SERVO_PW_MAX) pw = SERVO_PW_MAX;
	TIM_UpdateMatchValue(LPC_TIM2, 1, pw);
}

// FUNCION PARA MOVER EL SERVO QUE HACE UN BARRIDO COMPLETO
void MoverServoCompleto(uint32_t delta_pw, uint32_t d_ms){
	for(uint32_t pw = SERVO_PW_MIN; pw <= SERVO_PW_MAX; pw = pw + delta_pw){
		ServoSetPulse(pw);
		ServoSetAngulo(pw);
		SensorTrigger();
		DelayMs(d_ms);
	}
	for (int32_t pw = SERVO_PW_MAX; pw >= (int32_t)SERVO_PW_MIN; pw = pw - delta_pw){
		ServoSetPulse(pw);
		ServoSetAngulo(pw);
		SensorTrigger();
		DelayMs(d_ms);
	}
}

// FUNCION PARA MOVER EL SERVO DE A UN PASO
void MoverServoUnPaso(uint32_t step_us, uint32_t d_ms){
    static int32_t pw_us = SERVO_PW_CENTER;
    static int     dir   = +1;
    static uint32_t last_time = 0;

    if (step_us == 0) return;

    if((ms_ticks - last_time) < d_ms) {
        return;
    }
    last_time = ms_ticks;

    int32_t next = pw_us + (int32_t)step_us * dir;

    if (next >= (int32_t)SERVO_PW_MAX) {
        next = SERVO_PW_MAX;
        dir  = -1;
    } else if (next <= (int32_t)SERVO_PW_MIN) {
        next = SERVO_PW_MIN;
        dir  = +1;
    }

    pw_us = next;
    ServoSetPulse((uint32_t)pw_us);
}

void DelayMs(uint32_t ms) {
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < ms);
}

void SysTick_Handler(void) {
	// SysTick Handler: incrementa cada 1 ms CONSIDERANDO CLOCK 100MHz
    ms_ticks++;
}

uint32_t ServoGetAngulo(void) {
	return angulo;
}

void ServoSetAngulo(uint32_t pw_us){
	long angulo_calculado = (((long)pw_us - (long)SERVO_PW_MIN) * 180L) / ((long)SERVO_PW_MAX - (long)SERVO_PW_MIN);

	if (angulo_calculado < 0)   angulo = 0	;
	if (angulo_calculado > 180) angulo = 180;

	angulo = angulo_calculado;
}

