#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"

void boot_main(){
    uint32_t ret = failed(USART_E);
    ret = uart_init(UART1);
    while(1);

}