#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/* helpers */
static void *slot(stack *s, usize i) {
    return s->data + i * s->elem_size;
}
/* ---- basic ---- */

static stack stack_create(usize size, usize esz) {
    stack s;
    s.data = malloc(size * esz);
    s.elem_size = esz;
    s.size = size;
    s.top = 0;
    return s;
}

static void stack_destroy(stack *s) {
    if (!s || !s->data) return;
    free(s->data);
    s->data = 0;
    s->size = s->top = s->elem_size = 0;
}

static int stack_push(stack *s, const void *e) {
    if (!s || s->top >= s->size) return 0;
    memcpy(slot(s, s->top++), e, s->elem_size);
    return 1;
}

static int stack_pop(stack *s, void *out) {
    if (!s || s->top == 0) return 0;
    s->top--;
    if (out) memcpy(out, slot(s, s->top), s->elem_size);
    return 1;
}

static int stack_peek(stack *s, void *out) {
    if (!s || s->top == 0 || !out) return 0;
    memcpy(out, slot(s, s->top - 1), s->elem_size);
    return 1;
}

static int stack_empty(stack *s) {
    return (!s || s->top == 0);
}

/* ---- monotonic ---- */

static int stack_push_inc(stack *s, const void *e, stack_cmp cmp) {
    if (!s || !cmp) return 0;
    while (s->top > 0 &&
           cmp(slot(s, s->top - 1), e) > 0) {
        s->top--; /* logical pop */
    }
    return stack_push(s, e);
}

static int stack_push_dec(stack *s, const void *e, stack_cmp cmp) {
    if (!s || !cmp) return 0;
    while (s->top > 0 &&
           cmp(slot(s, s->top - 1), e) < 0) {
        s->top--;
    }
    return stack_push(s, e);
}

/* ---- namespace ---- */

const module_stack modstack = {
    .create   = stack_create,
    .destroy  = stack_destroy,
    .push     = stack_push,
    .pop      = stack_pop,
    .peek     = stack_peek,
    .empty    = stack_empty,
    .push_inc = stack_push_inc,
    .push_dec = stack_push_dec
};
