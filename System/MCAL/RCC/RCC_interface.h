/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : RCC_interface.h                                   */
/* Description : Interfacing macros for RCC module STM32F103       */
/*******************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Clock Bus ID */
#define RCC_AHB  0              /* Advanced High-performance Bus */
#define RCC_APB1 1              /* Peripheral Bus 1 */
#define RCC_APB2 2              /* Peripheral Bus 2 */

/* RCC_APB2 Peripheral ID */
#define RCC_AFIO        0           /* Alternate Function I/O */
#define RCC_GPIOA       2           /* Port A */
#define RCC_GPIOB       3           /* Port B */
#define RCC_GPIOC       4           /* Port C */
#define RCC_GPIOD       5           /* Port D */
#define RCC_GPIOE       6           /* Port E */
#define RCC_ADC1        9           /* Analog-to-Digital Converter 1 */
#define RCC_ADC2        10          /* Analog-to-Digital Converter 2 */
#define RCC_TIM1        11          /* Timer 1 */
#define RCC_SPI1        12          /* Serial Peripheral Interface 1 */
#define RCC_UART1       14          /* Universal Asynchronous Receiver/Transmitter 1 */

/* RCC_APB1 Peripheral ID */
#define RCC_TIM2        0           /* Timer 2 */
#define RCC_TIM3        1           /* Timer 3 */
#define RCC_TIM4        2           /* Timer 4 */
#define RCC_TIM5        3           /* Timer 5 */
#define RCC_TIM6        4           /* Timer 6 */
#define RCC_TIM7        5           /* Timer 7 */
#define RCC_WWDG        11          /* Window Watchdog */
#define RCC_SPI2        14          /* Serial Peripheral Interface 2 */
#define RCC_SPI3        15          /* Serial Peripheral Interface 3 */
#define RCC_UART2       17          /* Universal Asynchronous Receiver/Transmitter 2 */
#define RCC_UART3       18          /* Universal Asynchronous Receiver/Transmitter 3 */
#define RCC_UART4       19          /* Universal Asynchronous Receiver/Transmitter 4 */
#define RCC_UART5       20          /* Universal Asynchronous Receiver/Transmitter 5 */
#define RCC_I2C1        21          /* Inter-Integrated Circuit 1 */
#define RCC_I2C2        22          /* Inter-Integrated Circuit 2 */
#define RCC_CAN1        25          /* Controller Area Network 1 */
#define RCC_CAN2        26          /* Controller Area Network 2 */
#define RCC_BKP         27          /* Backup Registers */
#define RCC_PWR         28          /* Power Control */
#define RCC_DAC         29          /* Digital-to-Analog Converter */

/* RCC_AHB Peripheral ID */
#define RCC_DMA1        0           /* Direct Memory Access 1 */
#define RCC_DMA2        1           /* Direct Memory Access 2 */
#define RCC_SRAM        2           /* Static Random Access Memory */
#define RCC_FLITF       3           /* Flash Interface */
#define RCC_CRCEN       4           /* Cyclic Redundancy Check */
#define RCC_OTGFS       5           /* USB On-The-Go Full Speed */
#define RCC_ETHMAC      11          /* Ethernet MAC */
#define RCC_ETHMACTX    14          /* Ethernet MAC Transmit */
#define RCC_ETHMACRX    15          /* Ethernet MAC Receive */



/* Functions Declarations */

/* This function initializes the system clock */
void RCC_initSysClk(void);

/* This function enables the clock for a specific peripheral on a specific bus */
/* Parameters: busId - ID of the bus on which the peripheral is connected */
/*             perId - ID of the peripheral whose clock needs to be enabled */
void RCC_enableClk (uint8 busId, uint8 perId);

/* This function disables the clock for a specific peripheral on a specific bus */
/* Parameters: busId - ID of the bus on which the peripheral is connected */
/*             perId - ID of the peripheral whose clock needs to be disabled */
void RCC_disableClk(uint8 busId, uint8 perId);

#endif // RCC_INTERFACE_H
