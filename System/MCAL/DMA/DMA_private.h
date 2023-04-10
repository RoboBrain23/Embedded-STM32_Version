/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DMA_private.h                                     */
/* Description : Private addresses for DMA module STM32F103        */
/*******************************************************************/

#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

// Array of function pointers for DMA interrupt callback
static void (*DMA_CmpTra_channel[7])(void) = { NULL };
static void (*DMA_HlfTra_channel[7])(void) = { NULL };
static void (*DMA_ErrTra_channel[7])(void) = { NULL };

// DMA channel structure
typedef struct 
{
    uint32 CCR;
    uint32 CNDTR;
    uint32 CPAR;
    uint32 CMAR;
    uint32 Reserved;
}channel_t;

// DMA structure
typedef struct
{
    uint32 ISR;
    uint32 IFCR;
    channel_t channel[7]; 
}DMA_t;

// Define DMA base address
#define DMA ((volatile DMA_t *)0x40020000)

#endif // DMA_PRIVATE_H
