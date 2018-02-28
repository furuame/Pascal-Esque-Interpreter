#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

static void add_reserved_word(Reserved_word_table *table, \
                              token_t token)
{
    table->words[table->num] = token;
    table->num += 1;
}

static void init_reserved_word(Reserved_word_table *table)
{
    table->num = 0;

    token_t token = { .type = NONE, .value = NULL};

    /* Add Reserved Words here */
    token.type = BEGIN; token.value = "BEGIN";
    add_reserved_word(table, token);

    token.type = END; token.value = "END";
    add_reserved_word(table, token);
}

static token_t find_reserved_word(Reserved_word_table *table, \
                                  char *text)
{
    for (int i = 0; i < table->num; i++) {
        char *cmp_reserved_word = (char *) table->words[i].value;
        if (strcmp(cmp_reserved_word, text) == 0) 
            return table->words[i];
    }

    /* It's a identifier */
    token_t token = { .type = ID, .value = text};
    return token;
}

static int isDigit(char target)
{
    if (target >= '0' && target <= '9')
        return 1;
    return 0;
}

static void advance(Lexer *lexer)
{
    lexer->pos += 1;
    if (lexer->pos >= lexer->len) {
        lexer->current_char = '\n';
    } else {
        lexer->current_char = lexer->text[lexer->pos];
    }
}

static int integer(Lexer *lexer)
{
    char number[_AVAILABLE_DIGITS];
    int i = 0;

    do {
        number[i++] = lexer->current_char;
        advance(lexer);
    } while (lexer->current_char != '\n' && isDigit(lexer->current_char));
    number[i] = '\0';
    
    return atoi(number);
}

static void skip_whitespace(Lexer *lexer)
{
    do {
        advance(lexer);
    } while (lexer->current_char == ' ');
}

token_t get_next_token(Lexer *lexer)
{
    token_t ret = {.type = NONE, .value = NULL};

    if (lexer->current_char != '\n') {
        if (lexer->current_char == ' ')
            skip_whitespace(lexer);

        if (lexer->current_char == '\n')
            return ret;

        if (isDigit(lexer->current_char)) {
            ret.value = malloc(sizeof(int));
            * (int *) ret.value = integer(lexer);
            ret.type = INTEGER;
            return ret;
        }

        if (lexer->current_char == '+') {
            ret.type = PLUS;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '-') {
            ret.type = MINUS;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '*') {
            ret.type = MULTIPLY;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '/') {
            ret.type = DIVIDE;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '(') {
            ret.type = LPAREN;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == ')') {
            ret.type = RPAREN;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '^') {
            ret.type = POWER;
            advance(lexer);
            return ret;
        }

        printf("interpreter.c: Unavailable char exists\n");
        exit(0);
    }
    return ret;
}

void match(Lexer *lexer, TYPE type)
{
    if (lexer->current_token.type == type) {
        lexer->current_token = get_next_token(lexer);
    } else {
        printf("interpreter.c: Failed to match rules\n");
        exit(0);
    }
}

Lexer *lexer_init(const char *text)
{
    Lexer *lexer = (Lexer *) malloc(sizeof(Lexer));
    if (!lexer) {
        printf("lexer.c: No available memory for use\n");
        exit(0);
    }
    lexer->pos = 0;
    lexer->len = strlen(text);
    lexer->text = text;
    lexer->current_char = text[0];
    lexer->current_token = get_next_token(lexer);
    init_reserved_word(&lexer->RESERVED_WORDS);
    return lexer;
}

void lexer_destroy(Lexer *lexer)
{
    free(lexer);
}
