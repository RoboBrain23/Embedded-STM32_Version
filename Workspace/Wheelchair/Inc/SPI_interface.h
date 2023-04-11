/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : SPI_interface.h                                   */
/* Description : Interfacing macros for SPI module stm32f103       */
/*******************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H 

void SPI1_init();  // declare a function prototype to initialize SPI1
void SPI2_init();  // declare a function prototype to initialize SPI2


// declare a function prototype to send and receive a byte synchronously using SPI1
void SPI1_sendReceiveByteSync (uint8 SPI1_ByteToSend, uint8 * SPI1_ByteToReceive);  

 // declare a function prototype to send and receive a byte synchronously using SPI2
void SPI2_sendReceiveByteSync (uint8 SPI2_ByteToSend, uint8 * SPI2_ByteToReceive); 


// declare a function prototype to send and receive a byte asynchronously using SPI1 with a callback function
void SPI1_sendReceiveByteAsync(uint8 SPI1_ByteToSend, void (*SPI1_callBackPtr)(uint8));  

// declare a function prototype to send and receive a byte asynchronously using SPI2 with a callback function
void SPI2_sendReceiveByteAsync(uint8 SPI2_ByteToSend, void (*SPI2_callBackPtr)(uint8));  


void SPI1_IRQHandler(void);  // declare a function prototype for SPI1 interrupt handler
void SPI2_IRQHandler(void);  // declare a function prototype for SPI2 interrupt handler


#endif // SPI_INTERFACE_H