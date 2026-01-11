#ifndef _CRC_H_
#define _CRC_H_

#include "stdint.h"


#define CRC_RESET_VALUE         (0xffffffff)
#define CRC_CR_RESET               (1<<0)
#define CRC_BASE_ADDRESS            (0x40023000)
typedef struct{
    volatile uint32_t CRC_DR;
    volatile uint32_t CRC_IDR;
    volatile uint32_t CRC_CR;
}crc_reg;


uint32_t crc_init(void);
uint32_t calculate_crc(uint8_t *data,uint32_t len);
void crc_reset(void);

#endif