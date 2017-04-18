/*
 * uart.h
 *
 *  Created on: Jul 20, 2016
 *      Author: PDI
 */

#ifndef UART_H_
#define UART_H_

#include "externs.h"    

#define UART_BAUD       115200
#define UART_BAUD_1     9600

void uart_Init(UART_MemMapPtr uart, uint8_t alt, uint32_t baud_rate);
void uart_Put(UART_MemMapPtr uart, uint8_t c);
void uart_String(UART_MemMapPtr uart,char* txt );
uint8_t uart_Get(UART_MemMapPtr uart);

#endif /* UART_H_ */
