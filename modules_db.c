#include <stdlib.h>
#include "database.h"
#include "tokenizer.h"
#include "parser.h"
#include "io.h"

void start_managing();
void show_menu();
int get_menu_item();
int handle_item(int);
void handle_query();

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

void show_menu() {
    printf(" ,^^'=============='^^.\n");
    printf("|  DB_MANAGING_SYSTEM  |\n");
    printf("'.=======.           .'\n");
    printf("1. SELECT \\           \\\n");
    printf("2. INSERT |            |\n");
    printf("3. UPDATE |            |\n");
    printf("4. DELETE \\_           |\n");
    printf("5. List module          |\n");
    printf("6. Delete modules       |\n");
    printf("7. Protect module       |\n");
    printf("8. Module MEM_LVL/cell \\\n");
    printf("9. Set protection level |\n");
    printf("'----------------------'\n");
}

int get_menu_item() {
    int item;
    int res = scanf("%d", &item);
    int spaces_only = skip_spaces();
    if (res != 1 || !spaces_only)
        item = -1;
    if (item < 0 || item > 9) {
        item = -1;
    }
    return item;
}

int handle_item(int number) {
    int code = 1;
    if (number >= 1 && number <= 4) {
        handle_query();
    }
    switch (number) {
        case 1 : printf("SELECT module by ID\n>> ");
            select_q *query = NULL;
            select(query);
            break;
        case 2 : printf("INSERT module...\n>> ");
            insert_q *insert_query = NULL;
            insert(insert_query);
            break;
        case 3 : printf("UPDATE module by ID\n>> ");
            update_q *update_query = NULL;
            update(update_query);
            break;
        case 4 : printf("DELETE module by ID\n>> ");
            delete_q *delete_query = NULL;
            delete(delete_query);
            break;
        case 5 : printf("GET ALL active modules\n");
            getchar();
            break;
        case 6 : printf("DELETE MODULES\n>> ");
            getchar();
            break;
        case 7 : printf("PROTECT module by ID\n>> ");
            getchar();
            break;
        case 8 : printf("MOVE module by ID\n>> ");
            getchar();
            break;
        case 9 : printf("SET PROTECTION LEVEL TO:\n>> ");
            getchar();
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
        token_t **query_tokens = tokenize(query, query_size, &tokens_size);
        if (query_tokens) {
            query_t *query = parse(query_tokens, tokens_size);
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