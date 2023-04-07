/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : USART_config.h                                    */
/* Description : Configuration for USART module stm32f103          */
/*******************************************************************/

// This header file guards against multiple inclusion
#ifndef USART_CONFIG_H
#define USART_CONFIG_H


/** 
 Requirements:

- Enable the clock for the USART1 or USART2 peripheral using the RCC peripheral.
- Configure the GPIO pins used for USART1 or USART2 communication as alternate function inputs/outputs.
- Connect the USART1 or USART2 pins to the appropriate external device for communication.

 GPIO pins used for USART communication:
    USART1:
        PA9: USART1_TX
        PA10: USART1_RX
    USART2:
        PA2: USART2_TX
        PA3: USART2_RX
        
 Note: Failing to meet any of these requirements may result in unexpected behavior of the driver.
*/


// Default USART configuration options for USART1
#define USART1_STOP_BITS                                USART_1_STOP_BIT     // 1 stop bit          
#define USART1_RECEIVER_ENABLE                          USART_ENABLED        // Receiver enabled
#define USART1_TRANSMITTER_ENABLE                       USART_ENABLED        // Transmitter enabled
#define USART1_RXNE_INTERRUPT_ENABLE                    USART_DISABLED       // RXNE interrupt disabled
#define USART1_TRANSMISSION_COMPLETE_INTERRUPT_ENABLE   USART_DISABLED       // Transmission complete interrupt disabled
#define USART1_TXE_INTERRUPT_ENABLE                     USART_DISABLED       // TXE interrupt disabled
#define USART1_PARITY_SELECTION                         USART_EVEN_PARITY    // Even parity
#define USART1_PARITY_CONTROL_ENABLE                    USART_DISABLED       // Parity control disabled
#define USART1_WORD_LENGTH                              USART_8_DATA_BITS    // 8 data bits

// Default USART configuration options for USART2
#define USART2_STOP_BITS                                USART_1_STOP_BIT     // 1 stop bit
#define USART2_RECEIVER_ENABLE                          USART_ENABLED        // Receiver enabled
#define USART2_TRANSMITTER_ENABLE                       USART_ENABLED        // Transmitter enabled
#define USART2_RXNE_INTERRUPT_ENABLE                    USART_DISABLED       // RXNE interrupt disabled
#define USART2_TRANSMISSION_COMPLETE_INTERRUPT_ENABLE   USART_DISABLED       // Transmission complete interrupt disabled
#define USART2_TXE_INTERRUPT_ENABLE                     USART_DISABLED       // TXE interrupt disabled
#define USART2_PARITY_SELECTION                         USART_EVEN_PARITY    // Even parity
#define USART2_PARITY_CONTROL_ENABLE                    USART_DISABLED       // Parity control disabled
#define USART2_WORD_LENGTH                              USART_8_DATA_BITS    // 8 data bits


/*
    USART configuration options:

STOP_BITS                               >> USART_1_STOP_BIT (Default), USART_2_STOP_BIT 
WORD_LENGTH                             >> USART_8_DATA_BITS(Default), USART_9_DATA_BITS
PARITY_SELECTION                        >> USART_EVEN_PARITY(Default), USART_ODD_PARITY     
RECEIVER_ENABLE                         >> USART_DISABLED(Default), USART_ENABLED
TRANSMITTER_ENABLE                      >> USART_DISABLED(Default), USART_ENABLED
RXNE_INTERRUPT_ENABLE                   >> USART_DISABLED(Default), USART_ENABLED
TRANSMISSION_COMPLETE_INTERRUPT_ENABLE  >> USART_DISABLED(Default), USART_ENABLED
TXE_INTERRUPT_ENABLE                    >> USART_DISABLED(Default), USART_ENABLED           
PARITY_CONTROL_ENABLE                   >> USART_DISABLED(Default), USART_ENABLED   
                            
*/


#endif // USART_CONFIG_H