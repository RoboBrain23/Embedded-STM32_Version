/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : I2C_config.h                                      */
/* Description : Configuration for I2C module stm32f103            */
/*******************************************************************/

// This header file guards against multiple inclusion
#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

/**
Requirements:

- Enable the I2C peripheral in the RCC driver.
- Configure the GPIO pins as Alternate output open-drain mode.
- Initialize the I2C configuration structure before calling I2C_init function.
 
 Note: GPIO pins used for I2C communication:
 
 I2C1:
 
 - PB6: SCL
 - PB7: SDA
  
 I2C2:

 - PB10: SCL
 - PB11: SDA
  
 Note: For I2C2, you would need to remap the pins using the AFIO registers because the default pins are not available.
 
 Note: Failing to meet any of these requirements may result in unexpected behavior of the driver.
*/


#endif // I2C_CONFIG_H