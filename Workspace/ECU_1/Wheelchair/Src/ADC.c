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
#include "RCC_interface.h"
#include "RCC_private.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "STM32F103C6.h"

void ADC_Init(ADC_Num ADCx, const ADC_InitTypeDef *ADC_Cnfg) {

	/* Configure ADC mode */
	ADC_SetMode(ADCx, ADC_Cnfg->ADC_Mode);
	/* Configure ADC scan mode */
	ADC_SetScanMode(ADCx, ADC_Cnfg->ADC_ScanConvMode);
	/* Configure ADC Data align mode */
	ADC_SetDataAlignMode(ADCx, ADC_Cnfg->ADC_DataAlign);
	/* Configure ADC external trigger for regular group */
	ADC_ExternalTrigConvCmd(ADCx, ADC_Cnfg->ADC_ExternalTrigConv);
	/* Configure ADC continuous mode */
	ADC_SetContinuousMode(ADCx, ADC_Cnfg->ADC_ScanConvMode);
	/* Configure ADC number of channels */
	ADC_SetNumberOfChannels(ADCx, ADC_Cnfg->ADC_NbrOfChannel);

}

static void ADC_SetNumberOfChannels(ADC_Num ADCx, uint8 Copy_u8Channels)
{
	/* Assign the number of channels in sequence register */
	ADC[ADCx]->SQR1 |= ((Copy_u8Channels - (uint8) 1) << 20);
}
/******************************************************/
void ADC_ChannelCnfg(ADC_Num ADCx,ADC_channel_t Copy_u8ChNum,uint32 Copy_u32Rank,uint8 Copy_u8SampleTime)
{
	/* Regular sequence configuration */
	/* from 1 to 6 */
	if (Copy_u32Rank < 7U)
	{
		ADC[ADCx]->SQR3 &= ~((0x1F)<<(5*(Copy_u32Rank-1)));
		ADC[ADCx]->SQR3 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-1)));
	}
	/* from 7 to 12 */
	else if (Copy_u32Rank < 13U)
	{
		ADC[ADCx]->SQR2 &= ~((0x1F)<<(5*(Copy_u32Rank-7)));
		ADC[ADCx]->SQR2 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-7)));
	}
	/* from 13 to 16 */
	else
	{
		ADC[ADCx]->SQR1 &= ~((0x1F)<<(5*(Copy_u32Rank-13)));
		ADC[ADCx]->SQR1 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-13)));
	}

	/*channels from 10 to 17*/
	if (Copy_u8ChNum > ADC_CHANNEL_9)
	{
		/* Clear the old channel sample time */
		ADC[ADCx]->SMPR1 &= 0x7 << (3 * (Copy_u8ChNum - 10));
		/* Set the new channel sample time */
		ADC[ADCx]->SMPR1 |= (uint32)Copy_u8SampleTime << (3 * (Copy_u8ChNum - 10));
	}
	else /*channels from 0 to 9 */
	{
		/* Clear the old channel  */
		ADC[ADCx]->SMPR2 &= 0x7 << (3 * Copy_u8ChNum);
		/* Set the new channel */
		ADC[ADCx]->SMPR2 |= (uint32)Copy_u8SampleTime << (3 * Copy_u8ChNum);
	}
}
/*******************************************************/
/* Gets single conversion value with custom setting for the ease of use */
uint16 ADC_GetValue(ADC_Num ADCx,ADC_channel_t Copy_u8Channel,uint8 Copy_u8SamplingTime)
{
	uint16 Local_u16ReadData	=	0;
	/* Configures the channel */
	ADC_ChannelCnfg(ADCx,Copy_u8Channel,ADC_REGULAR_RANK_1,Copy_u8SamplingTime);
	/* Starts ADC */
	ADC_Start(ADCx);

	/* Get conversion value */
	Local_u16ReadData=ADC_GetConversionValue(ADCx);

	/* Disable ADC */
	ADC_Disalbe(ADCx);

	return Local_u16ReadData;
}
/* Enables ADC and start conversion */
void ADC_Start(ADC_Num ADCx)
{

	/* Clear ADC flags */
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_AWD);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_EOC);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_JEOC);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_JSTRT);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_STRT);

	/* Enable ADC */
		ADC_Enable(ADCx);
	/* Enable calibration */
	ADC_StartCalibration(ADCx);
	/* Start ADC conversion */
		ADC_StartConv(ADCx,ENABLE);


}
/* Polling on End of conversion flag */
void ADC_PollForConv(ADC_Num ADCx)
{
	/* Clear ADC flags */
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_EOC);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_STRT);
}

