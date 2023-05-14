/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     :19 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/

#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

/*****************Timer number**************/
#define TIM1        0
#define TIM2        1
#define TIM3        2
#define TIM4        3


/*************************TIM Interval modes******************************************** */
#define TIM_SINGLE_INTERVAL_MODE            0
#define TIM_PERIODIC_INTERVAL_MODE          1
/***************typedef******************/

 typedef enum {
     /*count from 0 to auto-reload value*/
     Up_Counting,
     /*count from auto-reload value 0*/
     Down_Counting,
     /*count from 0 to (auto-reload value -1) then count from auto-reload value to 1*/
     Center_Aligned
 }direction_m;

 typedef enum
 {
    TIM_Channel1,TIM_Channel2,TIM_Channel3,TIM_Channel4
 }channel_t;
 typedef enum
 {
    Div_1,
    Div_2,
    Div_3
 }Clk_Div;
 typedef enum
 {
    Disable_ARR_Buffer,
    Enable_ARR_Buffer
 }ARR_Buffer_State;
 typedef enum
 {
     Disable_Interrupt,
    Enable_Interrupts
 }INT_State;
 typedef enum {
  TIMER_CLK_SRC_INTERNAL,
  TIMER_CLK_SRC_EXTERNAL_MODE1,
  TIMER_CLK_SRC_EXTERNAL_MODE2
} timer_clk_src_t;

 typedef enum {
    Active_High,
    Active_Low
 }TIM_Polarity;
 typedef enum
 {
      EdgeAligned_Mode,CenterAligned_Mode
 }state;

 typedef enum
 {
     /*in forced output RISING meaning active and FAllING meaning inactive*/
     RISING, FALLING
 }edge_t;
 typedef enum {
        PWM_11  =   0b110,
        PWM_22  =   0b111
    }PWM_modee;
 typedef struct
{

    uint16 AutoReloadValue;/*value count to it */
    direction_m Tim_Direction;
    state AlignedMode;
    Clk_Div ClockFactor;
    ARR_Buffer_State AutoReloadBuffer;
    INT_State UDI_State;

}TIM_ConfigType;

typedef struct{
    uint16 AutoReloadValue;
    channel_t Channel;
    uint16 Freq;
    PWM_modee Mode;

}PWM_ConfigType;


/***************Functions ProtoTypes***************/
/*Function Description:
 * TIMx Should be (TIM1 ||  TIM2 || TIM3 || TIM4)
 * @TIM_ConfigType
 */
void TIM_Init(uint8 TIMx, TIM_ConfigType *TimConfig);
/*in Config file;
 * if TIM_Ratio     MilleSeconds
 * Ticks type is :1000 for Milliseconds
 *              :1 for microseconds
 * if TIM_Ratio     Seconds
 * Ticks type is :1000 for Seconds
 *              :1 for Milliseconds
 * */
void TIM_SetBusyWait(uint8 TIMx,uint16 Ticks,uint16 TicksTybe);
//void TIM_Delay_us (uint8 TIMx ,uint16 us);
//void TIM_Delay_ms (uint8 TIMx,uint16 ms);

void TIM_SetIntervalSingle  (uint8 TIMx, uint16 Ticks, uint16 Copy_u32TicksTybe, void (*Copy_voidpFuncPtr)(void) );
void TIM_SetIntervalPeriodic(uint8 TIMx,uint16 Ticks ,uint16 TicksTybe , void (* Copy_vpFuncPtr) (void));
uint16 TIM_uGetRemainingTime(uint16 TIMx ,direction_m Direction) ;

void TIM1_UP_IRQHandler (void);
void TIM2_UP_IRQHandler (void);
void TIM3_UP_IRQHandler (void);
void TIM4_UP_IRQHandler (void);

/**********************PWM Functions****************************************/

void PWM_Init( uint8 TIMx,PWM_ConfigType* PWM_Confnig);
/*Function Description :
 * set auto reload value
 */
void TIM_SetPeriod (uint8 TIMx , uint32 Period);
/*
 * First,call PWM_DeInit ,Then, set auto reload value at TIM_SetPeriod
 */
void PWM_voidSetDutyCycle(uint8 TIMx ,channel_t Channel, uint8 Duty);
void PWM_DeInit(uint8 TIMx ,channel_t Channel);
uint16 PWM_GetCounterValue(uint8 TIMx);

#endif

