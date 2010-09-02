CROSS_COMPILE = mipsel-elf-
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
CC = $(CROSS_COMPILE)gcc
CPP = $(CC) -E
AR = $(CROSS_COMPILE)ar
NM = $(CROSS_COMPILE)nm
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CFLAGS = -g -EL -march=mips3 -mno-mips16 -O0 -mgp32 -mfp32 -mabi=32 -mno-abicalls -msoft-float -mmemcpy -mlong-calls -fno-builtin -Werror -I../../kernel

all: testapp

testapp:
	$(CC) -c $(CFLAGS) start.S -o start.o
	$(CC) -c $(CFLAGS) testapp.c -o testapp.o
	$(CC) -T ldscript -o testapp start.o testapp.o `$(CC) -print-libgcc-file-name`

clean:
	rm -f testapp *.o