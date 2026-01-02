#ifndef _RCC_H_
#define _RCC_H_

#include "stdint.h"
#include "tool.h"

typedef struct{
    volatile uint32_t RCC_CR;                                   // 0x0
    volatile uint32_t RCC_PLLCFGR;                              // 0x4
    volatile uint32_t RCC_CFGR;                                 // 0x8
    volatile uint32_t RCC_CIR;                                  // 0xC
    volatile uint32_t RCC_AHB1RSTR;                             // 0x10
    volatile uint32_t RCC_AHB2RSTR;                             // 0x14
    volatile uint32_t RCC_AHB3RSTR;                             // 0x18
    volatile uint32_t RESERVED1[1];                             // 0x1C 
    volatile uint32_t RCC_APB1RSTR;                             // 0x20
    volatile uint32_t RCC_APB2RSTR;                             // 0x24
    volatile uint32_t RESERVED2[2];                             // 0x28 + 0x2C
    volatile uint32_t RCC_AHB1ENR;                              // 0x30
    volatile uint32_t RCC_AHB2ENR;                              // 0x34
    volatile uint32_t RCC_AHB3ENR;                              // 0x38
    volatile uint32_t RESERVED3[1];                             // 0x3C
    volatile uint32_t RCC_APB1ENR;                              // 0x40
    volatile uint32_t RCC_APB2ENR;                              // 0x44
    volatile uint32_t RESERVED4[2];                             // 0x48 + 0x4C
    volatile uint32_t RCC_AHB1LPENR;                            // 0x50
    volatile uint32_t RCC_AHB2LPENR;                            // 0x54
    volatile uint32_t RCC_AHB3LPENR;                            // 0x58
    volatile uint32_t RESERVED5[1];                             // 0x5C
    volatile uint32_t RCC_APB1LPENR;                            // 0x60
    volatile uint32_t RCC_APB2LPENR;                            // 0x64
    volatile uint32_t RESERVED6[2];                             // 0x68 + 0x6C
    volatile uint32_t RCC_BDCR;                                 // 0x70
    volatile uint32_t RCC_CSR;                                  // 0x74
    volatile uint32_t RCC_RESERVED7[2];                         // 0x78 + 0x7C
    volatile uint32_t RCC_SSCGR;                                // 0x80
    volatile uint32_t RCC_PLLI2SCFGR;                           // 0x84
    volatile uint32_t RCC_PLLSAICFGR;                           // 0x88
    volatile uint32_t RCC_DCKCFGR;                              // 0x88
}__attribute__((packed)) rcc_def;



typedef enum{
    RCC_PLLSAION,
    RCC_PLLI2SON,
    RCC_PLLON,
    RCC_CSSON,
    RCC_HSEON,
    RCC_HSION
}CLOCK_SELECTION;



typedef enum{
    GPIOK,
    GPIOJ,
    GPIOI,
    GPIOH,
    GPIOG,
    GPIOE,
    GPIOD,
    GPIOC,
    GPIOB,
    GPIOA,
    GPIOF,
    SPI6,
    SPI5,
    SPI4,
    SPI1,
    USART6,
    UART1,
    UART8,
    UART7,
    CAN2,
    CAN1,
    I2C3,
    I2C2,
    UART5,
    UART4,
    UART3,
    UART2,
    SPI3,
    SPI2,
    SPI1_SD
}INTERFACE_SELECTION;



typedef enum{
    AHB1,
    AHB2,
    AHB3,
    APB1,
    APB2
}BUS_SELECTION;

#define RCC_BASE_ADDRESS        0x40023800


#define ENABLE_PLL(rcc)         (rcc->RCC_CR |= (1 << 24));


static rcc_def *RCC;

uint32_t enable_rcc(CLOCK_SELECTION);
uint32_t disable_rcc(CLOCK_SELECTION);
uint32_t rcc_init(CLOCK_SELECTION);
void peripheral_clock_enable_register(INTERFACE_SELECTION);
void peripheral_reset_register(INTERFACE_SELECTION);
BUS_SELECTION find_interface(INTERFACE_SELECTION);
uint32_t get_sysclock(void);


