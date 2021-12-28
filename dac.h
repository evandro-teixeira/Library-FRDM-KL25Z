/*
 * dac.h
 *
 *  Created on: 21/04/2017
 *      Author: evandro
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "../Drivers/externs.h"
//#include "MKL25Z4.h"
//#include "stdbool.h"

void dac_Init(void);
bool dac_Output(uint16_t value);

#endif /* SOURCES_DAC_H_ */
