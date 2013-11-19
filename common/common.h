/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

//#define IO_ON_SERIAL
#define IO_ON_CONSOLE

//#define CUSTOM_STD_LIB
#define STD_LIB

/*
 * Debug prints ON (#define) or OFF (#undef)
 */
#define DEBUG
#define DEBUG_PRINT

/* 
 * Include the generic CPU header file 
 */
#include "arm_cm4.h"

/* 
 * Include the platform specific header file 
 */
#define TWR_K40X256 1
#if 0
#if (defined(TWR_K40X256))
  #include "k40_tower.h"
#elif (defined(TWR_K60N512))
 #include "k60_tower.h"
#else
  #error "No valid platform defined"
#endif

/* 
 * Include the cpu specific header file 
 */
#if (defined(CPU_MK40N512VMD100))
  #include "MK40N512VMD100.h"
#elif (defined(CPU_MK60N512VMD100))
  #include "MK60N512VMD100.h"
#else
  #error "No valid CPU defined"
#endif
#endif

//added by Kevin
#include "k40_tower.h"
#include "MK40X256VMD100.h"
//Kevin
/* 
 * Include common utilities
 */
#include "assert.h"
#ifdef IO_ON_SERIAL
#include "io.h"
#elif defined IO_ON_CONSOLE
#include <stdio.h>
#else
#error "NO IO DEFINED"
#endif
//#include "startup.h"
#ifdef CUSTOM_STD_LIB
#include "stdlib.h"
#elif defined STD_LIB
#include <stdlib.h>
#else
#error "NO STDLIB DEFINED"
#endif

/********************************************************************/

#endif /* _COMMON_H_ */
