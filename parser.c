#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *modules_columns[TABLE_COLUMNS_MAX_SIZE] = {
    "id", "name", "mem_level_number", "level_cell_number", "del_flag", NULL,
};

char *levels_columns[TABLE_COLUMNS_MAX_SIZE] = {
    "mem_level_number",
    "cells_number",
    "protect_flag",
    NULL,
};

char *statusses_columns[TABLE_COLUMNS_MAX_SIZE] = {
    "event_id",           "module_id",          "new_module_status",
    "status_date_change", "status_time_change", NULL,
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
  default:
    fprintf(stderr, "Unknown type of table\n");
    break;
  }
  return index;
}

int get_table_id_by_name(char *name) {
  int table_id = 0;
  if (strcmp(name, "modules") == 0)
    table_id = MODULES_TB_ID;
  else if (strcmp(name, "levels") == 0)
    table_id = LEVELS_TB_ID;
  else if (strcmp(name, "statusses") == 0)
    table_id = STATUSSES_TB_ID;
  return table_id;
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

void skip_token(parser_t *parser) { parser->curr_pos++; }

int expect_token(parser_t *parser, token_kind_t kind) {
  return curr_token(parser)->kind == kind;
}

query_t *parse(token_t **tokens, int tokens_size) {
  parser_t *parser = new_parser(tokens, tokens_size);
  query_t *query = parse_query(parser);
  free(parser);
  return query;
}

query_t *parse_query(parser_t *parser) {
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
  }
  return query;
}

