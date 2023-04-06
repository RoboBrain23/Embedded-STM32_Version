/*******************************************************************/
/* Author	   : Ibrahim Diab			   					       */
/* File Name   : I2C_config.h    		   						   */
/* Description : Configuration for I2C module stm32f103		 	   */
/*******************************************************************/

// This header file guards against multiple inclusion
#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

/**
Requirements:

- Enable the I2C peripheral in the RCC driver.
- Configure the GPIO pins as output open-drain mode.
- Initialize the I2C configuration structure before calling I2C_init function.
 
 Note: GPIO pins used for I2C communication:
  - PB6: I2C1_SCL
  - PB7: I2C1_SDA
 
Note: Failing to meet any of these requirements may result in unexpected behavior of the driver.
*/


#endif // I2C_CONFIG_H