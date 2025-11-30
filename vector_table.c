#include "vector_table.h"
#include "stdint.h"


void* vector_table[256] __attribute__((section(".isr_vector"))) = {
	&_estack,
	boot_main,
	NMI_Handler,
    HardFault_Handler,  
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
};


void NMI_Handler(){

}

void HardFault_Handler(){
    while(1){
        
    }
}

void MemManage_Handler(){

}

void BusFault_Handler(){

}

void UsageFault_Handler(){

}
