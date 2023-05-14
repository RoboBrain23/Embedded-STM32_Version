/**************************************************************************************/
/* Author      : Ibrahim Diab                                                         */
/* File Name   : STK_interface.h                                                      */
/* Description : Interfacing macros for System Tick core peripheral for ARM CORTEX-M3 */
/**************************************************************************************/


#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


// Initialize the SysTick timer.
void STK_init(void);

// Delay for a specified number of microseconds using the SysTick timer.
void STK_delayMicroSec(uint32 NoMicroSec);

// Delay for a specified number of milliseconds using the SysTick timer.
void STK_delayMilliSec(uint32 NoMilliSec);

// Delay for a specified number of seconds using the SysTick timer.
void STK_delaySec(uint32 NoSec);

// Set the SysTick timer to trigger a single interrupt after a specified number of microseconds.
void STK_setIntervalSingle ( uint32 NoMicroSec, void (*ptr)(void) );

// Set the SysTick timer to trigger periodic interrupts after a specified number of microseconds.
void STK_setIntervalPeriodic ( uint32 NoMicroSec, void (*ptr)(void) );

// Function to return 1 if system TIck is not used by interval interrupt.
uint8 STK_isSYSTickFree();

// Stop the SysTick timer from generating interrupts.
void STK_stopInterval(void);

// Get the amount of time in microseconds that has elapsed since the last SysTick interrupt in ticks.
uint32 STK_getElapsedTime(void);

// Get the remaining time in microseconds until the next SysTick interrupt in ticks.
uint32 STK_getRemainingTime(void);



#endif // STK_INTERFACE_H
