/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : SPI.c                                             */
/* Description : Functions Implementation for SPI module           */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "DIO_interface.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"


void SPI1_init() {
    // Set the SPI_CR1 register
    SPI1->CR1 = 
                (SPI1_CLOCK_PHASE << 0) |
                (SPI1_CLOCK_POLARITY << 1) |
                (SPI1_MASTER_SELECTION << 2) |
                (SPI1_BAUD_RATE_CONTROL << 3) |
                (SPI1_FRAME_FORMAT << 7 ) |
                (SPI1_INTERNAL_SLAVE_SELECT << 8) |
                (SPI1_SOFTWARE_SLAVE_MANAGEMENT << 9) |
                (SPI1_TRANSFER_DIR << 10) |
                (SPI1_DATA_FRAME_FORMAT << 11) |
                (SPI1_CRC_TRANSFER_NEXT << 12) |
                (SPI1_HARDWARE_CRC_CALCULATION_ENABLE << 13) |
                (SPI1_OUTPUT_ENABLE_IN_BI_DIR_MODE << 14) |
                (SPI1_BIDIRECTIONAL_DATA_MODE << 15);


    // Set the SPI_SR register
    SPI1->SR = 0;

    // Set the SPI_DR register
    SPI1->DR = 0;

    // Set the SPI_CRCPR register
    SPI1->CRCPR = 0;

    // Set the SPI_RXCRCR register
    SPI1->RXCRCR = 0;

    // Set the SPI_TXCRCR register
    SPI1->TXCRCR = 0;

    // Set the SPI_I2SCFGR register
    SPI1->I2SCFGR = 0;

    // Set the SPI_I2SPR register
    SPI1->I2SPR = 0;
    
    // Enable SPI_1 
    SET_BIT(SPI1->CR1,6);
}


void SPI2_init() {
    // Set the SPI_CR1 register
    SPI2->CR1 = 
                (SPI2_CLOCK_PHASE << 0) |
                (SPI2_CLOCK_POLARITY << 1) |
                (SPI2_MASTER_SELECTION << 2) |
                (SPI2_BAUD_RATE_CONTROL << 3) |
                (SPI2_FRAME_FORMAT << 7 ) |
                (SPI2_INTERNAL_SLAVE_SELECT << 8) |
                (SPI2_SOFTWARE_SLAVE_MANAGEMENT << 9) |
                (SPI2_TRANSFER_DIR << 10) |
                (SPI2_DATA_FRAME_FORMAT << 11) |
                (SPI2_CRC_TRANSFER_NEXT << 12) |
                (SPI2_HARDWARE_CRC_CALCULATION_ENABLE << 13) |
                (SPI2_OUTPUT_ENABLE_IN_BI_DIR_MODE << 14) |
                (SPI2_BIDIRECTIONAL_DATA_MODE << 15);


    // Set the SPI_SR register
    SPI2->SR = 0;

    // Set the SPI_DR register
    SPI2->DR = 0;

    // Set the SPI_CRCPR register
    SPI2->CRCPR = 0;

    // Set the SPI_RXCRCR register
    SPI2->RXCRCR = 0;

    // Set the SPI_TXCRCR register
    SPI2->TXCRCR = 0;

    // Set the SPI_I2SCFGR register
    SPI2->I2SCFGR = 0;

    // Set the SPI_I2SPR register
    SPI2->I2SPR = 0;
    
    // Enable SPI_2 
    SET_BIT(SPI2->CR1,6);
}

