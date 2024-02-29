/*
* File: Dio.h
* Author: Tran Nhat Thai
* Date: 29/02/2024
* Description:  Header file for Digital Input/Output (DIO) operations, including GPIO 
configurations and functions for controlling individual channels, channel groups, and ports. 
*/
#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

// Define GPIO_MODER_MODE0_0 macro
#define GPIO_MODER_MODE0_0    (0x1 << (0 * 2))

/* Vendor ID */
#define VENDOR_ID           1

/* Module ID */
#define MODULE_ID           1

/* Software Version Information */
#define SW_MAJOR_VERSION    1
#define SW_MINOR_VERSION    0
#define SW_PATCH_VERSION    0

/* Base Addresses for GPIO Ports */
#define GPIOA_BASE          ((Dio_PortType)GPIOA)
#define GPIOB_BASE          ((Dio_PortType)GPIOB)

/* Standard Logic Levels */
#define STD_HIGH            ((Dio_LevelType)1)
#define STD_LOW             ((Dio_LevelType)0)

/* Data Types */
typedef uint8_t Dio_ChannelType;            /* Type for individual channel */
typedef uint16_t Dio_PortType;              /* Type for GPIO port */
typedef uint16_t Dio_PortLevelType;         /* Type for port level */
typedef uint16_t Dio_LevelType;             /* Type for logic level */

/* Structure for Channel Group */
typedef struct {
    Dio_PortType port;                  /* Port ID */
    Dio_ChannelType mask;               /* Channel Mask */
} Dio_ChannelGroupType;

/* Version Information Structure */
typedef struct {
    uint16_t vendorID;                  /* Vendor ID */
    uint16_t moduleID;                  /* Module ID */
    uint8_t sw_major_version;           /* Software Major Version */
    uint8_t sw_minor_version;           /* Software Minor Version */
    uint8_t sw_patch_version;           /* Software Patch Version */
} Std_VersionInfoType;

/* Function Declarations */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);

#endif /* DIO_H_ */
