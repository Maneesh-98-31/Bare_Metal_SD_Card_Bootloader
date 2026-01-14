#ifndef __IMAGE__
#define __IMAGE__

#include "stdint.h"

#define IMAGE_TAG           0xa1U
#define IMAGE_VERSION       0x01U 
#define ARM_THUMB_BIT       0x1U

typedef struct{
    uint8_t tag;
    uint8_t reserved[2];
    uint8_t version;
    uint32_t starting_address;
    uint32_t entry_address;
    uint32_t image_length;
} image_header_t;


typedef struct{
    image_header_t header;
    uint8_t *image_payload;
    uint32_t crc;
} image_struct_t;


uint32_t image_header_check(image_struct_t *application_image);

void (*go_to_application)(void);

#endif