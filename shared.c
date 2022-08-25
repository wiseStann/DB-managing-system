#include "database.h"


void select(select_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID: read_from_database_modules(query->columns);
            break;
        case LEVELS_TB_ID: read_from_database_levels(query->columns);
            break;
        case STATUSSES_TB_ID: read_from_database_statusses(query->columns);
            break;
        default:
            break;
    }
}

tb_entity *read_table(int table_id) {
    
}

void output_entity(tb_entity *entity) {

}

int delete(FILE *db, int id) {

}

int insert(FILE *db, tb_entity *entity) {

}

int update(FILE *db, int id, tb_entity *entity) {

}

void read_from_database_modules(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_module\n");

    FILE* file;
    file = fopen("master_levels.db", "rb");

    int offset = getsize_file(file);
    rewind(file);
    for (int index = 0; index < offset; index++) {  
        levels_tb tmp_db;
        fread(&tmp_db, sizeof(levels_tb), 1, file);

        //Обработка вывода

        for (int i = 0; i < COLUMN_SIZE)

        printf("%d %d %d\n", tmp_db.mem_level_number, tmp_db.cells_number, tmp_db.protect_flag);
    }

    fclose(file);
}

void read_from_database_levels() {
    printf("[DEBUG] read_from_database_levels\n");

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
