/*
 * spi.c
 * Author: Evandro
 */
#include "spi.h"
/****************************************************************************************
*
*****************************************************************************************/
bool spi_Init(SPI_MemMapPtr spi,bool alt,uint8_t pre, uint16_t div,bool cs)
{
	if(spi == SPI0)
	{
		switch(alt)
		{
			case ALT_0:
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to C module
				//SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;  	//Enable SPI0 clock
				if(cs == CS_AUT)						//Chip Select Auto
					PORTC_PCR4 = PORT_PCR_MUX(0x2);     //Set PTC4 to mux 2 [SPI0_PCS0]
				PORTC_PCR5 = PORT_PCR_MUX(0x2);    		//Set PTC5 to mux 2 [SPI0_SCK]
				PORTC_PCR6 = PORT_PCR_MUX(0x2);    		//Set PTC6 to mux 2 [SPI0_MOSI]
				PORTC_PCR7 = PORT_PCR_MUX(0x2);    		//Set PTC7 to mux 2 [SPIO_MISO]
			break;

			case ALT_1:
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;      //Turn on clock to A module
				//SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   	//Enable SPI0 clock
				if(cs == CS_AUT)						//Chip Select Auto
					PORTA_PCR14 = PORT_PCR_MUX(0x2);   	//Set PTA14 to mux 2 [SPI0_PCS0]
				PORTA_PCR15 = PORT_PCR_MUX(0x2);    	//Set PTA15 to mux 2 [SPI0_SCK]
				PORTA_PCR16 = PORT_PCR_MUX(0x2);    	//Set PTA16 to mux 2 [SPI0_MOSI]
				PORTA_PCR17 = PORT_PCR_MUX(0x2);    	//Set PTA17 to mux 2 [SPIO_MISO]
			break;

			default:
				return false;
			break;
		}
		//Enable SPI0 clock
		SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
	}
	else if(spi == SPI1)
	{
		switch(alt)
		{
			case ALT_0:
				SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;      //Turn on clock to E module
				//SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;   	//Enable SPI1 clock
				if(cs == CS_AUT)						//Chip Select Auto
					PORTE_PCR4 = PORT_PCR_MUX(0x2);     //Set PTE4 to mux 2 [SPI1_PCS0]
				PORTE_PCR2 = PORT_PCR_MUX(0x2);    		//Set PTE2 to mux 2 [SPI1_SCK]
				PORTE_PCR1 = PORT_PCR_MUX(0x2);    		//Set PTE1 to mux 2 [SPI1_MOSI]
				PORTE_PCR3 = PORT_PCR_MUX(0x2);    		//Set PTE3 to mux 2 [SPI1_MISO]
			break;

			case ALT_1:
				SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK;     //Turn on clock to B module
				//SIM_SCGC4  |= SIM_SCGC4_SPI1_MASK;  	//Enable SPI1 clock
				if(cs == CS_AUT)						//Chip Select Auto
					PORTB_PCR10 = PORT_PCR_MUX(0x2);    //Set PTB10 to mux 2 [SPI1_PCS0]
				PORTB_PCR11 = PORT_PCR_MUX(0x2);    	//Set PTB11 to mux 2 [SPI1_SCK]
				PORTB_PCR16 = PORT_PCR_MUX(0x2);    	//Set PTB16 to mux 2 [SPI1_MOSI]
				PORTB_PCR17 = PORT_PCR_MUX(0x2);    	//Set PTB17 to mux 2 [SPI1_MISO]
			break;

			default:
				return false;
			break;
		}
		//Enable SPI1 clock
		SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
	}
	else
	{
		return false;
	}

	//Chip Select Auto
	if(cs == CS_AUT)
		// Set SPI to Master & SS pin to auto SS & spi mode in 0,0
		spi->C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;
	else
		// Set SPI to Master
		spi->C1 = SPI_C1_MSTR_MASK;

	// Configure SPI Register C2
	spi->C2 = SPI_C2_MODFEN_MASK;   //Master SS pin acts as slave select output

	// Set baud rate prescale divisor to 6 & set baud rate divisor to 4 for baud rate of 1 Mhz
	spi->BR = (SPI_BR_SPPR(pre) | SPI_BR_SPR(div));    //  Mhz

	// Enable SPI
	spi->C1 |= SPI_C1_SPE_MASK;

	return true;
}
/*
bool spi_init(bool spi,bool alt,uint8_t pre, uint16_t div,bool cs)
{
	switch(spi)
	{
		case SPI_0:
			switch(alt)
			{
				case ALT_0:
					SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to C module
					//SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;  	//Enable SPI0 clock
					if(cs == CS_AUT)						//Chip Select Auto
						PORTC_PCR4 = PORT_PCR_MUX(0x2);     //Set PTC4 to mux 2 [SPI0_PCS0]
					PORTC_PCR5 = PORT_PCR_MUX(0x2);    		//Set PTC5 to mux 2 [SPI0_SCK]
					PORTC_PCR6 = PORT_PCR_MUX(0x2);    		//Set PTC6 to mux 2 [SPI0_MOSI]
					PORTC_PCR7 = PORT_PCR_MUX(0x2);    		//Set PTC7 to mux 2 [SPIO_MISO]
				break;
 
				case ALT_1:
					SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;      //Turn on clock to A module
					//SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   	//Enable SPI0 clock
					if(cs == CS_AUT)						//Chip Select Auto
						PORTA_PCR14 = PORT_PCR_MUX(0x2);   	//Set PTA14 to mux 2 [SPI0_PCS0]
					PORTA_PCR15 = PORT_PCR_MUX(0x2);    	//Set PTA15 to mux 2 [SPI0_SCK]
					PORTA_PCR16 = PORT_PCR_MUX(0x2);    	//Set PTA16 to mux 2 [SPI0_MOSI]
					PORTA_PCR17 = PORT_PCR_MUX(0x2);    	//Set PTA17 to mux 2 [SPIO_MISO]
				break;
 
				default:
					return false;
				break;
			}
			//Enable SPI0 clock
			SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
 
			//Chip Select Auto
			if(cs == CS_AUT)
				// Set SPI0 to Master & SS pin to auto SS & spi mode in 0,0
				SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;
			else
				// Set SPI0 to Master
				SPI0_C1 = SPI_C1_MSTR_MASK;
 
			// Configure SPI Register C2
			SPI0_C2 = SPI_C2_MODFEN_MASK;   //Master SS pin acts as slave select output
 
			// Set baud rate prescale divisor to 6 & set baud rate divisor to 4 for baud rate of 1 Mhz
			SPI0_BR = (SPI_BR_SPPR(pre) | SPI_BR_SPR(div));    //  Mhz
 
			// Enable SPI0
			SPI0_C1 |= SPI_C1_SPE_MASK;
 
			return true;
		break;
 
		case SPI_1:
			switch(alt)
			{
				case ALT_0:
					SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;      //Turn on clock to E module
					//SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;   	//Enable SPI1 clock
					if(cs == CS_AUT)						//Chip Select Auto
						PORTE_PCR4 = PORT_PCR_MUX(0x2);     //Set PTE4 to mux 2 [SPI1_PCS0]
					PORTE_PCR2 = PORT_PCR_MUX(0x2);    		//Set PTE2 to mux 2 [SPI1_SCK]
					PORTE_PCR1 = PORT_PCR_MUX(0x2);    		//Set PTE1 to mux 2 [SPI1_MOSI]
					PORTE_PCR3 = PORT_PCR_MUX(0x2);    		//Set PTE3 to mux 2 [SPI1_MISO]
				break;
 
				case ALT_1:
					SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK;     //Turn on clock to B module
					//SIM_SCGC4  |= SIM_SCGC4_SPI1_MASK;  	//Enable SPI1 clock
					if(cs == CS_AUT)						//Chip Select Auto
						PORTB_PCR10 = PORT_PCR_MUX(0x2);    //Set PTB10 to mux 2 [SPI1_PCS0]
					PORTB_PCR11 = PORT_PCR_MUX(0x2);    	//Set PTB11 to mux 2 [SPI1_SCK]
					PORTB_PCR16 = PORT_PCR_MUX(0x2);    	//Set PTB16 to mux 2 [SPI1_MOSI]
					PORTB_PCR17 = PORT_PCR_MUX(0x2);    	//Set PTB17 to mux 2 [SPI1_MISO]
				break;
 
				default:
					return false;
				break;
			}
			//Enable SPI1 clock
			SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
 
			// Chip Select Auto
			if(cs == CS_AUT)
				// Set SPI0 to Master & SS pin to auto SS & spi mode in 0,0
				SPI1_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;
			else
				// Set SPI0 to Master
				SPI1_C1 = SPI_C1_MSTR_MASK;
 
			// Configure SPI Register C2
			SPI1_C2 = SPI_C2_MODFEN_MASK;   //Master SS pin acts as slave select output
 
			// Set baud rate prescale divisor to 6 & set baud rate divisor to 4 for baud rate of 1 Mhz
			SPI1_BR = (SPI_BR_SPPR(pre) | SPI_BR_SPR(div));    //  Mhz
 
			// Enable SPI0
			SPI1_C1 |= SPI_C1_SPE_MASK;
 
			return true;
		break;
 
		default:
			return false; // error
		break;
	}
}*/
/****************************************************************************************
*
*****************************************************************************************/
void spi_Send(SPI_MemMapPtr spi,uint8_t data)
{
	//While buffer is not empty do nothing
	while(!(SPI_S_SPTEF_MASK & spi->S))
	{
		__asm("nop");
	}
	spi->D = data;
}
/*
bool spi_send(bool spi,uint8_t data)
{
	switch(spi)
	{
		case SPI_0:
			//While buffer is not empty do nothing
			while(!(SPI_S_SPTEF_MASK & SPI0_S))
			{
				__asm("nop");
			}
			//Write char to SPI
			SPI0_D = data;
 
			return true;
		break;
 
		case SPI_1:
			//While buffer is not empty do nothing
			while(!(SPI_S_SPTEF_MASK & SPI1_S))
			{
				__asm("nop");
			}
			//Write char to SPI
			SPI1_D = data;
 
			return true;
		break;
 
		default:
			return false; //erro
		break;
	}
}*/
/****************************************************************************************
*
*****************************************************************************************/
uint8_t spi_Read(SPI_MemMapPtr spi)
{
	// Wait for receive flag to set
	while(!(spi->S & SPI_S_SPRF_MASK))
	{
		__asm("nop");
	}
	return spi->D;
}
/*
uint8_t spi_read(bool spi)
{
	switch(spi)
	{
		case SPI_0:
			  // Wait for receive flag to set
			  while(!(SPI0_S & SPI_S_SPRF_MASK))
			  {
			    __asm("nop");
			  }
			  // SPI0_D;  //Read SPI data from slave
			  return SPI0_D;
		break;
 
		case SPI_1:
			  // Wait for receive flag to set
			  while(!(SPI1_S & SPI_S_SPRF_MASK))
			  {
			    __asm("nop");
			  }
			  // SPI1_D;  //Read SPI data from slave
			  return SPI1_D;
		break;
 
		default:
			return false;
		break;
	}
}*/
/****************************************************************************************/
