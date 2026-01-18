#ifndef _UART_H_
#define _UART_H_

#include "stdint.h"
#include "rcc.h"

typedef struct{
    volatile uint32_t USART_SR;
    volatile uint32_t USART_DR;
    volatile uint32_t USART_BRR;
    volatile uint32_t USART_CR1;
    volatile uint32_t USART_CR2;
    volatile uint32_t USART_CR3;
    volatile uint32_t USART_GTPR;
}__attribute__((packed)) usart_def;


#define USART6_BASE_ADDRESS                         0x40011400
#define USART1_BASE_ADDRESS                         0x40011000
#define UART8_BASE_ADDRESS                          0x40007c00      
#define UART7_BASE_ADDRESS                          0x40007800      
#define UART5_BASE_ADDRESS                          0x40005000      
#define UART4_BASE_ADDRESS                          0x40004c00      
#define USART3_BASE_ADDRESS                         0x40004800      
#define USART2_BASE_ADDRESS                         0x40004400      


uint32_t uart_init(INTERFACE_SELECTION);
void printf_e(const char*);
void uart_send_char(char);


#define CBR_110 						     110
#define CBR_300 						     300
#define CBR_600 						     600
#define CBR_1200						    1200
#define CBR_2400						    2400
#define CBR_4800						    4800
#define CBR_9600						    9600
#define CBR_14400						   14400
#define CBR_19200						   19200
#define CBR_38400						   38400
#define CBR_56000						   56000
#define CBR_57600						   57600
#define CBR_115200						  115200
#define CBR_128000						  128000
#define CBR_256000						  256000


#define CTS                         (1 << 9)
#define LBD                         (1 << 8)
#define TXE                             (1 << 7)
#define TC                              (1 << 6)
#define RXNE                            (1 << 5)
#define IDLE                            (1 << 4)
#define ORE                             (1 << 3)
#define NF                            (1 << 2)
#define FE                            (1 << 1)
#define PE                          (1 << 0)

#define DIV_Mantissa                (1 << 4)
#define DIV_Fraction                (1 << 0)



#define SBK                     (1 << 0)
#define RWU                     (1 << 1)
#define RE                      (1 << 2)
#define TE                      (1 << 3)
#define IDLEIE                  (1 << 4)
#define RXNEIE                  (1 << 5)
#define TCIE                    (1 << 6)
#define TXEIE                   (1 << 7)
#define PEIE                    (1 << 8)
#define PS                      (1 << 9)
#define PCE                     (1 << 10)
#define WAKE                    (1 << 11)
#define M                       (1 << 12)
#define UE                      (1 << 13)
#define OVER8                   (1 << 15)



#define ADD                     (1 << 0)
#define LBDL                    (1 << 5)
#define LBDIE                   (1 << 6)
#define LBCL                    (1 << 8)
#define CPHA                    (1 << 9)
#define CPOL                    (1 << 10)
#define CLKEN                   (1 << 11)
#define STOP                    (1 << 12)
#define LINEN                   (1 << 14)


#define EIE                     (1 << 0)
#define IREN                    (1 << 1)
#define IRLP                    (1 << 2)
#define HDSEL                   (1 << 3)
#define NACK                    (1 << 4)
#define SCEN                    (1 << 5)
#define DMAR                    (1 << 6)
#define DMAT                    (1 << 7)
#define RTSE                    (1 << 8)
#define CTSE                    (1 << 9)
#define CTSIE                   (1 << 10)
#define ONEBIT                  (1 << 11)


#define PSC                     (1 << 0)
#define GT                      (1 << 0)



#endif