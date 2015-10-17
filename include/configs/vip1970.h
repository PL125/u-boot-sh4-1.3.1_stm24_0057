/*
 * (C) Copyright 2004 STMicroelectronics.
 *
 * Andy Sturges <andy.sturges@st.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */

#define CONFIG_SH4	1		/* This is an SH4 CPU		*/
#define CONFIG_CPU_SUBTYPE_SH4_2XX	/* its an SH4-202		*/

#ifndef INPUT_CLOCK_RATE
#warning Assuming 30MHz clock input
#define INPUT_CLOCK_RATE 30
#endif


/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * Assume we run out of uncached memory for the moment
 */

#ifdef CONFIG_SH_SE_MODE
#define CFG_FLASH_BASE		0xA0000000	/* FLASH (uncached) via PMB */
#define CFG_SDRAM_BASE		0x80000000      /* LMI-Sys via PMB */
#define CFG_SE_PHYSICAL_BASE	0x40000000	/* LMI-Sys Physical Address */
#define CFG_SE_UNACHED_BASE	0x90000000	/* LMI-Sys un-cached addr via PMB */
#define CFG_SE_SDRAM_WINDOW	(CFG_SDRAM_SIZE-1)
#else
#define CFG_FLASH_BASE		0xA0000000	/* FLASH in P2 region */
#define CFG_SDRAM_BASE		0x84000000      /* SDRAM in P1 region */
#endif

#define CFG_SDRAM_SIZE		0x04000000	/* 64 MiB of LMI-Sys SDRAM */

#define CFG_MONITOR_LEN		0x00020000	/* Reserve 128 KiB for Monitor */
#define CFG_MONITOR_BASE        CFG_FLASH_BASE
#define CFG_MALLOC_LEN		(1 << 20)	/* Reserve 1 MiB for malloc */
#define CFG_BOOTPARAMS_LEN	(128 << 10)
#define CFG_GBL_DATA_SIZE	1024		/* Global data structures */

#define CFG_MEMTEST_START	CFG_SDRAM_BASE
#define CFG_MEMTEST_END		(CFG_SDRAM_BASE + CFG_SDRAM_SIZE - (3 << 20))

#define CONFIG_BAUDRATE		115200
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define XSTR(s) STR(s)
#define STR(s) #s

#define BOARD vip1970

#if CFG_MONITOR_LEN == 0x00020000		/* 128 KiB */
#	define MONITOR_SECTORS	"1:0"		/* 1 sector */
#elif CFG_MONITOR_LEN == 0x00040000		/* 256 KiB */
#	define MONITOR_SECTORS	"1:0-1"		/* 2 sectors */
#else						/* unknown */
#	error "Unable to determine sectors for monitor"
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
		"board=" XSTR(BOARD) "_" XSTR(INPUT_CLOCK_RATE) "\0" \
		"monitor_base=" XSTR(CFG_MONITOR_BASE) "\0" \
		"monitor_len=" XSTR(CFG_MONITOR_LEN) "\0" \
		"monitor_sec=" MONITOR_SECTORS "\0" \
		"load_addr=" XSTR(CFG_LOAD_ADDR) "\0" \
		"unprot=" \
		  "protect off $monitor_sec\0" \
		"update=" \
		  "erase $monitor_sec;" \
		  "cp.b $load_addr $monitor_base $monitor_len;" \
		  "protect on $monitor_sec\0"

/*--------------------------------------------------------------
 * Command line configuration.
 */

#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_IDE

/*--------------------------------------------------------------
 * Serial console info
 */

/*
 * We can use one of two methods for the "serial" console.
 * We can either use the (normal hardware) internal ST ASC UART;
 * OR we can use STMicroelectronics' DTF (Data Transfer Format)
 * mechanism over a JTAG link to a remote GDB debugger.
 */
#if 1
#	define CONFIG_STM_ASC_SERIAL	/* use a ST ASC UART */
#else
#	define CONFIG_STM_DTF_SERIAL	/* use DTF over JTAG */
#endif

/* choose which ST ASC UART to use */
/* TO DO CORRECT THE IF ELSE STATEMENT */
#if 1
#	define CFG_STM_ASC_BASE		0xb8031000ul 	/* UART1 */
#if 2
#	define CFG_STM_ASC_BASE		0xb8032000ul	/* UART2 */
#else
#	define CFG_STM_ASC_BASE		0xb8033000ul	/* UART3 */
#endif

/*---------------------------------------------------------------
 * Ethernet driver config
 */

/*
 * Use the internal ST MAC device + LAN8700 PHY
 */
#	define CONFIG_DRIVER_NETSTMAC
#	define CFG_STM_STMAC_BASE	0xb8110000ul	/* MAC = STM MAC */
#	define CONFIG_STMAC_LAN8700			/* PHY = SMSC LAN8700 */
#	define CONFIG_CMD_MII