void ADC_EnableDMA(ADC_Num ADCx)
{
		/* Enable the selected ADC DMA request */
	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_DMA);


}
/* Resets calibration registers */
void ADC_ResetCalibration(ADC_Num ADCx)
{
	/* Resets the selected ADC calibration registers */
	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_RSTCAL);
}

/*Starts calibration */
void ADC_StartCalibration(ADC_Num ADCx)
{

	CLR_BIT(ADC[ADCx]->SR,ADC_SR_STRT);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_EOC);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_JEOC);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_JSTRT);
	CLR_BIT(ADC[ADCx]->SR,ADC_SR_AWD);


	SET_BIT(ADC[ADCx]->CR2,2);
}
/* Gets calibration status */
/*void ADC_GetCalibrationStatus(ADC_TypeDef* ADCx ,Flag_Status *Status)
{
	 Get the selected ADC calibration status
	*Status = GET_BIT(ADCx->CR2,ADC_CR2_CONT);
}*/
/* Configures ADC software conversion */
void ADC_StartConv(ADC_Num ADCx, State Copy_StartState)
{
	if (Copy_StartState == ENABLE)
	{
		/* Enable the selected ADC conversion */
		ADC[ADCx]->CR2 |= CR2_EXTTRIG_SWSTART_Set;
	}
	else if(Copy_StartState == DISABLE)
	{
		/* Disable the selected ADC conversion */
		ADC[ADCx]->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
	}

}
/* Gets ADC software conversion status */
//void ADC_GetConvStatus(ADC_Num ADCx,Flag_Status *StartStatus)
//{
//	/* the SWSTART bit status */
//	*StartStatus = GET_BIT(ADC[ADCx]->CR2,22);
//}
/* Gets ADC conversion value */
uint16 ADC_GetConversionValue(ADC_Num ADCx )
{
	/* read ADC conversion value */
	uint16 ADC_Val = (uint16)ADC[ADCx]->DR;
	return ADC_Val;
}

/* Enables ADC */
void ADC_Enable(ADC_Num ADCx)
{
	volatile uint32 ADC_StartPauseTime	=	0;
	/* First time to start ADC must enable ADC twice because it is by default in sleep mode */
	/* Enabling ADC sequence */
	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_ADON);

	/* Delay between two starts */
	ADC_StartPauseTime	=	(ADC_START_DELAY_US * (RCC_ADC_CLK_FRQ /1000000));

	while(ADC_StartPauseTime > 0)
	{
		ADC_StartPauseTime--;
	}

	/* Enable ADC again */
	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_ADON);

	while(GET_BIT(ADC[ADCx]->CR2,ADC_CR2_ADON) == NOK)
	{
		/* Wait until ADC is enabled */
	}


}

/************************************************************************************************************* */
/* Disables ADC and stops conversions */
void ADC_Disalbe(ADC_Num ADCx)
{
	/* Disable ADC */
	CLR_BIT(ADC[ADCx]->CR2,ADC_CR2_ADON);

}

static void ADC_SetContinuousMode(ADC_Num ADCx, State Copy_ContState)
{
	switch(Copy_ContState)
	{
	case DISABLE:
		/* Disable */
		CLR_BIT(ADC[ADCx]->CR2,ADC_CR2_CONT);
		break;
	case ENABLE:
		/* Enable*/
		SET_BIT(ADC[ADCx]->CR2,ADC_CR2_CONT);
		break;

	}

}


static void ADC_ExternalTrigConvCmd(ADC_Num ADCx, State Copy_xExTriggerState)
{
	switch(Copy_xExTriggerState)
	{
	case DISABLE:
		/* Disable ADC conversion on external event */
		CLR_BIT(ADC[ADCx]->CR2,ADC_CR2_EXTTRIG);
		break;
	case ENABLE:
		/* Enable ADC conversion on external event */
		SET_BIT(ADC[ADCx]->CR2,ADC_CR2_EXTTRIG);
		break;
	}
}

