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
const volatile I2C_t * I2C[NNUMBER_OF_I2C_IN_STM32F103C6] =
{
    ((volatile I2C_t *)0x40005400),  //I2C1 Address
    ((volatile I2C_t *)0x40005800)   //I2C2 Address
};

#endif // I2C_PRIVATE_H
 