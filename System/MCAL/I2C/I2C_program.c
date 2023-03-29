/*******************************************************************/
/* Author	   : Ibrahim Diab			   					       */
/* File Name   : I2C_program.c    		   		    	 		   */
/* Description : Functions Implementation for I2C module	  	   */
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
    // Check which I2C peripheral is being used
    if(I2CNum == I2C1)
    {
        // Reset I2C1 control registers
        I2C1->CR1  = 0;
        I2C1->CR2  = 0;
        I2C1->CCR  = 0;
        I2C1->OAR1 = 0;
        I2C1->OAR2 = 0;
        
        // Configure I2C1 clock speed and mode
        I2C1->CCR |= ((RCC_APB1_CLK_FRQ / (I2C_config->I2C_Clock_Speed_in_KHZ << 1)) & 0xFFF) | (I2C_config->I2C_mode <<15);
        
        // Configure I2C1 acknowledge, general call, stretch mode, and SMBus mode
        I2C1->CR1 = (I2C_config-> I2C_Acknowledge << 10) | (I2C_config-> general_call << 6) |
        		    (I2C_config-> stretch_mode << 7)     | (I2C_config-> SM_Bus_mode << 1);

        // Configure I2C1 rise time
        I2C1->TRISE = ((RCC_APB1_CLK_FRQ / 1000000) + 1);
        
        // Configure I2C1 event and error interrupts and clock frequency
        I2C1->CR2 = (RCC_APB1_CLK_FRQ / 1000000) | (I2C_config->event_interrupt << 9) | (I2C_config->error_interrupt << 8);
        
        // Configure I2C1 address mode and own address
        I2C1->OAR1 |= (I2C_config->address_mode << 15) | (I2C_config->own_address << 1);
        
        // Configure I2C1 dual addressing mode
        I2C1->OAR2 |= (I2C_config->dual_addressing_mode << 0);
        
        // Reset I2C1 status registers
        I2C1->SR1 = 0;
        I2C1->SR2 = 0;
        
        // Enable I2C1
        SET_BIT(I2C1->CR1, 0);
    }
    else if(I2CNum == I2C2)
    {
        // Reset I2C2 control registers
        I2C2->CR1  = 0;
        I2C2->CR2  = 0;
        I2C2->CCR  = 0;
        I2C2->OAR1 = 0;
        I2C2->OAR2 = 0;
        
        // Configure I2C2 clock speed and mode
        I2C2->CCR |= ((RCC_APB1_CLK_FRQ / (I2C_config->I2C_Clock_Speed_in_KHZ << 1)) & 0xFFF) | (I2C_config->I2C_mode <<15);
        
        // Configure I2C2 acknowledge, general call, stretch mode, and SMBus mode
        I2C2->CR1 = (I2C_config->I2C_Acknowledge << 10) | (I2C_config->general_call << 6);

		// Configure I2C2 rise time
        I2C2->TRISE = ((RCC_APB1_CLK_FRQ / 1000000) + 1);
        
        // Configure I2C2 event and error interrupts and clock frequency
        I2C2->CR2 = (RCC_APB1_CLK_FRQ / 1000000) | (I2C_config->event_interrupt << 9) | (I2C_config->error_interrupt << 8);
        
        // Configure I2C2 address mode and own address
        I2C2->OAR1 |= (I2C_config->address_mode << 15) | (I2C_config->own_address << 1);
        
        // Configure I2C2 dual addressing mode
        I2C2->OAR2 |= (I2C_config->dual_addressing_mode << 0);
        
        // Reset I2C2 status registers
        I2C2->SR1 = 0;
        I2C2->SR2 = 0;
        
        // Enable I2C2
        SET_BIT(I2C2->CR1, 0);
	}
}




/* 
 * Sends data over I2C interface
 *
 * I2CNum: specifies the I2C peripheral to use (I2C1 or I2C2)
 * address: the 7-bit address of the I2C slave
 * dataBuffer: pointer to the buffer containing the data to be sent
 * dataLength: length of the data to be sent
 * startState: specifies whether to use a repeated start or not
 * stopState: specifies whether to send a stop condition after the data has been sent
 */
void I2C_sendData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState)
{
	uint32 dummyRead;
	switch(I2CNum)
	{
		case I2C1:
			// Generate start condition if specified
			generateStart(I2C1, startState);
					
			// Wait for start condition to be generated
			while(!GET_BIT(I2C1->SR1,0));
					
			// Send slave address with write bit (1) set
			sendAddress(I2C1, address, 1);
					
			// Wait for address to be sent and ACK received
			while(!GET_BIT(I2C1->SR1,1));
					
			// To reset ADDR bit
			dummyRead = I2C1->SR2;
			
			// Wait for byte transfer to complete
			while(!GET_BIT(I2C1->SR1,7));
					
			// Send data bytes one by one
			for(uint16 index=0; index < dataLength; index++)
			{
				I2C1->DR = dataBuffer[index];
						
				// Wait for byte transfer to complete
				while(!GET_BIT(I2C1->SR1,7));
			}
					
			// Wait for byte transfer to complete
			while(!GET_BIT(I2C1->SR1,2));
					
			// Generate stop condition if specified
			if(stopState == WITH_STOP)
			{
				generateStop(I2C1);
			}
			break;
		
		case I2C2:
			// Generate start condition if specified
			generateStart(I2C2, startState);
					
			// Wait for start condition to be generated
			while(!GET_BIT(I2C2->SR1,0));
					
			// Send slave address with write bit (1) set
			sendAddress(I2C2, address, 1);
					
			// Wait for address to be sent and ACK received
			while(!GET_BIT(I2C2->SR1,1));
			
			// To reset ADDR bit
			dummyRead = I2C2->SR2;
					
			// Wait for byte transfer to complete
			while(!GET_BIT(I2C2->SR1,7));
					
			// Send data bytes one by one
			for(uint16 index=0; index < dataLength; index++)
			{
				I2C2->DR = dataBuffer[index];
						
				// Wait for byte transfer to complete
				while(!GET_BIT(I2C2->SR1,7));
			}
					
			// Wait for byte transfer to complete
			while(!GET_BIT(I2C2->SR1,2));
					
			// Generate stop condition if specified
			if(stopState == WITH_STOP)
			{
				generateStop(I2C2);
			}
			break;
	}
	
}



