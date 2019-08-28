/*
 * wdog.h
 *
 *  Created on: set 30, 2018
 *      Author: Evandro Teixeira
 */

#ifndef WDOG_H_
#define WDOG_H_

#include "../Library-FRDM-KL25Z/externs.h"

// COP Watchdog Timeout
// These write-once bits select the timeout period of the COP.
// The COPT field along with the COPCLKS bit define the COP timeout period.
#define COP_DISABLED	0 	//00 COP disabled
#define COP_CYCLES_01	1 	//01 COP timeout after 2^5 LPO cycles or 2^13 bus clock cycles
#define COP_CYCLES_02	2 	//10 COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles
#define COP_CYCLES_03	3	//11 COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles

//COP Clock Select
//This write-once bit selects the clock source of the COP watchdog.
#define INTERNAL_1KHz	0	//00 Internal 1 kHz clock is source to COP
#define BUS_CLOCK	1	//01 Bus clock is source to COP

// Windowed mode is only supported when COP is running from the bus clock.
// The COP window is opened three quarters through the timeout period.
#define NORMAL_MODE	0	//00 Normal mode
#define WINDOWED_MODE	1 	//01 Windowed mode

typedef struct
{
	uint8_t timeout;
	uint8_t clock_select;
	uint8_t windowsed_mode;
}COPC_config_t;

void wdog_Init(COPC_config_t *config);
void wdog_Denit(void);
void wdog_refresh(void);

#endif /* WDOG_H_ */
