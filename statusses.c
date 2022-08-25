#include "database.h"

void select_from_database_statusses(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_statusses\n");

    FILE* file;
    file = fopen("master_status_events.db", "rb");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        statusses_tb tmp_db;
        fread(&tmp_db, sizeof(statusses_tb), 1, file);

        //Обработка вывода

        if (a[0] == 1)
            printf("%d", tmp_db.event_id);
        if (a[1] == 1)
            printf(" %d", tmp_db.module_id);
        if (a[2] == 1)
            printf(" %d", tmp_db.new_module_status);
        if (a[3] == 1)
            printf(" %s", tmp_db.status_date_change);
        if (a[4] == 1)
            printf(" %s", tmp_db.status_time_change);

        // printf("%d %d %d %s %s\n", tmp_db.event_id, tmp_db.module_id, tmp_db.new_module_status, tmp_db.status_date_change, tmp_db.status_time_change);
    }

    fclose(file);
    return 0;
}