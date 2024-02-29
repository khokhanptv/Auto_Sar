/*
* File: Dio.c
* Author: Tran Nhat Thai
* Date: 29/02/2024
* Description: Source file for Dio.h containing implementation of GPIO (Digital Input/Output) operations.
*/


#include "DIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include <stddef.h>


/*
* Function: Dio_ReadChannel
* Description: Reads the state of a specific channel
* Input:
*   ChannelId - Identifier of the channel to read
* Output:
*   Returns the state of the specified channel (STD_HIGH or STD_LOW)
*/
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

/*
* Function: Dio_WriteChannel
* Description: Writes the state (HIGH or LOW) to a specified channel.
* Input:
*   - ChannelId: The ID of the channel to be written.
*   - Level: The desired state (STD_HIGH or STD_LOW) to be set on the channel.
* Output: None
*/
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

/*
* Function: Dio_ReadChannelGroup
* Description: Reads the state of a group of channels specified by the given ChannelGroupIdPtr.
* Input:
*   - ChannelGroupIdPtr: Pointer to a structure containing the port ID and channel mask.
* Output:
*   - Returns the state of the specified channel group.
*/

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
/*
* Function: Dio_WriteChannelGroup
* Description: Writes the specified level to the group of channels indicated by the given ChannelGroupIdPtr.
* Input:
*   - ChannelGroupIdPtr: Pointer to a structure containing the port ID and channel mask.
*   - Level: The level to be written to the specified channels.
* Output:
*   - None
*/
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


/*
* Function: Dio_GetVersionInfo
* Description: Retrieves the version information of the Dio module and stores it in the provided VersionInfo structure.
* Input:
*   - VersionInfo: Pointer to a structure where the version information will be stored.
* Output:
*   - None
*/
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

/*
* Function: Dio_FlipChannel
* Description: Toggles the state of the specified channel (i.e., flips the channel's logic level).
* Input:
*   - ChannelId: Identifier of the channel whose state will be toggled.
* Output:
*   - Returns the new state of the channel after toggling (STD_HIGH or STD_LOW).
*/

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

/*
* Function: Dio_MaskedWritePort
* Description: Writes the specified value to the specified port, while preserving the state of only the channels specified by the mask.
* Input:
*   - PortId: Identifier of the port to write to (e.g., GPIOA_BASE, GPIOB_BASE).
*   - Level: The value to write to the port.
*   - Mask: A bitmask indicating which channels' states should be preserved while writing the new value.
* Output: None
*/
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
            break;
    }
}
