#include <kern/disk.h>
#include <arch/config.h>
#include <kern/memory.h>
#include <lib/console.h>
#include <lib/string.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

void 
disk_init(int id)
{
	md_disk_init(id);
}

ssize_t 
disk_read(int id, unsigned char *buf, off_t offset, size_t count)
{
	int i;
	unsigned char tmp[DISK_SECTOR_SIZE];
	DPRINTF("id:%d buf:%p offset:%u count:%u\n",
		id, buf, offset, count);

	if((i = offset % DISK_SECTOR_SIZE) != 0) {
		if(count < i)
			i = count;
		DPRINTF("i:%d\n", i);
		if(md_disk_sector_read(id, tmp, offset / DISK_SECTOR_SIZE, 1))
			return -1;
		memcpy(buf, tmp + (offset % DISK_SECTOR_SIZE), i);
		DPRINTF("src:%p dst:%p count:%d\n",
			buf, tmp + (offset % DISK_SECTOR_SIZE), i);
	}
/*
	for(; c > DISK_SECTOR_SIZE;
	c -= DISK_SECTOR_SIZE, i += DISK_SECTOR_SIZE) {
	    DPRINTF("i:%d c:%u\n", i, c);
		if(md_disk_sector_read(id, buf + i, 
		(offset + i) / DISK_SECTOR_SIZE, 1))
		return -1;
		} 
*/
	if(count - i > 0) {
		if((count - i) / DISK_SECTOR_SIZE > 0) {
			if(md_disk_sector_read(id, buf + i, (offset + i) / DISK_SECTOR_SIZE,
					       (count - i) / DISK_SECTOR_SIZE))
				return -1;
			i += ((count - i) / DISK_SECTOR_SIZE) * DISK_SECTOR_SIZE;
			DPRINTF("i:%d\n", i);
		}
		if (count - i > 0) {
			if(md_disk_sector_read(id, tmp, (offset + i) / DISK_SECTOR_SIZE, 1))
				return -1;
			memcpy(buf + i, tmp, count - i);
			DPRINTF("src:%p dst:%p count:%d\n",
				buf + i, tmp, count - i);
		}
	} 
	return count;
}

ssize_t 
disk_write(int id, const unsigned char *buf, off_t offset, size_t count)
{
	return -1;
}
