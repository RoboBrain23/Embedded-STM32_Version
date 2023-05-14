/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : AFIO_private.h                                    */
/* Description : Private addresses for AFIO module STM32F103       */
/*******************************************************************/


#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H

typedef struct 
{
    volatile uint32 EVCR      ; 
    volatile uint32 MAPR      ;
    volatile uint32 EXTICR[4] ;
    volatile uint32 MAPR2     ;
}AFIO_t;

#define AFIO ((volatile AFIO_t *) 0x40010000)



#endif // AFIO_PRIVATE_H
