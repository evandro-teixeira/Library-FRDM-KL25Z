/*
 * gpio.h
 *
 *  Created on: 01/10/2016
 *      Author: Evandro
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

//#include "MKL25Z4.h"
/*
#ifndef PORT_PCR_PE(x)
#define PORT_PCR_PE(x) (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PE_SHIFT))&PORT_PCR_PE_MASK)
#endif
#ifndef bool
typedef unsigned char bool;
#endif
*/

#include "externs.h"
/*
#define PORT_A 	0
#define PORT_B 	1
#define PORT_C 	2
#define PORT_D 	3
#define PORT_E 	4
*/
#define OUTPUT 	1
#define INPUT 	0
#define HIGH 	1
#define LOW 	0

#define PULL_RESISTOR 1		// habilita pull resistor
#define NO_PULL_RESISTOR 0

/*
void gpio_direction(uint8_t port, uint8_t pin, uint8_t mode, bool pull_resistor);
void gpio_set(uint8_t port, uint8_t pin, uint8_t value);
void gpio_toggle(uint8_t port, uint8_t pin);
uint16_t gpio_read(uint8_t port, uint8_t pin);
*/

bool gpio_Init(GPIO_MemMapPtr gpio,uint8_t pin, uint8_t mode,bool pull_resistor);
void gpio_Set(GPIO_MemMapPtr gpio,uint8_t pin, uint8_t value);
void gpio_Toggle(GPIO_MemMapPtr gpio,uint8_t pin);
uint8_t gpio_Read(GPIO_MemMapPtr gpio,uint8_t pin);

#endif /* SOURCES_GPIO_H_ */
