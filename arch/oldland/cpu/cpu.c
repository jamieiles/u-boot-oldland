#include <common.h>
#include <asm/system.h>

int checkcpu(void)
{
	printf("Oldland CPU\n");

	return 0;
}

int cleanup_before_linux(void)
{
	disable_interrupts();
	return 0;
}

void __reset(void)
{
	printf("resetting...\n");
}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	disable_interrupts();
	__asm__("movhi $r1,%hi(__reset);  \
		 orlo  $r1,$r1,%lo(__reset); \
		 b $r1");
	/* not reached, __reset does not return */
	return 0;
}

void enable_interrupts(void)
{
}

int disable_interrupts(void)
{
	return 0;
}

int dcache_status(void)
{
	return 1;
}

void dcache_enable(void)
{
}

void dcache_disable(void)
{
}

void icache_enable(void)
{
}

unsigned long __one_cmplsi2(unsigned long x)
{
	asm volatile("mov	$r1, -1\n\t"
		     "xor	%0, %0, $r1" : "=r"(x) : "r"(x) : "$r1");

	return x;
}
