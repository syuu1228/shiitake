CFLAGS = -I.. -Werror -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -fno-builtin -g -O -D_KERNEL
CFLAGS += $(shell if $(CC) -fno-stack-protector -S -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "-fno-stack-protector"; fi)
LDFLAGS = -T ldscript
OBJS = boot.o init.o segment.o console.o thread.o memory.o switch.o interrupt.o disk.o interrupt_vector.o trap.o syscall.o ../lib/string.o ../lib/console.o ../kern/main.o ../kern/memory.o ../kern/thread.o ../kern/file_descriptor.o ../kern/mbr.o ../kern/fat32/bpb.o ../kern/fat32/cluster.o ../kern/fat32/cluster_data.o ../kern/fat32/dir_entry.o ../kern/fat32/fat32fs.o ../kern/fat32/fat_cluster_list.o ../kern/fat32/fat_dir.o ../kern/fat32/fat_file.o ../kern/fat32/fat_instance.o ../kern/fat32/fat_path.o ../kern/disk.o ../kern/execute.o ../kern/syscall.o

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
