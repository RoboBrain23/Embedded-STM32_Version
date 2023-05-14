/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : EXTI.c                                            */
/* Description : Functions Implementation for EXTI module          */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void EXTI_enableEXTI(uint8 Line, uint8 Mode)
{
    // Enable the interrupt on the specified line
    SET_BIT(EXTI->IMR, Line);
    
    // Set the triggering mode
    switch (Mode) {
        case RISING:
            SET_BIT(EXTI->RTSR, Line);
            CLR_BIT(EXTI->FTSR, Line);
            break;
        case FALLING:
            CLR_BIT(EXTI->RTSR, Line);
            SET_BIT(EXTI->FTSR, Line);
            break;
        case CHANGE:
            SET_BIT(EXTI->RTSR, Line);
            SET_BIT(EXTI->FTSR, Line);
            break;
        default:
            break;
    }
}


/*
   This function disables the external interrupt on the specified line.
   - Line: The external interrupt line number to be disabled.
*/
void EXTI_disableEXTI(uint8 Line)
{
    // Disable the interrupt on the specified line
    CLR_BIT(EXTI->IMR, Line);
}


/*
   This function sets a software trigger on the specified external interrupt line.
   - Line: The external interrupt line number to be triggered.
*/
void EXTI_setSWTrigger(uint8 Line)
{
    // Set a software trigger on the specified line
    SET_BIT(EXTI->SWIER, Line);
}



/*
   This function sets a callback function to be executed when the specified external interrupt line is triggered.
   - EXTINumber: The external interrupt line number.
   - ptr: A pointer to the callback function.
*/
void EXTI_setCallBack(uint8 EXTINumber, void (*ptr)(void))
{
    // Set the callback function for the specified external interrupt line
    if (EXTINumber <= 15) {
        EXTI_callBack[EXTINumber] = ptr;
    }
}



void EXTI0_IRQHandler(void)
{
    EXTI_callBack[0]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,0);
    
}

void EXTI1_IRQHandler(void)
{
    EXTI_callBack[1]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,1);
    
}

void EXTI2_IRQHandler(void)
{
    EXTI_callBack[2]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,2);
    
}

void EXTI3_IRQHandler(void)
{
    EXTI_callBack[3]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,3);
    
}
void EXTI4_IRQHandler(void)
{
    EXTI_callBack[4]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,4);
    
}
void EXTI5_IRQHandler(void)
{
    EXTI_callBack[5]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,5);
    
}
void EXTI6_IRQHandler(void)
{
    EXTI_callBack[6]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,6);
    
}
void EXTI7_IRQHandler(void)
{
    EXTI_callBack[7]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,7);
    
}
void EXTI8_IRQHandler(void)
{
    EXTI_callBack[8]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,8);
    
}
void EXTI9_IRQHandler(void)
{
    EXTI_callBack[9]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,9);
    
}
void EXTI10_IRQHandler(void)
{
    EXTI_callBack[10]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,10);
    
}
void EXTI11_IRQHandler(void)
{
    EXTI_callBack[11]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,11);
    
}
void EXTI12_IRQHandler(void)
{
    EXTI_callBack[12]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,12);
    
}
void EXTI13_IRQHandler(void)
{
    EXTI_callBack[13]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,13);
    
}
void EXTI14_IRQHandler(void)
{
    EXTI_callBack[14]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,14);
    
}

void EXTI15_IRQHandler(void)
{
    EXTI_callBack[15]();
    
    /*  Clear pending Bit       */
    SET_BIT(EXTI->PR,15);
    
}

