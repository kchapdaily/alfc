/*
 * serv.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */
#define SERV
#include "sys.h"

void serv_init() {	
	// enable the clock to FTM1
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
	
	// enable write-able mode for FTM1
	FTM1_MODE |= FTM_MODE_WPDIS_MASK;
	
	// turn off status and control
	FTM1_SC = 0;
	
	// makes the initial counter value for FTM1
	FTM1_CNTIN = 0;
	
	// writing any value to CNT loads the counter with CNTIN for FTM1
	FTM1_CNT = 0;
	
	// set edge-aligned PWM for all modules and channels
	FTM1_C0SC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	
	// when the counter = mod the counter resets, these set the MOD values
	FTM1_MOD = SERV_MOD_INIT;
	FTM1_C0V = 0;
	
	// set clock prescaler for FTM1
	FTM1_SC |= FTM_SC_PS(4);
	
	// set main clock as BUS clock (50 MHz) for FTM1
	FTM1_SC |= FTM_SC_CLKS(1);
	
	// enable the clock for Port A
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	// set Port A Pin 8 for GPIO functionality (A34)
	PORTA_PCR8 = (0|PORT_PCR_MUX(3));
	// set Port A Pin 8 for output to drive servo
	GPIOA_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(8));
	
	serv_flag = EXEC_FLAG_DOWN;
}

void serv_update() {
	if (serv_angle > SERV_MAX_VAL) {
		FTM1_C0V = SERV_OFFSET_VAL + SERV_MAX_VAL;
	} else if (serv_angle < SERV_MIN_VAL) {
		FTM1_C0V = SERV_OFFSET_VAL + SERV_MIN_VAL;
	} else {
		FTM1_C0V = SERV_OFFSET_VAL + serv_angle;
	}
}


