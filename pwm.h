/*
 * pwm.h
 *
 *  Created on: 07/01/2017
 *      Author: Evandro
 */

#ifndef SOURCES_PWM_H_
#define SOURCES_PWM_H_

#include "externs.h"
#include "stdbool.h"

// TPM clock source select
// Selects the clock source for the TPM counter clock
#define TPM_CLK_DIS     0	// Clock disabled
#define TPM_PLLFLL 		1	// MCGFLLCLK clock or MCGPLLCLK/2 clock
#define TPM_OSCERCLK 	2	// OSCERCLK clock
#define TPM_MCGIRCLK	3	// MCGIRCLK clock

#define	TPM_CNT_DIS		0	// counter is disabled
#define	TPM_CLK			1	// counter increments on every LPTPM counter clock
#define	TPM_EXT_CLK		2	// counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock

#define PS_1			0	// Prescale Factor Selection
#define PS_2			1
#define PS_4			2
#define PS_8			3
#define PS_16			4
#define PS_32			5
#define PS_64			6
#define PS_128			7

#define TPM_OC_TOGGLE	TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_OC_CLR		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_SET		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTL		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTH		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK

#define TPM_PWM_H 		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK
#define TPM_PWM_L		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK

#define EDGE_PWM		0
#define CENTER_PWM		1
/* */

bool pwm_tpm_Init(TPM_MemMapPtr tpm, uint16_t  clk, uint16_t module, uint8_t clock_mode,uint8_t ps, bool counting_mode);
//void pwm_tpm_Ch_Init(TPM_MemMapPtr tpm, uint16_t channel, uint8_t mode);
bool pwm_tpm_Ch_Init(TPM_MemMapPtr tpm, uint16_t channel, uint8_t mode,GPIO_MemMapPtr gpio,uint8_t pin);
void pwm_tpm_CnV(TPM_MemMapPtr TPMx, uint16_t channel, uint16_t value);

#endif /* SOURCES_PWM_H_ */
