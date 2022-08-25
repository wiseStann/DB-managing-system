#ifndef ASHLEEFR_H_
#define ASHLEEFR_H_

#include <stdlib.h>

int getsize_file(FILE **file) {
  int size = 0;
  fseek(*file, 0, SEEK_END);
  size = ftell(*file) / sizeof(data);
  rewind(*file);
  return size;
}

#endif  // ASHLEEFR_H_