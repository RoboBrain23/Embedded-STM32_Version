/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : I2C.c                                             */
/* Description : Functions Implementation for I2C module           */
/*******************************************************************/

#include "STM32F103C6.h"

#include "std_types.h"
#include "common_macros.h"

#include "RCC_interface.h"

#include "I2C_interface.h"
#include "I2C_config.h"
#include "I2C_private.h"


// Initialize I2C peripheral
void I2C_init(uint8 I2CNum, I2C_config_t * I2C_config)
{
        // Reset I2Cx control registers
        I2C[I2CNum]->CR1  = 0;
        I2C[I2CNum]->CR2  = 0;
        I2C[I2CNum]->CCR  = 0;
        I2C[I2CNum]->OAR1 = 0;
        I2C[I2CNum]->OAR2 = 0;
        
        // Configure I2Cx clock speed and mode
        I2C[I2CNum]->CCR |= (((RCC_APB1_CLK_FRQ /1000) / (I2C_config->I2C_Clock_Speed_in_KHZ << 1)) & 0xFFF) | (I2C_config->I2C_mode <<15);
        
        // Configure I2Cx acknowledge, general call, stretch mode, and SMBus mode
        I2C[I2CNum]->CR1 = (I2C_config-> I2C_Acknowledge << 10) | (I2C_config-> general_call << 6) |
                           (I2C_config-> stretch_mode    << 7 ) | (I2C_config-> SM_Bus_mode  << 1);

        // Configure I2Cx rise time
        I2C[I2CNum]->TRISE = ((RCC_APB1_CLK_FRQ / 1000000) + 1);
        
        // Configure I2Cx event and error interrupts and clock frequency
        I2C[I2CNum]->CR2 = (RCC_APB1_CLK_FRQ / 1000000) | (I2C_config->event_interrupt << 9) | (I2C_config->error_interrupt << 8);
        
        // Configure I2Cx address mode and own address
        I2C[I2CNum]->OAR1 |= (I2C_config->address_mode << 15) | (I2C_config->own_address << 1);
        
        // Configure I2Cx dual addressing mode
        I2C[I2CNum]->OAR2 |= (I2C_config->dual_addressing_mode << 0);
        
        // Reset I2Cx status registers
        I2C[I2CNum]->SR1 = 0;
        I2C[I2CNum]->SR2 = 0;
        
        // Enable I2Cx
        SET_BIT(I2C[I2CNum]->CR1, 0);
}



/* 
 * Sends data over I2C interface
 *
 * I2Cx: specifies the I2C peripheral to use (I2C1 or I2C2)
 * address: the 7-bit address of the I2C slave
 * dataBuffer: pointer to the buffer containing the data to be sent
 * dataLength: length of the data to be sent
 * startState: specifies whether to use a repeated start or not
 * stopState: specifies whether to send a stop condition after the data has been sent
 */
void I2C_sendData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState)
{
    // To read register value and reset it
    volatile uint32 dummyRead __attribute__((unused));

    // Generate start condition if specified
    generateStart(I2CNum, startState);
            
    // Wait for start condition to be generated
    while(!GET_BIT(I2C[I2CNum]->SR1,0));
            
    // Send slave address with write bit (0) set
    sendAddress(I2CNum, address, I2C_WRITE);
            
    // Wait for address to be sent and ACK received
    while(!GET_BIT(I2C[I2CNum]->SR1,1));
            
    // To reset ADDR bit
    dummyRead = I2C[I2CNum]->SR2;
    
    while(!GET_BIT(I2C[I2CNum]->SR2,0)); // Master [MSL] flag
    while(!GET_BIT(I2C[I2CNum]->SR2,1)); // Busy flag
    while(!GET_BIT(I2C[I2CNum]->SR2,2)); // Data bytes transmitted flag

    // Wait for byte transfer to complete
    while(!GET_BIT(I2C[I2CNum]->SR1,7));
            
    // Send data bytes one by one
    for(uint16 index=0; index < dataLength; index++)
    {
        I2C[I2CNum]->DR = dataBuffer[index];
                
        // Wait for byte transfer to complete
        while(!GET_BIT(I2C[I2CNum]->SR1,7));
    }
            
    // Wait for byte transfer to complete
    while(!GET_BIT(I2C[I2CNum]->SR1,2));
            
    // Generate stop condition if specified
    if(stopState == WITH_STOP)
    {
        generateStop(I2CNum);
    }   
}


