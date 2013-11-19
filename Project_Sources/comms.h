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
void comms_sendByte(uint8); //used by comms_send() to send one individual byte
void comms_receive(); //receives data on an interrupt, handles accordingly, and makes necessary adjustments
void comms_enable(); //enables the reception of data. call before any data can be received
void comms_disable(); //disables the reception of data. can be used to prevent uart interrupt from affecting other tasks

#ifdef COMMS
volatile int comms_flag;
#else
extern volatile int comms_flag;
#endif

#endif /* MAIN_H_ */

