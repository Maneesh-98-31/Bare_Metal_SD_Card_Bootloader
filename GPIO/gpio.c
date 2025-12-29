#include "stdint.h"
#include "gpio.h"
#include "rcc.h"
#include "error.h"
#include "tool.h"



uint32_t gpio_init(GPIOX gpiox){
    uint32_t ret = failed(GPIO_E);
    switch (gpiox){
        case GPIO_A:
            gpio_reg = (gpio_def*)GPIOA_BASE_ADDRESS;
            GPIOA_CLOCK_ENABLE();
            ret = pass(GPIO_E);
            break;
        case GPIO_B:
            gpio_reg = (gpio_def*)GPIOB_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_C:
            gpio_reg = (gpio_def*)GPIOC_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_D:
            gpio_reg = (gpio_def*)GPIOD_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_XE:
            gpio_reg = (gpio_def*)GPIOE_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_F:
            gpio_reg = (gpio_def*)GPIOF_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_G:
            gpio_reg = (gpio_def*)GPIOG_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_H:
            gpio_reg = (gpio_def*)GPIOH_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_I:
            gpio_reg = (gpio_def*)GPIOI_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_J:
            gpio_reg = (gpio_def*)GPIOJ_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        case GPIO_K:
            gpio_reg = (gpio_def*)GPIOK_BASE_ADDRESS;
            ret = pass(GPIO_E);
            break;
        default:
            ret = failed(GPIO_E);
            break;
    }
    
    return ret;

}


uint32_t gpio_pin_config(INTERFACE_SELECTION interface){
    uint32_t ret = failed(GPIO_E);

    switch(interface){
        case UART1:{
            //  Configure PA9 (TX) and PA10 (RX) as Alternate Function AF7
            uint32_t temp = ( MODER9_ALTERNATE_FUNCTION_MODE | MODER10_ALTERNATE_FUNCTION_MODE);
            (gpio_reg)->GPIOx_MODER |= temp;
            temp  = (PA1_AFRL9 | PA1_AFRL10);
            //  Select AF7 (USART1) in AFRL register (PA8, PA9 use AFRL)
            delay(1000);
            (gpio_reg)->GPIOx_AFRL |=  temp;
            ret = pass(GPIO_E);
            break;
        }
        case UART2:{
            GPIOA_CLOCK_RESET();
            uint32_t temp = (MODER2_ALTERNATE_FUNCTION_MODE         \
                            | MODER3_ALTERNATE_FUNCTION_MODE);
            (gpio_reg)->GPIOx_MODER |= temp;
            temp = (PA2_AFRL7 | PA3_AFRL7);
            delay(1000);
            (gpio_reg)->GPIOx_AFRL |= (AFRL2_PA7 | AFRL3_PA7);
            ret = pass(GPIO_E);
            break;
        }
        case SPI1_SD:{
            GPIOA_CLOCK_RESET();
            uint32_t modar_select = (MODER5_ALTERNATE_FUNCTION_MODE  \
                                    | MODER6_ALTERNATE_FUNCTION_MODE \
                                    | MODER7_ALTERNATE_FUNCTION_MODE \
                                    | MODER4_GENERAL_PURPOSE_OUTPUT_MODE
                                );
            uint32_t pin_select = ((5 << 4*6) | (5 << 4*5) | (5 << 4*7)); //(PA5_AFRL7 | PA6_AFRL7 | PA7_AFRL7);
            uint32_t speed = (VERY_HIGH_SPEED << MODER5)                \
                            | (VERY_HIGH_SPEED << MODER6)               \
                            | (VERY_HIGH_SPEED << MODER7)               \
                            | (VERY_HIGH_SPEED << MODER4)
                            ;
            uint32_t otyper = ~(OT5 | OT7 | OT4);
            uint32_t pull_up_pull_down_register = (PULL_UP << MODER6);
            (gpio_reg)->GPIOx_MODER |= modar_select;
            (gpio_reg)->GPIOx_AFRL |= pin_select;
            (gpio_reg)->GPIOx_OSPEEDR |= speed;
            (gpio_reg)->GPIOx_OTYPER &= otyper;
            (gpio_reg)->GPIOx_ODR |= (1 << 4);
            //(gpio_reg)->GPIOx_PUPDR |= pull_up_pull_down_register;
            break;
        }

        
        default:
            ret = failed(GPIO_E);
            break;
    }
    return ret;
}