/*  If this board does not have eeprom for ethernet address so allow the user
 *  to set it in the environment
 */

#define CONFIG_ENV_OVERWRITE


/*---------------------------------------------------------------
 * USB driver config
 */

/* Choose if we want USB Mass-Storage Support */
//#define CONFIG_SH_STB7100_USB

#ifdef CONFIG_SH_STB7100_USB
#	define CONFIG_CMD_USB
#	define CONFIG_CMD_FAT
#	define CONFIG_USB_OHCI_NEW
#	define CONFIG_USB_STORAGE
#	define CFG_USB_OHCI_CPU_INIT
#	define CFG_USB_BASE			0xb9100000
#	define CFG_USB_OHCI_REGS_BASE		(CFG_USB_BASE+0xffc00)
#	define CFG_USB_OHCI_SLOT_NAME		"ohci"
#	define CFG_USB_OHCI_MAX_ROOT_PORTS	1
#	define LITTLEENDIAN
#endif	/* ifdef CONFIG_SH_STB7100_USB */

/*---------------------------------------------------------------
 * IDE driver config
 */

/* Choose one of the the following two: */
//#define CONFIG_SH_STB7100_IDE
#define CONFIG_SH_STB7100_SATA

#ifdef CONFIG_SH_STB7100_IDE
#	define CFG_PIO_MODE		4
#	define CFG_IDE_MAXBUS		1
#	define CFG_IDE_MAXDEVICE	1
#ifdef CONFIG_SH_SE_MODE
#	define CFG_ATA_BASE_ADDR	0xB2800000
#else	/* CONFIG_SH_SE_MODE */
#	define CFG_ATA_BASE_ADDR	0xA2800000
#endif	/* CONFIG_SH_SE_MODE */
#	define CFG_ATA_IDE0_OFFSET	0x00200000
#	define CFG_ATA_REG_OFFSET	0
#	define CFG_ATA_DATA_OFFSET	0
#	define CFG_ATA_STRIDE		0x00020000
#	define CFG_ATA_ALT_OFFSET	-0x0100000
#endif	/* CONFIG_SH_STB7100_IDE */

#ifdef CONFIG_SH_STB7100_SATA
#	define CFG_PIO_MODE		4
#	define CFG_IDE_MAXBUS		1
#	define CFG_IDE_MAXDEVICE	1
#	define CFG_ATA_BASE_ADDR	0xB9209800
#	define CFG_ATA_IDE0_OFFSET	0x0
#	define CFG_ATA_REG_OFFSET	0x0
#	define CFG_ATA_DATA_OFFSET	0x0
#	define CFG_ATA_STRIDE		0x4
#	define CFG_ATA_ALT_OFFSET	0x8
#endif	/* CONFIG_SH_STB7100_SATA */

#if defined(CONFIG_SH_STB7100_IDE)  ||	\
    defined(CONFIG_SH_STB7100_SATA) ||	\
    defined(CONFIG_SH_STB7100_USB)
#	define CFG_64BIT_LBA
#	define CONFIG_LBA48
#	define CONFIG_DOS_PARTITION
#	define CONFIG_CMD_EXT2
#endif

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */

#define CFG_HUSH_PARSER		1
#define CFG_LONGHELP		1		/* undef to save memory		*/
#define CFG_PROMPT		"VIP1970 # "	/* Monitor Command Prompt	*/
#define CFG_PROMPT_HUSH_PS2	"> "
#define CFG_CBSIZE		1024
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size	*/
#define CFG_MAXARGS		16		/* max number of command args	*/
#define CFG_HZ			1000		/* HZ for timer ticks	*/
#define CFG_LOAD_ADDR		CFG_SDRAM_BASE	/* default load address		*/
#define CONFIG_BOOTDELAY	1		/* Boot automatically after 1 second */
#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE       1

/*-----------------------------------------------------------------------
 * FLASH organization
 */

/* Choose if we want FLASH Support (NAND, NOR & SPI devices),
 * all three, or none, or any other combination.
 *
 * Note: by default CONFIG_CMD_FLASH is defined in config_cmd_default.h
 */
#undef CONFIG_CMD_FLASH		/* undefine it, define only if needed */
#define CONFIG_CMD_FLASH	/* define for NOR flash */
#define CONFIG_CMD_NAND		/* define for NAND flash */
#define CONFIG_SPI_FLASH	/* define for SPI serial flash */

/*-----------------------------------------------------------------------
 * NOR FLASH organization
 */

/*
 * Note: Only 14 address lines (A[14:1]) are wired up to the NOR flash, hence
 * only a total of 16KiB of the NOR flash is (uniquely) addressable!
 */
