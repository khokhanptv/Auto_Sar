#include "DIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include <stddef.h>


/* Function to read the state of a channel */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType channel_state = STD_LOW;  /* Default channel state is LOW */
    
    if (ChannelId < 16) {
        if (GPIOA->IDR & (1 << ChannelId)) {
            return STD_HIGH;
        } else {
            return STD_LOW;
        }
    } else if (ChannelId < 32) {
        if (GPIOB->IDR & (1 << (ChannelId - 16))) {
            return STD_HIGH;
        } else {
            return STD_LOW;
        }
    }
    
    return channel_state;
}

/* Function to write a value to a channel */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    if (ChannelId < 16) {
        if (Level == STD_HIGH) {
            GPIOA->BSRR = (1 << ChannelId); // Set bit to turn on the channel
        } else {
            GPIOA->BSRR = (1 << (ChannelId + 16)); // Set bit to turn off the channel
        }
    } else if (ChannelId < 32) {
        if (Level == STD_HIGH) {
            GPIOB->BSRR = (1 << (ChannelId - 16)); // Set bit to turn on the channel
        } else {
            GPIOB->BSRR = (1 << (ChannelId + 16 - 16)); // Set bit to turn off the channel
        }
    }
}

/* Function to read the state of a channel group */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
    Dio_PortLevelType port_state = 0;  /* Initialize port state to 0 */
    
    if (ChannelGroupIdPtr != NULL)
    {
        switch(ChannelGroupIdPtr->port)
        {
            case GPIOA_BASE:
                port_state = GPIOA->IDR & ChannelGroupIdPtr->mask;  /* Read the state of port A for the specified channels and store in port_state */
                break;
            case GPIOB_BASE:
                port_state = GPIOB->IDR & ChannelGroupIdPtr->mask;  /* Read the state of port B for the specified channels and store in port_state */
                break;
            // Add other cases for other ports if needed
            default:
                // Handle the case if PortId is invalid
                // For example: do nothing or report an error
                break;
        }
    }
    
    return port_state;  /* Return the state of the port */
}

/* Function to write a value to a channel group */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
    if (ChannelGroupIdPtr != NULL)
    {
        switch(ChannelGroupIdPtr->port)
        {
            case GPIOA_BASE:
                GPIOA->ODR = (GPIOA->ODR & ~ChannelGroupIdPtr->mask) | (Level & ChannelGroupIdPtr->mask);  /* Write value of port A for the specified channels */
                break;
            case GPIOB_BASE:
                GPIOB->ODR = (GPIOB->ODR & ~ChannelGroupIdPtr->mask) | (Level & ChannelGroupIdPtr->mask);  /* Write value of port B for the specified channels */
                break;
            // Add other cases for other ports if needed
            default:
                // Handle the case if PortId is invalid
                // For example: do nothing or report an error
                break;
        }
    }
}

/* Function to get version information of the Dio module */
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
    if (VersionInfo != NULL)
    {
        /* Set version information */
        VersionInfo->vendorID = VENDOR_ID;
        VersionInfo->moduleID = MODULE_ID;
        VersionInfo->sw_major_version = SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = SW_PATCH_VERSION;
    }
}

/* Function to toggle the state of a channel */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType channel_state = Dio_ReadChannel(ChannelId);  /* Read current state of channel */
    
    /* Toggle the state */
    if(channel_state == STD_HIGH)
    {
        Dio_WriteChannel(ChannelId, STD_LOW);  /* If state is HIGH, write LOW */
        return STD_LOW;  /* Return LOW */
    }
    else
    {
        Dio_WriteChannel(ChannelId, STD_HIGH);  /* If state is LOW, write HIGH */
        return STD_HIGH;  /* Return HIGH */
    }
}

/* Function to write a value to a port, changing only the channels specified by a mask */
void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask)
{
    switch(PortId)
    {
        case GPIOA_BASE:
            GPIOA->ODR = (GPIOA->ODR & ~Mask) | (Level & Mask);  /* Write value to port A, changing only the channels specified by the mask */
            break;
        case GPIOB_BASE:
            GPIOB->ODR = (GPIOB->ODR & ~Mask) | (Level & Mask);  /* Write value to port B, changing only the channels specified by the mask */
            break;
        // Add other cases for other ports if needed
        default:
            // Handle the case if PortId is invalid
            // For example: do nothing or report an error
            break;
    }
}
