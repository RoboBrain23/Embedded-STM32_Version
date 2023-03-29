/*******************************************************************/
/* Author	   : Ibrahim Diab			   					       */
/* File Name   : EXTI_interface.h    		   					   */
/* Description : Interfacing macros for EXTI module			 	   */
/*******************************************************************/

// Preprocessor directive to prevent multiple inclusions of the same header file.
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

// Function prototype for enabling external line interrupt.
void EXTI_enableEXTI(uint8 Line, uint8 Mode);

// Function prototype for disabling external line interrupt.
void EXTI_disableEXTI(uint8 Line);

// Function prototype for triggering external line interrupt manually.
void EXTI_setSWTrigger(uint8 Line);

// Function prototype for setting the callback function for external line interrupt.
void EXTI_setCallBack(uint8 EXTINumber, void (*ptr)(void));


// Function prototypes for Interrupt Service Routines (ISRs) for external line interrupts.
void EXTI0_IRQHandler (void);
void EXTI1_IRQHandler (void);
void EXTI2_IRQHandler (void);
void EXTI3_IRQHandler (void);
void EXTI4_IRQHandler (void);
void EXTI5_IRQHandler (void);
void EXTI6_IRQHandler (void);
void EXTI7_IRQHandler (void);
void EXTI8_IRQHandler (void);
void EXTI9_IRQHandler (void);
void EXTI10_IRQHandler(void);
void EXTI11_IRQHandler(void);
void EXTI12_IRQHandler(void);
void EXTI13_IRQHandler(void);
void EXTI14_IRQHandler(void);
void EXTI15_IRQHandler(void);

// Constants for External Line Interrupts IDs.
#define EXTI_LINE_0     0
#define EXTI_LINE_1     1
#define EXTI_LINE_2     2
#define EXTI_LINE_3     3
#define EXTI_LINE_4     4
#define EXTI_LINE_5     5
#define EXTI_LINE_6     6
#define EXTI_LINE_7     7
#define EXTI_LINE_8     8
#define EXTI_LINE_9     9
#define EXTI_LINE_10    10
#define EXTI_LINE_11    11
#define EXTI_LINE_12    12
#define EXTI_LINE_13    13
#define EXTI_LINE_14    14
#define EXTI_LINE_15    15

// Constants for Interrupts Modes.
#define RISING          0
#define FALLING         1
#define CHANGE          2

// End of header guard.
#endif // EXTI_INTERFACE_H
