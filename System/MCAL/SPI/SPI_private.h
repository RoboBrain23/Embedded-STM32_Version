/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : SPI_private.h                                     */
/* Description : Private addresses for SPI module stm32f103        */
/*******************************************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

// Function pointers to callback functions for SPI1 and SPI2
void (*SPI1_callBack)(uint8 byteReceived)= NULL;
void (*SPI2_callBack)(uint8 byteReceived)= NULL;

volatile uint8 SPI1_ReadyToSend =1;
volatile uint8 SPI2_ReadyToSend =1;

typedef struct
{ 
    volatile uint32 CR1    ;
    volatile uint32 CR2    ;
    volatile uint32 SR     ;
    volatile uint32 DR     ;
    volatile uint32 CRCPR  ;
    volatile uint32 RXCRCR ;
    volatile uint32 TXCRCR ;
    volatile uint32 I2SCFGR;
    volatile uint32 I2SPR  ;
}SPI_t;

#define SPI1 ((volatile SPI_t *)0x40013000)
#define SPI2 ((volatile SPI_t *)0x40003800)


#define SPI_RISING_EDGE             0       // Constant representing SPI mode with rising edge
#define SPI_FAILING_EDGE            1       // Constant representing SPI mode with falling edge
    
#define SPI_IDLE_LOW                0       // Constant representing SPI mode with idle low
#define SPI_IDLE_HIGH               1       // Constant representing SPI mode with idle high
    
#define SPI_SLAVE                   0       // Constant representing SPI mode as slave
#define SPI_MASTER                  1       // Constant representing SPI mode as master

#define SPI_FRQ_CLK_DIV_2           0b000   // Constant representing SPI clock frequency divider of 2
#define SPI_FRQ_CLK_DIV_4           0b001   // Constant representing SPI clock frequency divider of 4
#define SPI_FRQ_CLK_DIV_8           0b010   // Constant representing SPI clock frequency divider of 8
#define SPI_FRQ_CLK_DIV_16          0b011   // Constant representing SPI clock frequency divider of 16
#define SPI_FRQ_CLK_DIV_32          0b100   // Constant representing SPI clock frequency divider of 32
#define SPI_FRQ_CLK_DIV_64          0b101   // Constant representing SPI clock frequency divider of 64
#define SPI_FRQ_CLK_DIV_128         0b110   // Constant representing SPI clock frequency divider of 128
#define SPI_FRQ_CLK_DIV_256         0b111   // Constant representing SPI clock frequency divider of 256

#define SPI_DISABLED                0       // Constant representing SPI as disabled
#define SPI_ENABLED                 1       // Constant representing SPI as enabled
             
#define SPI_MSB_FIRST               0       // Constant representing SPI data transfer with MSB first
#define SPI_LSB_FIRST               1       // Constant representing SPI data transfer with LSB first
             
#define SPI_TRANSMIT_AND_RECEIVE    0       // Constant representing SPI data transfer as transmit and receive
#define SPI_RECEIVE_ONLY            1       // Constant representing SPI data transfer as receive only
             
#define SPI_8_BIT_DATA              0       // Constant representing SPI data transfer with 8-bit data
#define SPI_16_BIT_DATA             1       // Constant representing SPI data transfer with 16-bit data
             
#define SPI_NO_CRC                  0       // Constant representing SPI without CRC
#define SPI_CRC                     1       // Constant representing SPI with CRC
             
#define SPI_2_LINE_UNI_DIR_DATA     0       // Constant representing SPI mode with 2-line unidirectional data flow
#define SPI_1_LINE_BI_DIR_DATA      1       // Constant representing SPI mode with 1-line bidirectional data flow


#endif // SPI_PRIVATE_H
