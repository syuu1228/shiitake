#define	DEV_CONS_ADDRESS		0x0000000010000000
#define	DEV_CONS_LENGTH			0x0000000000000020
#define	    DEV_CONS_PUTGETCHAR		    0x0000
#define	    DEV_CONS_HALT		    0x0010

#define	DEV_ETHER_ADDRESS		0x14000000
#define	DEV_ETHER_LENGTH		0x8000

#define	    DEV_ETHER_BUFFER		    0x0000
#define	    DEV_ETHER_BUFFER_SIZE	    0x4000
#define	    DEV_ETHER_STATUS		    0x4000
#define	    DEV_ETHER_PACKETLENGTH	    0x4010
#define	    DEV_ETHER_COMMAND		    0x4020

/*  Status bits:  */
#define	DEV_ETHER_STATUS_PACKET_RECEIVED		1
#define	DEV_ETHER_STATUS_MORE_PACKETS_AVAILABLE		2

/*  Commands:  */
#define	DEV_ETHER_COMMAND_RX		0
#define	DEV_ETHER_COMMAND_TX		1

#define	DEV_DISK_ADDRESS		0x13000000
#define	    DEV_DISK_OFFSET		    0x0000
#define	    DEV_DISK_ID			    0x0010
#define	    DEV_DISK_START_OPERATION	    0x0020
#define	    DEV_DISK_STATUS		    0x0030
#define	    DEV_DISK_BUFFER		    0x4000

#define	    DEV_DISK_BUFFER_LEN		0x200

/*  Operations:  */
#define	DEV_DISK_OPERATION_READ		0
#define	DEV_DISK_OPERATION_WRITE	1

/*  Physical base address for linear framebuffer memory:  */
#define	DEV_FB_ADDRESS			0x12000000

/*  Physical base address for the framebuffer controller:  */
#define	DEV_FBCTRL_ADDRESS		0x12f00000
#define	DEV_FBCTRL_LENGTH		      0x20

/*
 *  First choose the port by writing the port index to DEV_FBCTRL_PORT,
 *  then read or write DEV_FBCTRL_DATA.
 */

#define	DEV_FBCTRL_PORT			      0x00
#define	DEV_FBCTRL_DATA			      0x10

#define	DEV_FBCTRL_PORT_COMMAND			0
#define	DEV_FBCTRL_PORT_X1			1
#define	DEV_FBCTRL_PORT_Y1			2
#define	DEV_FBCTRL_PORT_X2			3
#define	DEV_FBCTRL_PORT_Y2			4
#define	DEV_FBCTRL_PORT_COLOR_R			5
#define	DEV_FBCTRL_PORT_COLOR_G			6
#define	DEV_FBCTRL_PORT_COLOR_B			7
#define	DEV_FBCTRL_NPORTS		8

/*
 *  Controller commands:
 */

/*  Do nothing.  */
#define	DEV_FBCTRL_COMMAND_NOP				0

/*  Set resolution to X1 x Y1.  */
#define	DEV_FBCTRL_COMMAND_SET_RESOLUTION		1

/*  Get current resolution into X1, Y1.  */
#define	DEV_FBCTRL_COMMAND_GET_RESOLUTION		2

/*  TODO:  */
#define	DEV_FBCTRL_COMMAND_FILL				3
#define	DEV_FBCTRL_COMMAND_COPY				4

#define	DEV_FBCTRL_MAXY(x)	(((DEV_FBCTRL_ADDRESS-DEV_FB_ADDRESS) / 3) / x)

#define	DEV_RTC_ADDRESS			0x0000000015000000
#define	DEV_RTC_LENGTH			0x0000000000000200

#define	    DEV_RTC_TRIGGER_READ	    0x0000
#define	    DEV_RTC_SEC			    0x0010
#define	    DEV_RTC_USEC		    0x0020

#define	    DEV_RTC_HZ			    0x0100
#define	    DEV_RTC_INTERRUPT_ACK	    0x0110

#define PHYSADDR_OFFSET	((signed int)0xa0000000)
#define PUTCHAR_ADDRESS	(PHYSADDR_OFFSET +		\
							DEV_CONS_ADDRESS + DEV_CONS_PUTGETCHAR)
#define HALT_ADDRESS		(PHYSADDR_OFFSET +		\
							DEV_CONS_ADDRESS + DEV_CONS_HALT)
#define DISK_ADDRESS		(PHYSADDR_OFFSET + DEV_DISK_ADDRESS)
#define NCPUS_ADDRESS		(PHYSADDR_OFFSET +		\
							DEV_MP_ADDRESS + DEV_MP_NCPUS)
#define FB_BASE			(PHYSADDR_OFFSET + DEV_FB_ADDRESS)
#define FBCTRL_BASE		(PHYSADDR_OFFSET + DEV_FBCTRL_ADDRESS)
#define RTC_ADDRESS		(PHYSADDR_OFFSET +		\
							DEV_RTC_ADDRESS)
