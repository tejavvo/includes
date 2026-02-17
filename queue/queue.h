#ifndef QUEUE_H
#define QUEUE_H

typedef unsigned long usize;

/* cmp(a,b) < 0 if a<b, 0 if equal, >0 if a>b */
typedef int (*queue_cmp)(const void *, const void *);

typedef struct {
    unsigned char *data; /* raw bytes (circular buffer) */
    usize elem_size;
    usize capacity;
    usize head;  /* index of front element */
    usize tail;  /* index where next element will be inserted */
    usize count; /* number of elements in queue */
} queue;

typedef struct {
    queue (*create)(usize capacity, usize elem_size);
    void  (*destroy)(queue *q);

    int   (*enqueue)(queue *q, const void *elem);
    int   (*dequeue)(queue *q, void *out);
    int   (*peek)(queue *q, void *out);
    int   (*empty)(queue *q);
    int   (*full)(queue *q);
    usize (*size)(queue *q);
} module_queue;

extern const module_queue modqueue;

#endif
