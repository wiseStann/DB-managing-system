#ifndef IO_H_
#define IO_H_

#include <stdio.h>

#define DEFAULT_QUERY_SIZE 128
#define REALLOC_CAP_VAL    16

int skip_spaces();

char *get_line_from_stdin(int *size);


#endif  // IO_H_
