#include <stdio.h>
#include <stdlib.h>

typedef struct Modules {
    int id;
    char name[30];
    int mem_level_number;
    int level_cell_number;
    int del_flag;
} modules_tb;

int getsize_file(FILE* file) {
  int size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(modules_tb);
  rewind(file);
  return size;
}

int main() {
   
void insert_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    printf("[DEBUG] insert_from_database_modules\n");
    FILE* file;
    file = fopen("master_modules.db", "rb");
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

void rewriting_file_in_insert(modules_tb tmp_db, modules_tb swap_db, FILE* file) {
    printf("[DEBUG] rewriting_file_in_insert\n");
    fread(&tmp_db, sizeof(modules_tb), 1, file);
    fseek(file, -sizeof(modules_tb), SEEK_SET);
    fwrite(swap_db, sizeof(modules_tb), 1, file);
}
    return 0;
}
