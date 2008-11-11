#include <kern/fat32/cluster_data.h>
#include <kern/fat32/cluster.h>
#include <lib/assert.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

static inline sector_t cluster_data_head_sector(bpb_t *bpb)
{
	DPRINTF("bpb:%p\n", bpb);
	uint32_t res = bpb->sectors_per_fat32 * bpb->number_of_fats
			+ bpb->reserved_sectors;
	DPRINTF("return:%u\n", res);
	return res;
}

off_t 
cluster_data_offset(fat_instance_t *ins, const cluster_t cluster_no)
{
	assert(!IS_END_OF_CLUSTER(cluster_no) && !IS_BAD_CLUSTER(cluster_no));
	DPRINTF("ins:%p clusterNo:%u\n", ins, cluster_no);
	off_t res = fat_instance_sector_to_offset (ins,
			cluster_data_head_sector (ins->bpb)+ bpb_cluster_to_sector (
					ins->bpb, cluster_no -2));
	DPRINTF("return:%u\n", res);
	return res;
}

ssize_t
cluster_data_read (fat_instance_t *ins, const cluster_t cluster_no, 
		   void *buffer, off_t o, size_t count)
{
	DPRINTF("ins:%p cluster_no:%u buffer:%p offset:%u\n", 
		ins, cluster_no, buffer, o);
	DPRINTF("count:%u\n", count);
	assert(!IS_BAD_CLUSTER(cluster_no));
	if(IS_END_OF_CLUSTER(cluster_no))
		return 0;
	assert(o + count <=  bpb_cluster_size(ins->bpb));
	off_t offset = cluster_data_offset (ins, cluster_no) + o;
	ssize_t ret;
	if((ret = disk_read (ins->disk_id, buffer, offset, count)) != count)
		DPRINTF("read failed\n");
	DPRINTF("return:%d\n", ret);
	return ret;
}
