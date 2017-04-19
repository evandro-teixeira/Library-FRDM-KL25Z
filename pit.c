/*
 * pit.c
 *
 *  Created on: 18/04/2017
 *      Author: Evandro
 */

#include "pit.h"

/*****************************************************************************************
* Global Variable
*****************************************************************************************/
#if (MODEISRTPM == FLAG_TPM)
	static bool pitIsrFlag[2] = {false};
#else if (MODEISRTPM == COUNTER_TPM)
	static uint64_t tpm_i[2] = {0};
#endif

/*****************************************************************************************
*
*****************************************************************************************/
bool pit_Init(uint32_t value,bool ch)
{
	//PIT_MCR;
	//PIT_TCTRL0;

	if(ch >= 2)
	{
		// Enable PIT clock
		SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

		// Turn on PIT
		PIT_MCR = 0;

		// Configure PIT to produce an interrupt every 1s
		//PIT_LDVAL0 = value;
		PIT_LDVAL_REG(PIT,ch) = value;

		// Enable interrupt and enable timer
		//PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
		PIT_TCTRL_REG(PIT,ch) |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

		// Enable External Interrupt
		NVIC_EnableIRQ(PIT_IRQn);

		return true;
	}
	else
	{
		return false;
	}
}
/*****************************************************************************************
*
*****************************************************************************************/
void pit_Start(bool ch)
{
	PIT_TCTRL_REG(PIT,ch) |= PIT_TCTRL_TEN_MASK;
}
/*****************************************************************************************
*
*****************************************************************************************/
void pit_Stop(bool ch)
{
	PIT_TCTRL_REG(PIT,ch) &= ~PIT_TCTRL_TEN_MASK;
}
/*****************************************************************************************
*
*****************************************************************************************/
#if (MODEISRTPM == FLAG_TPM)
bool pit_GetFlag_Isr(bool ch)
{
	return pitIsrFlag[ch];
}
void pit_ClearFlag_Isr(bool ch)
{
	 pitIsrFlag[ch] = false;
}
#else if (MODEISRTPM == COUNTER_TPM)
void pit_ClearCounter_Isr(bool ch)
{
	tpm_i[ch] = 0;
}
/*****************************************************************************************
*
*****************************************************************************************/
uint64_t pit_GetCounter_Isr(bool ch)
{
	return tpm_i[ch];
}
#endif
/*****************************************************************************************
* Handles PIT interrupt if enabled
*****************************************************************************************/
void PIT_IRQHandler(void)
{
	uint8_t index = 0;

	for(index=0;index<2;index++)
	{
		if( PIT_TFLG_REG(PIT,index) )
		{
			// Clear interrupt
			//PIT_TFLG0 = PIT_TFLG_TIF_MASK;
			PIT_TFLG_REG(PIT,index) = PIT_TFLG_TIF_MASK;
#if (MODEISRTPM == FLAG_TPM)
			pitIsrFlag[index] = true;
#else if (MODEISRTPM == COUNTER_TPM)
			tpm_i[index] += 1;
#endif
			//if(index)
				// Toggle Green LED Green
				//GPIOB_PTOR = (1 << 19);
			//else
				// Toggle Green LED Red
				//GPIOB_PTOR = (1 << 18);
		}
	}
}
/****************************************************************************************/


