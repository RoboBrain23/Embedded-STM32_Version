/*******************************************************************/
/* Author	   : Ibrahim Diab			   					       */
/* File Name   : NVIC_interface.h    		   					   */
/* Description : Interfacing macros for NVIC module			 	   */
/*******************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

// Enable a specific interrupt by its number
void NVIC_enableInterrupt(uint8 IntNum);

// Disable a specific interrupt by its number
void NVIC_disableInterrupt(uint8 IntNum);

// Set the pending flag for a specific interrupt by its number
void NVIC_setPendingFlag(uint8 IntNum);

// Clear the pending flag for a specific interrupt by its number
void NVIC_clearPendingFlag(uint8 IntNum);

// Get the active flag for a specific interrupt by its number
// Returns 1 if the interrupt is active, 0 otherwise
uint8 NVIC_getActiveFlag(uint8 IntNum);

// Set the priority for a specific interrupt by its number
// GroubPriority: the priority group (0-7) for the interrupt
// SubPriority: the subgroup priority (0-3) for the interrupt
void NVIC_setPriority(uint8 IntNum, uint8 GroubPriority, uint8 SubPriority);
/*Note: Priority Parameters must be limited between number of bits values for groups and subgroups as pre configured value*/



/* Most common Interrupts Id Number */
#define EXTI0              6   // External interrupt line 0
#define EXTI1              7   // External interrupt line 1
#define EXTI2              8   // External interrupt line 2
#define EXTI3              9   // External interrupt line 3
#define EXTI4              10  // External interrupt line 4
#define EXTI9_5        	   23  // External interrupt lines 5 to 9
#define EXTI15_10    	   40  // External interrupt lines 10 to 15
#define TIM1_UP_TIM10      25  // Timer 1 update interrupt and timer 10 global interrupt
#define TIM1_TRG_COM_TIM11 26  // Timer 1 trigger and commutation interrupt and timer 11 global interrupt
#define TIM2               28  // Timer 2 global interrupt
#define TIM3               29  // Timer 3 global interrupt
#define TIM4               30  // Timer 4 global interrupt
#define SPI1               35  // SPI1 global interrupt
#define SPI2               36  // SPI2 global interrupt
#define USART1             37  // USART1 global interrupt
#define USART2             38  // USART2 global interrupt
#define USART3             39  // USART3 global interrupt
#define EXTI9_5            23  // External interrupt lines 5 to 9
#define EXTI15_10          40  // External interrupt lines 10 to 15
#define ADC1_2             18  // ADC1 and ADC2 global interrupt
#define ADC3               39  // ADC3 global interrupt
#define DMA1_CH1           11  // DMA1 channel 1 global interrupt
#define DMA1_CH2           12  // DMA1 channel 2 global interrupt
#define DMA1_CH3           13  // DMA1 channel 3 global interrupt
#define DMA1_CH4           14  // DMA1 channel 4 global interrupt
#define DMA1_CH5           15  // DMA1 channel 5 global interrupt
#define DMA1_CH6           16  // DMA1 channel 6 global interrupt
#define DMA1_CH7           17  // DMA1 channel 7 global interrupt
#define DMA2_CH1           56  // DMA2 channel 1 global interrupt
#define DMA2_CH2           57  // DMA2 channel 2 global interrupt
#define DMA2_CH3           58  // DMA2 channel 3 global interrupt
#define DMA2_CH4           59  // DMA2 channel 4 global interrupt
#define DMA2_CH5           60  // DMA2 channel 5 global interrupt
#define I2C1_EV            31  // I2C1 event interrupt
#define I2C1_ER            32  // I2C1 error interrupt
#define I2C2_EV            33  // I2C2 event interrupt
#define I2C2_ER            34  // I2C2 error interrupt
#define USB_HP_CAN_TX      19  // USB high priority/CAN TX interrupt
#define USB_LP_CAN_RX0     20  // USB low priority/CAN RX0 interrupt
#define USBWakeUp          42  // USB wakeup interrupt

#endif // NVIC_INTERFACE_H
