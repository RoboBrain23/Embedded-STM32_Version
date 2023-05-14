/********************************************************************************************/
/* Author      : Ibrahim Diab                                                               */
/* File Name   : MotorDriver.c                                                              */
/* Description : Functions Implementation for Motor Driver (HAL Layer)                      */
/********************************************************************************************/

/* Library includes */
#include "Std_Types.h"
#include "Common_Macros.h"

/* MCU constant parameters includes */
#include "STM32F103C6.h"

/* Peripherals includes */
#include "RCC_interface.h"
#include "DIO_interface.h"

/* Module files includes */
#include "MotorDriver_interface.h"
#include "MotorDriver_private.h"
#include "MotorDriver_config.h"
