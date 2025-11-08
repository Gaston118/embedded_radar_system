/*
 * dac.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "../headers/dac.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"

void configDAC(){
	PINSEL_CFG_Type cfgpin = {0};
	DAC_CONVERTER_CFG_Type dacConfig = {0};
	dacConfig.DBLBUF_ENA = SET;
	dacConfig.CNT_ENA = SET;
	dacConfig.DMA_ENA = SET;

	cfgpin.Portnum = 0;
	cfgpin.Pinnum = 26;
	cfgpin.Funcnum = 2;
	cfgpin.Pinmode = PINSEL_PINMODE_TRISTATE;
	cfgpin.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&cfgpin);

	DAC_Init(LPC_DAC);
	DAC_SetBias(LPC_DAC, 1);
	DAC_SetDMATimeOut(LPC_DAC, 2500);
	DAC_ConfigDAConverterControl(LPC_DAC, &dacConfig);


}
