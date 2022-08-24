#include "database.h"


void start_managing();
void show_menu();
int get_menu_item();
void handle_item(int);

int main() {
    start_managing();
    return 0;
}

void start_managing() {
    int flag = 1;
    while (flag) {
        show_menu();
        printf(">> ");
        int number = get_menu_item();
        if (number == -1) {
            printf("Invalid item number\n");
        } else if (number == 0) {
            flag = 0;
        } else {
            handle_item(number);
        }
    }
}

/*

select column1, column2, ... from <tablename>

1. SELECT
2. INSERT
3. UPDATE
4. DELETE
5. Get all active additional modules (last module status is 1)
6. Delete modules by ids
7. Set protected mode for module by id
8. Move module by id to specified memory level and cell
9. Set protection flag of the specified memory level

*/
int get_menu_item() {

}

void handle_item(int number) {
    int code = 1;
    if (number >= 1 && number <= 4) {
        handle_query();
    }
    switch (number) {
        case 5:
            break;
        default:
            code = 0;
    }
    return code;
}

void handle_query() {
    printf("Type in select query, please: ");
    char *query = get_line_from_stdin();
    token **query_tokens = tokenize(query);
    query_t *query = parse_query(query_tokens);
    switch (query->query_id) {
        case 1: {
            tb_entity *entity = select(query->select_query);
            output_entity(entity);
        }
    }
    free(query);
}