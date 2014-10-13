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
	__asm__("movhi $r1,%hi(0x10000000);  \
		 orlo  $r1,$r1,%lo(0x10000000); \
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

struct oldland_regs {
	unsigned regs[17];
};

static void dump_regs(struct oldland_regs *regs)
{
	unsigned i;
	printf("regs:");
	for (i = 0; i <= 12; ++i)
		printf("r%2d: %08x\n", i, regs->regs[i]);
	printf("$fp: %08x\n", regs->regs[13]);
	printf("$sp: %08x\n", regs->regs[14]);
	printf("$lr: %08x\n", regs->regs[15]);
	printf("$pc: %08x\n", regs->regs[16]);
}

void oldland_illegal_instr(unsigned long faultlr, unsigned long far,
			   unsigned long dfar, struct oldland_regs *regs)
{
	printf("ILLEGAL INSTRUCTION: $lr %08lx $far %08lx $dfar %08lx\n",
	       faultlr, far, dfar);
	dump_regs(regs);
	for (;;)
		continue;
}

void oldland_swi(unsigned long faultlr, unsigned long far, unsigned long dfar,
		 struct oldland_regs *regs)
{
	printf("SWI: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	dump_regs(regs);
	for (;;)
		continue;
}

void oldland_irq(unsigned long faultlr, unsigned long far, unsigned long dfar,
		 struct oldland_regs *regs)
{
	printf("IRQ: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	dump_regs(regs);
	for (;;)
		continue;
}

void oldland_ifetch_abort(unsigned long faultlr, unsigned long far,
			  unsigned long dfar, struct oldland_regs *regs)
{
	printf("IFETCH ABORT: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	dump_regs(regs);
	for (;;)
		continue;
}

void oldland_data_abort(unsigned long faultlr, unsigned long far,
			unsigned long dfar, struct oldland_regs *regs)
{
	printf("DATA ABORT: $lr %08lx $far %08lx $dfar %08lx\n", faultlr, far, dfar);
	dump_regs(regs);
	for (;;)
		continue;
}
