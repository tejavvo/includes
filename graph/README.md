# Usage

## Basic Graph Operations

```c
#include <stdio.h>
#include "graph/graph.h"

void print_vertex(int v) {
    printf("%d ", v);
}

int main() {
    // Create graph with capacity for 10 vertices
    graph g = modgraph.create(10);
    
    // Add vertices (returns vertex ID)
    int v0 = modgraph.add_vertex(&g); // 0
    int v1 = modgraph.add_vertex(&g); // 1
    int v2 = modgraph.add_vertex(&g); // 2
    int v3 = modgraph.add_vertex(&g); // 3
    
    // Add directed edges
    modgraph.add_edge(&g, v0, v1);
    modgraph.add_edge(&g, v0, v2);
    modgraph.add_edge(&g, v1, v3);
    modgraph.add_edge(&g, v2, v3);
    
    // Check edge existence
    if (modgraph.has_edge(&g, v0, v1)) {
        printf("Edge 0->1 exists\n");
    }
    
    // Graph traversals
    printf("DFS from 0: ");
    modgraph.dfs(&g, v0, print_vertex);
    printf("\n");
    
    printf("BFS from 0: ");
    modgraph.bfs(&g, v0, print_vertex);
    printf("\n");
    
    // Get vertex degree (out-degree for directed graph)
    usize deg = modgraph.degree(&g, v0);
    printf("Degree of vertex 0: %lu\n", deg);
    
    // Remove edge
    modgraph.remove_edge(&g, v0, v1);
    
    // Cleanup
    modgraph.destroy(&g);
    
    return 0;
}
```

## Output
```
Edge 0->1 exists
DFS from 0: 0 1 3 2 
BFS from 0: 0 1 2 3 
Degree of vertex 0: 2
```

## Creating Undirected Graph

For an undirected graph, add edges in both directions:

```c
void add_undirected_edge(graph *g, int a, int b) {
    modgraph.add_edge(g, a, b);
    modgraph.add_edge(g, b, a);
}
```
