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
        case MODULES_TB_ID: delete_from_database_modules(query->columns, query->values);
            break;
        case LEVELS_TB_ID: delete_from_database_levels(query->columns, query->values);
            break;
        case STATUSSES_TB_ID: delete_from_database_statusses(query->columns, query->valuesx);
            break;
        default:
            break; 
    }
    
}

void insert(insert_q *query) {
    printf("[DEBUG] insert\n");
    switch (query->table.id) {
        case MODULES_TB_ID: insert_from_database_modules(query->columns, query->values);
            break;
        case LEVELS_TB_ID: insert_from_database_levels(query->columns);
            break;
        case STATUSSES_TB_ID: insert_from_database_statusses(query->columns);
            break;
        default: 
            break;
    }
}

int update(update_q *query) {
    printf("[DEBUG] update\n");
    switch (query->table.id) {
        case MODULES_TB_ID: update_from_database_modules(query->columns);
            break;
        case LEVELS_TB_ID: update_from_database_levels(query->columns);;
            break;
        case STATUSSES_TB_ID:update_from_database_statusses(query->columns);;
            break;
        default:
            break; 
    }

}
select_q *new_select_query(int columns[TABLE_COLUMNS_MAX_SIZE], int table_id) {
    select_q *selectq = (select_q *)malloc(sizeof(struct SelectQuery));
    strcpy(selectq->columns, columns);
    selectq->table_id = table_id;
    return selectq;
}

insert_q *new_insert_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], token_t **values) {
    insert_q *insertq = (insert_q *)malloc(sizeof(struct InsertQuery));
    insertq->table_id = table_id;
    strcpy(insertq->columns, columns);
    insertq->value = values;
    return insertq;
}

update_q *new_update_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], token_t **values) {
    update_q *updateq = (update_q *)malloc(sizeof(struct UpdateQuery));
    updateq->table_id = table_id;
    strcpy(updateq->columns, columns);
    updateq->value = values;
    return updateq;
}

delete_q *new_delete_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], token_t **values) {
    delete_q *deleteq = (delete_q *)malloc(sizeof(struct DeleteQuery));
    deleteq->table_id = table_id;
    strcpy(deleteq->columns, columns);
    deleteq->value = values;
    return deleteq;
}

void select(select_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID:
            break;
    }
}

int delete(FILE *db, int id) {
    return 0;
}

int insert(FILE *db, tb_entity *entity) {
    return 0;
}

int update(FILE *db, int id, tb_entity *entity) {
    return 0;
}