void I2C_receiveData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState)
{
	uint32 dummyRead;
	switch(I2CNum)
	{
		case I2C1:
			
			// Generate start condition if specified
			generateStart(I2C1, startState);
			
			// Wait for start condition to be generated
			while(!GET_BIT(I2C1->SR1,0));
			
			// Send slave address with read bit (0) set
			sendAddress(I2C1, address, 0);
			
			// Wait for address to be sent and ACK received
			while(!GET_BIT(I2C1->SR1,1));
			
			// To reset ADDR bit
			dummyRead = I2C1->SR2;
			
			// Acknowledge returned after a byte is received (matched address or data)
			SET_BIT(I2C1->CR1,10);
			
			if(dataLength) //Check if data length exist
			{
			for(uint16 index=0; index < dataLength; index++)
			{
				// wait until data register is ready
				while(!GET_BIT(I2C1->SR1,6));
				dataBuffer[index] =I2C1->DR;	
			}
			}
			
			// disable Acknowledge
			CLR_BIT(I2C1->CR1,10);
			
			// Generate stop condition if specified
			if(stopState == WITH_STOP)
			{
				generateStop(I2C1);
			}
			
			// enable Acknowledge
			SET_BIT(I2C1->CR1,10);
			
			break;
		
		case I2C2:
			
			// Generate start condition if specified
			generateStart(I2C2, startState);
			
			// Wait for start condition to be generated
			while(!GET_BIT(I2C2->SR1,0));
			
			// Send slave address with read bit (0) set
			sendAddress(I2C2, address, 0);
			
			// Wait for address to be sent and ACK received
			while(!GET_BIT(I2C2->SR1,1));
			
			// To reset ADDR bit
			dummyRead = I2C2->SR2;
			
			// Acknowledge returned after a byte is received (matched address or data)
			SET_BIT(I2C2->CR1,10);
			
			if(dataLength) //Check if data length exist
			{
			for(uint16 index=0; index < dataLength; index++)
			{
				// wait until data register is ready
				while(!GET_BIT(I2C2->SR1,6));				
				dataBuffer[index] =I2C2->DR;	
			}
			}
			
			// disable Acknowledge
			CLR_BIT(I2C2->CR1,10);
			
			// Generate stop condition if specified
			if(stopState == WITH_STOP)
			{
				generateStop(I2C2);
			}
			
			// enable Acknowledge
			SET_BIT(I2C2->CR1,10);
			
			break;
	}
}


// This function generates a start condition for I2C communication on a specified I2C bus
// It takes in the I2C bus number and a start state parameter (either START or REPEATED_START)
// If the start state is not REPEATED_START, it waits until the bus is ready before generating the start condition
// It sets the appropriate bit in the I2C control register to generate the start condition
void generateStart(uint8 I2CNum, uint8 startState)
{
	switch(I2CNum)
	{
		case I2C1:
		if(startState!= REPEATED_START)
		{
			while(GET_BIT(I2C1->SR2,1)); // wait until bus is ready
		}
		SET_BIT(I2C1->CR1,8); // set start bit in control register
		break;
		
		case I2C2:
		if(startState!= REPEATED_START)
		{
			while(GET_BIT(I2C2->SR2,1)); // wait until bus is ready
		}
		SET_BIT(I2C2->CR1,8); // set start bit in control register
		break;
	}
	
}


// This function sends the specified address and transmission direction over the specified I2C bus
// It takes in the I2C bus number, the address to send, and a transmit direction (either READ or WRITE)
// It shifts the address left by one and ORs it with the transmit direction to create the appropriate 8-bit address
// It then sends the address over the I2C bus using the appropriate data register
void sendAddress(uint8 I2CNum, uint16 address, uint8 transmitDirection)
{
	switch (I2CNum)
	{
		case I2C1:		
				address <<= 1; // shift address left by one
				address  |= transmitDirection; // OR with transmit direction to create 8-bit address
				I2C1->DR =(uint8)address; // send address using data register
		break;
		
		case I2C2:
				address <<= 1; // shift address left by one
				address  |= transmitDirection; // OR with transmit direction to create 8-bit address
				I2C2->DR =(uint8)address; // send address using data register
		break;
	}
}


// This function generates a stop condition for I2C communication on a specified I2C bus
// It takes in the I2C bus number and sets the appropriate bit in the I2C control register to generate the stop condition
void generateStop(uint8 I2CNum)
{
		switch (I2CNum)
	{
		case I2C1:		
				SET_BIT(I2C1->CR1,9); // set stop bit in control register
		break;
		
		case I2C2:
				SET_BIT(I2C2->CR1,9); // set stop bit in control register

		break;
	}
}
