/*
 * mot.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */
#define MOT
#include "sys.h"

void mot_init() {
	// enable clock to the FTM0
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	
	// enable write-able mode for FTM0
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;
	
	// turn off status and control
	FTM0_SC = 0;
	
	// makes the initial counter value for FTM0
	FTM0_CNTIN = 0;
	
	// writing any value to CNT loads the counter with CNTIN for FTM0
	FTM0_CNT = 0;
	
	// set edge-aligned PWM for all modules and channels
	FTM0_C4SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C5SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C2SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C3SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;

	// when the counter = mod the counter resets, these set the MOD value
	FTM0_MOD = MOT_MOD_INIT;
	FTM0_C4V = 0;
	FTM0_C5V = 0;
	FTM0_C2V = 0;
	FTM0_C3V = 0;
	
	// set clock prescaler for FTM0
	FTM0_SC |= FTM_SC_PS(1);

	// set main clock as BUS clock (50MHz) for FTM0, FTM1, and FTM2
	FTM0_SC |= FTM_SC_CLKS(1);
	
	// enable the clock for Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	// set Port D Pin 4 for GPIO functionality (B40)
	PORTD_PCR4 = (0|PORT_PCR_MUX(4));
	// set Port D Pin 4 for output to drive motor A1
	GPIOD_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(4));
	// set Port D Pin 5 for GPIO functionality (B39)
	PORTD_PCR5 = (0|PORT_PCR_MUX(4));
	// set Port D Pin 5 for output to drive motor A2
	GPIOD_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(5));
	// set Port C Pin 3 for GPIO functionality (A38)
	PORTC_PCR3 = (0|PORT_PCR_MUX(4));
	// set Port C Pin 3 for output to drive motor B1
	GPIOC_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(3));
	// set Port C Pin 4 for GPIO functionality (A37)
	PORTC_PCR4 = (0|PORT_PCR_MUX(4));
	// set Port C Pin 1 for output to drive motor B2
	GPIOC_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(4));
	// set Port C Pin 11 for GPIO functionality (A08)
	PORTC_PCR11= (0|PORT_PCR_MUX(1));
	// set Port C Pin 11 for H-bridge enable
	GPIOC_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(11));
	
	mot_enable();
	
	mot_flag = EXEC_FLAG_DOWN;
}

void mot_enable() {
	GPIOC_PSOR |= GPIO_PDOR_PDO(GPIO_PIN(11));
}

void mot_disable() {
	GPIOC_PSOR |= GPIO_PDOR_PDO(GPIO_PIN(11));
}

void mot_update() {
	FTM0_C4V = mot_motorSpeedA1;
	FTM0_C5V = mot_motorSpeedA2;	
	FTM0_C2V = mot_motorSpeedB1;
	FTM0_C3V = mot_motorSpeedB2;
}


