OBJS = boot.o kernel.o
CFLAGS = -I. -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -g -fno-builtin -nostdinc -O
CFLAGS += $(shell if $(CC) -fno-stack-protector -S -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "-fno-stack-protector"; fi)

all: shiitake

shiitake: $(OBJS)
	$(LD) -Map shiitake.map -T ldscript -o shiitake $(OBJS)

clean:
	rm -f $(OBJS) shiitake

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
