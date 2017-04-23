/*
 * pwm.c
 *
 *  Created on: 07/01/2017
 *      Author: Evandro
 */

#include "pwm.h"

bool pwm_tpm_Init(TPM_MemMapPtr tpm, uint16_t  clk, uint16_t module, uint8_t clock_mode,uint8_t ps, bool counting_mode)
{
	if(tpm == TPM0)
	{
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	}
	else if(tpm == TPM1)
	{
		SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	}
	else if(tpm == TPM2)
	{
		SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
	}
	else
	{
		return false;
	}

	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(clk);

	tpm->MOD = module;

	tpm->SC |= TPM_SC_CMOD(clock_mode) | TPM_SC_PS(ps);

	if(counting_mode == CENTER_PWM)
	{
		tpm->SC |= TPM_SC_CPWMS_MASK;
	}
	else if(counting_mode == EDGE_PWM)
	{
		tpm->SC &= ~TPM_SC_CPWMS_MASK;
	}
	else
	{
		return false;
	}
	return true;
}
/****************************************************************************************
*
*****************************************************************************************/
bool pwm_tpm_Ch_Init(TPM_MemMapPtr tpm, uint16_t channel, uint8_t mode,GPIO_MemMapPtr gpio,uint8_t pin)
{
	if(tpm == TPM0)
	{
		// PTA3 - CH0
		// PTA4 - CH1
		// PTA5 - CH2
		// PTA0 - CH5
		if(gpio == GPIOA)
		{
			if((channel<=2)||(channel==5))
			{
				if((pin>=3) || (pin<=5))
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTC1	- CH0
		// PTC2	- CH1
		// PTC3	- CH2
		// PTC4	- CH3
		// PTC8 - CH4
		// PTC9 - CH5
		else if(gpio == GPIOC)
		{
			if(channel<=5)
			{
				if((pin>=1 || pin<=4) || (pin==8) || (pin==9))
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
					PORT_PCR_REG(PORTC_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTD0 - CH0
		// PTD1 - CH1
		// PTD2 - CH2
		// PTD3 - CH3
		// PTD4 - CH4
		// PTD5 - CH5
		else if(gpio == GPIOD)
		{
			if(channel<=5)
			{
				if(pin<=5)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
					PORT_PCR_REG(PORTD_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		// PTE24 - CH0
		// PTE25 - CH1
		// PTE29 - CH2
		// PTE30 - CH3
		// PTE31 - CH4
		else if(gpio == GPIOE)
		{
			if(channel<=4)
			{
				if( (pin>=24 || pin<=25) || (pin>=29 || pin<=31) )
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if(tpm == TPM1)
	{
		if(channel <= 1)
		{
			// PTA12 - CH0
			// PTA13 - CH1
			if(gpio == GPIOA)
			{
				if(pin>=12 || pin<=13)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTB0 - CH0
			// PTB1 - CH1
			else if(gpio == GPIOB)
			{
				if(pin<=1)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORT_PCR_REG(PORTB_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTE20 - CH0
			// PTE21 - CH1
			else if(gpio == GPIOE)
			{
				if(pin>=20 || pin<=21)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if(tpm == TPM2)
	{
		if(channel <= 1)
		{
			// PTA1 - CH0
			// PTA2 - CH1
			if(gpio == GPIOA)
			{
				if(pin>=1 || pin<=2)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
					PORT_PCR_REG(PORTA_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTB2 - CH0
			// PTB3 - CH1
			// PTB18 - CH0
			// PTB19 - CH1
			else if(gpio == GPIOB)
			{
				if((pin>=2||pin<=3) || (pin>=18||pin<19))
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
					PORT_PCR_REG(PORTB_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			// PTE22 - CH0
			// PTE23 - CH1
			else if(gpio == GPIOE)
			{
				if(pin>=22 || pin<=23)
				{
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
					PORT_PCR_REG(PORTE_BASE_PTR,pin) = PORT_PCR_MUX(3);
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;

	TPM_CnSC_REG(tpm, channel) |= mode;

	return true;
}
/****************************************************************************************
*
*****************************************************************************************/
void pwm_tpm_CnV(TPM_MemMapPtr tpm, uint16_t channel, uint16_t value)
{
	TPM_CnV_REG(tpm, channel) = value;
}
/***************************************************************************************/
