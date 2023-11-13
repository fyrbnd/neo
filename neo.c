/*===------------ neo - Library for Working With graphs in C ------------===*\
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

int init_graph(graph_t* g, uint n)
{
    g->num_verts = n;

    g->matrix = malloc(n * sizeof(int*));
    g->vertices = malloc(n * sizeof(vertex_t));
    if (g->vertices == NULL || g->matrix == NULL) return -1;

    for (uint i = 0; i < n; ++i) {
        g->matrix[i] = malloc(n * sizeof(int));
        if (g->matrix[i] == NULL) return -1;

        for (uint k = 0; k < n; ++k) {
            g->matrix[i][k] = i == k ? 0 : -1;
        }
    }

    return 0;
}

int check_graph(graph_t g)
{
    if (g.vertices == NULL ||
        g.matrix == NULL ||
        g.num_verts == 0
    ) return -1;

    for (uint i = 0; i < g.num_verts; ++i) {
        if (g.matrix[i] == NULL) return -1;
    }

    return 0;
}

int set_edge(graph_t* g, uint from, uint to, int value)
{
    if (g == NULL ||
        g->matrix == NULL ||
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    return 0;
}

int set_edge_nd(graph_t* g, int from, int to, int value)
{
    if (g == NULL ||
        g->matrix == NULL ||
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    g->matrix[to][from] = value;
    return 0;
}

int rename_vertex(graph_t* g, uint index, const char* name_new)
{
    if (g == NULL || g->vertices == NULL) return -1;

    if(g->vertices[index].name != NULL) free(g->vertices[index].name);

    g->vertices[index].name = malloc((strlen(name_new) + 1) * sizeof(char));
    if(g->vertices[index].name == NULL) return -1; /*this should never happen but who knows*/

    if (strcpy(g->vertices[index].name, name_new) == NULL) return -1;
    return 0;
}

int get_vert_index_by_name(graph_t g, const char* search_name)
{
    for (uint i = 0; i < g.num_verts; ++i) {
        if (g.vertices[i].name != NULL && !strcmp(g.vertices[i].name, search_name)) return i;
    }

    return -1;
}

int is_directed(graph_t g)
{
    for (uint i = 0; i < g.num_verts; ++i) {
        for (uint k = 0; k < i; ++k) {
            if (g.matrix[i][k] != g.matrix[k][i]) return 0;
        }
    }

    return 1;
}
