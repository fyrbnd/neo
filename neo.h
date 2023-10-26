#ifndef NEO_GRAPH_H_
#define NEO_GRAPH_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct graph graph;
typedef struct node node;

struct graph {
    uint numNodes;
    node* nodes;
    int** matrix;
};

struct node {
    char* name;
};

int initGraph(graph* g, uint numNodes);
int checkGraph(graph g);

int setEdge(graph* g, uint from, uint to, int value);
int setEdgeND(graph* g, int from, int to, int value);
int renameNode(graph* g, uint index, const char* newName);

int getNodeIndexByName(graph g, const char* name);
char* getNodeName(graph g, uint index);

#endif /*NEO_GRAPH_H_*/