/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : SPI_config.h                                      */
/* Description : Configuration for SPI module stm32f103            */
/*******************************************************************/

// This header file guards against multiple inclusion
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/**
 Requirements:
 
- Enable the RCC peripheral clock for the GPIO pins connected to the SPI peripheral.
- Configure the GPIO pins as alternate function push-pull mode for SPI peripheral.
- Enable the RCC peripheral clock for the SPI peripheral.
- Configure the SPI peripheral by calling SPI1/SPI2_init() function.
- Enable the NVIC interrupt for SPI1/SPI2 IRQHandler function.

 Note: GPIO pins used for SPI communication are:
       - SPI1: PA4 (NSS), PA5 (SCK), PA6 (MISO), PA7 (MOSI)
       - SPI2: PB12 (NSS), PB13 (SCK), PB14 (MISO), PB15 (MOSI)
**/



// Flag to set software slave pin control for SPI1
#define SPI1_SET_SLAVE_PIN_SOFTWARE 1

// Flag to set software slave pin control for SPI2
#define SPI2_SET_SLAVE_PIN_SOFTWARE 1

// Define the slave pin for SPI1 if software control is enabled
#if SPI1_SET_SLAVE_PIN_SOFTWARE == 1
#define SPI1_SLAVE_PIN DIO_GPIOA,0
#endif

// Define the slave pin for SPI2 if software control is enabled
#if SPI2_SET_SLAVE_PIN_SOFTWARE == 1
#define SPI2_SLAVE_PIN DIO_GPIOA,1
#endif


/* SPI 1 configurations */
#define SPI1_BIDIRECTIONAL_DATA_MODE         SPI_2_LINE_UNI_DIR_DATA  // Bi-directional data mode (default is uni-directional)
#define SPI1_OUTPUT_ENABLE_IN_BI_DIR_MODE    SPI_DISABLED             // Output enable in bi-directional mode (default is disabled)
#define SPI1_HARDWARE_CRC_CALCULATION_ENABLE SPI_DISABLED             // Hardware CRC calculation enable (default is disabled)
#define SPI1_CRC_TRANSFER_NEXT               SPI_CRC                  // CRC transfer next (default is CRC disabled)
#define SPI1_DATA_FRAME_FORMAT               SPI_8_BIT_DATA           // Data frame format (default is 8-bit)
#define SPI1_TRANSFER_DIR                    SPI_TRANSMIT_AND_RECEIVE // Transfer direction (default is transmit and receive)
#define SPI1_SOFTWARE_SLAVE_MANAGEMENT       SPI_DISABLED             // Software slave management (default is disabled)
#define SPI1_INTERNAL_SLAVE_SELECT           SPI_DISABLED             // Internal slave select (default is disabled)
#define SPI1_FRAME_FORMAT                    SPI_MSB_FIRST            // Frame format (default is MSB first)
#define SPI1_BAUD_RATE_CONTROL               SPI_FRQ_CLK_DIV_2        // Baud rate control (default is clk/2)
#define SPI1_MASTER_SELECTION                SPI_MASTER               // Master selection (default is master)
#define SPI1_CLOCK_POLARITY                  SPI_IDLE_LOW             // Clock polarity (default is idle low)
#define SPI1_CLOCK_PHASE                     SPI_RISING_EDGE          // Clock phase (default is rising edge)
                                                                      
/* SPI 2 configurations */                                            
#define SPI2_BIDIRECTIONAL_DATA_MODE         SPI_2_LINE_UNI_DIR_DATA  // Bi-directional data mode (default is uni-directional)
#define SPI2_OUTPUT_ENABLE_IN_BI_DIR_MODE    SPI_DISABLED             // Output enable in bi-directional mode (default is disabled)
#define SPI2_HARDWARE_CRC_CALCULATION_ENABLE SPI_DISABLED             // Hardware CRC calculation enable (default is disabled)
#define SPI2_CRC_TRANSFER_NEXT               SPI_CRC                  // CRC transfer next (default is CRC disabled)
#define SPI2_DATA_FRAME_FORMAT               SPI_8_BIT_DATA           // Data frame format (default is 8-bit)
#define SPI2_TRANSFER_DIR                    SPI_TRANSMIT_AND_RECEIVE // Transfer direction (default is transmit and receive)
#define SPI2_SOFTWARE_SLAVE_MANAGEMENT       SPI_DISABLED             // Software slave management (default is disabled)
#define SPI2_INTERNAL_SLAVE_SELECT           SPI_DISABLED             // Internal slave select (default is disabled)
#define SPI2_FRAME_FORMAT                    SPI_MSB_FIRST            // Frame format (default is MSB first)
#define SPI2_BAUD_RATE_CONTROL               SPI_FRQ_CLK_DIV_2        // Baud rate control (default is clk/2)
#define SPI2_MASTER_SELECTION                SPI_MASTER               // Master selection (default is master)
#define SPI2_CLOCK_POLARITY                  SPI_IDLE_LOW             // Clock polarity (default is idle low)
#define SPI2_CLOCK_PHASE                     SPI_RISING_EDGE          // Clock phase (default is rising edge)

/*
 Configuration Options: 
 
 
SPIX_CLOCK_PHASE                     >> SPI_RISING_EDGE ,SPI_FAILING_EDGE       
 
SPIX_CLOCK_POLARITY                  >> SPI_IDLE_LOW ,SPI_IDLE_HIGH         

SPIX_MASTER_SELECTION                >> SPI_SLAVE ,SPI_MASTER               

SPIX_BAUD_RATE_CONTROL               >>     SPI_FRQ_CLK_DIV_2       
                                            SPI_FRQ_CLK_DIV_4       
                                            SPI_FRQ_CLK_DIV_8       
                                            SPI_FRQ_CLK_DIV_16      
                                            SPI_FRQ_CLK_DIV_32      
                                            SPI_FRQ_CLK_DIV_64      
                                            SPI_FRQ_CLK_DIV_128     
                                            SPI_FRQ_CLK_DIV_256 
                            
                            

SPIX_INTERNAL_SLAVE_SELECT           >> SPI_DISABLED ,SPI_ENABLED   
   
SPIX_SOFTWARE_SLAVE_MANAGEMENT       >> SPI_DISABLED ,SPI_ENABLED   
   
SPIX_HARDWARE_CRC_CALCULATION_ENABLE >> SPI_DISABLED ,SPI_ENABLED   
   
SPIX_OUTPUT_ENABLE_IN_BI_DIR_MODE    >> SPI_DISABLED ,SPI_ENABLED   
                                                       
       
SPIX_FRAME_FORMAT                    >> SPI_MSB_FIRST ,SPI_LSB_FIRST            
    
SPIX_TRANSFER_DIR                    >> SPI_TRANSMIT_AND_RECEIVE ,SPI_RECEIVE_ONLY      
   
SPIX_DATA_FRAME_FORMAT               >> SPI_8_BIT_DATA ,SPI_16_BIT_DATA         
   
SPIX_CRC_TRANSFER_NEXT               >> SPI_NO_CRC ,SPI_CRC                 
    
SPIX_BIDIRECTIONAL_DATA_MODE         >> SPI_2_LINE_UNI_DIR_DATA ,SPI_1_LINE_BI_DIR_DATA 



*/

#endif // SPI_CONFIG_H


