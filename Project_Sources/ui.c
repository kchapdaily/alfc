/*
 * ui.c
 *
 *  Created on: Nov 8, 2013
 *      Author: Ryan
 */
#define UI
#include "sys.h"

int ui_init() {
	ui_menuState = UI_PERF;
	
	disable_irq(89);
	
	// enable the clock for Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//Set PTC5 and PTC13 (connected to SW1 and SW2) for GPIO 
	// functionality, falling IRQ, and to use internal pull-ups. 
	// (pin defaults to input state)  
	PORTC_PCR5 = (0|PORT_PCR_MUX(1)|PORT_PCR_IRQC(0xA)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK);
	PORTC_PCR13 = (0|PORT_PCR_MUX(1)|PORT_PCR_IRQC(0xA)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK);

	enable_irq(89);
	
	ui_menuState = UI_PERF;
	
	return UI_RET_SUCCESS;
}

void ui_isr() {
	// if the “Select” button was pressed, update the mode accordingly
	if (PORTC_ISFR & PORT_ISFR_ISF(GPIO_PIN(5))) {
	    // check if system is already running, stop it if it is
	    if (exec_sysMode != EXEC_MODE_IDLE) {
	        exec_sysMode = EXEC_MODE_IDLE;
	    } else {
			switch (ui_menuState) {
				case UI_PERF:
					ui_menuState = UI_PERF_SPE;
					break;
				case UI_TEST:
					ui_menuState = UI_TEST_SPE; 
					break;
				case UI_REMOTE:
					exec_sysMode = EXEC_MODE_REMOTE;
					break;
				case UI_PERF_SPE:
					exec_sysMode = EXEC_MODE_PERF_SPE;
					break;
				case UI_PERF_ACC:
					exec_sysMode = EXEC_MODE_PERF_ACC;
					break;
				case UI_PERF_DIS:
					exec_sysMode = EXEC_MODE_PERF_DIS;
					break;
				case UI_PERF_RET:
					ui_menuState = UI_PERF;
					break;
				case UI_TEST_SPE:
					exec_sysMode = EXEC_MODE_TEST_SPE;
					break;
				case UI_TEST_ACC:
					exec_sysMode = EXEC_MODE_TEST_ACC;
					break;
				case UI_TEST_DIS:
					exec_sysMode = EXEC_MODE_TEST_DIS;
					break;
				case UI_TEST_RET:
					ui_menuState = UI_TEST;
					break;
			}
	    }
		lcd_update();
		exec_update();
		comms_send();
	}

	// if the “Next” button was pressed, update the current menu item
	if (PORTC_ISFR & PORT_ISFR_ISF(GPIO_PIN(13))) {
		if (exec_sysMode == EXEC_MODE_IDLE) {
			switch (ui_menuState) {
				case UI_PERF:
					ui_menuState = UI_TEST;
					break;
				case UI_TEST:
					ui_menuState = UI_REMOTE; 
					break;
				case UI_REMOTE:
					ui_menuState = UI_PERF;
					break;
				case UI_PERF_SPE:
					ui_menuState = UI_PERF_ACC;
					break;
				case UI_PERF_ACC:
					ui_menuState = UI_PERF_DIS;
					break;
				case UI_PERF_DIS:
					ui_menuState = UI_PERF_RET;
					break;
				case UI_PERF_RET:
					ui_menuState = UI_PERF_SPE;
					break;
				case UI_TEST_SPE:
					ui_menuState = UI_TEST_ACC;
					break;
				case UI_TEST_ACC:
					ui_menuState = UI_TEST_DIS;
					break;
				case UI_TEST_DIS:
					ui_menuState = UI_TEST_RET;
					break;
				case UI_TEST_RET:
					ui_menuState = UI_TEST_SPE;
					break;
			}
			lcd_update();	
		}
	}
	
	// reset the PORT C ISR flag
	PORTC_ISFR = 0xFFFFFFFF;
}


