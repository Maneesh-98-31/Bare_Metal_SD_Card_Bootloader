#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "sd.h"

static spi_def *spi1 = 0x0;

#define SPI1_CS_PIN   4U    /* PA4 */

#define CS_LOW()  (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_BSRR  |= (1U << (SPI1_CS_PIN + 16)))
#define CS_HIGH() (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_BSRR  |= (1U << SPI1_CS_PIN))

void uart_test(){
    //uint32_t ret = failed(RCC_E);
    //gpio_init(GPIO_A);
    //(void)ret;
    //gpio_pin_config(UART2);
    //(void)ret;
    //ret = uart_init(UART2);
    //(void)ret;
    //while(1){
    //    printf("maneesh");
    //}
    spi_test();
}

void spi_test(){
    uint32_t ret = failed(RCC_E);
    gpio_init(GPIO_A);
    (void)ret;
    gpio_pin_config(SPI1_SD);
    (void)ret;
    spi_init(SPI_1);
    //sd_init();
    uint8_t commond[] = {0x40,0x0,0x0,0x0,0x0,0x95};
    uint8_t resp[6] = {0};
    for(int i=0;i<sizeof(commond);i++){
        resp[i] = spi_transmit(commond[i]);
        //resp[i] = spi_received();
    }
    (void)commond;
    (void)resp;
}

uint8_t spi1_master(void) {
uint8_t sendData = 0xa6; // Example data
    uint8_t receivedData = 0;

    // 1. Manually pull Chip Select Low (If you configured a CS pin)
    // GPIOA->ODR &= ~(1 << 4); 
    CS_LOW();
    // 2. Transmit and Receive
    while (!(((spi_def*)SPI1_BASE_ADDRESS)->SPI_SR & (1 << 1))); // Wait for TXE
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_DR = sendData;           // Start transmission

    while (!(spi1->SPI_SR & (1 << 0))); // Wait for RXNE (Data received)
    receivedData = (uint8_t)((spi_def*)SPI1_BASE_ADDRESS)->SPI_DR;
    // 3. Pull Chip Select High
    // GPIOA->ODR |= (1 << 4);

    // 5. Wait for BSY (Busy) to clear
    // This ensures the LAST clock pulse has physically finished on the wire.
    while (spi1->SPI_SR & (1 << 7));
    //delay(1000U);
     CS_HIGH();
    // 4. Verification
    if (receivedData == sendData) {
        // Success: Data went through MOSI -> Jumper -> MISO
    }
    return receivedData;
}

void spi_debug_master_arduino(){
    gpio_init(GPIO_A);
    gpio_pin_config(SPI1_SD);
    spi1 = (spi_def*)SPI1_BASE_ADDRESS;
    peripheral_clock_enable_register(SPI1);
    //spi_init(SPI_1);
        // 4. Configure spi1 Control Register 1 (CR1)
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 = 0;                        // Reset register
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 2);                // MSTR: Master Mode
    //spi1->SPI_CR1 |= (0 << 2);                // MSTR: Slave Mode
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (3 << 3);                // BR[2:0]: Baud rate = fPCLK/16
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 8) | (1 << 9);     // SSI & SSM: Software Slave Management
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (0 << 0) | (0 << 1);     // CPOL=0, CPHA=0 (Mode 0)

    // 5. Enable spi1
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 6);                // SPE: SPI Enable
    uint8_t recv = 0x0;
    while(1){
        recv = spi1_master();
        (void)recv;
    }
    
}

void spi1_slave(uint8_t dataToReply){
    // 1. Load the data into the buffer so it's ready for the Master's clock
    while (!( ((spi_def*)SPI1_BASE_ADDRESS)->SPI_SR & (1 << 1))); // Wait for TXE
     ((spi_def*)SPI1_BASE_ADDRESS)->SPI_DR = dataToReply;

    // 2. Wait for the Master to send 8 clock pulses
    // The RXNE flag will set once the Master has finished shifting
    while (!( ((spi_def*)SPI1_BASE_ADDRESS)->SPI_SR & (1 << 0))); // Wait for RXNE

    // 3. Return the data sent by the Master
    return (uint8_t) ((spi_def*)SPI1_BASE_ADDRESS)->SPI_DR;
}

void spi_debug_slave_arduino(){
    gpio_init(GPIO_A);
    gpio_pin_config(SPI1_SD);
    spi1 = (spi_def*)SPI1_BASE_ADDRESS;
    peripheral_clock_enable_register(SPI1);
    //spi_init(SPI_1);
        // 4. Configure spi1 Control Register 1 (CR1)
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 = 0;                        // Reset register
    //((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 2);                // MSTR: Master Mode
    //((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (0 << 2);                // MSTR: Slave Mode
    //((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (3 << 3);                // BR[2:0]: Baud rate = fPCLK/16
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 9);     // SSI & SSM: Software Slave Management
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (0 << 0) | (0 << 1);     // CPOL=0, CPHA=0 (Mode 0)

    // 5. Enable spi1
    ((spi_def*)SPI1_BASE_ADDRESS)->SPI_CR1 |= (1 << 6);                // SPE: SPI Enable
    uint8_t recv = 0x0;
    while(1){
        spi1_slave(0xa6);
    }
}

void boot_main(){
    uint32_t ret = failed(RCC_E);
    ret = rcc_init(RCC_PLLON);
    if(ret == failed(RCC_E)){
        assert();
    }
    spi_debug_slave_arduino();
    while(1);

}