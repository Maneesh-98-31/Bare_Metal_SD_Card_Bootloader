#include "stdint.h"
#include "image.h"
#include "error.h"
#include "stddef.h"
#include "security.h"

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

void control_to_application(image_struct_t *application_image){
    uint32_t ret = failed(IMAGE_E);
    do{
        void *function_pointer = (void*)((uint32_t)(application_image->header.entry_address) | ARM_THUMB_BIT);
        go_to_application = function_pointer;
        go_to_application();
    }while(0);
    return ret;
}