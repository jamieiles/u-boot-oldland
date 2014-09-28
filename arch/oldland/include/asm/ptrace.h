/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_OLDLAND_PTRACE_H
#define __ASM_OLDLAND_PTRACE_H

#ifndef __ASSEMBLY__
/*
 * This is the layout of the regset returned by the GETREGSET ptrace call
 */
struct user_regs_struct {
	/* GPR R0-$lr... */
	unsigned long gpr[16];
	unsigned long pc;
	unsigned long psr;
};
#endif

#ifdef __KERNEL__

/*
 * Make kernel PTrace/register structures opaque to userspace... userspace can
 * access thread state via the regset mechanism.  This allows us a bit of
 * flexibility in how we order the registers on the stack, permitting some
 * optimizations like packing call-clobbered registers together so that
 * they share a cacheline (not done yet, though... future optimization).
 */

#ifndef __ASSEMBLY__
/*
 * This struct describes how the registers are laid out on the kernel stack
 * during a syscall or other kernel entry.
 *
 * This structure should always be cacheline aligned on the stack.
 * FIXME: I don't think that's the case right now.  The alignment is
 * taken care of elsewhere... head.S, process.c, etc.
 */

struct pt_regs {
	long gpr[16];
	long pc;
	long syscallno;	/* Syscall number (used by strace) */
	long dummy;		/* Cheap alignment fix */
};
#endif /* __ASSEMBLY__ */

/* TODO: Rename this to REDZONE because that's what it is */
#define STACK_FRAME_OVERHEAD  128  /* size of minimum stack frame */

#define instruction_pointer(regs)	((regs)->pc)
#define user_mode(regs)			(0)
#define user_stack_pointer(regs)	((unsigned long)(regs)->gpr[14])
#define profile_pc(regs)		instruction_pointer(regs)

/*
 * Offsets used by 'ptrace' system call interface.
 */
#define PT_R0         0
#define PT_R1         4
#define PT_R2       8
#define PT_R3       12
#define PT_R4       16
#define PT_R5       20
#define PT_R6       24
#define PT_R7       28
#define PT_R8       32
#define PT_R9       36
#define PT_R10      40
#define PT_R11      44
#define PT_R12      48
#define PT_R13      52
#define PT_R14      56
#define PT_R15      60
#define PT_PC	      64
#define PT_ORIG_GPR11 68

#endif /* __KERNEL__ */

#endif /* __ASM_OLDLAND_PTRACE_H */
