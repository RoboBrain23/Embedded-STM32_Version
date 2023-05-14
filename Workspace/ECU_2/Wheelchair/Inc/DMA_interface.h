/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DMA_interface.h                                   */
/* Description : Interfacing macros for DMA module STM32F103       */
/*******************************************************************/


#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/*
 * Configuration options for DMA_Channel_Config_t structure
 * Mem2Mem_Mode: enable memory-to-memory mode if set to 1
 * mem_Inc: enable memory increment if set to 1
 * per_Inc: enable peripheral increment if set to 1
 * circular_Mode: enable circular mode if set to 1
 * transfer_Err_Int: enable transfer error interrupt if set to 1
 * half_Transfer_Int: enable half transfer interrupt if set to 1
 * trnsfer_Complete_Int: enable transfer complete interrupt if set to 1
 */
#define DMA_DISABLED     0  
#define DMA_ENABLED      1

/* transfer_Dir: direction of data transfer */
#define READ_FROM_MEM    0
#define READ_FROM_PER    1

/* channel_Priority: priority level of the DMA channel */
#define CHANNEL_LOW_PRIORITY        0b00
#define CHANNEL_MEDIUM_PRIORITY     0b01
#define CHANNEL_HIGH_PRIORITY       0b10
#define CHANNEL_VERY_HIGH_PRIORITY  0b11

/* memory_Size and per_Size: size of memory and peripheral data transfers */
#define BITS_8  0b00
#define BITS_16 0b01
#define BITS_32 0b10


typedef struct
{
    uint8 channel_Priority;     // DMA channel priority level
    uint8 memory_Size;          // Memory data transfer size
    uint8 per_Size;             // Peripheral data transfer size
    uint8 mem_Inc;              // Memory increment mode
    uint8 per_Inc;              // Peripheral increment mode
    uint8 circular_Mode;        // Circular mode
    uint8 transfer_Dir;         // Data transfer direction
    uint8 transfer_Err_Int;     // Transfer error interrupt
    uint8 half_Transfer_Int;    // Half transfer interrupt
    uint8 trnsfer_Complete_Int; // Transfer complete interrupt
    uint8 Mem2Mem_Mode;         // Memory to memory mode
} DMA_Channel_Config_t;


/* 
 * Initialize DMA channel with the given configuration settings.
 * channelNum: DMA channel number (1 to 7)
 * DMA_channelCfgPtr: pointer to DMA channel configuration structure
 */
void DMA_InitChannel(uint8 channelNum, DMA_Channel_Config_t *DMA_channelCfgPtr);


/*
 * Start DMA data transmission.
 * channelNum: DMA channel number (1 to 7)
 * ptrAddressSrc: pointer to source memory location
 * ptrAddressDes: pointer to destination memory location
 * DataLength: length of data to be transmitted (0 up to 65535)
 */
void DMA_StartTransmit(uint8 channelNum, uint32 *ptrAddressSrc, uint32 *ptrAddressDes, uint32 DataLength);


/*
 * Set callback function to handle DMA interrupts.
 * DMA_channelNumber: DMA channel number (1 to 7)
 * DMA_Ch_CmpTtr: function pointer for transfer complete interrupt handler
 * DMA_CH_HlfTtr: function pointer for half transfer interrupt handler
 * DMA_CH_ErrTtr: function pointer for transfer error interrupt handler
 */
void DMA_setCallBackInt(uint8 DMA_channelNumber, void (*DMA_Ch_CmpTtr)(void), void (*DMA_CH_HlfTtr)(void), void (*DMA_CH_ErrTtr)(void));


// Interrupt handlers for each DMA channel
void DMA1_Channel1_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);
void DMA1_Channel3_IRQHandler(void);
void DMA1_Channel4_IRQHandler(void);
void DMA1_Channel5_IRQHandler(void);
void DMA1_Channel6_IRQHandler(void);
void DMA1_Channel7_IRQHandler(void);



#endif // DMA_INTERFACE_H


