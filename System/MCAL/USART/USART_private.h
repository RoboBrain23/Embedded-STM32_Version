/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : USART_private.h                                   */
/* Description : Private addresses for USART module STM32F103      */
/*******************************************************************/

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

typedef struct
{
    volatile uint32 SR  ;
    volatile uint32 DR  ;
    volatile uint32 BRR ;
    volatile uint32 CR1 ;
    volatile uint32 CR2 ;
    volatile uint32 CR3 ;
    volatile uint32 GTPR;
    
}USART_t;

#define USART1 ((volatile USART_t *)0x40013800) 
#define USART2 ((volatile USART_t *)0x40004400) 

#define USART1_ID           0
#define USART2_ID           1

#define USART_1_STOP_BIT    0b00
#define USART_2_STOP_BIT    0b10

#define USART_DISABLED      0                       
#define USART_ENABLED       1
                        
#define USART_EVEN_PARITY   0
#define USART_ODD_PARITY    1               
                        
#define USART_8_DATA_BITS   0
#define USART_9_DATA_BITS   1               


/* Calculate the BRR register value for a given baud rate */
uint16 calcBRRReg(uint32 baudRate, uint8 USARTX);

#endif // USART_PRIVATE_H
