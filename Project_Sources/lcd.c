/*
 * lcd.c
 *
 *  Created on: Oct 25, 2013
 *      Author: Ryan
 */
#include "sys.h"

int lcd_init() {
	// to enable the Internal Reference Clock
	MCG_C1 |= 0x02;

	// to enabled the LCD clocks
	SIM_SCGC3 = 0x40000000;

	// to enable LCD pins 0, 1, 2, 3, 12, 13, 14, 15, 20, 21, 22:
	LCD_PENL = 0x0070F00F;
	
	// to enable LCD backplanes 0, 1, 2, 3
	LCD_BPENL = 0x0000000F;

	// to assign LCD backplanes – 0 is BP1, 1 is BP2, etc.
	LCD_WF3TO0 = 0x08040201;

	// to configure the LCD General Control Register
	LCD_GCR |= LCD_GCR_VSUPPLY(1);
	LCD_GCR |= LCD_GCR_CPSEL_MASK;
	LCD_GCR |= LCD_GCR_DUTY(3);
	LCD_GCR |= LCD_GCR_SOURCE_MASK;
	LCD_GCR |= LCD_GCR_LCLK(4);

	// clear all 3 digits
	LCD_WF23TO20 &= 0x00000000;
	LCD_WF15TO12 &= 0x00000000;
	
	// to enable the LCD
	LCD_GCR |= LCD_GCR_LCDEN_MASK;	
	
	return LCD_RET_SUCCESS;
}

int lcd_setDigit0(char val) {
	LCD_WF23TO20 &= 0xFF00FF00;

	if (BIT(val,0) == 1) {
		// if val(0) == 1, turn on A segment
		LCD_WF23TO20 |= 0x00000001;
	}
	
	if (BIT(val,1) == 1) {
		// if val(1) == 1, turn on B segment
		LCD_WF23TO20 |= 0x00000002;	
	}
	
	if (BIT(val,2) == 1) {
		// if val(2) == 1, turn on C segment
		LCD_WF23TO20 |= 0x00000004;	
	}
	
	if (BIT(val,3) == 1) {
		// if val(3) == 1, turn on D segment
		LCD_WF23TO20 |= 0x00000008;	
	}
	
	if (BIT(val,4) == 1) {
		// if val(4) == 1, turn on E segment
		LCD_WF23TO20 |= 0x00040000;
	}
	
	if (BIT(val,5) == 1) {
		// if val(5) == 1, turn on F segment
		LCD_WF23TO20 |= 0x00010000;
	}
	
	if (BIT(val,6) == 1) {
		// if val(6) == 1, turn on G segment
		LCD_WF23TO20 |= 0x00020000;
	}
	
	return LCD_RET_SUCCESS;
}

int lcd_setDigit1(char val) {
	LCD_WF15TO12 &= 0xFFFF0000;

	if (BIT(val,0) == 1) {
		// if val(0) == 1, turn on A segment
		LCD_WF15TO12 |= 0x00000001;		
	}
	
	if (BIT(val,1) == 1) {
		// if val(1) == 1, turn on B segment
		LCD_WF15TO12 |= 0x00000002;	
	}
	
	if (BIT(val,2) == 1) {
		// if val(2) == 1, turn on C segment
		LCD_WF15TO12 |= 0x00000004;	
	}
	
	if (BIT(val,3) == 1) {
		// if val(3) == 1, turn on D segment
		LCD_WF15TO12 |= 0x00000008;	
	}
	
	if (BIT(val,4) == 1) {
		// if val(4) == 1, turn on E segment
		LCD_WF15TO12 |= 0x00000400;
	}
	
	if (BIT(val,5) == 1) {
		// if val(5) == 1, turn on F segment
		LCD_WF15TO12 |= 0x00000100;
	}
	
	if (BIT(val,6) == 1) {
		// if val(6) == 1, turn on G segment
		LCD_WF15TO12 |= 0x00000200;
	}
	
	return LCD_RET_SUCCESS;
}

