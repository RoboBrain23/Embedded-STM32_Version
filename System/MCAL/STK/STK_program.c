/********************************************************************************************/
/* Author      : Ibrahim Diab                                                               */
/* File Name   : STK_program.c                                                              */
/* Description : Functions Implementation for System Tick core peripheral for ARM CORTEX-m3 */
/********************************************************************************************/

#include  "STM32F103C6.h"

#include "std_types.h"
#include "common_macros.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

#if MCU == STM32F103C6
#define CPU_INPUT_CLOCK RCC_AHB_CLK_FRQ
#endif


// Initialize the SysTick timer.
void STK_init ()
{
     microSecToTicksRatio = CPU_INPUT_CLOCK / 1000000;
     
    #if STK_CLOCK_PRESCALER == STK_AHB_DIV8
    microSecToTicksRatio = microSecToTicksRatio >> 3;
    #endif 
    
    /*Enable SysTick and its interrupt*/
    STK->CTRL=0b11;
    
    /*Configure the SysTick timer with the selected Clock*/
    #if STK_CLOCK_PRESCALER == STK_AHB
    SET_BIT(STK->CTRL,2);
    #endif
    
}


// Delay for a specified number of microseconds using the SysTick timer.
void STK_delayMicroSec ( uint32 NoMicroSec )
{
    
    // Assign number of TIcks To load register.
    STK->LOAD = (NoMicroSec *microSecToTicksRatio);
    
    // Initiate Timer.
    SET_BIT(STK->CTRL,0);
    
    // Wait the Time delay.
    while(GET_BIT(STK->CTRL,16) == 0);
    
    //Stop Timer and reset its value.
    CLR_BIT(STK->CTRL,0);
    STK->LOAD = 0;
    STK->VAL  = 0;
}


// Delay for a specified number of milliseconds using the SysTick timer.
void STK_delayMilliSec ( uint32 NoMilliSec )
{
    for(uint32 counter=0;counter <NoMilliSec;counter++)
    {
    // Assign number of TIcks To load register.
    STK->LOAD = (1000 *microSecToTicksRatio); //No Ticks equals to equation
    
    // Initiate Timer.
    SET_BIT(STK->CTRL,0);
    
    // Wait the Time delay.
    while(GET_BIT(STK->CTRL,16) == 0);
    
    //Stop Timer and reset its value.
    CLR_BIT(STK->CTRL,0);
    STK->LOAD =0;
    STK->VAL  =0;   
    }
}


// Delay for a specified number of seconds using the SysTick timer.
void STK_delaySec ( uint32 NoSec )
{   
    for(uint32 counter=0;counter <NoSec;counter++)
    {   
        for(uint32 counter=0;counter <1000;counter++)
        {
        // Assign number of TIcks To load register.
        STK->LOAD = (1000 *microSecToTicksRatio); //No Ticks equals to equation
        
        // Initiate Timer.
        SET_BIT(STK->CTRL,0);
        
        // Wait the Time delay.
        while(GET_BIT(STK->CTRL,16) == 0);
        
        //Stop Timer and reset its value.
        CLR_BIT(STK->CTRL,0);
        STK->LOAD =0;
        STK->VAL  =0;   
        }
    }
}


// Set the SysTick timer to trigger a single interrupt after a specified number of microseconds.
void STK_setIntervalSingle ( uint32 NoMicroSec, void (*ptr)(void) )
{
    //Load number of ticks to Load Register.
    STK->LOAD = (NoMicroSec *microSecToTicksRatio);
    
    // Assign callback function.
    STK_callBack = ptr;
    
    // Set interval mode to single.
    STK_INTERVAL_MODE = STK_SINGLE_INTERVAL;
    
    //Start timer and enable the interrupt.
    STK->CTRL =3;
}


// Set the SysTick timer to trigger periodic interrupts after a specified number of microseconds.
void STK_setIntervalPeriodic ( uint32 NoMicroSec, void (*ptr)(void) )
{
    //Load number of ticks to Load Register.
    STK->LOAD = (NoMicroSec *microSecToTicksRatio);
    
    // Assign callback function.
    STK_callBack = ptr;
    
    // Set interval mode to single.
    STK_INTERVAL_MODE = STK_PERIODIC_INTERVAL;
    
    //Start timer and enable the interrupt.
    STK->CTRL =3;
}


// Stop the SysTick timer from generating interrupts.
void STK_stopInterval (void)
{
    /* Disable interrupt and Timer bins */
    STK->CTRL = 0;
    
    /* Clear the SysTick reload value */
    STK->LOAD = 0;
    
    /* Clear the SysTick current value */   
    STK->VAL  = 0;
    
}

// Get the amount of time that has elapsed since the last SysTick interrupt in microseconds.
uint32 STK_getElapsedTime(void)
{
    // Initialize ElapsedTime to 0.
    uint32 ElapsedTime = 0;

    // Calculate the number of ticks that have elapsed.
    ElapsedTime = (STK->LOAD - STK->VAL);

    // Convert ticks to microseconds using the microSecToTicksRatio constant.
    ElapsedTime /= microSecToTicksRatio;

    // Return the elapsed time in microseconds.
    return ElapsedTime;
}

// Get the remaining time until the next SysTick interrupt in microseconds.
uint32 STK_getRemainingTime(void)
{
    // Initialize RemainingTime to 0.
    uint32 RemainingTime = 0;

    // Calculate the number of ticks remaining until the next interrupt.
    RemainingTime = STK->VAL;

    // Convert ticks to microseconds using the microSecToTicksRatio constant.
    RemainingTime /= microSecToTicksRatio;

    // Return the remaining time in microseconds.
    return RemainingTime;
}

// SysTick interrupt handler function.
void SysTick_Handler(void)
{
    // Check if SysTick interval mode is single interval.
    if (STK_INTERVAL_MODE == STK_SINGLE_INTERVAL)
    {
        // Stop the timer and clear the registers.
        STK->CTRL = 0;
        STK->LOAD = 0;
        STK->VAL  = 0;
    }

    // Call the callback function.
    STK_callBack();
}

