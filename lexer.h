#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"

#define _AVAILABLE_DIGITS 100

typedef struct __lexer Lexer;

struct __lexer {
    int pos;
    int len;
    const char *text;
    char current_char;
    token_t current_token;
};

Lexer *lexer_init(const char *text);
void lexer_destroy(Lexer *lexer);
token_t get_next_token(Lexer *lexer);
void match(Lexer *lexer, TYPE type);

#endif
