/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : RCC.c                                             */
/* Description : Functions Implementation for RCC module           */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"



/* This function initializes the system clock */
void RCC_initSysClk(void)
{

    #if RCC_CLK_TYPE == RCC_HSE_CRYSTAL
        RCC_CR   = 0x00010000 ; // Enable HSE Clock.
        RCC_CFGR = 0x00000001 ; // HSE selected as system clock.    
    
    #elif RCC_CLK_TYPE == RCC_HSE_RC
        RCC_CR   = 0x00050000 ; // Enable HSE Clock with bypass.
        RCC_CFGR = 0x00000001 ; // HSE selected as system clock.    
    
    #elif RCC_CLK_TYPE == RCC_HSI
        RCC_CR   = 0x00000081 ; // Enable HSI.
        RCC_CFGR = 0x00000000 ; // HSI selected as system clock.    
        
    #elif RCC_CLK_TYPE == RCC_PLL   
        
            RCC_CFGR |= (((uint32)(RCC_PLL_MUL_VAL-2))<<18); // PLL multiplication factor from 2 to 16.
        
        #if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
            CLR_BIT(RCC_CFGR,16) ; // HSI oscillator clock / 2 selected as PLL input clock.
            RCC_CR  = 0x01010000 ; // Enable PLL and HSI clock.
            SET_BIT(RCC_CFGR,1)  ; // select PLL as system clock.
            

        
        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
            SET_BIT(RCC_CFGR,16)  ; // HSE oscillator selected as PLL input clock.
            SET_BIT(RCC_CFGR,17)  ; // HSE clock divided by 2.
            RCC_CR = 0x01010000   ; // Enable PLL and HSE clock.
            SET_BIT(RCC_CFGR,1)   ; // select PLL as system clock.
            
        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
            SET_BIT(RCC_CFGR,16)  ; // HSE oscillator selected as PLL input clock.
            CLR_BIT(RCC_CFGR,17)  ; // HSE clock not divided.
            RCC_CR = 0x01010000   ; // Enable PLL and HSE clock.
            SET_BIT(RCC_CFGR,1)   ; // select PLL as system clock.
        #endif
    
    #else
         #error("Wrong Clock Type")
        
    #endif

            MOD_4BIT(RCC_CFGR, 4 , AHB_PRESCALER) ; /* Set AHB bus prescaler value  */
            MOD_3BIT(RCC_CFGR, 8 , APB1_PRESCALER); /* Set APB1 bus prescaler value */
            MOD_3BIT(RCC_CFGR, 11, APB2_PRESCALER); /* Set APB2 bus prescaler value */
            MOD_2BIT(RCC_CFGR, 14, ADC_PRESCALER) ; /* Set ADC bus prescaler value  */

}

/* Function to enable clock for a specific peripheral on a specific bus */
void RCC_enableClk(uint8 busId, uint8 perId)
{
    /* Check if perId is valid (<= 31) */
    if(perId <= 31)
    {
        /* Enable clock for peripheral based on busId */
        switch(busId)
        {
            case RCC_AHB:  
                SET_BIT(RCC_AHBENR ,perId);     
                break;
            case RCC_APB1: 
                SET_BIT(RCC_APB1ENR,perId);     
                break;      
            case RCC_APB2: 
                SET_BIT(RCC_APB2ENR,perId);     
                break;  
            default:        
                /* Return Error */                      
                break; //May cause error if default case was not implemented (compiler dependence).
        }
    }
    else 
    {
        /* Return Error*/
    }
}

/* Function to disable clock for a specific peripheral on a specific bus */
void RCC_disableClk(uint8 busId, uint8 perId)
{
    /* Check if perId is valid (<= 31) */
    if(perId <= 31)
    {
        /* Disable clock for peripheral based on busId */
        switch(busId)
        {
            case RCC_AHB:  
                CLR_BIT(RCC_AHBENR ,perId);     
                break;
            case RCC_APB1: 
                CLR_BIT(RCC_APB1ENR,perId);     
                break;      
            case RCC_APB2: 
                CLR_BIT(RCC_APB2ENR,perId);     
                break;  
            default:        
                /* Return Error */                      
                break; //May cause error if default case was not implemented (compiler dependence).
        }
    }
    else 
    {
        /* Return Error*/
    }
}


