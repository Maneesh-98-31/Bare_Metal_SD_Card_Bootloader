#include "stdint.h"
#include "tool.h"
#include "stddef.h"


void delay(uint32_t val){
   for(uint32_t i=0;i<=val;i++){
    
   }
}

void assert(){
   while(1){
      
   }
}

void mem_clear(void *address,size_t size){
   for(uint8_t *ptr = (uint8_t*)address; ptr!=((uint8_t*)address + size); ptr++){
      *ptr = 0;
   }
}