#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index.h"
#include "search.h"

static void usage() {
    printf("usage:\n");
    printf("  pse index <dir> <index_file>\n");
    printf("  pse search <index_file> <query>\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage();
        return 1;
    }

    if (strcmp(argv[1], "index") == 0) {
        if (argc < 4) {
            usage();
            return 1;
        }
        Index *idx = index_create();
        if (!idx) return 1;
        index_scan_dir(idx, argv[2]);
        if (index_write(idx, argv[3]) != 0) {
            fprintf(stderr, "failed to write index\n");
            index_free(idx);
            return 1;
        }
        index_free(idx);
        return 0;
    }

    if (strcmp(argv[1], "search") == 0) {
        if (argc < 4) {
            usage();
            return 1;
        }
        Index *idx = index_read(argv[2]);
        if (!idx) {
            fprintf(stderr, "failed to read index\n");
            return 1;
        }
        char *query = argv[3];
        SearchResult *results = NULL;
        int count = 0;
        search_query(idx, query, &results, &count);
        for (int i = 0; i < count; i++) {
            printf("%d\t%s\n", results[i].score, results[i].path);
        }
        free(results);
        index_free(idx);
        return 0;
    }

    usage();
    return 1;
}