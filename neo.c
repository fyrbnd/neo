#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neo.h"

int initGraph(graph* graph, uint numNodes) {
    graph->numNodes = numNodes;

    graph->matrix = malloc(numNodes * sizeof(int*));
    graph->nodes = malloc(numNodes * sizeof(node));
    if (graph->nodes == NULL || graph->matrix == NULL) return -1;

    for (uint i = 0; i < numNodes; ++i) {
        graph->matrix[i] = malloc(numNodes * sizeof(int));
        if (graph->matrix[i] == NULL) return -1;

        for (uint k = 0; k < numNodes; ++k) {
            graph->matrix[i][k] = i == k ? 0 : -1;
        }
    }

    return 0;
}

int setEdge(graph* graph, uint from, uint to, int value) {
    if (graph == NULL ||
        graph->matrix == NULL || 
        graph->matrix[from] == NULL
    ) return -1;

    graph->matrix[from][to] = value;
    return 0;
}

int setEdgeUndir(graph* graph, int from, int to, int value) {
    if (setEdge(graph, from, to, value) ||
        setEdge(graph, to, from, value)
    ) return -1;

    return 0;
}

int renameNode(graph* graph, uint index, const char* newName) {
    if (graph->nodes == NULL) return -1;

    if(graph->nodes[index].name != NULL) free(graph->nodes[index].name);

    graph->nodes[index].name = malloc((strlen(newName) + 1) * sizeof(char));
    if(graph->nodes[index].name == NULL) return -1;

    if (strcpy(graph->nodes[index].name, newName) == NULL) return -1;
    return 0;
}

int getNodeIndexByName(graph graph, const char* searchName) {
    for (uint i = 0; i < graph.numNodes; ++i) {
        if (!strcmp(graph.nodes[i].name, searchName)) return i;
    }

    return -1;
}

char* getNodeName(graph graph, uint index) {
    if (index < graph.numNodes) return graph.nodes[index].name;
    return NULL;
}