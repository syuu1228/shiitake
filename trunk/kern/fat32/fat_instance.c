#include <kern/fat32/fat_instance.h>
#include <kern/mbr.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

fat_instance_t *fat_instance_new(int disk_id, int partition_no)
{
	fat_instance_t *ins = 
		(fat_instance_t *) calloc (1, sizeof(fat_instance_t));
	if (!ins)
	{
		DPRINTF ("malloc failed\n");
		return NULL;
	}
	mbr_t *m = mbr_read(disk_id);
	if(!m)
	{
		DPRINTF ("mbr read failed\n");
		free(ins);
		return NULL;
	}
#ifdef DEBUG
	mbr_dump(m);
#endif
	ins->disk_id = disk_id;
	ins->partition = m->partition_table + partition_no;
	if (!bpb_read (ins))
		goto kfree_and_return;
#ifdef DEBUG
	bpb_dump(ins->bpb);
#endif
	if (!bpb_validate (ins->bpb))
		goto kfree_and_return;
	if (ins->bpb->bytes_per_sector != MBR_SECTOR_SIZE)
	{
		DPRINTF ("Illigal sector size\n");
		goto kfree_and_return;
	}
	return ins;
kfree_and_return: 
	free (ins);
	return NULL;
}

void 
fat_instance_delete(fat_instance_t * ins)
{
	free (ins->bpb);
	free (ins);
}

void 
fat_instance_dump(fat_instance_t * ins)
{
	bpb_dump (ins->bpb);
	bpb_cluster_size (ins->bpb);
	bpb_count_of_clusters (ins->bpb);
}

off_t 
fat_instance_head_offset(fat_instance_t * ins)
{
	DPRINTF("ins:%p\n", ins);
	off_t res = mbr_partition_offset (ins->partition);
	DPRINTF("return:%u\n", res);
	return res;
}

off_t 
fat_instance_byte_to_offset(fat_instance_t * ins, off_t byte)
{
	DPRINTF("ins:%p byte:%u\n", ins, byte);
	off_t res = fat_instance_head_offset (ins) + byte;
	DPRINTF("return:%u\n", res);
	return res;
}

off_t 
fat_instance_sector_to_offset(fat_instance_t * ins, sector_t sector)
{
	DPRINTF("ins:%p sector:%u\n", ins, sector);
	off_t res = 
		fat_instance_byte_to_offset (ins, 
					     bpb_sector_to_byte (ins->bpb,
								 sector));

	DPRINTF("return:%u\n", res);
	return res;
}

off_t 
fat_instance_cluster_to_offset(fat_instance_t * ins, cluster_t cluster)
{
	DPRINTF("ins:%p cluster:%u\n", ins, cluster);
	off_t res = 
		fat_instance_sector_to_offset (ins, 
					       bpb_cluster_to_sector (
						       ins->bpb, cluster));
	DPRINTF("return:%u\n", res);
	return res;
}
