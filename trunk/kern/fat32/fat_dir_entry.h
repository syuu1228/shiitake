#ifndef KERN_FAT32_FAT_DIR_ENTRY_H_
#define KERN_FAT32_FAT_DIR_ENTRY_H_
#include <kern/fat32/dir_entry.h>
typedef struct
{
	dir_entry_t dir_entry;
	char short_name[13];
	char long_name[256];
} fat_dir_entry_t;

#endif /* KERN_FAT32_FAT_DIR_ENTRY_H_*/
