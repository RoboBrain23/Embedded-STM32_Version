/* Author   : Hind Fouad                                                          */
/* date     : 8 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/
#ifndef ADC_CONFIG_H    
#define ADC_CONFIG_H


/*********************************************
 * two main functions:
 *  ADC_Init(ADC_Num ADCx, const ADC_InitTypeDef *ADC_Cnfg);
 *  preferd sampling time is  ADC_SAMPLETIME_28CYCLES5,
 *  ADC_u16GetSingleConv(ADC_Num ADCx,uint8 Copy_u8Channel,uint8 Copy_u8SamplingTime);
 *   Initializes ADC configuration structure with custom setting for the ease of use
void ADC_vInitStruct(ADC_InitTypeDef *pxADC_Cnfg)
{
     Initialize the ADC_DataAlign member
    pxADC_Cnfg->ADC_DataAlign           = ADC_DATA_ALIGN_RIGHT;
     Initialize the ADC mode member
    pxADC_Cnfg->ADC_Mode                = ADC_MODE_INDEPENDENT;
     Initialize the ADC number of channels member
    pxADC_Cnfg->ADC_NbrOfChannel        = 1;
     Initialize the ADC external trigger member
    pxADC_Cnfg->ADC_ExternalTrigConv    = ADC_EXTERNALTRIGCONV_NONE;
     Initialize the continuous mode member
    pxADC_Cnfg->ADC_ContinuousConvMode  = DISABLE;
     Initialize the scan mode member
    pxADC_Cnfg->ADC_ScanConvMode        = DISABLE;
}
 * */
 /*
 * 1 enable RCC clock for ADC.
 * 2 enable RCC clock for port
 * 3 call Initiation function for ADC.
 * 4 call ADC_u16GetSingleConv(ADC_Num ADCx,uint8 Copy_u8Channel,uint8 Copy_u8SamplingTime);
 * 4 set pins as input mode,analog pins
 *
 *
 *
 *
 *
 */
#endif
