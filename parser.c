#include <stdlib.h>
#include <string.h>
#include "parser.h"


char *modules_column[TABLE_COLUMNS_MAX_SIZE] = {
    "id", "name", "mem_level_number",
    "level_cell_number", "del_flag",
    NULL,
};

char *levels_column[TABLE_COLUMNS_MAX_SIZE] = {
   "mem_level_number", "cells_number", "protect_flag",
    NULL,
};

char *statusses_column[TABLE_COLUMNS_MAX_SIZE] = {
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
    return query;
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
    skip_token(); // skip select keyword
    int columns[TABLE_COLUMNS_MAX_SIZE], table_id;
    token_t *next;

    // parse columns list
    while ((next = curr_token()) != NULL) {
        if (next->kind != TOKEN_WORD) {
            _THROW_ERROR("Expected word token as the name of a column\n");
            parser->state = 0;
            break;
        } else if (search_array()) {
            
        }
    }
    if (next == NULL) {
        _THROW_ERROR("Expected keyword 'from' after columns list\n");
        parser->state = 0;
    } else {

    }
    query_t *query = new_query(query_id);
    query->select_query = new_select_query(columns, table_id);
    return query;
}

// insert into modules (id, name) (12, "new module")
insert_q *parse_insert_query(parser_t *parser, int query_id) {
    printf("Debug [parse_insert_query]\n");

}

// update modules set id = 12, name = "updated module"
update_q *parse_update_query(parser_t *parser, int query_id) {
    printf("Debug [parse_update_query]\n");

}

// delete from modules where id = 2
delete_q *parse_delete_query(parser_t *parser, int query_id) {
    printf("Debug [parse_delete_query]\n");

}
