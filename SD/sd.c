#include "sd.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "tool.h"
#include "stdbool.h"

#define SPI1_CS_PIN   4U    /* PA4 */
#define CS_LOW()  (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_BSRR  |= (1U << (SPI1_CS_PIN + 16)))
#define CS_HIGH() (((gpio_def*)GPIOA_BASE_ADDRESS)->GPIOx_BSRR  |= (1U << SPI1_CS_PIN))

#define SD_BLOCK_SIZE   512
#define MAX_DELAY_CYCLE     0x2

// Card type global (SDHC / SDSC)
sd_type_t g_sd_type = SD_TYPE_UNKNOWN;


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
    CS_LOW();
    while(cycle != 0){
        ret = spi_transmit_receive(0xff);
        if(ret == failed(SPI_E)){
            break;
        }
        cycle--;
    }
    CS_HIGH();
    delay(100);
    if(cycle == 0) ret = pass(SD_E);
    return ret;
}




// Send command in SPI mode
// cmd = index (0..63), arg = 32-bit argument, crc (valid only for CMD0/CMD8)
uint32_t sd_send_command(sd_command *cmd,sd_responce *resp){
    uint32_t ret = failed(SD_E);
    uint8_t *cmd_arr = (uint8_t*)0,*resp_arr = (uint8_t*)0;
    bool responce_flag = false;
    uint32_t responce_top = 0;
    do{
        CS_LOW();
        // One dummy byte before command (recommended)
        spi_transmit_receive(0xff);
        

        cmd_arr = (uint8_t*)cmd;
        resp_arr = (uint8_t*)resp;
        for(uint32_t i=0; i<sizeof(sd_command) ;i++){
            spi_transmit_receive(cmd_arr[i]);
            //delay(10);
        }

        for(uint32_t i=0;i<sizeof(resp);i++){
            uint8_t responce = spi_transmit_receive(0xff);
            if( (0xff != responce || true == responce_flag)            \
                && sizeof(responce) > responce_top ){
                resp_arr[responce_top++] = responce;
                responce_flag = true;
            }
            //resp_arr[responce_top++] = responce;
        }
        
        if(false == responce_flag){
            ret = failed(SD_E);
            break;
        }
        
        // One dummy byte before command (recommended)
        spi_transmit_receive(0xff);
        CS_HIGH();
        //sd_wait_response(resp);
        delay(100);
        ret = pass(SD_E);

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
    
    if(pre_resp.response > 0x1){
        ret = failed(SD_E);
    }

    sd_send_clock_cycle(MAX_DELAY_CYCLE);
    sd_send_command(cmd,resp);
    
    sd_send_clock_cycle(MAX_DELAY_CYCLE);
    ret = pass(SD_E);
    return ret;
}


uint32_t sd_write_data_block(const uint8_t *buf,uint8_t token){
    
}

uint32_t sd_read_data_block(uint8_t *buf, uint16_t len){
    uint32_t ret = failed(SD_E);
    uint16_t timeout = 0xFFFF;
    uint8_t token;
    do{
        CS_LOW();
        // 1) Wait for token 0xFE
        do {
            token = spi_transmit_receive(0xff);
            
        } while ((token == 0xFF) && --timeout);

        if (token != 0xFE) {
            // Not a valid start token
            ret = failed(SD_E);
            break;
        }
            // 2) Read 'len' bytes into buffer
        for (uint16_t i = 0; i < len; i++) {
            buf[i] = spi_transmit_receive(0xFF);
        }

            // 3) Read and ignore 2 CRC bytes
       sd_send_clock_cycle(MAX_DELAY_CYCLE);
        CS_HIGH();
    }while(0);
    return true;
}


uint32_t sd_read_block(uint32_t lba, uint8_t *buf){
    uint32_t ret = failed(SD_E);
    uint16_t timeout = 0xff;
    uint8_t token = 0;
    sd_command command;
    sd_responce resp;
    do{
        if(g_sd_type == SD_TYPE_SDSC){
            lba <<=9;
        }
        // CMD17: READ_SINGLE_BLOCK
        setup_command(&command,CMD17,lba,0x01);       
        sd_send_command(&command,&resp);        
        if(resp.response != COMMAND_ACCEPTED){
            ret = failed(SD_E);
            break;
        }

        // Here is where we actually RECEIVE data from card:
        // wait for 0xFE, then 512 bytes, then CRC.
        sd_read_data_block(buf,SD_BLOCK_SIZE);
        sd_send_clock_cycle(MAX_DELAY_CYCLE);
    }while(0);
    return ret;
}


uint32_t sd_init() {
    uint32_t ret = failed(SD_E);
    sd_command command;
    sd_responce resp;
    do{
        ret = sd_send_clock_cycle(MAX_DELAY_CYCLE);      // 80+ dummy clocks with CS high
        if(ret == failed(SD_E))
            break;



        setup_command(&command,CMD0,0x0,0x95);       // set up commond CMD0: GO_IDLE_STATE
        ret = sd_send_command(&command,&resp);        // send CMD0: GO_IDLE_STATE command

        if(ret == failed(SD_E) || IN_IDLE_STATE != resp.response){
            ret = failed(SD_E);
            break;
        }

        if(resp.response != IN_IDLE_STATE){
            ret = failed(SD_E);
            break;
        }

        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce

        // send 5 dummy cycles

        ret = sd_send_clock_cycle(MAX_DELAY_CYCLE);
        if(ret == failed(SD_E))
            break;


        // prepare command
        // CMD8: SEND_IF_COND (check SD v2, 2.7-3.6V, pattern 0xAA)     
        setup_command(&command,CMD8,0x000001AA,0x87);      // CRC for CMD8
        ret = sd_send_command(&command,&resp);
        
        if(ret == failed(SD_E))
            break;
        

        // Check that voltage accepted and pattern matches
        if(resp.response != IN_IDLE_STATE ||                        \
            resp.operation_condition_register[2] == 0x1 ||          \
            resp.operation_condition_register[3] == 0xaa
        ){
            ret = failed(SD_E);
            break;    
        }

        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce

        // send 5 dummy cycles
        ret = sd_send_clock_cycle(MAX_DELAY_CYCLE);
        if(ret == failed(SD_E))
            break;
 

        // Now repeatedly send ACMD41 with HCS bit set until card is ready
        uint32_t timeout = 0xff;
        setup_command(&command,ACMD41,0x40000000,0x01);
        do{
            sd_send_command_acmd(&command,&resp);
        }while(--timeout != 0 && resp.response != 0x0);

        if(timeout == 0 || resp.response != 0x0 ){
            ret = failed(SD_E);
            //break;
        }

        mem_clear(&command,sizeof(command));                    // clear command
        mem_clear(&resp,sizeof(resp));                          // clear responce

        // CMD58: READ_OCR to check CCS (capacity)
        setup_command(&command,CMD58,0,0x01);
        sd_send_command(&command,&resp);
        
        sd_send_clock_cycle(MAX_DELAY_CYCLE);

        if(resp.response & 0x40){
            g_sd_type = SD_TYPE_SDHC;  // High capacity: block addressing
        }else{
            g_sd_type = SD_TYPE_SDSC;  // Standard capacity: byte addressing
        }

        spi_set_high_speed();
        
    }while(0);
    return ret;
}
