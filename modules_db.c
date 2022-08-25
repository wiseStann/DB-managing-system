#include "database.h"
#include <stdio.h>
#include <ctype.h>

void start_managing();
void show_menu();
int get_menu_item();
int scan_for_non_blank();
int read_stdin();
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

/*

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
    int m;
    if ((m = read_stdin()) > 0) {
        if (m > 0 && m < 10)
            handle_item(m);
        else
            m = -1;
    } else {
        m = -1;
    }
    return m;
}

void handle_item(int number) {
    switch (number) {
        case 1 : printf("SELECT module by ID\n>> ");
            getchar();
            break;
        case 2 : printf("INSERT module...\n>> ");
            getchar();
            break;
        case 3 : printf("UPDATE module by ID\n>> ");
            getchar();
            break;
        case 4 : printf("DELETE module by ID\n>> ");
            getchar();
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
    }
}

int scan_for_non_blank() {
  int non_blank = 1;
  int c;
  while ((c = getchar()) && c != EOF && c != '\n') {
    if (!isspace(c))
      non_blank = 0;
  }
  return non_blank;
}

int read_stdin() {
    int m = 1;
    int res = scanf("%d", &m);
    int spaces_only = scan_for_non_blank();
    if (res != 1 || !spaces_only)
        m = 0;
//    if (c < 1 || c > 31 || c < 1 || c > 12)
//        code = 0;
    return m;
}
