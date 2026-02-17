#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* helpers */
static void *slot(queue *q, usize i) {
    return q->data + i * q->elem_size;
}

/* ---- basic ---- */

static queue queue_create(usize capacity, usize esz) {
    queue q;
    q.data = malloc(capacity * esz);
    q.elem_size = esz;
    q.capacity = capacity;
    q.head = 0;
    q.tail = 0;
    q.count = 0;
    return q;
}

static void queue_destroy(queue *q) {
    if (!q || !q->data) return;
    free(q->data);
    q->data = 0;
    q->capacity = q->head = q->tail = q->count = q->elem_size = 0;
}

static int queue_enqueue(queue *q, const void *e) {
    if (!q || q->count >= q->capacity) return 0;
    memcpy(slot(q, q->tail), e, q->elem_size);
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;
    return 1;
}

static int queue_dequeue(queue *q, void *out) {
    if (!q || q->count == 0) return 0;
    if (out) memcpy(out, slot(q, q->head), q->elem_size);
    q->head = (q->head + 1) % q->capacity;
    q->count--;
    return 1;
}

static int queue_peek(queue *q, void *out) {
    if (!q || q->count == 0 || !out) return 0;
    memcpy(out, slot(q, q->head), q->elem_size);
    return 1;
}

static int queue_empty(queue *q) {
    return (!q || q->count == 0);
}

static int queue_full(queue *q) {
    return (!q || q->count >= q->capacity);
}

static usize queue_size(queue *q) {
    return q ? q->count : 0;
}

/* ---- namespace ---- */

const module_queue modqueue = {
    .create  = queue_create,
    .destroy = queue_destroy,
    .enqueue = queue_enqueue,
    .dequeue = queue_dequeue,
    .peek    = queue_peek,
    .empty   = queue_empty,
    .full    = queue_full,
    .size    = queue_size
};
