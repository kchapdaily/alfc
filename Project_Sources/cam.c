/*
 * cam.c
 *
 *  Created on: Oct 26, 2013
 *      Author: Ryan
 */

#define CAM
#include "sys.h"

int cam_enable() {
	enable_irq(64);
	
	return CAM_RET_SUCCESS;
}

int cam_disable() {
	disable_irq(64);
	
	return CAM_RET_SUCCESS;
}

int cam_init() {
	//
	// disable interrupt
	//
	disable_irq(64);
	
	//
	// FTM2 configuration
	//
	
	// enable the clock for FTM2
	SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
	
	// enable write-able mode for FTM2
	FTM2_MODE |= FTM_MODE_WPDIS_MASK;
	
	// turn off Status and Control
	FTM2_SC = 0;
	
	// makes the initial counter value for FTM2
	FTM2_CNTIN = 0;
	
	// writing any value to CNT loads the counter with CNTIN for FTM 2
	FTM2_CNT = 0;
	
	// CHIE enables interrupts as an ISR (used by ADC function after
	// clock pulses)
	FTM2_C0SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK | FTM_CnSC_CHIE_MASK;
	
	// when counter == mod, the counter resets, set MOD value
	FTM2_MOD = CAM_MOD_INIT;
	FTM2_C0V = 0;
	
	// set clock prescaler for FTM2
	FTM2_SC |= FTM_SC_PS(2);
	
	// set main clock as BUS clock (50 MHz) for FTM2
	FTM2_SC |= FTM_SC_CLKS(1);	
	
	//
	// GPIO configuration for top level pins
	//
		
	// enable the clock for Port A
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	// set Port A Pin 14 for GPIO functionality (A22)
	PORTA_PCR14 = (0|PORT_PCR_MUX(1));
	// set Port A Pin 14 for output to drive the SI pulse
	GPIOA_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(14));
	
	// set Port A Pin 10 for GPIO functionality (B66)
	PORTA_PCR10 = (0|PORT_PCR_MUX(3));
	// set Port A Pin 10 for output to drive the camera clock
	GPIOA_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(10));

	
	
	return CAM_RET_SUCCESS;
}

void cam_isr() {
	// clear interrupt flag
	FTM2_C0SC;
	FTM2_C0SC &= ~(0x80u);
	
	// send SI low
	GPIOA_PCOR |= GPIO_PDOR_PDO(GPIO_PIN(14));
	
	// run ADC on data input for 128 pixels
	if (cam_clockCounter < 128) {
		cam_clockCounter++;
		adc_start();
	} else {
		// disable interrupt
		disable_irq(64);
		
		cam_clockCounter = 0;
		FTM2_C0V = 0;
		cam_flag = EXEC_FLAG_DOWN;
	}	
}

void cam_start() {	
	// call pwm driver to start camera clock (CLK) for a 5% duty cycle
	FTM2_CNT = 0;
	FTM2_C0V = 45;
	
	// set cam flag
	cam_flag = EXEC_FLAG_UP;
	
	// set SI pulse high
	GPIOA_PSOR |= GPIO_PDOR_PDO(GPIO_PIN(14));
	
	// enable interrupt
	enable_irq(64);
}


