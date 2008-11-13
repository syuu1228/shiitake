#include <kern/fat32/cluster_data.h>
#include <kern/fat32/fat_file.h>
#include <kern/fat32/fat_type.h>
#include <kern/fat32/fat_path.h>
#include <kern/memory.h>
#include <lib/assert.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

fat_file_t *
fat_file_new(fat_instance_t *ins, fat_cluster_list_t *cluster)
{
	DPRINTF("ins:%p cluster:%p\n", ins, cluster);
	assert(ins);
	if(!cluster)
		return NULL;
	fat_file_t *file = (fat_file_t *) calloc (1, sizeof(fat_file_t));
	if (!file)
	{
		DPRINTF ("malloc failed");
		return NULL;
	}
	file->ins = ins;
	file->cluster = cluster;
	return file;
}

fat_file_t *
fat_file_open(fat_instance_t *ins, const char *path)
{
	return fat_file_new(ins, fat_path_get_cluster(ins, path));
}

ssize_t 
fat_file_read(fat_file_t *file, unsigned char *buffer, size_t c)
{
	DPRINTF("file:%p buffer:%p count:%u\n", file, buffer, c);
	size_t count = c;
	off_t offset = file->offset;
	
	while (c >= bpb_cluster_size(file->ins->bpb))
	{
		ssize_t res = cluster_data_read (file->ins, fat_cluster_list_read(file->cluster), buffer,
				offset, bpb_cluster_size(file->ins->bpb) - offset);
		c -= res;
		if (res != bpb_cluster_size(file->ins->bpb))
		{
			fat_file_seek_cur(file, res);
			return count - c;
		}
		buffer += res;
		offset = 0;
		if(IS_END_OF_CLUSTER(fat_cluster_list_next(file->cluster)))
			return count - c;
	}
	
	if (!c)
		return count;
	ssize_t res = cluster_data_read (file->ins, fat_cluster_list_read(file->cluster), buffer, offset, c);
	fat_file_seek_cur(file, res);
	if (res != c - offset)
		return res;
	assert(c - res == 0);
	assert(offset + c <= bpb_cluster_size(file->ins->bpb));
	if (offset + c == bpb_cluster_size(file->ins->bpb))
		fat_cluster_list_next(file->cluster);
	return count;
}

off_t 
fat_file_seek_set(fat_file_t *file, off_t o)
{
	off_t offset = o;
	DPRINTF("file:%p offset:%u\n", file, o);
	if (o >= bpb_cluster_size(file->ins->bpb))
	{
		cluster_t coff = o / bpb_cluster_size(file->ins->bpb);
		if(fat_cluster_list_seek_set(file->cluster, coff) < 0)
			return 0;
		o -= coff * bpb_cluster_size(file->ins->bpb);
	}
	file->offset = o;
	return offset;
}

off_t 
fat_file_seek_cur(fat_file_t *file, off_t o)
{
	off_t offset = o;
	DPRINTF("file:%p offset:%u\n", file, o);
	o += file->offset;
	if(o >= bpb_cluster_size(file->ins->bpb))
	{
		cluster_t coff = o / bpb_cluster_size(file->ins->bpb);
		if(fat_cluster_list_seek_cur(file->cluster, coff) < 0)
			return 0;
		o -= coff * bpb_cluster_size(file->ins->bpb);
	}
	file->offset = o;
	return offset;
}

off_t 
fat_file_tell (fat_file_t *file)
{
	return file->offset + fat_cluster_list_tell(file->cluster) * bpb_cluster_size(file->ins->bpb); 
}

int 
fat_file_close(fat_file_t *file)
{
	DPRINTF("file:%p\n", file);
	fat_cluster_list_close(file->cluster);
	free(file);
	return 0;
}
