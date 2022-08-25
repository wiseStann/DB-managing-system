#include "database.h"
#include <stdio.h>

void select_from_database_statusses(int columns[COLUMN_SIZE]) {
    printf("[DEBUG] read_from_database_statusses\n");

    FILE* file;
    file = fopen("master_status_events.db", "r+b");

    int offset = getsize_file(file);

    rewind(file);

    for (int index = 0; index < offset; index++) {  
        statusses_tb tmp_db;
        fread(&tmp_db, sizeof(statusses_tb), 1, file);

        //Обработка вывода

        if (columns[0] == 1)
            printf("%d", tmp_db.event_id);
        if (columns[1] == 1)
            printf(" %d", tmp_db.module_id);
        if (columns[2] == 1)
            printf(" %d", tmp_db.new_module_status);
        if (columns[3] == 1)
            printf(" %s", tmp_db.status_date_change);
        if (columns[4] == 1)
            printf(" %s", tmp_db.status_time_change);

        // printf("%d %d %d %s %s\n", tmp_db.event_id, tmp_db.module_id, tmp_db.new_module_status, tmp_db.status_date_change, tmp_db.status_time_change);
    }

    fclose(file);
    return 0;
}

void insert_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    printf("[DEBUG] insert_from_database_statusses\n");

    FILE* file;
    file = fopen("master_status_events.db", "r+b");
    int offset = getsize_file(file);
    statusses_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(statusses_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.event_id = values[0];
    tmp_db.module_id = values[1];
    tmp_db.new_module_status = values[2];
    tmp_db.status_date_change = values[3];
    tmp_db.status_time_change = values[4]; 

    rewriting_file_in_insert(&swap_db, &tmp_db, file);
    swap_db.mem_level_number++;

    while (swap_db.mem_level_number < offset) {
    rewriting_file_in_insert(&tmp_db, &swap_db, file);
    swap_db.mem_level_number++;
    }

    fflush(file);
    fclose(file);
}

void update_from_database_statusses(query->columns) {
    printf("[DEBUG] update_from_database_statusses\n");

    FILE* file;
    file = fopen("master_status_events.db", "r+b");
    int offset = getsize_file(file);
    statusses_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(statusses_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.event_id = values[0];
    tmp_db.module_id = values[1];
    tmp_db.new_module_status = values[2];
    tmp_db.status_date_change = values[3];
    tmp_db.status_time_change = values[4];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(statusses_tb), 1, file);
        if (tmp_db.event_id == swap_db.event_id) {
            fseek(file, -sizeof(statusses_tb), SEEK_SET);
            fwrite(*tmp_db, sizeof(statusses_tb), 1, file);
            break;
        }
    }

    fflush(file);
    fclose(file);
}

void delete_from_database_statusses(query->columns) {
    printf("[DEBUG] delete_from_database_statusses\n");

    FILE* file, file_temp;
    file = fopen("master_status_events.db", "r+b");
    file_temp = fopen("temp.db", "wb");

    int offset = getsize_file(file);
    statusses_tb tmp_db, swap_db;
    int index;

    int offset = index * sizeof(statusses_tb);
    fseek(file, offset, SEEK_SET);

    tmp_db.event_id = values[0];
    tmp_db.module_id = values[1];
    tmp_db.new_module_status = values[2];
    tmp_db.status_date_change = values[3];
    tmp_db.status_time_change = values[4];

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(statusses_tb), 1, file);
        if (tmp_db.event_id == swap_db.event_id || tmp_db.module_id == swap_db.module_id || tmp_db.new_module_status == swap_db.new_module_status ||
         tmp_db.status_date_change == swap_db.status_date_change || tmp_db.status_time_change == swap_db.status_time_change) {
            continue;
        } else {
            fwrite(*swap_db, sizeof(statusses_tb), 1, file_temp);
        }
    }

    fflush(file);
    fclose(file_temp);
    remove("master_status_events.db");
    rename("temp.db", "master_status_events.db");
    fclose(file);
}

void rewriting_file_in_insert(statusses_tb* tmp_db, statusses_tb* swap_db, FILE* file) {
    printf("[DEBUG] rewriting_file_in_insert\n");
    fread(tmp_db, sizeof(statusses_tb), 1, file);
    fseek(file, -sizeof(statusses_tb), SEEK_SET);
    fwrite(*swap_db, sizeof(statusses_tb), 1, file);
}

int getsize_file(FILE **file) {
  int size = 0;
  fseek(*file, 0, SEEK_END);
  size = ftell(*file) / sizeof(statusses_tb);
  rewind(*file);
  return size;
}