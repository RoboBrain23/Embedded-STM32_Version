/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : I2C_interface.h                                   */
/* Description : Interfacing macros for I2C module stm32f103       */
/*******************************************************************/

// Header guard to prevent multiple inclusions
#ifndef I2C_INTERFACE_H 
#define I2C_INTERFACE_H


// Definition of a structure that holds the configuration parameters for an I2C peripheral
typedef struct
{
    // Configuration flags for various modes and settings
    uint8 I2C_mode              : 1;        // I2C operating mode (standard or fast mode)
    uint8 SM_Bus_mode           : 1;        // SMBus mode enable/disable
    uint8 address_mode          : 1;        // Addressing mode (7-bit or 10-bit addressing)
    uint8 dual_addressing_mode  : 1;        // Dual addressing mode enable/disable
    uint8 I2C_Acknowledge       : 1;        // Enable/disable ACK/NACK bit for I2C data transfer
    uint8 general_call          : 1;        // General call enable/disable
    uint8 stretch_mode          : 1;        // Clock stretching enable/disable
    uint8 event_interrupt       : 1;        // Event interrupt enable/disable
    uint8 error_interrupt       : 1;        // Error interrupt enable/disable
    uint8 I2C_Clock_Speed_in_KHZ;           // I2C clock speed in kHz
                                            // Valid range: 1 to 100
                                    
    uint8 own_address;                      // I2C own address
} I2C_config_t;

// Definitions for various flags used in the I2C configuration structure
#define I2C_DISABLE              0
#define I2C_ENABLE               1

// Definitions for I2C operating modes
#define I2C_SM_MODE              0  // Standard mode
#define I2C_FM_MODE              1  // Fast mode

// Definitions for I2C addressing modes
#define I2C_7_BIT_ADDRESS_MODE   0  // 7-bit addressing
#define I2C_10_BIT_ADDRESS_MODE  1  // 10-bit addressing

// Definitions for stop mode
#define I2C_STOP_ENABLE          0  // Generate stop condition
#define I2C_REPEATED_START       1  // Generate repeated start condition

// Definitions for SM_Bus mode
#define I2C_MODE                 0  // I2C mode
#define SMBus_mode               1  // SMBus mode

// Definitions for clock stretching mode
#define STRETCH_ENABLED          0  // Enable clock stretching
#define STRETCH_DISABLED         1  // Disable clock stretching

// Definitions for I2C number
#define I2C1                     0  // I2C1 peripheral
#define I2C2                     1  // I2C2 peripheral

// Definition for stop state
#define WITHOUT_STOP             0  // Indicates that stop condition will not be generated after sending data
#define WITH_STOP                1  // Indicates that stop condition will be generated after sending data

// Definitions for start state
#define START                    0  // Indicates that start condition will be generated before sending data
#define REPEATED_START           1  // Indicates that repeated start condition will be generated before sending data


// Initialize I2C peripheral
void I2C_init(uint8 I2CNum, I2C_config_t * I2C_config);

/*
 * Sends data over I2C interface
 *
 * I2Cx: specifies the I2C peripheral to use (I2C1 or I2C2)
 * address: the 7-bit address of the I2C slave
 * dataBuffer: pointer to the buffer containing the data to be sent
 * dataLength: length of the data to be sent
 * startState: specifies whether to use a repeated start or not
 * stopState: specifies whether to send a stop condition after the data has been sent
 */
void I2C_sendData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState);

/*
 * Receive data over I2C interface
 *
 * I2Cx: specifies the I2C peripheral to use (I2C1 or I2C2)
 * address: the 7-bit address of the I2C slave
 * dataBuffer: pointer to the buffer containing the data to be received
 * dataLength: length of the data to be received
 * startState: specifies whether to use a repeated start or not
 * stopState: specifies whether to send a stop condition after the data has been received
 */
void I2C_receiveData(uint8 I2CNum, uint16 address, uint8 * dataBuffer, uint16 dataLength, uint8 startState, uint8 stopState);


#endif // I2C_INTERFACE_H
