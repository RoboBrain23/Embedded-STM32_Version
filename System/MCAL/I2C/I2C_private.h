/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : I2C_private.h                                     */
/* Description : Private addresses for I2C module stm32f103        */
/*******************************************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#define NNUMBER_OF_I2C_IN_STM32F103C6   2

typedef struct
{
    uint32 CR1;     // I2C Control Register 1 (full access)
    uint32 CR2;     // I2C Control Register 2 (full access)
    uint32 OAR1;    // I2C Own Address Register 1 (full access)
    uint32 OAR2;    // I2C Own Address Register 2 (full access)
    uint32 DR;      // I2C Data Register (16-bit access)
    uint32 SR1;     // I2C Status Register 1 (full access)
    uint32 SR2;     // I2C Status Register 2 (full access)
    uint32 CCR;     // I2C Clock Control Register (full access)
    uint32 TRISE;   // I2C TRISE Register (full access)
    
}I2C_t;


//Array of pointers to I2C_t structures
 volatile I2C_t * const I2C[NNUMBER_OF_I2C_IN_STM32F103C6] =
{
    ((volatile I2C_t *)0x40005400),  //I2C1 Address
    ((volatile I2C_t *)0x40005800)   //I2C2 Address
};


 // This function generates a stop condition for I2C communication on a specified I2C bus
 // It takes in the I2C bus number and sets the appropriate bit in the I2C control register to generate the stop condition
 void generateStop(uint8 I2CNum);


 // This function sends the specified address and transmission direction over the specified I2C bus
 // It takes in the I2C bus number, the address to send, and a transmit direction (either READ or WRITE)
 // It shifts the address left by one and ORs it with the transmit direction to create the appropriate 8-bit address
 // It then sends the address over the I2C bus using the appropriate data register
 void sendAddress(uint8 I2CNum, uint16 address, uint8 transmitDirection);


 // This function generates a start condition for I2C communication on a specified I2C bus
 // It takes in the I2C bus number and a start state parameter (either START or REPEATED_START)
 // If the start state is not REPEATED_START, it waits until the bus is ready before generating the start condition
 // It sets the appropriate bit in the I2C control register to generate the start condition
 void generateStart(uint8 I2CNum, uint8 startState);

#define I2C_WRITE   0
#define I2C_READ    1

#endif // I2C_PRIVATE_H
 
