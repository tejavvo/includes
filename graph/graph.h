#ifndef GRAPH_H
#define GRAPH_H

typedef unsigned long usize;

/* adjacency list for a single vertex */
typedef struct {
    int *neighbors;   /* array of adjacent vertex indices */
    usize count;      /* number of neighbors */
    usize capacity;   /* allocated capacity */
} adjacency_list;

/* graph structure using adjacency lists */
typedef struct {
    adjacency_list *vertices;
    usize num_vertices;
    usize capacity;
} graph;

/* visitor callback for traversal */
typedef void (*graph_visitor)(int vertex);

typedef struct {
    graph (*create)(usize capacity);
    void  (*destroy)(graph *g);
    
    int   (*add_vertex)(graph *g);
    int   (*add_edge)(graph *g, int from, int to);
    int   (*has_edge)(graph *g, int from, int to);
    int   (*remove_edge)(graph *g, int from, int to);
    
    void  (*dfs)(graph *g, int start, graph_visitor visit);
    void  (*bfs)(graph *g, int start, graph_visitor visit);
    
    usize (*vertex_count)(graph *g);
    usize (*degree)(graph *g, int vertex);
} module_graph;

extern const module_graph modgraph;

#endif
