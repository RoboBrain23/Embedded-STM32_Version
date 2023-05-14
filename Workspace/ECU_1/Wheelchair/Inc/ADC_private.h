/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     : 8 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define NUM_OF_ADC_IN_STM32F103C6 2
#define NOK		0
#define OK		1

#define ADC_START_DELAY_US               1U
/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set     ((uint32)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((uint32)0xFFAFFFFF)

/****************Base Addresses***************************/

#define ADC1_Adress             0x40012400
#define ADC2_Adress             0x40012800

/************************Register Bits***********************/
#define ADC_SQR1_L        			(0x0F << 20)
#define ADC_SQR3          			(0x1F)
#define ADC_JSQR_JL       			(0x03 << 20)
#define ADC_JSQR_JSQ1_Pos 			0
#define DISCEN            			11
#define ADC1EN            			9
#define ADC2EN            			10
#define RCC_CFGR_ADCPRE_0			14
#define RCC_CFGR_ADCPRE_1			15
#define ADC_CR1_SCAN				8
#define ADC_CR2_ADON         		0
#define ADC_CR2_CONT              	1
#define ADC_CR2_CAL            		2
#define ADC_CR2_ALIGN				11
#define ADC_CR2_CONT				1
#define ADC_CR2_SWSTART				22
#define ADC_CR2_RSTCAL				3
#define ADC_CR2_DMA					8
#define ADC_CR2_EXTTRIG				20
#define ADC_SR_SCAN					8
/* ADC flags */
#define ADC_SR_AWD                  0
#define ADC_SR_EOC                  1
#define ADC_SR_JEOC                 2
#define ADC_SR_JSTRT                3
#define ADC_SR_STRT                 4



/******************Registers**************************************/
typedef struct{
    /*status register*/
    volatile uint32 SR;  
    /*control register x*/
    volatile uint32 CR1; 
    volatile uint32 CR2; 
    /*sample time register x */
    volatile uint32 SMPR1; 
    volatile uint32 SMPR2; 
    /*injected channel data offset register x*/
    volatile uint32 JOFR1; 
    volatile uint32 JOFR2;
    volatile uint32 JOFR3;
    volatile uint32 JOFR4;
    /*watch dog high threshold register*/
    volatile uint32 HTR;
    /*watch dog low threshold register*/
    volatile uint32 LTR;
    /*regular sequence register x*/
    volatile uint32 SQR1;
    volatile uint32 SQR2;
    volatile uint32 SQR3;
    /*injected sequence register*/
    volatile uint32 JSQR;
    /*injected data register x*/
    volatile uint32 JDR1;
    volatile uint32 JDR2;
    volatile uint32 JDR3;
    volatile uint32 JDR4;
    /*ADC regular data register*/
    volatile uint32 DR;
}ADC_type;

//Array of pointers to ADC_type structures
 volatile ADC_type * ADC[NUM_OF_ADC_IN_STM32F103C6] =
{
    ((volatile ADC_type *)ADC1_Adress),  //ADC1 Address
    ((volatile ADC_type *)ADC2_Adress)   //ADC2 Address
};


 /**********************Function Prototype**************/
 static void ADC_SetNumberOfChannels(ADC_Num ADCx, uint8 Copy_u8Channels);
 void ADC_ChannelCnfg(ADC_Num ADCx,uint8 Copy_u8ChNum,uint32 Copy_u32Rank,uint8 Copy_u8SampleTime);
 void ADC_Start(ADC_Num ADCx);
 void ADC_PollForConv(ADC_Num ADCx);
 void ADC_EnableDMA(ADC_Num ADCx);
 void ADC_ResetCalibration(ADC_Num ADCx);
 void ADC_StartCalibration(ADC_Num ADCx);
 void ADC_StartConv(ADC_Num ADCx, State Copy_StartState);
uint16 ADC_GetConversionValue(ADC_Num ADCx );
 void ADC_Enable(ADC_Num ADCx);
 void ADC_Disalbe(ADC_Num ADCx);
 static void ADC_SetContinuousMode(ADC_Num ADCx, State Copy_ContState);
 static void ADC_ExternalTrigConvCmd(ADC_Num ADCx, State Copy_xExTriggerState);
 static void ADC_SetDataAlignMode(ADC_Num ADCx, ADC_ALIGN_MODE Copy_u8AlignMode);
 static void ADC_SetScanMode(ADC_Num ADCx, State Copy_State);
 static void ADC_SetMode(ADC_Num ADCx , uint32 Copy_u32Mode);





#endif
