#include "database.h"


void select(select_q *query) {
    switch (query->table_id) {
        case MODULES_TB_ID: modules_tb tmp_db; tmp_db.curr_table = 1; read_from_database_modules(tmp_db, );
            break;
        case LEVELS_TB_ID: levels_tb tmp_db; tmp_db.curr_table = 2; read_from_database_levels(tmp_db, );
            break;
        case STATUSSES_TB_ID: statusses_tb tmp_db; tmp_db.curr_table = 3; read_from_database_statusses(tmp_db, );
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

read_from_database(tb_entity tmp_db) {
    switch (tmp_db.curr_table) {
    case 1: gets()
        break;
    
    default:
        break;
    }
}

int read_file(FILE **file) {
  data data_i;
  int n = getsize_file(file);
  rewind(*file);

  for (int i = 0; i < n; i++) {
    fread(&data_i, sizeof(data), 1, *file);
    printf("%d %d %d %d %d %d %d %d\n", data_i.year, data_i.month, data_i.day,
           data_i.hour, data_i.minute, data_i.sec, data_i.status, data_i.code);
  }
  rewind(*file);
  return 0;