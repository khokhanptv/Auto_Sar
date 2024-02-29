/*
* File: Spi.c
* Author: Tran Nhat Thai
* Date: 29/02/2024
* Description: Source file for Spi.h containing implementation of SPI (Serial Peripheral Interface) operations.
*/

#include "Spi.h"

/*
* Function: Spi_Init
* Description: Initializes the SPI peripheral with the provided configuration.
* Input:
*   - ConfigPtr: Pointer to the configuration structure containing SPI settings.
* Output:
*   - E_OK: If initialization is successful.
*   - E_NOT_OK: If the configuration pointer is NULL.
*/

Std_ReturnType Spi_Init(const Spi_ConfigType* ConfigPtr) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    // Check if the configuration pointer is valid
    if (ConfigPtr == NULL) {
        return E_NOT_OK; // Return error code if the pointer is NULL
    }

    // Initialize SPI structure
    SPI_InitTypeDef SPI_InitStruct;

    // Configure SPI settings from the provided configuration
    SPI_InitStruct.SPI_Direction = ConfigPtr->direction;
    SPI_InitStruct.SPI_Mode = ConfigPtr->mode;
    SPI_InitStruct.SPI_DataSize = ConfigPtr->dataSize;
    SPI_InitStruct.SPI_CPOL = ConfigPtr->clockPolarity;
    SPI_InitStruct.SPI_CPHA = ConfigPtr->clockPhase;
    SPI_InitStruct.SPI_NSS = ConfigPtr->nss;
    SPI_InitStruct.SPI_BaudRatePrescaler = ConfigPtr->baudRatePrescaler;
    SPI_InitStruct.SPI_FirstBit = ConfigPtr->firstBit;
    SPI_InitStruct.SPI_CRCPolynomial = ConfigPtr->crcPolynomial;

    // Return success status
    return E_OK;
}



/*
* Function: Spi_DeInit
* Description: Deinitializes the SPI peripheral.
* Input: None
* Output:
*   - E_OK: If deinitialization is successful.
*/

Std_ReturnType Spi_DeInit(void) {
    // Deinitialize SPI peripheral
    SPI_DeInit(SPI1);
    // Return success status
    return E_OK;
}

/*
* Function: Spi_WriteIB
* Description: Writes data to the SPI peripheral using interrupt-based transmission.
* Input:
*   - DataBufferPtr: Pointer to the data buffer containing the data to be transmitted.
* Output:
*   - E_OK: If data transmission is successful.
*   - E_NOT_OK: If the data buffer pointer is NULL.
*/

Std_ReturnType Spi_WriteIB(const uint8_t* DataBufferPtr) {
    // Check if the data buffer pointer is valid
    if (DataBufferPtr == NULL) {
        return E_NOT_OK; // Return error code if the pointer is NULL
    }
    
    // Wait until SPI is ready for transmission
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    // Send data via SPI
    SPI_I2S_SendData(SPI1, *DataBufferPtr);

    // Return success status
    return E_OK;
}

/*
* Function: Spi_SetupEB
* Description: Sets up SPI for transmission and reception using interrupt-based communication.
* Input:
*   - ConfigPtr: Pointer to the SPI configuration structure.
*   - SrcDataBufferPtr: Pointer to the source data buffer containing the data to be transmitted.
*   - DesDataBufferPtr: Pointer to the destination data buffer to store the received data.
*   - Length: Length of the data to be transmitted and received.
* Output:
*   - E_OK: If data transmission and reception are successful.
*   - E_NOT_OK: If any of the pointers is NULL or if data transmission fails.
*/

Std_ReturnType Spi_SetupEB(const Spi_ConfigType* ConfigPtr, const uint8_t* SrcDataBufferPtr, uint8_t* DesDataBufferPtr, uint16_t Length) {
    // Check if any of the pointers is NULL
    if (ConfigPtr == NULL || SrcDataBufferPtr == NULL || DesDataBufferPtr == NULL) {
        return E_NOT_OK; // Return error code if any pointer is NULL
    }

    // Initialize SPI with the provided configuration
    if (Spi_Init(ConfigPtr) != E_OK) {
        return E_NOT_OK; // Return error code if initialization fails
    }

    // Transmit and receive data
    for (uint16_t i = 0; i < Length; i++) {
        // Send data from source buffer
        if (Spi_WriteIB(&SrcDataBufferPtr[i]) != E_OK) {
            return E_NOT_OK; // Return error code if data transmission fails
        }

        // Wait until data is received
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

        // Receive data into destination buffer
        DesDataBufferPtr[i] = SPI_I2S_ReceiveData(SPI1);
    }

    // Return success status
    return E_OK;
}

