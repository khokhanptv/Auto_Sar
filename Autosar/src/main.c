#include "DIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "spi.h"
#include "stdio.h"




int main(void)
{
    /* Initialize configuration for GPIOA and GPIOB */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;  /* Enable clock for GPIOA and GPIOB */
    /* Configure PA0 and PB0 as output pins */
    GPIOA->MODER |= GPIO_MODER_MODE0_0;   
    GPIOB->MODER |= GPIO_MODER_MODE0_0; 
  
    // Initialize SPI configuration and other necessary variables
    Spi_ConfigType spiConfig;
    // Configure spiConfig appropriately
    
    // Prepare data for transmission
    uint8_t txData[] = {0x01, 0x02, 0x03};
    uint8_t rxData[sizeof(txData)]; // Buffer to receive data
   
    // Main loop for continuous data transmission
    
    
    while(1)
    {
				/* CODE DIO*/
        /* Turn on LEDs on both ports */
        GPIOA->BSRR |= GPIO_BSRR_BS_0;  // Turn on LED on port A (PA0)
        GPIOB->BSRR |= GPIO_BSRR_BS_0;  // Turn on LED on port B (PB0)
        /* Delay to keep the LEDs on for a period of time */
        for(int i = 0; i < 1000000; i++);  // Delay
        /* Turn off LEDs on both ports */
        GPIOA->BSRR |= GPIO_BSRR_BR_0;  // Turn off LED on port A (PA0)
        GPIOB->BSRR |= GPIO_BSRR_BR_0;  // Turn off LED on port B (PB0)
        /* Delay to keep the LEDs off for a period of time */
        for(int i = 0; i < 1000000; i++);  // Delay
			
			
			
				/* CODE SPI*/
				// Perform data transmission and reception
        if (Spi_SetupEB(&spiConfig, txData, rxData, sizeof(txData)) != E_OK) {
						// Handle error if transmission fails
        }
        // Wait for transmission and reception to complete
        while (Spi_GetJobResult() != E_OK) {
	 
        }
				// Process the received data if needed
				printf("Received data: ");
				for (int i = 0; i < sizeof(rxData); ++i) {
							printf("%02X ", rxData[i]);
				}
				printf("\n");
				for(int i = 0; i < 1000000; i++);  // Delay
			
			
    }
}
