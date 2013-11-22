/*
 * serv.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */

#ifndef SERV_H_
#define SERV_H_

void serv_init();
void serv_update();

#define SERV_RET_SUCCESS	0
#define SERV_MOD_INIT		62499
#define SERV_OFFSET_VAL		4000
#define SERV_MIN_VAL		0
#define SERV_MAX_VAL		2062
#define SERV_MID_VAL		1031

#ifdef SERVO
volatile int serv_angle;
int serv_flag;
#else
extern volatile int serv_angle;
extern int serv_flag;
#endif

#endif /* SERV_H_ */
