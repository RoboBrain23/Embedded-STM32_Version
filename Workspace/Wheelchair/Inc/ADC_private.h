/**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     : 8 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define NUM_OF_ADC_IN_STM32F103C6 2


/****************Base Addresses***************************/

#define ADC1_Adress             0x40012400
#define ADC2_Adress             0x40012800

/************************Register Bits***********************/
#define ADC_SQR1_L        (0x0F << 20)
#define ADC_SQR3          (0x1F)
#define ADC_JSQR_JL       (0x03 << 20)
#define ADC_JSQR_JSQ1_Pos (0)
#define ADC_SR_EOC        (0x01 << 1)
#define ADON              (0)
#define CAL               (2)
#define CONT              (1)
#define DISCEN            (11)
#define ADC1EN            (9)
#define ADC2EN            (10)


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

#endif
