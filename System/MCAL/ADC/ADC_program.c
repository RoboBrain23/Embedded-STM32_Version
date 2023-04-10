/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     : 8 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/

/******************include files******************************/
#include "std_types.h"
#include "common_macros.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/***************function*****************************/
void ADC_init(ADC_Num  ADCX)
{
/* power ADC ON*/
SET_BIT (ADC[ADCX]-> CR2, ADON);
/* start calibration*/
SET_BIT (ADC[ADCX] -> CR2 ,CAL);

}

/*conversion number must be from 1 to 16 */
void ADC_regulargroupInit(ADC_Num  ADCX,Convertion_Number Convertion_x)
{
  uint32 reg_value;

  // read current value of ADC_SQR1 register
  reg_value = ADC[ADCX]->SQR1;

  // clear the bits for number of regular conversions (bits 20-23)
  reg_value &= ~(0xF << 20);

  // set the new value for number of regular conversions
  reg_value |= ((Convertion_x - 1) << 20);

  // write the new value back to ADC_SQR1 register
  ADC[ADCX]->SQR1 = reg_value;
}

/*conversion number must be from 1 to 4 */
void ADC_injectedGroupInit(ADC_Num  ADCX ,Convertion_Number Convertion_x)
{
  uint32 reg_value;

  // read current value of ADC_JSQR register
  reg_value = ADC[ADCX]->JSQR;
   

  // clear the bits for number of regular conversions (bits 20-21)
  reg_value &= ~(0xF << 20);

  // set the new value for number of regular conversions
  reg_value |= ((Convertion_x - 1) << 20);

  // write the new value back to ADC_SQR1 register
  ADC[ADCX]->JSQR = reg_value;
    
}

void ADC_setChannel(ADC_Num ADCX, ADC_channel_t channel, ADC_Group_Type group_type)
{
    /* check if regular or injected*/
  if (group_type == ADC_Group_Regular) {

      ADC[ADCX]->SQR1 &= ~(ADC_SQR1_L);
      ADC[ADCX]->SQR3 |= channel;


  } else if (group_type == ADC_Group_Injected) {

      ADC[ADCX]->JSQR &= ~(ADC_JSQR_JL);
      ADC[ADCX]->JSQR |= channel << ADC_JSQR_JSQ1_Pos;

    }

}

void Adc_setMode(ADC_Num ADCX ,Mode_Type mode)
{
  /* Configure ADC mode */
  if (mode ==  ADC_MODE_SINGLE) {
      /* Single conversion mode */
      CLR_BIT (ADC[ADCX] -> CR2 , CONT);
     
    /* Disable discontinuous mode */
    CLR_BIT( ADC[ADCX] -> CR1 , DISCEN);
          
  } else if (mode == ADC_MODE_CONTINUOUS) {
     /* Continuous conversion mode */
     SET_BIT ( ADC[ADCX]->CR2,CONT);
     
    /* Disable discontinuous mode */    
    CLR_BIT( ADC[ADCX] -> CR1 , DISCEN);
  } else if (mode == ADC_MODE_DISCONTINUOUS) {
    /* Single conversion mode */
    CLR_BIT (ADC[ADCX] -> CR2 , CONT);
    /* Enable discontinuous mode */ 
    SET_BIT(ADC[ADCX]->CR1 , DISCEN);
             
  }
}

uint16 ADC_typeRead(ADC_Num ADCX ,ADC_channel_t Channel ) {
     // Set the channel in the sequence register
      ADC[ADCX]->SQR3 = Channel;

      // Start a conversion
      SET_BIT(ADC[ADCX]->CR2, ADON);
      /* SWSTART bit*/
      SET_BIT(ADC[ADCX]->CR2,22);

      // Wait for the conversion to complete
      while (!(ADC[ADCX]->SR & ADC_SR_EOC));

      // Read the converted value
      uint16 value = ADC[ADCX]->DR;

     return value;
}
