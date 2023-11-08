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

#ifndef NEO_GRAPH_H_
#define NEO_GRAPH_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct graph graph;
typedef struct vertex vertex;
typedef struct path path;


struct graph {
    uint num_verts;
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

int init_graph(graph* g, uint num_verts);
int check_graph(graph g);

int set_edge(graph* g, uint from, uint to, int value);
int set_edge_nd(graph* g, int from, int to, int value);
int rename_vertex(graph* g, uint index, const char* new_name);

int get_vert_index_by_name(graph g, const char* name);

path shortest_path(graph g, uint from, uint to); /*TODO*/
path* all_paths(graph g, uint from, uint to); /*TODO*/

int is_directed(graph g);
/*int is_connected(graph g);
int is_planar(graph g);
int is_cyclic(graph g);
int is_chordal(graph g);*/

#endif /*NEO_GRAPH_H_*/
