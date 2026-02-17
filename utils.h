#ifndef UTILS_H
#define UTILS_H

#include "stack/stack.h"
#include "queue/queue.h"
#include "graph/graph.h"

/* forward-declare size_t without including stddef */
typedef unsigned long usize;

int fsread(void);

void printarray(void *start, void *end,
                usize elem_size,
                void (*printer)(void *));

void print_int(void *p);
void print_long(void *p);
void print_ll(void *p);
void print_char(void *p);

/* convenience macros */
#define dprintarray(s,e) printarray(s,e,sizeof(int), print_int)
#define lprintarray(s,e) printarray(s,e,sizeof(long), print_long)
#define llprintarray(s,e) printarray(s,e,sizeof(long long), print_ll)
#define cprintarray(s,e) printarray(s,e,sizeof(char), print_char)

#define printstack(s, printer) \
    printarray( \
        (s).data, \
        (s).data + (s).top * (s).elem_size, \
        (s).elem_size, \
        printer \
    )

/* compare functins */
int icmp(const void *a, const void *b);

#endif
