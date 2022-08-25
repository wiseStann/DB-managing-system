#include "database.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

query_t *new_query(int query_id) {
  query_t *query = (query_t *)malloc(sizeof(struct Query));
  query->query_id = query_id;
  return query;
}

void free_query(query_t *query) {
  if (query != NULL) {
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
}

select_q *new_select_query(int columns[TABLE_COLUMNS_MAX_SIZE], int table_id) {
  select_q *selectq = (select_q *)malloc(sizeof(struct SelectQuery));
  for (int i = 0; i < TABLE_COLUMNS_MAX_SIZE; i++) {
    selectq->columns[i] = columns[i];
  }
  // strcpy(selectq->columns, columns);
  selectq->table_id = table_id;
  return selectq;
}

insert_q *new_insert_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE],
                           int size, token_t **values) {
  insert_q *insertq = (insert_q *)malloc(sizeof(struct InsertQuery));
  insertq->table_id = table_id;
  for (int i = 0; i < size; i++) {
    insertq->columns[i] = columns[i];
  }
  // strcpy(insertq->columns, columns);
  insertq->values = values;
  return insertq;
}

update_q *new_update_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE],
                           int size, token_t **values) {
  update_q *updateq = (update_q *)malloc(sizeof(struct UpdateQuery));
  updateq->table_id = table_id;
  for (int i = 0; i < size; i++) {
    updateq->columns[i] = columns[i];
  }
  // strcpy(updateq->columns, columns);
  updateq->values = values;
  return updateq;
}

delete_q *new_delete_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE],
                           int size, token_t **values) {
  delete_q *deleteq = (delete_q *)malloc(sizeof(struct DeleteQuery));
  deleteq->table_id = table_id;
  for (int i = 0; i < size; i++) {
    deleteq->columns[i] = columns[i];
  }
  // strcpy(deleteq->columns, columns);
  deleteq->values = values;
  return deleteq;
}

void select(select_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID: select_from_database_modules(query->columns);
            break;
        case LEVELS_TB_ID: select_from_database_levels(query->columns);
            break;
        case STATUSSES_TB_ID: select_from_database_statusses(query->columns);
            break;
        default:
            break;
    }
}

void delete(delete_q *query) {
    switch(query->table_id) {
        case MODULES_TB_ID: delete_from_database_modules(query->columns, query->values);
            break;
        case LEVELS_TB_ID: delete_from_database_levels(query->columns, query->values);
            break;
        case STATUSSES_TB_ID: delete_from_database_statusses(query->columns, query->values);
            break;
        default:
            break; 
    }
    
}

void insert(insert_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID: insert_from_database_modules(query->columns, query->values);
            break;
        case LEVELS_TB_ID: insert_from_database_levels(query->columns, query->values);
            break;
        case STATUSSES_TB_ID: insert_from_database_statusses(query->columns, query->values);
            break;
        default: 
            break;
    }
}

void update(update_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID: update_from_database_modules(query->columns, query->values);
            break;
        case LEVELS_TB_ID: update_from_database_levels(query->columns, query->values);
            break;
        case STATUSSES_TB_ID:update_from_database_statusses(query->columns, query->values);
            break;
        default:
            break; 
    }
}