#define GPIOA_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 0))
#define GPIOB_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 1))
#define GPIOC_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 2))
#define GPIOD_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 3))
#define GPIOE_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 4))
#define GPIOF_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 5))
#define GPIOG_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 6))
#define GPIOH_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 7))
#define GPIOI_CLOCK_ENABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR |= (1 << 8))

#define GPIOA_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 0))
#define GPIOB_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 1))
#define GPIOC_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 2))
#define GPIOD_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 3))
#define GPIOE_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 4))
#define GPIOF_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 5))
#define GPIOG_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 6))
#define GPIOH_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 7))
#define GPIOI_CLOCK_DISABLE() 			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1ENR &= ~(1 << 8))

#define GPIOA_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<0)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<1)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<2)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<3)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<4)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOF_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<5)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<5)); }while(0)
#define GPIOG_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<6)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<6)); }while(0)
#define GPIOH_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<7)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<7)); }while(0)
#define GPIOI_CLOCK_RESET()				do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR |= (1<<8)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_AHB1RSTR &= ~(1<<8)); }while(0)

#define USART1_CLOCK_ENABLE()			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<4))
#define USART1_CLOCK_DISABLE()			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR &= ~(1<<4))


#define USART2_CLOCK_ENABLE()			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<17))
#define USART2_CLOCK_DISABLE()			(((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR &= ~(1<<17))


#define SPI3_CLOCK_RESET()              do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1RSTR |= (1<<15)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1RSTR &= ~(1<<15)); }while(0)
#define SPI2_CLOCK_RESET()              do{ (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1RSTR |= (1<<14)); delay(1000); (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1RSTR &= ~(1<<14)); }while(0)

#define SPI1_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<12))
#define SPI2_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1ENR |= (1<<17))
#define SPI3_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB1ENR |= (1<<17))
#define SPI4_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<17))
#define SPI5_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<17))
#define SPI6_CLOCK_ENABLE()             (((rcc_def*)RCC_BASE_ADDRESS)->RCC_APB2ENR |= (1<<17))

typedef enum{
    PLLSAIRDY       = (1 << 29 )   ,
    PLLSAION        = (1 << 28 )   ,
    PLLI2SRDY       = (1 << 27 )   ,
    PLLI2SON        = (1 << 26 )   ,
    PLLRDY          = (1 << 25 )   ,
    PLLON           = (1 << 24 )   ,
    CSSON           = (1 << 19 )   ,
    HSEBYP          = (1 << 18 )   ,
    HSERDY          = (1 << 17 )   ,
    HSEON           = (1 << 16 )   ,
    HSIRDY          = (1 << 1  )   ,
    HSION           = (1 << 0  )
}RCC_CR;


typedef enum{
    PLLQ3           = ( 1<< 27)        ,
    PLLQ2           = ( 1<< 26)        ,
    PLLQ1           = ( 1<< 25)        ,
    PLLQ0           = ( 1<< 24)        ,
    PLLSRC          = ( 1<< 22)        ,
    PLLP1           = ( 1<< 17)        ,
    PLLP0           = ( 1<< 16)        ,
    PLLN            = ( 1<< 6 )        ,
    PLLM5           = ( 1<< 5 )        ,
    PLLM4           = ( 1<< 4 )        ,
    PLLM3           = ( 1<< 3 )        ,
    PLLM2           = ( 1<< 2 )        ,
    PLLM1           = ( 1<< 1 )        ,
    PLLM0           = ( 1<< 0 )
}RCC_PLLCFGR;



