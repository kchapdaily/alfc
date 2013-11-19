/*
 * schd.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */

#ifndef SCHD_H_
#define SCHD_H_

void schd_init();

#define SCHD_NUM_SCHEDULES	8

typedef struct {
	int dur;
	void (* task)();
	volatile int  *flag;
	int per;
	int cycCnt;
} frame_t;

typedef struct {
	int len;
	frame_t *schedule;
} schedule_t;

#ifdef SCHD
schedule_t schd_schedules[SCHD_NUM_SCHEDULES];

frame_t	schd_camStartFrame;
frame_t schd_contSpeAccProcFrame;
frame_t schd_contDisProcFrame;
frame_t schd_contSpeAccContFrame;
frame_t schd_contDisContFrame;
frame_t schd_motUpdateFrame;
frame_t schd_servUpdateFrame;
frame_t schd_commsSendFrame;

frame_t schd_idleFrames[0];
frame_t schd_perfSpeFrames[5];
frame_t schd_perfAccFrames[5];
frame_t schd_perfDisFrames[5];
frame_t schd_testSpeFrames[6];
frame_t schd_testAccFrames[6];
frame_t schd_testDisFrames[6];
frame_t schd_remoteFrames[0];

schedule_t schd_idleSchedule;
schedule_t schd_perfSpeSchedule;
schedule_t schd_perfAccSchedule;
schedule_t schd_perfDisSchedule;
schedule_t schd_testSpeSchedule;
schedule_t schd_testAccSchedule;
schedule_t schd_testDisSchedule;
schedule_t schd_remoteSchedule;
#else
extern schedule_t schd_schedules[SCHD_NUM_SCHEDULES];

extern frame_t schd_camStartFrame;
extern frame_t schd_contSpeAccProcFrame;
extern frame_t schd_contDisProcFrame;
extern frame_t schd_contSpeAccContFrame;
extern frame_t schd_contDisContFrame;
extern frame_t schd_motUpdateFrame;
extern frame_t schd_servUpdateFrame;
extern frame_t schd_commsSendFrame;

extern frame_t schd_idleFrames[0];
extern frame_t schd_perfSpeFrames[5];
extern frame_t schd_perfAccFrames[5];
extern frame_t schd_perfDisFrames[5];
extern frame_t schd_testSpeFrames[6];
extern frame_t schd_testAccFrames[6];
extern frame_t schd_testDisFrames[6];
extern frame_t schd_remoteFrames[0];

extern schedule_t schd_idleSchedule;
extern schedule_t schd_perfSpeSchedule;
extern schedule_t schd_perfAccSchedule;
extern schedule_t schd_perfDisSchedule;
extern schedule_t schd_testSpeSchedule;
extern schedule_t schd_testAccSchedule;
extern schedule_t schd_testDisSchedule;
extern schedule_t schd_remoteSchedule;
#endif

#endif /* SCHD_H_ */
