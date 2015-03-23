#include <common.h>
#include <asm/system.h>

static inline unsigned long cache_line_size(unsigned long cpuidnum)
{
	unsigned long config;

	asm volatile("cpuid %0, %1" : "=r"(config) : "I"(cpuidnum));

	return (config & 0xff) * 4;
}

void flush_dcache_range(unsigned long addr, unsigned long stop)
{
	unsigned long line_size;

	line_size = cache_line_size(4);

	while (addr < stop) {
		unsigned long index = addr / line_size;
		asm volatile("cache	%0, 0x2" :: "r"(index));
		addr += line_size;
	}
}

void invalidate_dcache_range(unsigned long addr, unsigned long stop)
{
	unsigned long line_size;

	line_size = cache_line_size(4);

	while (addr < stop) {
		unsigned long index = addr / line_size;
		asm volatile("cache	%0, 0x1" :: "r"(index));
		addr += line_size;
	}
}

static void invalidate_icache_range(unsigned long addr, unsigned long stop)
{
	unsigned long line_size;

	line_size = cache_line_size(3);

	while (addr < stop) {
		unsigned long index = addr / line_size;
		asm volatile("cache	%0, 0x0" :: "r"(index));
		addr += line_size;
	}
}

void flush_cache(unsigned long addr, unsigned long size)
{
	flush_dcache_range(addr, addr + size);
	invalidate_icache_range(addr, addr + size);
}
