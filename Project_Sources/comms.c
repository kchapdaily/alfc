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
	uart_putchar(UART5_BASE_PTR, 'a');

	//uart_putchar(UART5_BASE_PTR, (char)adjustment);
	uart_putchar(UART5_BASE_PTR, 'b');
			
	//uart_putchar(UART5_BASE_PTR, (char)serv_angle);
	uart_putchar(UART5_BASE_PTR, 'c');

	//uart_putchar(UART5_BASE_PTR, (char)mot_speedA);
	uart_putchar(UART5_BASE_PTR, 'd');

	//uart_putchar(UART5_BASE_PTR, (char)mot_speedB);
	uart_putchar(UART5_BASE_PTR, 'e');
}

void comms_receive()
{
	//receives data on ? interrupt, handles accordingly, and makes necessary adjustments
	/*	possible input values are as follows:
	 * 	left, right, go, and speed.
	 * 	
	 * 	a select byte will be sent previous to a data byte. the select byte will be as follows:
	 * 	
	 * 	[00000001] : left
	 * 	[00000010] : right
	 * 	[00000011] : go
	 * 	[00000100] : speed
	 */
	
	static uint8 dataSelect = 0; //represents what the next piece of data is going to be
	static uint8 dataNext = 0; //if this var is high, there is data to be processed
	
	//these vars will be toggled on input
	static char left = 0;
	static char right = 0;
	static char go = 0;
	
	char input = 0;
	char oldInput = 1;
	
	static float speed = 0; //except this one
	
	
	//printf("entered comms_receive\n");
	//printf("status reg 2 contents: 0x%x\n", UART_S2_REG(UART5_BASE_PTR));
	
	input = uart_getchar(UART5_BASE_PTR);
	
		printf("UART received %i\n", input);
		
		if (dataNext == 0)
		{
			if (input == 1)
			{
				//next byte is left command
				dataSelect = 1;
				dataNext = 1;
			}
			
			if (input == 2)
			{
				//next byte is right command
				dataSelect = 2;
				dataNext = 1;
			}
			
			if (input == 3)
			{
				//next byte is go command
				dataSelect = 3;
				dataNext = 1;		
			}
			
			if (input == 3)
			{
				//next byte is speed command
				dataSelect = 4;
				dataNext = 1;				
			}
		}
		
		if (dataNext == 1)
		{
			if (dataSelect == 1)
			{
				left = !left;
				if (left == 1)
				{
					serv_angle = 0;
				}
				else
				{
					serv_angle = 1031;
				}
				serv_update();
			}
			
			if (dataSelect == 2)
			{
				right = !right;
				if (right == 1)
				{
					serv_angle = 2062;
				}
				else
				{
					serv_angle = 1031;
				}
				
				serv_update();
				
			}
			
			if (dataSelect == 3){
				go = !go;
				
			}
			
			if (dataSelect == 4){
				speed = (float)input;
				
				if (go == 1)
				{
					mot_motorSpeedA1 = 0000;
					mot_motorSpeedA2 = (int)(speed*2000);
				
					mot_motorSpeedB1 = 0000;
					mot_motorSpeedB2 = (int)(speed*2000);
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
			
			dataNext = 0;
			dataSelect = 0;
		}	
	
	//printf("leaving comms_receive\n");
	oldInput = input;
}


