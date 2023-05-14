/*********************************************************************************/
/* Author      : Ibrahim Diab                                                    */
/* File Name   : STK_config.h                                                    */
/* Description : Configuration for System Tick core peripheral for ARM CORTEX-M3 */
/*********************************************************************************/


#ifndef STK_CONFIG_H
#define STK_CONFIG_H

/**
 NOTE:
        EnSure that the SysTick timer is not being used by other drivers or application code,
        as the STK driver relies on it to generate interrupts.
*/


/*
[Must]
Options: 
         STK_AHB_DIV8 // clock input: AHB/8
         STK_AHB      // clock input: AHB
*/
#define STK_CLOCK_PRESCALER  STK_AHB_DIV8

#endif // STK_CONFIG_H
