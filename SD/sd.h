#ifndef _SD_H_
#define _SD_H_

#include "stdint.h"
#include "gpio.h"

#define SPI1_CS_PIN   4U    /* PA4 */

typedef struct {
    uint8_t command;
    uint8_t arg[4];
    uint8_t crc;
}sd_command;

typedef struct {
    uint8_t response;
    uint8_t operation_condition_register[4];
}sd_responce;

typedef enum{
    SD_TYPE_UNKNOWN,        
    SD_TYPE_SDHC,       // High capacity: block addressing
    SD_TYPE_SDSC        // Standard capacity: byte addressing
} sd_type_t;

typedef enum{
    COMMAND_ACCEPTED      =    (0u),
    IN_IDLE_STATE         =   (1u<<0),
    ERASE_STATE           =   (1u<<1),
    ILLEGAL_CMD           =   (1u<<2),
    CMD_CRC_ERROR           =   (1u<<3),
    ERASE_SEQ_ERROR         =   (1u<<4),
    ADDRESS_ERROR           =   (1u<<5),
    PARAM_ERROR             =   (1u<<6)  
} RESPONCES;

typedef enum{
    CMD0    =   0u,     // GO_IDLE_STATE: Resets the SD card to the idle state.
    CMD8    =   8u,     //	SEND_IF_COND: Sends interface condition (check voltage/version).
    CMD16   =   16u,    // SET_BLOCKLEN: Sets the block length for read/write (default 512 bytes).   
    CMD17   =   17u,    // READ_SINGLE_BLOCK: Reads a single block of data from the card.
    CMD24   =   24u,    // WRITE_BLOCK: Writes a single block of data to the card.
    CMD55    =   55u,    // APP_CMD: Informs the card the next command is application-specific.
    ACMD41  =   41u,    // 	SD_SEND_OP_COND: Sends host capacity support information.
    CMD58    =  58u     // 	READ_OCR: Reads the Operation Conditions Register.
} COMMANDS;

uint32_t sd_init(void);
uint32_t sd_send_command(sd_command *cmd,sd_responce *resp);
uint32_t sd_wait_response(sd_responce *resp);
uint32_t sd_write_data_block(const uint8_t *buf,uint8_t token);
uint32_t sd_read_data_block(uint8_t *buf, uint16_t len);
uint32_t sd_send_clock_cycles(uint32_t cycle);
uint32_t sd_send_command_acmd(sd_command *cmd,sd_responce *resp);

#endif