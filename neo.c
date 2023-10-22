#include <stdio.h>
#include <stdlib.h>

typedef struct graph graph;
typedef struct node node;
typedef unsigned int uint;

struct graph {
    struct node* nodes;
    uint width;
    int** matrix;
};

struct node {
    char* name;
    int value;
};

int graph_init(graph* graph, uint width) {
    graph->width = width;

    graph->matrix = malloc(width * sizeof(int*));
    graph->nodes = malloc(width * sizeof(struct node));
    
    if (graph->matrix == NULL || graph->nodes == NULL) return 1;
    
    for (int i = 0; i < width; ++i) {
        graph->matrix[i] = malloc(width * sizeof(int));
        if (graph->matrix[i] == NULL) return 1;

        for (int k = 0; k < width; ++k) {
            graph->matrix[i][k] = i == k ? 0 : -1;
        }
    }
    return 0;
}

void print_matrix(FILE* stream, graph graph) {
    for (int i = 0; i < graph.width; ++i) {
        for (int k = 0; k < graph.width; ++k) {
            fprintf(stream, "%4d ", graph.matrix[i][k]);
        }
        putc('\n', stream);
    }
}

void modify_edge(graph graph, int from, int to, int value) {
    graph.matrix[from][to] = value;
}

void modify_edge_undir(graph graph, int from, int to, int value) {
    modify_edge(graph, from, to, value);
    modify_edge(graph, to, from, value); 
}

/*void modify_name(node node, const char* name){
    if (node.name == NULL) {
        node.name = calloc(
    }
}*/

void print_error(void) {
    fputs("?\n", stderr);
}

int main(void) {

    struct graph graph1;

    if(graph_init(&graph1, 4)) return 1;
    print_matrix(stdout, graph1);
    putchar('\n');

    modify_edge_undir(graph1, 1, 3, 2);
    print_matrix(stdout, graph1);
    

    return 0;
}
