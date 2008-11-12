#include <kern/disk.h>
#include <i386/config.h>
#include <lib/string.h>
#include <lib/console.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
//#define DPRINTF(...) do{}while(0)


static inline uint8_t inb(uint16_t port)
{
	uint8_t value;
	asm volatile("inb %%dx,%0" : "=a"(value) : "d"(port));
	return value;
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t value;
	asm volatile("inw %%dx,%0" : "=a"(value) : "d"(port));
	return value;
}

static inline uint16_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile("inl %%dx,%0" : "=a"(value) : "d"(port));
	return value;
}

static inline void outb(uint8_t value, uint16_t port)
{
	asm volatile("outb %0,%%dx" : : "a"(value), "d"(port));
}

static inline void outw(uint16_t value, uint8_t port)
{
	asm volatile("outw %0,%%dx" : : "a"(value), "d"(port));
}

static inline void outl(uint32_t value, uint8_t port)
{
	asm volatile("outw %0,%%dx" : : "a"(value), "d"(port));
}

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

#define IDE_COMMAND_PIO_READ 0xec

void md_disk_init(int id)
{
	// プライマリのみ初期化
	
	// 割込み不許可
	outb (0x02, 0x3F6);
	
	// マスタデバイス選択
	while ((inb(0x1F7) & 0x88) != 0x00);
	outb ((inb(0x1F6) & 0xEF), 0x1F6);

	// SET FEATUREコマンド(割込み禁止中)
	while ((inb(0x1F7) & 0x88) != 0x00);
	printf ("select,");
	
	outb (0x03, 0x1F1);
	// PIO4モード
	outb (0x0C, 0x1F2);
	outb (0x00, 0x1F3);
	outb (0x00, 0x1F4);
	outb (0x00, 0x1F5);
	outb (0x00, 0x1F6);
	outb (0xEF, 0x1F7);
	
	// ステータスの引取り
	while ((inb(0x1F7) & 0x88) != 0x00);
}

int 
md_disk_sector_read(int id, unsigned char *buf, uint32_t lba, uint8_t count)
{
	// READ SECTORSコマンド(割込みフェーズあり)
	outb (0x00, 0x1F1);
	outb (count, 0x1F2);
	// sector number (LBA[7:0])
	outb ((lba & 0xFF), 0x1F3);
	// cylinder low (LBA[15:8])
	outb (((lba >> 8) & 0xFF), 0x1F4);
	// cylinder high (LBA[23:16])
	outb (((lba >> 16) & 0xFF), 0x1F5);
	// device/head(マスタ，LBAモード，LBA[27:24])
	outb ((0xE0 | ((lba >> 24) & 0xF)), 0x1F6);
	outb (0x20, 0x1F7);
	
	do
	{ // 全セクタ読込み完了まで
		// バースト転送準備完了待ち
		while ((inb(0x1F7) & 0x08) != 0x08);
		printf ("cmd,"); 
		do
		{ // データ読取り
			unsigned short data = inw (0x1F0);
			*buf++ = data & 0xFF;
			*buf++ = (data >> 8) & 0xFF;
		} while ((inb(0x1F7) & 0x88) == 0x08);
		
	} while ((inb(0x1F7) & 0x88) != 0x00);
	printf ("data\n");
	return 0;
}

int 
md_disk_sector_write(int id, const unsigned char *buf, uint32_t lba, uint8_t count)
{
	DPRINTF("id:%d buf:%p lba:%u count:%u\n",
		id, buf, lba, count);

	return -1;
}
