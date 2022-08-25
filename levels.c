#include "database.h"
#include <stdio.h>

void select_from_database_levels(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_levels\n");

    FILE* file;
    file = fopen("master_levels.db", "rb");

    int offset = getsize_file(file);
    rewind(file);
    for (int index = 0; index < offset; index++) {  
        levels_tb tmp_db;
        fread(&tmp_db, sizeof(levels_tb), 1, file);

        //Обработка вывода

        if (columns[0] == 1)
            printf("%d", tmp_db.mem_level_number);
        if (columns[1] == 1)
            printf(" %d", tmp_db.cells_number);
        if (columns[2] == 1)
            printf(" %d", tmp_db.protect_flag);

        printf("\n");

        //printf("%d %d %d\n", tmp_db.mem_level_number, tmp_db.cells_number, tmp_db.protect_flag);
    }

    fclose(file);
}

int getsize_file(FILE **file) {
  int size = 0;
  fseek(*file, 0, SEEK_END);
  size = ftell(*file) / sizeof(levels_tb);
  rewind(*file);
  return size;
}