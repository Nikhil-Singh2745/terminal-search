#ifndef SEARCH_H
#define SEARCH_H

#include "index.h"

typedef struct {
    char *path;
    int score;
} SearchResult;

void search_query(Index *idx, const char *query, SearchResult **out, int *out_count);

#endif