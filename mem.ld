ENTRY(handle_reset)

stack_end = 0x20020000;

MEMORY {
	DTCMRAM (xrw)	: ORIGIN = 0x20000000, LENGTH = 128K
	RAM_D1 (xrw)	: ORIGIN = 0x24000000, LENGTH = 512K
	RAM_D2 (xrw)	: ORIGIN = 0x30000000, LENGTH = 288K
	RAM_D3 (xrw)	: ORIGIN = 0x38000000, LENGTH = 64K
	ITCMRAM (xrw)	: ORIGIN = 0x00000000, LENGTH = 64K
	FLASH (rx)	: ORIGIN = 0x8000000, LENGTH = 2048K
}

SECTIONS {
	.isr_vec : {
		 . = ALIGN(4);
		 KEEP(*(.isr_vec))
		 . = ALIGN(4);
	} >FLASH

	.text : {
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.eh_frame)

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
	} >FLASH

	.rodata : {
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH

	.data : {
		. = ALIGN(4);
		data_start = .;
		*(.data)
		*(.data*)

		. = ALIGN(4);
		data_end = .;
	} >DTCMRAM AT> FLASH

	.bss : {
		. = ALIGN(4);
		bss_start = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		bss_end = .;
	}

	/DISCARD/ : {
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}
}
