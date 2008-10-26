CFLAGS = -I.. -Werror -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -fno-builtin -g -O
CFLAGS += $(shell if $(CC) -fno-stack-protector -S -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "-fno-stack-protector"; fi)
LDFLAGS = -T ldscript
OBJS = boot.o init.o segment.o console.o thread.o memory.o locore.o ../lib/string.o ../lib/console.o ../kern/main.o ../kern/memory.o ../kern/thread.o

all: shiitake

link_arch:
	rm -f ../arch
	ln -sf i386 ../arch

shiitake: link_arch $(OBJS)
	$(LD) -Map shiitake.map $(LDFLAGS) -o shiitake $(OBJS) `$(CC) -print-libgcc-file-name`

clean:
	rm -f $(OBJS) shiitake shiitake.map ../arch

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
