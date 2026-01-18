#include "stdint.h"
#include "image.h"
#include "error.h"
#include "stddef.h"
#include "crc.h"
#include "sd.h"
#include "tool.h"

#define LOGICAL_BLOCK_ADDRESS       0x5
#define IMAGE_LOAD_ADDRESS         (uint32_t*)0x20014000U

typedef void (*go_to_application)(void);


static inline void set_msp_asm(uint32_t sp)
{
    asm volatile ("msr msp, %0" : : "r" (sp) : );
}

uint32_t image_header_check(image_struct_t *application_image){
    uint32_t ret = failed(IMAGE_E);
    uint32_t starting_address = application_image->header.starting_address;
    uint32_t entry_address = application_image->header.entry_address;
    do{
        // check if image pointer is null or not
        if(application_image == NULL){
            ret = failed(IMAGE_E);
            break;
        }
        // check image header
        if(
            application_image->header.tag != IMAGE_TAG          ||                  \
            application_image->header.version != IMAGE_VERSION  ||                  \
            application_image->header.image_length == NULL      ||                  \
            starting_address >= entry_address
        ){

            ret = failed(IMAGE_E);
            break;
        }
        
        // set pass if image is correct
        ret = pass(IMAGE_E);

    }while(0);
    return ret;
}


uint32_t image_crc_check(image_struct_t *application_image){
    uint32_t ret = failed(IMAGE_E);
    do{
        //check if image pointer is null or not
        if(application_image == NULL){
            ret = failed(IMAGE_E);
            break;
        }
        crc_init();
        crc_reset();
        uint32_t image_length = application_image->header.image_length  \
                                + sizeof(image_header_t);
        uint32_t re_calculated_crc = calculate_crc((uint8_t*)application_image,image_length);
        
        // check application CRC
        if(re_calculated_crc != application_image->crc){
            ret = failed(IMAGE_E);
            break;
        }

        ret == pass(IMAGE_E);

    }while(0);
    return ret;
}

uint32_t load_application_image(image_struct_t *application_image){
    uint32_t ret = failed(IMAGE_E);
    do{
        crc_init();
        crc_reset();
        uint32_t image_length = application_image->header.image_length  \
                                + sizeof(image_header_t);
        application_image->crc = calculate_crc((uint8_t*)application_image,image_length);
        ret = sd_write_block(LOGICAL_BLOCK_ADDRESS,(uint8_t*)application_image);
        if(ret != pass(SD_E)){
            ret = failed(IMAGE_E);
            break;
        }
        ret = pass(IMAGE_E);
    }while(0);
    return ret;
}

uint32_t read_application_image(image_struct_t *applicarion_image){
    uint32_t ret = failed(IMAGE_E);
    do{
        uint8_t read_buffer[512];
        mem_clear(IMAGE_LOAD_ADDRESS,sizeof(read_buffer));
        ret = sd_read_block(LOGICAL_BLOCK_ADDRESS,IMAGE_LOAD_ADDRESS);
        if(ret != pass(SD_E)){
            ret = failed(IMAGE_E);
            break;
        }
        //mem_copy((void*)read_buffer,(void*)i,sizeof(image_struct_t));
        applicarion_image->header = *((image_header_t*)IMAGE_LOAD_ADDRESS);
        //applicarion_image->image_payload = (uint8_t*)(IMAGE_LOAD_ADDRESS + sizeof(image_header_t));
        applicarion_image->image_payload = applicarion_image->header.entry_address;
        applicarion_image->crc = *(uint32_t*)(IMAGE_LOAD_ADDRESS + sizeof(image_header_t) + applicarion_image->header.image_length);    
        ret = pass(IMAGE_E);
    }while(0);
    return ret;
}

uint32_t IsValidStack(uint32_t sp){
    // adjust ranges for your MCU RAM region
    return (sp >= 0x20000000U) && (sp <= 0x2003FFFFU) && ((sp & 0x7U) == 0);
}

void control_to_application(image_struct_t *application_image){
    uint32_t ret = failed(IMAGE_E);
    do{
        uint32_t sp = *(uint32_t*)(application_image->image_payload); // initial stack pointer
        uint32_t reset = *(uint32_t*)(application_image->image_payload + 0x4); // reset handler address
        if(!IsValidStack(sp)){
            ret = failed(IMAGE_E);
            break;
        }
        if(reset % 2 != 0){
            reset = reset | ARM_THUMB_BIT; // set thumb bit
        }
        set_msp_asm(sp); // Set Main Stack Pointer
        go_to_application entry = (go_to_application*)(reset); // reset handler
        entry();
    }while(0);
    return ret;
}