/* 
 * Receive data over I2C interface
 *
 * I2Cx: specifies the I2C peripheral to use (I2C1 or I2C2)
 * address: the 7-bit address of the I2C slave
 * dataBuffer: pointer to the buffer containing the data to be received
 * dataLength: length of the data to be received
 * startState: specifies whether to use a repeated start or not
 * stopState: specifies whether to send a stop condition after the data has been received
 */
void I2C_receiveData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState)
{
    // To read register value and reset it
    volatile uint32 dummyRead __attribute__((unused));
           
    // Generate start condition if specified
    generateStart(I2CNum, startState);
    
    // Wait for start condition to be generated
    while(!GET_BIT(I2C[I2CNum]->SR1,0));
    
    // Send slave address with read bit (1) set
    sendAddress(I2CNum, address, I2C_READ);
    
    // Wait for address to be sent and ACK received
    while(!GET_BIT(I2C[I2CNum]->SR1,1));
    
    // To reset ADDR bit
    dummyRead = I2C[I2CNum]->SR2;
    
    // Acknowledge returned after a byte is received (matched address or data)
    SET_BIT(I2C[I2CNum]->CR1,10);
    
    if(dataLength) //Check if data length exist
    {
      for(uint16 index=0; index < dataLength; index++)
      {
        // wait until data register is ready
        while(!GET_BIT(I2C[I2CNum]->SR1,6));
        dataBuffer[index] =I2C[I2CNum]->DR;    
      }
    }
    
    // disable Acknowledge
    CLR_BIT(I2C[I2CNum]->CR1,10);
    
    // Generate stop condition if specified
    if(stopState == WITH_STOP)
    {
        generateStop(I2CNum);
    }
    
    // enable Acknowledge
    SET_BIT(I2C[I2CNum]->CR1,10);
}


// This function generates a start condition for I2C communication on a specified I2C bus
// It takes in the I2C bus number and a start state parameter (either START or REPEATED_START)
// If the start state is not REPEATED_START, it waits until the bus is ready before generating the start condition
// It sets the appropriate bit in the I2C control register to generate the start condition
void generateStart(uint8 I2CNum, uint8 startState)
{
    if(startState!= REPEATED_START)
    {
        while(GET_BIT(I2C[I2CNum]->SR2,1)); // wait until bus is ready
    }
    SET_BIT(I2C[I2CNum]->CR1,8); // set start bit in control register
}


// This function sends the specified address and transmission direction over the specified I2C bus
// It takes in the I2C bus number, the address to send, and a transmit direction (either READ or WRITE)
// It shifts the address left by one and ORs it with the transmit direction to create the appropriate 8-bit address
// It then sends the address over the I2C bus using the appropriate data register
// It supports 7 bit mode only
void sendAddress(uint8 I2CNum, uint16 address, uint8 transmitDirection)
{
    address <<= 1; // shift address left by one
    address  |= transmitDirection; // OR with transmit direction to create 8-bit address
    I2C[I2CNum]->DR =(uint8)address; // send address using data register
}


// This function generates a stop condition for I2C communication on a specified I2C bus
// It takes in the I2C bus number and sets the appropriate bit in the I2C control register to generate the stop condition
void generateStop(uint8 I2CNum)
{
    SET_BIT(I2C[I2CNum]->CR1,9); // set stop bit in control register
}
