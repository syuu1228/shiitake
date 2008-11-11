#ifndef KERN_FAT32_DIR_ENTRY_H_
#define KERN_FAT32_DIR_ENTRY_H_
#include <kern/fat32/fat_type.h>

#define DIR_ENTRY_IS_END(dir) \
	((dir)->name[0] == 0x00)

#define DIR_ENTRY_IS_DELETED(dir) \
	((dir)->name[0] == 0x05 ||(dir)->name[0] == 0xe5)

#define DIR_ENTRY_IS_LDIR_ENTRY(dir) \
	((dir)->attributes.read_only && (dir)->attributes.hidden \
	&& (dir)->attributes.system && (dir)->attributes.volume_label)

typedef struct
{
  uint16_t date:5;
  uint16_t month:4;
  uint16_t year:7;
}
__attribute__ ((packed)) dir_entry_date_t;

typedef struct
{
  uint16_t two_sec:5;
  uint16_t minite:6;
  uint16_t hour:5;
}
__attribute__ ((packed)) dir_entry_time_t;

typedef struct
{
  uint16_t read_only:1;
  uint16_t hidden:1;
  uint16_t system:1;
  uint16_t volume_label:1;
  uint16_t directory:1;
  uint16_t archive:1;
  uint16_t reserved:2;
}
__attribute__ ((packed)) dir_attributes_t;

typedef struct
{
  uint8_t name[8];
  uint8_t extension[3];
  dir_attributes_t attributes;
  uint8_t nt_reserved;
  uint8_t create_time_ms;
  dir_entry_time_t create_time;
  dir_entry_date_t create_date;
  dir_entry_date_t access_date;
  uint16_t cluster_hi;
  dir_entry_time_t update_time;
  dir_entry_date_t update_date;
  uint16_t cluster_lo;
  uint32_t file_size;
}
__attribute__ ((packed)) dir_entry_t;

void dir_entry_dump (dir_entry_t *dir);
void dir_attributes_dump (dir_attributes_t *attributes);
void time_dump (dir_entry_time_t *time);
void date_dump (dir_entry_date_t *date);
uint8_t dir_entry_short_name_check_code (dir_entry_t *dir);
cluster_t dir_entry_get_cluster (dir_entry_t *dir);
void dir_entry_combine_short_name(dir_entry_t *dir, char *buf);
#endif /* KERN_FAT32_DIR_ENTRY_H_ */
