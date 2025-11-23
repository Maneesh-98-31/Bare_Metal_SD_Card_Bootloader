
#ifndef VECTOR_TABLE_H_
#define VECTOR_TABLE_H_
#include "stdint.h"
extern uint32_t _estack;
void boot_main();
void NMI_Handler();
void HardFault_Handler();
void MemManage_Handler();
void BusFault_Handler();
void UsageFault_Handler();

extern void* vector_table[256];


#endif /* VECTOR_TABLE_H_ */
