#include <common.h>
#include <stdio_dev.h>
#include <malloc.h>
#include <mmc.h>
#include <spi.h>
#include <timestamp.h>
#include <version.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependend #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */

extern int cache_init(void);

/*
 * Initialization sequence
 */
static int (* const init_sequence[])(void) = {
	timer_init,		/* initialize timer */
	env_init,
	serial_init,
	console_init_f,
	display_options,
	checkcpu,
	checkboard,
};

static void oldland_mmc_init(void)
{
	struct mmc *mmc = mmc_spi_init(0, 0, 100000, SPI_MODE_0);

	if (!mmc) {
		printf("Failed to create SPI MMC device\n");
		return;
	}

	mmc_init(mmc);
}


/***********************************************************************/
void board_init(void)
{
	bd_t *bd;
	int i;

	gd = (gd_t *)CONFIG_SYS_GBL_DATA_ADDR;

	memset((void *)gd, 0, GENERATED_GBL_DATA_SIZE);

	gd->bd = (bd_t *)(gd+1);	/* At end of global data */
	gd->baudrate = CONFIG_BAUDRATE;
	gd->cpu_clk = CONFIG_SYS_CLK_FREQ;

	bd = gd->bd;
	bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;
	bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;

	for (i = 0; i < ARRAY_SIZE(init_sequence); i++) {
		if (init_sequence[i]())
			hang();
	}

	/* The Malloc area is immediately below the monitor copy in RAM */
	mem_malloc_init(CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_LEN);

	env_relocate();
	stdio_init();
	jumptable_init();
	console_init_r();
	oldland_mmc_init();

#if defined(CONFIG_BOARD_LATE_INIT)
	board_late_init();
#endif

	for (;;) {
		main_loop();
	}
}