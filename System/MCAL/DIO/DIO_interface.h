/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DIO_interface.h                                   */
/* Description : Interfacing macros for DIO module STM32F103       */
/*******************************************************************/

// Header guard to prevent multiple inclusion of this header file
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/* Port IDs */
#define DIO_GPIOA  0    // ID for GPIO Port A
#define DIO_GPIOB  1    // ID for GPIO Port B
#define DIO_GPIOC  2    // ID for GPIO Port C

/* Pins IDs */
#define DIO_PIN0   0    // ID for Pin 0
#define DIO_PIN1   1    // ID for Pin 1
#define DIO_PIN2   2    // ID for Pin 2
#define DIO_PIN3   3    // ID for Pin 3
#define DIO_PIN4   4    // ID for Pin 4
#define DIO_PIN5   5    // ID for Pin 5
#define DIO_PIN6   6    // ID for Pin 6
#define DIO_PIN7   7    // ID for Pin 7
#define DIO_PIN8   8    // ID for Pin 8
#define DIO_PIN9   9    // ID for Pin 9
#define DIO_PIN10  10   // ID for Pin 10
#define DIO_PIN11  11   // ID for Pin 11
#define DIO_PIN12  12   // ID for Pin 12
#define DIO_PIN13  13   // ID for Pin 13
#define DIO_PIN14  14   // ID for Pin 14
#define DIO_PIN15  15   // ID for Pin 15


/* Output Pins Mode with Maximum speed up to 2MHz */
#define OUTPUT_SPEED_2MHZ_PP     0b0010    // Output push-pull mode with max speed 2MHz
#define OUTPUT_SPEED_2MHZ_OD     0b0110    // Output open-drain mode with max speed 2MHz
#define OUTPUT_SPEED_2MHZ_ALPP   0b1010    // Output push-pull mode with max speed 2MHz and alternate function
#define OUTPUT_SPEED_2MHZ_ALOD   0b1110    // Output open-drain mode with max speed 2MHz and alternate function

/* Output Pins Mode with Maximum speed up to 10MHz */
#define OUTPUT_SPEED_10MHZ_PP    0b0001    // Output push-pull mode with max speed 10MHz
#define OUTPUT_SPEED_10MHZ_OD    0b0101    // Output open-drain mode with max speed 10MHz
#define OUTPUT_SPEED_10MHZ_ALPP  0b1001    // Output push-pull mode with max speed 10MHz and alternate function
#define OUTPUT_SPEED_10MHZ_ALOD  0b1101    // Output open-drain mode with max speed 10MHz and alternate function

/* Output Pins Mode with Maximum speed up to 50MHz */
#define OUTPUT_SPEED_50MHZ_PP    0b0011    // Output push-pull mode with max speed 50MHz
#define OUTPUT_SPEED_50MHZ_OD    0b0111    // Output open-drain mode with max speed 50MHz
#define OUTPUT_SPEED_50MHZ_ALPP  0b1011    // Output push-pull mode with max speed 50MHz and alternate function
#define OUTPUT_SPEED_50MHZ_ALOD  0b1111    // Output open-drain mode with max speed 50MHz and alternate function


/* Inputs Pins Mode */
#define INPUT_ANALOG             0b0000    // Input analog mode
#define INPUT_FLOATING           0b0100    // Input floating mode
#define INPUT_PULLUP_PULLDOWN    0b1000    // Input pull-up/pull-down mode


/* Output pins Value */
#define HIGH 1
#define LOW  0



/*
 * Configures the direction (input or output) of a specific pin on a specific port.
 *
 *  Port - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  Pin  - the ID of the pin (PIN0 to PIN15)
 *  Mode - the mode to set the pin to (INPUT, OUTPUT, or any other modes that are supported by the hardware)
 */
void DIO_setPinDirection(uint8 Port, uint8 Pin, uint8 Mode);


/*
 * Sets the binary value of a specific pin in a specific GPIO port.
 *
 *  Port  - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  Pin   - the ID of the pin (PIN0 to PIN15)
 *  Value - the value to set the pin to (HIGH or LOW)
 */
void DIO_setPinValue(uint8 Port, uint8 Pin, uint8 Value);


/*
 * Gets the binary value of a specific pin in a specific GPIO port.
 *
 *  Port - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  Pin  - the ID of the pin (PIN0 to PIN15)
 *  Returns the binary value of the pin (HIGH or LOW)
 */
uint8 DIO_getPinValue(uint8 Port, uint8 Pin);




/*
 * Sets the direction (input or output) of multiple pins in a specific GPIO port.
 *
 *  Port     - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  startPin - the ID of the first pin to be set (PIN0 to PIN15)
 *  Numpins  - the number of pins to be set (1 to 16)
 *  Mode     - the direction to be set as selected Mode
 */
void DIO_setMultiPinsDirection(uint8 Port, uint8 startPin, uint8 Numpins, uint8 Mode);


/*
 * Sets the binary value of multiple pins in a specific GPIO port.
 *
 *  Port     - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  StartPin - the ID of the first pin to be set (PIN0 to PIN15)
 *  NumPins  - the number of pins to be set (1 to 16)
 *  Value    - the binary value of the pins to be set (a 16-bit integer, where each bit corresponds to a pin)
 */
void DIO_setMultiPinValue(uint8 Port, uint8 StartPin, uint8 NumPins, uint16 Value );




/*
 * Gets the binary value of multiple pins in a specific GPIO port.
 *
 *  Port     - the ID of the GPIO port (GPIOA, GPIOB or GPIOC)
 *  StartPin - the ID of the first pin to be read (PIN0 to PIN15)
 *  NumPins  - the number of pins to be read (1 to 16)
 *
 *  Returns the binary value of the specified pins (a 16-bit integer, where each bit corresponds to a pin)
 */
uint16 DIO_getMultiPinValue(uint8 Port, uint8 StartPin, uint8 NumPins);


#endif // DIO_INTERFACE_H
