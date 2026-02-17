# Usage

```c
queue q = modqueue.create(16, sizeof(int));

int v = 42;
modqueue.enqueue(&q, &v);

int out;
modqueue.dequeue(&q, &out); // out = 42

// Check status
if (modqueue.empty(&q)) {
    printf("Queue is empty\n");
}

if (modqueue.full(&q)) {
    printf("Queue is full\n");
}

// Peek without removing
modqueue.peek(&q, &out);

// Get current size
usize count = modqueue.size(&q);

// Cleanup
modqueue.destroy(&q);
```
