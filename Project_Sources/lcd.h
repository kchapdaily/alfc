/*
 * lcd.h
 *
 *  Created on: Oct 25, 2013
 *      Author: Ryan
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_RET_SUCCESS		0
#define LCD_RET_INVALID_ARG	1

int lcd_init();
int lcd_setDigit0(char val);
int lcd_setDigit1(char val);
int lcd_setDigit2(char val);
int lcd_update();
void tlcd_set_numeric1(int n);
void tlcd_set_numeric2(int n);
void tlcd_set_numeric3(int n);


#endif /* LCD_H_ */
