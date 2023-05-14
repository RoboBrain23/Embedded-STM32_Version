/***************************************************************/
/* Author      : Ibrahim Diab                                  */
/* File Name   : STM32F103C6.h                                 */
/* Description : Global Definitions for stm32f103C6 MCU        */
/***************************************************************/

#ifndef STM32F103C6_h
#define STM32F103C6_h

#if MCU == STM32F103C6

/****** It must be Set manually according to RCC peripheral values *******/

// RCC_SYS_FRQ is the frequency of the internal RC oscillator in Hz
#define SYSTEM_CLOCK_FREQUENCY  36000000

// RCC_AHB_FRQ is the frequency of the AHB bus in Hz.
#define RCC_AHB_CLK_FRQ         36000000

// RCC_APB1_FRQ is the frequency of the APB1 bus in Hz.
#define RCC_APB1_CLK_FRQ        36000000

// RCC_APB2_FRQ is the frequency of the APB2 bus in Hz.
#define RCC_APB2_CLK_FRQ        36000000

#define RCC_ADC_CLK_FRQ         9000000

#define RCC_TIM1_CLK_FRQ        36000000

#define RCC_TIMX_CLK_RFQ        36000000
#endif

#endif //STM32F103C6_h
