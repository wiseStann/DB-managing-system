#ifndef PARSER_H_
#define PARSER_H_

#include "database.h"
#include "tokenizer.h"

#define ERR_MESSAGE_MAX_LEN 128

#define _THROW_ERROR(fmt, ...) {              \
    char err_message[ERR_MESSAGE_MAX_LEN];    \
    sprintf(err_message, fmt, ##__VA_ARGS__); \
    fprintf(stderr, err_message);             \
}

extern char *modules_columns[TABLE_COLUMNS_MAX_SIZE];
extern char *levels_columns[TABLE_COLUMNS_MAX_SIZE];
extern char *statusses_columns[TABLE_COLUMNS_MAX_SIZE];

int search_array(char **array, char *search);

int search_array_by_table_id(int query_id, char *column);

int get_index_of_field_in_struct(int table_id, char *column);

int get_table_id_by_name(char *name);


typedef struct Parser {
    token_t **tokens;
    int tokens_size;
    int curr_pos;
    int state;
} parser_t;

parser_t *new_parser(token_t **tokens, int tokens_size);

token_t *curr_token(parser_t *parser);

void skip_token(parser_t *parser);
int expect_token(parser_t *parser, token_kind_t kind);
token_t *seek_token(parser_t *parser);

query_t *parse(token_t **tokens, int tokens_size);

query_t *parse_query(parser_t *parser);

void validate_query_columns(parser_t *parser, char **str_columns, int *bin_columns,
                            int table_id, int columns_idx);

query_t *parse_select_query(parser_t *parser, int query_id);

query_t *parse_insert_query(parser_t *parser, int query_id);

query_t *parse_update_query(parser_t *parser, int query_id);

query_t *parse_delete_query(parser_t *parser, int query_id);


#endif  // PARSER_H_