void validate_query_columns(parser_t *parser, char **str_columns,
                            int *bin_columns, int table_id, int columns_idx) {
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
query_t *parse_select_query(parser_t *parser, int query_id) {
  skip_token(parser);  // skip select keyword
  int bin_columns[TABLE_COLUMNS_MAX_SIZE], table_id;
  char *str_columns[TABLE_COLUMNS_MAX_SIZE];
  token_t *next;
  int columns_idx = 0;
  // parse columns list
  while ((next = curr_token(parser)) != NULL &&
         next->kind != TOKEN_FROM_KEYWORD && parser->state) {
    if (next->kind != TOKEN_WORD) {
      _THROW_ERROR("Expected word token as the name of a column, got '%s'\n",
                   next->str_token);
      parser->state = 0;
    } else {
      str_columns[columns_idx] = next->str_token;
      columns_idx++;
      skip_token(parser);   // skip column name
      if (!expect_token(parser, TOKEN_COMMA) &&
          curr_token(parser)->kind != TOKEN_FROM_KEYWORD) {
        _THROW_ERROR("Expected comma token after column name\n");
        parser->state = 0;
      } else if (curr_token(parser)->kind != TOKEN_FROM_KEYWORD) {
        skip_token(parser);   // skip comma
        if (curr_token(parser)->kind == TOKEN_FROM_KEYWORD) {
          _THROW_ERROR("Expected column name after comma\n");
          parser->state = 0;
        }
      }
    }
  }
  if (next == NULL) {
    _THROW_ERROR("Expected keyword 'from' after columns list\n");
    parser->state = 0;
  } else {
    skip_token(parser);  // skip from keyword
    table_id = get_table_id_by_name(curr_token(parser)->str_token);
    skip_token(parser);  // skip table name
  }

  validate_query_columns(parser, str_columns, bin_columns, table_id,
                         columns_idx);
  query_t *query = new_query(query_id);
  query->select_query = new_select_query(bin_columns, table_id);
  return query;
}

// insert into modules (id, name) (12, "new module")
query_t *parse_insert_query(parser_t *parser, int query_id) {
  skip_token(parser);  // skip insert keyword
  int bin_columns[TABLE_COLUMNS_MAX_SIZE], table_id, size = 0;
  token_t **values = NULL;
  if (!expect_token(parser, TOKEN_INTO_KEYWORD)) {
    _THROW_ERROR("Expected 'into' keyword after 'insert' keyword\n");
    parser->state = 0;
  } else {
    skip_token(parser);  // skip into keyword
    table_id = get_table_id_by_name(curr_token(parser)->str_token);
    skip_token(parser);  // skip table name
    if (!expect_token(parser, TOKEN_OPEN_BRACKET)) {
      _THROW_ERROR("Expected open bracket after table name\n");
      parser->state = 0;
    } else {
      skip_token(parser);  // skip open bracket
      token_t *next;
      while ((next = curr_token(parser)) != NULL &&
             next->kind != TOKEN_CLOSE_BRACKET && parser->state) {
        if (next->kind != TOKEN_WORD) {
          _THROW_ERROR("Expected word token as the name of a column\n");
          parser->state = 0;
        } else if (!search_array_by_table_id(table_id, next->str_token)) {
          _THROW_ERROR("Invalid table column name\n");
          parser->state = 0;
        } else {
          int column_idx =
              get_index_of_field_in_struct(table_id, next->str_token);
          bin_columns[column_idx] = 1;
          size++;
          skip_token(parser);  // skip column name
          if (!expect_token(parser, TOKEN_COMMA) &&
              curr_token(parser)->kind != TOKEN_CLOSE_BRACKET) {
            _THROW_ERROR("Expected comma token after column name\n");
            parser->state = 0;
          } else if (curr_token(parser)->kind != TOKEN_CLOSE_BRACKET) {
            skip_token(parser);  // skip comma
          }
        }
      }
      if (next == NULL) {
        _THROW_ERROR("Can't find close bracket\n");
        parser->state = 0;
      } else {
        values = (token_t **)malloc(size * sizeof(struct Token *));
        int values_idx = 0;
        skip_token(parser);  // skip close bracket
        if (!expect_token(parser, TOKEN_OPEN_BRACKET)) {
          _THROW_ERROR("Expected open bracket after (colunms...)\n");
          parser->state = 0;
        } else {
          skip_token(parser);  // skip open bracket
          while ((next = curr_token(parser)) != NULL &&
                 next->kind != TOKEN_CLOSE_BRACKET && parser->state) {
            skip_token(parser);  // skip column name
            values[values_idx] = next;
            if (!expect_token(parser, TOKEN_COMMA) &&
                curr_token(parser)->kind != TOKEN_CLOSE_BRACKET) {
              _THROW_ERROR("Expected comma token after column value\n");
              parser->state = 0;
            } else if (curr_token(parser)->kind != TOKEN_CLOSE_BRACKET) {
              skip_token(parser);  // skip comma
            }
          }
        }
      }
    }
  }
  query_t *query = new_query(query_id);
  query->insert_query = new_insert_query(table_id, bin_columns, size, values);
  return query;
}

// update modules set id = 12, name = "updated module"
query_t *parse_update_query(parser_t *parser, int query_id) {
  skip_token(parser);  // skip update keyword
  int table_id = get_table_id_by_name(curr_token(parser)->str_token);
  token_t **values =
      (token_t **)malloc(TABLE_COLUMNS_MAX_SIZE * sizeof(struct Token *));
  int bin_columns[TABLE_COLUMNS_MAX_SIZE], size = 0;
  int values_idx = 0;
  if (!expect_token(parser, TOKEN_SET_KEYWORD)) {
    _THROW_ERROR("Expected 'set' keyword after table name\n");
    parser->state = 0;
  } else {
    skip_token(parser);  // skip set keyword
    token_t *next;
    while ((next = curr_token(parser)) != NULL && parser->state) {
      if (!search_array_by_table_id(table_id, next->str_token)) {
        _THROW_ERROR("Invalid table column name\n");
        parser->state = 0;
      } else {
        int column_idx =
            get_index_of_field_in_struct(table_id, next->str_token);
        bin_columns[column_idx] = 1;
        size++;
        if (!expect_token(parser, TOKEN_ASSIGN)) {
          _THROW_ERROR("Expected '=' token after column name\n");
          parser->state = 0;
        } else {
          skip_token(parser);  // skip assign token
          token_t *value = curr_token(parser);
          values[values_idx] = value;
          skip_token(parser);  // skip value token
          if (!expect_token(parser, TOKEN_COMMA) &&
              curr_token(parser) != NULL) {
            _THROW_ERROR("Expected comma token after column expression\n");
            parser->state = 0;
          } else {
            skip_token(parser);  // skip comma
            if (curr_token(parser) == NULL) {
              _THROW_ERROR("Expected column expression after comma\n");
              parser->state = 0;
            }
          }
        }
      }
    }
  }
  query_t *query = new_query(query_id);
  query->update_query = new_update_query(table_id, bin_columns, size, values);
  return query;
}

// delete from modules where id = 2
query_t *parse_delete_query(parser_t *parser, int query_id) {
  skip_token(parser);  // skip delete keyword
  int table_id;
  token_t **values = (token_t **)malloc(sizeof(struct Token *));
  int bin_columns[TABLE_COLUMNS_MAX_SIZE], size = 0;
  int values_idx = 0;
  if (!expect_token(parser, TOKEN_FROM_KEYWORD)) {
    _THROW_ERROR("Expected 'from' keyword after 'delete' keyword\n");
    parser->state = 0;
  } else {
    skip_token(parser);  // skip from token
    table_id = get_table_id_by_name(curr_token(parser)->str_token);
    skip_token(parser);  // skip table name
    if (!expect_token(parser, TOKEN_WHERE_KEYWORD)) {
      _THROW_ERROR("Expected 'where' keyword after table name\n");
      parser->state = 0;
    } else {
      skip_token(parser);  // skip where keyword
      token_t *column_name = curr_token(parser);
      if (!search_array_by_table_id(table_id, column_name->str_token)) {
        _THROW_ERROR("Invalid table column name\n");
        parser->state = 0;
      } else {
        int column_idx =
            get_index_of_field_in_struct(table_id, column_name->str_token);
        bin_columns[column_idx] = 1;
        size++;
        if (!expect_token(parser, TOKEN_ASSIGN)) {
          _THROW_ERROR("Expected assign token after column name\n");
          parser->state = 0;
        } else {
          skip_token(parser);  // skip assign token
          token_t *value = curr_token(parser);
          values[0] = value;
          skip_token(parser);  // skip value token
        }
      }
    }
  }
  query_t *query = new_query(query_id);
  query->delete_query = new_delete_query(table_id, bin_columns, size, values);
  return query;
}
