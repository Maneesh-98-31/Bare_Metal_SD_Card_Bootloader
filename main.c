#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "sd.h"

void uart_test(){
    uint32_t ret = failed(RCC_E);
    gpio_init(GPIO_A);
    (void)ret;
    gpio_pin_config(UART2);
    (void)ret;
    ret = uart_init(UART2);
    (void)ret;
    while(1){
        printf("maneesh");
    }
}

void spi_test(){
    uint32_t ret = failed(RCC_E);
    gpio_init(GPIO_A);
    (void)ret;
    gpio_pin_config(SPI2);
    (void)ret;
    spi_init(SPI_1);
    sd_init();
}

void boot_main(){
    uint32_t ret = failed(RCC_E);
    ret = rcc_init(RCC_PLLON);
    if(ret == failed(RCC_E)){
        assert();
    }
    spi_test();
    

}