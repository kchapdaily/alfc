/*
 * mot.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */

#ifndef MOT_H_
#define MOT_H_

void mot_init();
void mot_enable();
void mot_update();

#define MOT_MOD_INIT		4999

#define MOT_MAX_VAL			4999
#define MOT_MIN_VAL			0

#ifdef MOT
volatile int mot_speedA;
int mot_motorSpeedA1;
int mot_motorSpeedA2;
volatile int mot_speedB;
int mot_motorSpeedB1;
int mot_motorSpeedB2;
int mot_flag;
#else
extern volatile int mot_speedA;
extern int mot_motorSpeedA1;
extern int mot_motorSpeedA2;
extern volatile int mot_speedB;
extern int mot_motorSpeedB1;
extern int mot_motorSpeedB2;
extern int mot_flag;
#endif

#endif /* MOT_H_ */
