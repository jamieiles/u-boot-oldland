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

.macro ex_handler name, handler
\name:
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
