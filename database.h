#define ENTITY

#define MODULES_TB_ID 1
#define LEVELS_TB_ID 2
#define STATUSSES_TB_ID 3

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


//////////////////////////////////////////////////////

tb_entity *select(FILE *db, int id);

int delete(FILE *db, int id);

int insert(FILE *db, tb_entity *entity);

int update(FILE *db, int id, tb_entity *entity);

//////////////////////////////////////////////////////
