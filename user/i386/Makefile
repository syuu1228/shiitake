CROSS_COMPILE = i386-elf-
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
CC = $(CROSS_COMPILE)gcc
CPP = $(CC) -E
AR = $(CROSS_COMPILE)ar
NM = $(CROSS_COMPILE)nm
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CFLAGS = -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -fno-builtin -g -O -I../../kernel

all: testapp

testapp:
	$(CC) -c $(CFLAGS) start.S -o start.o
	$(CC) -c $(CFLAGS) testapp.c -o testapp.o
	$(CC) -T ldscript -nostdlib -o testapp start.o testapp.o

clean:
	rm -f testapp *.o