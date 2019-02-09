/**
 * @brief Handle a pure virtual function call.
 *
 * This should *never* happen in release code, but is useful for debugging if an
 * unimplemented virtual function is accidentally called.
 */
extern "C" void __cxa_pure_virtual() {
    while (1) {
    }
}