int lcd_setDigit2(char val) {
	LCD_WF15TO12 &= 0x0000FFFF;

	if (BIT(val,0) == 1) {
		// if val(0) == 1, turn on A segment
		LCD_WF15TO12 |= 0x00010000;		
	}
	
	if (BIT(val,1) == 1) {
		// if val(1) == 1, turn on B segment
		LCD_WF15TO12 |= 0x00020000;	
	}
	
	if (BIT(val,2) == 1) {
		// if val(2) == 1, turn on C segment
		LCD_WF15TO12 |= 0x00040000;	
	}
	
	if (BIT(val,3) == 1) {
		// if val(3) == 1, turn on D segment
		LCD_WF15TO12 |= 0x00080000;	
	}
	
	if (BIT(val,4) == 1) {
		// if val(4) == 1, turn on E segment
		LCD_WF15TO12 |= 0x04000000;
	}
	
	if (BIT(val,5) == 1) {
		// if val(5) == 1, turn on F segment
		LCD_WF15TO12 |= 0x01000000;
	}
	
	if (BIT(val,6) == 1) {
		// if val(6) == 1, turn on G segment
		LCD_WF15TO12 |= 0x02000000;
	}
	
	return LCD_RET_SUCCESS;
}

int lcd_update() {
	switch (ui_menuState) {
		case UI_PERF:
			lcd_setDigit2(0x73);
			lcd_setDigit1(0x50);
			lcd_setDigit0(0x71);
			break;
		case UI_TEST:
			lcd_setDigit2(0x78);
			lcd_setDigit1(0x6D);
			lcd_setDigit0(0x78);
			break;
		case UI_REMOTE:
			lcd_setDigit2(0x50);
			lcd_setDigit1(0x78);
			lcd_setDigit0(0x79);
			break;
		case UI_PERF_SPE:
			lcd_setDigit2(0x6D);
			lcd_setDigit1(0x73);
			lcd_setDigit0(0x79);
			break;
		case UI_PERF_ACC:
			lcd_setDigit2(0x77);
			lcd_setDigit1(0x39);
			lcd_setDigit0(0x39);
			break;
		case UI_PERF_DIS:
			lcd_setDigit2(0x5E);
			lcd_setDigit1(0x06);
			lcd_setDigit0(0x6D);
			break;
		case UI_PERF_RET:
			lcd_setDigit2(0x50);
			lcd_setDigit1(0x78);
			lcd_setDigit0(0x54);
			break;
		case UI_TEST_SPE:
			lcd_setDigit2(0x6D);
			lcd_setDigit1(0x73);
			lcd_setDigit0(0x79);
			break;
		case UI_TEST_ACC:
			lcd_setDigit2(0x77);
			lcd_setDigit1(0x39);
			lcd_setDigit0(0x39);
			break;
		case UI_TEST_DIS:
			lcd_setDigit2(0x5E);
			lcd_setDigit1(0x06);
			lcd_setDigit0(0x6D);
			break;
		case UI_TEST_RET:
			lcd_setDigit2(0x50);
			lcd_setDigit1(0x78);
			lcd_setDigit0(0x54);
			break;
	}
	
	switch (exec_sysMode) {
		case EXEC_MODE_IDLE:
			LCD_WF23TO20 &= ~0x00000100;
			break;
		default:
			LCD_WF23TO20 |= 0x00000100;
			break;
	}
	
	return LCD_RET_SUCCESS;
}

void tlcd_set_numeric1(int n)
{
  switch(n)
  {
  case 0:
    {
          LCD_WF15TO12 |= 0x050f0000;
          LCD_WF15TO12 &= 0xfDffffff;
    break;}
  case 1:
    {
          LCD_WF15TO12 |= 0x00060000;
          LCD_WF15TO12 &= 0xf8f6ffff;
    break;}
  case 2:
    {
          LCD_WF15TO12 |= 0x060B0000;
          LCD_WF15TO12 &= 0xfEfBffff;
    break;}
  case 3:
    {
          LCD_WF15TO12 |= 0x020F0000;
          LCD_WF15TO12 &= 0xfAfFffff;
    break;}
  case 4:
    {
          LCD_WF15TO12 |= 0x03060000;
          LCD_WF15TO12 &= 0xfBf6ffff;
    break;}
  case 5:
    {
          LCD_WF15TO12 |= 0x030D0000;
          LCD_WF15TO12 &= 0xfBfDffff;
    break;}
  case 6:
    {
          LCD_WF15TO12 |= 0x070D0000;
          LCD_WF15TO12 &= 0xfFfDffff;
    break;}
  case 7:
    {
          LCD_WF15TO12 |= 0x00070000;
          LCD_WF15TO12 &= 0xf8f7ffff;
    break;}
   case 8:
    {
          LCD_WF15TO12 |= 0x070F0000;
          LCD_WF15TO12 &= 0xfFfFffff;
    break;}

   case 9:
    {
          LCD_WF15TO12 |= 0x030F0000;
          LCD_WF15TO12 &= 0xfBfFffff;
          break;
    }

    default:

      break;
}
}

