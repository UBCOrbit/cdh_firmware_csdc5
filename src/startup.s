	.cpu cortex-m7
	.fpu softvfp
	.syntax unified
	.thumb

	.text
	.globl handle_reset
handle_reset:
	/* copy .data into ram */
	ldr r1, =data_vma_start
	ldr r2, =data_lma_start
	ldr r3, =data_vma_end
0:
	cmp r1, r3
	bhs 1f
	ldr r0, [r2], #4
	str r0, [r1], #4
	b 0b
1:
	/* zero out .bss */
	mov r0, #0
	ldr r1, =bss_start
	ldr r2, =bss_end
2:
	cmp r1, r2
	bhs 3f
	str r0, [r1], #4
	b 2b
3:
	/* enable the fpu */
	ldr r0, =0xe000ed88
	ldr r1, [r0]
	orr r1, #(0xf << 20)
	str r1, [r0]
	dsb
	isb
	bl main
	/* if main ever returns, just loop */
0:
	b 0b
