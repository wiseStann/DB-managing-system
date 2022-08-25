#include <string.h>
#include <stdio.h>
#include "database.h"


int getsize_file2(FILE *file) {
  int size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(statusses_tb);
  rewind(file);
  return size;
}

void set_value_for_structure1(statusses_tb *statusses, int i, token_t *value) {
    switch (i) {
        case 0:
            statusses->event_id = value->number;
            break;
        case 1:
            statusses->module_id = value->number;
            break;
        case 2:
            statusses->new_module_status = value->number;
            break;
        case 3:
            strcpy(statusses->status_date_change, value->string);
            break;
        case 4:
            strcpy(statusses->status_time_change, value->string);
            break;
    }
}

void select_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE]) {
    FILE* file;
    file = fopen("master_status_events.db", "r+b");

    int offset = getsize_file2(file);

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
}

void insert_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file;
    file = fopen("master_status_events.db", "r+b");
    int offset = getsize_file2(file);
    statusses_tb tmp_db, swap_db;

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure1(&tmp_db, i, values[i]);
    }

    rewriting_file_in_insert2(&swap_db, &tmp_db, file);
    swap_db.event_id++;

    while (swap_db.event_id < offset) {
        rewriting_file_in_insert2(&tmp_db, &swap_db, file);
        swap_db.event_id++;
    }

    fflush(file);
    fclose(file);
}

void update_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file;
    file = fopen("master_status_events.db", "r+b");
    int offset = getsize_file2(file);
    statusses_tb tmp_db, swap_db;

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure1(&tmp_db, i, values[i]);
    }

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(statusses_tb), 1, file);
        if (tmp_db.event_id == swap_db.event_id) {
            fseek(file, -sizeof(statusses_tb), SEEK_SET);
            fwrite(&tmp_db, sizeof(statusses_tb), 1, file);
            break;
        }
    }

    fflush(file);
    fclose(file);
}

void delete_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values) {
    FILE* file, *file_temp;
    file = fopen("master_status_events.db", "r+b");
    file_temp = fopen("temp.db", "wb");

    int offset = getsize_file2(file);
    statusses_tb tmp_db, swap_db;

    fseek(file, offset, SEEK_SET);

    for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
        if (columns[i] == 1)
            set_value_for_structure1(&tmp_db, i, values[i]);
    }

    for (int index = 0; index < offset; index++) {
        fread(&swap_db, sizeof(statusses_tb), 1, file);
        if (tmp_db.event_id == swap_db.event_id || tmp_db.module_id == swap_db.module_id || tmp_db.new_module_status == swap_db.new_module_status ||
         tmp_db.status_date_change == swap_db.status_date_change || tmp_db.status_time_change == swap_db.status_time_change) {
            continue;
        } else {
            fwrite(&swap_db, sizeof(statusses_tb), 1, file_temp);
        }
    }

    fflush(file);
    fclose(file_temp);
    remove("master_status_events.db");
    rename("temp.db", "master_status_events.db");
    fclose(file);
}

void rewriting_file_in_insert2(statusses_tb* tmp_db, statusses_tb* swap_db, FILE* file) {
    fread(tmp_db, sizeof(statusses_tb), 1, file);
    fseek(file, -sizeof(statusses_tb), SEEK_SET);
    fwrite(swap_db, sizeof(statusses_tb), 1, file);
}
