/*
 * uart.h
 *
 *  Created on: Jul 20, 2016
 *      Author: PDI
 */

#ifndef UART_H_
#define UART_H_

#include "../Drivers/externs.h"

#define UART_BAUD       115200
#define UART_BAUD_1     9600

bool uart_Init(UART_MemMapPtr uart, uint8_t alt, uint32_t baud_rate);
void uart_Put(UART_MemMapPtr uart, uint8_t c);
void uart_String(UART_MemMapPtr uart,char* txt );
uint8_t uart_Get(UART_MemMapPtr uart);
void uart_enable_irq(UART_MemMapPtr uart);
void uart_add_callback(UART_MemMapPtr uart, void (*task)(void));

#endif /* UART_H_ */
