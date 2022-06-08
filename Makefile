CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -f *.0