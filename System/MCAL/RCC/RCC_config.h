/***************************************************************/
/* Author      : Ibrahim Diab                                  */
/* File Name   : RCC_config.h                                  */
/* Description : Configuration for RCC module STM32F103        */
/***************************************************************/


#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* 
 IMPORTANT NOTES: 
 
- The driver does not support error handling that may occur when setting different clock frequency inputs and pre-scaler values.
 It is the responsibility of the user to ensure that correct configurations are set to avoid any errors.
 
- The driver does not support getting the current frequency of clock buses.
 In case of changing the default clock values, 
 you should manually rewrite the clock frequency of each bus in "STM32F103C6.h" file to ensure correct functionality.

*/


/******************************* Clock Frequency Configuration *******************************/
/* [Must] Select clock type   
Options:
         RCC_HSI
         RCC_HSE_RC
         RCC_HSE_CRYSTAL
         RCC_PLL
*/
#define RCC_CLK_TYPE  RCC_PLL



/*  Select type only in case the clock type is PLL.
Options: 
         RCC_PLL_IN_HSI_DIV_2   
         RCC_PLL_IN_HSE_DIV_2   
         RCC_PLL_IN_HSE         
*/
#if RCC_CLK_TYPE == RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSI_DIV_2
#endif


/* Select value only in case the clock type is PLL.
Options: 2 to 16    
*/
#if RCC_CLK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL 9
#endif 


/******************************* Prescaler Configuration *******************************/

/* Options: AHB_NOT_DIVIDED, AHB_DIV_BY_2, 4, 8, 16, 64, 128, 256, AHB_DIV_BY_512 */
/* Note: AHB Bus maximum clock frequency value input equals 72MHZ */
/* Note: In case of using a prescaler different from 1, you should enable the prefetch buffer*/
#define AHB_PRESCALER   AHB_NOT_DIVIDED

/* Options: APB1_NOT_DIVIDED, APB1_DIV_BY_2, 4, 8, APB1_DIV_BY_16 */
/* Note: APB1 Bus maximum clock frequency value input equals 36MHZ */
#define APB1_PRESCALER  APB1_NOT_DIVIDED

/* Options: APB2_NOT_DIVIDED, APB2_DIV_BY_2, 4, 8, APB2_DIV_BY_16 */
/* Note: APB2 Bus maximum clock frequency value input equals 72MHZ */
#define APB2_PRESCALER  APB2_NOT_DIVIDED

/* Options: ADC_DIV_BY_2, 4, 6, ADC_DIV_BY_8 */
/* Note: ADC maximum clock frequency value input equals 14MHZ */
#define ADC_PRESCALER   ADC_DIV_BY_2


#endif // RCC_CONFIG_H
