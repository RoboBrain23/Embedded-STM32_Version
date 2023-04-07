/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : I2C_private.h                                     */
/* Description : Private addresses for I2C module stm32f103        */
/*******************************************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H


typedef struct
{
    uint32 CR1;
    uint32 CR2;
    uint32 OAR1;
    uint32 OAR2;
    uint32 DR;
    uint32 SR1;
    uint32 SR2;
    uint32 CCR;
    uint32 TRISE;
    
}I2C_t;

#define I2C1 ((volatile I2C_t *)0x40005400)
#define I2C2 ((volatile I2C_t *)0x40005800)

#endif // I2C_PRIVATE_H
 