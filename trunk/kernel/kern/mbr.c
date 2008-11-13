#include <kern/mbr.h>
#include <kern/disk.h>
#include <kern/memory.h>
#include <lib/string.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

mbr_t *
mbr_read(const int id)
{
	DPRINTF("id:%d\n", id);
	mbr_t *m = (mbr_t *)calloc(1, sizeof(mbr_t));
	if ((disk_read (id, (unsigned char *)m, 0, sizeof (mbr_t))) != sizeof (mbr_t))
	{
		DPRINTF ("read failed\n");
		free(m);
		return NULL;
	}
	DPRINTF("return:%p\n", m);
	return m;
}

void 
mbr_dump(mbr_t *mbr)
{
	DPRINTF("mbr:%p\n", mbr);
	int i;
	for (i = 0; i < 4; i++)
	{
		printf ("Nr:%d ", i);
		partition_record_dump(&(mbr->partition_table[i]));
	}
	printf ("Signature:0x%x\n\n", mbr->signature);
}

void 
partition_record_dump(partition_record_t *partition)
{
	DPRINTF("partition:%p\n", partition);
	printf ("Bt:%u Hd:%u Sec:%u Cyl:%u ID:%x\n", partition->boot_flag,
			partition->chs_start.head, partition->chs_start.sector,
			partition->chs_start.cylinder, partition->type);
	printf ("Hd:%u Sec:%u Cyl:%u Start:%u Size:%u\n",
			partition->chs_end.head, partition->chs_end.sector,
			partition->chs_end.cylinder, partition->lba_start,
			partition->lba_total);
}

off_t 
mbr_partition_offset(partition_record_t *partition)
{
	DPRINTF("partition:%p\n", partition);
	off_t res = partition->lba_start * MBR_SECTOR_SIZE;
	DPRINTF("return:%d\n", res);
	return res;
}
