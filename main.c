#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"

void boot_main(){
    uint32_t ret = failed(RCC_E);
    ret = rcc_init(RCC_PLLON);
    if(ret == failed(RCC_E)){
        while(1);
    }
    ret = failed(USART_E);
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