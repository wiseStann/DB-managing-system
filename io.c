#include <ctype.h>
#include "io.h"


int skip_spaces() {
    int spaces_only = 1;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (!isspace(ch))
            spaces_only = 0;
    }
    return spaces_only;
}

char *get_line_from_stdin() {
    char *query = (char *)malloc(DEFAULT_QUERY_SIZE)
}