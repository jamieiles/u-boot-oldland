/*
 * Oldland SPI driver
 *
 * based on oldland_spi.c
 * Copyright (c) 2005-2008 Analog Devices Inc.
 * Copyright (C) 2010 Thomas Chou <thomas@wytron.com.tw>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/io.h>
#include <malloc.h>
#include <spi.h>

#define OLDLAND_SPI_CONTROL	0x0
#define OLDLAND_SPI_SLAVE_SEL	0x4
#define OLDLAND_SPI_XFER_CTRL	0x8
#define XFER_BUF		8192

#define XFER_START		(1 << 16)
#define XFER_BUSY		(1 << 17)

#ifndef CONFIG_SYS_OLDLAND_SPI_LIST
#define CONFIG_SYS_OLDLAND_SPI_LIST { CONFIG_SYS_SPI_BASE }
#endif

static ulong oldland_spi_base_list[] = CONFIG_SYS_OLDLAND_SPI_LIST;

struct oldland_spi_slave {
	struct spi_slave slave;
	ulong base;
};
#define to_oldland_spi_slave(s) container_of(s, struct oldland_spi_slave, slave)

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus < ARRAY_SIZE(oldland_spi_base_list) && cs < 32;
}

void spi_cs_activate(struct spi_slave *slave)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);

	writel(1 << slave->cs, spi->base + OLDLAND_SPI_SLAVE_SEL);
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);

	writel(0, spi->base + OLDLAND_SPI_SLAVE_SEL);
}

void spi_init(void)
{
}

void spi_set_speed(struct spi_slave *slave, uint hz)
{
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
				  unsigned int max_hz, unsigned int mode)
{
	struct oldland_spi_slave *spi;

	if (!spi_cs_is_valid(bus, cs))
		return NULL;

	spi = spi_alloc_slave(struct oldland_spi_slave, bus, cs);
	if (!spi)
		return NULL;

	spi->base = oldland_spi_base_list[bus];
	debug("%s: bus:%i cs:%i base:%lx\n", __func__,
		bus, cs, spi->base);

	return &spi->slave;
}

void spi_free_slave(struct spi_slave *slave)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);

	free(spi);
}

int spi_claim_bus(struct spi_slave *slave)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);

	writel(0, spi->base + OLDLAND_SPI_CONTROL);
	writel(0, spi->base + OLDLAND_SPI_SLAVE_SEL);

	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);

	writel(0, spi->base + OLDLAND_SPI_SLAVE_SEL);
}

static void spi_copy_data_to_xfer_buf(const struct oldland_spi_slave *spi,
				      const void *data, uint nbytes)
{
	const unsigned char *data8 = data;
	size_t m;

	for (m = 0; m < nbytes; ++m)
		writeb(data8[m], data ? spi->base + XFER_BUF + m : 0xff);
}

static void spi_copy_data_from_xfer_buf(const struct oldland_spi_slave *spi,
					void *data, uint nbytes)
{
	unsigned char *data8 = data;
	size_t m;

	if (!data)
		return;

	for (m = 0; m < nbytes; ++m)
		data8[m] = readb(spi->base + XFER_BUF + m);
}

static void spi_wait_idle(struct oldland_spi_slave *spi)
{
	unsigned long xfer_ctrl;

	do {
		xfer_ctrl = readl(spi->base + OLDLAND_SPI_XFER_CTRL);
	} while (xfer_ctrl & XFER_BUSY);
}

int spi_xfer(struct spi_slave *slave, unsigned int bitlen, const void *dout,
	     void *din, unsigned long flags)
{
	struct oldland_spi_slave *spi = to_oldland_spi_slave(slave);
	uint bytes = bitlen / 8;

	debug("%s: bus:%i cs:%i bitlen:%i bytes:%i flags:%lx\n", __func__,
		slave->bus, slave->cs, bitlen, bytes, flags);

	if (bitlen == 0)
		goto done;

	if (bitlen % 8) {
		flags |= SPI_XFER_END;
		goto done;
	}

	/* empty read buffer */
	if (flags & SPI_XFER_BEGIN)
		spi_cs_activate(slave);

	spi_copy_data_to_xfer_buf(spi, dout, bytes);
	writel(1, spi->base + OLDLAND_SPI_CONTROL);
	writel(XFER_START | bytes, spi->base + OLDLAND_SPI_XFER_CTRL);
	spi_wait_idle(spi);
	spi_copy_data_from_xfer_buf(spi, din, bytes);

 done:
	if (flags & SPI_XFER_END)
		spi_cs_deactivate(slave);

	return 0;
}
