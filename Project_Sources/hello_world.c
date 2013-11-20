/*
 * File:		hello_world.c
 * Purpose:		Main process
 *
 */

#include "sys.h"

/********************************************************************/
int main (void)
{
	exec_init();
	//exec_run();
	while (1)
	{
		comms_send();
		comms_receive();
	}
	return 0;
}
/********************************************************************/
