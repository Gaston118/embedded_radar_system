/*
 * sensor.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "../headers/sensor.h"

#define TRIG_PORT       0
#define TRIG_PIN        17
#define TRIG_PIN_MASK   ((uint32_t)(1 << TRIG_PIN))

volatile uint8_t  captura_completa  = 1;
volatile uint8_t  captura_flag  	= 0;
volatile uint32_t t_start           = 0;
volatile uint32_t t_end             = 0;
volatile uint32_t write_index       = 0;

void SensorInit(void){
    ConfigCaptureSensor();
    ConfigTriggerGPIO();
}

void ConfigCaptureSensor(void){
    PINSEL_CFG_Type pincfg = {0};
    TIM_TIMERCFG_Type timercfg = {0};
    TIM_CAPTURECFG_Type captureCfg = {0};

    // =========== CONFIGURACION CAP3.1 ===================

    pincfg.Portnum = 0;
    pincfg.Pinnum = 24;
    pincfg.Funcnum = 3;                         // MODE CAPTURE CAP3.1
    pincfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    pincfg.Pinmode = PINSEL_PINMODE_PULLDOWN;
    PINSEL_ConfigPin(&pincfg);

    timercfg.PrescaleOption = TIM_PRESCALE_USVAL;
    timercfg.PrescaleValue = 1;
    TIM_Init(LPC_TIM3, TIM_TIMER_MODE, &timercfg);

    captureCfg.CaptureChannel = 1;              // CAP3.1
    captureCfg.RisingEdge     = ENABLE;
    captureCfg.FallingEdge    = ENABLE;
    captureCfg.IntOnCaption   = ENABLE;
    TIM_ConfigCapture(LPC_TIM3, &captureCfg);

    NVIC_EnableIRQ(TIMER3_IRQn);
    NVIC_SetPriority(TIMER3_IRQn, 3);

    TIM_Cmd(LPC_TIM3, ENABLE);
}

void ConfigTriggerGPIO(void){
    PINSEL_CFG_Type pincfg = {0};

    // P0.10 como GPIO
    pincfg.Portnum = TRIG_PORT;
    pincfg.Pinnum = TRIG_PIN;
    pincfg.Funcnum = 0;                         // GPIO
    pincfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    pincfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    PINSEL_ConfigPin(&pincfg);

    GPIO_SetDir(TRIG_PORT, TRIG_PIN_MASK, 1);  // Salida
    GPIO_ClearValue(TRIG_PORT, TRIG_PIN_MASK); // Iniciar en bajo
}

void SensorTrigger(void){
    GPIO_SetValue(TRIG_PORT, TRIG_PIN_MASK);    // Subir pin

    // Delay 10us usando Timer3 que ya está corriendo
    uint32_t start = LPC_TIM3->TC;
    while ((LPC_TIM3->TC - start) < 100);

    GPIO_ClearValue(TRIG_PORT, TRIG_PIN_MASK); // Bajar pin
}

void TIMER3_IRQHandler(void) {
    if (TIM_GetIntCaptureStatus(LPC_TIM3, 1)) {
        static uint8_t flanco = 1;              // ENTRAMOS PRIMERO POR SUBIDA

        if (flanco == 1) {
            t_start = TIM_GetCaptureValue(LPC_TIM3, 1);
            flanco = 0;
            captura_completa = 0;
        } else {
            t_end = TIM_GetCaptureValue(LPC_TIM3, 1);
            flanco = 1;
            captura_completa = 1;
            captura_flag	 = 1;
        }

        if (captura_completa) {
            uint32_t distancia = (t_end - t_start) / 58; // DISTANCIA EN cm
            DIST_BUFFER[write_index] = distancia;

            write_index++;
            if (write_index >= BUFFER_SIZE){
                write_index = 0;
            }
        }

        TIM_ClearIntCapturePending(LPC_TIM3, 1);
    }
}

void SetCapFlag(uint8_t valor){
	captura_flag = valor;
}

uint8_t GetCapFlag(void){
	return captura_flag;
}

uint32_t GetLastDistance(void){
	return DIST_BUFFER[write_index];
}
