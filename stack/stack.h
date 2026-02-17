#ifndef STACK_H
#define STACK_H

typedef unsigned long usize;

void print_stack_elem(void *p);

/* cmp(a,b) < 0 if a<b, 0 if equal, >0 if a>b */
typedef int (*stack_cmp)(const void *, const void *);

typedef struct {
    unsigned char *data; /* raw bytes */
    usize elem_size;
    usize size;
    usize top;
} stack;

typedef struct {
    stack (*create)(usize size, usize elem_size);
    void  (*destroy)(stack *s);

    int   (*push)(stack *s, const void *elem);
    int   (*pop)(stack *s, void *out);
    int   (*peek)(stack *s, void *out);
    int   (*empty)(stack *s);

    /* monotonic */
    int   (*push_inc)(stack *s, const void *elem, stack_cmp cmp);
    int   (*push_dec)(stack *s, const void *elem, stack_cmp cmp);
} module_stack;

extern const module_stack modstack;

#endif
