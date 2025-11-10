/*
 * dma.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_DMA_H_
#define HEADERS_DMA_H_

#define ADC_BUFFER_SIZE 20
#define ADC_BUFFER_START (uint32_t*)0x20080000 //SRAM1
#define muestras ((uint32_t*)ADC_BUFFER_START)

extern volatile uint8_t index_buffer;

void DMAInit(void);

void ConfigDMA(void);

#endif /* HEADERS_DMA_H_ */
