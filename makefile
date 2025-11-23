all:
	arm-none-eabi-gcc -o main.o -c main.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-gcc -o vector_table.o -c vector_table.c -mcpu=cortex-m4 -g -mthumb 
	arm-none-eabi-ld -Tlinker.ld main.o vector_table.o -o ./build/stm32F407xx.elf
	arm-none-eabi-objdump -D -S ./build/stm32F407xx.elf > ./build/stm32F407xx.elf.lst

clean:
	rm *.o
	rm ./build/stm32F407xx.elf.lst
	rm ./build/stm32F407xx.elf
	
	