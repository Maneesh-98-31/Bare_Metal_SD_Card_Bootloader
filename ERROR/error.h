#ifndef _ERROR_H_
#define _ERROR_H_

#include "stdint.h"

typedef enum{
    RCC_E           =       (1),
    USART_E         =       (RCC_E + 1),
    GPIO_E          =       (RCC_E + 2),

}module;


#define FAIL        0xfafa
#define PASS        0xafaf


#define RETURN_IF_ERRER(ret,module)                 if(ret == failed(USART_E)){return ret;}


uint32_t failed(module m);
uint32_t pass(module m);


#endif