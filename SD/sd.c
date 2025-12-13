#include "sd.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"




void setup_command(sd_command *command ,uint8_t cmd,uint32_t arg,uint8_t crc){
    command->command = cmd | 0x40;
    command->arg[0] = (uint8_t)(arg >> 24);
    command->arg[1] = (uint8_t)(arg >> 16);
    command->arg[2] = (uint8_t)(arg >> 8);
    command->arg[3] = (uint8_t)(arg);
    command->crc = (crc << 0) | 0;
}

uint32_t sd_send_clock_cycles(uint32_t cycle){
    uint32_t ret = failed(SD_E);
    CS_HIGH();
    while(cycle != 0){
        ret = spi_transmit(0xff);
        if(ret == failed(SPI_E)){
            break;
        }
        cycle--;
    }
    
    if(cycle == 0) ret = pass(SD_E);
    return ret;
}

// Send command in SPI mode
// cmd = index (0..63), arg = 32-bit argument, crc (valid only for CMD0/CMD8)
uint32_t sd_send_command(sd_command *cmd,sd_responce *resp){
    uint32_t ret = failed(SD_E);
    uint8_t *cmd_arr = 0;
    do{
        CS_LOW();

        // One dummy byte before command (recommended)
        ret = spi_transmit(0xff);
        if(ret == failed(SPI_E)){
            break;
        }
        cmd_arr = (uint8_t*)cmd;
        for(uint32_t i=0; i<sizeof(sd_command) ;i++){
            ret = spi_transmit(cmd_arr[i]);
        }
        if(ret == failed(SPI_E)){
            break;
        }



    }while(0);
    return ret;
}

uint32_t sd_wait_response(sd_responce *resp) {
    uint32_t ret = failed(SD_E);
    uint8_t resp_arr[sizeof(sd_responce)];
    do{
        
    }while(0);
    return ret;
}

uint32_t sd_write_data_block(const uint8_t *buf,uint8_t token){

}

uint32_t sd_read_data_block(uint8_t *buf, uint16_t len){
    
}

uint32_t sd_init() {
    uint32_t ret = failed(SD_E);
    sd_command command;
    sd_responce resp;
    do{
        ret = sd_send_clock_cycle(10);      // 80+ dummy clocks with CS high
        if(ret == failed(SD_E))
            break;


        setup_command(&command,0x0,0x0,0x95);       // set up commond CMD0: GO_IDLE_STATE
        ret = sd_send_command(&command,&resp);        // send CMD0: GO_IDLE_STATE command
        mem_clear(&command,sizeof(command));                    // clear command
        if(ret = failed(SD_E))
            break;


        ret = sd_send_clock_cycle(1);
        if(ret == failed(SD_E))
            break;

    }while(0);
    return ret;
}
