/**********************************************************************************/
/* Author	: Hind Fouad                                                          */
/* date		: 8 Mar 2022                                                          */
/* Version	: V01                                                                 */
/**********************************************************************************/

/******************include files******************************/
#include "std_types.h"
#include "common_macros.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/***************function*****************************/
void ADC_init(ADC_type * ADCx)
{
/* power ADC ON*/
SET_BIT (ADCx-> CR2, ADON);
/* start calibration*/
SET_BIT (ADCx -> CR2 ,CAL);

}

/*conversion number must be from 1 to 16 */
void ADC_regulargroupInit(ADC_type * ADCx,Convertion_Number Convertion_x)
{
  uint32 reg_value;

  // read current value of ADC_SQR1 register
  reg_value = ADCx->SQR1;

  // clear the bits for number of regular conversions (bits 20-23)
  reg_value &= ~(0xF << 20);

  // set the new value for number of regular conversions
  reg_value |= ((Convertion_x - 1) << 20);

  // write the new value back to ADC_SQR1 register
  ADCx->SQR1 = reg_value;	
}

/*conversion number must be from 1 to 4 */
void ADC_injectedGroupInit(ADC_type * ADCx ,Convertion_Number Convertion_x)
{
  uint32 reg_value;

  // read current value of ADC_JSQR register
  reg_value = ADCx->JSQR;
   

  // clear the bits for number of regular conversions (bits 20-21)
  reg_value &= ~(0xF << 20);

  // set the new value for number of regular conversions
  reg_value |= ((Convertion_x - 1) << 20);

  // write the new value back to ADC_SQR1 register
  ADCx->JSQR = reg_value;	
	
}

void ADC_setChannel(ADC_type* ADCx, ADC_channel_t channel, ADC_Group_Type group_type)
{
	/* check if regular or injected*/
  if (group_type == ADC_Group_Regular) {
	  /*check ADC type**/
    if (ADCx == ADC1) {
      ADC1->SQR1 &= ~(ADC_SQR1_L);
      ADC1->SQR3 |= channel;
    } else if (ADCx == ADC2) {
      ADC2->SQR1 &= ~(ADC_SQR1_L);
      ADC2->SQR3 |= channel;
    }
  } else if (group_type == ADC_Group_Injected) {
    if (ADCx == ADC1) {
      ADC1->JSQR &= ~(ADC_JSQR_JL);
      ADC1->JSQR |= channel << ADC_JSQR_JSQ1_Pos;
    } else if (ADCx == ADC2) {
      ADC2->JSQR &= ~(ADC_JSQR_JL);
      ADC2->JSQR |= channel << ADC_JSQR_JSQ1_Pos;
    }
  }
}

void Adc_setMode(Mode_Type mode)
{
  /* Configure ADC mode */
  if (mode ==  ADC_MODE_SINGLE) {
	  /* Single conversion mode */
	  CLR_BIT (ADC1 -> CR2 , CONT);
     
	/* Disable discontinuous mode */
	CLR_BIT( ADC1 -> CR1 , DISCEN); 
          
  } else if (mode == ADC_MODE_CONTINUOUS) {
	 /* Continuous conversion mode */
	 SET_BIT ( ADC1->CR2,CONT);
     
    /* Disable discontinuous mode */	
    CLR_BIT( ADC1 -> CR1 , DISCEN);       
  } else if (mode == ADC_MODE_DISCONTINUOUS) {
    /* Single conversion mode */
    CLR_BIT (ADC1 -> CR2 , CONT);
    /* Enable discontinuous mode */	
	SET_BIT(ADC1->CR1 , DISCEN);
             
  }
}

uint16 ADC_typeRead(ADC_type* ADCx ,ADC_channel_t Channel ) {
	 // Set the channel in the sequence register
	  ADC1->SQR3 = Channel;

	  // Start a conversion
	  SET_BIT(ADCx->CR2, ADON);
	  /* SWSTART bit*/
	  SET_BIT(ADCx->CR2,22);

	  // Wait for the conversion to complete
	  while (!(ADCx->SR & ADC_SR_EOC));

	  // Read the converted value
	  uint16 value = ADCx->DR;

	 return value;
}
