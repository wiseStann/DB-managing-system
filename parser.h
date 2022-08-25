#ifndef PARSER_H_
#define PARSER_H_

#include "database.h"
#include "tokenizer.h"


#define _THROW_ERROR(fmt, ...) {              \
    char err_message[ERR_MESSAGE_MAX_LEN];    \
    sprintf(err_message, fmt, ##__VA_ARGS__); \
    fprintf(stderr, err_message);             \
}

extern char *modules_columns[TABLE_COLUMNS_MAX_SIZE];
extern char *levels_column[TABLE_COLUMNS_MAX_SIZE];
char *statusses_column[TABLE_COLUMNS_MAX_SIZE];

int search_array(char **array, char *search);

int 
typedef struct Parser {
    token_t **tokens;
    int tokens_size;
    int curr_pos;
    int state;
} parser_t;

parser_t *new_parser(token_t **tokens, int tokens_size);

token_t *curr_token(parser_t *parser);

void skip_token(parser_t *parser);

query_t *parse(token_t **tokens, int tokens_size);

query_t *parse_query(parser_t *parser);

query_t *parse_select_query(parser_t *parser, int query_id);

query_t *parse_insert_query(parser_t *parser, int query_id);

query_t *parse_update_query(parser_t *parser, int query_id);

query_t *parse_delete_query(parser_t *parser, int query_id);


#endif  // PARSER_H_
