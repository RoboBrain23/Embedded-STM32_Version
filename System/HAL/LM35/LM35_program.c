/********************************************************************************************/
/* Author      : Ibrahim Diab                                                               */
/* File Name   : LM35_program.c                                                             */
/* Description : Functions Implementation for LM35 temperature sensor (HAL Layer)           */
/********************************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_private.h"
#include "LM35_config.h"


void LM35_init()
{   
    // check if LM35_channel_ID is within valid range for GPIOA
    if(LM35_channel_ID <= ADC_CHANNEL_7 && LM35_channel_ID >= ADC_CHANNEL_0)
    {
        // enable clock for GPIOA
        RCC_enableClk (RCC_APB2, GPIOA);
        
        // set the direction of the corresponding GPIO pin to input analog mode
        DIO_setPinDirection(GPIOA, LM35_channel_ID, INPUT_ANALOG);
    }
    
    // check if LM35_channel_ID is within valid range for GPIOB
    else if(LM35_channel_ID <= ADC_CHANNEL_9)
    {
        // enable clock for GPIOB
        RCC_enableClk (RCC_APB2, GPIOB);

        // set the direction of the corresponding GPIO pin to input analog mode
        DIO_setPinDirection(GPIOB, LM35_channel_ID, INPUT_ANALOG);
    }
    
    // check if LM35_channel_ID is within valid range for GPIOC
    else if(LM35_channel_ID <= ADC_CHANNEL_15)
    {
        // enable clock for GPIOC
        RCC_enableClk (RCC_APB2, GPIOC);

        // set the direction of the corresponding GPIO pin to input analog mode
        DIO_setPinDirection(GPIOC, LM35_channel_ID, INPUT_ANALOG);
    }
    
    // if LM35_channel_ID is out of range, do nothing or return error
    else 
    {
        // do nothing
    }
    
    // enable clock for ADC1
    RCC_enableClk (RCC_APB2, ADC1);
    
    // initialize ADC1
    ADC_init(ADC1);

    // set the channel for regular group conversion
    ADC_setChannel(ADC1, LM35_channel_ID, ADC_Group_Regular);

    // set the conversion sequence
    ADC_regulargroupInit(ADC1, LM35_convertion_NUM);

    // set the ADC to single conversion mode
    Adc_setMode(ADC_MODE_SINGLE);
}

#if MEASURE_SETUP == LM35_BASIC
// Function to read the positive range temperature from an LM35 sensor and return the value as an uint8 type
uint8 LM35_getTemperature()
{
    // Declare a variable to hold the temperature value
    uint16 temperature;
    
    // Read the voltage output of the LM35 sensor using an ADC and store the result in the temperature variable
    temperature = ADC_typeRead(ADC1, LM35_channel_ID );
    
    // Convert the ADC reading to a temperature value in degrees Celsius using the formula: 
    // temperature = (voltage * LM35_MAX_TEMPERATURE) / (ADC_MAX_VALUE * SENSOR_MAX_VOLT_VALUE)
    // Note: This formula assumes that the LM35 sensor is linearly proportional to temperature and correctly calibrated
    temperature = (((((temperature * ADC_REF_VOLT_VALUE) / ADC_MAX_VALUE) * LM35_MAX_TEMPERATURE) / SENSOR_MAX_VOLT_VALUE) + 0.5);
    
    // Return the temperature value as an int16 type
    return (uint8)temperature;
}
#elif MEASURE_SETUP == LM35_FULL_RANGE

// Function to read full range temperature from an LM35 sensor and return the value as an int8 type
int8 LM35_getTemperature()
{
    // To be implemented..
}


#endif
