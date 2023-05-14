 /**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     :19 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/

/**************includes***************/
#include "std_types.h"
#include "common_macros.h"
#include "RCC_interface.h"
#include "GPT_interface.h"
#include "GPT_private.h"
#include "GPT_config.h"
#include "STM32F103C6.h"

static volatile float32 microSecToTicksRatio = 0;
/* Variable to define interval mode of Timer*/
static volatile uint8 TIM1_u8IntervalMode;
static volatile uint8 TIM2_u8IntervalMode;
static volatile uint8 TIM3_u8IntervalMode;
static volatile uint8 TIM4_u8IntervalMode;

/* Local macros to set and get Interval mode for timer interrupt*/
#define TIM1_SET_INTERVAL_MODE(MODE)                          TIM1_u8IntervalMode = MODE
#define TIM1_GET_INTERVAL_MODE()                               (TIM1_u8IntervalMode & 1)

#define TIM2_SET_INTERVAL_MODE(MODE)                          TIM2_u8IntervalMode = MODE
#define TIM2_GET_INTERVAL_MODE()                               (TIM2_u8IntervalMode & 1)

#define TIM3_SET_INTERVAL_MODE(MODE)                          TIM3_u8IntervalMode = MODE
#define TIM3_GET_INTERVAL_MODE()                               (TIM3_u8IntervalMode & 1)

#define TIM4_SET_INTERVAL_MODE(MODE)                          TIM4_u8IntervalMode = MODE
#define TIM4_GET_INTERVAL_MODE()                               (TIM4_u8IntervalMode & 1)

static void (*TIM1_CallBack)(void);
static void (*TIM2_CallBack)(void);
static void (*TIM3_CallBack)(void);
static void (*TIM4_CallBack)(void);



