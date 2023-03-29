/*******************************************************************/
/* Author	   : Ibrahim Diab			   					       */
/* File Name   : RCC_interface.h    		   					   */
/* Description : Interfacing macros for RCC module stm32f103 	   */
/*******************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Clock Bus ID */
#define RCC_AHB  0  			/* Advanced High-performance Bus */
#define RCC_APB1 1  			/* Peripheral Bus 1 */
#define RCC_APB2 2  			/* Peripheral Bus 2 */

/* RCC_APB2 Peripheral ID */
#define AFIO 		0  			/* Alternate Function I/O */
#define GPIOA 		2			
#define GPIOB 		3			
#define GPIOC 		4			
#define GPIOD 		5			
#define GPIOE 		6			
#define ADC1 		9  			/* Analog-to-Digital Converter 1 */
#define ADC2 		10 			/* Analog-to-Digital Converter 2 */
#define TIM1 		11 			/* Timer 1 */
#define SPI1 		12 			/* Serial Peripheral Interface 1 */
#define UART1 		14 			/* Universal Asynchronous Receiver/Transmitter 1 */

/* RCC_APB1 Peripheral ID */
#define TIM2 		0  			/* Timer 2 */
#define TIM3 		1  			/* Timer 3 */
#define TIM4 		2  			/* Timer 4 */
#define TIM5 		3  			/* Timer 5 */
#define TIM6 		4  			/* Timer 6 */
#define TIM7 		5  			/* Timer 7 */
#define WWDG 		11 			/* Window Watchdog */
#define SPI2 		14 			/* Serial Peripheral Interface 2 */
#define SPI3 		15 			/* Serial Peripheral Interface 3 */
#define UART2 		17 			/* Universal Asynchronous Receiver/Transmitter 2 */
#define UART3 		18 			/* Universal Asynchronous Receiver/Transmitter 3 */
#define UART4 		19 			/* Universal Asynchronous Receiver/Transmitter 4 */
#define UART5 		20 			/* Universal Asynchronous Receiver/Transmitter 5 */
#define I2C1		21 			/* Inter-Integrated Circuit 1 */
#define I2C2 		22 			/* Inter-Integrated Circuit 2 */
#define CAN1 		25 			/* Controller Area Network 1 */
#define CAN2 		26 			/* Controller Area Network 2 */
#define BKP			27 			/* Backup Registers */
#define PWR 		28 			/* Power Control */
#define DAC 		29 			/* Digital-to-Analog Converter */

/* RCC_AHB Peripheral ID */
#define DMA1 		0  			/* Direct Memory Access 1 */
#define DMA2 		1  			/* Direct Memory Access 2 */
#define SRAM 		2  			/* Static Random Access Memory */
#define FLITF 		3  			/* Flash Interface */
#define CRCEN 		4  			/* Cyclic Redundancy Check */
#define OTGFS 		5  			/* USB On-The-Go Full Speed */
#define ETHMAC 		11 			/* Ethernet MAC */
#define ETHMACTX 	14 			/* Ethernet MAC Transmit */
#define ETHMACRX 	15 			/* Ethernet MAC Receive */



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
