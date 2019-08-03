#include "i2a.h"

char *i2a(int i) {
    static char buf[1024];
    buf[1023] = '\0';
    char *start = buf;

    bool neg = i < 0;
    if (neg) {
        i = -i;
    }

    while (i != 0) {
        *(--start) = '0' + (i % 10);
        i /= 10;
    }

    if (neg) {
        *(--start) = '-';
    }

    return start;
}