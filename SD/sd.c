#include "sd.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"

void sd_send_command(uint8_t cmd, uint32_t arg, uint8_t crc) {
    spi_transmit(0x40 | cmd);          // Start bit + command
    spi_transmit(arg >> 24);
    spi_transmit(arg >> 16);
    spi_transmit(arg >> 8);
    spi_transmit(arg);
    spi_transmit(crc);
}

uint8_t sd_wait_response() {
    uint8_t res = 0x0;
    for (uint32_t i = 0; i < 8; i++) {
        spi_transmit(0xFF);
    }
    return res;
}

uint32_t sd_init() {
    CS_HIGH();
    for (uint8_t i = 0; i < 10; i++) spi_transmit(0xFF); // 80+ clock cycles
    CS_LOW();

    sd_send_command(0, 0, 0x95); // CMD0
    if (sd_wait_response() != 0x01) return -1;

    CS_HIGH(); spi_transmit(0xFF); CS_LOW();
    sd_send_command(8, 0x1AA, 0x87); // CMD8
    if (sd_wait_response() != 0x01) return -2;

    // Send ACMD41 until card ready
    for (uint8_t i = 0; i < 1000; i++) {
        CS_HIGH(); spi_transmit(0xFF); CS_LOW();
        sd_send_command(55, 0, 0); // CMD55
        sd_wait_response();
        sd_send_command(41, 0x40000000, 0); // ACMD41
        if (sd_wait_response() == 0x00) break;
    }

    // CMD58 to read OCR
    CS_HIGH(); spi_transmit(0xFF); CS_LOW();
    sd_send_command(58, 0, 0); // CMD58
    if (sd_wait_response() != 0x00) return -4;

    CS_HIGH(); spi_transmit(0xFF);
    return 0;
}
