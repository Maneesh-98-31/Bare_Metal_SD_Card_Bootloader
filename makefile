INCLUDE_PATHS = -I./ERROR/ -I./TOOLS/ -I./GPIO/ -I./UART/ -I./RCC/ -I./SPI/ -I./SD/ -I./CRC/
FLAGS = -Wconversion -Wall -nodefaultlibs

all:
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o main.o -c main.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc -o vector_table.o -c vector_table.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o error.o -c ./ERROR/error.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o tool.o -c ./TOOLS/tool.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o gpio.o -c ./GPIO/gpio.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o uart.o -c ./UART/uart.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o rcc.o -c ./RCC/rcc.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o spi.o -c ./SPI/spi.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o sd.o -c ./SD/sd.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc $(INCLUDE_PATHS) -o crc.o -c ./CRC/crc.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-ld -Tlinker.ld main.o vector_table.o error.o tool.o gpio.o uart.o rcc.o spi.o sd.o crc.o -o ./build/stm32F407xx.elf
	arm-none-eabi-objdump -D -S ./build/stm32F407xx.elf > ./build/stm32F407xx.elf.lst

clean:
	rm *.o
	rm ./build/stm32F407xx.elf.lst
	rm ./build/stm32F407xx.elf

cls:
	del *.o
	del .\build\stm32F407xx.elf.lst
	del .\build\stm32F407xx.elf
	
	