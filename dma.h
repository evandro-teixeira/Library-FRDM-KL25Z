/*
 * dma.h
 *
 *  Created on: 13/02/2018
 *      Author: evandro
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_

#include "MKL25Z4.h"
#include <stdio.h>

#define NUMBER_CHANNEL					4

#define DMA_CHANNEL_0 					0
#define DMA_CHANNEL_1 					1
#define DMA_CHANNEL_2 					2
#define DMA_CHANNEL_3 					3

#define DMA_SIZE_32_BIT					0
#define DMA_SIZE_08_BIT					1
#define DMA_SIZE_16_BIT					2
#define DMA_SIZE_RESERVED				3

#define DMA_DESTINATION_INCREMENT		1
#define DMA_DESTINATION_NO_INCREMENT	0

#define DMA_BUFFER_DISABLED				0
#define DMA_BUFFER_SIZE_16_BYTE			1
#define DMA_BUFFER_SIZE_32_BYTE			2
#define DMA_BUFFER_SIZE_64_BYTE			3
#define DMA_BUFFER_SIZE_128_BYTE		4
#define DMA_BUFFER_SIZE_256_BYTE		5
#define DMA_BUFFER_SIZE_512_BYTE		6
#define DMA_BUFFER_SIZE_1_KBYTE			7
#define DMA_BUFFER_SIZE_2_KBYTE			8
#define DMA_BUFFER_SIZE_4_KBYTE			9
#define DMA_BUFFER_SIZE_8_KBYTE			10
#define DMA_BUFFER_SIZE_16_KBYTE		11
#define DMA_BUFFER_SIZE_32_KBYTE		12
#define DMA_BUFFER_SIZE_64_KBYTE		13
#define DMA_BUFFER_SIZE_128_KBYTE		14
#define DMA_BUFFER_SIZE_256_KBYTE		15

#define DMA_UART0_RECEIVE				2
#define DMA_UART0_TRANSMIT				3
#define DMA_UART1_RECEIVE				4
#define DMA_UART1_TRANSMIT				5
#define DMA_UART2_RECEIVE				6
#define DMA_UART2_TRANSMIT				7
#define DMA_SPI0_RECEIVE				16
#define DMA_SPI0_TRANSMIT				17
#define DMA_SPI1_RECEIVE				18
#define DMA_SPI1_TRANSMIT				19
#define DMA_I2C0						22
#define DMA_I2C1						23
#define DMA_TPM0_CHANNEL_0				24
#define DMA_TPM0_CHANNEL_1				25
#define DMA_TPM0_CHANNEL_2				26
#define DMA_TPM0_CHANNEL_3				27
#define DMA_TPM0_CHANNEL_4				28
#define DMA_TPM0_CHANNEL_5				29
#define DMA_TPM1_CHANNEL_0				32
#define DMA_TPM1_CHANNEL_1				33
#define DMA_TPM1_CHANNEL_2				34
#define DMA_TPM1_CHANNEL_3				35
#define DMA_ADC0						40
#define DMA_CMP0						42
#define DMA_DAC0						45
#define DMA_PTA							49
#define DMA_PTD							52
#define DMA_TPM0_OVERFLOW				54
#define DMA_TPM1_OVERFLOW				55
#define DMA_TPM2_OVERFLOW				56
#define DMA_TSI							57

#define DMA_CONTINUOUSLY_TRANSFERS		0
#define DMA_FORCES_SINGLE				1

typedef struct
{
	uint8_t channel;
	uint8_t number_byte;
	uint8_t channel_source;
	uint32_t *source_address;
	uint32_t *destination_address;
	uint8_t source_size;
	uint8_t destination_size;
	uint8_t destination_increment;
	uint8_t destination_address_modulo;
	uint8_t source_address_modulo;
	uint8_t cycle_steal;
	uint8_t peripheral_request;
	uint8_t start_transfer;
}dma_config_t;

void dma_init(dma_config_t config);

void dma0_callback(void (*task)(void));
void dma1_callback(void (*task)(void));
void dma2_callback(void (*task)(void));
void dma3_callback(void (*task)(void));

#endif /* SOURCES_DMA_H_ */
