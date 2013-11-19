/*
 * hl.c
 *
 *  Created on: Oct 25, 2013
 *      Author: Ryan
 */
#include "sys.h"

void hl_init() {
	// enable the clock for Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	// set Port C Pin 10 for GPIO functionality (A07)
	PORTC_PCR10 = (0|PORT_PCR_MUX(1));

	// set Port C Pin 10 for output to drive the headlight display
	GPIOC_PDDR = GPIO_PDDR_PDD(GPIO_PIN(10));
}

void hl_on() {
	// to turn on the LED headlights
	GPIOC_PCOR |= GPIO_PDOR_PDO(GPIO_PIN(10));
}

void hl_off() {
	// to turn off the LED headlights
	GPIOC_PSOR |= GPIO_PDOR_PDO(GPIO_PIN(10));
}


