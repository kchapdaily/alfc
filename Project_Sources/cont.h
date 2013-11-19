/*
 * cont.h
 *
 *  Created on: Nov 8, 2013
 *      Author: Ryan
 */

#ifndef CONT_H_
#define CONT_H_

#define CONT_RET_SUCCESS 0

#define CONT_DIS_SERV_MAX 800
#define CONT_DIS_SERV_INC 50

void cont_init();
void cont_speAccProc();
void cont_speAccCont();
void cont_disProc();
void cont_disCont();

#ifdef CONT
int cont_lineWidth;
int cont_lineLoc;
int cont_flag;
int derivative[100];
int flag[100];
int cutoff;
int numcounts;
int lapsremaining;
int inframe;
int oldservangle;
int lostline;
float maxspeed;
float speed;
float differential_in;
float differential_out;
float differential_out_brake;
int correctionval;
int delta_cent;
int P;
float kp;
int I;
float ki;
int D;
float kd;
int prev_error;
int center1;
int diff_div;
int cont_disServUpdateCnt;
int cont_procFlag;
int cont_contFlag;
#else
extern int cont_lineWidth;
extern int cont_lineLoc;
extern int cont_flag;
extern int derivative[100];
extern int flag[100];
extern int cutoff;
extern int numcounts;
extern int lapsremaining;
extern int inframe;
extern int oldservangle;
extern int lostline;
extern float maxspeed;
extern float speed;
extern float differential_in;
extern float differential_out;
extern float differential_out_brake;
extern int correctionval;
extern int delta_cent;
extern int P;
extern float kp;
extern int I;
extern float ki;
extern int D;
extern float kd;
extern int prev_error;
extern int center1;
extern int diff_div;
extern int cont_disServUpdateCnt;
extern int cont_procFlag;
extern int cont_contFlag;
#endif

#endif /* CONT_H_ */
