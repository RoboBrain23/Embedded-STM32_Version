/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     :19 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/
#ifndef GPT_PRIVATE_H
#define GPT_PRIVATE_H


#define NNUMBER_OF_TIM_IN_STM32F103C6		4
 /***********************Timx Addresses************************/
 
 #define TIM1_BaseAddress           0x40012C00
 #define TIM2_BaseAddress           0x40000000
 #define TIM3_BaseAddress           0x40000400
 #define TIM4_BaseAddress           0x40000800
 #define TIM5_BaseAddress           0x40000C00
 #define TIM6_BaseAddress           0x40001000
 #define TIM7_BaseAddress           0x40001400
 #define TIM8_BaseAddress           0x40013400
 #define TIM9_BaseAddress           0x40014C00
 
 
 /**********************TIMx Register Bits***********************/

#define     TIM_CR1_CEN             0
#define     TIM_CR1_DIR             4
#define 	TIM_CR1_URS				2
#define 	TIM_CR1_ARPE			7
#define     TIM_DIER_UIE    		0
#define     ARPE            		7
#define     TIM_CCER_CC1P            		1
#define     TIM_CCER_CC2P            		5
#define     TIM_CCER_CC3P            		9
#define     TIM_CCER_CC4P            		13
#define     TIM_CCER_CC1E            		0
#define     TIM_CCER_CC2E            		4
#define     TIM_CCER_CC3E            		8
#define     TIM_CCER_CC4E            		12
#define     TIM_CCMR1_OC1PE         3
#define     TIM_CCMR1_OC2PE         11
#define     TIM_CCMR2_OC3PE         3
#define     TIM_CCMR2_OC4PE         11
#define     IC1F            		4
#define     IC2F            		12
#define     IC3F            		4
#define     IC4F            		12
#define     TIM_DIER_UIE            0
#define     TIM_SR_UIF             		0
#define     TIM1EN          		11
#define     TIM8EN          		13
#define 	TIM_EGR_CC1G			1
#define 	TIM_EGR_CC2G			2
#define 	TIM_EGR_CC3G			3
#define 	TIM_EGR_CC4G			4
#define 	TIM_BDTR_MOE			15
#define 	TIM_EGR_UG				0
#define 	TIM_DIER_CC1IE			1
#define 	TIM_DIER_CC2IE			2
#define 	TIM_DIER_CC3IE			3
#define 	TIM_DIER_CC4IE			4


 /*******************************Registers ***********************/
typedef struct
{
     /*control register */
     volatile uint16 CR1;
     uint16  RESERVED0;
     volatile uint16 CR2;
     uint16  RESERVED1;
     /*slave mode control register*/
     volatile uint16 SMCR;
     uint16  RESERVED2;
     /*DMA/Interrupt enable register*/
     volatile uint16 DIER;
     uint16  RESERVED3;
     /*status register*/
     volatile uint16 SR;
     uint16  RESERVED4;
     /*event generation register*/
     volatile uint16 EGR;
     uint16  RESERVED5;
     /*capture/compare mode register x*/
     volatile uint16 CCMR1;
     uint16  RESERVED6;
     volatile uint16 CCMR2;
     uint16  RESERVED7;
     /*capture/compare enable register*/
     volatile uint16 CCER;
     uint16  RESERVED8;
     /*counter*/
     volatile uint16 CNT;
     uint16  RESERVED9;
     /*pre scaler*/
     volatile uint16 PSC;
     uint16  RESERVED10;
     /*auto-reload register*/
     volatile uint16 ARR;
     uint16  RESERVED11;
     /*advanced for TIM1 & TIM8
     *repetition counter
     */
     volatile uint16 RCR ;
     uint16  RESERVED12;
     /*capture/compare register x*/
     volatile uint16 CCR1;
     uint16  RESERVED13;
     volatile uint16 CCR2;
     uint16  RESERVED14;
     volatile uint16 CCR3;
     uint16  RESERVED15;
     volatile uint16 CCR4;
     uint16  RESERVED16;
     /*advanced for TIM1 & TIM8
     *break and dead-time register
     */
     volatile uint16 BDTR;
     uint16  RESERVED17;
     /*DMA control register*/
     volatile uint16 DCR;
     uint16  RESERVED18;
     /*address for full transfer*/
     volatile uint16 DMAR;
     uint16  RESERVED19;

}TIM_t;
volatile TIM_t * TIM[NNUMBER_OF_TIM_IN_STM32F103C6] =

{
   ((volatile TIM_t *)TIM1_BaseAddress),  //Timer1 Address
   ((volatile TIM_t *)TIM2_BaseAddress),   //Timer2 Address
   ((volatile TIM_t *)TIM3_BaseAddress) ,  //Timer3 Address
   ((volatile TIM_t *)TIM4_BaseAddress)   //Timer4 Address
};
/**********************private functions prototype***************/
/*Function description:
This function stops the timer
*/
void TIM_Disable(uint8 TIMx);
/*Function description:
This function starts the timer
*/
void TIM_Enable(uint8 TIMx);
/*Function description:
This function set timer pre scaler
*/
void TIM_SetPrescaler(uint8 TIMx , uint16 Prescaler);
/*
Function description:
This function set timer auto-reload value
*/

/*Function description:
This function set timer clock source ( Internal | External mode1 | External mode 2)
*/
void TIM_voidSetClkDiv(uint8 TIMx,Clk_Div Copy_ClockDiv);
/*
Function description:
This function select counter mode ( UpCounting | DownCounting | centerAligned )
*/
void TIM_Direction(uint8 TIMx,direction_m Copy_CounterMode);


 /*Function Description
this function is used to enable or disable the update interrupt of a timer.
*/
void TIM_SetARR_Buffer(uint8 TIMx,ARR_Buffer_State AutoReloadBuffer);
void TIM_SetInterrupt(uint8 TIMx,INT_State IntState);
void PWM_SetAlignmentMode(uint8 TIMx, state mode);
/*********************PWM Functions ProtoTypes***************/
void PWM_SetChannel(uint8 TIMx,channel_t Channel,PWM_modee Copy_u32Mod);



#endif
