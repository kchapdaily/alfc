/*
 * schd.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Ryan
 */
#define SCHD
#include "sys.h"

void schd_init() {
	schd_camStartFrame.dur = 0;
	schd_camStartFrame.task = cam_start;
	schd_camStartFrame.flag = &cam_flag;
	schd_camStartFrame.per = 1;
	schd_camStartFrame.cycCnt = 0;
	
	schd_contSpeAccProcFrame.dur = 0;
	schd_contSpeAccProcFrame.task = cont_speAccProc;
	schd_contSpeAccProcFrame.flag = &cont_procFlag;
	schd_contSpeAccProcFrame.per = 1;
	schd_contSpeAccProcFrame.cycCnt = 0;
	
	schd_contSpeAccContFrame.dur = 0;
	schd_contSpeAccContFrame.task = cont_speAccCont;
	schd_contSpeAccContFrame.flag = &cont_contFlag;
	schd_contSpeAccContFrame.per = 1;
	schd_contSpeAccContFrame.cycCnt = 0;
	
	schd_contDisProcFrame.dur = 0;
	schd_contDisProcFrame.task = cont_disProc;
	schd_contDisProcFrame.flag = &cont_procFlag;
	schd_contDisProcFrame.per = 1;
	schd_contDisProcFrame.cycCnt = 0;
	
	schd_contDisContFrame.dur = 0;
	schd_contDisContFrame.task = cont_disCont;
	schd_contDisContFrame.flag = &cont_contFlag;
	schd_contDisContFrame.per = 1;
	schd_contDisContFrame.cycCnt = 0;
	
	schd_motUpdateFrame.dur = 0;
	schd_motUpdateFrame.task = mot_update;
	schd_motUpdateFrame.flag = &mot_flag;
	schd_motUpdateFrame.per = 1;
	schd_motUpdateFrame.cycCnt = 0;
	
	schd_servUpdateFrame.dur = 0;
	schd_servUpdateFrame.task = serv_update;
	schd_servUpdateFrame.flag = &serv_flag;
	schd_servUpdateFrame.per = 1;
	schd_servUpdateFrame.cycCnt = 0;
	
	schd_commsSendFrame.dur = 0;
	schd_commsSendFrame.task = comms_send;
	schd_commsSendFrame.flag = &comms_flag;
	schd_commsSendFrame.per = 1;
	schd_commsSendFrame.cycCnt = 0;	
	
	schd_perfSpeFrames[0] = schd_camStartFrame;
	schd_perfSpeFrames[1] = schd_contSpeAccProcFrame;
	schd_perfSpeFrames[2] = schd_contSpeAccContFrame;
	schd_perfSpeFrames[3] = schd_motUpdateFrame;
	schd_perfSpeFrames[4] = schd_servUpdateFrame;
	
	schd_perfAccFrames[0] = schd_camStartFrame;
	schd_perfAccFrames[1] = schd_contSpeAccProcFrame;
	schd_perfAccFrames[2] = schd_contSpeAccContFrame;
	schd_perfAccFrames[3] = schd_motUpdateFrame;
	schd_perfAccFrames[4] = schd_servUpdateFrame;
	
	schd_perfDisFrames[0] = schd_camStartFrame;
	schd_perfDisFrames[1] = schd_contDisProcFrame;
	schd_perfDisFrames[2] = schd_contDisContFrame;
	schd_perfDisFrames[3] = schd_motUpdateFrame;
	schd_perfDisFrames[4] = schd_servUpdateFrame;
	
	schd_testSpeFrames[0] = schd_camStartFrame;
	schd_testSpeFrames[1] = schd_contSpeAccProcFrame;
	schd_testSpeFrames[2] = schd_contSpeAccContFrame;
	schd_testSpeFrames[3] = schd_motUpdateFrame;
	schd_testSpeFrames[4] = schd_servUpdateFrame;
	schd_testSpeFrames[5] = schd_commsSendFrame;
	
	schd_testAccFrames[0] = schd_camStartFrame;
	schd_testAccFrames[1] = schd_contSpeAccProcFrame;
	schd_testAccFrames[2] = schd_contSpeAccContFrame;
	schd_testAccFrames[3] = schd_motUpdateFrame;
	schd_testAccFrames[4] = schd_servUpdateFrame;
	schd_testAccFrames[5] = schd_commsSendFrame;
	
	schd_testDisFrames[0] = schd_camStartFrame;
	schd_testDisFrames[1] = schd_contDisProcFrame;
	schd_testDisFrames[2] = schd_contDisContFrame;
	schd_testDisFrames[3] = schd_motUpdateFrame;
	schd_testDisFrames[4] = schd_servUpdateFrame;
	schd_testDisFrames[5] = schd_commsSendFrame;
	
	schd_idleSchedule.len = 0;
	schd_idleSchedule.schedule = NULL;
	
	schd_perfSpeSchedule.len = 5;
	schd_perfSpeSchedule.schedule = schd_perfSpeFrames;
	
	schd_perfAccSchedule.len = 5;
	schd_perfAccSchedule.schedule = schd_perfAccFrames;

	schd_perfDisSchedule.len = 5;
	schd_perfDisSchedule.schedule = schd_perfDisFrames;
	
	schd_testSpeSchedule.len = 6;
	schd_testSpeSchedule.schedule = schd_testSpeFrames;
	
	schd_testAccSchedule.len = 6;
	schd_testAccSchedule.schedule = schd_testAccFrames;

	schd_testDisSchedule.len = 6;
	schd_testDisSchedule.schedule = schd_testDisFrames;
	
	schd_remoteSchedule.len = 0;
	schd_remoteSchedule.schedule = NULL;
	
	schd_schedules[0] = schd_idleSchedule;
	schd_schedules[1] = schd_perfSpeSchedule;
	schd_schedules[2] = schd_perfAccSchedule;
	schd_schedules[3] = schd_perfDisSchedule;
	schd_schedules[4] = schd_testSpeSchedule;
	schd_schedules[5] = schd_testAccSchedule;
	schd_schedules[6] = schd_testDisSchedule;
	schd_schedules[7] = schd_remoteSchedule;
}


