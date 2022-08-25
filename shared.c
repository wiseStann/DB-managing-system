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
