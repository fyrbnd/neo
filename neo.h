#ifndef NEO_GRAPH_H_
#define NEO_GRAPH_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct graph graph;
typedef struct node node;
typedef struct path path;

struct graph {
    uint numNodes;
    node* nodes;
    int** matrix;
};

struct node {
    char* name;
};

struct path {
    uint length;
    uint* nodes;
};

int initGraph(graph* g, uint numNodes);

int setEdge(graph* g, uint from, uint to, int value);
int setEdgeND(graph* g, int from, int to, int value);
int renameNode(graph* g, uint index, const char* newName);

int getNodeIndexByName(graph g, const char* name);
char* getNodeName(graph g, uint index);

path shortestPath(graph g, uint from, uint to);

#endif /*NEO_GRAPH_H_*/