/************************************************************************************************************* */
void TIM_Init(uint8 TIMx, TIM_ConfigType *TimConfig) {
    TIM_SetPeriod(TIMx,TimConfig-> AutoReloadValue);
#if TIM_Ratio == MilleSeconds

    if (TIMx==TIM1){
        uint16 Prescaler =(uint16)(TIM_Clk_Freq /1000000)-1;

        TIM_SetPrescaler(TIMx,Prescaler) ;
    }else if  (TIMx==TIM2 || TIMx==TIM3||TIMx==TIM4){
        uint16 Prescaler =(uint16)(TIM_Clk_Freq /1000000)-1;

        TIM_SetPrescaler(TIMx, Prescaler);
    }
#elif TIM_Ratio == Seconds
    if (TIMx==TIM1){
            uint16 Prescaler =(uint16)(TIM_Clk_Freq /1000)-1;

            TIM_SetPrescaler(TIMx,Prescaler) ;
        }else if  (TIMx==TIM2 || TIMx==TIM3||TIMx==TIM4){
            uint16 Prescaler =(uint16)(TIM_Clk_Freq/1000)-1;

            TIM_SetPrescaler(TIMx, Prescaler);
        }

#endif
    TIM_SetARR_Buffer(TIMx,TimConfig->AutoReloadBuffer);
    //PWM_SetAlignmentMode(TIMx,TimConfig->AlignedMode);
    TIM_Direction(TIMx, TimConfig->Tim_Direction);

    TIM_voidSetClkDiv(TIMx,TimConfig->ClockFactor );
    TIM_SetInterrupt(TIMx,TimConfig->UDI_State);

    //SET_BIT(TIM[TIMx]->EGR, TIM_EGR_UG);
    TIM_Enable(TIMx);
    ///while (!(TIM[TIMx]->SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated


}
void TIM_Enable(uint8 TIMx){
    SET_BIT(TIM[TIMx]->CR1,TIM_CR1_CEN );
}
void TIM_Direction(uint8 TIMx,direction_m Copy_CounterMode){
    switch (Copy_CounterMode){
  case Up_Counting:
  /*set direction of counter: up */
      CLR_BIT(TIM[TIMx] -> CR1 ,TIM_CR1_DIR );

      break;
  case Down_Counting :
    /*set direction of counter: up */
      SET_BIT (TIM[TIMx] -> CR1 ,TIM_CR1_DIR);

      break;
  case Center_Aligned:
      CLR_BIT ( TIM[TIMx] -> CR1 , TIM_CR1_DIR);
      SET_BIT (TIM[TIMx] -> CR1 ,6);
      CLR_BIT (TIM[TIMx] -> CR1 ,5);
     break;
      default:
      break;
}
}
void TIM_SetPrescaler(uint8 TIMx , uint16 Prescaler){
      /*Set the prescalar value in PSC register*/
    TIM[TIMx] ->PSC =  Prescaler;

}
void TIM_SetPeriod (uint8 TIMx , uint32 Period){
    /* Set the autoreload value value in ARP register*/
    TIM[TIMx]->ARR = Period;
}
void TIM_voidSetClkDiv(uint8 TIMx,Clk_Div Copy_ClockDiv)
{
    switch(Copy_ClockDiv)
    {
    case Div_1:
        CLR_BIT(TIM[TIMx]->CR1,8);
        CLR_BIT(TIM[TIMx]->CR1,9);
        break;

    case Div_2:
        SET_BIT(TIM[TIMx]->CR1,8);
        CLR_BIT(TIM[TIMx]->CR1,9);
        break;

    case Div_3:
        CLR_BIT(TIM[TIMx]->CR1,8);
        SET_BIT(TIM[TIMx]->CR1,9);
        break;

    default:
        break;
    }
}
void TIM_SetARR_Buffer(uint8 TIMx,ARR_Buffer_State AutoReloadBuffer)
{
    switch(AutoReloadBuffer)
    {
    case Disable_ARR_Buffer:
        CLR_BIT(TIM[TIMx]->CR1,TIM_CR1_ARPE);
        break;
    case Enable_ARR_Buffer:
        SET_BIT(TIM[TIMx]->CR1,TIM_CR1_ARPE);
        break;

    }
}
void TIM_SetInterrupt(uint8 TIMx,INT_State IntState)
{
    switch(IntState)
    {
        case Disable_Interrupt:
            CLR_BIT(TIM[TIMx]->DIER,TIM_DIER_UIE);
            break;
        case Enable_Interrupts:
            SET_BIT(TIM[TIMx]->DIER,TIM_DIER_UIE);
            break;
    }
}
void TIM_Disable(uint8 TIMx){

    CLR_BIT(TIM[TIMx] ->CR1 ,TIM_CR1_CEN);
}
//void TIM_Delay_us (uint8 TIMx ,uint16 us)
//{
//
//  TIM[TIMx]->CNT = 0;
//  while (TIM[TIMx]->CNT < us);
//}
//
//void TIM_Delay_ms (uint8 TIMx,uint16 ms)
//{
//  for (uint16 i=0; i<ms; i++)
//  {
//      TIM_Delay_us (TIMx,1000); // delay of 1 ms
//  }
//}
void TIM_SetBusyWait(uint8 TIMx, uint16 Ticks, uint16 TicksTybe) {
    /*Assign ticks to load register*/

    TIM[TIMx]->ARR = (uint16) (Ticks * TicksTybe);
    CLR_BIT(TIM[TIMx]->DIER, 0);
    /*Start timer*/
    SET_BIT(TIM[TIMx]->CR1, 0);
    /*Wait until CNT is equal to comapre value */
    while (TIM[TIMx]->CNT != TIM[TIMx]->ARR)
        ;
    /*Stop timer*/
    TIM[TIMx]->CNT = 0;
    CLR_BIT(TIM[TIMx]->CR1, 0);
    /*Clear Timer registers*/
    TIM[TIMx]->ARR = 0;

}
void TIM_SetIntervalSingle(uint8 TIMx, uint16 Ticks, uint16 TicksTybe,
        void (*Copy_voidpFuncPtr)(void)) {
    /*Stop timer*/
    TIM_Disable(TIMx);
    /*Clear Timer registers*/
    TIM[TIMx]->ARR = 0;

    TIM[TIMx]->ARR = (uint16) (Ticks * TicksTybe);
    /* Assign callBack function */
    if (TIMx == TIM1) {

        TIM1_CallBack = Copy_voidpFuncPtr;
        TIM1_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM2) {

        TIM2_CallBack = Copy_voidpFuncPtr;
        TIM2_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM3) {

        TIM3_CallBack = Copy_voidpFuncPtr;
        TIM3_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM4) {

        TIM4_CallBack = Copy_voidpFuncPtr;
        TIM4_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    }

    /*Enable Timer interrupt*/
    SET_BIT(TIM[TIMx]->DIER, TIM_DIER_UIE);

    /*Start timer*/
    TIM_Enable(TIMx);
}
void TIM_SetIntervalPeriodic(uint8 TIMx, uint16 Ticks, uint16 TicksTybe,
        void (*Copy_vpFuncPtr)(void)) {
    /*Assign ticks to load register*/
    TIM[TIMx]->ARR = (uint16) (Ticks * TicksTybe);
    /*Assign the function to the callback function */
    if (TIM[TIMx] == TIM[0]) {
        TIM1_CallBack = Copy_vpFuncPtr;
        TIM1_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);/* Set Mode to periodic */
        CLR_BIT(TIM[0]->SR, TIM_SR_UIF);
    } else if (TIM[TIMx] == TIM[1]) {
        TIM2_CallBack = Copy_vpFuncPtr;
        TIM2_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);/* Set Mode to periodic */
        CLR_BIT(TIM[1]->SR, TIM_SR_UIF);
    } else if (TIM[TIMx] == TIM[2]) {
        TIM3_CallBack = Copy_vpFuncPtr;
        TIM3_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
        CLR_BIT(TIM[2]->SR, TIM_SR_UIF);
    } else if (TIM[TIMx] == TIM[3]) {
        TIM4_CallBack = Copy_vpFuncPtr;
        TIM4_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
        CLR_BIT(TIM[3]->SR, TIM_SR_UIF);
    }

    /*Enable Timer interrupt*/
    SET_BIT(TIM[TIMx]->DIER, TIM_DIER_UIE);
    /*Start the counter*/
    SET_BIT(TIM[TIMx]->CR1, TIM_CR1_CEN);
}
uint16 TIM_GetRemainingTime(uint16 TIMx,direction_m Direction) {
    static volatile uint16 RemainingTime = 0;

    if (Direction == Up_Counting) {
        RemainingTime = (uint16) ((TIM[TIMx]->ARR) - (TIM[TIMx]->CNT));
    } else if (Direction == Down_Counting) {
        RemainingTime = (uint16) (TIM[TIMx]->CNT);
    }

    return (RemainingTime);
}


