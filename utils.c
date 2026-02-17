#define _GNU_SOURCE

#include <stdio.h>
#include <stddef.h>

#include "utils.h"

int fsread(void) {
    int x = 0, sign = 1;
    int c = getchar_unlocked();

    while ((c < '0' || c > '9') && c != '-')
        c = getchar_unlocked();

    if (c == '-') {
        sign = -1;
        c = getchar_unlocked();
    }

    for (; c >= '0' && c <= '9'; c = getchar_unlocked())
        x = x * 10 + (c - '0');

    return sign * x;
}

void print_int(void *p)  { printf("%d",  *(int*)p); }
void print_long(void *p) { printf("%ld", *(long*)p); }
void print_ll(void *p)   { printf("%lld",*(long long*)p); }
void print_char(void *p) { printf("%c",  *(char*)p); }

void printarray(void *s, void *e, usize sz,
                void (*printer)(void *)) {
    unsigned char *p = s;
    unsigned char *end = e;

    printf("[ ");
    while (p < end) {
        printer(p);
        printf(" ");
        p += sz;
    }
    printf("]\n");
}
