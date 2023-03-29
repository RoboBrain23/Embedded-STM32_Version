/**********************************************************************************/
/* Author	: Hind Fouad                                                          */
/* date		: 8 Mar 2022                                                          */
/* Version	: V01                                                                 */
/**********************************************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_MAX_VALUE 			    4096  // 4096 pulses	
#define ADC_REF_VOLT_VALUE			3.3   // 3.3 Volt

#define 	Enable					1		
#define 	Disable					0
 

typedef enum {
	Conversion_1,
	Conversion_2,
	Conversion_3,
	Conversion_4,	
	Conversion_5,	
	Conversion_6,	
	Conversion_7,	
	Conversion_8,
	Conversion_9,			
	Conversion_10,	
	Conversion_11,	
	Conversion_12,		
	Conversion_13,
	Conversion_14,	
	Conversion_15,	
	Conversion_16,		
}Convertion_Number;



typedef enum {
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
	ADC_CHANNEL_9,
	ADC_CHANNEL_10,
	ADC_CHANNEL_11,
	ADC_CHANNEL_12,
	ADC_CHANNEL_13,
	ADC_CHANNEL_14,
	ADC_CHANNEL_15,
	ADC_CHANNEL_16,
	ADC_CHANNEL_17,
	ADC_CHANNEL_18,
   
} ADC_channel_t;


typedef enum 
{
 ADC_Group_Regular,
 ADC_Group_Injected
}ADC_Group_Type;

typedef enum
{
 ADC_MODE_SINGLE ,
 ADC_MODE_CONTINUOUS ,
 ADC_MODE_DISCONTINUOUS ,
}Mode_Type;


/****************prototypes******************/
/*Function Description  :
enable ADC

*/
void ADC_init(ADC_type * ADCx);


/*Function Description  :
set conversion number of regular group

*/
void ADC_regulargroupInit(ADC_type * ADCx,Convertion_Number Convertion_x);


/*Function Description  :
set conversion number of injected group

*/
void ADC_injectedgroupInit(ADC_type * ADCx ,Convertion_Number);


/*Function Description  :
select channel
which takes:
ADCx -> ADC type (ADC1 or ADC2)
channel -> channel number
group type -> regular or injected 

*/
void ADC_setChannel(ADC_type* ADCx, ADC_channel_t channel, ADC_Group_Type group_type);


/*Function Description  :
select mode:
single -->> In Single conversion mode the ADC does one conversion
continuous mode -->>
In continuous conversion mode ADC starts another conversion as soon as
 it finishes one.
discontinuous mode -->>It can be used to
convert a short sequence of n conversions (n <=8)
*/
void Adc_setMode(uint32_t mode);


/*Function Description  :
read value 

*/
uint16 ADC_typeRead(ADC_type* ADCx ,ADC_channel_t Channel );


#endif