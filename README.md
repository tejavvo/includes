# C Utilities Library

A collection of generic data structures implemented in C17, designed for competitive programming and general-purpose use.

## Features

- **Stack** - Generic stack with monotonic stack support
- **Queue** - Circular buffer-based FIFO queue
- **Graph** - Adjacency list-based graph with DFS/BFS traversal
- **Utilities** - Array printing, fast I/O, comparison functions

## Building

```bash
make        # Build libutils.a
make clean  # Remove build artifacts
```

## Usage

### Including in Your Project

```bash
gcc -I/path/to/includes your_program.c /path/to/includes/libutils.a -o your_program
```

Or copy the library to your project:

```bash
cp libutils.a /your/project/
gcc -I/path/to/includes your_program.c libutils.a -o your_program
```

### In Your Code

```c
#include <utils.h>

int main() {
    // All modules are now available
    stack s = modstack.create(10, sizeof(int));
    queue q = modqueue.create(10, sizeof(int));
    graph g = modgraph.create(10);
    
    // ... use data structures ...
    
    modstack.destroy(&s);
    modqueue.destroy(&q);
    modgraph.destroy(&g);
    return 0;
}
```

## API Documentation

### Stack (`stack/stack.h`)

Generic stack with support for monotonic stacks.

**Structure:**
```c
typedef struct {
    unsigned char *data;
    usize elem_size;
    usize size;
    usize top;
} stack;
```

**Operations:**
- `create(size, elem_size)` - Create stack with capacity
- `destroy(s)` - Free stack memory
- `push(s, elem)` - Push element
- `pop(s, out)` - Pop element
- `peek(s, out)` - View top element
- `empty(s)` - Check if empty
- `push_inc(s, elem, cmp)` - Push maintaining non-decreasing order
- `push_dec(s, elem, cmp)` - Push maintaining non-increasing order

**Example:**
```c
stack s = modstack.create(16, sizeof(int));
int v = 5;
modstack.push(&s, &v);
modstack.pop(&s, &v);
modstack.destroy(&s);
```

See [stack/README.md](stack/README.md) for detailed usage.

---

### Queue (`queue/queue.h`)

Circular buffer-based FIFO queue with O(1) operations.

**Structure:**
```c
typedef struct {
    unsigned char *data;
    usize elem_size;
    usize capacity;
    usize head;
    usize tail;
    usize count;
} queue;
```

**Operations:**
- `create(capacity, elem_size)` - Create queue with capacity
- `destroy(q)` - Free queue memory
- `enqueue(q, elem)` - Add element to back
- `dequeue(q, out)` - Remove element from front
- `peek(q, out)` - View front element
- `empty(q)` - Check if empty
- `full(q)` - Check if full
- `size(q)` - Get current size

**Example:**
```c
queue q = modqueue.create(16, sizeof(int));
int v = 42;
modqueue.enqueue(&q, &v);
modqueue.dequeue(&q, &v);
modqueue.destroy(&q);
```

See [queue/README.md](queue/README.md) for detailed usage.

---

### Graph (`graph/graph.h`)

Adjacency list-based directed graph with traversal algorithms.

**Structure:**
```c
typedef struct {
    adjacency_list *vertices;
    usize num_vertices;
    usize capacity;
} graph;
```

**Operations:**
- `create(capacity)` - Create graph with max vertices
- `destroy(g)` - Free graph memory
- `add_vertex(g)` - Add new vertex (returns ID)
- `add_edge(g, from, to)` - Add directed edge
- `has_edge(g, from, to)` - Check if edge exists
- `remove_edge(g, from, to)` - Remove edge
- `dfs(g, start, visitor)` - Depth-first search
- `bfs(g, start, visitor)` - Breadth-first search
- `vertex_count(g)` - Get number of vertices
- `degree(g, vertex)` - Get out-degree of vertex

**Example:**
```c
void print_vertex(int v) { printf("%d ", v); }

graph g = modgraph.create(10);
int v0 = modgraph.add_vertex(&g);
int v1 = modgraph.add_vertex(&g);
modgraph.add_edge(&g, v0, v1);
modgraph.dfs(&g, v0, print_vertex);
modgraph.destroy(&g);
```

**Note:** The graph is directed by default. For undirected graphs, add edges in both directions.

See [graph/README.md](graph/README.md) for detailed usage.

---

### Utilities (`utils.h`)

**Array Printing:**
- `printarray(start, end, elem_size, printer)` - Print array
- `dprintarray(start, end)` - Print int array
- `lprintarray(start, end)` - Print long array
- `llprintarray(start, end)` - Print long long array
- `cprintarray(start, end)` - Print char array
- `printstack(stack, printer)` - Print stack contents

**Comparison Functions:**
- `icmp(a, b)` - Integer comparison

**I/O:**
- `fsread()` - Fast space-separated read

**Example:**
```c
int arr[] = {1, 2, 3, 4, 5};
dprintarray(arr, arr + 5); // prints: 1 2 3 4 5
```

## Design Philosophy

- **Generic:** All data structures use `void*` for type-agnostic storage
- **Namespace-based:** Module pattern (`modstack`, `modqueue`, `modgraph`) for clean API
- **Zero dependencies:** Only standard library (stdio, stdlib, string)
- **C17 standard:** Modern C with designated initializers
- **Performance-focused:** Efficient algorithms and memory management

## Project Structure

```
includes/
├── LICENSE
├── makefile
├── README.md
├── utils.h          # Main header (includes all modules)
├── utils.c          # Utility implementations
├── stack/
│   ├── stack.h
│   ├── stack.c
│   └── README.md
├── queue/
│   ├── queue.h
│   ├── queue.c
│   └── README.md
└── graph/
    ├── graph.h
    ├── graph.c
    └── README.md
```

## Requirements

- C17-compatible compiler (gcc, clang)
- GNU Make

## License

See [LICENSE](LICENSE) file for details.

## Contributing

This is a personal utility library. Feel free to use and modify for your own needs.
