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
    __asm__("mov r1, %[msg];"
            "mov r0, #0x4;"
            "bkpt #0xab;"
            :
            : [ msg ] "r"(msg));
#endif
}

/**
 * @brief Prompt for user input on the given UART.
 *
 * @return A static string with the user's input, truncated to 1024
 * characters.  Will be mangled on the next call.
 */
const char *debug_getline(UART &uart) {
    int i = 0;
    static char buf[1024];
    buf[i] = 0;
    uart.transmit("> ").block();

    while (true) {
        uart.receive((uint8_t *)buf + i, 1).block();
        if (buf[i] == '\r') {
            buf[i + 1] = 0;
            break;
        }
        if (buf[i] == '\177') {
            if (i != 0) {
                uart.transmit("\b \b").block();
                i--;
            }
        } else {
            uart.transmit((uint8_t *)buf + i, 1).block();
            i++;
        }
    }

    uart.transmit("\r\n").block();

    return buf;
} // :D
