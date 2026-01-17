#include "search.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void lower_str(char *s) {
    for (; *s; s++) *s = (char)tolower((unsigned char)*s);
}

static TermEntry *find_term(Index *idx, const char *term) {
    for (int i = 0; i < idx->term_count; i++) {
        if (strcmp(idx->terms[i].term, term) == 0) return &idx->terms[i];
    }
    return NULL;
}

static void add_score(int *scores, int file_id, int score) {
    scores[file_id] += score;
}

static int cmp_res(const void *a, const void *b) {
    const SearchResult *ra = a;
    const SearchResult *rb = b;
    return rb->score - ra->score;
}

//Need to implement search function, have got the structure ready and the helper functions above.