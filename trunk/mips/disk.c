#include <kern/disk.h>
#include <mips/testmachine.h>
#include <mips/config.h>
#include <lib/string.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
//#define DPRINTF(...) do{}while(0)

void md_disk_init(int id)
{
}

int 
md_disk_sector_read(int id, unsigned char *buf, uint32_t lba, uint8_t count)
{
	DPRINTF("id:%d buf:%p lba:%u count:%u\n",
		id, buf, lba, count);
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_ID)) = id;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = lba * DISK_SECTOR_SIZE;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
		= DEV_DISK_OPERATION_READ;
	if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS))) {
		DPRINTF("disk read error\n");
		return -1;
	}
	memcpy((void *)buf,
	       (const void *)((volatile unsigned char *) DISK_ADDRESS
			      + DEV_DISK_BUFFER), DISK_SECTOR_SIZE * count);
	return 0;
}

int 
md_disk_sector_write(int id, const unsigned char *buf, uint32_t lba, uint8_t count)
{
	DPRINTF("id:%d buf:%p lba:%u count:%u\n",
		id, buf, lba, count);
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_ID)) = id;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = lba * DISK_SECTOR_SIZE;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
		= DEV_DISK_OPERATION_WRITE;
	if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS))) {
		DPRINTF("disk write error\n");
		return -1;
	}
	memcpy((void *)((volatile unsigned char *) DISK_ADDRESS
			+ DEV_DISK_BUFFER), 
	       (const void *)buf, DISK_SECTOR_SIZE * count);
	return 0;
}
