#include "uart.h"

//void InitUart0(void)
void uart_init (UART_MemMapPtr uartch, int sysclk, int baud)
{
	register unsigned int sbr;
	unsigned char temp;
	
	//switch(uartch)
	//{
	//	case UART0_BASE_PTR:
	if(uartch == (UART_MemMapPtr)UART0_BASE_PTR)
	{
			/* Enable the SCI0_TXD function on the pin */
			PORTA_PCR1 = PORT_PCR_MUX(0x2);
			/* Enable the SCI0_RXD function on the pin */
			PORTA_PCR2 = PORT_PCR_MUX(0x2);
			/* Select the clock source for UART0 */
			SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
			/* UART0 and UART1 are clocked from the core clock, but all other UARTs are
			* clocked from the peripheral clock. So we have to determine which clock
			* to send to the uart_init function.
			*/
			/* Enable the clock to the selected UART */
			SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	}		
	//	break;		
	//	case UART1_BASE_PTR:
	else if(uartch == (UART_MemMapPtr)UART1_BASE_PTR)	
	{	
			/* Enable the UART_TXD function on PTC4 */
			PORTC_PCR4 = PORT_PCR_MUX(0x3); // UART1 is alt3 function for this pin
			/* Enable the UART_RXD function on PTC3 */
			PORTC_PCR3 = PORT_PCR_MUX(0x3); // UART1 is alt3 function for this pin
			/* Select the clock source for UART1 */
			//SIM_SOPT2 |= SIM_SOPT2_UART1SRC(1);
			/* Enable the clock to the selected UART */
			SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
	}		
	//	break;			
	//	case UART2_BASE_PTR:
	else if(uartch == (UART_MemMapPtr)UART2_BASE_PTR)
	{
			/* Enable the UART_TXD function on PTD3 */
			PORTD_PCR3 = PORT_PCR_MUX(0x3); // UART2 is alt3 function for this pin
			/* Enable the UART_RXD function on PTD2 */
			PORTD_PCR2 = PORT_PCR_MUX(0x3); // UART2 is alt3 function for this pin	
			/* Select the clock source for UART1 */
			//SIM_SOPT2 |= SIM_SOPT2_UART2SRC(1);
			/* Enable the clock to the selected UART */
			SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
	}
	//break;		
	//}
   /* Make sure that the transmitter and receiver are disabled while we
	* change settings.
	*/
	UART_C2_REG(uartch) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

	/* Configure the UART for 8-bit mode, no parity */
	UART_C1_REG(uartch) = 0;	/* We need all default settings, so entire register is cleared */

	/* Calculate baud settings */
	sbr = (unsigned int) ((sysclk*1000)/(baud * 16));

	/* Save off the current value of the UARTx_BDH except for the SBR field */
	temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));

	UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	UART_BDL_REG(uartch) = (unsigned char)(sbr & UART_BDL_SBR_MASK);

	/* Enable receiver and transmitter */
	UART_C2_REG(uartch) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

}


void uart_putchar (UART_MemMapPtr channel, char ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));

    /* Send the character */
    UART_D_REG(channel) = (unsigned char)ch;
}


char uart_getchar (UART_MemMapPtr channel)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));

    /* Return the 8-bit data from the receiver */
    return UART_D_REG(channel);
}