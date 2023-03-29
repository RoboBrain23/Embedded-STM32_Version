/***************************************************************/
/* Author	   : Ibrahim Diab			   					   */
/* File Name   : STM32F103C6.h    		   					   */
/* Description : Global Definitions for stm32f103C6 MCU		   */
/***************************************************************/

#ifndef STM32F103C6_h
#define STM32F103C6_h

#define MCU STM32F103C6 

/*>>>>>> MUST be Set Manually According to RCC Peripheral Values <<<<<<*/

// RCC_SYS_FRQ is the frequency of the internal RC oscillator in Hz
#define SYSTEM_CLOCK_FREQUENCY 	8000000

// RCC_AHB_FRQ is the frequency of the AHB bus in Hz, which is the same as RCC_SYS_FRQ since no prescaler is applied
#define RCC_AHB_CLK_FRQ		    8000000

// RCC_APB1_FRQ is the frequency of the APB1 bus in Hz, which is half the frequency of RCC_AHB_FRQ since the prescaler is set to 2
#define RCC_APB1_CLK_FRQ	    4000000

// RCC_APB2_FRQ is the frequency of the APB2 bus in Hz, which is the same as RCC_AHB_FRQ since no prescaler is applied
#define RCC_APB2_CLK_FRQ		8000000


#endif //STM32F103C6_h