#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neo.h"

int initGraph(graph* g, uint numVerts) {
    g->numVerts = numVerts;

    g->matrix = malloc(numVerts * sizeof(int*));
    g->vertices = malloc(numVerts * sizeof(vertex));
    if (g->vertices == NULL || g->matrix == NULL) return -1;

    for (uint i = 0; i < numVerts; ++i) {
        g->matrix[i] = malloc(numVerts * sizeof(int));
        if (g->matrix[i] == NULL) return -1;

        for (uint k = 0; k < numVerts; ++k) {
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

int renameVertex(graph* g, uint index, const char* newName) {
    if (g->vertices == NULL) return -1;

    if(g->vertices[index].name != NULL) free(g->vertices[index].name);

    g->vertices[index].name = malloc((strlen(newName) + 1) * sizeof(char));
    if(g->vertices[index].name == NULL) return -1;

    if (strcpy(g->vertices[index].name, newName) == NULL) return -1;
    return 0;
}

int getVertIndexByName(graph g, const char* searchName) {
    for (uint i = 0; i < g.numVerts; ++i) {
        if (g.vertices[i].name != NULL && !strcmp(g.vertices[i].name, searchName)) return i;
    }

    return -1;
}

char* getVertexName(graph g, uint index) {
    if (index < g.numVerts) return g.vertices[index].name;
    return NULL;
}

int isDirected(graph g) {
    for (uint i = 0; i < g.numVerts; ++i) {
        for (uint k = 0; k < 1; ++k) {
            if (g.matrix[i][k] != g.matrix[k][i]) return 0;
        }
    }

    return 1;
}