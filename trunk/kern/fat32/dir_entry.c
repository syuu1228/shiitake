#include <kern/fat32/dir_entry.h>
#include <lib/string.h>
#include <lib/assert.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

static inline int sfncpy(char *dest, char *src, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
		if (src[i] == '\0'||src[i] == ' ')
			break;
	}
	dest[i] = '\0';
	return i;
}
void
dir_entry_dump (dir_entry_t *dir)
{
  DPRINTF("dir:%p\n", dir);
  if(!dir)
  {
	  DPRINTF("dir_entry is nil\n");
	  return ;
  }
  assert (sizeof (dir_entry_date_t) == 2);
  assert (sizeof (dir_entry_time_t) == 2);
  assert (sizeof (dir_attributes_t) == 1);
  assert (sizeof (dir_entry_t) == 32);
  printf ("\nname:");
  putns ((const char *) dir->name, 8);
  printf ("\nextension:");
  putns ((const char *) dir->extension, 3);
  puts ("\nattributes:");
  dir_attributes_dump (&(dir->attributes));
  printf ("ntReserved:%u\n", dir->nt_reserved);
  printf ("createTimeMs:%u\n", dir->create_time_ms);
  puts ("createTime:");
  time_dump (&(dir->create_time));
  puts ("createDate:");
  date_dump (&(dir->create_date));
  puts ("accessDate:");
  date_dump (&(dir->access_date));
  printf ("clusterHI:%p\n", dir->cluster_hi);
  puts ("updateTime:");
  time_dump (&(dir->update_time));
  puts ("updateDate:");
  date_dump (&(dir->update_date));
  printf ("clusterLO:%p\n", dir->cluster_lo);
  printf ("fileSize:%u\n", dir->file_size);
  printf ("shortNameCheckCode:%p\n", dir_entry_short_name_check_code (dir));
}

void
dir_attributes_dump (dir_attributes_t *attributes)
{
  DPRINTF("attributes:%p\n", attributes);
  printf ("\treadOnly:%u\n", attributes->read_only);
  printf ("\thidden:%u\n", attributes->hidden);
  printf ("\tsystem:%u\n", attributes->system);
  printf ("\tvolumeLabel:%u\n", attributes->volume_label);
  printf ("\tdirectory:%u\n", attributes->directory);
  printf ("\tarchive:%u\n", attributes->archive);
}

void
time_dump (dir_entry_time_t *time)
{ 
  DPRINTF("time:%p\n", time);
  printf ("\thour:%u\n", time->hour);
  printf ("\tminite:%u\n", time->minite);
  printf ("\tSec:%u\n", time->two_sec * 2);
}

void
date_dump (dir_entry_date_t *date)
{
	DPRINTF("date:%p\n", date);
  printf ("\tyear:%u\n", date->year + 1980);
  printf ("\tmonth:%u\n", date->month);
  printf ("\tdate:%u\n", date->date);
}

uint8_t
dir_entry_short_name_check_code (dir_entry_t *dir)
{
  DPRINTF("dir:%p\n", dir);
  uint8_t *p = (uint8_t *) dir->name;
  uint8_t *end = p + 11;
  uint8_t ret = 0;
  while (p < end)
    ret = (((ret & 1) << 7) | ((ret & 0xfe) >> 1)) + *p++;
  DPRINTF("return:%u\n", ret);
  return ret;
}

cluster_t
dir_entry_get_cluster (dir_entry_t *dir)
{
  DPRINTF("dir:%p\n", dir);
  cluster_t res;
  ((uint16_t *) & res)[0] = dir->cluster_lo;
  ((uint16_t *) & res)[1] = dir->cluster_hi;
  DPRINTF("return:%u\n", res);
  return res;
}

void 
dir_entry_combine_short_name(dir_entry_t *dir, char *buf)
{
	int pos = sfncpy (buf, dir->name, 8);
	if (dir->extension[0] != ' ')
	{
		buf[pos++] = '.';
		pos = sfncpy (&(buf[pos]), dir->extension, 3);
	}
}
