/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     :19 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/
#ifndef GPT_CONFIG_H
#define GPT_CONFIG_H

#define     TIM_Clk_Freq        RCC_APB2_CLK_FRQ
/*
 * RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);*
 * Timer Number             from            to
 * 1                        PA8             PA11
 * 2                        PA0             PA3
 * 3                      PA6 to PA7 + PB0 to PB1
 * 4                        PB6             PB9
 * Pin Mode:GPIO_Mode_AFPP, GPIO_Speed_50MHz
 *
 *
 *
 *
 *
 * if you want timer counts milliseconds and microseconds:*/
/* [Must]  Select Ratio
Options:
     MilliSeconds                   For Microseconds and MilliSeconds
     Seconds                        For MilliSeconds and Seconds
*/
  #define TIM_Ratio     MilleSeconds


#endif
