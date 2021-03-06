#include <kern/fat32/fat_path.h>
#include <kern/fat32/fat_file.h>
#include <kern/fat32/fat_dir.h>
#include <lib/string.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

static char * pathtok(const char *p);

static char * 
pathtok(const char *p)
{
	static int start, end;
	static const char *path;
	static char buf[256];

	if (p)
	{
		start = end = 1;
		path = p;
		return NULL;
	}
	while (path[end] && !(path[end] == '/'&& !path[end + 1]))
	{
		memset(buf, 0, 256);
		for (end = start; path[end] && path[end] != '/'; end++)
			;
		strncpy(buf, path + start, end - start);
		start = end + 1;
		return buf;
	}
	return NULL;
}

int 
fat_path_get_entry(fat_instance_t *ins, const char *path, fat_dir_entry_t *dir)
{
	char *name;
	bool root_dir = true;
	
	if (!strcmp("/", path))
	{
		memset(dir, 0, sizeof(fat_dir_entry_t));
		dir->dir_entry.attributes.directory = 1;
		dir->dir_entry.cluster_lo = ins->bpb->root_dir_cluster;
		return 0;
	}
	pathtok(path);
	while ((name = pathtok(NULL)))
	{
		fat_cluster_list_t *list;
		fat_file_t *file;
		DPRINTF("name:%s\n", name);
		if (root_dir)
		{
			list = fat_cluster_list_open_by_cluster_no(ins, ins->bpb->root_dir_cluster);
			root_dir = false;
		}else
			list = fat_cluster_list_open_by_fat_dir_entry(ins, dir);

		if (!list)
			return -1;
		file = fat_file_new(ins, list);
		if (!file)
		{
			fat_cluster_list_close(list);
			return -1;
		}
		if (fat_dir_find(file, name, dir) < 0)
		{
			fat_file_close(file);
			return -1;
		}
		fat_file_close(file);
	}
	return 0;
}

fat_cluster_list_t *
fat_path_get_cluster(fat_instance_t *ins, const char *path)
{
	fat_dir_entry_t dir;
	if (!strcmp("/", path))
		return fat_cluster_list_open_by_cluster_no(ins, ins->bpb->root_dir_cluster);
	if (fat_path_get_entry(ins, path, &dir) < 0)
		return NULL;
	return fat_cluster_list_open_by_fat_dir_entry(ins, &dir);
}
