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

void search_query(Index *idx, const char *query, SearchResult **out, int *out_count) {
    *out = NULL;
    *out_count = 0;
    if (!idx || !query) return;

    int *scores = calloc(idx->file_count, sizeof(int));
    char qbuf[512];
    strncpy(qbuf, query, sizeof(qbuf) - 1);
    qbuf[sizeof(qbuf) - 1] = 0;

    char *tok = qbuf;
    while (*tok) {
        while (*tok && !isalnum((unsigned char)*tok)) tok++;
        if (!*tok) break;
        char *start = tok;
        while (*tok && isalnum((unsigned char)*tok)) tok++;
        if (*tok) { *tok = 0; tok++; }
        lower_str(start);
        TermEntry *t = find_term(idx, start);
        if (t) {
            for (int i = 0; i < t->count; i++) {
                add_score(scores, t->file_ids[i], t->freqs[i]);
            }
        }
    }

    int count = 0;
    for (int i = 0; i < idx->file_count; i++) {
        if (scores[i] > 0) count++;
    }
    if (count == 0) {
        free(scores);
        return;
    }

    SearchResult *res = malloc(sizeof(SearchResult) * count);
    int ri = 0;
    for (int i = 0; i < idx->file_count; i++) {
        if (scores[i] > 0) {
            res[ri].path = idx->files[i].path;
            res[ri].score = scores[i];
            ri++;
        }
    }
    qsort(res, count, sizeof(SearchResult), cmp_res);

    free(scores);
    *out = res;
    *out_count = count;
}