#include "stdint.h"
#include "tool.h"



void delay(uint32_t val){
   for(uint32_t i=0;i<=val;i++){
    
   }
}

void assert(){
   while(1){
      
   }
}

void mem_clear(void *address,uint32_t size){
   for(uint8_t *ptr = (uint8_t*)address; ptr!=((uint8_t*)address + size); ptr++){
      *ptr = 0;
   }
}

void mem_copy(void *src,void *dest,uint32_t size){
   uint8_t *src_ptr = (uint8_t*)src, *dest_ptr = (uint8_t*)dest;
   while(src_ptr < (src_ptr + size)){
      *dest_ptr = *src_ptr;
   }
}