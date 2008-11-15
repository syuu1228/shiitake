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
CFLAGS = -g -EL -I../ -march=mips3 -mno-mips16 -O0 -mgp32 -mfp32 -mabi=32 -mno-abicalls -msoft-float -mmemcpy -mlong-calls -fno-builtin -Werror
LDFLAGS = -T ldscript --oformat $(OFORMAT)
OBJS = boot.o init.o console.o thread.o memory.o switch.o interrupt.o trap.o syscall.o disk.o exception.o tlb_refill_vector.o xtlb_refill_vector.o general_vector.o interrupt_vector.o reset_vector.o cache_error_vector.o ../lib/string.o ../lib/console.o ../kern/main.o ../kern/memory.o ../kern/thread.o ../kern/file_descriptor.o ../kern/mbr.o ../kern/fat32/bpb.o ../kern/fat32/cluster.o ../kern/fat32/cluster_data.o ../kern/fat32/dir_entry.o ../kern/fat32/fat32fs.o ../kern/fat32/fat_cluster_list.o ../kern/fat32/fat_dir.o ../kern/fat32/fat_file.o ../kern/fat32/fat_instance.o ../kern/fat32/fat_path.o ../kern/disk.o

all: shiitake

link_arch:
	rm -f ../arch
	ln -sf mips ../arch

shiitake: link_arch $(OBJS)
	$(LD) -Map sos.map $(LDFLAGS) -o shiitake $(OBJS) `$(CC) -print-libgcc-file-name`

clean:
	rm -f $(OBJS) shiitake shiitake.map ../arch
.S.o:
	$(CC) -c $(CFLAGS) $< -o $@
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
