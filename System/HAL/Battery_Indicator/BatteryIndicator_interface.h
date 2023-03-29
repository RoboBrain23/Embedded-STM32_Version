/**************************************************************************************/
/* Author     : Ibrahim Diab                                                          */
/* File Name  : BatteryIndicator_interface.h    	                                  */
/* Description: Interfacing macros for  Battery Indicator (HAL Layer)          	      */
/**************************************************************************************/

#ifndef BATTERY_INDICATOR_INTERFACE_H
#define BATTERY_INDICATOR_INTERFACE_H

/*
This function initializes the battery indicator module.
It sets up the ADC for measuring the battery voltage, configures GPIO pins
and initializes any other necessary variables or settings. 
*/
void BattInd_init();
 
 
#if BATTERY_DISCHARGE_CURVE == NON_LINEAR
/*
  This function calculates the capacity level of the battery based on the lookup table of voltage values 
  for different capacity levels, obtained from the battery discharge curve.
  It reads the ADC value of the battery voltage, converts it to voltage value, and compares it to the
  voltage values in the lookup table to determine the battery capacity level.
  Returns the capacity level (1 to 10), or 0 if the battery voltage is below the minimum lookup value.
 */
uint8 BattInd_getBatteryCapacityLevel();



#elif BATTERY_DISCHARGE_CURVE == LINEAR 
/*
  This function calculates the percentage of remaining capacity of the battery based on the linear
  discharge curve of the battery, assuming that the battery voltage decreases linearly with capacity level.
  It reads the ADC value of the battery voltage, converts it to voltage value, and calculates the
  percentage of remaining capacity based on the difference between the battery voltage and the minimum
  and maximum voltages of the discharge curve.
  Returns the remaining capacity percentage (0 to 100).
 */
uint8 BattInd_getBatteryCapacityPercentage();

#endif

#endif // BATTERY_INDICATOR_INTERFACE_H
