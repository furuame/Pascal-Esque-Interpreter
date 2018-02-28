#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"

#define _AVAILABLE_DIGITS 100
#define _MAX_RESERVED_WORDS 20

typedef struct __reserved_word_table Reserved_word_table;

struct __reserved_word_table {
    token_t words[_MAX_RESERVED_WORDS];
    int num;
};

typedef struct __lexer Lexer;

struct __lexer {
    int pos;
    int len;
    const char *text;
    char current_char;
    token_t current_token;
    Reserved_word_table RESERVED_WORDS;
};

Lexer *lexer_init(const char *text);
void lexer_destroy(Lexer *lexer);
token_t get_next_token(Lexer *lexer);
void match(Lexer *lexer, TYPE type);

#endif
