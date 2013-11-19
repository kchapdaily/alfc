/*
 * exec.h
 *
 *  Created on: Oct 26, 2013
 *      Author: Ryan
 */

#ifndef EXEC_H_
#define EXEC_H_

#define EXEC_PIT_IRQ_NUM	68

#define EXEC_FLAG_UP		0
#define EXEC_FLAG_DOWN		1

#define EXEC_MODE_IDLE		0
#define EXEC_MODE_PERF_SPE	1
#define EXEC_MODE_PERF_ACC	2
#define EXEC_MODE_PERF_DIS	3
#define EXEC_MODE_TEST_SPE	4
#define EXEC_MODE_TEST_ACC	5
#define EXEC_MODE_TEST_DIS	6
#define EXEC_MODE_REMOTE	7

void exec_init();
void exec_isr();
void exec_run();
void exec_update();
void exec_enablePit();
void exec_disablePit();

#ifdef EXEC
volatile int exec_sysMode;
volatile int exec_flag;
int exec_sI;
int exec_fI;
int exec_pitVal;
#else
extern volatile int exec_sysMode;
extern volatile int exec_flag;
extern int exec_sI;
extern int exec_fI;
extern int exec_pitVal;
#endif

#endif /* EXEC_H_ */
