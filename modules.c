#include "database.h"

void select_from_database_modules(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_modules\n");

    FILE* file;
    file = fopen("master_modules.db", "rb");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        modules_tb tmp_db;
        fread(&tmp_db, sizeof(modules_tb), 1, file);

        //Обработка вывода

        if (a[0] == 1)
            printf("%d", tmp_db.id);
        if (a[1] == 1)
            printf(" %s", tmp_db.name);
        if (a[2] == 1)
            printf(" %d", tmp_db.mem_level_number);
        if (a[3] == 1)
            printf(" %d", tmp_db.level_cell_number);
        if (a[4] == 1)
            printf(" %d", tmp_db.del_flag);

        printf("\n");

        // printf("%d %s %d %d %d\n", tmp_db.id, tmp_db.name, tmp_db.mem_level_number, tmp_db.level_cell_number, tmp_db.del_flag);
    }

    fclose(file);
    return 0;
}
