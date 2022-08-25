#include "database.h"
#include <stdio.h>

int getsize_file(FILE *file) {
  int size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(modules_tb);
  rewind(file);
  return size;
}

void select_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE]) {
    printf("[DEBUG] read_from_database_modules\n");

    FILE* file;
    file = fopen("master_modules.db", "r+b");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        modules_tb tmp_db;
        fread(&tmp_db, sizeof(modules_tb), 1, file);

        //Обработка вывода

        if (columns[0] == 1)
            printf("%d", tmp_db.id);
        if (columns[1] == 1)
            printf(" %s", tmp_db.name);
        if (columns[2] == 1)
            printf(" %d", tmp_db.mem_level_number);
        if (columns[3] == 1)
            printf(" %d", tmp_db.level_cell_number);
        if (columns[4] == 1)
            printf(" %d", tmp_db.del_flag);

        printf("\n");

        // printf("%d %s %d %d %d\n", tmp_db.id, tmp_db.name, tmp_db.mem_level_number, tmp_db.level_cell_number, tmp_db.del_flag);
    }

    fclose(file);
}

void insert_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    printf("[DEBUG] insert_from_database_modules\n");

    FILE* file;
    file = fopen("master_modules.db", "r+b");
    int offset = getsize_file(file);
    modules_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(modules_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.id = values[0];
    tmp_db.name = values[1];
    tmp_db.mem_level_number = values[2];
    tmp_db.level_cell_number = values[3];
    tmp_db.del_flag = values[4]; 

    rewriting_file_in_insert(swap_db, tmp_db, file);
    swap_db.id++;

    while (swap_db.id < offset) {
    rewriting_file_in_insert(tmp_db, swap_db, file);
    swap_db.id++;
    }

    fflush(file);
    fclose(file);
}

void update_from_database_modules(query->columns) {
    printf("[DEBUG] update_from_database_modules\n");

    FILE* file;
    file = fopen("master_modules.db", "r+b");
    int offset = getsize_file(file);
    modules_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(modules_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.id = values[0];
    tmp_db.name = values[1];
    tmp_db.mem_level_number = values[2];
    tmp_db.level_cell_number = values[3];
    tmp_db.del_flag = values[4];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(modules_tb), 1, file);
        if (tmp_db.id == swap_db.id) {
            fseek(file, -sizeof(modules_tb), SEEK_SET);
            fwrite(*tmp_db, sizeof(modules_tb), 1, file);
            break;
        }
    }

    fflush(file);
    fclose(file);
}

void delete_from_database_modules(query->columns) {
    printf("[DEBUG] delete_from_database_modules\n");

    FILE* file, file_temp;
    file = fopen("master_modules.db", "r+b");
    file_temp = fopen("temp.db", "wb");

    int offset = getsize_file(file);
    modules_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(modules_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.id = values[0];
    tmp_db.name = values[1];
    tmp_db.mem_level_number = values[2];
    tmp_db.level_cell_number = values[3];
    tmp_db.del_flag = values[4];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(modules_tb), 1, file);
        if (tmp_db.id == swap_db.id || tmp_db.name == swap_db.name || tmp_db.mem_level_number == swap_db.mem_level_number || tmp_db.level_cell_number == swap_db.level_cell_number || tmp_db.del_flag == swap_db.del_flag) {
            continue;
        } else {
            fwrite(*swap_db, sizeof(modules_tb), 1, file_temp);
        }
    }

    fflush(file);
    fclose(file_temp);
    remove("master_modules.db");
    rename("temp.db", "master_modules.db");
    fclose(file);
}

void rewriting_file_in_insert(modules_tb tmp_db, modules_tb swap_db, FILE* file) {
    printf("[DEBUG] rewriting_file_in_insert\n");
    fread(&tmp_db, sizeof(modules_tb), 1, file);
    fseek(file, -sizeof(modules_tb), SEEK_SET);
    fwrite(swap_db, sizeof(modules_tb), 1, file);
}

