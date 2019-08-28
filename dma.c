/*
 * dma.c
 *
 *  Created on: 13/02/2018
 *      Author: evandro
 */
#include "../Library-FRDM-KL25Z/dma.h"
/****************************************************************************************
*
*****************************************************************************************/
static void (*dma0_task_callback)(void);
static void (*dma1_task_callback)(void);
static void (*dma2_task_callback)(void);
static void (*dma3_task_callback)(void);
/****************************************************************************************
*
*****************************************************************************************/
const IRQn_Type dma_irq[NUMBER_CHANNEL] =
{
	DMA0_IRQn,
	DMA1_IRQn,
	DMA2_IRQn,
	DMA3_IRQn
};
uint8_t dma_number_byte[NUMBER_CHANNEL];
/****************************************************************************************
*
*****************************************************************************************/
void dma_init(dma_config_t config)
{
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	DMA0->DMA[config.channel].DAR 	   = (uint32_t)config.destination_address;
	DMA0->DMA[config.channel].SAR 	   = (uint32_t)config.source_address;
	DMA0->DMA[config.channel].DSR_BCR  = DMA_DSR_BCR_BCR( config.number_byte );
	DMA0->DMA[config.channel].DCR 	   = 0;
	DMA0->DMA[config.channel].DCR 	  |= DMA_DCR_EINT_MASK;
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_ERQ(   config.peripheral_request );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_CS(    config.cycle_steal );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_SSIZE( config.source_size );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_DSIZE( config.destination_size );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_DINC(  config.destination_increment );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_SMOD(  config.source_address_modulo );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_DMOD(  config.destination_address_modulo );
	DMA0->DMA[config.channel].DCR     |= DMA_DCR_START( config.start_transfer );

	DMAMUX0->CHCFG[config.channel]    |= DMAMUX_CHCFG_ENBL_MASK;
	DMAMUX0->CHCFG[config.channel]    |= DMAMUX_CHCFG_SOURCE( config.channel_source );

	NVIC_EnableIRQ( dma_irq[config.channel] );

	dma_number_byte[config.channel]    = (uint8_t)config.number_byte;

//	number = (uint8_t)config.number_byte;
}
/****************************************************************************************
*
*****************************************************************************************/
void dma0_callback(void (*task)(void))
{
	if(task != NULL)
		dma0_task_callback = task;
}
/****************************************************************************************
*
*****************************************************************************************/
void dma1_callback(void (*task)(void))
{
	if(task != NULL)
		dma1_task_callback = task;
}
/****************************************************************************************
*
*****************************************************************************************/
void dma2_callback(void (*task)(void))
{
	if(task != NULL)
		dma2_task_callback = task;
}
/****************************************************************************************
*
*****************************************************************************************/
void dma3_callback(void (*task)(void))
{
	if(task != NULL)
		dma3_task_callback = task;
}
/****************************************************************************************
*
*****************************************************************************************/
void DMA0_IRQHandler(void)
{
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_BCR( dma_number_byte[0] );
	dma0_task_callback();
}
/****************************************************************************************
*
*****************************************************************************************/
void DMA1_IRQHandler(void)
{
	DMA0->DMA[1].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	DMA0->DMA[1].DSR_BCR |= DMA_DSR_BCR_BCR( dma_number_byte[1] );
	dma1_task_callback();
}
/****************************************************************************************
*
*****************************************************************************************/
void DMA2_IRQHandler(void)
{
	DMA0->DMA[2].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	DMA0->DMA[2].DSR_BCR |= DMA_DSR_BCR_BCR( dma_number_byte[2] );
	dma2_task_callback();
}
/****************************************************************************************
*
*****************************************************************************************/
void DMA3_IRQHandler(void)
{
	DMA0->DMA[3].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	DMA0->DMA[3].DSR_BCR |= DMA_DSR_BCR_BCR( dma_number_byte[3] );
	dma3_task_callback();
}
/*****************************************************************************************/
