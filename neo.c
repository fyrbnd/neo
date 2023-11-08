/*===------------ neo - Library for Working With _graphs in C ------------===*\
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

int init_graph(graph* g, uint num_verts)
{
    g->num_verts = num_verts;

    g->matrix = malloc(num_verts * sizeof(int*));
    g->vertices = malloc(num_verts * sizeof(vertex));
    if (g->vertices == NULL || g->matrix == NULL) return -1;

    for (uint i = 0; i < num_verts; ++i) {
        g->matrix[i] = malloc(num_verts * sizeof(int));
        if (g->matrix[i] == NULL) return -1;

        for (uint k = 0; k < num_verts; ++k) {
            g->matrix[i][k] = i == k ? 0 : -1;
        }
    }

    return 0;
}

int check_graph(graph g)
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

int set_edge(graph* g, uint from, uint to, int value)
{
    if (g == NULL ||
        g->matrix == NULL ||
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    return 0;
}

int set_edge_nd(graph* g, int from, int to, int value)
{
    if (g == NULL ||
        g->matrix == NULL ||
        g->matrix[from] == NULL
    ) return -1;

    g->matrix[from][to] = value;
    g->matrix[to][from] = value;
    return 0;
}

int rename_vertex(graph* g, uint index, const char* new_name)
{
    if (g == NULL || g->vertices == NULL) return -1;

    if(g->vertices[index].name != NULL) free(g->vertices[index].name);

    g->vertices[index].name = malloc((strlen(new_name) + 1) * sizeof(char));
    if(g->vertices[index].name == NULL) return -1; /*this should never happen but who knows*/

    if (strcpy(g->vertices[index].name, new_name) == NULL) return -1;
    return 0;
}

int get_vert_index_by_name(graph g, const char* search_name)
{
    for (uint i = 0; i < g.num_verts; ++i) {
        if (g.vertices[i].name != NULL && !strcmp(g.vertices[i].name, search_name)) return i;
    }

    return -1;
}

int is_directed(graph g)
{
    for (uint i = 0; i < g.num_verts; ++i) {
        for (uint k = 0; k < i; ++k) {
            if (g.matrix[i][k] != g.matrix[k][i]) return 0;
        }
    }

    return 1;
}
