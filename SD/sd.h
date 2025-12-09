#ifndef _SD_H_
#define _SD_H_

#include "stdint.h"
#include "gpio.h"

#define CS_LOW()  (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_ODR &= ~(1 << 4))
#define CS_HIGH() (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_ODR |= (1 << 4))


uint32_t sd_init(void);
void sd_send_command(uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t sd_wait_response();


#endif