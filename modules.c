#include <string.h>
#include <stdio.h>
#include "database.h"

int getsize_file3(FILE *file) {
  int size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(modules_tb);
  rewind(file);
  return size;
}

void select_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE]) {
    FILE* file;
    file = fopen("master_modules.db", "r+b");

    int offset = getsize_file3(file);

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

void set_value_for_structure2(modules_tb *module, int i, token_t *value) {
    switch (i) {
        case 0:
            module->mem_level_number = value->number;
            break;
        case 1:
            strcpy(module->name, value->string);
            break;
        case 2:
            module->mem_level_number = value->number;
            break;
        case 3:
            module->level_cell_number = value->number;
            break;
        case 4:
            module->del_flag = value->number;
            break;
    }
}

void insert_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file;
    file = fopen("master_modules.db", "r+b");
    int offset = getsize_file3(file);
    modules_tb tmp_db, swap_db = {};

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure2(&tmp_db, i, values[i]);
    }

    rewriting_file_in_insert3(swap_db, tmp_db, file);
    swap_db.id++;

    while (swap_db.id < offset) {
    rewriting_file_in_insert3(tmp_db, swap_db, file);
    swap_db.id++;
    }

    fflush(file);
    fclose(file);
}

void update_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file;
    file = fopen("master_modules.db", "r+b");
    int offset = getsize_file3(file);
    modules_tb tmp_db, swap_db;

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure2(&tmp_db, i, values[i]);
    }

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(modules_tb), 1, file);
        if (tmp_db.id == swap_db.id) {
            fseek(file, -sizeof(modules_tb), SEEK_SET);
            fwrite(&tmp_db, sizeof(modules_tb), 1, file);
            break;
        }
    }

    fflush(file);
    fclose(file);
}

void delete_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file, *file_temp;
    file = fopen("master_modules.db", "r+b");
    file_temp = fopen("temp.db", "wb");

    int offset = getsize_file3(file);
    modules_tb tmp_db, swap_db;

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure2(&tmp_db, i, values[i]);
    }

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(modules_tb), 1, file);
        if (tmp_db.id == swap_db.id || tmp_db.name == swap_db.name || tmp_db.mem_level_number == swap_db.mem_level_number || tmp_db.level_cell_number == swap_db.level_cell_number || tmp_db.del_flag == swap_db.del_flag) {
            continue;
        } else {
            fwrite(&swap_db, sizeof(modules_tb), 1, file_temp);
        }
    }

    fflush(file);
    fclose(file_temp);
    remove("master_modules.db");
    rename("temp.db", "master_modules.db");
    fclose(file);
}

void rewriting_file_in_insert3(modules_tb tmp_db, modules_tb swap_db, FILE* file) {
    fread(&tmp_db, sizeof(modules_tb), 1, file);
    fseek(file, -sizeof(modules_tb), SEEK_SET);
    fwrite(&swap_db, sizeof(modules_tb), 1, file);
}
