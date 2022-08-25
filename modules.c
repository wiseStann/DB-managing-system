#include "database.h"

void read_from_database_modules() {
    printf("[DEBUG] read_from_database_module\n");

    FILE* file;
    file = fopen("master_levels.db", "rb");

    int offset = getsize_file(file);
    rewind(file);
    for (int index = 0; index < offset; index++) {  
        levels_tb tmp_db;
        fread(&tmp_db, sizeof(levels_tb), 1, file);

        //Обработка вывода
        printf("%d %d %d\n", tmp_db.mem_level_number, tmp_db.cells_number, tmp_db.protect_flag);
    }

    fclose(file);
}