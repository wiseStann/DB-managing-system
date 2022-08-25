#include <stdlib.h>
#include <string.h>
#include "database.h"


query_t *new_query(int query_id) {
    query_t *query = (query_t *)malloc(sizeof(struct Query));
    query->query_id = query_id;
    return query;
}

void free_query(query_t *query) {
    switch (query->query_id) {
        case SELECT_QUERY_ID:
            free(query->select_query);
            break;
        case INSERT_QUERY_ID:
            free(query->insert_query);
            break;
        case UPDATE_QUERY_ID:
            free(query->update_query);
            break;
        case DELETE_QUERY_ID:
            free(query->delete_query);
            break;
    }
    free(query);
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
