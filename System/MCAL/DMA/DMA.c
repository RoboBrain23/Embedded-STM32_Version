/*******************************************************************/
/* Author      : Ibrahim Diab                                      */
/* File Name   : DMA.c                                             */
/* Description : Functions Implementation for DMA module           */
/*******************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"



void DMA_InitChannel(uint8 channelNum, DMA_Channel_Config_t * DMA_channelCfgPtr)
{
    // Enable or disable transfer complete interrupt based on configuration
    if (DMA_channelCfgPtr->trnsfer_Complete_Int == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 1);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 1);

    // Enable or disable half transfer interrupt based on configuration
    if (DMA_channelCfgPtr->half_Transfer_Int == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 2);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 2);

    // Enable or disable transfer error interrupt based on configuration
    if (DMA_channelCfgPtr->transfer_Err_Int == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 3);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 3);

    // Enable or disable memory to memory transfer based on configuration
    if (DMA_channelCfgPtr->Mem2Mem_Mode == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 14);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 14);

    // Set transfer direction based on configuration
    if (DMA_channelCfgPtr->transfer_Dir == READ_FROM_MEM)
        SET_BIT(DMA->channel[channelNum].CCR, 4);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 4);

    // Enable or disable circular mode based on configuration
    if (DMA_channelCfgPtr->circular_Mode == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 5);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 5);

    // Enable or disable memory increment mode based on configuration
    if (DMA_channelCfgPtr->mem_Inc == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 7);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 7);

    // Enable or disable peripheral increment mode based on configuration
    if (DMA_channelCfgPtr->per_Inc == DMA_ENABLED)
        SET_BIT(DMA->channel[channelNum].CCR, 6);
    else
        CLR_BIT(DMA->channel[channelNum].CCR, 6);

    // Set peripheral data size based on configuration
    MOD_2BIT(DMA->channel[channelNum].CCR, 8, DMA_channelCfgPtr->per_Size);

    // Set memory data size based on configuration
    MOD_2BIT(DMA->channel[channelNum].CCR, 10, DMA_channelCfgPtr->memory_Size);

    // Set channel priority based on configuration
    MOD_2BIT(DMA->channel[channelNum].CCR, 12, DMA_channelCfgPtr->channel_Priority);
}



void DMA_StartTransmit(uint8 channelNum, uint32 * ptrAddressSrc, uint32 * ptrAddressDes, uint32 DataLength)
{
    // Disable the DMA channel to configure it
    CLR_BIT(DMA->channel[channelNum].CCR,0);
    
    // Set the number of data items to transfer
    DMA->channel[channelNum].CNDTR = DataLength;
    
    // Set the source address for the transfer
    DMA->channel[channelNum].CPAR = (uint32)ptrAddressSrc;
    
    // Set the destination address for the transfer
    DMA->channel[channelNum].CMAR = (uint32)ptrAddressDes;
    
    // Enable the DMA channel to start the transfer
    SET_BIT(DMA->channel[channelNum].CCR,0);
}

void DMA_setCallBackInt(uint8 DMA_channelNumber, void (*DMA_Ch_CmpTtr)(void), void (*DMA_CH_HlfTtr)(void), void (*DMA_CH_ErrTtr)(void))
{
    // Assign the provided callback functions to the appropriate elements in the DMA callback arrays.
    DMA_CmpTra_channel[(DMA_channelNumber-1)] = DMA_Ch_CmpTtr;  // Set the transfer complete callback function for the specified DMA channel.
    DMA_HlfTra_channel[(DMA_channelNumber-1)] = DMA_CH_HlfTtr;  // Set the half transfer complete callback function for the specified DMA channel.
    DMA_ErrTra_channel[(DMA_channelNumber-1)] = DMA_CH_ErrTtr;  // Set the error transfer callback function for the specified DMA channel.
}


void DMA1_Channel1_IRQHandler(void)
{

    if(GET_BIT(DMA->ISR,1)==1) // check if transfer complete interrupt flag is set for channel 1
    {
        // transfer complete
        if(DMA_CmpTra_channel[0]!= NULL)
            DMA_CmpTra_channel[0]();
    }
    else if((GET_BIT(DMA->ISR,2)==1)) // check if half transfer interrupt flag is set for channel 1
    {
        // half transfer
        if(DMA_HlfTra_channel[0]!= NULL)
            DMA_HlfTra_channel[0]();
    }
    else if(GET_BIT(DMA->ISR,3)==1) // check if transfer error interrupt flag is set for channel 1
    {
        // transfer error
        if(DMA_ErrTra_channel[0]!= NULL)
            DMA_ErrTra_channel[0]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,0,0xf);
}

void DMA1_Channel2_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,5)==1) // check if transfer complete interrupt flag is set for channel 2
    {
        // transfer complete
        if(DMA_CmpTra_channel[1]!= NULL)
            DMA_CmpTra_channel[1]();

    }
    else if((GET_BIT(DMA->ISR,6)==1)) // check if half transfer interrupt flag is set for channel 2
    {
        // half transfer
        if(DMA_HlfTra_channel[1]!= NULL)
            DMA_HlfTra_channel[1]();
    }
    else if(GET_BIT(DMA->ISR,7)==1) // check if transfer error interrupt flag is set for channel 2
    {
        // transfer error
        if(DMA_ErrTra_channel[1]!= NULL)
            DMA_ErrTra_channel[1]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,4,0xf);
}

void DMA1_Channel3_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,9)==1) // check if transfer complete interrupt flag is set for channel 3
    {
        // transfer complete
        if(DMA_CmpTra_channel[2]!= NULL)
            DMA_CmpTra_channel[2]();

    }
    else if((GET_BIT(DMA->ISR,10)==1)) // check if half transfer interrupt flag is set for channel 3
    {
        // half transfer
        if(DMA_HlfTra_channel[2]!= NULL)
            DMA_HlfTra_channel[2]();
    }
    else if(GET_BIT(DMA->ISR,11)==1) // check if transfer error interrupt flag is set for channel 3
    {
        // transfer error
        if(DMA_ErrTra_channel[2]!= NULL)
            DMA_ErrTra_channel[2]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,8,0xf);
}

void DMA1_Channel4_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,13)==1) // check if transfer complete interrupt flag is set for channel 4
    {
        // transfer complete
        if(DMA_CmpTra_channel[3]!= NULL)
            DMA_CmpTra_channel[3]();

    }
    else if((GET_BIT(DMA->ISR,13)==1)) // check if half transfer interrupt flag is set for channel 4
    {
        // half transfer
        if(DMA_HlfTra_channel[3]!= NULL)
            DMA_HlfTra_channel[3]();
    }
    else if(GET_BIT(DMA->ISR,13)==1) // check if transfer error interrupt flag is set for channel 4
    {
        // transfer error
        if(DMA_ErrTra_channel[3]!= NULL)
            DMA_ErrTra_channel[3]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,12,0xf);
}


void DMA1_Channel5_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,17)==1) // check if transfer complete interrupt flag is set for channel 5
    {
        // transfer complete
        if(DMA_CmpTra_channel[4]!= NULL)
            DMA_CmpTra_channel[4]();

    }
    else if((GET_BIT(DMA->ISR,18)==1)) // check if half transfer interrupt flag is set for channel 5
    {
        // half transfer
        if(DMA_HlfTra_channel[4]!= NULL)
            DMA_HlfTra_channel[4]();
    }
    else if(GET_BIT(DMA->ISR,19)==1) // check if transfer error interrupt flag is set for channel 5
    {
        // transfer error
        if(DMA_ErrTra_channel[4]!= NULL)
            DMA_ErrTra_channel[4]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,16,0xf);
}

void DMA1_Channel6_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,21)==1) // check if transfer complete interrupt flag is set for channel 6
    {
        // transfer complete
        if(DMA_CmpTra_channel[5]!= NULL)
            DMA_CmpTra_channel[5]();

    }
    else if((GET_BIT(DMA->ISR,22)==1)) // check if half transfer interrupt flag is set for channel 6
    {
        // half transfer
        if(DMA_HlfTra_channel[5]!= NULL)
            DMA_HlfTra_channel[5]();
    }
    else if(GET_BIT(DMA->ISR,23)==1) // check if transfer error interrupt flag is set for channel 6
    {
        // transfer error
        if(DMA_ErrTra_channel[5]!= NULL)
            DMA_ErrTra_channel[5]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,20,0xf);
}

void DMA1_Channel7_IRQHandler(void)
{
    if(GET_BIT(DMA->ISR,25)==1) // check if transfer complete interrupt flag is set for channel 7
    {
        // transfer complete
        if(DMA_CmpTra_channel[6]!= NULL)
            DMA_CmpTra_channel[6]();
    }
    else if((GET_BIT(DMA->ISR,26)==1)) // check if half transfer interrupt flag is set for channel 7
    {
        // half transfer
        if(DMA_HlfTra_channel[6]!= NULL)
            DMA_HlfTra_channel[6]();
    }
    else if(GET_BIT(DMA->ISR,27)==1) // check if transfer error interrupt flag is set for channel 7
    {
        // transfer error
        if(DMA_ErrTra_channel[6]!= NULL)
            DMA_ErrTra_channel[6]();
    }

    /*Clear Interrupt flag*/
    MOD_4BIT(DMA->IFCR,24,0xf);
}


