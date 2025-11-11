/*
 * dma.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_gpdma.h"
#include "../headers/dma.h"

volatile uint8_t index_buffer = 0;
volatile uint32_t *muestras = (volatile uint32_t *) ADC_BUFFER_START;

void DMAInit(void){
	ConfigDMA();
}

void ConfigDMA(void) {
	    static GPDMA_LLI_Type LLI0 = {0};
	    GPDMA_Init();

	    LLI0.SrcAddr = (uint32_t)&(LPC_ADC->ADDR2);
	    LLI0.DstAddr = (uint32_t)muestras;
	    LLI0.NextLLI = (uint32_t)&LLI0; // circular
	    LLI0.Control = (ADC_BUFFER_SIZE << 0)  // tamaño de la transferencia
	                 | (2 << 18)               // Ancho origen (32 bits)
	                 | (2 << 21)               // Ancho destino (32 bits)
	                 | (1 << 27)               // Incrementar destino
	                 | (1 << 31);              // Terminal count interrupt


	    GPDMA_Channel_CFG_Type dmaCfg;
	    dmaCfg.ChannelNum = 0;
	    dmaCfg.SrcConn = GPDMA_CONN_ADC;
	    dmaCfg.DstConn = 0;
	    dmaCfg.SrcMemAddr = 0;
	    dmaCfg.DstMemAddr = (uint32_t)muestras;
	    dmaCfg.TransferType = GPDMA_TRANSFERTYPE_P2M;
	    dmaCfg.TransferWidth = 0;
	    dmaCfg.DMALLI = (uint32_t)&LLI0;

	    GPDMA_Setup(&dmaCfg);

	    GPDMA_ChannelCmd(0, ENABLE);
}