typedef enum{
    MCO2            =  (1 << 30)            ,
    MCO2_PRE        =  (1 << 27)            ,
    MCO1_PRE        =  (1 << 24)            ,
    I2SSCR          =  (1 << 23)            , 
    MCO1            =  (1 << 21)            ,
    RTCPRE          =  (1 << 16)            ,
    PPRE2           =  (1 << 13)            ,
    PPRE1           =  (1 << 10)            ,
    HPRE            =  (1 << 5 )            ,
    SWS1            =  (1 << 3 )            ,
    SWS0            =  (1 << 2 )            ,
    SW1             =  (1 << 1 )            ,
    SW0             =  (1 << 0 )
}RCC_CFGR;


typedef enum{
    CSSC            = (1 << 23)            ,
    PLLSAIRDYC      = (1 << 22)            ,
    PLLI2SRDYC      = (1 << 21)            ,
    PLLRDYC         = (1 << 20)            ,
    HSERDYC         = (1 << 19)            ,
    HSIRDYC         = (1 << 18)            ,
    LSERDYC         = (1 << 17)            ,
    LSIRDYC         = (1 << 16)            ,
    PLLSAIRDYIE     = (1 << 14)            ,
    PLLI2SRDYIE     = (1 << 13)            ,
    PLLRDYIE        = (1 << 12)            ,
    HSERDYIE        = (1 << 11)            ,
    HSIRDYIE        = (1 << 10)            ,
    LSERDYIE        = (1 << 9 )            ,
    LSIRDYIE        = (1 << 8 )            ,
    CSSF            = (1 << 7 )            ,
    PLLSAIRDYF      = (1 << 6 )            ,
    PLLI2SRDYF      = (1 << 5 )            ,
    PLLRDYF         = (1 << 4 )            ,
    HSERDYF         = (1 << 3 )            ,
    HSIRDYF         = (1 << 2 )            ,
    LSERDYF         = (1 << 1 )            ,
    LSIRDYF         = (1 << 0 )
}RCC_CIR;



typedef enum{
    OTGHSRST        = (1 << 29),
    ETHMACRST       = (1 << 25),
    DMA2DRST        = (1 << 23),
    DMA2RST         = (1 << 22),
    DMA1RST         = (1 << 21),
    CRCRST          = (1 << 11),
    GPIOKRST        = (1 << 10),
    GPIOJRST        = (1 << 9),
    GPIOIRST        = (1 << 8),
    GPIOHRST        = (1 << 7),
    GPIOGGRST       = (1 << 6),
    GPIOFRST        = (1 << 5),
    GPIOERST        = (1 << 4),
    GPIODRST        = (1 << 3),
    GPIOCRST        = (1 << 2),
    GPIOBRST        = (1 << 1),
    GPIOARST        = (1 << 0)
}RCC_AHB1RSTR;


typedef enum{
    OTGFSRST        =   (1 << 7),
    RNGRST          =   (1 << 6),
    HASHRST         =   (1 << 5),
    CRYPRST         =   (1 << 4),
    DCMIRST         =   (1 << 0)
}RCC_AHB2RSTR;


typedef enum{
    FMCRST = 0
}RCC_AHB3RSTR;

