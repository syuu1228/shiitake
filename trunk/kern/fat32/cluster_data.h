#ifndef KERN_FAT32_CLUSTER_DATA_H_
#define KERN_FAT32_CLUSTER_DATA_H_
#include <kern/fat32/fat_instance.h>

off_t cluster_data_offset (fat_instance_t *ins, const cluster_t cluster_no);
ssize_t cluster_data_read (fat_instance_t *ins, const cluster_t cluster_no, void *buffer, off_t offset, size_t count);
#endif /* KERN_FAT32_CLUSTER_DATA_H_ */
