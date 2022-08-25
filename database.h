#define ENTITY

#define MODULES_TB_ID 1
#define LEVELS_TB_ID 2
#define STATUSSES_TB_ID 3

#define COLUMN_SIZE 10

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

#define MAX_COLUMN_SIZE 128

#define SELECT_QUERY_ID 1
#define INSERT_QUERY_ID 2
#define UPDATE_QUERY_ID 3
#define DELETE_QUERY_ID 4

typedef struct SelectQuery {
    // char *columns[128];
    int columns[10]; // какие столбцы выводить 
    int table_id; // какую таблицу открывать
} select_q;

// typedef struct InsertQuery {
//     char *columns[128];
//     int table_id;
// } select_q;

typedef struct Query {
    union {
        select_q *select_query;
        // else
    };
    int query_id;
} query_t;


// select id from table

void select(select_q *query);

void output_entity(tb_entity *entity);

int delete(FILE *db, int id);

int insert(FILE *db, tb_entity *entity);

int update(FILE *db, int id, tb_entity *entity);

//////////////////////////////////////////////////////

