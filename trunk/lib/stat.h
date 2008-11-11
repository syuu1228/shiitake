#ifndef LIB_STAT_H_
#define LIB_STAT_H_
#include <lib/types.h>

typedef struct
{
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
} stat;

#define S_IFDIR       010000
#define S_IFREG       020000

#endif /* LIB/STAT_H_*/