/*
typedef enum{
    UART8RST =      (1 <<  31),
    UART7RST =      (1 << 30), 
    DACRST =        (1 << 29),
    PWRRST =        (1 << 28),
    CAN2RST =       (1 << 26),
    CAN1RST =       (1 << 25),
    I2C3RST =       (1 << 23),
    I2C2RST =       (1 << 22),
    I2C1RST =       (1 << 21),
    UART5RST =      (1 << 20),
    UART4RST =      (1 << 19),
    UART3RST =      (1 << 18),
    UART2RST =      (1 << 17),
    SPI3RST =       (1 << 15),
    SPI2RST =       (1 << 14),
    WWDGRST =       (1 << 11),
    TIM14RST =      (1 << 8),
    TIM13RST =      (1 << 7),
    TIM12RST =      (1 <<  6),
    TIM7RST =       (1 << 5),
    TIM6RST =       (1 <<  4),
    TIM5RST =       (1 << 3),
    TIM4RST =       (1 << 2),
    TIM3RST =       (1 << 1),
    TIM2RST =       (1 << 0)
}RCC_APB1RSTR;
*/
typedef enum{
    UART8RST=       ( 1 <<  31),
    UART7RST=       ( 1 <<  30), 
    DACRST =        ( 1 <<  29),
    PWRRST =        ( 1 <<  28),
    CAN2RST =       ( 1 <<  26),
    CAN1RST =       ( 1 <<  25),
    I2C3RST =       ( 1 <<  23),
    I2C2RST =       ( 1 <<  22),
    I2C1RST =       ( 1 <<  21),
    UART5RST =      ( 1 <<  20),
    UART4RST =      ( 1 <<  19),
    UART3RST =      ( 1 <<  18),
    UART2RST =      ( 1 <<  17),
    SPI3RST =       ( 1 <<  15),
    SPI2RST =       ( 1 <<  14),
    WWDGRST =       ( 1 <<  11),
    TIM14RST=       ( 1 <<   8),
    TIM13RST=       ( 1 <<   7),
    TIM12RST=       ( 1 <<   6),
    TIM7RST =       ( 1 <<   5),
    TIM6RST =       ( 1 <<   4),
    TIM5RST =       ( 1 <<   3),
    TIM4RST =       ( 1 <<   2),
    TIM3RST =       ( 1 <<   1),
    TIM2RST =       ( 1 <<   0)
}RCC_APB1RSTR;


typedef enum{
    LTDCRST     =   (1 << 26),
    SAI1RST     =   (1 << 22),
    SPI6RST     =   (1 << 21),
    SPI5RST     =   (1 << 20),
    TIM11RST    =   (1 << 18),
    TIM10RST    =   (1 << 17),
    TIM9RST     =   (1 << 16),
    SYSCFG      =   (1 << 14),
    SPI4RST     =   (1 << 13),
    SPI1RST     =   (1 << 12),
    SDIORST     =   (1 << 11),
    ADCRST      =   (1 << 8),
    USART6RST   =   (1 << 5),
    USART1RST   =   (1 << 4),
    TIM8RST     =   (1 << 1),
    TIM1RST     =   (1 << 0)
}RCC_APB2RSTR;


typedef enum{
    OTGHSULPIEN     =       (1 << 30),
    OTGHSEN         =       (1 << 29),
    ETHMACPTPEN     =       (1 << 28),
    ETHMACRXEN      =       (1 << 27),
    ETHMACTXEN      =       (1 << 26),
    ETHMACEN        =       (1 << 25),
    DMA2DEN         =       (1 << 23),
    DMA2EN          =       (1 << 22),
    DMA1EN          =       (1 << 21),
    CCMDATARAMEN    =       (1 << 20),
    BKPSRAMEN       =       (1 << 18),
    CRCEN           =       (1 << 12),
    GPIOKEN         =       (1 << 10),
    GPIOJEN         =       (1 << 9),
    GPIOIEN         =       (1 << 8),
    GPIOHEN         =       (1 << 7),
    GPIOGEN         =       (1 << 6),
    GPIOFEN         =       (1 << 5),
    GPIOEEN         =       (1 << 4),
    GPIODEN         =       (1 << 3),
    GPIOCEN         =       (1 << 2),
    GPIOBEN         =       (1 << 1),
    GPIOAEN         =       (1 << 0)
}RCC_AHB1ENR;

typedef enum{
    OTGFSEN = (1 << 7),
    RNGEN = (1 << 6),
    HASHEN = (1 << 5),
    CRYPEN = (1 << 4),
    DCMIEN = (1 << 0)
}RCC_AHB2ENR;

typedef enum{
    FMCEN = (1 << 0)
}RCC_AHB3ENR;

