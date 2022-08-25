#include "database.h"

void read_from_database_statusses() {
    printf("[DEBUG] read_from_database_statusses\n");

    FILE* file;
    file = fopen("master_status_events.db", "rb");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        statusses_tb tmp_db;
        fread(&tmp_db, sizeof(statusses_tb), 1, file);

        //Обработка вывода
        printf("%d %d %d %s %s\n", tmp_db.event_id, tmp_db.module_id, tmp_db.new_module_status, tmp_db.status_date_change, tmp_db.status_date_change);
    }

    fclose(file);
    return 0;
}
