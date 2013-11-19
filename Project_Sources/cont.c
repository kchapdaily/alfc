/*
 * cont.c
 *
 *  Created on: Nov 8, 2013
 *      Author: Ryan
 */
#define CONT
#include "sys.h"

void cont_init() {
	cont_flag = EXEC_FLAG_DOWN;
	numcounts = -1;
	lapsremaining = 4;
	oldservangle = 1031;
	lostline = 0;
	maxspeed = 3000;
	speed = 3000;
	differential_in = 1.25; //1; //Subtract speed from inside wheel. Increasing decreases amount of speed subtracted
	differential_out = 2; //3; //Add speed to outside wheel, doubling divides added speed by 2
	differential_out_brake = 64; // Subtract speed from outside wheel under large correction values
	diff_div = 2500;
	correctionval = 50;
	center1 = 50;
	P = 0;
	kp = .6;// .4; 
	I = 0;
	ki = .35;
	D = 0;
	kd = 2; //.5;
	prev_error = 0;
	cont_lineLoc = -1;
	
	cont_procFlag = EXEC_FLAG_DOWN;
	cont_contFlag = EXEC_FLAG_DOWN;
}

void cont_speAccProc() {
	// debug only
	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	
	float float_serv_angle = 0;	
	int error = 0;
	int smoothing;
	int averages[124];
	int average;
	int min_contrast = 60;
	int offset = -4;
	int serv_center = 1031;
	int div_brake = 5;
	int difference = 0;
	int total = 0;
	int calcwidth = -1;
	int leftedge = 0;
	int rightedge = 0;
	int center = -1;	
	int linewidth = -1;
	int i = 2; 
	int exp_line = 12;// Set expected line width
	int tolerance = 4; //set the expected tolerance

	// 
	for (i=2; i<126; i++){
		smoothing = (adc_rawCameraData[i+0]+adc_rawCameraData[i-1]+adc_rawCameraData[i-2]+adc_rawCameraData[i+1]+adc_rawCameraData[i+2])/5;
		averages[i-2] = smoothing;
	}

		for (i=0; i<100; i++){
			difference = averages[i+12]-averages[i+11];
			derivative[i] = abs(difference);
			total = total+derivative[i];
		}
	        
		average = total/100;
		//Calculate the Cutoff value, and bound the cutoff // 
		cutoff = average*3;  //////
		if (cutoff < 8){
			cutoff = 8;
		}
		else if (cutoff > 20){
			cutoff = 20;
		}

		for (i=0; i<100; i++){
			if (derivative[i] > cutoff){
				flag[i] = 1;
			}
			else{
				flag[i] = 0;
			}
		}

		for (i=3; i<96; i++){
			if (flag[i] == 1 && leftedge ==0){
				if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1){
					leftedge = i;
					while (flag[i+1]==1|| flag[i+2] ==1 ){
						if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1|| flag[i+3] ==1 || flag[i-3] ==1  ){
							leftedge = i;
							i++;
						}
					}
				}
			}
			else if (flag[i] == 1 && leftedge !=0 && rightedge ==0 && i> leftedge +4 ){
				if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1 ){
					while ((flag[i+1]==1 || flag[i+2]==1)&& i<96){
						if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1 || flag[i+3] ==1 || flag[i-3] ==1  ){
							rightedge = i;
							i++;
						}
					}
				}
			}
			
			if (leftedge != 0 && rightedge != 0){
				calcwidth = rightedge - leftedge;
				
				if (calcwidth < (exp_line +tolerance) && calcwidth > (exp_line -tolerance)){  //Is it the size of the line?
					if (averages[leftedge+8]>(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)<averages[rightedge+16]){   // Is it a white to black transition?
						linewidth = calcwidth;
						center = ((leftedge + rightedge)/2)+offset;  
						
						leftedge = rightedge;
						rightedge = 0;
						
						
					}
					else if ((averages[leftedge+8]<(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)>averages[rightedge+16]&& (averages[rightedge+8]+min_contrast)>averages[rightedge+0])||(averages[leftedge+8]<(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)>averages[rightedge+16]&& (averages[rightedge+8]+min_contrast)>averages[rightedge+36])){
						
						inframe = 1;
						leftedge = rightedge;
						rightedge = 0;
					}
						
					
					else {   // Is it a white to black transition?
						leftedge = rightedge;   //We don't care, so set leftedge to be rightedge and keep looking
						rightedge = 0;
					}
				}

				else{
					leftedge = rightedge;
					rightedge = 0;
		
				}
			}
		}
		
		
		if (inframe == 1 && center != -1 && center > 25 && center < 75){
			inframe = 0;
			numcounts = 5;
			
		}
		
		else if (inframe == 0 && numcounts > 0 && center != -1 && center > 25 && center < 75){
			numcounts--;
		}
		else if (inframe == 0 && numcounts == 0 && center != -1 && lapsremaining > 0){
			lapsremaining--;
			numcounts = -1;
			
		}
		
		
		
		
		

		
		cont_lineWidth = linewidth;
		if (center >= 0){
			cont_lineLoc = center;
		}
		
		ones=lapsremaining%10;
		tens=(lapsremaining/10)%10;
		hundreds=(lapsremaining/100)%10;

		//Update SLCD
		tlcd_set_numeric3(ones); // ones
		tlcd_set_numeric2(tens); // tens
		tlcd_set_numeric1(hundreds); // hundreds
		
		
		
		
		
	////////////////////////////////////////////
	////////////////////////////////////////////
		/// Check to see if we've lost the line ///
		if (center >= 0){
			if (lostline > 0){
				lostline--;
			}
		}
		
		else if (center == -1 && lostline < 500){
			
			lostline++;
		}

		
		////PID///////
		
		
		
		if (cont_lineLoc >= 0){
			error = -(50-cont_lineLoc);
			P = error * kp;
			I = (I+error)*ki;
			if (I > 50){I = 50;}
			D = error - prev_error;
			D = D * kd;
			correctionval = P+I+D;
			if (correctionval > 50){
				correctionval = 50;
			}
			else if (correctionval < -50){
				correctionval = -50;
			}
			
			correctionval = (correctionval*serv_center)/50;

			correctionval = (serv_center+correctionval);
			serv_angle = correctionval;
		}
		else{
			serv_angle = oldservangle;
		}
		
		prev_error = error;
		/// Update Servo //////
		oldservangle = serv_angle;
		serv_update();
		float_serv_angle = serv_angle;
		//////Set Motor Speeds///////	
		
		if (lapsremaining <= 0 || lostline >= 50){
			mot_motorSpeedA1 = 1000;
			mot_motorSpeedA2 = 000;
			
			mot_motorSpeedB1 = 1000;
			mot_motorSpeedB2 = 000;
			
			mot_update();
		}
		
		else if (serv_angle < 1431 && serv_angle > 631 ){
			mot_motorSpeedA1 = 0000;
			mot_motorSpeedA2 = speed;
			
			mot_motorSpeedB1 = 0000;
			mot_motorSpeedB2 = speed;
			
			mot_update();
		}
		
		
		
		else{
			
			if( serv_angle < 631 ){
				mot_motorSpeedA1 = 0000;
				mot_motorSpeedA2 = speed - (((serv_center-float_serv_angle)/serv_center)*(((speed/diff_div)*speed)/differential_in));
				
				mot_motorSpeedB1 = 0000;
				mot_motorSpeedB2 = speed + ((((serv_center-float_serv_angle)/serv_center)*(((speed/diff_div)*speed)/differential_out)));// - (delta_cent * 30);
							
				
				if (mot_motorSpeedA2 < 0 ){
					mot_motorSpeedA1 = abs(speed - (((serv_center-float_serv_angle)/serv_center)*(((speed/diff_div)*speed)/differential_in)));
					mot_motorSpeedA2 = 0000;	
				}
				
				if (abs(D) > div_brake){
					mot_motorSpeedB1 = 0000;
					mot_motorSpeedB2 = speed - ((((serv_center-float_serv_angle)/serv_center)*(((speed/diff_div)*speed)/differential_out_brake)));// - (delta_cent * 30);
				}
				
				
				mot_update();
			}	
			else if (serv_angle > 1431){
				mot_motorSpeedA1 = 0000;
				mot_motorSpeedA2 = speed + ((((float_serv_angle-serv_center)/serv_center)*(((speed/diff_div)*speed)/differential_out)));
				
				mot_motorSpeedB1 = 0000;
				mot_motorSpeedB2 = speed - (((float_serv_angle-serv_center)/serv_center)*(((speed/diff_div)*speed)/differential_in));
				
				if (mot_motorSpeedB2 < 0){

					mot_motorSpeedB1 = abs(speed - (((float_serv_angle-serv_center)/serv_center)*(((speed/diff_div)*speed)/differential_in)));
					mot_motorSpeedB2 = 0000;
				}
				
				if (abs(D) > div_brake){
					mot_motorSpeedA1 = 0000;
					mot_motorSpeedA2 = speed - ((((float_serv_angle-serv_center)/serv_center)*(((speed/diff_div)*speed)/differential_out_brake)));
				}
				
				mot_update();
			}
				
				
		}
}