/*
* Function: Spi_GetStatus
* Description: Checks the status of SPI.
* Input: None
* Output:
*   - E_OK: If SPI is not busy.
*   - E_NOT_OK: If SPI is busy.
*/

Std_ReturnType Spi_GetStatus(void) {
    // Check the status of SPI
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {
        return E_NOT_OK; // Return error code if SPI is busy
    } else {
        return E_OK; // Return success status if SPI is not busy
    }
}

// Function to get version information
/*
void Spi_GetVersionInfo(Std_VersionInfoType* VersionInfo) {
    // Check if the version information pointer is valid
    if (VersionInfo != NULL) {
        // Populate version information fields
        VersionInfo->vendorID = VENDOR_ID;
        VersionInfo->moduleID = MODULE_ID;
        VersionInfo->sw_major_version = SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = SW_PATCH_VERSION;
    }
}
*/



/*
* Function: Spi_SyncTransmit
* Description: Performs synchronous data transmission according to the specified sequence.
* Input:
*   - Sequence: The sequence of data transmission and reception.
* Output:
*   - E_OK: If the transmission process is completed successfully.
*   - E_NOT_OK: If the sequence is invalid.

*/
Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence) {
    // Check the validity of the sequence
    if (Sequence >= NUM_OF_SEQUENCES) {
        return E_NOT_OK; // Return error code if the sequence is invalid
    }

    // Perform data transmission and reception according to the sequence
    // Wait until the process is completed

    // Return the result
    return E_OK;
}



/*
* Function: Spi_Cancel
* Description: Cancels data transmission or reception for the specified sequence.
* Input:
*   - Sequence: The sequence of data transmission or reception to be cancelled.
* Output:
*   - E_OK: If the cancellation process is completed successfully.
*   - E_NOT_OK: If the sequence is invalid.
*/

Std_ReturnType Spi_Cancel(Spi_SequenceType Sequence) {
    // Perform cancellation of data transmission or reception for the specified sequence
    
    // Check the validity of the sequence
    if (Sequence < NUM_OF_SPI_SEQUENCES) {
        // Perform necessary actions to cancel data transmission or reception for the sequence
        
        // Return success status
        return E_OK;
    } else {
        // Return error code if the sequence is invalid
        return E_NOT_OK;
    }
}



/*
* Function: Spi_SetAsyncMode
* Description: Sets asynchronous mode of operation for the specified SPI hardware unit.
* Input:
*   - HWUnit: The SPI hardware unit for which asynchronous mode is to be set.
*   - Mode: The asynchronous mode to be set (SPI_POLLING_MODE, SPI_INTERRUPT_MODE, or SPI_DMA_MODE).
* Output:
*   - E_OK: If the asynchronous mode is set successfully.
*   - E_NOT_OK: If the hardware unit or mode is invalid.
*/

Std_ReturnType Spi_SetAsyncMode(Spi_HWUnitType HWUnit, Spi_AsyncModeType Mode) {
    // Set asynchronous mode of operation for the specified SPI hardware unit
    
    // Check the validity of the SPI hardware unit and mode
    if (HWUnit < NUM_OF_SPI_HW_UNITS && (Mode == SPI_POLLING_MODE || Mode == SPI_INTERRUPT_MODE || Mode == SPI_DMA_MODE)) {
        // Perform necessary actions to set asynchronous mode of operation for the SPI hardware unit
 
        // Return success status
        return E_OK;
    } else {
        // Return error code if the hardware unit or mode is invalid
        return E_NOT_OK;
    }
}

/*
* Function: Spi_GetJobResult
* Description: Checks the state of the SPI to determine the result of the job.
* Input: None
* Output:
*   - E_OK: If the SPI job is completed successfully.
*   - E_NOT_OK: If the SPI job is still ongoing.
*/
Std_ReturnType Spi_GetJobResult(void) {
    // Check the state of the SPI to determine the result
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET) {
        return E_OK;  
    } else {
        return E_NOT_OK;  
    }
}