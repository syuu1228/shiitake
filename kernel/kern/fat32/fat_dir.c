#include <kern/fat32/fat_dir.h>
#include <lib/string.h>
#include <lib/assert.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

int 
fat_dir_read(fat_file_t *file, fat_dir_entry_t *dir)
{
	DPRINTF("file:%p\n", file);

	retry:
	if ((fat_file_read(file, (unsigned char *)&(dir->dir_entry), sizeof(dir_entry_t)))
			!= sizeof(dir_entry_t))
	{
		DPRINTF("read failed\n");
		return -1;
	}
	if (DIR_ENTRY_IS_END(&(dir->dir_entry)))
	{
		DPRINTF("dir is end\n");
		return -1;
	}else if (DIR_ENTRY_IS_DELETED(&(dir->dir_entry)) || 
		  DIR_ENTRY_IS_LDIR_ENTRY(&(dir->dir_entry)))
	{
		DPRINTF("retrying\n");
		goto retry;
	}else{
		dir_entry_combine_short_name(&(dir->dir_entry), 
					     dir->short_name);
		
	}
	return 0;
}

int 
fat_dir_find(fat_file_t * file, const char *name, fat_dir_entry_t *dir)
{
	DPRINTF("file:%p name:%s\n", file, name);
	
	while (!fat_dir_read (file, dir))
	{
		if (!strncmp (dir->short_name, name, 12))
		{
			DPRINTF("%s matched with %p\n", name, dir);
			return 0;
		}
		else
			DPRINTF("%s doesn't match with %s\n", 
				name, dir->short_name);
	}
	return -1;
}
