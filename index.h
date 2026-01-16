#ifndef INDEX_H
#define INDEX_H

typedef struct {
    char *path;
} FileEntry;

typedef struct {
    char *term;
    int *file_ids;
    int *freqs;
    int count;
    int cap;
} TermEntry;

typedef struct {
    FileEntry *files;
    int file_count;
    int file_cap;

    TermEntry *terms;
    int term_count;
    int term_cap;
} Index;

Index *index_create();
void index_free(Index *idx);

void index_scan_dir(Index *idx, const char *dir);
int index_write(Index *idx, const char *path);
Index *index_read(const char *path);

#endif