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

void oldland_illegal_instr(unsigned long faultlr, unsigned long far,
			   unsigned long dfar)
{
	printf("ILLEGAL INSTRUCTION: $lr %08lx $far %08lx $dfar %08lx\n",
	       faultlr, far, dfar);
	for (;;)
		continue;
}

void oldland_swi(unsigned long faultlr, unsigned long far, unsigned long dfar)
{
	printf("SWI: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	for (;;)
		continue;
}

void oldland_irq(unsigned long faultlr, unsigned long far, unsigned long dfar)
{
	printf("IRQ: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	for (;;)
		continue;
}

void oldland_ifetch_abort(unsigned long faultlr, unsigned long far,
			  unsigned long dfar)
{
	printf("IFETCH ABORT: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	for (;;)
		continue;
}

void oldland_data_abort(unsigned long faultlr, unsigned long far,
			unsigned long dfar)
{
	printf("DATA ABORT: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	for (;;)
		continue;
}
