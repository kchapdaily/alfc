/*
 * adc.c
 *
 *  Created on: Oct 25, 2013
 *      Author: Ryan
 */

#define ADC
#include "sys.h"

int adc_init() {
	adc_pixelIndex = 0;
	
	// disable ADC irq - not ready yet
	disable_irq(ADC_IRQ_NUM);
	
	// turn on clock to ADC0
	SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK);
	
	// to setup SW trigger on FTM2
	SIM_SOPT7 = SIM_SOPT7_ADC0TRGSEL(10);
	
	// to calibrate the ADC module
	unsigned short cal_var;
	cal_var = 0x0000;

	// add the plus-side calibration results
	cal_var += ADC_CLP0_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLP1_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLP2_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLP3_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLP4_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLPS_REG(ADC0_BASE_PTR);

	cal_var /= 2;
	cal_var |= 0x8000;
	
	// store value in plus-side gain calibration register (PG)
	ADC_PG_REG(ADC0_BASE_PTR) = ADC_PG_PG(cal_var);

	cal_var = 0x0000;
		
	// add the minus-side calibration results
	cal_var += ADC_CLM0_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLM1_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLM2_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLM3_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLM4_REG(ADC0_BASE_PTR);
	cal_var += ADC_CLMS_REG(ADC0_BASE_PTR);

	cal_var /= 2;
	cal_var |= 0x8000;

	// store value in minus-side gain calibration register (MG)
	ADC_MG_REG(ADC0_BASE_PTR) = ADC_MG_MG(cal_var);

	ADC_SC3_REG(ADC0_BASE_PTR) &= ~ADC_SC3_CAL_MASK;

	// to set the configuration register 1 (CFG1) to select the mode of
	// operation, clock source, clock divide, and configuration for low
	// power or long sample time
	ADC_CFG1_REG(ADC0_BASE_PTR) = ADLPC_NORMAL
		| ADC_CFG1_ADIV(ADIV_1)
		| ADLSMP_SHORT
		| ADC_CFG1_MODE(MODE_8)
		| ADC_CFG1_ADICLK(ADICLK_BUS);
	
	// to set the configuration register 2 (CFG2) to select the special
	// high-speed configuration for very high speed conversions and 
	// select the long sample time duration during long sample mode
	ADC_CFG2_REG(ADC0_BASE_PTR) = MUXSEL_ADCA
		| ADACKEN_DISABLED
		| ADHSC_HISPEED
		| ADC_CFG2_ADLSTS(ADLSTS_2);

	// to configure the status and control register 2 (SC2)
	ADC_SC2_REG(ADC0_BASE_PTR) = ADTRG_SW
		| ACFE_DISABLED
		| ACFGT_GREATER
		| ACREN_DISABLED
		| DMAEN_DISABLED
		| ADC_SC2_REFSEL(REFSEL_EXT);

	// to configure the status and control register 3 (SC3)
	// enable hw averaging, 16 samples taken
	ADC_SC3_REG(ADC0_BASE_PTR) = CAL_OFF
		| ADCO_SINGLE
		| AVGE_ENABLED
		| ADC_SC3_AVGS(AVGS_16);

	// to configure the status and control register 1 (SC1)
	//     enable the interrupt, single-ended conversion, on AD18

	ADC_SC1_REG(ADC0_BASE_PTR, A)= AIEN_ON 
		| DIFF_SINGLE 
		| ADC_SC1_ADCH(18);

	// to configure the PGA register
	ADC_PGA_REG(ADC0_BASE_PTR) = PGAEN_DISABLED
		| PGACHP_NOCHOP
		| PGALP_NORMAL
		| ADC_PGA_PGAG(PGAG_64);
	
	// enable ADC irq
	enable_irq(ADC_IRQ_NUM);
	
	return ADC_RET_SUCCESS;
}

void adc_isr() {
	adc_rawCameraData[adc_pixelIndex] = ADC0_RA;

	adc_pixelIndex++;
	if (adc_pixelIndex == ADC_NUM_PIXELS) {
		adc_pixelIndex = 0;
	}
}

inline void adc_start() {	
	// to start the ADC conversion
	ADC_SC1_REG(ADC0_BASE_PTR, A)= AIEN_ON 
		| DIFF_SINGLE 
		| ADC_SC1_ADCH(18);
}



