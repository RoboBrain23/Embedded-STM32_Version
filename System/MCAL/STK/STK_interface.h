/**************************************************************************************/
/* Author	   : Ibrahim Diab			   					       					  */
/* File Name   : STK_interface.h    		   					  				      */
/* Description : Interfacing macros for System Tick core peripheral for ARM cortex-m3 */
/**************************************************************************************/


#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


// Initialize the SysTick timer.
void STK_init(void);

// Delay for a specified number of microseconds using the SysTick timer.
void STK_delayMicroSec(uint32_t NoMicroSec);

// Delay for a specified number of milliseconds using the SysTick timer.
void STK_delayMilliSec(uint32_t NoMilliSec);

// Delay for a specified number of seconds using the SysTick timer.
void STK_delaySec(uint32_t NoSec);

// Set the SysTick timer to trigger a single interrupt after a specified number of microseconds.
void STK_setIntervalSingle ( uint32 NoMicroSec, void (*ptr)(void) );

// Set the SysTick timer to trigger periodic interrupts after a specified number of microseconds.
void STK_setIntervalPeriodic ( uint32 NoMicroSec, void (*ptr)(void) );

// Stop the SysTick timer from generating interrupts.
void STK_stopInterval(void);

// Get the amount of time in microseconds that has elapsed since the last SysTick interrupt in ticks.
uint32_t STK_getElapsedTime(void);

// Get the remaining time in microseconds until the next SysTick interrupt in ticks.
uint32_t STK_getRemainingTime(void);



#endif // STK_INTERFACE_H
