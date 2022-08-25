#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

char *_keywords = {
    "select", "insert", "update",
    "delete", "from", "group by",
    "into", "set", "where", NULL,
};

int is_key_word(char *word) {
    int found = 0;
    for (int i = 0; _keywords[i] != NULL; i++) {
        found |= strcmp(_keywords[i], word) == 0;
    }
    return found;
}

token_t *new_token(char str_token[WORD_MAX_LEN], token_kind_t kind) {
    token_t *token = (token_t *)malloc(sizeof(struct Token));
    token->kind = kind;
    strcpy(token->str_token, str_token);
    return token;
}

token_kind_t get_punct_kind(char symbol) {
    token_kind_t kind;
    switch (symbol) {
        case '(':
            kind = TOKEN_OPEN_BRACKET;
            break;
        case ')':
            kind = TOKEN_CLOSE_BRACKET;
            break;
        case '*':
            kind = TOKEN_STAR;
            break;
        case ',':
            kind = TOKEN_COMMA;
            break;
    }
    return kind;
}

tokenizer_t *new_tokenizer(char *query, int query_size) {
    tokenizer_t *t = (tokenizer_t *)malloc(sizeof(struct Tokenizer));
    t->query = query;
    t->query_size = query_size;
    t->curr_pos = 0;
    t->state = 1;
    return t;
}

char curr_symbol(tokenizer_t *t) {
    char ch = 0;
    if (t->curr_pos < t->query_size)
        ch = t->query[t->curr_pos];
    return ch;
}

void skip_char(tokenizer_t *t) {
    t->curr_pos++;
}

token_t **tokenize(char *query, int query_size, int *tokens_size) {
    printf("Debug [tokenize]\n");
    tokenizer_t *t = new_tokenizer(query, query_size);
    token_t **tokens = tokenize_query(t);
    *tokens_size = t->curr_pos;
    if (t->state == 0) {
        for (int i = 0; i < tokens_size; i++)
            free(tokens[i]);
        free(tokens);
        tokens = NULL;
    }
    free(t);
    return tokens;
}

token_t **tokenize_query(tokenizer_t *t) {
    printf("Debug [tokenize_query]\n");
    token_t **tokens = (token_t **)malloc(sizeof(struct Token*));
    for (; t->curr_pos < t->query_size; ) {
        char current = curr_symbol(t);
        token_t *next_token = NULL;
        if (isalpha(current))
            next_token = tokenize_word(t);
        else if (isdigit(current))
            next_token = tokenize_number(t);
        else
            next_token = tokenize_punctuator(t);
    }
}

token_t *tokenize_word(tokenizer_t *t) {
    printf("Debug [tokenize_word]\n");
    char str_word[TOKEN_MAX_LEN], next;
    int idx = 0;
    while (isalpha(next = curr_symbol(t))) {
        str_word[idx] = next;
        skip_char(t);
        idx++;
    }
    str_word[idx] = '\0';
    token_kind_t kind;
    if (is_key_word(str_word))
        kind = TOKEN_KEYWORD;
    else
        kind = TOKEN_WORD;
    return new_token(str_word, kind);
}

token_t *tokenize_number(tokenizer_t *t) {
    printf("Debug [tokenize_number]\n");
    char str_number[TOKEN_MAX_LEN], next;
    int idx = 0;
    while (isdigit(next = curr_symbol())) {
        str_number[idx] = next;
        skip_char(t);
        idx++;
    }
    str_number[idx] = '\0';
    return new_token(str_number, TOKEN_NUMBER);
}

token_t *tokenize_punctuator(tokenizer_t *t) {
    printf("Debug [tokenize_punctuator]\n");
    token_t *token = NULL;
    char current = curr_symbol(t);
    if (current == '\"')
        token = tokenize_string(t);
    else {
        token_kind_t kind;
        token = new_token(current, get_punct_kind(current));
    }
    return token;
}

token_t *tokenize_string(tokenizer_t *t) {
    printf("Debug [tokenize_string]\n");
    skip_char(t); // skip open double quote
    char str_string[TOKEN_MAX_LEN], next;
    int idx = 0;
    while ((next = curr_symbol(t)) != '\"' && next != 0) {
        str_string[idx] = next;
        skip_char(t);
        idx++;
    }
    if (next == 0) {
        fprintf(stderr, "Can't find close double quote\n");
        t->state = 0;
    }
    str_string[idx] = '\0';
    return new_token(str_string, TOKEN_STRING);
}
