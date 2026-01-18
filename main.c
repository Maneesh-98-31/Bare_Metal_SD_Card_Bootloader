#include "vector_table.h"
#include "stdint.h"
#include "uart.h"
#include "error.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "sd.h"
#include "crc.h"
#include "image.h"

extern char _s_ram_data;
extern char _e_ram_data;

void uart_test(){
    //uint32_t ret = failed(RCC_E);
    //gpio_init(GPIO_A);
    //(void)ret;
    //gpio_pin_config(UART2);
    //(void)ret;
    //ret = uart_init(UART2);
    //(void)ret;
    //while(1){
    //    printf("maneesh");
    //}
    spi_test();
}

void spi_test(){
    uint32_t ret = failed(RCC_E);
    gpio_init(GPIO_A);
    (void)ret;
    gpio_pin_config(SPI1_SD);
    (void)ret;
    spi_init(SPI_1);
    sd_init();
    uint8_t write_buffer[512],*image_pointer;
    uint32_t image_size = (uint8_t*)&_e_ram_data - (uint8_t*)&_s_ram_data;
    
    mem_clear(write_buffer,sizeof(write_buffer));
    
    image_pointer = (uint8_t*)&_s_ram_data;
    for(uint32_t i=0;i<image_size;i++){
        write_buffer[i] = image_pointer[i];
    }
    image_struct_t *image = (image_struct_t*)write_buffer;
    //load_application_image(image);
    image_struct_t read_image;
    read_application_image(&read_image);
    

    control_to_application(&read_image);
    while(1);
}

void boot_main(){
    uint32_t ret = failed(RCC_E);
    ret = rcc_init(RCC_PLLON);
    if(ret == failed(RCC_E)){
        assert();
    }
    spi_test();
    

}