/* Configures data aligning mode */
static void ADC_SetDataAlignMode(ADC_Num ADCx, ADC_ALIGN_MODE Copy_u8AlignMode)
{
	switch (Copy_u8AlignMode){
	case ADC_DATA_ALIGN_RIGHT:
		CLR_BIT(ADC[ADCx]->CR2, ADC_CR2_ALIGN);
		break;
	case ADC_DATA_ALIGN_LEFT:
		SET_BIT(ADC[ADCx]->CR2,ADC_CR2_ALIGN);
		break;

	}

}

/************************************************************************************************************* */

/* Sets scan mode for ADC */
static void ADC_SetScanMode(ADC_Num ADCx, State Copy_State)
{
	switch(Copy_State)
	{
	case DISABLE:
		CLR_BIT(ADC[ADCx]->CR1,ADC_SR_SCAN);
		break;
	case ENABLE:
		SET_BIT(ADC[ADCx]->CR1,ADC_SR_SCAN);
		break;
	}
}

/************************************************************************************************************* */

/* Sets mode for ADC : Dual mode or independant mode */
static void ADC_SetMode(ADC_Num ADCx , uint32 Copy_u32Mode)
{
	/* Assign the mode */
	ADC[ADCx]->CR1 |= Copy_u32Mode;
}













//
//
///***************function*****************************/
//void ADC_init(ADC_Num ADCx,ADC_channel_t channel) {
//
//	//prescale clock cho adc /2
//	CLR_BIT(RCC_CFGR,RCC_CFGR_ADCPRE_0);
//	CLR_BIT(RCC_CFGR,RCC_CFGR_ADCPRE_1);
//
//	// enable scan mode
//	SET_BIT(ADC[ADCx]->CR1,ADC_CR1_SCAN);
//		//ADC[ADCX]->CR1|= ADC_CR1_SCAN;
//		//12 bit data align right
//	CLR_BIT(ADC[ADCx]->CR2,ADC_CR2_ALIGN);
//		//ADC[ADCX]->CR2 &=~ADC_CR2_ALIGN;
//		// continuous conversion
//	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_CONT);
//		//ADC[ADCX]->CR2|= ADC_CR2_CONT;
//		// sampling time chanel 0 : 1.5CYCLE
//	CLR_BIT(ADC[ADCx]->SMPR2,0);
//	CLR_BIT(ADC[ADCx]->SMPR2,1);
//	CLR_BIT(ADC[ADCx]->SMPR2,2);
//		//ADC[ADCX]->SMPR2 &=~ ADC_SMPR2_SMP0;
//		//Regular channel sequence length
//	CLR_BIT(ADC[ADCx]->SQR1,20);
//	CLR_BIT(ADC[ADCx]->SQR1,21);
//	CLR_BIT(ADC[ADCx]->SQR1,22);
//	CLR_BIT(ADC[ADCx]->SQR1,23);
//		//ADC[ADCX]->SQR1&=~ ADC_SQR1_L;
//		//bat pa0 thanh analog in
//
//		////configure the pins to analog*/
//
//
//	/* start calibration*/
//	//SET_BIT(ADC[ADCx]->CR2, CAL);
// ADC_Enable(ADCx);
// ADC_Start(ADCx,channel);
//}
//
//
//void ADC_Enable(ADC_Num ADCx){
//	/* power ADC ON*/
//		SET_BIT(ADC[ADCx]->CR2, ADC_CR2_ADON);
//
//	uint32 delay = 10000;
//	while(delay--);
//	/*enable conversion */
//	ADC[ADCx]->CR2 |= ADC_CR2_ADON;
//}
//void ADC_Start(ADC_Num ADCx,ADC_channel_t channel){
//	/*set channel*/
//	SET_BIT(ADC[ADCx]->SQR3,(channel<<0));
//	//ADC[ADCx]->SQR3 |= (channel<<0);
//	//reset status
//	ADC[ADCx]->SR=0;
//	//Start conversion of regular channels
//	SET_BIT(ADC[ADCx]->CR2,ADC_CR2_SWSTART);
//
//
//}
//void ADC_WaitForConv(ADC_Num ADCx){
//	/*End of conversion*/
//	while(!(ADC[ADCx]->SR & (ADC_SR_EOC)));
//}
//uint16 ADC_GetVal(ADC_Num ADCx){
//	return ADC[ADCx]->DR;
//}
//
//void ADC_Disable(ADC_Num ADCx){
//	CLR_BIT(ADC[ADCx]->CR2,ADC_CR2_ADON);
//	//ADC[ADCx]->CR2 &=~ ADC_CR2_ADON;
//}
//
//
//
///*conversion number must be from 1 to 16 */
//void ADC_regulargroupInit(ADC_Num  ADCX,Convertion_Number Convertion_x)
//{
//  uint32 reg_value;
//
//  // read current value of ADC_SQR1 register
//  reg_value = ADC[ADCX]->SQR1;
//
//  // clear the bits for number of regular conversions (bits 20-23)
//  reg_value &= ~(0xF << 20);
//
//  // set the new value for number of regular conversions
//  reg_value |= ((Convertion_x - 1) << 20);
//
//  // write the new value back to ADC_SQR1 register
//  ADC[ADCX]->SQR1 = reg_value;
//}
//
///*conversion number must be from 1 to 4 */
//void ADC_injectedGroupInit(ADC_Num  ADCX ,Convertion_Number Convertion_x)
//{
//  uint32 reg_value;
//
//  // read current value of ADC_JSQR register
//  reg_value = ADC[ADCX]->JSQR;
//
//

