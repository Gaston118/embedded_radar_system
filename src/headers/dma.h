/*
 * dma.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_DMA_H_
#define HEADERS_DMA_H_

#define ADC_BUFFER_SIZE 	20
#define ADC_BUFFER_START 	0x20080000 //SRAM1
extern volatile uint32_t *muestras;

extern volatile uint8_t index_buffer;

void DMAInit(void);

void ConfigDMA(void);

#endif /* HEADERS_DMA_H_ */