void cont_speAccCont() {
	
}

void cont_disProc() {
	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	int error = 0;
    int smoothing;
    int averages[124];
    int average;
    int min_contrast = 40;


    int difference = 0;
    int total = 0;

    int calcwidth = -1;
    int leftedge = 0;
    int rightedge = 0;
    int center = -1;
    int oldcenter = 50;
    int linewidth = -1;
    int i = 2; 

    int exp_line = 12;// Set expected line width
    //int exp_ssline = 10; // Set expected SSLine width
    int tolerance = 4; //set the expected tolerance

    for (i=2; i<126; i++){
		smoothing = (adc_rawCameraData[i+0]+adc_rawCameraData[i-1]+adc_rawCameraData[i-2]+adc_rawCameraData[i+1]+adc_rawCameraData[i+2])/5;
		averages[i-2] = smoothing;
    }

	for (i=0; i<100; i++){
		difference = averages[i+12]-averages[i+11];
		derivative[i] = abs(difference);
		total = total+derivative[i];
	}
        
	average = total/100;

	cutoff = average*3;  //////
	if (cutoff < 4){
		cutoff = 4;
	}

	for (i=0; i<100; i++){
		if (derivative[i] > cutoff){
			flag[i] = 1;
		}
		else{
			flag[i] = 0;
		}
	}

	for (i=3; i<96; i++){
		if (flag[i] == 1 && leftedge ==0){
			if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1){
				leftedge = i;
				while (flag[i+1]==1|| flag[i+2] ==1 ){
					if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1|| flag[i+3] ==1 || flag[i-3] ==1  ){
						leftedge = i;
						i++;
					}
				}
			}
		}
		else if (flag[i] == 1 && leftedge !=0 && rightedge ==0 && i> leftedge +4 ){
			if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1 ){
				while ((flag[i+1]==1 || flag[i+2]==1)&& i<96){
					if(flag[i-1] == 1 || flag[i-2] ==1 || flag[i+1] == 1 || flag[i+2] ==1 || flag[i+3] ==1 || flag[i-3] ==1  ){
						rightedge = i;
						i++;
					}
				}
			}
		}
		
		if (leftedge != 0 && rightedge != 0){
			calcwidth = rightedge - leftedge;
			
			if (calcwidth < (exp_line +tolerance) && calcwidth > (exp_line -tolerance)){  //Is it the size of the line?
				if (averages[leftedge+8]>(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)<averages[rightedge+16]){   // Is it a white to black transition?
					
					center = ((leftedge + rightedge)/2)-1;  
					
					leftedge = rightedge;
					rightedge = 0;
					
					
				}
				else if ((averages[leftedge+8]<(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)>averages[rightedge+16]&& (averages[rightedge+8]+min_contrast)>averages[rightedge+0])||(averages[leftedge+8]<(averages[leftedge+16]+min_contrast) && (averages[rightedge+8]+min_contrast)>averages[rightedge+16]&& (averages[rightedge+8]+min_contrast)>averages[rightedge+36])){
					linewidth = calcwidth;
					inframe = 1;
					leftedge = rightedge;
					rightedge = 0;
				}
					
				
				else {   // Is it a white to black transition?
					leftedge = rightedge;   //We don't care, so set leftedge to be rightedge and keep looking
					rightedge = 0;
				}
			}

			else{
				leftedge = rightedge;
				rightedge = 0;
	
			}
		}
	}
	
	
	if (inframe == 1 && center != -1 && center > 25 && center < 75){
		inframe = 0;
		numcounts = 50;
		
	}
	
	else if (inframe == 0 && numcounts > 0 && center != -1 && center > 25 && center < 75){
		numcounts--;
	}
	else if (inframe == 0 && numcounts == 0 && center != -1 && center > 25 && center < 75 && lapsremaining > 0){
		lapsremaining--;
		numcounts = -1;
		
	}
	
	
	
	
	
	
