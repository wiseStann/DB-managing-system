#include <stdlib.h>
#include "io.h"

int skip_spaces() {
    char ch;
    int spaces_only = 1;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (!isspace(ch))
            spaces_only = 0;
    }
    return spaces_only;
}

char *get_line_from_stdin(int *size) {
    char *query = (char *)malloc(DEFAULT_QUERY_SIZE);
    int idx = 0, ch, code = 1;

    while ((ch = getc(stdin)) != '\n' && ch != EOF && code) {
        if (idx >= DEFAULT_QUERY_SIZE) {
            char *tmp = (char*)realloc(query, idx + REALLOC_CAP_VAL);
            if (tmp == NULL) {
                fprintf(stderr, "Unable to reallocate memory for query, aborted\n");
                free(query);
                code = 0;
            } else {
                query = tmp;
            }
        }
        query[idx++] = ch;
    }
    query[idx] = '\0';
    *size = idx;
    return (code) ? query : NULL;
}
