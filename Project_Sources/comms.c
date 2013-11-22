/*
 * main.h
 *
 *  Created on: Nov 6, 2013
 *      Author: Kevin Chapman
 */

#define COMMS
#include "sys.h"

void comms_init(){
	//call this before the UART can be used
	
	// enable the clock for Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	//setting up UART RX and TX pins
	PORTE_PCR9 = (0|PORT_PCR_MUX(3)); //sets up receive for UART 5 B77
	GPIOE_PDDR &= ~GPIO_PDDR_PDD(GPIO_PIN(9)); //set up pin 9 as an input (0)
	
	PORTE_PCR8 = (0|PORT_PCR_MUX(3)); //sets up transmit for UART 5 B76
	GPIOE_PDDR |= GPIO_PDDR_PDD(GPIO_PIN(8)); //set up pin 8 as an output (1)

			
	//initialize UART
	uart_init(UART5_BASE_PTR, 50000, 115200);
	
	comms_flag = EXEC_FLAG_DOWN;
}

void comms_send()
{
	//send one round of frame data
		
	//uart_putchar(UART5_BASE_PTR, (char)midpoint);
	uart_putchar(UART5_BASE_PTR, (uint8)'a');

	//uart_putchar(UART5_BASE_PTR, (char)adjustment);
	uart_putchar(UART5_BASE_PTR, (uint8)'b');
			
	//uart_putchar(UART5_BASE_PTR, serv_angle);
	uart_putchar(UART5_BASE_PTR, 'c');

	//uart_putchar(UART5_BASE_PTR, mot_motorSpeedA2);
	uart_putchar(UART5_BASE_PTR, 'd');

	//uart_putchar(UART5_BASE_PTR, mot_motorSpeedB2);
	uart_putchar(UART5_BASE_PTR, 'e');
}

void comms_receive()
{
	/*	possible input values are as follows:
	 * 	left, right, go, and speed.
	 * 	
	 * 	a select byte will be sent previous to a data byte. the select byte will be as follows:
	 * 	
	 * 	1 : left
	 * 	2 : right
	 * 	3 : go
	 * 	4 : speed
	 */
	
	int dataSelect = 0;
	int dataInput = 0;
	
	static int left = 0;
	static int right = 0;
	static int go = 0;
	//static int speed = 0; //should be between 0 and 10
	
	
	dataSelect = (int)uart_getchar(UART5_BASE_PTR);
	//comms_send((uint8)dataSelect);
	//dataInput = (int)uart_getchar(UART5_BASE_PTR);
	
	//printf("data select: %i\n", dataSelect);
	//printf("data input: %i\n", dataInput);
	
	if (dataSelect == 49)
	{
		left = ((left == 1)?0:1);
		
		if (left == 1)
		{
			serv_angle = 0;
		}
		else
		{
			serv_angle = 1031;
		}
		serv_update();
		
		//comms_send((uint8)'s');
		//comms_send((uint8)'L');
	}
	
	if (dataSelect == 50)
	{
		
		right = ((right == 1)?0:1);
		
		if (right == 1)
		{
			serv_angle = 2062;
		}
		else
		{
			serv_angle = 1031;
		}
		
		serv_update();
		//comms_send((uint8)'s');
		//comms_send((uint8)'R');
	}
			
		
	if (dataSelect == 51)
	{
		go = ((go == 1)?0:1);
		
		/*if (go == 1)
		{
			mot_motorSpeedA1 = 0000;
			mot_motorSpeedA2 = 2000;
		
			mot_motorSpeedB1 = 0000;
			mot_motorSpeedB2 = 2000;
		}
		else
		{
			mot_motorSpeedA1 = 0000;
			mot_motorSpeedA2 = 0000;
			
			mot_motorSpeedB1 = 0000;
			mot_motorSpeedB2 = 0000;
		}
		
		mot_update();*/
		
		//comms_send((uint8)'s');
		//comms_send((uint8)'G');
		
		
		
		dataSelect = 52; //we need to go update motor speeds
		
	}
	
	if (dataSelect == 52){
		speed = dataInput;
		//printf("speed command: %i\n", speed);
		
		if (go == 1)
		{
			mot_motorSpeedA1 = 0000;
			mot_motorSpeedA2 = (speed*350);
		
			mot_motorSpeedB1 = 0000;
			mot_motorSpeedB2 = (speed*350);
		}
		else
		{
			mot_motorSpeedA1 = 0000;
			mot_motorSpeedA2 = 0000;
			
			mot_motorSpeedB1 = 0000;
			mot_motorSpeedB2 = 0000;
		}
		
		mot_update();
	}
}


