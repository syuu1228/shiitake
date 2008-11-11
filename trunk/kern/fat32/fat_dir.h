#ifndef KERN_FAT32_FAT_DIR_H_
#define KERN_FAT32_FAT_DIR_H_
#include <kern/fat32/fat_file.h>
#include <kern/fat32/fat_dir_entry.h>
int fat_dir_read (fat_file_t *file, fat_dir_entry_t *dir);
int fat_dir_find (fat_file_t *file, const char *name, fat_dir_entry_t *dir);
#endif /*KERN_FAT32_FAT_DIR_H_ */
