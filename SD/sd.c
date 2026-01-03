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

uint32_t sd_send_clock_cycle(uint32_t cycle){
    uint32_t ret = failed(SD_E);
    while(cycle != 0){
        ret = spi_transmit_receive(0xff);
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
    uint8_t *cmd_arr = 0,*resp_arr = 0;
    do{

        // One dummy byte before command (recommended)
        ret = sd_send_clock_cycle(0x1);
        if(ret == failed(SPI_E)){
            break;
        }
        cmd_arr = (uint8_t*)cmd;
        resp_arr = (uint8_t*)resp;
        for(uint32_t i=0; i<sizeof(sd_command) ;i++){
            resp_arr[i] = spi_transmit_receive(cmd_arr[i]);
        }
        if(ret == failed(SPI_E)){
            break;
        }

        // One dummy byte before command (recommended)
        ret = sd_send_clock_cycle(0x1);
        //sd_wait_response(resp);

    }while(0);
    return ret;
}

uint32_t sd_wait_response(sd_responce *resp) {
    uint32_t ret = failed(SD_E);
    uint8_t resp_arr[sizeof(sd_responce)];
    do{
        for(uint32_t loop = 0; loop<sizeof(sd_responce); loop++){
            resp_arr[loop] = spi_received();
        }
        mem_copy((void*)resp,(void*)resp_arr,sizeof(sd_responce));
        ret = pass(SD_E);
    }while(0);
    return ret;
}


/*
    1. ACMD = Application-Specific Command
    2. An ACMD cannot be sent directly
    3. It must ALWAYS be preceded by CMD55
*/
uint32_t sd_send_command_acmd(sd_command *cmd,sd_responce *resp){
    uint32_t ret = failed(SD_E);
    sd_command pre_cmd;
    sd_responce pre_resp;
    setup_command(&pre_cmd,CMD55,0,0x01);
    sd_send_command(&pre_cmd,&pre_resp);
    
    sd_send_clock_cycle(0x1);
    sd_send_command(cmd,resp);
    
    sd_send_clock_cycle(0x1);
    ret = pass(SD_E);
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


        setup_command(&command,CMD0,0x0,0x95);       // set up commond CMD0: GO_IDLE_STATE
        ret = sd_send_command(&command,&resp);        // send CMD0: GO_IDLE_STATE command

        if(ret = failed(SD_E)){
            break;
        }

        if(resp.response != IN_IDLE_STATE){
            ret = failed(SD_E);
            break;
        }

        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce


        ret = sd_send_clock_cycle(1);
        if(ret == failed(SD_E))
            break;


        // CMD8: SEND_IF_COND (check SD v2, 2.7-3.6V, pattern 0xAA)    
        setup_command(&command,CMD8,0x000001AA,0x87);      // CRC for CMD8
        ret = sd_send_command(&command,&resp);
        if(ret = failed(SD_E))
            break;

        if(resp.response != IN_IDLE_STATE){
            ret = failed(SD_E);
            break;    
        }
        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce

        // Now repeatedly send ACMD41 with HCS bit set until card is ready
        uint32_t timeout = 0xffff;
        setup_command(&command,ACMD41,0x40000000,0x01);
        do{
            sd_send_command_acmd(&command,&resp);
        }while(--timeout != 0);
        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce

        // CMD58: READ_OCR to check CCS (capacity)
        setup_command(&command,CMD58,0,0x01);
        sd_send_command(&command,&resp);
        if(resp.response != 0x0){
            ret = failed(SD_E);
            break;
        }
        

    }while(0);
    return ret;
}