typedef enum{
    UART8EN =   (1 << 31),
    UART7EN =   (1 << 30),
    DACEN =     (1 << 29),
    PWREN =     (1 << 28),
    CAN2EN =    (1 << 26),
    CAN1EN =    (1 << 25),
    I2C3EN =    (1 << 23),
    I2C2EN =    (1 << 22),
    I2C1EN =    (1 << 21),
    UART5EN =   (1 << 20),
    UART4EN =   (1 << 19),
    UART3EN =  (1 << 18),
    UART2EN =  (1 << 17),
    SPI3EN =    (1 << 15),
    SPI2EN =    (1 << 14),
    WWDGEN =    (1 << 11),
    TIM14EN =   (1 << 8),
    TIM13EN =   (1 << 7),
    TIM12EN =   (1 << 6),
    TIM7EN =    (1 << 5),
    TIM6EN =    (1 << 4),
    TIM5EN =    (1 << 3),
    TIM4EN =    (1 << 2),
    TIM3EN =    (1 << 1),
    TIM2EN =    (1 << 0)
}RCC_APB1ENR;

typedef enum{
    
    LTDCEN              =       (1 << 26),
    SAI1EN              =       (1 << 22),
    SPI6EN              =       (1 << 21),
    SPI5EN              =       (1 << 20),
    TIM11EN             =       (1 << 18),
    TIM10EN             =       (1 << 17),
    TIM9EN              =       (1 << 16),
    SYSCFGEN            =       (1 << 14),
    SPI4EN              =       (1 << 13),
    SPI1EN              =       (1 << 12),
    SDIOEN              =       (1 << 11),
    ADC3EN              =       (1 << 10),
    ADC2EN              =       (1 << 9),
    ADC1EN              =       (1 << 8),
    USART6EN            =       (1 << 5),
    USART1EN            =       (1 << 4),
    TIM8EN              =       (1 << 1),
    TIM1EN              =       (1 << 0)
}RCC_APB2ENR;

typedef enum{
    OTGHSULPILPEN   =       (1 << 30),
    OTGHSLPEN       =       (1 << 29),
    ETHPTPLPEN      =       (1 << 28),
    ETHRXLPEN       =       (1 << 27),
    ETHTXLPEN       =       (1 << 26),
    ETHMACLPEN      =       (1 << 25),
    DMA2DLPEN       =       (1 << 23),
    DMA2LPEN        =       (1 << 22),
    DMA1LPEN        =       (1 << 21),
    SRAM3LPEN       =       (1 << 19),
    BKPSRAMLPEN     =       (1 << 18),
    SRAM2LPEN       =       (1 << 17),
    SRAM1LPEN       =       (1 << 16),
    FLITFLPEN       =       (1 << 15),
    CRCLPEN         =       (1 << 12),
    GPIOKLPEN       =       (1 << 10),
    GPIOIJLPEN      =       (1 << 9),
    GPIOILPEN       =       (1 << 8),
    GPIOHLPEN       =       (1 << 7),
    GPIOGGLPEN      =       (1 << 6),
    GPIOFLPEN       =       (1 << 5),
    GPIOELPEN       =       (1 << 4),
    GPIODLPEN       =       (1 << 3),
    GPIOCLPEN       =       (1 << 2),
    GPIOBLPEN       =       (1 << 1),
    GPIOALPEN       =       (1 << 0)
}RCC_AHB1LPENR;


typedef enum{
    OTGFSLPEN       =       (1 << 7),
    RNGLPEN         =       (1 << 6),
    HASHLPEN        =       (1 << 5),
    CRYPLPEN        =       (1 << 4),
    DCMILPEN        =       (1 << 0)
}RCC_AHB2LPENR;

typedef enum{
    FMCLPEN         =       (1 << 0)
}RCC_AHB3LPENR;

