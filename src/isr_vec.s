	/*
	 * The interrupt vector is defined here --- you shouldn't
	 * need to add any interrupt, because they're all defined as weak
	 * symbols by default.
	 */

	.section  .isr_vec, "a", %progbits
isr_vec:
	.word stack_end
	.word handle_reset
	.word handle_nmi
	.word handle_hardfault
	.word handle_memmanage
	.word handle_busfault
	.word handle_usagefault
	.word 0
	.word 0
	.word 0
	.word 0
	.word handle_svc
	.word handle_debugmon
	.word 0
	.word handle_pendsv
	.word handle_systick

	/*
	 * default handlers -- if these aren't defined elsewhere,
	 * they'll just infinite loop (so you can boot up gdb and see
	 * what happened).
	 */
	.weak handle_nmi
	.thumb_set handle_nmi, handle_default
	.weak handle_hardfault
	.thumb_set handle_hardfault, handle_default
	.weak handle_memmanage
	.thumb_set handle_memmanage, handle_default
	.weak handle_busfault
	.thumb_set handle_busfault, handle_default
	.weak handle_usagefault
	.thumb_set handle_usagefault, handle_default
	.weak handle_svc
	.thumb_set handle_svc, handle_default
	.weak handle_debugmon
	.thumb_set handle_debugmon, handle_default
	.weak handle_pendsv
	.thumb_set handle_pendsv, handle_default
	.weak handle_systick
	.thumb_set handle_systick, handle_default

	.text
handle_default:
	bl handle_default
