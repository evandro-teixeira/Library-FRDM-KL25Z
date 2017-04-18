/*
 * spi.h
 * Author: Evandro
 */
 
#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_
 
//#include "MKL25Z4.h"
//#include "stdbool.h"
#include "externs.h"
 
//#define SPI_0	0
//#define SPI_1	1
#define ALT_0	0
#define ALT_1   1
#define PRESCALE_0	1
#define PRESCALE_1	2
#define PRESCALE_2	3
#define PRESCALE_3	4
#define PRESCALE_4	5
#define PRESCALE_5	6
#define PRESCALE_6	7
#define PRESCALE_7	8
#define DIVISOR_0	2
#define DIVISOR_1	4
#define DIVISOR_2	8
#define DIVISOR_3	16
#define DIVISOR_4	32
#define DIVISOR_5	64
#define DIVISOR_6	128
#define DIVISOR_7	256
#define DIVISOR_8	512
#define CS_AUT		1
#define CS_MAN		0
 
/*
bool spi_init(	bool spi,	// SPI0 ou SPI1
		bool alt,			// SPI0 - PTC ou PTA || SPI1 - PTE ou PTB
		uint8_t pre, 		// Prescale
		uint16_t div,		// Divisor
		bool cs);			// Chip Selet Automatico / Manual
 
bool spi_send(	bool spi,	// SPI0 ou SPI1
		uint8_t data);		// dado a ser enviado
 
uint8_t spi_read(bool spi); // SPI0 ou SPI1
*/

bool spi_Init(SPI_MemMapPtr spi,bool alt,uint8_t pre, uint16_t div,bool cs);
void spi_Send(SPI_MemMapPtr spi,uint8_t data);
uint8_t spi_Read(SPI_MemMapPtr spi);
 
#endif /* SOURCES_SPI_H_ */
