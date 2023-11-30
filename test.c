#include <stdio.h>
#include "neo.h"

/*Random non-useless program used for testing our library.*/

uint dec_len(int n)
{
    if (!(n / 10)) return n < 0 ? 2 : 1;
    return dec_len(n / 10) + 1;
}

void print_matrix(FILE* stream, graph_t graph, const char* prefix)
{
    uint lenM = 1;

    for (uint i = 0; i < graph.num_verts; ++i) {
        for (uint k = 0; k < graph.num_verts; ++k) {
            uint lenC = dec_len(graph.matrix[i][k]);
            if (lenC > lenM) lenM = lenC;
        }
    }

    for (uint i = 0; i < graph.num_verts; ++i) {
        fprintf(stream, "%s", prefix);
        for (uint k = 0; k < graph.num_verts; ++k) {
            fprintf(stream, "%*d ", lenM, graph.matrix[i][k]);
        }
        fputc('\n', stream);
    }

    return;
}

void print_vertices(FILE* stream, graph_t graph, const char* prefix)
{
    for (uint i = 0; i < graph.num_verts; ++i) {
        /*fprintf(stream, "%svertex %-2i: %s\n", prefix, i, graph.vertices[i].name);*/
        fprintf(stream, "%svertex %*d: %s\n", prefix, dec_len(graph.num_verts), i, graph.vertices[i].name);
    }
}

void print_graph_state(graph_t graph)
{
    puts("  -> current graph state:\n    - vertices:");
    print_vertices(stdout, graph, "        ");
    puts("    - matrix:");
    print_matrix(stdout, graph, "        ");
}

int test(void)
{
    int size = 4;
    graph_t testgraph;

    puts(":: test begin");
    puts("  -> initializing graph");
    if (init_graph(&testgraph, size)) return -1;
    puts("  -> init successful");
    print_graph_state(testgraph);

    puts(":: test 1: setting vertex names");
    if (rename_vertex(&testgraph, 0, "vertexA") ||
        rename_vertex(&testgraph, 1, "vertexB") ||
        rename_vertex(&testgraph, 3, "vertexD")
    ) return -1;
    puts("  -> test 1 successful");
    puts("  -> current vertex list:");
    print_vertices(stdout, testgraph, "      ");

    puts(":: test 2: renaming vertex");
    if (rename_vertex(&testgraph, 1, "vertexB-nameIsLongerThanBefore")) return -1;
    puts("  -> test 2 successful");
    puts("  -> current vertex list:");
    print_vertices(stdout, testgraph, "      ");

    puts(":: test 3: setting edges");
    if (set_edge_nd(&testgraph, 0, 1, 1) ||
        set_edge(&testgraph, 0, 3, -30) ||
        set_edge(&testgraph, 1, 2, 1) ||
        set_edge_nd(&testgraph, 1, 3, 3) ||
        set_edge(&testgraph, 2, 0, 42) ||
        set_edge(&testgraph, 2, 3, 69420)
    ) return -1;
    puts("  -> test 3 successful");
    puts("  -> current matrix:");
    print_matrix(stdout, testgraph, "    ");

    puts(":: test 4: get vertex index");
    printf("  -> index of vertex \"vertexD\": %d", get_vert_index_by_name(testgraph, "vertexD"));
    printf("  -> index of vertex \"thisIsNotAValid_vertex_name\": %d", get_vert_index_by_name(testgraph, "thisIsNotAValid_vertex_name"));
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
