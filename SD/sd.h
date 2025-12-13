#ifndef _SD_H_
#define _SD_H_

#include "stdint.h"
#include "gpio.h"

#define CS_LOW()  (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_ODR &= ~(1 << 4))
#define CS_HIGH() (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_ODR |= (1 << 4))


typedef struct {
    uint8_t command;
    uint8_t arg[4];
    uint8_t crc;
}sd_command;

typedef struct {
    uint8_t response;
    uint8_t operation_condition_register[4];
}sd_responce;


uint32_t sd_init(void);
uint32_t sd_send_command(sd_command *cmd,sd_responce *resp);
uint32_t sd_wait_response(sd_responce *resp);
uint32_t sd_write_data_block(const uint8_t *buf,uint8_t token);
uint32_t sd_read_data_block(uint8_t *buf, uint16_t len);
uint32_t sd_send_clock_cycles(uint32_t cycle);

#endif