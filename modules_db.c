#include "database.h"
#include "io.h"

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

0. Exit
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
    int item;
    int res = scanf("%d", &item);
    int spaces_only = skip_spaces();
    if (res != 1 || !spaces_only)
        item = -1;
    if (item < 0 || item > 9) {
        item = -1
    }
    return item;
}

void handle_item(int number) {
    int code = 1;
    if (number >= 1 && number <= 4) {
        handle_query();
    }
    switch (number) {
        case 5 : //get_active_mods();
            break;
        case 6 : //delete_mods();
            break;
        case 7 : //lockdown();
            break;
        case 8 : //escalate();
            break;
        case 9 : //set_mem_level();
            break;
        default:
            code = 0;
    }
    return code;
}

void handle_query() {
    printf("Type in select query, please: ");
    int query_size, tokens_size;
    char *query = get_line_from_stdin(&query_size);
    if (query) {
        token **query_tokens = tokenize_query(query, query_size, &tokens_size);
        if (query_tokens) {
            query_t *query = parse_query(query_tokens, tokens_size);
            if (query) {
                // switch (query->query_id) {
                //     case 1:
                //         select(query->select_query);
                //         break;
                //     case 2:
                //         insert(query->insert_query);
                //         break;
                //     case 3:
                //         update(query->update_query);
                //         break;
                //     case 4:
                //         delete(query->delete_query);
                //         break;
                //     default:
                //         fprintf(stderr, "Invalid type of query [handle_query]\n");
                //         break;
                // }
                for (int i = 0; i < tokens_size; i++)
                    free(query_tokens[i]);
                free(query_tokens);
            }
        }
        free(query);
    }
}