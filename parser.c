#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char *modules_columns[TABLE_COLUMNS_MAX_SIZE] = {
    "id", "name", "mem_level_number",
    "level_cell_number", "del_flag",
    NULL,
};

char *levels_columns[TABLE_COLUMNS_MAX_SIZE] = {
   "mem_level_number", "cells_number", "protect_flag",
    NULL,
};

char *statusses_columns[TABLE_COLUMNS_MAX_SIZE] = {
    "event_id", "module_id", "new_module_status",
    "status_date_change", "status_time_change",
    NULL,
};

int search_array(char **array, char *search) {
    int reached = 0;
    for (int i = 0; array[i] != NULL; i++) {
        reached |= strcmp(array[i], search) == 0;
    }
    return reached;
}

int get_index_in_array(char **array, char *search) {
    int index = -1;
    for (int i = 0; array[i] != NULL && index == -1; i++) {
        if (strcmp(array[i], search) == 0)
            index = i;
    }
    return index;
}

int search_array_by_table_id(int table_id, char *column) {
    int res = 0;
    switch (table_id) {
        case MODULES_TB_ID:
            res = search_array(modules_columns, column);
            break;
        case LEVELS_TB_ID:
            res = search_array(levels_columns, column);
            break;
        case STATUSSES_TB_ID:
            res = search_array(statusses_columns, column);
            break;
    }
    return res;
}

int get_index_of_field_in_struct(int table_id, char *column) {
    int index = -1;
    switch (table_id) {
        case MODULES_TB_ID:
            index = get_index_in_array(modules_columns, column);
            break;
        case LEVELS_TB_ID:
            index = get_index_in_array(levels_columns, column);
            break;
        case STATUSSES_TB_ID:
            index = get_index_in_array(statusses_columns, column);
            break;
    }
    return index;
}

parser_t *new_parser(token_t **tokens, int tokens_size) {
    parser_t *parser = (parser_t *)malloc(sizeof(struct Parser));
    parser->tokens = tokens;
    parser->tokens_size = tokens_size;
    parser->state = 1;
    parser->curr_pos = 0;
    return parser;
}

token_t *curr_token(parser_t *parser) {
    token_t *token = NULL;
    if (parser->curr_pos < parser->tokens_size)
        token = parser->tokens[parser->curr_pos];
    return token;
}

void skip_token(parser_t *parser) {
    parser->curr_pos++;
}

int expect_token(parser_t *parser, token_kind_t kind) {
    return curr_token(parser)->kind == kind;
}

token_t *seek_token(parser_t *parser) {
    int seek_pos = parser->curr_pos + 1;
    token_t *seeked = NULL;
    if (seek_pos < parser->tokens_size)
        seeked = parser->tokens[seek_pos];
    return seeked;
}

query_t *parse(token_t **tokens, int tokens_size) {
    printf("Debug [parse]\n");
    parser_t *parser = new_parser(tokens, tokens_size);
    query_t *query = parse_query(parser);
    free(parser);
    return query;
}

query_t *parse_query(parser_t *parser) {
    printf("Debug [parse_query]\n");
    token_t *query_type = curr_token(parser);
    char *str_type = query_type->str_token;
    query_t *query = NULL;
    if (strcmp(str_type, "select") == 0) {
        query = parse_select_query(parser, SELECT_QUERY_ID);
    } else if (strcmp(str_type, "insert") == 0) {
        query = parse_insert_query(parser, INSERT_QUERY_ID);
    } else if (strcmp(str_type, "update") == 0) {
        query = parse_update_query(parser, UPDATE_QUERY_ID);
    } else if (strcmp(str_type, "delete") == 0) {
        query = parse_delete_query(parser, DELETE_QUERY_ID);
    } else {
        _THROW_ERROR("Invalid query type, aborted\n");
        parser->state = 0;
    }
    if (parser->state == 0) {
        free_query(query);
        query = NULL;
    }
    return query;
}

void validate_query_columns(parser_t *parser, char **str_columns, int *bin_columns,
                            int table_id, int columns_idx) {
    int res = 1;
    for (int i = 0; i < columns_idx; i++) { 
        res &= search_array_by_table_id(table_id, str_columns[i]);
        int column_idx = get_index_of_field_in_struct(table_id, str_columns[i]);
        if (column_idx != -1)
            bin_columns[column_idx] = 1;
    }
    if (res == 0) {
        _THROW_ERROR("Some of specified columns are not in table\n");
        parser->state = 0;
    }
}

// select id, name from modules (group by id)

/*

typedef struct SelectQuery {
    int columns[TABLE_COLUMNS_MAX_SIZE];
    int table_id;
} select_q;

*/
query_t *parse_select_query(parser_t *parser, int query_id) {
    printf("Debug [parse_select_query]\n");
    skip_token(parser); // skip select keyword
    int bin_columns[TABLE_COLUMNS_MAX_SIZE], table_id;
    char *str_columns[TABLE_COLUMNS_MAX_SIZE];
    token_t *next;
    int columns_idx = 0;
    // parse columns list
    while ((next = curr_token(parser)) != NULL && parser->state) {
        if (next->kind != TOKEN_WORD) {
            _THROW_ERROR("Expected word token as the name of a column\n");
            parser->state = 0;
        } else {
            printf("NEXT LINE CAN THROW SEGFAULT\n");
            strcpy(str_columns[columns_idx], next->str_token);
            columns_idx++;
            if (!expect_token(parser, TOKEN_COMMA) &&
                strcmp(seek_token(parser)->str_token, "from") != 0) {
                _THROW_ERROR("Expected comma token after column name\n");
                parser->state = 0;
            } else {
                skip_token(parser); // skip comma
            }
        }
    }
    if (next == NULL) {
        _THROW_ERROR("Expected keyword 'from' after columns list\n");
        parser->state = 0;
    } else {

    }
    printf("Debug finish [parse_select_query]");
    validate_query_columns(parser, str_columns, bin_columns, table_id, columns_idx);
    query_t *query = new_query(query_id);
    query->select_query = new_select_query(bin_columns, table_id);
    return query;
}

// insert into modules (id, name) (12, "new module")
query_t *parse_insert_query(parser_t *parser, int query_id) {
    printf("Debug [parse_insert_query]\n");
    return NULL;
}

// update modules set id = 12, name = "updated module"
query_t *parse_update_query(parser_t *parser, int query_id) {
    printf("Debug [parse_update_query]\n");
    return NULL;
}

// delete from modules where id = 2
query_t *parse_delete_query(parser_t *parser, int query_id) {
    printf("Debug [parse_delete_query]\n");
    return NULL;
}
