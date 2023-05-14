/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : RCC_private.h                                     */
/* Description : Private addresses for RCC module stm32f103        */
/*******************************************************************/


#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/* RCC register definitions */
#define RCC_CR                *((volatile uint32 *)0x40021000) /* Clock Control Register */
#define RCC_CFGR              *((volatile uint32 *)0x40021004) /* Clock Configuration Register */
#define RCC_CIR               *((volatile uint32 *)0x40021008) /* Clock Interrupt Register */
#define RCC_APB2RSTR          *((volatile uint32 *)0x4002100C) /* APB2 Peripheral Reset Register */
#define RCC_APB1RSTR          *((volatile uint32 *)0x40021010) /* APB1 Peripheral Reset Register */
#define RCC_AHBENR            *((volatile uint32 *)0x40021014) /* AHB Peripheral Clock Enable Register */
#define RCC_APB2ENR           *((volatile uint32 *)0x40021018) /* APB2 Peripheral Clock Enable Register */
#define RCC_APB1ENR           *((volatile uint32 *)0x4002101C) /* APB1 Peripheral Clock Enable Register */
#define RCC_BDCR              *((volatile uint32 *)0x40021020) /* Backup Domain Control Register */
#define RCC_CSR               *((volatile uint32 *)0x40021024) /* Control/Status Register */

/* System Clock Types */
#define RCC_HSI                 0                              /* High Speed Internal oscillator */
#define RCC_HSE_RC              1                              /* High Speed External oscillator with RC */
#define RCC_HSE_CRYSTAL         2                              /* High Speed External oscillator with crystal */
#define RCC_PLL                 3                              /* Phase Locked Loop */

/* RCC PLL Input Types */
#define RCC_PLL_IN_HSI_DIV_2    0                              /* PLL input clock is HSI divided by 2 */
#define RCC_PLL_IN_HSE_DIV_2    1                              /* PLL input clock is HSE divided by 2 */
#define RCC_PLL_IN_HSE          2                              /* PLL input clock is HSE */


/* AHB Prescaler [System Clock] */
#define AHB_NOT_DIVIDED         0b0000
#define AHB_DIV_BY_2            0b1000
#define AHB_DIV_BY_4            0b1001
#define AHB_DIV_BY_8            0b1010
#define AHB_DIV_BY_16           0b1011
#define AHB_DIV_BY_64           0b1100
#define AHB_DIV_BY_128          0b1101
#define AHB_DIV_BY_256          0b1110
#define AHB_DIV_BY_512          0b1111

/* APB1 Prescaler */
#define APB1_NOT_DIVIDED        0b000
#define APB1_DIV_BY_2           0b100
#define APB1_DIV_BY_4           0b101
#define APB1_DIV_BY_8           0b110
#define APB1_DIV_BY_16          0b111

/* APB2 Prescaler */
#define APB2_NOT_DIVIDED        0b000
#define APB2_DIV_BY_2           0b100
#define APB2_DIV_BY_4           0b101
#define APB2_DIV_BY_8           0b110
#define APB2_DIV_BY_16          0b111

/* ADC Prescaler */
#define ADC_DIV_BY_2            0b00
#define ADC_DIV_BY_4            0b01
#define ADC_DIV_BY_6            0b10
#define ADC_DIV_BY_8            0b11

#endif // RCC_PRIVATE_H
