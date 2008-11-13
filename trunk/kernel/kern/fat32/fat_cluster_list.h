#ifndef KERN_FAT32_FAT_CLUSTER_LIST_H_
#define KERN_FAT32_FAT_CLUSTER_LIST_H_
#include <kern/fat32/fat_type.h>
#include <kern/fat32/fat_instance.h>
#include <kern/fat32/cluster.h>
#include <kern/fat32/fat_dir_entry.h>

typedef struct
{
	cluster_t *clusters;
	int offset, length, end;
} fat_cluster_list_t;

fat_cluster_list_t *fat_cluster_list_open_by_cluster_no(fat_instance_t * ins,
							cluster_t cluster_no);
fat_cluster_list_t *fat_cluster_list_open_by_fat_dir_entry(fat_instance_t * ins,
							   fat_dir_entry_t *dir);
cluster_t fat_cluster_list_read(fat_cluster_list_t *list);
cluster_t fat_cluster_list_next(fat_cluster_list_t *list);
int fat_cluster_list_tell(fat_cluster_list_t *list);
int fat_cluster_list_seek_set(fat_cluster_list_t *list, int offset);
int fat_cluster_list_seek_cur(fat_cluster_list_t *list, int offset);
int fat_cluster_list_size(fat_cluster_list_t *list);
void fat_cluster_list_close(fat_cluster_list_t *list);
void fat_cluster_list_dump(fat_cluster_list_t *list);
#endif /*KERN_FAT32_FAT_CLUSTER_LIST_H_*/
