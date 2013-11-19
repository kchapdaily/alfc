/*
 * ui.h
 *
 *  Created on: Nov 8, 2013
 *      Author: Ryan
 */

#ifndef UI_H_
#define UI_H_

#define UI_RET_SUCCESS 0

#define UI_PERF		0
#define UI_TEST		1
#define UI_REMOTE	2
#define UI_PERF_SPE	3
#define UI_PERF_ACC	4
#define UI_PERF_DIS	5
#define UI_PERF_RET	6
#define UI_TEST_SPE	7
#define UI_TEST_ACC	8
#define UI_TEST_DIS	9
#define UI_TEST_RET	10

int ui_init();
void ui_isr();

#ifdef UI
volatile int ui_menuState;
#else
extern volatile int ui_menuState;
#endif

#endif /* UI_H_ */
