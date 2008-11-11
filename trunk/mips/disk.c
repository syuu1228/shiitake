#include <kern/disk.h>
#include <mips/testmachine.h>
#include <lib/string.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

ssize_t 
disk_read(int id, void *buf, off_t offset, size_t count)
{
	int i, c = count;
	
	DPRINTF("id:%d buf:%x offset:%u count:%u\n", id, buf, offset, count);
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_ID)) = id;
	for (i = 0; c > DEV_DISK_BUFFER_LEN; c -= DEV_DISK_BUFFER_LEN, i
			+= DEV_DISK_BUFFER_LEN)
	{
		*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = offset + i;
		*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
				=DEV_DISK_OPERATION_READ;
		DPRINTF("READ_OP offset:%u\n", offset + i);
		if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)))
		{
			DPRINTF("DISK_STATUS:%d\n", *((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)));
			DPRINTF("return:-1\n");
			return -1;
		}
		memcpy(buf + i, (const void *)((volatile unsigned char *) DISK_ADDRESS
				+ DEV_DISK_BUFFER), DEV_DISK_BUFFER_LEN);
	}
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = offset + i;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
			= DEV_DISK_OPERATION_READ;
	DPRINTF("READ_OP offset:%u\n", offset + i);
	if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)))
	{
		DPRINTF("DISK_STATUS:%d\n", *((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)));
		DPRINTF("return:-1\n");
		return -1;
	}
	memcpy(buf + i, (const void *)((volatile unsigned char *) DISK_ADDRESS + DEV_DISK_BUFFER),
			c);
	DPRINTF("return:%d\n", i + c);
	return i + c;
}

ssize_t 
disk_write(int id, const void *buf, off_t offset, size_t count)
{
	int i, c = count;

	DPRINTF("id:%d buf:%x offset:%u count:%u\n", id, buf, offset, count);
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_ID)) = id;
	for (i = 0; c > DEV_DISK_BUFFER_LEN; c -= DEV_DISK_BUFFER_LEN, i
			+= DEV_DISK_BUFFER_LEN)
	{
		*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = offset + i;
		*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
				= DEV_DISK_OPERATION_WRITE;
		DPRINTF("WRITE_OP offset:%u\n", offset + i);
		if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)))
			return -1;
		memcpy((void *)((volatile unsigned char *) DISK_ADDRESS + DEV_DISK_BUFFER), buf
				+ i, DEV_DISK_BUFFER_LEN);
	}
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_OFFSET)) = offset + i;
	*((volatile int *) (DISK_ADDRESS + DEV_DISK_START_OPERATION))
			=DEV_DISK_OPERATION_WRITE;
	DPRINTF("WRITE_OP offset:%u\n", offset + i);
	if (!*((volatile int *) (DISK_ADDRESS + DEV_DISK_STATUS)))
		return -1;
	memcpy((void *)((volatile unsigned char *) DISK_ADDRESS + DEV_DISK_BUFFER), buf + i,
			c);
	DPRINTF("return:%d\n", i + c);
	return i + c;
}
