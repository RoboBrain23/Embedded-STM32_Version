/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : AFIO_interface.h                                  */
/* Description : Interfacing macros for AFIO module STM32F103      */
/*******************************************************************/


#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

/*
 This function configures an external interrupt line to a GPIO port.
 Line is the ID of the external interrupt line to be configured.
 PortMap is the ID of the GPIO port to be mapped to the line.
 Only ports A, B, and C are supported by the STM32f103c6.
 Only Lines from 0 to 4 are available in the STM32f103c6.
*/
void AFIO_setEXTIConfig(uint8 Line ,uint8 PortMap);

/* Lines ID*/
#define AFIO_LINE_0     0
#define AFIO_LINE_1     1
#define AFIO_LINE_2     2
#define AFIO_LINE_3     3
#define AFIO_LINE_4     4
#define AFIO_LINE_5     5
#define AFIO_LINE_6     6
#define AFIO_LINE_7     7
#define AFIO_LINE_8     8
#define AFIO_LINE_9     9
#define AFIO_LINE_10    10
#define AFIO_LINE_11    11
#define AFIO_LINE_12    12
#define AFIO_LINE_13    13
#define AFIO_LINE_14    14
#define AFIO_LINE_15    15

/* Port ID */
// NOTE: STM32f103c6 supports PORT [A,B,C] Only, 16 bins in A,B and 3 in C. 
#define AFIO_PORT_A     0b0000
#define AFIO_PORT_B     0b0001
#define AFIO_PORT_C     0b0010  
#define AFIO_PORT_D     0b0011
#define AFIO_PORT_E     0b0100
#define AFIO_PORT_F     0b0101
#define AFIO_PORT_G     0b0110

#endif // AFIO_INTERFACE_H
