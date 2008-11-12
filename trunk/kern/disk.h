#ifndef KERN_DISK_H_
#define KERN_DISK_H_
#include <lib/types.h>

void disk_init(int id);
ssize_t disk_read(int id, unsigned char *buf, off_t offset, size_t count);
ssize_t disk_write(int id, const unsigned char *buf, off_t offset, size_t count);

void md_disk_init(int id);
int md_disk_sector_read(int id, unsigned char *buf, uint32_t lba, uint8_t count);
int md_disk_sector_write(int id, const unsigned char *buf, uint32_t lba, uint8_t count);
#endif /* KERN_DISK_H_ */
