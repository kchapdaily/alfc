/*
 * sys.h
 *
 *  Created on: Oct 25, 2013
 *      Author: Ryan
 */

#ifndef SYS_H_
#define SYS_H_

#include "common.h"
#include "mcg.h"

#include "adc.h"
#include "cam.h"
#include "exec.h"
#include "hl.h"
#include "lcd.h"
#include "mot.h"
#include "schd.h"
#include "serv.h"
#include "cont.h"
#include "comms.h"
#include "ui.h"

// general
#define BIT(var, pos) 		(((var) & (1<<(pos))) >> pos)
#define GPIO_PIN_MASK		0x1Fu
#define GPIO_PIN(x)			(((1)<<(x & GPIO_PIN_MASK)))

// system mode
#define SYS_IDLE_MODE		0
#define SYS_BUSY_MODE		1
#define SYS_SPEED_MODE		2
#define SYS_ACCURACY_MODE	3
#define SYS_DISCOVERY_MODE	4
#define SYS_REMOTE_MODE		5
#define SYS_TEST_MODE		6

#endif /* SYS_H_ */
