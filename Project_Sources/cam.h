/*
 * cam.h
 *
 *  Created on: Oct 26, 2013
 *      Author: Ryan
 */

#ifndef CAM_H_
#define CAM_H_

#define CAM_RET_SUCCESS		0

#define CAM_MOD_INIT		899
#define CAM_CLK_COUNT		0

int cam_enable();
int cam_disable();
int cam_init();
void cam_isr();
void cam_start();

#ifdef CAM
int cam_clockCounter;
int frame = 0; // delete this
volatile int cam_flag;
#else
extern int cam_clockCounter;
extern int frame;
extern volatile int cam_flag;
#endif

#endif /* CAM_H_ */
