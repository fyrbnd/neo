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

typedef struct graph graph_t;
typedef struct vertex vertex_t;
typedef struct path path_t;


struct graph {
    uint num_verts;
    vertex_t* vertices;
    int** matrix;
};

struct vertex {
    char* name;
};

/*struct path {
    uint length;
    uint* vertices;
};*/

/* initializes graph 'g' with 'n' vertices */
int init_graph(graph_t* g, uint n);

/* checks if graph 'g' is valid */
int check_graph(graph_t g);

/* fully deletes graph 'g' */
int delete_graph(graph_t* g);

/* sets the edge between nodes 'from' and 'to' to 'value' */
int set_edge(graph_t* g, uint from, uint to, int value);

/* sets the edge between nodes 'from' and 'to' to 'value' in both directions */
int set_edge_nd(graph_t* g, int from, int to, int value);

/* sets the name of node 'index' to 'name_new' */
int rename_vertex(graph_t* g, uint index, const char* name_new);

/* add a new vertex to the graph 'g'. returns -1 on failure, otherwise returns id of created vertex */
int add_vertex(graph_t* g);

/* returns the index of the first node with the name 'search_name' */
int get_vert_index_by_name(graph_t g, const char* name);


/* returns 1 if 'g' is a directed graph */
int is_directed(graph_t g);


/*path_t shortest_path(graph_t g, uint from, uint to); TODO*/
/*path_t* all_paths(graph_t g, uint from, uint to); TODO*/
/*int is_connected(graph g); TODO*/
/*int is_planar(graph g); TODO*/
/*int is_cyclic(graph g); TODO*/
/*int is_chordal(graph g); TODO*/

#endif /*NEO_GRAPH_H_*/