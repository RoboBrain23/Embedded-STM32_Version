/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : AFIO.c                                            */
/* Description : Functions Implementation for AFIO module          */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"


/* Function to configure EXTI interrupt lines */
void AFIO_setEXTIConfig(uint8 Line ,uint8 PortMap)
{
    uint8 RegIndex =0;
    
    /* Calculate the register index based on the line number */
    if(Line<=3)
    {
        /* No need to change the register index */
    }
    else if(Line<=7)
    {
        RegIndex = 1;
        Line -=4;
    }
    else if(Line<=11)
    {
        RegIndex = 2;
        Line -=8;
    }
    else if(Line<=15)
    {
        RegIndex = 3;
        Line -=12;
    }
    
    /* Clear the corresponding bits and set the new port map */
    AFIO->EXTICR[RegIndex] &= ~(0b1111 << (Line*4));
    AFIO->EXTICR[RegIndex] |=  (PortMap << (Line*4));
}