void tlcd_set_numeric2(int n)
{
  switch(n)
  {
  case 0:
    {
          LCD_WF15TO12 |= 0x0000050f;
          LCD_WF15TO12 &= 0xfffffDff;
    break;}
  case 1:
    {
          LCD_WF15TO12 |= 0x00000006;
          LCD_WF15TO12 &= 0xfffff8f6;
    break;}
  case 2:
    {
          LCD_WF15TO12 |= 0x0000060B;
          LCD_WF15TO12 &= 0xfFfFfEfB;
    break;}
  case 3:
    {
          LCD_WF15TO12 |= 0x0000020F;
          LCD_WF15TO12 &= 0xfffFfAff;
    break;}
  case 4:
    {
          LCD_WF15TO12 |= 0x00000306;
          LCD_WF15TO12 &= 0xfffffbf6;
    break;}
  case 5:
    {
          LCD_WF15TO12 |= 0x0000030d;
          LCD_WF15TO12 &= 0xfffffbfd;
    break;}
  case 6:
    {
          LCD_WF15TO12 |= 0x0000070D;
          LCD_WF15TO12 &= 0xfFfffffd;
    break;}
  case 7:
    {
          LCD_WF15TO12 |= 0x00000007;
          LCD_WF15TO12 &= 0xfFfff8f7;
    break;}
   case 8:
    {
          LCD_WF15TO12 |= 0x0000070F;
          LCD_WF15TO12 &= 0xfFfFffff;
    break;}

   case 9:
    {
          LCD_WF15TO12 |= 0x0000030F;
          LCD_WF15TO12 &= 0xfffFfBff;
          break;
    }

    default:

      break;
}
}

void tlcd_set_numeric3(int n)
{

  switch(n)
  {
  case 0:
    {
          LCD_WF23TO20 |= 0x0005000f;
          LCD_WF23TO20 &= 0xfffDffff;
    break;}
  case 1:
    {
          LCD_WF23TO20 |= 0x00000006;
          LCD_WF23TO20 &= 0xfff8fff6;
    break;}
  case 2:
    {
          LCD_WF23TO20 |= 0x0006000B;
          LCD_WF23TO20 &= 0xfFfEfffB;
    break;}
  case 3:
    {
          LCD_WF23TO20 |= 0x0002000F;
          LCD_WF23TO20 &= 0xfffAffff;
    break;}
  case 4:
    {
          LCD_WF23TO20 |= 0x00030006;
          LCD_WF23TO20 &= 0xfffbfff6;
    break;}
  case 5:
    {
          LCD_WF23TO20 |= 0x0003000d;
          LCD_WF23TO20 &= 0xfffbfffd;
    break;}
  case 6:
    {
          LCD_WF23TO20 |= 0x0007000D;
          LCD_WF23TO20 &= 0xfFfffffd;
    break;}
  case 7:
    {
          LCD_WF23TO20 |= 0x00000007;
          LCD_WF23TO20 &= 0xfFf8fff7;
    break;}
   case 8:
    {
          LCD_WF23TO20 |= 0x0007000F;
          LCD_WF23TO20 &= 0xfFfFffff;
    break;}

   case 9:
    {
          LCD_WF23TO20 |= 0x0003000F;
          LCD_WF23TO20 &= 0xfffBffff;
          break;
    }

    default:

      break;
  }
}