#ifdef CONFIG_CMD_FLASH				/* NOR flash present ? */
#	define CFG_FLASH_CFI_DRIVER
#	define CFG_FLASH_CFI
#	define CONFIG_FLASH_PROTECT_SINGLE_CELL
#	define CFG_FLASH_PROTECTION	1	/* use hardware flash protection	*/
#	define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#	define CFG_MAX_FLASH_SECT	1024	/* max number of sectors on one chip	*/
#	define CFG_FLASH_EMPTY_INFO		/* test if each sector is empty		*/
#	define MTDPARTS_NOR						\
	"physmap-flash:"	/* First NOR flash device */		\
		"256k(U-Boot)"		/* first partition */		\
		",128k(Environment)"					\
		",4M(Kernel)"						\
		",-(RestOfNor0)"	/* last partition */
#	define MTDIDS_NOR						\
	"nor0=physmap-flash"	/* First NOR flash device */
#else
#	undef CONFIG_CMD_IMLS			/* NOR-flash specific */
#	define CFG_NO_FLASH			/* NOR-flash specific */
#endif	/* CONFIG_CMD_FLASH */

/*-----------------------------------------------------------------------
 * NAND FLASH organization
 */

#ifdef CONFIG_CMD_NAND				/* NAND flash present ? */
#	define CFG_MAX_NAND_DEVICE	1
#	define NAND_MAX_CHIPS		CFG_MAX_NAND_DEVICE
#	define CFG_NAND0_BASE		CFG_EMI_NAND_BASE
#	define CFG_NAND_BASE_LIST	{ CFG_NAND0_BASE }
#	define MTDPARTS_NAND						\
	"gen_nand.1:"		/* First NAND flash device */		\
		"128k(env-nand0)"	/* first partition */		\
		",4M(kernel-nand0)"					\
		",32M(root-nand0)"					\
		",-(RestOfNand0)"	/* last partition */
#	define MTDIDS_NAND						\
	"nand0=gen_nand.1"	/* First NAND flash device */

	/*
	 * Currently, there are 2 main modes to read/write from/to
	 * NAND devices on STM SoCs:
	 *	a) "bit-banging" (can NOT be used in boot-from-NAND)
	 *	b) FLEX-mode (only supported means for boot-from-NAND)
	 * If CFG_NAND_FLEX_MODE is defined, then FLEX-mode will be
	 * used, otherwise, "bit-banging" will be used.
	 */
	/* on this board, we *only* support bit-banging */
#	undef CFG_NAND_FLEX_MODE	/* no FLEX, use bit-banging instead!  */

	/*
	 * If we want to store the U-boot environment variables in
	 * the NAND device, then we also need to specify *where* the
	 * environment variables will be stored. Typically this
	 * would be immediately after the U-boot monitor itself.
	 * However, that *may* be a bad block. Define the following
	 * to place the environment in an appropriate good block.
	 */
#	define CFG_NAND_ENV_OFFSET (CFG_MONITOR_LEN + 0x0)	/* immediately after u-boot.bin */
#endif	/* CONFIG_CMD_NAND */


/*-----------------------------------------------------------------------
 * SPI SERIAL FLASH organization
 */

/*
 *	Name	Manuf	Device
 *	-----	-----	------
 *	UM6	ST	N25Q128
 *	UM7	ST	N25Q256
 */
#if defined(CONFIG_SPI_FLASH)			/* SPI serial flash present ? */
#	define CONFIG_SPI_FLASH_ST		/* ST N25Qxxx */
#	define CONFIG_SPI			/* enable the SPI driver */
#	define CONFIG_CMD_EEPROM		/* enable the "eeprom" command set */
#	define CFG_I2C_FRAM			/* to minimize performance degradation */
#	undef  CFG_EEPROM_PAGE_WRITE_DELAY_MS	/* to minimize performance degradation */

	/* Use H/W FSM SPI Controller (not H/W SSC, nor S/W "bit-banging") */
#	define CONFIG_STM_FSM_SPI		/* Use the H/W FSM for SPI */
#	define CFG_STM_SPI_FSM_BASE	0xfe902000	/* FSM SPI Controller Base */
#	define CFG_STM_SPI_CLOCKDIV	2	/* set SPI_CLOCKDIV = 2 */
#	undef CONFIG_CMD_SPI			/* SPI serial bus command support - NOT with FSM! */
#endif	/* CONFIG_SPI_FLASH */

/*-----------------------------------------------------------------------
 * Addresss, size, & location of U-boot's Environment Sector
 */

#define CFG_ENV_IS_IN_FLASH	1
#define CFG_ENV_OFFSET		CFG_MONITOR_LEN
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + CFG_ENV_OFFSET)
#define CFG_ENV_SIZE		0x10000
#define CFG_ENV_SECT_SIZE	0x20000

#endif	/* __CONFIG_H */
