/**************************************************************************/
/* Author      : Ibrahim Diab                                             */
/* File Name   : EXTI_config.h                                            */
/* Description : Configuration for EXTI Module for STM32f103c6            */
/**************************************************************************/

#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

/**
Requirements:

- Enable the RCC peripheral clock for AFIO.
- Configure EXTI interrupt lines using "AFIO_setEXTIConfig" function.
- Enable the NVIC for the EXTI IRQ.
- Set the callback function using the EXTI_setCallBack() function before using EXTI_enableEXTI() function.

Note: Failing to meet any of these requirements may result in unexpected behavior of the driver.
*/


#endif //EXTI_CONFIG_H

