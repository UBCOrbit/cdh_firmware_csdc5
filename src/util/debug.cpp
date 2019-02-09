#include "util/debug.h"

/**
 * @brief Write a message to the debugger's console.
 *
 * This can only be used when the debugger is in semihosting mode: if it isn't,
 * the `bpkt` instruction will trigger a general processor fault and stop the
 * program.
 *
 * @param msg Pointer to a zero-terminted string to print.
 */
void debug_msg(const char *msg) {
#ifdef DEBUG
    __asm__("mov r0, #0x4;"
            "mov r1, %[msg];"
            "bkpt #0xab;"
            :
            : [msg] "r" (msg));
#endif
}