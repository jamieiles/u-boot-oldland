/*
 * (C) Copyright 2011, Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 * (C) Copyright 2011, Julius Baxter <julius@opencores.org>
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/system.h>
#include <asm/io.h>

static ulong timestamp;

/* how many counter cycles in a jiffy */
#define TIMER_COUNTER_CYCLES  (500000000/1000)
/* how many ms elapses between each timer interrupt */
#define TIMER_TIMESTAMP_INC   1
/* how many cycles per ms */
#define TIMER_CYCLES_MS       (500000000/1000)
/* how many cycles per us */
#define TIMER_CYCLES_US       (500000000/1000000uL)

#define TIMER0_BASE 0x80003000
#define REG_COUNT_OFFS 0x0
#define REG_RELOAD_OFFS 0x4
#define REG_CONTROL_OFFS 0x8
#define REG_EOI_OFFS 0xc

#define CONTROL_ENABLED (1 << 1)

int timer_init(void)
{
	/* Set up the timer for the first expiration. */
	timestamp = 0;

	writel(CONTROL_ENABLED, TIMER0_BASE + REG_CONTROL_OFFS);

	return 0;
}

void reset_timer(void)
{
	timestamp = 0;
}
