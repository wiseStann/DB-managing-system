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
    FILE* file;
    file = fopen("master_modules.db", "rb");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        modules_tb tmp_db;
        fread(&tmp_db, sizeof(modules_tb), 1, file);

        //Обработка вывода
        printf("%d %s %d %d %d\n", tmp_db.id, tmp_db.name, tmp_db.mem_level_number, tmp_db.level_cell_number, tmp_db.del_flag);
    }

    fclose(file);
    return 0;
}
