#ifndef KERN_MBR_H_
#define KERN_MBR_H_
#include <lib/types.h>

#define MBR_SECTOR_SIZE 512

typedef struct
{
  uint8_t head;
  uint8_t sector;
  uint8_t cylinder;
} __attribute__ ((packed)) chs_t;

typedef struct
{
  uint8_t boot_flag;
  chs_t chs_start;
  uint8_t type;
  chs_t chs_end;
  uint32_t lba_start;
  uint32_t lba_total;
} __attribute__ ((packed)) partition_record_t;

typedef enum
{
  PT_FAT12 = 0x01,
  PT_FAT16lt32M = 0x04,
  PT_FAT16 = 0x06,
  PT_W95FAT32 = 0x0b,
  PT_W95FAT32LBA = 0x0c,
  PT_W95FAT16LBA = 0x0e
} partition_type_t;

typedef struct
{
  uint8_t loader[446];
  partition_record_t partition_table[4];
  uint16_t signature;
} __attribute__ ((packed)) mbr_t;

mbr_t *mbr_read (const int fd);
void mbr_dump (mbr_t *mbr);
void partition_record_dump (partition_record_t *partition);
off_t mbr_partition_offset (partition_record_t *partition);
#endif /*KERN_MBR_H_ */
