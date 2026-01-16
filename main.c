//Just the basic setup, LOTS to do
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
        //Need to work on index.h
        return 0;
    }

    if (strcmp(argv[1], "search") == 0) {
        if (argc < 4) {
            usage();
            return 1;
        }
        //Need to work on search.h
        return 0;
    }

    usage();
    return 1;
}