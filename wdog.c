/*
 * wdog.h
 *
 *  Created on: set 30, 2018
 *      Author: Evandro Teixeira
 */
#include "../Library-FRDM-KL25Z/wdog.h"

void wdog_Init(COPC_config_t *config)
{
	SIM->COPC = (SIM_COPC_COPW(config->windowsed_mode))  | 		// COP windowed mode
			    (SIM_COPC_COPCLKS(config->clock_select)) | 	// COP Clock Select
			    (SIM_COPC_COPT(config->timeout));		// COP Watchdog Timeout
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

