#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * BOARD/CPU
 */

#define CONFIG_SYS_CLK_FREQ		500000000
#define CONFIG_SYS_RESET_ADDR		0x10000000

#define CONFIG_SYS_SDRAM_BASE		0x20000000
#define CONFIG_SYS_SDRAM_SIZE		(32 * 1024 *1024)

#define CONFIG_SYS_CACHELINE_SIZE	32

#define CONFIG_SYS_UART_BASE		0x80000000
#define CONFIG_SYS_UART_FREQ		CONFIG_SYS_CLK_FREQ
#define CONFIG_SYS_UART_BAUD		115200

#define CONFIG_BOARD_NAME		"Oldland Generic"

#define CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_MAX_FLASH_SECT	0

/*
 * SERIAL
 */
#define CONFIG_SYS_OLDLAND_UART
#define CONFIG_BAUDRATE			CONFIG_SYS_UART_BAUD
#define CONFIG_SYS_BAUDRATE_TABLE	{CONFIG_BAUDRATE}
#define CONFIG_SYS_CONSOLE_INFO_QUIET	/* Suppress console info */
#define CONSOLE_ARG			"console=console=ttyS0,115200\0"

/*
 * Memory organisation:
 *
 * RAM start ---------------------------
 *           | ...                     |
 *           ---------------------------
 *           | Stack                   |
 *           ---------------------------
 *           | Global data             |
 *           ---------------------------
 *           | Environment             |
 *           ---------------------------
 *           | Monitor                 |
 *           ---------------------------
 *           | Heap                    |
 * RAM end   ---------------------------
 */
/* We're running in RAM */
#define CONFIG_MONITOR_IS_IN_RAM
#define CONFIG_SYS_MONITOR_LEN	0x80000	/* Reserve 512k */
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_SYS_SDRAM_BASE + \
				CONFIG_SYS_SDRAM_SIZE - \
				CONFIG_SYS_MONITOR_LEN - \
				CONFIG_SYS_MALLOC_LEN)

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE		0x20000 /* Total Size of Environment, 128KB */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SIZE)

/*
 * Global data object and stack pointer
 */
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_ENV_ADDR \
					- GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_GBL_DATA_ADDR	CONFIG_SYS_GBL_DATA_OFFSET
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_GBL_DATA_OFFSET
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET
#define CONFIG_SYS_STACK_LENGTH		0x10000 /* 64KB */
#define CONFIG_SYS_MALLOC_LEN		0x400000 /* 4MB */
#define CONFIG_SYS_MALLOC_BASE		(CONFIG_SYS_SDRAM_BASE)
/*
 * MISC
 */
#define CONFIG_SYS_LONGHELP		/* Provide extended help */
#define CONFIG_SYS_CBSIZE		256	/* Console I/O buf size */
#define CONFIG_SYS_MAXARGS		16	/* Max command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE /* Bootarg buf size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + \
					16)	/* Print buf size */
#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_START	(CONFIG_SYS_SDRAM_BASE + 0x2000)
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_INIT_SP_ADDR - 0x20000)
#define CONFIG_CMDLINE_EDITING

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>


#define CONFIG_CMD_IRQ
#define CONFIG_CMD_ELF
#define CONFIG_CMD_BSP

#define CONFIG_CMD_MII
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING

#define CONFIG_OF_LIBFDT
#define CONFIG_LMB

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

#define CONFIG_NEEDS_MANUAL_RELOC
#define CONFIG_SYS_TIMER_RATE 50000000
#define CONFIG_SYS_TIMER_COUNTER 0x80003000
#define CONFIG_SYS_TIMER_COUNTS_DOWN

#undef CONFIG_CMD_IRQ
#undef CONFIG_CMD_BOOTM
#undef CONFIG_CMD_BOOTD

#define CONFIG_SYS_SPI_BASE 0x80004000
#define CONFIG_OLDLAND_SPI
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_MMC_SPI
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_PART
#define CONFIG_CMD_MMC
#define CONFIG_PARTITION_UUIDS

#endif /* __CONFIG_H */
