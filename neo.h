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

int initGraph(graph* graph, uint numNodes);
int setEdge(graph* graph, uint from, uint to, int value);
int setEdgeUndir(graph* graph, int from, int to, int value);
int renameNode(graph* graph, uint index, const char* newName);
int getNodeIndexByName(graph graph, const char* name);
char* getNodeName(graph graph, uint index);

#endif /*NEO_GRAPH_H_*/