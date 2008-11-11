#ifndef KERN_FAT32_BPB_H_
#define KERN_FAT32_BPB_H_
#include <kern/fat32/fat_type.h>

typedef struct
{
	uint8_t jmp_ope_code[3];
	uint8_t oem_name[8];
	uint16_t bytes_per_sector;
	uint8_t sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t number_of_fats;
	uint16_t root_entries;
	uint16_t total_sectors16;
	uint8_t media_descriptor;
	uint16_t sectors_per_fat16;
	uint16_t sectors_per_track;
	uint16_t heads;
	uint32_t hidden_sectors;
	uint32_t total_sectors32;
	uint32_t sectors_per_fat32;
	uint16_t ext_flags;
	uint16_t fs_version;
	uint32_t root_dir_cluster;
	uint16_t fs_info_sector;
	uint16_t backup_boot_sector;
	uint8_t reserved[12];
	uint8_t drive_number;
	uint8_t reserved1;
	uint8_t boot_signature;
	uint32_t volume_id;
	uint8_t volume_label[11];
	uint8_t file_system_type[8];
	uint8_t load_program_code[420];
	uint16_t signature;
} __attribute__ ((packed)) bpb_t;

bool bpb_validate_cluster_no(bpb_t *bpb, cluster_t cluster_no);
bool bpb_validate (bpb_t *bpb);
bool bpb_read (void *ins);
void bpb_dump(bpb_t *bpb);
uint32_t bpb_cluster_size(bpb_t *bpb);
cluster_t bpb_count_of_clusters(bpb_t *bpb);
sector_t bpb_cluster_to_sector(bpb_t *bpb, cluster_t cluster);
off_t bpb_sector_to_byte(bpb_t *bpb, sector_t sector);
#endif /*KERN_FAT32_BPB_H_ */
