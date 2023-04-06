/***************************************************************/
/* Author	   : Ibrahim Diab			   					   */
/* File Name   : RCC_config.h    		   					   */
/* Description : Configuration for RCC module stm32f103 	   */
/***************************************************************/


#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* 
 IMPORTANT NOTES: 
 
- The driver does not support error handling that may occur when setting different clock frequency inputs and prescaler values.
 It is the responsibility of the user to ensure that correct configurations are set to avoid any errors.
 
- The driver does not support getting the current frequency of clock buses.
 In case of changing the default clock values, 
 you should manually rewrite the clock frequency of each bus in "STM32F103C6.h" file to ensure correct functionality.

*/



/* [Must] Select clock type   
Options:
		 RCC_HSI
		 RCC_HSE_RC
		 RCC_HSE_CRYSTAL
		 RCC_PLL
*/
#define RCC_CLOCK_TYPE	RCC_HSI



/*  Select type only in case the clock type is PLL.
Options: 
		 RCC_PLL_IN_HSI_DIV_2 	
		 RCC_PLL_IN_HSE_DIV_2 	
		 RCC_PLL_IN_HSE	  	  	
*/
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSI_DIV_2
#endif


/* Select value only in case the clock type is PLL.
Options: 2 to 16	
*/
#if RCC_CLOCK_TYPE == RCC_PLL 
#define RCC_PLL_MUL_VAL 4
#endif 

#endif // RCC_CONFIG_H