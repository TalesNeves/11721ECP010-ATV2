CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4		\
	 	   -mthumb        		\
		   -specs=nano.specs	\
		   -specs=nosys.specs	\
		   -mfpu=fpv4-sp-d16 	\
		   -mfloat-abi=hard		\
		   -fmessage-length=0	\
		   -ffunction-sections	\
		   -c					\
		   
CC_LINKER_FLAGS =-mcpu=cortex-m4		\
				-mthumb				\
				-specs=nano.specs	\
				-specs=nosys.specs	\
				-mfpu=fpv4-sp-d16	\
				-mfloat-abi=hard	\
				-Wl,--gc-sections	\
				-T"linker.ld"		\
				-Wl,-Map=memmap.map	\

all: executavel.elf
executavel.elf: main.o startup.o
	$(CC) $(CC_LINKER_FLAGS) $^ -o executavel.elf
main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

startup.o: startup.c 
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm *.o
	rm *.elf