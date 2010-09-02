#include <kern/fat32/cluster.h>
#include <kern/disk.h>
#include <lib/string.h>
#include <lib/assert.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

off_t 
cluster_offset(fat_instance_t * ins, const cluster_t cluster_no)
{
	DPRINTF("ins:%p clusterNo:%u\n", ins, cluster_no);
	off_t res = fat_instance_sector_to_offset (ins, (sector_t)ins->bpb->reserved_sectors);
	res += cluster_no * 4;
	DPRINTF("return:%u\n", res);
	return res;
}

uint32_t 
cluster_read(fat_instance_t * ins, const cluster_t cluster_no)
{
	uint32_t extent;

	DPRINTF("ins:%p clusterNo:%u\n", ins, cluster_no);
	assert(bpb_validate_cluster_no (ins->bpb, cluster_no));
	if ((disk_read (ins->disk_id, (unsigned char *)&extent, cluster_offset(ins, cluster_no),
			sizeof(uint32_t))) != sizeof(uint32_t))
		DPRINTF("read failed\n");
	extent &= 0x0FFFFFFF;
	DPRINTF("return:%u\n", extent);
	return extent;
}

void 
cluster_dump(fat_instance_t * ins, const cluster_t cluster_no)
{
	DPRINTF("ins:%p clusterNo:%u\n", ins, cluster_no);
	uint32_t extent = cluster_read (ins, cluster_no);
	printf ("%u->", cluster_no);
	if (IS_BAD_CLUSTER (extent))
	{
		printf ("bad\n");
		return;
	}
	else if (IS_END_OF_CLUSTER (extent))
	{
		printf("end\n");
		return;
	}
	else
	{
		printf ("%u\n", extent);
		cluster_dump (ins, extent);
	}
}
