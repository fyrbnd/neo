#ifndef NEO_GRAPH_H_
#define NEO_GRAPH_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct graph graph;
typedef struct vertex vertex;
typedef struct path path;

struct graph {
    uint numVerts;
    vertex* vertices;
    int** matrix;
};

struct vertex {
    char* name;
};

struct path {
    uint length;
    uint* vertices;
};

int initGraph(graph* g, uint numVerts);

int setEdge(graph* g, uint from, uint to, int value);
int setEdgeND(graph* g, int from, int to, int value);
int renameVertex(graph* g, uint index, const char* newName);

int getVertIndexByName(graph g, const char* name);
char* getVertexName(graph g, uint index);

path shortestPath(graph g, uint from, uint to);
path* allPaths(graph g, uint from, uint to);

int isDirected(graph g);
/*int isConnected(graph g);
int isPlanar(graph g);
int isCyclic(graph g);
int isChordal(graph g);*/

#endif /*NEO_GRAPH_H_*/