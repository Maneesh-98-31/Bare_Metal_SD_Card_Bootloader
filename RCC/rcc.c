#include "rcc.h"
#include "tool.h"
#include "error.h"


uint32_t rcc_init(CLOCK_SELECTION clock){
    uint32_t ret = failed(RCC_E);
    RCC = (rcc_def*)RCC_BASE_ADDRESS;
    ret = disable_rcc(clock);
    delay(100);
    ret = enable_rcc(clock);
    return ret;
}

uint32_t enable_rcc(CLOCK_SELECTION clock){
    uint32_t ret = failed(RCC_E);
    do{
        switch(clock)
        {
            case RCC_PLLSAION:{
                RCC->RCC_CR |= PLLSAION;
                delay(1000);
                if(((RCC->RCC_CR & PLLSAIRDY)) == PLLSAIRDY){
                    ret = pass(RCC_E);
                }
                break;
            }
            case RCC_PLLI2SON:
                RCC->RCC_CR |= PLLI2SON;
                delay(1000);
                if((RCC->RCC_CR & PLLI2SRDY) == PLLI2SRDY){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_PLLON:
                RCC->RCC_CR |= PLLON;
                delay(1000);
                if((RCC->RCC_CR & PLLRDY)==PLLRDY){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_CSSON:
                RCC->RCC_CR |= CSSON;
                delay(1000);
                break;
            case RCC_HSEON:
                RCC->RCC_CR |= HSEON;
                delay(1000);
                if((RCC->RCC_CR & HSERDY) == HSERDY){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_HSION:
                RCC->RCC_CR |= HSION;
                delay(1000);
                if(VALUE_AT(RCC->RCC_CR,HSIRDY)==SET){
                    ret = pass(RCC_E);
                }
                break;
            default:
                ret = failed(RCC_E);
                break;
        }
    }while(0);
    return ret;
}


uint32_t disable_rcc(CLOCK_SELECTION clock){
    uint32_t ret = failed(RCC_E);
    do{
        switch(clock)
        {
            case RCC_PLLSAION:{
                RCC->RCC_CR &= ~PLLSAION;
                delay(1000);
                if(((RCC->RCC_CR & ~PLLSAIRDY))==CLEAR){
                    ret = pass(RCC_E);
                }
                break;
            }
            case RCC_PLLI2SON:
                RCC->RCC_CR &= ~PLLI2SON;
                delay(1000);
                if((RCC->RCC_CR & ~PLLI2SRDY)==CLEAR){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_PLLON:
                RCC->RCC_CR &= ~PLLON;
                delay(1000);
                if((RCC->RCC_CR & ~PLLRDY)==CLEAR){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_CSSON:
                RCC->RCC_CR &= ~CSSON;
                delay(1000);
                break;
            case RCC_HSEON:
                RCC->RCC_CR &= ~HSEON;
                delay(1000);
                if((RCC->RCC_CR & ~HSERDY)==CLEAR){
                    ret = pass(RCC_E);
                }
                break;
            case RCC_HSION:
                RCC->RCC_CR &= ~HSION;
                delay(1000);
                if((RCC->RCC_CR & ~HSIRDY)==CLEAR){
                    ret = pass(RCC_E);
                }
                break;
            default:
                ret = failed(RCC_E);
                break;
        }
    }while(0);
    return ret;
}

uint32_t get_sysclock(void){
	uint32_t clk_src = ((RCC)->RCC_CFGR >> SW1) & 0x3;
	if(clk_src == 0) return 16000000;
	if(clk_src == 1) return 8000000;
	if(clk_src == 2) return 168000000;

	return 0;
}

void peripheral_clock_enable_register(INTERFACE_SELECTION interface){
    //uint32_t ret = failed(RCC_E);
    do{
        switch(interface){
            case GPIOA:{
                RCC->RCC_AHB1RSTR |= GPIOARST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOARST;
                RCC->RCC_AHB1ENR |= GPIOAEN;                    
                break;
            }
            case GPIOB:{
                RCC->RCC_AHB1RSTR |= GPIOBRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOBRST;                  
                RCC->RCC_AHB1ENR |= GPIOBEN;                    
                break;
            }
            case GPIOC:{
                RCC->RCC_AHB1RSTR |= GPIOCRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOCRST;
                RCC->RCC_AHB1ENR |= GPIOCEN;                    
                break;
            }
            case GPIOD:{
                RCC->RCC_AHB1RSTR |= GPIODRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIODRST;   
                RCC->RCC_AHB1ENR |= GPIODEN;                    
                break;
            }
            case GPIOE:{
                RCC->RCC_AHB1RSTR |= GPIOERST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOERST;                  
                RCC->RCC_AHB1ENR |= GPIOEEN;                    
                break;
            }
            case GPIOF:{
                RCC->RCC_AHB1RSTR |= GPIOFRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOFRST;
                RCC->RCC_AHB1ENR |= GPIOFEN;                    
                break;
            }
            case GPIOG:{
                RCC->RCC_AHB1RSTR |= GPIOGGRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOGGRST; 
                RCC->RCC_AHB1ENR |= GPIOGEN;                    
                break;
            }
            case GPIOH:{
                RCC->RCC_AHB1RSTR |= GPIOHRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOHRST;
                RCC->RCC_AHB1ENR |= GPIOHEN;                    
                break;
            }
            case GPIOI:{
                RCC->RCC_AHB1RSTR |= GPIOIRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOIRST;
                RCC->RCC_AHB1ENR |= GPIOIEN;                    
                break;
            }
            case GPIOJ:{
                RCC->RCC_AHB1RSTR |= GPIOJRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOJRST;
                RCC->RCC_AHB1ENR |= GPIOJEN;                    
                break;
            }
            case GPIOK:{
                RCC->RCC_AHB1RSTR |= GPIOKRST;                  
                delay(0X1000);
                RCC->RCC_AHB1RSTR &= ~GPIOKRST;
                RCC->RCC_AHB1ENR |= GPIOKEN;                    
                break;
            }
            case USART6:{
                RCC->RCC_APB2RSTR |= USART6RST;
                delay(0x1000);
                RCC->RCC_APB2RSTR &= ~USART6RST;
                RCC->RCC_APB2ENR |= USART6EN;
            }
            case UART1:{
                RCC->RCC_APB2RSTR |= USART1RST;
                delay(0x1000);
                RCC->RCC_APB2RSTR &= ~USART1RST;
                RCC->RCC_APB2ENR |= USART1EN;
                break;
            }
            case UART2:{
                RCC->RCC_APB1RSTR |= UART2RST;
                delay(0x1000);
                RCC->RCC_APB1RSTR &= ~UART2RST;
                RCC->RCC_APB1ENR |= UART2EN;
                break;
            }
            case SPI1:{
                RCC->RCC_APB2RSTR |= SPI1RST;
                delay(0x1000);
                RCC->RCC_APB2RSTR &= ~SPI1RST;
                RCC->RCC_APB2ENR |= SPI1EN;
                break;
            }
            case SPI2:{
                RCC->RCC_APB1RSTR |= SPI2RST;
                delay(0x1000);
                RCC->RCC_APB1RSTR &= ~SPI2RST;
                RCC->RCC_APB1ENR |= SPI2EN;
                break;
            }
            case SPI3:{
                RCC->RCC_APB1RSTR |= SPI3RST;
                delay(0x1000);
                RCC->RCC_APB1RSTR &= ~SPI3RST;
                RCC->RCC_APB1ENR |= SPI3EN;
                break;
            }
            case CRC:{
                RCC->RCC_AHB1RSTR |= CRCRST;
                delay(0x1000);
                RCC->RCC_AHB1RSTR &= ~CRCRST;
                RCC->RCC_AHB1ENR |= CRCEN;
            }
            default:
                //ret = failed(RCC_E);
                break;
        }

    }while(0);
}



