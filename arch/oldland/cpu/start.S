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
	b	board_init

	.size	_start, .-_start
