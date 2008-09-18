OBJS = boot.o kernel.o
CFLAGS = -I. -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -g -fno-builtin -nostdinc -O

all: shiitake

shiitake: $(OBJS)
	$(CC) -g -o shiitake -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000 $(OBJS)

clean:
	rm -f $(OBJS) shiitake