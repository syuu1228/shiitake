CROSS_COMPILE = mipsel-elf-
OFORMAT = elf32-littlemips
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
CC = $(CROSS_COMPILE)gcc
CPP = $(CC) -E
AR = $(CROSS_COMPILE)ar
NM = $(CROSS_COMPILE)nm
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
CFLAGS = -g -EL -I../ -march=mips1 -mno-mips16 -O0 -mgp32 -mfp32 -mabi=32 -mno-abicalls -msoft-float -mmemcpy -mlong-calls -fno-builtin
LDFLAGS = -T ldscript --oformat $(OFORMAT)
OBJS = boot.o init.o console.o ../lib/list.o ../lib/string.o ../lib/console.o ../kern/main.o

all: shiitake

shiitake: $(OBJS)
	$(LD) -Map sos.map $(LDFLAGS) -o shiitake $(OBJS) `$(CC) -print-libgcc-file-name`

clean:
	rm -f $(OBJS) shiitake shiitake.map
.S.o:
	$(CC) -c $(CFLAGS) -D__ASSEMBLY__ $< -o $@
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
