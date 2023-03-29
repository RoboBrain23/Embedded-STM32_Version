/**************************************************************************************/
/* Author     : Ibrahim Diab                                                          */
/* File Name  : LM35_interface.h                                                      */
/* Description: Interfacing macros for LM35 temperature sensor (HAL Layer)     	      */
/**************************************************************************************/

#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H



/*
 * Function: LM35_init
 * -------------------
 * Enabling required RCC buses and peripherals.
 * Initializes the GPIO module.
 * Initializes the LM35 temperature sensor by configuring the ADC pin and enabling the ADC module.
 * This function should be called before using the LM35_getTemperature function.
 */
void LM35_init();


#if MEASURE_SETUP == LM35_BASIC
/*
 * Function: LM35_getTemperature
 * ----------------------------
 * Reads the temperature from an LM35 temperature sensor connected to an ADC pin
 * Returns: uint8 value representing the positive range temperature in degrees Celsius (Â°C)
 */
uint8 LM35_getTemperature();


#elif MEASURE_SETUP == LM35_FULL_RANGE
/*
 * Function: LM35_getTemperature
 * ----------------------------
 * Reads the temperature from an LM35 temperature sensor connected to an ADC pin
 * Returns: int8 value representing the full range temperature in degrees Celsius (Â°C)
 */
int8 LM35_getTemperature();
#endif


#endif //LM35_INTERFACE_H