//  // clear the bits for number of regular conversions (bits 20-21)
//  reg_value &= ~(0xF << 20);
//
//  // set the new value for number of regular conversions
//  reg_value |= ((Convertion_x - 1) << 20);
//
//  // write the new value back to ADC_SQR1 register
//  ADC[ADCX]->JSQR = reg_value;
//
//}
//void Adc_setMode(ADC_Num ADCX ,Mode_Type mode)
//{
//   Configure ADC mode
//  if (mode ==  ADC_MODE_SINGLE) {
//       Single conversion mode
//      CLR_BIT (ADC[ADCX] -> CR2 , CONT);
//
//     Disable discontinuous mode
//    CLR_BIT( ADC[ADCX] -> CR1 , DISCEN);
//
//  } else if (mode == ADC_MODE_CONTINUOUS) {
//      Continuous conversion mode
//     SET_BIT ( ADC[ADCX]->CR2,CONT);
//
//     Disable discontinuous mode
//    CLR_BIT( ADC[ADCX] -> CR1 , DISCEN);
//  } else if (mode == ADC_MODE_DISCONTINUOUS) {
//     Single conversion mode
//    CLR_BIT (ADC[ADCX] -> CR2 , CONT);
//     Enable discontinuous mode
//    SET_BIT(ADC[ADCX]->CR1 , DISCEN);
//
//  }
//void ADC_setChannel(ADC_Num ADCX, ADC_channel_t channel, ADC_Group_Type group_type)
//{
//    /* check if regular or injected*/
//  if (group_type == ADC_Group_Regular) {
//
//      ADC[ADCX]->SQR1 &= ~(ADC_SQR1_L);
//      ADC[ADCX]->SQR3 |= channel;
//
//
//  } else if (group_type == ADC_Group_Injected) {
//
//      ADC[ADCX]->JSQR &= ~(ADC_JSQR_JL);
//      ADC[ADCX]->JSQR |= channel << ADC_JSQR_JSQ1_Pos;
//
//    }
//
//}
//
//
//
//
//uint16 ADC_typeRead(ADC_Num ADCX ,ADC_channel_t Channel ) {
//     // Set the channel in the sequence register
//      ADC[ADCX]->SQR3 = Channel;
//
//      // Start a conversion
//      SET_BIT(ADC[ADCX]->CR2, ADC_CR2_ADON);
//      /* SWSTART bit*/
//      SET_BIT(ADC[ADCX]->CR2,22);
//
//      // Wait for the conversion to complete
//      while (!(ADC[ADCX]->SR & ADC_SR_EOC));
//
//      // Read the converted value
//      uint16 value = ADC[ADCX]->DR;
//
//     return value;
//}
//
