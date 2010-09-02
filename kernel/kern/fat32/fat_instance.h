#ifndef KERN_FAT32_FAT_INSTANCE_H_
#define KERN_FAT32_FAT_INSTANCE_H_
#include <kern/mbr.h>
#include <kern/fat32/bpb.h>
#include <lib/types.h>

typedef struct
{
  int disk_id;
  partition_record_t *partition;
  bpb_t *bpb;
} fat_instance_t;

fat_instance_t *fat_instance_new (int disk_id, int partition_no);
void fat_instance_delete (fat_instance_t *ins);
void fat_instance_dump (fat_instance_t *ins);
off_t fat_instance_head_offset (fat_instance_t *ins);
off_t fat_instance_byte_to_offset (fat_instance_t *ins, off_t byte);
off_t fat_instance_sector_to_offset (fat_instance_t *ins, sector_t sector);
off_t fat_instance_cluster_to_offset (fat_instance_t *ins, cluster_t cluster);
#endif /* KERN_FAT32_FAT_INSTANCE_H_ */
