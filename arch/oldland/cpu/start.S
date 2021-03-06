#include <config.h>
#include <asm-offsets.h>

	/* Startup routine */
	.text
	.global _start
_start:
	/* Init stack and frame pointers */
	movhi	$sp, %hi(CONFIG_SYS_INIT_SP_ADDR)
	orlo	$sp, $sp, %lo(CONFIG_SYS_INIT_SP_ADDR)
	mov	$fp, $sp
	or	$fp, $fp, 1

	/* clear BSS segments */
	movhi	$r4, %hi(_bss_start)
	orlo	$r4, $r4, %lo(_bss_start)
	movhi	$r5, %hi(_bss_end)
	orlo	$r5, $r5, %lo(_bss_end)
	mov	$r3, 0
_clear_bss:
	str8	$r3, [$r4, 0]
	cmp	$r4, $r5
	beq	1f
	add	$r4, $r4, 1
	b	_clear_bss

1:
	movhi	$r6, %hi(ex_table)
	orlo	$r6, $r6, %lo(ex_table)
	scr	0, $r6
	b	board_init

	.size	_start, .-_start

.macro saveregs
	str32	$lr, [$sp, -8]
	str32	$sp, [$sp, -12]
	str32	$fp, [$sp, -16]
	str32	$r12, [$sp, -20]
	str32	$r11, [$sp, -24]
	str32	$r10, [$sp, -28]
	str32	$r9, [$sp, -32]
	str32	$r8, [$sp, -36]
	str32	$r7, [$sp, -40]
	str32	$r6, [$sp, -44]
	str32	$r5, [$sp, -48]
	str32	$r4, [$sp, -52]
	str32	$r3, [$sp, -56]
	str32	$r2, [$sp, -60]
	str32	$r1, [$sp, -64]
	str32	$r0, [$sp, -68]
	sub	$sp, $sp, 68
	gcr	$r0, 3
	str32	$r0, [$sp, 16 * 4]
	mov	$r3, $sp
.endm

.macro ex_handler name, handler
\name:
	saveregs
	mov	$r0, $lr
	gcr	$r1, 3
	gcr	$r2, 4
	b	\handler
.endm

ex_handler __illegal_instr, oldland_illegal_instr
ex_handler __swi, oldland_swi
ex_handler __irq, oldland_irq
ex_handler __ifetch_abort, oldland_ifetch_abort
ex_handler __data_abort, oldland_data_abort

	.balign	64
ex_table:
	b	__reset
	b	__illegal_instr
	b	__swi
	b	__irq
	b	__ifetch_abort
	b	__data_abort
