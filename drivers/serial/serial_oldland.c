/*
 * (C) Copyright 2004, Psyent Corporation <www.psyent.com>
 * Scott McNutt <smcnutt@psyent.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <common.h>
#include <asm/io.h>
#include <linux/compiler.h>
#include <serial.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_DATA_OFFS 0x0
#define UART_STATUS_OFFS 0x4

#define UART_STATUS_TX_EMPTY (1 << 0)
#define UART_STATUS_RX_READY (1 << 1)

static void oldland_serial_putc(char c)
{
	if (c == '\n')
		serial_putc ('\r');
	while (!(readl(CONFIG_SYS_UART_BASE + UART_STATUS_OFFS) &
		 UART_STATUS_TX_EMPTY))
		continue;
	writel((unsigned char)c, CONFIG_SYS_UART_BASE + UART_DATA_OFFS);
}

static int oldland_serial_tstc(void)
{
	return (readl(CONFIG_SYS_UART_BASE + UART_STATUS_OFFS) &
		UART_STATUS_RX_READY);
}

static int oldland_serial_getc(void)
{
	while (!(readl(CONFIG_SYS_UART_BASE + UART_STATUS_OFFS) &
		 UART_STATUS_RX_READY))
		continue;
	return readl(CONFIG_SYS_UART_BASE + UART_DATA_OFFS) & 0xff;
}

static void oldland_serial_setbrg(void)
{
}

static int oldland_serial_init(void)
{
	return 0;
}

static struct serial_device oldland_serial_drv = {
	.name	= "oldland_serial",
	.start	= oldland_serial_init,
	.stop	= NULL,
	.setbrg	= oldland_serial_setbrg,
	.putc	= oldland_serial_putc,
	.puts	= default_serial_puts,
	.getc	= oldland_serial_getc,
	.tstc	= oldland_serial_tstc,
};

void oldland_serial_initialize(void)
{
	serial_register(&oldland_serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &oldland_serial_drv;
}
