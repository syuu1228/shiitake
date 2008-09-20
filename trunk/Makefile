OBJS = boot.o kernel.o
CFLAGS = -I. -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -g -fno-builtin -nostdinc -O -fno-stack-protector

all: shiitake

shiitake: $(OBJS)
#	$(CC) -g -o shiitake -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000 $(OBJS)
	$(LD) -Map shiitake.map -T ldscript -o shiitake $(OBJS)

clean:
	rm -f $(OBJS) shiitake

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
