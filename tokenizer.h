#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#define TOKEN_MAX_LEN 128

extern char *_keywords[10];

int is_key_word(char *word);

typedef enum TokenKind {
    TOKEN_SELECT_KEYWORD,
    TOKEN_INSERT_KEYWORD,
    TOKEN_UPDATE_KEYWORD,
    TOKEN_DELETE_KEYWORD, 
    TOKEN_FROM_KEYWORD,
    TOKEN_GROUP_BY_KEYWORD,
    TOKEN_INTO_KEYWORD,
    TOKEN_SET_KEYWORD,
    TOKEN_WHERE_KEYWORD,

    TOKEN_WORD,
    TOKEN_STRING,
    TOKEN_NUMBER,

    TOKEN_ASSIGN,
    TOKEN_COMMA,
    TOKEN_STAR,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
} token_kind_t;

typedef struct Token {
    union {
        int  number;
        char string[TOKEN_MAX_LEN];
    };
    char str_token[TOKEN_MAX_LEN];
    token_kind_t kind;
} token_t;

token_t *new_token(char str_token[TOKEN_MAX_LEN], token_kind_t kind);

token_kind_t get_punct_kind(char symbol);


typedef struct Tokenizer {
    char *query;
    int query_size;
    int curr_pos;
    int state;
} tokenizer_t;

tokenizer_t *new_tokenizer(char *query, int query_size);

token_t **tokenizer(char *query, int query_size, int *tokens_size);

char curr_symbol(tokenizer_t *t);

void skip_char(tokenizer_t *t);

token_t **tokenize(char *query, int query_size, int *tokens_size);

token_t **tokenize_query(tokenizer_t *t);

token_t *tokenize_word(tokenizer_t *t);

token_t *tokenize_number(tokenizer_t *t);

token_t *tokenize_punctuator(tokenizer_t *t);

token_t *tokenize_string(tokenizer_t *t);


#endif  // TOKENIZER_H_
