#include "database.h"

void select(select_q *query) {
    printf("[DEBUG] select\n");
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

void delete(delete_q *query) {
    printf("[DEBUG] delete\n");
    switch(query->table.id) {
        case MODULES_TB_ID: delete_from_database_modules(query->);
            break;
        case LEVELS_TB_ID: delete_from_database_levels(query->);
            break;
        case STATUSSES_TB_ID: delete_from_database_statusses(query->);
            break;
        default:
            break; 
    }
    
}

void insert(insert_q *query) {
    printf("[DEBUG] insert\n");
    switch (query->table.id) {
        case MODULES_TB_ID: insert_from_database_modules(query->);
            break;
        case LEVELS_TB_ID: insert_from_database_levels(query->);
            break;
        case STATUSSES_TB_ID: insert_from_database_statusses(query->);
            break;
        default: 
            break;
    }
}

int update(update_q *query) {
    printf("[DEBUG] update\n");
    switch (query->table.id) {
        case MODULES_TB_ID: update_from_database_modules(query->);
            break;
        case LEVELS_TB_ID: update_from_database_levels(query->);;
            break;
        case STATUSSES_TB_ID:update_from_database_statusses(query->);;
            break;
        default:
            break; 
    }

}