// This function sends a byte of data using SPI1 and receives a byte in response synchronously.
void SPI1_sendReceiveByteSync (uint8 SPI1_ByteToSend, uint8 * SPI1_ByteToReceive)
{
    #if SPI1_SET_SLAVE_PIN_SOFTWARE == 1
    // If software control of the slave pin is enabled, set it low to indicate the start of the transaction.
    DIO_setPinValue(SPI1_SLAVE_PIN, LOW);
    #endif
    
    // Send the byte of data over SPI1.
    SPI1->DR =SPI1_ByteToSend;
    
    // Wait for the SPI1 transmit buffer to become empty.
    while(GET_BIT(SPI1->SR,7)==1);
    
    // Read the byte of data received over SPI1.
    *SPI1_ByteToReceive = SPI1->DR ;
    
    #if SPI1_SET_SLAVE_PIN_SOFTWARE == 1
    // If software control of the slave pin is enabled, set it high to indicate the end of the transaction.
    DIO_setPinValue(SPI1_SLAVE_PIN, HIGH);
    #endif
    
}

// This function sends a byte of data using SPI1 and registers a callback function to be called when the data is transmitted.
void SPI1_sendReceiveByteAsync(uint8 SPI1_ByteToSend, void (*SPI1_callBackPtr)(uint8))
{
    if(SPI1_ReadyToSend == 1)
    {
        // Register the callback function to be called when the data is transmitted.
        SPI1_callBack =SPI1_callBackPtr;
        
        // Send the byte of data over SPI1.
        SPI1->DR =SPI1_ByteToSend;
        
        // Set the flag to indicate that a transmission is in progress.
        SPI1_ReadyToSend = 0;
    }
}


void SPI2_sendReceiveByteSync (uint8 SPI2_ByteToSend, uint8 * SPI2_ByteToReceive)
{
    // If the slave pin is software-controlled, set it to LOW
    #if SPI2_SET_SLAVE_PIN_SOFTWARE == 1
    DIO_setPinValue(SPI2_SLAVE_PIN, LOW);
    #endif
    
    // Send the byte to the SPI2 data register
    SPI2->DR = SPI2_ByteToSend;
    
    // Wait for the transmission to complete
    while (GET_BIT(SPI2->SR, 7) == 1);
    
    // Read the received byte from the SPI2 data register
    *SPI2_ByteToReceive = SPI2->DR ;
    
    // If the slave pin is software-controlled, set it to HIGH
    #if SPI2_SET_SLAVE_PIN_SOFTWARE == 1
    DIO_setPinValue(SPI2_SLAVE_PIN, HIGH);
    #endif
}

void SPI2_sendReceiveByteAsync(uint8 SPI2_ByteToSend, void (*SPI2_callBackPtr)(uint8))
{
    // If SPI2 is ready to send a byte
    if (SPI2_ReadyToSend == 1)
    {
        // Save the callback function pointer
        SPI2_callBack = SPI2_callBackPtr;
        
        // Send the byte to the SPI2 data register
        SPI2->DR = SPI2_ByteToSend;
        
        // Set the flag to indicate that SPI2 is not ready to send
        SPI2_ReadyToSend = 0;
    }
}



void SPI1_IRQHandler(void)
{
    // Check if RXNE flag is set
    if(GET_BIT(SPI1->SR,0)==1)
    {
        // Call the callback function with the received byte
        if(SPI1_callBack!=NULL)
        {
            SPI1_callBack((SPI1->DR));
        }
        // Clear the RXNE flag
        CLR_BIT(SPI1->SR,0);
    }
    
    // Check if TXE flag is set
    if(GET_BIT(SPI1->SR,1)==1)
    {
        // Set the flag indicating the SPI is ready to send data
        SPI1_ReadyToSend = 1;
    }
}

void SPI2_IRQHandler(void)
{
    // Check if RXNE flag is set
    if(GET_BIT(SPI2->SR,0)==1)
    {
        // Call the callback function with the received byte
        if(SPI2_callBack!=NULL)
        {
            SPI2_callBack((SPI2->DR));
        }
        // Clear the RXNE flag
        CLR_BIT(SPI2->SR,0);
    }
    
    // Check if TXE flag is set
    if(GET_BIT(SPI2->SR,1)==1)
    {
        // Set the flag indicating the SPI is ready to send data
        SPI2_ReadyToSend = 1;
    }
}
