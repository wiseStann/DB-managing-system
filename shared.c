#include "database.h"


tb_entity *select(select_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID:
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
