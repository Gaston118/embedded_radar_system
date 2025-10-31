/*
 * sensor.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "../headers/sensor.h"

volatile uint8_t  captura_completa 	= 0;
volatile uint32_t t_start 			= 0;
volatile uint32_t t_end 			= 0;
volatile uint32_t write_index 		= 0;

void SensorInit(void){

}

void ConfigCaptureSensor(void){
	PINSEL_CFG_Type pincfg = {0};
	TIM_TIMERCFG_Type timercfg = {0};
	TIM_CAPTURECFG_Type captureCfg = {0};

	// =========== CONFIGURACION CAP0.0 ===================

	pincfg.Portnum = 1;
	pincfg.Pinnum = 26;
	pincfg.Funcnum = 3; 						// MODE CAPTURE CAP0.0
	pincfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	pincfg.Pinmode = PINSEL_PINMODE_TRISTATE;
	PINSEL_ConfigPin(&pincfg);

	timercfg.PrescaleOption = TIM_PRESCALE_USVAL;
	timercfg.PrescaleValue = 1;
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timercfg);

	captureCfg.CaptureChannel = 0;            	// CAP0.0
	captureCfg.RisingEdge     = ENABLE;
	captureCfg.FallingEdge    = ENABLE;
	captureCfg.IntOnCaption   = ENABLE;       	// Generar interrupción
	TIM_ConfigCapture(LPC_TIM0, &captureCfg);

	NVIC_EnableIRQ(TIMER0_IRQn);

	TIM_Cmd(LPC_TIM0, ENABLE);
}

void TIMER0_IRQHandler(void) {
    if (TIM_GetIntCaptureStatus(LPC_TIM0, 0)) {
        static uint8_t flanco = 1; 	// ENTRAMOS PRIMERO POR SUBIDA

        if (flanco == 1) {
        	t_start = TIM_GetCaptureValue(LPC_TIM0, 0);
        	flanco = 0;
        	captura_completa = 0;
        } else {
        	t_end = TIM_GetCaptureValue(LPC_TIM0, 0);
        	flanco = 1;
        	captura_completa = 1;
        }

        if (captura_completa) {
        	uint32_t distancia = (t_end - t_start) / 58; // DISTANCIA EN cm
        	DIST_BUFFER[write_index] = distancia;

        	write_index++;
        	if (write_index >= BUFFER_SIZE){
        		write_index = 0;
        	}
        }

        TIM_ClearIntCapturePending(LPC_TIM0, 0);
    }
}
