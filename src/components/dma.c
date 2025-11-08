/*
 * dma.c
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#include "lpc17xx_gpdma.h"
#include "../headers/dma.h"

void DMAInit(void){
	ConfigDMA();
}

void ConfigDMA(void) {
    GPDMA_LLI_Type LLI0;
    GPDMA_Init();

    LLI0.SrcAddr = (uint32_t)&(LPC_ADC->ADDR2);
    LLI0.DstAddr = (uint32_t)&(LPC_DAC->DACR);
    LLI0.NextLLI = (uint32_t)&LLI0; // circular
    LLI0.Control = GPDMA_DMACCxControl_TransferSize(1)
                 | GPDMA_DMACCxControl_SWidth(GPDMA_WIDTH_WORD)
                 | GPDMA_DMACCxControl_DWidth(GPDMA_WIDTH_WORD)
                 | GPDMA_DMACCxControl_DI
                 | GPDMA_DMACCxControl_SI
                 | GPDMA_DMACCxControl_I;

    GPDMA_Channel_CFG_Type dmaCfg;
    dmaCfg.ChannelNum = 0;
    dmaCfg.SrcConn = GPDMA_CONN_ADC;
    dmaCfg.DstConn = GPDMA_CONN_DAC;
    dmaCfg.TransferType = GPDMA_TRANSFERTYPE_P2P;
    dmaCfg.TransferSize = 1;
    dmaCfg.TransferWidth = GPDMA_WIDTH_WORD;
    dmaCfg.DMALLI = (uint32_t)&LLI0;

    GPDMA_Setup(&dmaCfg);
    GPDMA_ChannelCmd(0, ENABLE);
}
