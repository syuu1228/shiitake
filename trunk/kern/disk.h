#ifndef KERN_DISK_H_
#define KERN_DISK_H_
#include <lib/types.h>

ssize_t disk_read(int id, void *buf, off_t offset, size_t count);
ssize_t disk_write(int id, const void *buf, off_t offset, size_t count);

#endif /* KERN_DISK_H_ */
