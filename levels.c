#include "database.h"
#include <stdio.h>


int getsize_file(FILE *file) {
  int size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(levels_tb);
  rewind(file);
  return size;
}

void select_from_database_levels(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_levels\n");

    FILE* file;
    file = fopen("master_levels.db", "r+b");

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

void insert_from_database_levels(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    printf("[DEBUG] insert_from_database_levels\n");

    FILE* file;
    file = fopen("master_levels.db", "r+b");
    int offset = getsize_file(file);
    levels_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(levels_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.mem_level_number = values[0];
    tmp_db.cells_number = values[1];
    tmp_db.protect_flag = values[2];
 

    rewriting_file_in_insert(&swap_db, &tmp_db, file);
    swap_db.mem_level_number++;

    while (swap_db.mem_level_number < offset) {
    rewriting_file_in_insert(&tmp_db, &swap_db, file);
    swap_db.mem_level_number++;
    }

    fflush(file);
    fclose(file);
}

void update_from_database_levels(query->columns) {
    printf("[DEBUG] update_from_database_levels\n");

    FILE* file;
    file = fopen("master_levels.db", "r+b");
    int offset = getsize_file(file);
    levels_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(levels_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.mem_level_number = values[0];
    tmp_db.cells_number = values[1];
    tmp_db.protect_flag = values[2];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(levels_tb), 1, file);
        if (tmp_db.mem_level_number == swap_db.mem_level_number) {
            fseek(file, -sizeof(levels_tb), SEEK_SET);
            fwrite(*tmp_db, sizeof(levels_tb), 1, file);
            break;
        }
    }

    fflush(file);
    fclose(file);
}

void delete_from_database_levels(query->columns) {
    printf("[DEBUG] delete_from_database_levels\n");

    FILE* file, file_temp;
    file = fopen("master_levels.db", "r+b");
    file_temp = fopen("temp.db", "wb");

    int offset = getsize_file(file);
    levels_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(levels_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.mem_level_number = values[0];
    tmp_db.cells_number = values[1];
    tmp_db.protect_flag = values[2];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(levels_tb), 1, file);
        if (tmp_db.mem_level_number == swap_db.mem_level_number || tmp_db.cells_number == swap_db.cells_number || tmp_db.protect_flag == swap_db.protect_flag) {
            continue;
        } else {
            fwrite(*swap_db, sizeof(levels_tb), 1, file_temp);
        }
    }

void rewriting_file_in_insert(levels_tb* tmp_db, levels_tb* swap_db, FILE* file) {
    printf("[DEBUG] rewriting_file_in_insert\n");
    fread(tmp_db, sizeof(levels_tb), 1, file);
    fseek(file, -sizeof(levels_tb), SEEK_SET);
    fwrite(*swap_db, sizeof(levels_tb), 1, file);
}
