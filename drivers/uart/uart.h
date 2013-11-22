/*
 * File:		uart.h
 * Purpose:     Provide common ColdFire UART routines for polled serial IO
 *
 * Notes:
 */

#ifndef __UART_H__
#define __UART_H__

/********************************************************************/

void uart_init (UART_MemMapPtr, int, int);
uint8 uart_getchar (UART_MemMapPtr);
void uart_putchar (UART_MemMapPtr, uint8);
int uart_getchar_present (UART_MemMapPtr);

/********************************************************************/

#endif /* __UART_H__ */
