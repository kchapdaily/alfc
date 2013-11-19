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
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		
		//setting up UART RX and TX pins
		PORTE_PCR9 = (0|PORT_PCR_MUX(3)); //sets up receive for UART 5 B77
		PORTE_PCR8 = (0|PORT_PCR_MUX(3)); //sets up transmit for UART 5 B76
		
		//NOTE: RXEDGIF interrupt is entered once on power up for some reason
		
		//disable RXEDGIF interrupt through UART status interrupt
		disable_irq(47);	
		
		uint16 sbr = 0;
		uint16 temp = 0;
		uint16 brfa = 0;
		int sysclk = 100000; //in kHz to prevent overflow
		int baud = 9600;
		
		SIM_SCGC1 |= SIM_SCGC1_UART5_MASK; //enable clock on UART 5

		/* Make sure that the transmitter and receiver are disabled while we 
		 * change settings.
		 */
		UART_C2_REG(UART5_BASE_PTR) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

		    /* Configure the UART for 8-bit mode, no parity */
		UART_C1_REG(UART5_BASE_PTR) = 0;	/* We need all default settings, so entire register is cleared */

		//this configures the UART to generate the RXEDGIF interrupt.
		//interrupt is generated when an active edge occurs on RxD pin.
		
		
		//CALCULATING BAUD RATES------------------------------------------------------------
		
		/* Calculate baud settings */
		sbr = (uint16)((sysclk*1000)/(baud * 16));
		        
		/* Save off the current value of the UARTx_BDH except for the SBR field */
		temp = UART_BDH_REG(UART5_BASE_PTR) & ~(UART_BDH_SBR(0x1F));
		    
		UART_BDH_REG(UART5_BASE_PTR) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
		UART_BDL_REG(UART5_BASE_PTR) = (uint8)(sbr & UART_BDL_SBR_MASK);
		    
		/* Determine if a fractional divider is needed to get closer to the baud rate */
		brfa = (((sysclk*32000)/(baud * 16)) - (sbr * 32));
		    
		/* Save off the current value of the UARTx_C4 register except for the BRFA field */
		temp = UART_C4_REG(UART5_BASE_PTR) & ~(UART_C4_BRFA(0x1F));
		    
		UART_C4_REG(UART5_BASE_PTR) = temp |  UART_C4_BRFA(brfa);  
		
		//-----------------------------------------------------------------------------------
		
		//enable fifo for receive and transmit and set datawords for each fifo to be 1 dataword long
		//UART_PFIFO_REG(UART1_BASE_PTR) |= 0x88;

		/* Enable receiver and transmitter */
		UART_C2_REG(UART5_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
			
		//enable RXEDGIF interrupt under UART 1 status interrupt
		UART_BDH_REG(UART5_BASE_PTR) |= RXEDGIF;
		
		enable_irq(47);
		
		comms_flag = EXEC_FLAG_DOWN;
}

void comms_send()
{
	//send one round of frame data
		
		//comms_sendByte((uint8)midpoint);

		//comms_sendByte((uint8)adjustment);
		
		comms_sendByte('a');
		//comms_sendByte((uint8)serv_angle);
		printf("servo angle is %d\n", (uint8)serv_angle);

		comms_sendByte((uint8)mot_speedA);

		comms_sendByte((uint8)mot_speedB);

		/*for (int count = 0; count < error_log_length; count++)
		{
			comms_sendByte((uint8)error_log[count]);
		}*/
}

void comms_sendByte(uint8 input)
{
	//used by comms_send() to send one individual byte

		//wait for FIFO space
		//while (!(UART_S1_REG(UART5_BASE_PTR) & UART_S1_TDRE_MASK));
		//write input data argument to UART data register
		UART_D_REG(UART5_BASE_PTR) = input;
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
		static uint8 left = 0;
		static uint8 right = 0;
		static uint8 go = 0;
		
		static uint8 input = 0;
		
		static float speed = 0; //except this one
		
		
		printf("entered comms_receive\n");
		//printf("status reg 2 contents: 0x%x\n", UART_S2_REG(UART5_BASE_PTR));
		
		
		
		//make sure the interrupt is set
		//if ((UART_C2_REG(UART1_BASE_PTR) & 0x40) == 0x40)
		//{
			/* Wait until character has been received */
			//while (!(UART_S1_REG(UART1_BASE_PTR) & UART_S1_RDRF_MASK));
				
			//write input data argument to UART data register
			input = UART_D_REG(UART5_BASE_PTR);
			printf("UART received 0x%x\n", input);
			
			//print input for testing. comment out when not connected via USB to computer
			//printf("input = %d\n", input);
			
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
		//}
		
		UART_S2_REG(UART5_BASE_PTR) |= RXEDGIF; //clear RXEDGIF interrupt
		
		printf("leaving comms_receive\n");
}
void comms_enable()
{
	SIM_SCGC1 |= SIM_SCGC1_UART5_MASK; //enable UART5
}
void comms_disable(){
	
	SIM_SCGC1 &= ~SIM_SCGC1_UART5_MASK; //disable UART5 clock

}


