#ifndef KERN_FAT32_FAT_FILE_H_
#define KERN_FAT32_FAT_FILE_H_
#include <kern/fat32/fat_type.h>
#include <kern/fat32/fat_instance.h>
#include <kern/fat32/fat_cluster_list.h>

typedef struct {
	fat_instance_t *ins;
	fat_cluster_list_t *cluster;
	off_t offset;
} fat_file_t;

fat_file_t *fat_file_new(fat_instance_t *ins, fat_cluster_list_t *cluster);
fat_file_t *fat_file_open(fat_instance_t *ins, const char *path);
ssize_t fat_file_read(fat_file_t * file, void *buffer, size_t count);
off_t fat_file_seek_set(fat_file_t *file, off_t offset);
off_t fat_file_seek_cur(fat_file_t *file, off_t offset);
off_t fat_file_tell(fat_file_t *file);
int fat_file_close(fat_file_t * file);
#endif /* KERN_FAT_FILE_H_ */
