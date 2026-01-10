#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "sd.h"

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
    sd_init();
    uint8_t write_buffer[512];
    uint8_t read_buffer[512];
    mem_clear(write_buffer,sizeof(write_buffer));
    mem_clear(read_buffer,sizeof(read_buffer));
    for(uint32_t i=0;i<SD_BLOCK_SIZE;i++){
        write_buffer[i] = 0xa0 | (i%0x10);
    }
    sd_write_block(0,write_buffer);
    sd_read_block(0,read_buffer);
    while(1);
}

void boot_main(){
    uint32_t ret = failed(RCC_E);
    ret = rcc_init(RCC_PLLON);
    if(ret == failed(RCC_E)){
        assert();
    }
    spi_test();
    

}