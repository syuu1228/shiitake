#include <kern/fat32/bpb.h>
#include <kern/fat32/fat_instance.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

static inline sector_t bpb_root_dir_sectors(bpb_t *bpb)
{
	DPRINTF("bpb:%p\n", bpb);
	sector_t res =((bpb->root_entries * 32)+(bpb->bytes_per_sector - 1))
			/ bpb->bytes_per_sector;
	DPRINTF("return:%u\n", res);
	return res;
}

static inline sector_t bpb_data_sectors(bpb_t *bpb)
{
	DPRINTF("bpb:%p\n", bpb);
	sector_t res = bpb->total_sectors32- (bpb->reserved_sectors
			+(bpb->number_of_fats * bpb->sectors_per_fat32))
			+bpb_root_dir_sectors (bpb);
	DPRINTF("return:%u\n", res);
	return res;
}

bool 
bpb_validate_cluster_no(bpb_t *bpb, cluster_t clusterNo)
{
	DPRINTF("bpb:%p clusterNo:%u\n", bpb, clusterNo);
	return (bpb_count_of_clusters(bpb) >= clusterNo
			&& clusterNo > 1);
}

bool
bpb_validate (bpb_t *bpb)
{
	if(!bpb->total_sectors16 && bpb->signature == 0xaa55)
		return true;
	return false;
}

bool
bpb_read (void *ptr)
{
	fat_instance_t *ins = (fat_instance_t *)ptr;
	DPRINTF("ins:%p\n", ins);
	ins->bpb = (bpb_t *) calloc (1, sizeof (bpb_t));
	if (!ins->bpb)
	{
		DPRINTF("malloc failed\n");
		DPRINTF("return:false\n");
		return false;
	}
	if ((disk_read (ins->disk_id, ins->bpb, fat_instance_head_offset (ins), sizeof (bpb_t))) != sizeof (bpb_t))
	{
		DPRINTF("read failed\n");
		DPRINTF("return:false\n");
		return false;
	}
	DPRINTF("return:true\n");
	return true;
}

cluster_t 
bpb_count_of_clusters(bpb_t *bpb)
{
	DPRINTF("bpb:%p\n", bpb);
	cluster_t res = bpb_data_sectors (bpb) / bpb->sectors_per_cluster;
	DPRINTF("return:%u\n", res);
	return res;
}

uint32_t 
bpb_cluster_size(bpb_t *bpb)
{
	DPRINTF("bpb:%p\n", bpb);
	uint32_t res = bpb->sectors_per_cluster * bpb->bytes_per_sector;
	DPRINTF("return:%u\n", res);
	return res;
}

void 
bpb_dump(bpb_t *bpb)
{
	printf ("JmpOpeCode:%p %p %p\n", bpb->jmp_ope_code[0],
			bpb->jmp_ope_code[1], bpb->jmp_ope_code[2]);
	printf ("OEMName:");
	putns ((const char *) bpb->oem_name, 8);
	printf ("\nBytesPerSector:%u\n", bpb->bytes_per_sector);
	printf ("SectorsPerCluster:%u\n", bpb->sectors_per_cluster);
	printf ("ReservedSectors:%u\n", bpb->reserved_sectors);
	printf ("NumberOfFATs:%u\n", bpb->number_of_fats);
	printf ("RootEntries:%u\n", bpb->root_entries);
	printf ("TotalSectors16:%u\n", bpb->total_sectors16);
	printf ("MediaDescriptor:%u\n", bpb->media_descriptor);
	printf ("SectorsPerFAT16:%u\n", bpb->sectors_per_fat16);
	printf ("SectorsPerTrack:%u\n", bpb->sectors_per_track);
	printf ("Heads:%u\n", bpb->heads);
	printf ("HiddenSectors:%u\n", bpb->hidden_sectors);
	printf ("TotalSectors32:%u\n", bpb->total_sectors32);

	printf ("SectorsPerFAT32:%u\n", bpb->sectors_per_fat32);
	printf ("ExtFlags:%u\n", bpb->ext_flags);
	printf ("FSVersion:%u\n", bpb->fs_version);
	printf ("RootDirCluster:%u\n", bpb->root_dir_cluster);
	printf ("FSInfoSector:%u\n", bpb->fs_info_sector);
	printf ("BackupBootSector:%u\n", bpb->backup_boot_sector);
	printf ("DriveNumber:%u\n", bpb->drive_number);
	printf ("BootSignature:%u\n", bpb->boot_signature);
	printf ("VolumeID:%u\n", bpb->volume_id);
	printf ("VolumeLabel:");
	putns ((const char *) bpb->volume_label, 11);
	printf ("\nFileSystemType:");
	putns ((const char *) bpb->file_system_type, 8);
	printf ("\nSignature:%p\n", bpb->signature);
}

sector_t 
bpb_cluster_to_sector(bpb_t *bpb, cluster_t cluster)
{
	DPRINTF("bpb:%p cluster:%u\n", bpb, cluster);
	sector_t res = cluster * bpb->sectors_per_cluster;
	DPRINTF("return:%u\n", res);
	return res;
}

off_t 
bpb_sector_to_byte(bpb_t *bpb, sector_t sector)
{
	DPRINTF("bpb:%p sector:%u\n", bpb, sector);
	off_t res = sector * bpb->bytes_per_sector;
	DPRINTF("return:%u\n", res);
	return res;
}