void TIM1_UP_IRQHandler (void)
{
    if(TIM1_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLR_BIT(TIM[0] -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLR_BIT(TIM[0] ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM[1]->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM1_CallBack();

    /*Clear interrupt flag*/
    CLR_BIT(TIM[1]->SR,TIM_SR_UIF);
}

void TIM2_UP_IRQHandler (void)
{
    if(TIM2_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLR_BIT(TIM[1] -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLR_BIT(TIM[1] ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM[2]->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM2_CallBack();

    /*Clear interrupt flag*/
    CLR_BIT(TIM[1]->SR,TIM_SR_UIF);
}
void TIM3_UP_IRQHandler (void)
{
    if(TIM3_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLR_BIT(TIM[2] -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLR_BIT(TIM[2] ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM[2]->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM3_CallBack();

    /*Clear interrupt flag*/
    CLR_BIT(TIM[2]->SR,TIM_SR_UIF);
}
void TIM4_UP_IRQHandler (void)
{
    if(TIM4_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLR_BIT(TIM[3] -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLR_BIT(TIM[3] ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM[3]->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM4_CallBack();

    /*Clear interrupt flag*/
    CLR_BIT(TIM[3]->SR,TIM_SR_UIF);
}



/**********************PWM Functions****************************************/
void PWM_Init( uint8 TIMx,PWM_ConfigType* PWM_Config){
    /* turn on channel*/
    PWM_SetChannel( TIMx,PWM_Config->Channel,PWM_Config->Mode);
    /*calculate prescaler*/
    uint32 Counter =((PWM_Config->Freq)*(PWM_Config->AutoReloadValue));
    uint16 Prescaler = TIM_Clk_Freq/Counter;
    TIM_SetPrescaler(TIMx,Prescaler);
    /*set ARR value*/
    TIM_SetPeriod(TIMx,PWM_Config->AutoReloadValue);
    //CLR_BIT(TIM[TIMx]->CR1,8);
    //CLR_BIT(TIM[TIMx]->CR1,9);
    /*turn on timer*/
    SET_BIT(TIM[TIMx]->CR1,TIM_CR1_ARPE);
    SET_BIT(TIM[TIMx]->CR1,TIM_CR1_CEN);
    SET_BIT(TIM[TIMx]->EGR,TIM_EGR_UG);

    //PWM_SetAlignmentMode(TIMx,PWM_Config->EdgeAlignmentMode);
    //PWM_SetOutputCompareMode(TIMx, PWM_Config->Channel, PWM_Config->EdgeMode);
    //PWM_SetChannelPolarity(TIMx, PWM_Config->Channel, PWM_Config-> ChannelPolarity);
    //PWM_SetDutyCycle(TIMx,PWM_Config->Channel, PWM_Config->DutyCyclePrecent,PWM_Config->AutoReloadValue);
}
void PWM_SetAlignmentMode(uint8 TIMx, state mode){
    if(mode == EdgeAligned_Mode ) {
        CLR_BIT(TIM[TIMx]->CR1,5);
        CLR_BIT(TIM[TIMx]->CR1,6);
    }
    else if(mode == CenterAligned_Mode) {
        SET_BIT(TIM[TIMx]->CR1,5);
        CLR_BIT(TIM[TIMx]->CR1,6);

}
}
void PWM_SetChannel(uint8 TIMx,channel_t Channel,PWM_modee mode){

    switch(Channel){
    case TIM_Channel1:
        TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 & ~(0b1111<<4) ;  //clearing the previous  PWM mode
        TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 | (mode <<4);  //setting the PWM mode
        SET_BIT(TIM[TIMx]->CCMR1,TIM_CCMR1_OC1PE);   //preload enable
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC1E );      //capture compare output enable for channel 1
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC1P);
        break;
    case TIM_Channel2:
        TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 & ~(0b1111<<12) ;
        TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 | (mode <<12);
        SET_BIT(TIM[TIMx]->CCMR1,TIM_CCMR1_OC2PE);
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC2P);
        break;
    case TIM_Channel3:
        TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 & ~(0b1111<<4) ;
        TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 | (mode <<4);
        SET_BIT(TIM[TIMx]->CCMR2,TIM_CCMR2_OC3PE);
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC3E);
        SET_BIT(TIM[TIMx]->CCER ,  TIM_CCER_CC3P);
        break;
    case TIM_Channel4:
        TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 & ~(0b1111<<12) ;
        TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 | (mode <<12);
        SET_BIT(TIM[TIMx]->CCMR2,TIM_CCMR2_OC4PE);
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC4E);
        SET_BIT(TIM[TIMx]->CCER , TIM_CCER_CC4P );
        break;

    }

}

void PWM_voidSetDutyCycle(uint8 TIMx ,channel_t Channel, uint8 Duty)
{
    uint16 Pulse= (TIM[TIMx]->ARR) * Duty/100.0;
    switch(Channel){
    case TIM_Channel1:
        TIM[TIMx]->CCR1=Pulse;
        break;
    case TIM_Channel2:
        TIM[TIMx]->CCR2=Pulse;
        break;
    case TIM_Channel3:
        TIM[TIMx]->CCR3=Pulse;
        break;
    case TIM_Channel4:
        TIM[TIMx]->CCR4=Pulse;
        break;

        }
}


void PWM_DeInit(uint8 TIMx ,channel_t Channel){
        switch(Channel){
        case TIM_Channel1:
            TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 & ~(0b1111<<4) ;
            CLR_BIT(TIM[TIMx]->CCMR1,TIM_CCMR1_OC1PE);
            CLR_BIT(TIM[TIMx]->CCER , TIM_CCER_CC1E);
            break;
        case TIM_Channel2:
            TIM[TIMx]->CCMR1 = TIM[TIMx]->CCMR1 & ~(0b1111<<12) ;
            CLR_BIT(TIM[TIMx]->CCMR1,TIM_CCMR1_OC2PE);
            CLR_BIT(TIM[TIMx]->CCER , TIM_CCER_CC2E);
            break;
        case TIM_Channel3:
            TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 & ~(0b1111<<4) ;
            CLR_BIT(TIM[TIMx]->CCMR2,TIM_CCMR2_OC3PE);
            CLR_BIT(TIM[TIMx]->CCER , TIM_CCER_CC3E);
            break;
        case TIM_Channel4:
            TIM[TIMx]->CCMR2 = TIM[TIMx]->CCMR2 & ~(0b1111<<12) ;
            CLR_BIT(TIM[TIMx]->CCMR2,TIM_CCMR2_OC4PE);
            CLR_BIT(TIM[TIMx]->CCER , TIM_CCER_CC4E);
            break;

        }
}
uint16 PWM_GetCounterValue(uint8 TIMx){
    uint16 CounterValue= TIM[TIMx]->CNT;
    return CounterValue;
}
