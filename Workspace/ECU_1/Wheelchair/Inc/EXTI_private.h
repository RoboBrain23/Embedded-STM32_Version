/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : EXTI_private.h                                    */
/* Description : Private addresses for EXTI module                 */
/*******************************************************************/

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

typedef struct
{
    volatile uint32 IMR   ;
    volatile uint32 EMR   ; 
    volatile uint32 RTSR  ;
    volatile uint32 FTSR  ;
    volatile uint32 SWIER ;
    volatile uint32 PR    ;
}EXTI_t;

#define EXTI ((volatile EXTI_t *) 0x40010400)

volatile void (*EXTI_callBack[16])(void) = { NULL };


#endif // NVIC_PRIVATE_H
