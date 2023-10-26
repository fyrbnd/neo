/*===------------ neo - Library for Working With Graphs in C ------------===*\
|*                                                                          *|
|* This file is part of Neo.                                                *|
|*                                                                          *|
|* Neo is free software: you can redistribute it and/or modify it under the *|
|* terms of the GNU Lesser General Public License as published by the Free  *|
|* Software Foundation, version 2.1 of the License, or (at your option) any *|
|* later version.                                                           *|
|*                                                                          *|
|* Neo is distributed in the hope that it will be useful, but WITHOUT ANY   *|
|* WARRANTY; without even the implied warranty of MERCHANTABILITY or        *|
|* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public      *|
|* License for more details.                                                *|
|*                                                                          *|
|* You should have received a copy of the GNU Lesser General Public License *|
|* along with Neo. If not, see <https://www.gnu.org/licenses/>.             *|
|*                                                                          *|
\*===--------------------------------------------------------------------===*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neo.h"

int initGraph(graph* g, uint numNodes) {
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

int checkGraph(graph g) {
    if (g.nodes == NULL ||
        g.matrix == NULL ||
        g.numNodes == 0
    ) return -1;

    for (int i = 0; i < g.numNodes; ++i) {
        if (g.matrix[i] == NULL) return -1;
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
    if (g == NULL ||
        g->matrix == NULL ||
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    g->matrix[to][from] = value;
    return 0;
}

int renameNode(graph* g, uint index, const char* newName) {
    if (g == NULL || g->nodes == NULL) return -1;

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
