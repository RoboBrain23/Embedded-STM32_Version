/*************************************************************************************/
/* Author	   : Ibrahim Diab			   					       					 */
/* File Name   : STK_private.h    		   		     			  					 */
/* Description : Private addresses for System Tick core peripheral for ARM cortex-m3 */
/*************************************************************************************/


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

typedef struct
{
	uint32 CTRL  ;
	uint32 LOAD  ;
	uint32 VAL   ;
	uint32 CALIB ;
}STK_t;

#define STK ((volatile STK_t *)0xE000ED00)

#define STK_AHB			  	  0
#define STK_AHB_DIV8		  1

#define STK_SINGLE_INTERVAL   0
#define STK_PERIODIC_INTERVAL 1

static void (*STK_callBack)(void) = NULL;
static uint8 STK_INTERVAL_MODE    =0;

static volatile uint16 microSecToTicksRatio =0;

#endif // STK_PRIVATE_H