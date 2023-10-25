#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neo.h"

int initg(graph* g, uint numNodes) {
    g->numNodes = numNodes;

    g->matrix = malloc(numNodes * sizeof(int*));
    g->nodes = malloc(numNodes * sizeof(node));
    if (g->nodes == NULL || g->matrix == NULL) return -1;

    for (uint i = 0; i < numNodes; ++i) {
        g->matrix[i] = malloc(numNodes * sizeof(int));
        if (g->matrix[i] == NULL) return -1;

        for (uint k = 0; k < numNodes; ++k) {
            g->matrix[i][k] = i == k ? 0 : -1;
        }
    }

    return 0;
}

int setEdge(graph* g, uint from, uint to, int value) {
    if (g == NULL ||
        g->matrix == NULL || 
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    return 0;
}

int setEdgeND(graph* g, int from, int to, int value) {
    if (setEdge(g, from, to, value) ||
        setEdge(g, to, from, value)
    ) return -1;

    return 0;
}

int renameNode(graph* g, uint index, const char* newName) {
    if (g->nodes == NULL) return -1;

    if(g->nodes[index].name != NULL) free(g->nodes[index].name);

    g->nodes[index].name = malloc((strlen(newName) + 1) * sizeof(char));
    if(g->nodes[index].name == NULL) return -1;

    if (strcpy(g->nodes[index].name, newName) == NULL) return -1;
    return 0;
}

int getNodeIndexByName(graph g, const char* searchName) {
    for (uint i = 0; i < g.numNodes; ++i) {
        if (g.nodes[i].name != NULL && !strcmp(g.nodes[i].name, searchName)) return i;
    }

    return -1;
}

char* getNodeName(graph g, uint index) {
    if (index < g.numNodes) return g.nodes[index].name;
    return NULL;
}