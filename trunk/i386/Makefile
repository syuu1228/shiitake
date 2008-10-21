OBJS = boot.o kernel.o segment.o console.o ../lib/list.o ../lib/string.o ../lib/console.o
CFLAGS = -I.. -Werror -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -fno-builtin -g -O
CFLAGS += $(shell if $(CC) -fno-stack-protector -S -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "-fno-stack-protector"; fi)

all: shiitake

shiitake: $(OBJS)
	$(LD) -Map shiitake.map -T ldscript -o shiitake $(OBJS) `$(CC) -print-libgcc-file-name`

clean:
	rm -f $(OBJS) shiitake

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
