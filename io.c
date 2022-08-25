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

int read_file(FILE **file) {
  data data_i;
  int n = getsize_file(file);
  rewind(*file);

  for (int i = 0; i < n; i++) {
    fread(&data_i, sizeof(data), 1, *file);
    printf("%d %d %d %d %d %d %d %d\n", data_i.year, data_i.month, data_i.day,
           data_i.hour, data_i.minute, data_i.sec, data_i.status, data_i.code);
  }
  rewind(*file);
  return 0;