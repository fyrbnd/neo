#include <stdio.h>
#include "neo.h"

/*Random non-useless program used for testing our library.*/

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

uint decLen(int n)
{
    if (!(n / 10)) return n < 0 ? 2 : 1;
    return decLen(n / 10) + 1;
}

void printMatrix(FILE* stream, graph graph, const char* prefix)
{
    uint lenM = 1;

    for (uint i = 0; i < graph.numVerts; ++i) {
        for (uint k = 0; k < graph.numVerts; ++k) {
            uint lenC = decLen(graph.matrix[i][k]);
            if (lenC > lenM) lenM = lenC;
        }
    }

    for (uint i = 0; i < graph.numVerts; ++i) {
        fprintf(stream, "%s", prefix);
        for (uint k = 0; k < graph.numVerts; ++k) {
            fprintf(stream, "%*d ", lenM, graph.matrix[i][k]);
        }
        fputc('\n', stream);
    }

    return;
}

void printVertices(FILE* stream, graph graph, const char* prefix)

{
    for (uint i = 0; i < graph.numVerts; ++i) {
        /*fprintf(stream, "%svertex %-2i: %s\n", prefix, i, graph.vertices[i].name);*/
        fprintf(stream, "%svertex %*d: %s\n", prefix, decLen(graph.numVerts), i, getVertexName(graph, i));
    }
}

void printGraphState(graph graph)
{
    puts("  -> current graph state:\n    - vertices:");
    printVertices(stdout, graph, "        ");
    puts("    - matrix:");
    printMatrix(stdout, graph, "        ");
}

int test(void)
{
    int size = 4;
    graph testgraph;

    puts(":: test begin");
    puts("  -> initializing graph");
    if (initGraph(&testgraph, size)) return -1;
    puts("  -> init successful");
    printGraphState(testgraph);

    puts(":: test 1: setting vertex names");
    if (renameVertex(&testgraph, 0, "vertexA") ||
        renameVertex(&testgraph, 1, "vertexB") ||
        renameVertex(&testgraph, 3, "vertexD")
    ) return -1;
    puts("  -> test 1 successful");
    puts("  -> current vertex list:");
    printVertices(stdout, testgraph, "      ");

    puts(":: test 2: renaming vertex");
    if (renameVertex(&testgraph, 1, "vertexB-nameIsLongerThanBefore")) return -1;
    puts("  -> test 2 successful");
    puts("  -> current vertex list:");
    printVertices(stdout, testgraph, "      ");

    puts(":: test 3: setting edges");
    if (setEdgeND(&testgraph, 0, 1, 1) ||
        setEdge(&testgraph, 0, 3, -30) ||
        setEdge(&testgraph, 1, 2, 1) ||
        setEdgeND(&testgraph, 1, 3, 3) ||
        setEdge(&testgraph, 2, 0, 42) ||
        setEdge(&testgraph, 2, 3, 69420)
    ) return -1;
    puts("  -> test 3 successful");
    puts("  -> current matrix:");
    printMatrix(stdout, testgraph, "    ");

    puts(":: test 4: get vertex index");
    printf("  -> index of vertex \"vertexD\": %d", getVertIndexByName(testgraph, "vertexD"));
    printf("  -> index of vertex \"thisIsNotAValidVertexName\": %d", getVertIndexByName(testgraph, "thisIsNotAValidVertexName"));
    puts("  -> test 4 successful");

    /* add more tests */

    puts(":: all tests successful");
    return 0;
}

int main(void) {
    if (test()) {
        fputs("\033[41m?\033[0m\n", stderr); /* why the everliving fuck does puts append a fucking newline but fputs doesn't it's literally the exact same fucking thing except that the fucking file stream is predefined as fucking stdout this makes me so fucking angry why the fuck did they do this */
        return -1;
    }

    return 0;
}
