/*
* uart.c
*
*  Created on: Jul 20, 2016
*      Author: PDI
*/

#include "../Library-FRDM-KL25Z/uart.h"
/****************************************************************************************
*
*****************************************************************************************/
void (*uart0_task_irq)(void);
void (*uart1_task_irq)(void);
void (*uart2_task_irq)(void);
/****************************************************************************************
*
*****************************************************************************************/
bool uart_Init(UART_MemMapPtr uart, uint8_t alt, uint32_t baud_rate)
{
	uint16_t divisor;
	uint8_t temp;

	if(uart == (UART_MemMapPtr)UART0)
	{
	    SIM_SCGC4 |=  SIM_SCGC4_UART0_MASK;
	    SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	    SIM_SOPT2 |=  SIM_SOPT2_UART0SRC(1);
	    divisor = (uint16_t)(SystemCoreClock / baud_rate ) / 16;

		switch(alt)
		{
			case 0:
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;	// Turn on clock to A module
			    PORTA_PCR1 = PORT_PCR_MUX(2);		// Set PTA1 to mux 2 [RX]
			    PORTA_PCR2 = PORT_PCR_MUX(2);		// Set PTA2 to mux 2 [TX]
			break;

			case 1:
				SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK;	// Turn on clock to A module
			    PORTA_PCR14 = PORT_PCR_MUX(3);		// Set PTA14 to mux 3 [TX]
			    PORTA_PCR15 = PORT_PCR_MUX(3);		// Set PTA15 to mux 3 [RX]
			break;

			case 2:
				SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK;	// Turn on clock to B module
			    PORTB_PCR16 = PORT_PCR_MUX(3);		// Set PTA14 to mux 3 [RX]
			    PORTB_PCR17 = PORT_PCR_MUX(3);		// Set PTA15 to mux 3 [TX]
			break;

			case 3:
				SIM_SCGC5  |= SIM_SCGC5_PORTD_MASK;	// Turn on clock to D module
			    PORTD_PCR6 = PORT_PCR_MUX(3);		// Set PTA14 to mux 3 [RX]
			    PORTD_PCR7 = PORT_PCR_MUX(3);		// Set PTA15 to mux 3 [TX]
			break;

			case 4:
				SIM_SCGC5  |= SIM_SCGC5_PORTE_MASK;	// Turn on clock to E module
			    PORTE_PCR6 = PORT_PCR_MUX(3);		// Set PTA14 to mux 3 [RX]
			    PORTE_PCR7 = PORT_PCR_MUX(3);		// Set PTA15 to mux 3 [TX]
			break;

			default:
				return false;
			break;
		}
	}
	else if(uart == (UART_MemMapPtr)UART1)
	{
	    SIM_SCGC4 |=  SIM_SCGC4_UART1_MASK;

	    if(baud_rate == 115200)
	    	divisor = (uint16_t)(SystemCoreClock / 128 / baud_rate ) * 66; // 115200
	    else
	    	divisor = (uint16_t)( SystemCoreClock / (baud_rate * 32) );  // 9600

		switch(alt)
		{
			case 0:
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;	// Turn on clock to A module
			    PORTA_PCR18 = PORT_PCR_MUX(3);		// Set PTA18 to mux 3 [RX]
			    PORTA_PCR19 = PORT_PCR_MUX(3);		// Set PTA19 to mux 3 [TX]
			break;

			case 1:
				SIM_SCGC5  |= SIM_SCGC5_PORTC_MASK;	// Turn on clock to A module
			    PORTC_PCR3 = PORT_PCR_MUX(3);		// Set PTC3 to mux 3 [RX]
			    PORTC_PCR4 = PORT_PCR_MUX(3);		// Set PTC4 to mux 3 [TX]
			break;

			case 2:
				SIM_SCGC5  |= SIM_SCGC5_PORTE_MASK;	// Turn on clock to E module
			    PORTE_PCR0 = PORT_PCR_MUX(3);		// Set PTE0 to mux 3 [TX]
			    PORTE_PCR1 = PORT_PCR_MUX(3);		// Set PTE1 to mux 3 [RX]
			break;

			default:
				return false;
			break;
		}
	}
	else if(uart == (UART_MemMapPtr)UART2)
	{
	    SIM_SCGC4 |=  SIM_SCGC4_UART2_MASK;

	    if(baud_rate == 115200)
	    	divisor = (uint16_t)(SystemCoreClock / 128 / baud_rate ) * 66; // 115200
	    else
	    	divisor = (uint16_t)( SystemCoreClock / (baud_rate * 32) );  // 9600

		switch(alt)
		{
			case 0:
				SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	// Turn on clock to A module
			    PORTD_PCR2 = PORT_PCR_MUX(3);		// Set PTA18 to mux 3 [RX]
			    PORTD_PCR3 = PORT_PCR_MUX(3);		// Set PTA19 to mux 3 [TX]
			break;

			case 1:
				SIM_SCGC5  |= SIM_SCGC5_PORTD_MASK;	// Turn on clock to A module
			    PORTD_PCR4 = PORT_PCR_MUX(3);		// Set PTC3 to mux 3 [RX]
			    PORTD_PCR5 = PORT_PCR_MUX(3);		// Set PTC4 to mux 3 [TX]
			break;

			case 2:
				SIM_SCGC5  |= SIM_SCGC5_PORTE_MASK;	// Turn on clock to E module
			    PORTE_PCR22 = PORT_PCR_MUX(3);		// Set PTE0 to mux 3 [TX]
			    PORTE_PCR23 = PORT_PCR_MUX(3);		// Set PTE1 to mux 3 [RX]
			break;

			default:
				return false;
			break;
		}
	}
	else
	{
		return false;
	}

	//
	uart->C2 &=~ (UART_C2_TE_MASK | UART_C2_RE_MASK);
	uart->C1 = 0;

	temp = uart->BDH & ~(UART_BDH_SBR(0x1F));
	uart->BDH = ( temp |  UART_BDH_SBR(((divisor & 0x1F00) >> 8)) );
	uart->BDL = (uint16_t)(divisor & UART_BDL_SBR_MASK);

	uart->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);

	return true;
}
/****************************************************************************************
*
*****************************************************************************************/
void uart_Put(UART_MemMapPtr uart, uint8_t c)
{
	while((uart->S1 & UART0_S1_TDRE_MASK) != UART0_S1_TDRE_MASK);
	uart->D = c;
}
/****************************************************************************************
*
*****************************************************************************************/
uint8_t uart_Get(UART_MemMapPtr uart)
{
	//while(!(UART0_S1 & 0x20));
	while((uart->S1 & UART0_S1_TDRE_MASK) != UART0_S1_TDRE_MASK);
	return uart->D;
}
/****************************************************************************************
*
*****************************************************************************************/
void uart_String(UART_MemMapPtr uart,char* txt )
{
	while(*txt)
	{
		uart_Put(uart,*txt);
		txt++;
	}
}
/****************************************************************************************
*
*****************************************************************************************/
void uart_enable_irq(UART_MemMapPtr uart)
{
	uart->C2 |= UART_C2_RIE_MASK;
	//uart->C3 |= UART_C3_ORIE_MASK;

	if(uart == UART1)
	{
		NVIC_EnableIRQ(UART1_IRQn);
	}
	else if(uart == UART2)
	{
		NVIC_EnableIRQ(UART2_IRQn);
	}
	else
	{
		NVIC_EnableIRQ(UART0_IRQn);
	}
}
/****************************************************************************************
*
*****************************************************************************************/
void uart_add_callback(UART_MemMapPtr uart, void (*task)(void))
{
	if(uart == UART1)
	{
		if(task != NULL)
		{
			uart1_task_irq = task;
		}
	}
	else if(uart == UART2)
	{
		if(task != NULL)
		{
			uart2_task_irq = task;
		}
	}
	else
	{
		if(task != NULL)
		{
			uart0_task_irq = task;
		}
	}
}
/****************************************************************************************
*
*****************************************************************************************/
void UART0_IRQHandler(void)
{
	if(uart0_task_irq != NULL)
	{
		uart0_task_irq();
	}
}
/****************************************************************************************
*
*****************************************************************************************/
void UART1_IRQHandler(void)
{
	if(uart1_task_irq != NULL)
	{
		uart1_task_irq();
	}
}
/****************************************************************************************
*
*****************************************************************************************/
void UART2_IRQHandler(void)
{
	if(uart2_task_irq != NULL)
	{
		uart2_task_irq();
	}
}
/****************************************************************************************
*
*****************************************************************************************/
