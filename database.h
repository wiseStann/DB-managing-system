#ifndef DATABASE_SRC_H_
#define DATABASE_SRC_H_

#include <stdio.h>
#include "tokenizer.h"

#define MODULES_TB_ID   1
#define LEVELS_TB_ID    2
#define STATUSSES_TB_ID 3

#define TABLE_COLUMNS_MAX_SIZE 6


typedef struct Modules {
    int id;
    char name[30];
    int mem_level_number;
    int level_cell_number;
    int del_flag;
} modules_tb;

typedef struct Levels {
    int mem_level_number;
    int cells_number;
    int protect_flag;
} levels_tb;

typedef struct Statusses {
    int event_id;
    int module_id;
    int new_module_status;
    char status_date_change[11];
    char status_time_change[9];
} statusses_tb;


typedef struct Entity {
    union {
        modules_tb   *module;
        levels_tb    *level;
        statusses_tb *status;
    };
    int curr_table;
} tb_entity;


////////////////// QUERIES /////////////////////


#define SELECT_QUERY_ID 1
#define INSERT_QUERY_ID 2
#define UPDATE_QUERY_ID 3
#define DELETE_QUERY_ID 4


// select id, name from modules (group by id)
typedef struct SelectQuery {
    int columns[TABLE_COLUMNS_MAX_SIZE];
    int table_id;
} select_q;

// insert into modules (id, name) (12, "new module")
typedef struct InsertQuery {
    int table_id;
    int columns[TABLE_COLUMNS_MAX_SIZE];
    token_t **values;
} insert_q;

// update modules set id = 12, name = "updated module"
typedef struct UpdateQuery {
    int table_id;
    int columns[TABLE_COLUMNS_MAX_SIZE];
    token_t **values;
} update_q;

// delete from modules where id = 2
typedef struct DeleteQuery {
    int table_id;
    int columns[TABLE_COLUMNS_MAX_SIZE];
    token_t **values;
} delete_q;


typedef struct Query {
    union {
        select_q *select_query;
        insert_q *insert_query;
        update_q *update_query;
        delete_q *delete_query;
    };
    int query_id;
} query_t;

query_t *new_query(int query_id);

void free_query(query_t *query);

select_q *new_select_query(int columns[TABLE_COLUMNS_MAX_SIZE], int table_id);

insert_q *new_insert_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], int size, token_t **values);

update_q *new_update_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], int size, token_t **values);

delete_q *new_delete_query(int table_id, int columns[TABLE_COLUMNS_MAX_SIZE], int size, token_t **values);


//////////////////////////////////////////////////////


void select(select_q *query);

void insert(insert_q *query);

void update(update_q *query);

void delete(delete_q *query);

void select_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE]);

void insert_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void update_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);


void delete_from_database_statusses(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void select_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE]);

void insert_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void update_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void delete_from_database_modules(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void select_from_database_levels(int columns[TABLE_COLUMNS_MAX_SIZE]);

void insert_from_database_levels(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void update_from_database_levels(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void delete_from_database_levels(int columns[TABLE_COLUMNS_MAX_SIZE], token_t** values);

void rewriting_file_in_insert1(levels_tb* tmp_db, levels_tb* swap_db, FILE* file);

void rewriting_file_in_insert2(statusses_tb* tmp_db, statusses_tb* swap_db, FILE* file);

void rewriting_file_in_insert3(modules_tb tmp_db, modules_tb swap_db, FILE* file);


#endif  // DATABASE_SRC_H_
