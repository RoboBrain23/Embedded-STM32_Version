/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DIO_private.h                                     */
/* Description : Private addresses for DIO module STM32F103        */
/*******************************************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/* Port A Registers Addresses */

#define GPIOA_CRL       *((volatile uint32 *)0x40010800)
#define GPIOA_CRH       *((volatile uint32 *)0x40010804)
#define GPIOA_IDR       *((volatile uint32 *)0x40010808)
#define GPIOA_ODR       *((volatile uint32 *)0x4001080C)
#define GPIOA_BSRR      *((volatile uint32 *)0x40010810)
#define GPIOA_BRR       *((volatile uint32 *)0x40010814)
#define GPIOA_LCKR      *((volatile uint32 *)0x40010818)


/* Port B Registers Addresses */

#define GPIOB_CRL       *((volatile uint32 *)0x40010C00)
#define GPIOB_CRH       *((volatile uint32 *)0x40010C04)
#define GPIOB_IDR       *((volatile uint32 *)0x40010C08)
#define GPIOB_ODR       *((volatile uint32 *)0x40010C0C)
#define GPIOB_BSRR      *((volatile uint32 *)0x40010C10)
#define GPIOB_BRR       *((volatile uint32 *)0x40010C14)
#define GPIOB_LCKR      *((volatile uint32 *)0x40010C18)


/* Port C Registers Addresses */

#define GPIOC_CRL       *((volatile uint32 *)0x400110000)
#define GPIOC_CRH       *((volatile uint32 *)0x400110004)
#define GPIOC_IDR       *((volatile uint32 *)0x400110008)
#define GPIOC_ODR       *((volatile uint32 *)0x40011000C)
#define GPIOC_BSRR      *((volatile uint32 *)0x400110010)
#define GPIOC_BRR       *((volatile uint32 *)0x400110014)
#define GPIOC_LCKR      *((volatile uint32 *)0x400110018)




#endif // DIO_PRIVATE_H
