/*
 * exec.c
 *
 *  Created on: Oct 26, 2013
 *      Author: Ryan
 */
#define EXEC
#include "sys.h"

void exec_init() {
	// initialize all sub-systems
	hl_init();
	schd_init();
	lcd_init();
	cam_init();	
	adc_init();
	serv_init();
	cont_init();
	ui_init();
	mot_init();
	//comms_init();	
	
	// disable interrupt
	disable_irq(EXEC_PIT_IRQ_NUM);
	
	// enable the clock to the PIT module (pg. 299)
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	// enable clock for PIT timers and allow timers to continue to
	// run in debug mode (pg. 1038)
	PIT_MCR = 0x0; 
	
	exec_disablePit();
	
	exec_sysMode = EXEC_MODE_IDLE;
	lcd_update();
	exec_update();		
}

void exec_isr() {
	// reset interrupt flag
	PIT_TFLG0 |= 0x00000001;
	PIT_TFLG0;	
	
	// setup PIT duration
	PIT_LDVAL0 = exec_pitVal;
	
	// set exec_flag
	exec_flag = EXEC_FLAG_UP;
	
	// reset frame index
	exec_fI = 0;
}

void exec_run() {	
	while(1) {
		exec_flag = EXEC_FLAG_DOWN;
		
		// is there still a task to run?
		while (exec_fI != schd_schedules[exec_sI].len) {
			// update the cycle count for the task
			schd_schedules[exec_sI].schedule[exec_fI].cycCnt++;
			
			// does the task need to be run?
			if (schd_schedules[exec_sI].schedule[exec_fI].cycCnt == schd_schedules[exec_sI].schedule[exec_fI].per) {
				// reset cycle count for the task
				schd_schedules[exec_sI].schedule[exec_fI].cycCnt = 0;
								
				// is there time to run the task?
				//if (PIT_CVAL0 > schedules[exec_sI].schedule[exec_fI].dur) {					
				schd_schedules[exec_sI].schedule[exec_fI].task();
				//}
					
				// wait for the task to finish executing
				while (*schd_schedules[exec_sI].schedule[exec_fI].flag != EXEC_FLAG_DOWN);
			}			
			
			// increment the frame index
			exec_fI++;
		}
		
		// wait for the next executive cycle to begin
		while (exec_flag != EXEC_FLAG_UP);
	}
}

void exec_update() {
	// disable interrupt
	disable_irq(EXEC_PIT_IRQ_NUM);	
	exec_disablePit();
	exec_flag = EXEC_FLAG_UP;
	exec_fI = 0;
	
	switch (exec_sysMode) {
		case EXEC_MODE_IDLE:
			exec_sI = EXEC_MODE_IDLE;
			mot_motorSpeedA1 = 0;
			mot_motorSpeedA2 = 0;	
			mot_motorSpeedB1 = 0;
			mot_motorSpeedB2 = 0;	
			mot_update();
			serv_angle = SERV_MID_VAL;
			serv_update();
			break;
		case EXEC_MODE_PERF_SPE:
			exec_sI = EXEC_MODE_PERF_SPE;
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_PERF_ACC:
			exec_sI = EXEC_MODE_PERF_ACC;
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_PERF_DIS:
			exec_sI = EXEC_MODE_PERF_DIS;
			mot_motorSpeedA1 = 0;
			mot_motorSpeedA2 = 2000;	
			mot_motorSpeedB1 = 0;
			mot_motorSpeedB2 = 2000;	
			mot_update();
			serv_angle = 0;
			serv_update();
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_TEST_SPE:
			exec_sI = EXEC_MODE_TEST_SPE;
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_TEST_ACC:
			exec_sI = EXEC_MODE_TEST_ACC;
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_TEST_DIS:
			exec_sI = EXEC_MODE_TEST_DIS;
			exec_pitVal = 1000000;
			exec_enablePit();
			break;
		case EXEC_MODE_REMOTE:
			exec_sI = EXEC_MODE_REMOTE;
			mot_motorSpeedA1 = 0;
			mot_motorSpeedA2 = 0;	
			mot_motorSpeedB1 = 0;
			mot_motorSpeedB2 = 0;	
			mot_update();
			serv_angle = 0;
			serv_update();
			break;
	}
	
	// enable interrupt
	enable_irq(EXEC_PIT_IRQ_NUM);
}

void exec_disablePit() {
	PIT_TCTRL0 = 0;
}

void exec_enablePit() {
	PIT_LDVAL0 = exec_pitVal;
	// reset interrupt flag to prevent pending interrupts from triggering
	PIT_TFLG0 |= 0x00000001;
	PIT_TFLG0;
	PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
}
