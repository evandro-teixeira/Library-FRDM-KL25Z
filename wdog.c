/*
 * wdog.h
 *
 *  Created on: set 30, 2018
 *      Author: Evandro Teixeira
 */
#include "wdog.h"

void wdog_Init(COPC_config_t *config)
{
	SIM_COPC = (SIM_COPC_COPW(config->timeout)) |
			   (SIM_COPC_COPCLKS(config->clock_select)) |
			   (SIM_COPC_COPT(config->windowsed_mode));
}

void wdog_Denit(void)
{
	SIM_COPC_COPW(COP_DISABLED);
}

void wdog_refresh(void)
{
	 SIM_SRVCOP = 0x55;
	 SIM_SRVCOP = 0xAA;
}

