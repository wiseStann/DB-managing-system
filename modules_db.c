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
//        show_menu();
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
        case 1 : //select();
            break;
        case 2 : //insert();
            break;
        case 3 : //update();
            break;
        case 4 : //delete();
            break;
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
