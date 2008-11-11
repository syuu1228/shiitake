#include <lib/types.h>

typedef struct
{
	ino_t d_ino;
	off_t d_off;
	unsigned short int d_reclen;
	unsigned char d_type;
	char d_name[256];
} dirent;

#define DT_DIR 1
#define DT_REG 2
