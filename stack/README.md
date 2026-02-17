# Usage

```c
int icmp(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

stack s = modstack.create(16, sizeof(int));

int v = 5;
modstack.push(&s, &v);

v = 3;
modstack.push_inc(&s, &v, icmp);
```
