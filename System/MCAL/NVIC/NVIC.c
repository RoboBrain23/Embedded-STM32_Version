/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : NVIC.c                                            */
/* Description : Functions Implementation for NVIC module          */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"



// This function enables the interrupt specified by IntNum parameter
void NVIC_enableInterrupt (uint8 IntNum)
{
    // Check if IntNum is between 0 and 31 (inclusive)
    if ( IntNum <= 31 )
    {
        // Set the corresponding bit in NVIC_ISER0 register to enable the interrupt
        NVIC_ISER0 = ( 1 << IntNum );
    }
    // Check if IntNum is between 32 and 63 (inclusive)
    else if ( IntNum <= 63 )
    {
        // Subtract 32 from IntNum to get the correct bit position in NVIC_ISER1 register
        IntNum -= 32 ;
        // Set the corresponding bit in NVIC_ISER1 register to enable the interrupt
        NVIC_ISER1 = ( 1 << IntNum );
    }
    else 
    {
        // If IntNum is out of range, return an error
        /*Return Error*/
    }
}

// This function disables the interrupt specified by IntNum parameter
void NVIC_disableInterrupt (uint8 IntNum)
{
    // Check if IntNum is between 0 and 31 (inclusive)
    if ( IntNum <= 31 )
    {
        // Set the corresponding bit in NVIC_ICER0 register to disable the interrupt
        NVIC_ICER0 = ( 1 << IntNum );
    }
    // Check if IntNum is between 32 and 59 (inclusive)
    else if ( IntNum <= 59 )
    {
        // Subtract 32 from IntNum to get the correct bit position in NVIC_ICER1 register
        IntNum -= 32 ;
        // Set the corresponding bit in NVIC_ICER1 register to disable the interrupt
        NVIC_ICER1 = ( 1 << IntNum );
    }
    else 
    {
        // If IntNum is out of range, return an error
        /*Return Error*/
    }
}

// This function sets the pending flag for the interrupt specified by IntNum parameter
void NVIC_setPendingFlag  (uint8 IntNum)
{
    // Check if IntNum is between 0 and 31 (inclusive)
    if ( IntNum <= 31 )
    {
        // Set the corresponding bit in NVIC_ISPR0 register to set the pending flag for the interrupt
        NVIC_ISPR0 = ( 1 << IntNum );
    }
    // Check if IntNum is between 32 and 59 (inclusive)
    else if ( IntNum <= 59 )
    {
        // Subtract 32 from IntNum to get the correct bit position in NVIC_ISPR1 register
        IntNum -= 32 ;
        // Set the corresponding bit in NVIC_ISPR1 register to set the pending flag for the interrupt
        NVIC_ISPR1 = ( 1 << IntNum );
    }
    else 
    {
        // If IntNum is out of range, return an error
        /*Return Error*/
    }
}


// This function clears the pending flag for the given interrupt number
void NVIC_clearPendingFlag (uint8 IntNum)
{
    if ( IntNum <= 31 )
    {
        // Clear the interrupt pending flag in NVIC_ICPR0 register
        NVIC_ICPR0 = ( 1 << IntNum );
    }
    
    else if ( IntNum <= 59 )
    {
        // Clear the interrupt pending flag in NVIC_ICPR1 register
        IntNum -= 32 ;
        NVIC_ICPR1 = ( 1 << IntNum );
    }
    
    else 
    {
        // Return error if interrupt number is out of range
        /*Return Error */
    }
}

// This function gets the active status of the given interrupt number
uint8 NVIC_getActiveFlag (uint8 IntNum)
{
    uint8 flagStatus=0;
    
    if ( IntNum <= 31 )
    {
        // Get the active status of the interrupt from NVIC_IABR0 register
        flagStatus = GET_BIT(NVIC_IABR0,IntNum);
    }
    
    else if ( IntNum <= 59 )
    {
        // Get the active status of the interrupt from NVIC_IABR1 register
        IntNum -= 32 ;
        flagStatus = GET_BIT(NVIC_IABR0,IntNum);
    }
    
    else 
    {
        // Return error if interrupt number is out of range
        /*Return Error */
    }
    
    return flagStatus;
}


// This function sets the priority for the given interrupt number, group priority, and subgroup priority
// Note: Priority parameters must be limited between number of bits values for groups and subgroups as pre-configured value
void NVIC_setPriority (uint8 IntNum, uint8 GroubPriority,  uint8 SubPriority)
{
    
    if (IntNum >= 0)
    {
        // Set the priority for the interrupt in the NVIC_IPR[] register
        NVIC_IPR[IntNum] = ((SubPriority|(GroubPriority << _4G_0S )) << 4 );
    }
    
    #if NO_BITS_GROUBS_SUB == _4G_0S
    SCB_AIRCR = 0x05FA0300 ;
    
    #elif NO_BITS_GROUBS_SUB == _3G_1S
    SCB_AIRCR = 0x05FA0400 ;
    
    #elif NO_BITS_GROUBS_SUB == _2G_2S
    SCB_AIRCR = 0x05FA0500 ;
    
    #elif NO_BITS_GROUBS_SUB == _1G_3S
    SCB_AIRCR = 0x05FA0600 ;
    
    #elif NO_BITS_GROUBS_SUB == _0G_4S
    SCB_AIRCR = 0x05FA0700 ;
    
    #else
        #error "Wrong NO_BITS_GROUBS_SUB "
    
    #endif
    
}
