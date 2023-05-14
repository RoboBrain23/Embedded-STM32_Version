/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DIO.c                                             */
/* Description : Functions Implementation for DIO module           */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



/* Configures the direction (input or output) of a specific pin on a specific port.*/
void DIO_setPinDirection(uint8 Port, uint8 Pin, uint8 Mode)
{
    // Select the GPIO port based on the input parameter
    switch (Port)
    {
        case DIO_GPIOA:

            if(Mode == INPUT_PULLDOWN)
            {
                // Clear the pin number in ODR register to configure the pin as PullDown
                CLR_BIT(GPIOA_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else if(Mode == INPUT_PULLUP)
            {
                // Set the pin number in ODR register to configure the pin as PullDown
                SET_BIT(GPIOA_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else
            {
                CLR_BIT(GPIOA_ODR,Pin); // To reset ODR value in case
            }

            // If the pin number is within the range of 0-7 (inclusive)
            if (Pin <= 7)
            {
                // Clear the 4 bits corresponding to the pin in the CRL register
                GPIOA_CRL &= ~(0b1111 << (Pin * 4));
                // Set the 4 bits corresponding to the desired mode in the CRL register
                GPIOA_CRL |= (Mode << (Pin * 4));
            }
            // If the pin number is within the range of 8-15 (inclusive)
            else if (Pin <= 15)
            {
                // Subtract 8 from the pin number to get the index within the CRH register
                Pin -= 8;
                // Clear the 4 bits corresponding to the pin in the CRH register
                GPIOA_CRH &= ~(0b1111 << (Pin * 4));
                // Set the 4 bits corresponding to the desired mode in the CRH register
                GPIOA_CRH |= (Mode << (Pin * 4));
            }

            break;

        case DIO_GPIOB:

            if(Mode == INPUT_PULLDOWN)
            {
                // Clear the pin number in ODR register to configure the pin as PullDown
                CLR_BIT(GPIOB_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else if(Mode == INPUT_PULLUP)
            {
                // Set the pin number in ODR register to configure the pin as PullDown
                SET_BIT(GPIOB_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else
             {
                CLR_BIT(GPIOA_ODR,Pin); // To reset ODR value in case of reconfiguration
             }

            // Same as above for GPIOB
            if (Pin <= 7)
            {
                GPIOB_CRL &= ~(0b1111 << (Pin * 4));
                GPIOB_CRL |= (Mode << (Pin * 4));
            }
            else if (Pin <= 15)
            {
                Pin -= 8;
                GPIOB_CRH &= ~(0b1111 << (Pin * 4));
                GPIOB_CRH |= (Mode << (Pin * 4));
            }
            break;

        case DIO_GPIOC:

            if(Mode == INPUT_PULLDOWN)
            {
                // Clear the pin number in ODR register to configure the pin as PullDown
                CLR_BIT(GPIOC_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else if(Mode == INPUT_PULLUP)
            {
                // Set the pin number in ODR register to configure the pin as PullDown
                SET_BIT(GPIOC_ODR,Pin);
                // Set the 4 bits corresponding to the desired mode in the CRL register
                Mode = 0b1000;
            }
            else
             {
                CLR_BIT(GPIOA_ODR,Pin); // To reset ODR value in case of reconfiguration
             }

            // Same as above for GPIOC
            if (Pin <= 7)
            {
                GPIOC_CRL &= ~(0b1111 << (Pin * 4));
                GPIOC_CRL |= (Mode << (Pin * 4));
            }
            else if (Pin <= 15)
            {
                Pin -= 8;
                GPIOC_CRH &= ~(0b1111 << (Pin * 4));
                GPIOC_CRH |= (Mode << (Pin * 4));
            }
            break;

        default:
            // do nothing for invalid GPIO port
            break;
    }
}



/* Set the binary value of a specific pin in a specific GPIO port.*/
void DIO_setPinValue(uint8 Port, uint8 Pin, uint8 Value)
{
    /* Select the appropriate GPIO port */
    switch(Port)
    {
        case DIO_GPIOA:
            /* Set the pin to HIGH if the value is HIGH, else set it to LOW */
            if(Value == HIGH)
                SET_BIT(GPIOA_ODR, Pin);
            else if(Value == LOW)
                CLR_BIT(GPIOA_ODR, Pin);
            break;

        case DIO_GPIOB:
            /* Set the pin to HIGH if the value is HIGH, else set it to LOW */
            if(Value == HIGH)
                SET_BIT(GPIOB_ODR, Pin);
            else if(Value == LOW)
                CLR_BIT(GPIOB_ODR, Pin);
            break;

        case DIO_GPIOC:
            /* Set the pin to HIGH if the value is HIGH, else set it to LOW */
            if(Value == HIGH)
                SET_BIT(GPIOC_ODR, Pin);
            else if(Value == LOW)
                CLR_BIT(GPIOC_ODR, Pin);
            break;
    }
}


 /* Get the binary value of a specific pin in a specific GPIO port. */
uint8 DIO_getPinValue(uint8 Port, uint8 Pin)
{
    uint8 pinValue = 0;
    
    switch(Port)
    {
        case DIO_GPIOA:
            /* Read the binary value of the pin from GPIOA */
            pinValue = GET_BIT(GPIOA_IDR, Pin);
            break;
        
        case DIO_GPIOB:
            /* Read the binary value of the pin from GPIOB */
            pinValue = GET_BIT(GPIOB_IDR, Pin);
            break;
        
        case DIO_GPIOC:
            /* Read the binary value of the pin from GPIOC */
            pinValue = GET_BIT(GPIOC_IDR, Pin);
            break;
    }
    
    /* Return the binary value of the pin */
    return pinValue;
}



/* Sets the direction (input or output) of multiple pins in a specific GPIO port. */
void DIO_setMultiPinsDirection(uint8 Port, uint8 startPin, uint8 Numpins, uint8 Mode)
{
    // Check if the specified pins are within the range of 16 pins
    if((Numpins + startPin) <= 16)
    {
        // Loop through the specified number of pins
        for(uint8 i = 0; i < Numpins; i++)
        {
            // Set the direction of the current pin
            DIO_setPinDirection(Port, startPin + i, Mode);
        }
    }
    else
    {
        // If the specified pins are out of range, return an error value or throw an error message
        
    }
}



/* Set the values of multiple pins on a GPIO port based on a binary value */
void DIO_setMultiPinValue(uint8 Port, uint8 StartPin, uint8 NumPins, uint16 Value )
{
    // Check if the number of pins to modify is valid (less than or equal to 16)
    if((NumPins+StartPin)<=16)
    {
        // Select the specified GPIO port and modify the specified pins with the specified value
        switch(Port)
        {
            case DIO_GPIOA:
                MOD_NBIT(GPIOA_ODR, StartPin, NumPins, Value);
                break;

            case DIO_GPIOB:
                MOD_NBIT(GPIOB_ODR, StartPin, NumPins, Value);
                break;

            case DIO_GPIOC:
                MOD_NBIT(GPIOC_ODR, StartPin, NumPins, Value);
                break;
        }
    }
    else
    {
        // If the number of pins to modify is invalid, do nothing
    }
}


/* Returns the binary value of multiple pins on a specific GPIO port */
uint16 DIO_getMultiPinValue(uint8 Port, uint8 StartPin, uint8 NumPins)
{
    // Initialize binary value to 0
    uint16 pinsValue = 0;
    
    // Switch statement based on selected GPIO port
    switch(Port)
    {
        case DIO_GPIOA:
            // Read the binary value of the pins from GPIOA
            pinsValue = GET_NBIT(GPIOA_IDR, StartPin, NumPins);
            break;
        
        case DIO_GPIOB:
            // Read the binary value of the pins from GPIOB
            pinsValue = GET_NBIT(GPIOB_IDR, StartPin, NumPins);
            break;
        
        case DIO_GPIOC:
            // Read the binary value of the pins from GPIOC
            pinsValue = GET_NBIT(GPIOC_IDR, StartPin, NumPins);
            break;
    }
    
    // Return the binary value of the pins read from the port
    return pinsValue;
}


