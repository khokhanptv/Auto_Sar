#include "SPI.h"

// Function to initialize SPI with the provided configuration
Std_ReturnType Spi_Init(const Spi_ConfigType* ConfigPtr) {
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



// Function to deinitialize SPI
Std_ReturnType Spi_DeInit(void) {
    // Deinitialize SPI peripheral
    SPI_DeInit(SPI1);
    // Return success status
    return E_OK;
}

// Function to write data to SPI
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

// Function to setup SPI with enabled buffering
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

// Function to get the status of SPI
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


// Function to perform synchronous data transmission via SPI
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

// Function to cancel data transmission or reception of SPI
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

// Function to set asynchronous mode of operation for SPI
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

// Define a function to get the results of an SPI  
Std_ReturnType Spi_GetJobResult(void) {
    // Check the state of the SPI to determine the result
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET) {
        return E_OK;  
    } else {
        return E_NOT_OK;  
    }
}