/*
 * main.h
 *
 *  Created on: Nov 6, 2013
 *      Author: Kevin Chapman
 */

#ifndef MAIN_H_
#define MAIN_H_

#define COMMS_RET_SUCCESS 0

void comms_init(); //call this before the uart can be used
void comms_send(); //send one round of frame data
void comms_receive(); //receives data on an interrupt, handles accordingly, and makes necessary adjustments

#ifdef COMMS
volatile int comms_flag;
#else
extern volatile int comms_flag;
#endif

#endif /* MAIN_H_ */

