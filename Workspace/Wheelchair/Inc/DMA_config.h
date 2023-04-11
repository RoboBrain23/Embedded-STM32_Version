/***************************************************************/
/* Author      : Ibrahim Diab                                  */
/* File Name   : DMA_config.h                                  */
/* Description : Configuration for DMA module STM32F103        */
/***************************************************************/


#ifndef DMA_CONFIG_H
#define DMA_CONFIG_H

/**
Requirements:

- Enable the DMA clock(s) in the RCC driver before using the DMA driver.
- Configure the DMA channel(s) using DMA_InitChannel function before starting a transfer.
- Set up the transfer source and destination addresses using DMA_StartTransmit function before starting a transfer.
- If using interrupt-based transfers, set up the corresponding interrupt callback using DMA_setCallBackInt function before starting a transfer.
- Enable the corresponding DMA channel interrupt in NVIC using NVIC_EnableIRQ function if using interrupt-based transfers.

Note: Failing to meet any of these requirements may result in unexpected behavior of the driver.
*/


#endif // DMA_CONFIG_H
