#include <stdio.h>
#include "neo.h"

/*Random non-useless program used for testing our library.*/

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

uint decLen(int n) {
    if (!(n / 10)) return n < 0 ? 2 : 1;
    return decLen(n / 10) + 1;
}

void printMatrix(FILE* stream, graph graph, const char* prefix) {
    uint lenM = 1;
    
    for (uint i = 0; i < graph.numNodes; ++i) {
        for (uint k = 0; k < graph.numNodes; ++k) {
            uint lenC = decLen(graph.matrix[i][k]);
            if (lenC > lenM) lenM = lenC;
        }
    }

    for (uint i = 0; i < graph.numNodes; ++i) {
        fprintf(stream, "%s", prefix);
        for (uint k = 0; k < graph.numNodes; ++k) {
            fprintf(stream, "%*d ", lenM, graph.matrix[i][k]);
        }
        fputc('\n', stream);
    }

    return;
}

void printNodes(FILE* stream, graph graph, const char* prefix) {
    for (uint i = 0; i < graph.numNodes; ++i) {
        /*fprintf(stream, "%snode %-2i: %s\n", prefix, i, graph.nodes[i].name);*/
        fprintf(stream, "%snode %*d: %s\n", prefix, decLen(graph.numNodes), i, getNodeName(graph, i));
    }
}

void printGraphState(graph graph) {
    puts("  -> current graph state:\n    - nodes:");
    printNodes(stdout, graph, "        ");
    puts("    - matrix:");
    printMatrix(stdout, graph, "        ");
}

int test(void) {
    int size = 4;
    graph testgraph;
    
    puts(":: test begin");
    puts("  -> initializing graph");
    if (initGraph(&testgraph, size)) return -1;
    puts("  -> init successful");
    printGraphState(testgraph);

    puts(":: test 1: setting node names");
    if (renameNode(&testgraph, 0, "nodeA") ||
        renameNode(&testgraph, 1, "nodeB") ||
        renameNode(&testgraph, 3, "nodeD")
    ) return -1;
    puts("  -> test 1 successful");
    puts("  -> current node list:");
    printNodes(stdout, testgraph, "      ");

    puts(":: test 2: renaming node");
    if (renameNode(&testgraph, 1, "nodeB-nameIsLongerThanBefore")) return -1;
    puts("  -> test 2 successful");
    puts("  -> current node list:");
    printNodes(stdout, testgraph, "      ");

    puts(":: test 3: setting edges");
    if (setEdgeUndir(&testgraph, 0, 1, 1) ||
        setEdge(&testgraph, 0, 3, -30) ||
        setEdge(&testgraph, 1, 2, 1) ||
        setEdgeUndir(&testgraph, 1, 3, 3) ||
        setEdge(&testgraph, 2, 0, 42) ||
        setEdge(&testgraph, 2, 3, 69420)
    ) return -1;
    puts("  -> test 3 successful");
    puts("  -> current matrix:");
    printMatrix(stdout, testgraph, "    ");

    /* add more tests */

    puts(":: all tests successful");
    return 0;
}

int main(void) {
    if (test()) {
        fputs("\033[41m?\033[0m\n", stderr);
        return -1;
    }

    return 0;
}
