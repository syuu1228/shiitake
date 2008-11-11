#include <kern/file_system.h>
#include <kern/file_descriptor.h>
#include <kern/fat32/fat_instance.h>
#include <kern/fat32/fat_dir.h>
#include <kern/fat32/fat_file.h>
#include <kern/fat32/fat_path.h>
#include <lib/string.h>
#include <arch/config.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)

static fat_instance_t *ins;

void 
file_system_init(void)
{
	file_descriptor_init();
	if (!(ins = fat_instance_new(DISK_ID, PARTITION_NO)))
		panic("fat32fs initialize failed.\n");
}

int 
getattr(const char *path, stat *stbuf)
{
	DPRINTF("path:%s stbuf:%p\n", path, stbuf);

	fat_dir_entry_t dir;
	if (fat_path_get_entry(ins, path, &dir) < 0)
		return -1;
	memset(stbuf, 0, sizeof(stat));
	if (dir.dir_entry.attributes.directory)
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	else
	{
		stbuf->st_mode = S_IFREG | 0644;
		stbuf->st_nlink = 1;
	}
	stbuf->st_size = dir.dir_entry.file_size;
	stbuf->st_ino = dir_entry_get_cluster(&dir.dir_entry);
	return 0;
}

int 
opendir(const char *name)
{
	DPRINTF("name:%s\n", name);
	file_descriptor_t *fd = file_descriptor_new();
	if(!fd)
	{
		DPRINTF("return:-1\n");
		return -1;
	}
	fat_file_t *dir = fat_file_open(ins, name);
	if (!dir)
	{
		DPRINTF("return:-1\n");
		return -1;
	}
	fd->private_data =(void *)dir;
	file_descriptor_open(fd);
	DPRINTF("return:%d\n", fd->no);
	return fd->no;
}

dirent *
readdir(int fno)
{
	static dirent d;
	fat_dir_entry_t dir;
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return NULL;
	if (!fd->private_data)
		return NULL;
	if (fat_dir_read((fat_file_t *)fd->private_data, &dir) < 0)
	return NULL;
	memset(&d, 0, sizeof(dirent));
	strcpy(d.d_name, dir.short_name);
	d.d_reclen = strlen(dir.short_name);
	d.d_ino = dir_entry_get_cluster(&dir.dir_entry);
	if(dir.dir_entry.attributes.directory)
	d.d_type = DT_DIR;
	else
	d.d_type = DT_REG;
	DPRINTF("dirent:%p ino:%d off:%u reclen:%d type:%d\n",
	&d, d.d_ino, d.d_off, d.d_reclen, d.d_type);
	return &d;
}

off_t 
seekdir(int fno, off_t offset)
{
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return;
	if (!fd->private_data)
		return -1;
	return fat_file_seek_set((fat_file_t *)fd->private_data, offset);
}

off_t 
telldir(int fno)
{
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return 0;
	if (!fd->private_data)
		return -1;
	return fat_file_tell((fat_file_t *)fd->private_data);
}

int 
closedir(int fno)
{
	int ret;
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return -1;
	if (!fd->private_data)
		return -1;
	ret = fat_file_close((fat_file_t *)fd->private_data);
	file_descriptor_close(fd);
	return ret;
}

int 
open(const char *path, int flags, mode_t mode)
{
	file_descriptor_t *fd = file_descriptor_new();
	if(!fd)
		return -1;
	fat_file_t *file = fat_file_open(ins, path);
	if (!file)
		return -1;
	fd->private_data =(void *)file;
	file_descriptor_open(fd);
	return fd->no;
}

ssize_t 
read(int fno, void *buf, size_t count)
{
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return -1;
	if (!fd->private_data)
		return -1;
	return fat_file_read((fat_file_t *)fd->private_data, buf, count);
}

off_t 
lseek(int fno, off_t offset, int whence)
{
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return -1;
	if (!fd->private_data)
		return -1;
	return fat_file_seek_set((fat_file_t *)fd->private_data, offset);
}

int 
close(int fno)
{
	int ret;
	file_descriptor_t *fd = file_descriptor_get(fno);

	if(!fd)
		return -1;
	if (!fd->private_data)
		return -1;
	ret = fat_file_close((fat_file_t *)fd->private_data);
	file_descriptor_close(fd);
	return ret;
}
