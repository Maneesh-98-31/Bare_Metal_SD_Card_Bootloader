#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "rcc.h"


static usart_def* uart;


uint32_t uart_init(INTERFACE_SELECTION interface){

    uint32_t ret = failed(USART_E);
    switch(interface){
        case UART1:
            uart = (usart_def*)USART1_BASE_ADDRESS;
            peripheral_clock_enable_register(UART1);
            //uart->USART_CR2 |= CLKEN;
            uart->USART_CR2 &= ~(STOP);
            ret = pass(USART_E);
            break;
        case UART2:
            uart = (usart_def*)USART2_BASE_ADDRESS;
            peripheral_clock_enable_register(UART2);
            //uart->USART_CR2 |= CLKEN;
            uart->USART_CR2 &= ~(STOP);
            ret = pass(USART_E);
            break;
        default:
            ret = failed(USART_E);
    }
    
    uart->USART_CR1 |= (UE | RE | TE);
    uart->USART_BRR = get_sysclock()/CBR_115200;
    return ret;
}


void printf_e(const char *str){
    if(str == 0){
        return;
    }
    while(*str){
        uart_send_char(*str);
        str++;
    }
}


void uart_send_char(char c){
    while((uart->USART_SR & TC) != TC){
        // do nothing
    }
    uart->USART_DR = c;
}