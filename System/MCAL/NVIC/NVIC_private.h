/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : NVIC_private.h                                    */
/* Description : Private addresses for NVIC module                 */
/*******************************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

/* NVIC Registers Addresses */
#define NVIC_ISER0  *((volatile uint32 *)0xE000E100)    /* Enable External interrupts from 0   to 31 */
#define NVIC_ISER1  *((volatile uint32 *)0xE000E104)    /* Enable External interrupts from 32  to 63 */

#define NVIC_ICER0  *((volatile uint32 *)0xE000E180)
#define NVIC_ICER1  *((volatile uint32 *)0xE000E184)

#define NVIC_ISPR0  *((volatile uint32 *)0xE000E200)
#define NVIC_ISPR1  *((volatile uint32 *)0xE000E204)

#define NVIC_ICPR0  *((volatile uint32 *)0xE000E280)
#define NVIC_ICPR1  *((volatile uint32 *)0xE000E284)


#define NVIC_IABR0  *((volatile uint32 *)0xE000E300)
#define NVIC_IABR1  *((volatile uint32 *)0xE000E304)

#define NVIC_IPR     ((volatile uint8  *)0xE000E400)

#define SCB_AIRCR   *((volatile uint32 *)0xE000ED0C)


 /* Number of bits for groups and subgroups. */
#define _4G_0S  0
#define _3G_1S  1
#define _2G_2S  2
#define _1G_3S  3
#define _0G_4S  4


#endif //NVIC_PRIVATE_H