//	if (center == -1){
//		center = oldcenter;
//	}
//	oldcenter = center;
	cont_lineWidth = linewidth;
	cont_lineLoc = center;
//	
//	ones=cont_lineLoc%10;
//	tens=(cont_lineLoc/10)%10;
//	hundreds=(cont_lineLoc/100)%10;
//
//	//Update SLCD
//	tlcd_set_numeric3(ones); // ones
//	tlcd_set_numeric2(tens); // tens
//	tlcd_set_numeric1(hundreds); // hundreds
	
	
	
	
	
	
	
	
	if (cont_lineLoc >= 0){
		
		error = cont_lineLoc-50;
		correctionval = error+50;
		//serv_angle = (correctionval * 2062) / 100;
	}
	else{
		//serv_angle = oldservangle;
	}
	
	//oldservangle = serv_angle;
	
	//serv_update();
	
	if (center >= 0){
		if (lostline > 0){
			lostline--;
		}
	}
	
	else if (center == -1 && lostline < 701){
		
		lostline++;
	}

	
	
	
//	if (lapsremaining <= 0 || lostline >= 100){
//		mot_motorSpeedA1 = 000;
//		mot_motorSpeedA2 = 000;
//		
//		mot_motorSpeedB1 = 000;
//		mot_motorSpeedB2 = 000;
//		
//		mot_update();
//	}
//	
//	else if (serv_angle < 1100 && serv_angle > 962){
//		mot_motorSpeedA1 = 0000;
//		mot_motorSpeedA2 = maxspeed;
//		
//		mot_motorSpeedB1 = 0000;
//		mot_motorSpeedB2 = maxspeed;
//		
//		mot_update();
//	}
//	
//	else{
//		
//		if( serv_angle > 1100 ){
//			mot_motorSpeedA1 = 0000;
//			mot_motorSpeedA2 = maxspeed - (((serv_angle-1100)*2));
//			
//			mot_motorSpeedB1 = 0000;
//			mot_motorSpeedB2 = maxspeed;
//			
//			mot_update();
//		}	
//		else if (serv_angle < 962){
//			mot_motorSpeedA1 = 0000;
//			mot_motorSpeedA2 = maxspeed;
//			
//			mot_motorSpeedB1 = 0000;
//			mot_motorSpeedB2 = maxspeed - (((962-serv_angle)*2));
//			
//			mot_update();
//		}
//			
//			
//	}
		
	if (cont_lineLoc != -1) {
		// motor setup
//		mot_motorSpeedA1 = 0000;
//		mot_motorSpeedA2 = 0000;	
//		mot_motorSpeedB1 = 0000;
//		mot_motorSpeedB2 = 0000;	
//		mot_update();
		exec_sysMode = EXEC_MODE_PERF_SPE;
		exec_update();
	}
	
	cont_disServUpdateCnt++;
	if (cont_disServUpdateCnt == 100) {
		if (serv_angle < CONT_DIS_SERV_MAX) {
			serv_angle += CONT_DIS_SERV_INC;
			serv_update();
		}
		cont_disServUpdateCnt = 0;
	}
}

void cont_disCont() {
	
}
