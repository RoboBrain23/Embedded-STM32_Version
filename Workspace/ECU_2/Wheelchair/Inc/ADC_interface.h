/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     : 8 Mar 2022                                                          */
/* Version  : V02                                                                 */
/**********************************************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_MAX_VALUE               4096  // 4096 pulses    
#define ADC_REF_VOLT_VALUE          3.3   // 3.3 Volt


/*
#define     Enable                  1       
#define     Disable                 0
*/
typedef unsigned char	   		Error_Status;
typedef unsigned char	   		Flag_Status;
typedef unsigned char			State;
typedef unsigned char										ADC_State_t;
#define ADC_DISBLE											(0)
#define ADC_ENABLE											(1)
/*******************************************************************************/
typedef enum
{
     ADC1, ADC2,ADC3
}ADC_Num;
/* ADC channels */
typedef enum{

	 ADC_CHANNEL_0  = ((uint8)0x00),
	 ADC_CHANNEL_1  ,
	 ADC_CHANNEL_2  ,
	 ADC_CHANNEL_3  ,
	 ADC_CHANNEL_4  ,
	 ADC_CHANNEL_5  ,
	 ADC_CHANNEL_6  ,
	 ADC_CHANNEL_7  ,
	 ADC_CHANNEL_8  ,
	 ADC_CHANNEL_9  ,
	 ADC_CHANNEL_10 ,
     ADC_CHANNEL_11 ,
	 ADC_CHANNEL_12 ,
	 ADC_CHANNEL_13 ,
	 ADC_CHANNEL_14 ,
	 ADC_CHANNEL_15 ,
	 ADC_CHANNEL_16 ,
	 ADC_CHANNEL_17
}ADC_channel_t;
/*******************************************/
/*ADC ALIGN MODE*/
typedef enum {
	ADC_DATA_ALIGN_RIGHT,ADC_DATA_ALIGN_LEFT
}ADC_ALIGN_MODE;
/************************************************************************************************************* */
/* ADC SAMPLING TIME */
typedef enum {
	ADC_SAMPLETIME_1CYCLES5 =  ((uint8)0x00),
	ADC_SAMPLETIME_7CYCLES5,
	 ADC_SAMPLETIME_13CYCLES5 ,
	 ADC_SAMPLETIME_28CYCLES5,
	 ADC_SAMPLETIME_41CYCLES5,
	 ADC_SAMPLETIME_55CYCLES5,
	 ADC_SAMPLETIME_71CYCLES5,
	 ADC_SAMPLETIME_239CYCLES5
}ADC_Sampling_Time;
/*****************************************************************************/
/* ADC Regular ranks */
#define ADC_REGULAR_RANK_1                 			0x00000001U
#define ADC_REGULAR_RANK_2         			        0x00000002U
#define ADC_REGULAR_RANK_3                 			0x00000003U
#define ADC_REGULAR_RANK_4                 			0x00000004U
#define ADC_REGULAR_RANK_5                 			0x00000005U
#define ADC_REGULAR_RANK_6                 			0x00000006U
#define ADC_REGULAR_RANK_7                			0x00000007U
#define ADC_REGULAR_RANK_8                			0x00000008U
#define ADC_REGULAR_RANK_9                 			0x00000009U
#define ADC_REGULAR_RANK_10                			0x0000000AU
#define ADC_REGULAR_RANK_11                			0x0000000BU
#define ADC_REGULAR_RANK_12               			0x0000000CU
#define ADC_REGULAR_RANK_13                			0x0000000DU
#define ADC_REGULAR_RANK_14                			0x0000000EU
#define ADC_REGULAR_RANK_15                			0x0000000FU
#define ADC_REGULAR_RANK_16            			    0x00000010U
/******************************************************************************/
/* ADC modes */
#define ADC_MODE_INDEPENDENT                       ((uint32)0x00000000)
#define ADC_MODE_REGINJECSIMULT                    ((uint32)0x00010000)
#define ADC_MODE_REGSIMULT_ALTERTRIG               ((uint32)0x00020000)
#define ADC_MODE_INJECSIMULT_FASTINTERL            ((uint32)0x00030000)
#define ADC_MODE_INJECSIMULT_SLOWINTERL            ((uint32)0x00040000)
#define ADC_MODE_INJECSIMULT                       ((uint32)0x00050000)
#define ADC_MODE_REGSIMULT                         ((uint32)0x00060000)
#define ADC_MODE_FASTINTERL                        ((uint32)0x00070000)
#define ADC_MODE_SLOWINTERL                        ((uint32)0x00080000)
#define ADC_MODE_ALTERTRIG                         ((uint32)0x00090000)

/************************************************************************************************************* */

/* ADC external triggers for regular channels conversion */
#define ADC_EXTERNALTRIGCONV_T1_CC1                ((uint32)0x00000000)
#define ADC_EXTERNALTRIGCONV_T1_CC2                ((uint32)0x00020000)
#define ADC_EXTERNALTRIGCONV_T2_CC2                ((uint32)0x00060000)
#define ADC_EXTERNALTRIGCONV_T3_TRGO               ((uint32)0x00080000)
#define ADC_EXTERNALTRIGCONV_T4_CC4                ((uint32)0x000A0000)
#define ADC_EXTERNALTRIGCONV_EXT_IT11_TIM8_TRGO    ((uint32)0x000C0000)
/*!< For ADC1, ADC2 AND ADC3 */
#define ADC_EXTERNALTRIGCONV_T1_CC3                ((uint32)0x00040000)
#define ADC_EXTERNALTRIGCONV_NONE                  ((uint32)0x000E0000)
/*!< For ADC3 only */
#define ADC_EXTERNALTRIGCONV_T3_CC1                ((uint32)0x00000000)
#define ADC_EXTERNALTRIGCONV_T2_CC3                ((uint32)0x00020000)
#define ADC_EXTERNALTRIGCONV_T8_CC1                ((uint32)0x00060000)
#define ADC_EXTERNALTRIGCONV_T8_TRGO               ((uint32)0x00080000)
#define ADC_EXTERNALTRIGCONV_T5_CC1                ((uint32)0x000A0000)
#define ADC_EXTERNALTRIGCONV_T5_CC3                ((uint32)0x000C0000)

/************************************************************************************************************* */
typedef struct
{
	/*select independent or dual mode*/
	uint32 ADC_Mode;

	/*Enable for multi_channel , DISABLE for single channels*/
	State ADC_ScanConvMode;

	/*Enable for Continuous , DISABLE for single mode*/
	State ADC_ContinuousConvMode;

	/* select external trigger*/
	uint32 ADC_ExternalTrigConv;

	/*Right or left*/
	uint32 ADC_DataAlign;

	/*Numbers of ADC Channels*/
	uint8 ADC_NbrOfChannel;
}ADC_InitTypeDef;


///****************Functions Prototypes******************/
/*Function Description  :
Initiate ADC configurations
*/
void ADC_Init(ADC_Num ADCx, const ADC_InitTypeDef *ADC_Cnfg);

/*Function Description  :
 * read value
 * ADCx :ADC Number
 * Copy_u8Channel :number of channel
 *
 */
uint16 ADC_GetValue(ADC_Num ADCx,ADC_channel_t Copy_u8Channel,uint8 Copy_u8SamplingTime);




#endif
