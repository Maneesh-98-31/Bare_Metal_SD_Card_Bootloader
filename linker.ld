ENTRY(boot_main)
MEMORY
{
  CCMRAM      (xrw)     : ORIGIN = 0x10000000,    LENGTH = 64K
  RAM         (xrw)     : ORIGIN = 0x20000000,    LENGTH = 128K
  FLASH       (rx)      : ORIGIN = 0x08000000,    LENGTH = 1024K
}
_estack = ORIGIN(RAM) + LENGTH(RAM);
_rdata = ORIGIN(RAM);

SECTIONS
{
  .isr_vector : {
    
    *(.isr_vector*)
    
  } >FLASH

  .text : {
    
    *(.text*)
    
  } >FLASH

  . = ALIGN(4);
  _s_flash_data = .;
  
  .data : {
     . = ALIGN(4);
     _s_ram_data = .;
    *(.data*)
     . = ALIGN(4);
     _e_ram_data = .;
  } >RAM AT> FLASH

  _e_flash_data = LOADADDR(.bss);

  .bss : {
     _sbss = .; 
    *(.bss*)
    _ebss = .;
  } >RAM AT> RAM
  
  .rodata : {
    
    *(.rodata*)
    
  } >FLASH

  /DISCARD/ :{
  
  }
}
