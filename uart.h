/*
 * uart.h
 *
 *  Created on: Jul 20, 2016
 *      Author: PDI
 */

#ifndef UART_H_
#define UART_H_

#include "externs.h"    

#define POLLING_MODE 	1  
#define UART_MODE 		POLLING_MODE  
#define UART_BAUD       115200
#define CORE_CLK_KHZ    48000

void uart_init (UART_MemMapPtr uartch, int sysclk, int baud);
void uart_putchar (UART_MemMapPtr channel, char ch);
char uart_getchar (UART_MemMapPtr channel); 

#endif /* UART_H_ */