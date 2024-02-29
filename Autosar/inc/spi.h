 #ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"
#include <stddef.h>

// Vendor and module identification information
#define VENDOR_ID          0x1234 // Vendor ID
#define MODULE_ID          0xABCD // Module ID
#define SW_MAJOR_VERSION   1      // Software major version
#define SW_MINOR_VERSION   0      // Software minor version
#define SW_PATCH_VERSION   0      // Software patch version

// Number of SPI sequences
#define NUM_OF_SPI_SEQUENCES 5

// Number of SPI hardware units
#define NUM_OF_SPI_HW_UNITS 3

// Definition of SPI hardware units
typedef enum {
    SPI_HWUnit_0,
    SPI_HWUnit_1,
    SPI_HWUnit_2,
    // Add more hardware units if needed
} Spi_HWUnitType;

// Definition of modes for setting SPI asynchronous mode
typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE,
    SPI_DMA_MODE
    // Add more modes if needed
} Spi_AsyncModeType;

typedef uint8_t Spi_SequenceType;
#define NUM_OF_SEQUENCES 8

// Return type for SPI functions
typedef enum {
    E_OK = 0,       // Success
    E_NOT_OK = 1    // Failure
} Std_ReturnType;

// Structure for SPI configuration
typedef struct {
    uint16_t direction;
    uint16_t mode;
    uint16_t dataSize;
    uint16_t clockPolarity;
    uint16_t clockPhase;
    uint16_t nss;
    uint16_t baudRatePrescaler;
    uint16_t firstBit;
    uint16_t crcPolynomial;
} Spi_ConfigType;

// Structure for version information
/*
typedef struct {
    uint16_t vendorID;
    uint16_t moduleID;
    uint8_t sw_major_version;
    uint8_t sw_minor_version;
    uint8_t sw_patch_version;
} Std_VersionInfoType;
*/


// Function prototypes
Std_ReturnType Spi_Init(const Spi_ConfigType* ConfigPtr);
Std_ReturnType Spi_DeInit(void);
Std_ReturnType Spi_WriteIB(const uint8_t* DataBufferPtr);
Std_ReturnType Spi_SetupEB(const Spi_ConfigType* ConfigPtr, const uint8_t* SrcDataBufferPtr, uint8_t* DesDataBufferPtr, uint16_t Length);
Std_ReturnType Spi_GetJobResult(void);
Std_ReturnType Spi_GetSequenceResult(void);
/*void Spi_GetVersionInfo(Std_VersionInfoType* VersionInfo);*/
Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence);
Std_ReturnType Spi_Cancel(Spi_SequenceType Sequence);
Std_ReturnType Spi_SetAsyncMode(Spi_HWUnitType HWUnit, Spi_AsyncModeType Mode);

#endif /* SPI_H */
