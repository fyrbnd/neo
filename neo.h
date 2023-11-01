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

#ifndef NEO_GRAPH_H_
#define NEO_GRAPH_H_

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct graph graph;
typedef struct vertex vertex;

struct graph {
    uint numVerts;
    vertex* vertices;
    int** matrix;
};

struct vertex {
    char* name;
};

int initGraph(graph* g, uint numVerts);
int checkGraph(graph g);

int setEdge(graph* g, uint from, uint to, int value);
int setEdgeND(graph* g, int from, int to, int value);
int renameVertex(graph* g, uint index, const char* newName);

int getVertIndexByName(graph g, const char* name);
char* getVertexName(graph g, uint index);

#endif /*NEO_GRAPH_H_*/
