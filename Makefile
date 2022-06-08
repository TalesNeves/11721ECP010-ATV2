CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb

all: startup.o main.o
main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -f *.0