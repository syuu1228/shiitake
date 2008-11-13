#include <kern/disk.h>
#include <i386/config.h>
#include <i386/cpu.h>
#include <lib/string.h>
#include <lib/console.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
//#define DPRINTF(...) do{}while(0)

#define IDE_REG_DATA            0x01f0
#define IDE_REG_ERROR           0x01f1
#define IDE_REG_FEATURES        0x01f1
#define IDE_REG_SECTOR_COUNT    0x01f2
#define IDE_REG_SECTOR_NUMBER   0x01f3
#define IDE_REG_CYLINDER_LOW    0x01f4
#define IDE_REG_CYLINDER_HIGH   0x01f5
#define IDE_REG_DEVICE_HEAD     0x01f6
#define IDE_REG_STATUS          0x01f7
#define IDE_REG_COMMAND         0x01f7
#define IDE_REG_ALTRNATE_STATUS 0x03f6
#define IDE_REG_DEVICE_CONTROL  0x03f6

#define IDE_STATUS_ERR  0x01
#define IDE_STATUS_DRQ  0x08
#define IDE_STATUS_DRDY 0x40
#define IDE_STATUS_BSY  0x80

#define IDE_COMMAND_READ_SECTORS 0x20
#define IDE_COMMAND_SET_FEATURES 0xef

#define IDE_DEVICE_CONTROL_NIEN 0x2
#define IDE_DEVICE_CONTROL_SRST 0x4

#define IDE_COMMAND_PIO_READ 0xec

void md_disk_init(int id)
{
	ioport_write8(IDE_REG_DEVICE_CONTROL, IDE_DEVICE_CONTROL_NIEN); 
	
	while((ioport_read8(IDE_REG_STATUS) & 
	       (IDE_STATUS_DRQ|IDE_STATUS_BSY)) != 0)
		;
	ioport_write8(IDE_REG_DEVICE_HEAD, 
		      ioport_read8(IDE_REG_DEVICE_HEAD) & 0xEF);

	while((ioport_read8(IDE_REG_STATUS) & 
	       (IDE_STATUS_DRQ|IDE_STATUS_BSY)) != 0)
		;
	
	ioport_write8(IDE_REG_FEATURES, 0x03);
	ioport_write8(IDE_REG_SECTOR_COUNT, 0x0C);
	ioport_write8(IDE_REG_SECTOR_NUMBER, 0x00);
	ioport_write8(IDE_REG_CYLINDER_LOW, 0x00);
	ioport_write8(IDE_REG_CYLINDER_HIGH, 0x00);
	ioport_write8(IDE_REG_DEVICE_HEAD, 0x00);
	ioport_write8(IDE_REG_COMMAND, IDE_COMMAND_SET_FEATURES);
	
	while((ioport_read8(IDE_REG_STATUS) & 
	       (IDE_STATUS_DRQ|IDE_STATUS_BSY)) != 0)
		;
}

int 
md_disk_sector_read(int id, unsigned char *buf, uint32_t lba, uint8_t count)
{
	uint16_t *sbuf = (unsigned short *)buf;
	ioport_write8(IDE_REG_FEATURES, 0x00);
	ioport_write8(IDE_REG_SECTOR_COUNT, count);
	ioport_write8(IDE_REG_SECTOR_NUMBER, (lba & 0xff)); /* lba[7:0] */
	ioport_write8(IDE_REG_CYLINDER_LOW, (lba >> 8) & 0xff); /* lba[15:8] */
	ioport_write8(IDE_REG_CYLINDER_HIGH, (lba >> 16) & 0xff); /* lba[23:16] */
	ioport_write8(IDE_REG_DEVICE_HEAD, ((lba >> 24) & 0xf) | 0xe0); /* lba[27:24] */
	ioport_write8(IDE_REG_COMMAND, IDE_COMMAND_READ_SECTORS);
	do
	{
		while((ioport_read8(IDE_REG_STATUS) & IDE_STATUS_DRQ)
		      != IDE_STATUS_DRQ)
			;
		do
		
			*sbuf++ = ioport_read16(IDE_REG_DATA) & 0xffff;
		while((ioport_read8(IDE_REG_STATUS) & 
		       (IDE_STATUS_DRQ|IDE_STATUS_BSY)) == IDE_STATUS_DRQ);
	} while ((ioport_read8(IDE_REG_STATUS) &
		  (IDE_STATUS_DRQ|IDE_STATUS_BSY)) != 0);
	return 0;
}

int 
md_disk_sector_write(int id, const unsigned char *buf, uint32_t lba, uint8_t count)
{
	DPRINTF("id:%d buf:%p lba:%u count:%u\n",
		id, buf, lba, count);

	return -1;
}
