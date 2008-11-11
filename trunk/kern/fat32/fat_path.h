#ifndef KERN_FAT32_FAT_PATH_H_
#define KERN_FAT32_FAT_PATH_H_
#include <kern/fat32/fat_type.h>
#include <kern/fat32/fat_dir_entry.h>
#include <kern/fat32/fat_cluster_list.h>

int fat_path_get_entry(fat_instance_t *ins, const char *path, fat_dir_entry_t *dir);
fat_cluster_list_t *fat_path_get_cluster(fat_instance_t *ins, const char *path);
#endif /* KERN_FAT32_FAT_PATH_H_*/