typedef enum{
    UART8LPEN       =       (1 << 31),
    UART7LPEN       =       (1 << 30),
    DACLPEN         =       (1 << 29),
    PWRLPEN         =       (1 << 28),
    CAN2LPEN        =       (1 << 26),
    CAN1LPEN        =       (1 << 25),
    I2C3LPEN        =       (1 << 23),
    I2C2LPEN        =       (1 << 22),
    I2C1LPEN        =       (1 << 21),
    UART5LPEN       =       (1 << 20),
    UART4LPEN       =       (1 << 19),
    USART3LPEN      =       (1 << 18),
    USART2LPEN      =       (1 << 17),
    SPI3LPEN        =       (1 << 15),
    SPI2LPEN        =       (1 << 14),
    WWDGLPEN        =       (1 << 11),
    TIM14LPEN       =       (1 << 8),
    TIM13LPEN       =       (1 << 7),
    TIM12LPEN       =       (1 << 6),
    TIM7LPEN        =       (1 << 5),
    TIM6LPEN        =       (1 << 4),
    TIM5LPEN        =       (1 << 3),
    TIM4LPEN        =       (1 << 2),
    TIM3LPEN        =       (1 << 1),
    TIM2LPEN        =       (1 << 0)
}RCC_APB1LPENR;


typedef enum{
    LTDCLPEN        =       (1 << 26),
    SAI1LPEN        =       (1 << 22),
    SPI6LPEN        =       (1 << 21),
    SPI5LPEN        =       (1 << 20),
    TIM11LPEN       =       (1 << 18),
    TIM10LPEN       =       (1 << 17),
    TIM9LPEN        =       (1 << 16),
    SYSCFGLPEN      =       (1 << 14),
    SPI4LPEN        =       (1 << 13),
    SPI1LPEN        =       (1 << 12),
    SDIOLPEN        =       (1 << 11),
    ADC3LPEN        =       (1 << 10),
    ADC2LPEN        =       (1 << 9),
    ADC1LPEN        =       (1 << 8),
    USART6LPEN      =       (1 << 5),
    USART1LPEN      =       (1 << 4),
    TIM8LPEN        =       (1 << 1),
    TIM1LPEN        =       (1 << 0)
}RCC_APB2LPENR;


typedef enum{
    BDRST           =       (1 << 16),
    RTCEN           =       (1 << 15),
    RTCSEL          =       (1 << 8),
    LSEBYP          =       (1 << 2),
    LSERDY          =       (1 << 1),
    LSEON           =       (1 << 0)
}RCC_BDCR;


typedef enum{
    LPWRRSTF        =       (1 << 31),
    WWDGRSTF        =       (1 << 30),
    IWDGRSTF        =       (1 << 29),
    SFTRSTF         =       (1 << 28),
    PORRSTF         =       (1 << 27),
    PINRSTF         =       (1 << 26),
    BORRSTF         =       (1 << 25),
    RMVF            =       (1 << 24),
    LSIRDY          =       (1 << 1),
    LSION           =       (1 << 0)
} RCC_CSR;

typedef enum{
    SSCGEN          =       (1 << 31),
    SPREADSEL       =       (1 << 30),
    INCSTEP         =       (1 << 13),
    MODPER          =       (1 << 0)
}RCC_SSCGR;


typedef enum{
    PLLI2SR2        =       (1 << 30),
    PLLI2SR1        =       (1 << 29),
    PLLI2SR0        =       (1 << 28),
    PLLI2SQ         =       (1 << 24),
    PLLI2SN8        =       (1 << 14),
    PLLI2SN7        =       (1 << 13),
    PLLI2SN6        =       (1 << 12),
    PLLI2SN5        =       (1 << 11),
    PLLI2SN4        =       (1 << 10),
    PLLI2SN3        =       (1 << 9),
    PLLI2SN2        =       (1 << 8),
    PLLI2SN1        =       (1 << 7),
    PLLI2SN0        =       (1 << 0)
}RCC_PLLI2SCFGR;


typedef enum{
    PLLSAIR         =       (1 << 28),
    PLLSAIQ         =       (1 << 24),
    PLLSAIN         =       (1 << 6)
}RCC_PLLSAICFGR;

typedef enum{
    TIMPRE          =       (1 << 24),
    SAI1BSRC        =       (1 << 22),
    SAI1ASRC        =       (1 << 20),
    PLLSAIDIVR      =       (1 << 16),
    PLLSAIDIVQ      =       (1 << 8),
    PLLS2DIVQ       =       (1 << 0)
} RCC_DCKCFGR;



#endif