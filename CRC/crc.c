#include "stdint.h"
#include "crc.h"
#include "tool.h"
#include "rcc.h"
#include "error.h"
#include "stddef.h"

crc_reg *crc = NULL;

uint32_t crc_init(void){
    peripheral_clock_enable_register(CRC);          // enable clock for CRC module
    crc = (crc_reg*)(CRC_BASE_ADDRESS);             // set base address for CRC module

    if(crc->CRC_DR != CRC_RESET_VALUE){
        crc->CRC_CR |= CRC_CR_RESET;
    }
}

uint32_t calculate_crc(uint8_t *data,uint32_t len){
    uint32_t ret = CRC_RESET_VALUE;
    do{
        if(data == NULL || len <= 0){
            ret = CRC_RESET_VALUE;
            break;
        }
        for(uint32_t i=0;i<len;i++){
            crc->CRC_DR = data[i];
        }
        ret = crc->CRC_DR;
    }while(0);
    return ret;
}


void crc_reset(void){
    crc->CRC_CR |= CRC_CR_RESET;
}
