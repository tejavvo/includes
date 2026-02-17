#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

/* ---- adjacency list helpers ---- */

static void adjlist_init(adjacency_list *adj, usize initial_cap) {
    adj->neighbors = malloc(initial_cap * sizeof(int));
    adj->count = 0;
    adj->capacity = initial_cap;
}

static void adjlist_destroy(adjacency_list *adj) {
    if (adj && adj->neighbors) {
        free(adj->neighbors);
        adj->neighbors = NULL;
        adj->count = adj->capacity = 0;
    }
}

static int adjlist_add(adjacency_list *adj, int vertex) {
    if (!adj) return 0;
    
    /* check if already exists */
    for (usize i = 0; i < adj->count; i++) {
        if (adj->neighbors[i] == vertex) return 1; /* already present */
    }
    
    /* resize if needed */
    if (adj->count >= adj->capacity) {
        usize new_cap = adj->capacity * 2;
        int *new_buf = realloc(adj->neighbors, new_cap * sizeof(int));
        if (!new_buf) return 0;
        adj->neighbors = new_buf;
        adj->capacity = new_cap;
    }
    
    adj->neighbors[adj->count++] = vertex;
    return 1;
}

static int adjlist_has(adjacency_list *adj, int vertex) {
    if (!adj) return 0;
    for (usize i = 0; i < adj->count; i++) {
        if (adj->neighbors[i] == vertex) return 1;
    }
    return 0;
}

static int adjlist_remove(adjacency_list *adj, int vertex) {
    if (!adj) return 0;
    for (usize i = 0; i < adj->count; i++) {
        if (adj->neighbors[i] == vertex) {
            /* shift remaining elements */
            for (usize j = i; j < adj->count - 1; j++) {
                adj->neighbors[j] = adj->neighbors[j + 1];
            }
            adj->count--;
            return 1;
        }
    }
    return 0;
}

/* ---- graph operations ---- */

static graph graph_create(usize capacity) {
    graph g;
    g.vertices = malloc(capacity * sizeof(adjacency_list));
    g.num_vertices = 0;
    g.capacity = capacity;
    
    /* initialize all adjacency lists */
    for (usize i = 0; i < capacity; i++) {
        adjlist_init(&g.vertices[i], 4); /* start with small capacity */
    }
    
    return g;
}

static void graph_destroy(graph *g) {
    if (!g || !g->vertices) return;
    
    for (usize i = 0; i < g->capacity; i++) {
        adjlist_destroy(&g->vertices[i]);
    }
    
    free(g->vertices);
    g->vertices = NULL;
    g->num_vertices = g->capacity = 0;
}

static int graph_add_vertex(graph *g) {
    if (!g || g->num_vertices >= g->capacity) return -1;
    return g->num_vertices++;
}

static int graph_add_edge(graph *g, int from, int to) {
    if (!g || from < 0 || to < 0) return 0;
    if ((usize)from >= g->num_vertices || (usize)to >= g->num_vertices) return 0;
    
    return adjlist_add(&g->vertices[from], to);
}

static int graph_has_edge(graph *g, int from, int to) {
    if (!g || from < 0 || to < 0) return 0;
    if ((usize)from >= g->num_vertices || (usize)to >= g->num_vertices) return 0;
    
    return adjlist_has(&g->vertices[from], to);
}

static int graph_remove_edge(graph *g, int from, int to) {
    if (!g || from < 0 || to < 0) return 0;
    if ((usize)from >= g->num_vertices || (usize)to >= g->num_vertices) return 0;
    
    return adjlist_remove(&g->vertices[from], to);
}

/* ---- traversal algorithms ---- */

static void graph_dfs_helper(graph *g, int v, int *visited, graph_visitor visit) {
    visited[v] = 1;
    if (visit) visit(v);
    
    adjacency_list *adj = &g->vertices[v];
    for (usize i = 0; i < adj->count; i++) {
        int neighbor = adj->neighbors[i];
        if (!visited[neighbor]) {
            graph_dfs_helper(g, neighbor, visited, visit);
        }
    }
}

static void graph_dfs(graph *g, int start, graph_visitor visit) {
    if (!g || start < 0 || (usize)start >= g->num_vertices) return;
    
    int *visited = calloc(g->num_vertices, sizeof(int));
    if (!visited) return;
    
    graph_dfs_helper(g, start, visited, visit);
    
    free(visited);
}

static void graph_bfs(graph *g, int start, graph_visitor visit) {
    if (!g || start < 0 || (usize)start >= g->num_vertices) return;
    
    int *visited = calloc(g->num_vertices, sizeof(int));
    int *queue = malloc(g->num_vertices * sizeof(int));
    if (!visited || !queue) {
        free(visited);
        free(queue);
        return;
    }
    
    usize head = 0, tail = 0;
    
    /* enqueue start */
    queue[tail++] = start;
    visited[start] = 1;
    
    while (head < tail) {
        int v = queue[head++];
        if (visit) visit(v);
        
        adjacency_list *adj = &g->vertices[v];
        for (usize i = 0; i < adj->count; i++) {
            int neighbor = adj->neighbors[i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[tail++] = neighbor;
            }
        }
    }
    
    free(visited);
    free(queue);
}

/* ---- utility functions ---- */

static usize graph_vertex_count(graph *g) {
    return g ? g->num_vertices : 0;
}

static usize graph_degree(graph *g, int vertex) {
    if (!g || vertex < 0 || (usize)vertex >= g->num_vertices) return 0;
    return g->vertices[vertex].count;
}

/* ---- namespace ---- */

const module_graph modgraph = {
    .create        = graph_create,
    .destroy       = graph_destroy,
    .add_vertex    = graph_add_vertex,
    .add_edge      = graph_add_edge,
    .has_edge      = graph_has_edge,
    .remove_edge   = graph_remove_edge,
    .dfs           = graph_dfs,
    .bfs           = graph_bfs,
    .vertex_count  = graph_vertex_count,
    .degree        = graph_degree
};
